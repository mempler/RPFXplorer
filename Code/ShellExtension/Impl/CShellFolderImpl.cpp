#include "pch.h"
#include "CShellFolderImpl.h"

#pragma comment(lib, "SHELL32.LIB")

// Some code have been copied from https://www.codeproject.com/Articles/1649/The-Complete-Idiot-s-Guide-to-Writing-Namespace-Ex
// Thanks for this detailed explanation! 

HANDLE hLog;

#define QUICK_DBG \
    const wchar_t* message = __FUNCTIONW__; \
    ReportEventW(hLog, EVENTLOG_WARNING_TYPE, 0, 12341, NULL, 1, 0, &message, NULL)

STDMETHODIMP CShellFolderImpl::GetClassID(CLSID* pClsid)
{
    QUICK_DBG;

    *pClsid = CLSID_ShellFolderImpl;
    return S_OK;
}

////////////////////////////////

STDMETHODIMP CShellFolderImpl::Initialize(LPCITEMIDLIST pidl)
{
    //
    // Members
    //
    if (m_pActiveRPF == NULL)
    {
        m_pActiveRPF = new RPFReader();
    }

    //
    // Variables
    //
    HRESULT hr = S_OK;
    wchar_t path[MAX_PATH];
    HANDLE hFile = NULL;

    //
    // hLog, used for QUICK_DBG
    //
    if (hLog != NULL)
    {
        hLog = RegisterEventSource(NULL, L"RPFXplorer");
    }

    QUICK_DBG;

    SHGetPathFromIDListW(pidl, path);
    
    //
    // Open the file in READ-ONLY mode
    //
    hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == NULL || hFile == INVALID_HANDLE_VALUE)
    {
        hr = E_UNEXPECTED;
    }

    //
    // Open the RPF file
    //
    return m_pActiveRPF->Open(hFile);
}

////////////////////////////////

struct PIDLDATA
{
    RPFEntry* m_pEntry;
};

class CPIDLManager
{
public:
    CPIDLManager()
    {
        ATLASSERT(SUCCEEDED(SHGetMalloc(&m_spMalloc)));
    }

    ~CPIDLManager()
    {
    }

    LPITEMIDLIST Create(RPFEntry* pEntry)
    {
        UINT uSize = sizeof(ITEMIDLIST) + sizeof(PIDLDATA);
        LPITEMIDLIST pidl = (LPITEMIDLIST)m_spMalloc->Alloc(uSize + sizeof(ITEMIDLIST));
        if (pidl)
        {
            LPITEMIDLIST pidlTemp = pidl;

            // Prepares the PIDL to be filled with actual data
            pidlTemp->mkid.cb = uSize;
            PIDLDATA* pData = (PIDLDATA*)pidlTemp->mkid.abID;

            // Fill the PIDL
            pData->m_pEntry = pEntry;

            // A PIDL of size 0 means the end of the chain
            pidlTemp = GetNextItem(pidlTemp);
            pidlTemp->mkid.cb = 0;
            pidlTemp->mkid.abID[0] = 0;
        }
        return pidl;
    }

    void Delete(LPITEMIDLIST pidl)
    {
        m_spMalloc->Free(pidl);
    }

    LPITEMIDLIST GetNextItem(LPCITEMIDLIST pidl)
    {
        ATLASSERT(pidl != NULL);

        return LPITEMIDLIST(LPBYTE(pidl) + pidl->mkid.cb);
    }

    LPITEMIDLIST GetLastItem(LPCITEMIDLIST pidl)
    {
        LPITEMIDLIST pidlLast = NULL;

        ATLASSERT(pidl != NULL);

        while (0 != pidl->mkid.cb)
        {
            pidlLast = (LPITEMIDLIST)pidl;
            pidl = GetNextItem(pidl);
        }

        return pidlLast;
    }

    PIDLDATA* GetData(LPCITEMIDLIST pidl)
    {
        LPITEMIDLIST pLast;
        PIDLDATA* pData;

        if (pidl == NULL)
            return NULL;

        // Get the last item of the PIDL to make sure we get the right TCHAR
        // in case of multiple nesting levels
        pLast = GetLastItem(pidl);

        pData = (PIDLDATA*)(pLast->mkid.abID);

        return pData;
    }

private:
    CComPtr<IMalloc> m_spMalloc;
};

static CPIDLManager s_PIDLManager;

class CCopyTcharToPidl
{
public:
    static void init(LPITEMIDLIST* p)
    {
        // No init needed.
    }

    static HRESULT copy(LPITEMIDLIST* pTo, const RPFEntry* pEntry)
    {
        *pTo = s_PIDLManager.Create((RPFEntry*)pEntry);
        return (NULL != *pTo) ? S_OK : E_OUTOFMEMORY;
    }

    static void destroy(LPITEMIDLIST* p)
    {
        s_PIDLManager.Delete(*p);
    }
};

typedef CComEnumOnSTL<IEnumIDList, &IID_IEnumIDList, LPITEMIDLIST, CCopyTcharToPidl, std::vector<RPFEntry>> CEnumIDListImpl;

STDMETHODIMP CShellFolderImpl::BindToObject(LPCITEMIDLIST pidl, LPBC pbcReserved, REFIID riid, void** ppvOut)
{
    QUICK_DBG;

    HRESULT hr = S_OK;

    if (riid != IID_IShellFolder)
        return E_NOINTERFACE;

    CComObject<CShellFolderImpl>* pNewSelf = 0;
    hr = CComObject<CShellFolderImpl>::CreateInstance(&pNewSelf);
    if (FAILED(hr))
        return hr;

    pNewSelf->AddRef();

    auto* data = s_PIDLManager.GetData(pidl);
    if (data == NULL || data->m_pEntry == NULL)
        return E_POINTER;

    pNewSelf->m_pActiveRPF = m_pActiveRPF;

    hr = pNewSelf->QueryInterface(riid, ppvOut);

    pNewSelf->Release();

    return hr;
}

STDMETHODIMP CShellFolderImpl::CompareIDs(LPARAM, LPCITEMIDLIST, LPCITEMIDLIST)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::CreateViewObject(HWND hwndOwner, REFIID riid, void** ppvOut)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::EnumObjects(HWND hwndOwner, DWORD dwFlags, LPENUMIDLIST* ppEnumIDList)
{
    QUICK_DBG;
    HRESULT hr;

    if (ppEnumIDList == NULL)
        return E_POINTER;

    *ppEnumIDList = NULL;

    CComObject<CEnumIDListImpl>* pEnum;
    hr = CComObject<CEnumIDListImpl>::CreateInstance(&pEnum);
    if (FAILED(hr))
        return hr;

    pEnum->AddRef();

    auto entries = m_pActiveRPF->GetSubEntries(&m_pActiveRPF->GetRootEntry());
    hr = pEnum->Init(GetUnknown(), entries);

    if (SUCCEEDED(hr))
        hr = pEnum->QueryInterface(IID_IEnumIDList, (void**)ppEnumIDList);

    pEnum->Release();

    return hr;
}

STDMETHODIMP CShellFolderImpl::GetAttributesOf(UINT uCount, LPCITEMIDLIST aPidls[], LPDWORD pdwAttribs)
{
    QUICK_DBG;

    *pdwAttribs = -1;

    for (UINT i = 0; i < uCount; i++)
    {
        DWORD dwAttr = 0;

        auto* data = s_PIDLManager.GetData(aPidls[i]);

        if (data->m_pEntry != NULL)
        {
            dwAttr |= SFGAO_FOLDER | SFGAO_COMPRESSED | SFGAO_ENCRYPTED;

            if (!m_pActiveRPF->GetSubEntries(data->m_pEntry).empty())
            {
                dwAttr |= SFGAO_HASSUBFOLDER;
            }
        }

        *pdwAttribs &= dwAttr;
    }

    return S_OK;
}

STDMETHODIMP CShellFolderImpl::GetUIObjectOf(HWND hwndOwner, UINT uCount, LPCITEMIDLIST* pPidl, REFIID riid, LPUINT puReserved, void** ppvReturn)
{
    QUICK_DBG;

    HRESULT hr = S_OK;

    if (ppvReturn == NULL)
        return E_POINTER;

    // Make sure we support the given riid
    if (  riid != IID_IExtractIconA
    /* && riid != IID_INameSpaceTreeControlFolderCapabilities */
        )
        return NTE_NOT_SUPPORTED;


    for (size_t i = 0; i < uCount; i++)
    {
        if (riid == IID_IExtractIconA)
        {
            // get the icon for the given file / directory
            auto data = s_PIDLManager.GetData(pPidl[i]);
            if (data->m_pEntry != NULL)
            {
                hr = SHCreateFileExtractIconW(L"/", FILE_ATTRIBUTE_DIRECTORY, riid, ppvReturn);
            }
            else
            {
                std::wstring name = m_pActiveRPF->GetNameW(data->m_pEntry);
                hr = SHCreateFileExtractIconW(name.c_str(), FILE_ATTRIBUTE_NORMAL, riid, ppvReturn);
            }
        }

        if (hr != S_OK)
            return hr;
    }

    return hr;
}

STDMETHODIMP CShellFolderImpl::BindToStorage(LPCITEMIDLIST pidl, LPBC pbc, REFIID riid, void** ppv)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::GetDisplayNameOf(LPCITEMIDLIST pidl, DWORD uFlags, LPSTRRET pName)
{
    QUICK_DBG;

    auto name = m_pActiveRPF->GetNameA(s_PIDLManager.GetData(pidl)->m_pEntry);
    pName->uType = STRRET_CSTR;
    strcpy_s(pName->cStr, MAX_PATH, name.c_str());

    return S_OK;
}

STDMETHODIMP CShellFolderImpl::ParseDisplayName(HWND hwnd, LPBC pbc, LPOLESTR pszDisplayName, LPDWORD pchEaten, LPITEMIDLIST* ppidl, LPDWORD pdwAttributes)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::SetNameOf(HWND hwnd, LPCITEMIDLIST pidl, LPCOLESTR pszName, DWORD uFlags, LPITEMIDLIST* ppidlOut)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

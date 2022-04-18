#include "pch.h"
#include "CShellFolderImpl.h"

#include "RPF.h"

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
    QUICK_DBG;

    hLog = RegisterEventSource(NULL, L"RPFXplorer");

    wchar_t path[MAX_PATH];
    SHGetPathFromIDListW(pidl, path);
    
    HANDLE hFile = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    m_pActiveRPFReader = new RPFReader();
    m_pActiveRPFReader->Open(hFile);
    m_pActiveRPF = new RPF(m_pActiveRPFReader);

    m_pActiveDirectory = m_pActiveRPF->OpenDir("/");
    m_pWorkingPidl = pidl;

    return S_OK;
}

STDMETHODIMP CShellFolderImpl::GetCurFolder(PIDLIST_ABSOLUTE* pidl)
{
    QUICK_DBG;

    if (pidl == NULL)
        return E_POINTER;

    // Copy the pidl
    *pidl = (LPITEMIDLIST)ILClone(m_pWorkingPidl);

    return S_OK;
}

////////////////////////////////

struct PIDLDATA
{
    // Will be set depending if it's a file or dir lol
    const RPF::Directory* m_pDir;
    const RPF::File* m_pFile;
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

    LPITEMIDLIST Create(const RPF::Directory* pDirectory)
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
            pData->m_pDir = pDirectory;

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

    UINT GetSize(LPCITEMIDLIST pidl)
    {
        UINT uSize = 0;
        LPITEMIDLIST pidlTemp = (LPITEMIDLIST)pidl;

        ATLASSERT(pidl != NULL);

        while (0 != pidlTemp->mkid.cb)
        {
            uSize += pidlTemp->mkid.cb;
            pidlTemp = GetNextItem(pidlTemp);
        }

        // add the size of the NULL terminating ITEMIDLIST
        uSize += sizeof(ITEMIDLIST);

        return uSize;
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

    LPITEMIDLIST Concatenate(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
    {
        LPITEMIDLIST   pidlNew;
        UINT           cb1 = 0,
            cb2 = 0;

        //are both of these NULL?
        if (!pidl1 && !pidl2)
            return NULL;

        //if pidl1 is NULL, just return a copy of pidl2
        if (!pidl1)
        {
            pidlNew = Copy(pidl2);
            return pidlNew;
        }

        //if pidl2 is NULL, just return a copy of pidl1
        if (!pidl2)
        {
            pidlNew = Copy(pidl1);
            return pidlNew;
        }

        cb1 = GetByteSize(pidl1) - sizeof(ITEMIDLIST);
        cb2 = GetByteSize(pidl2);

        //create the new PIDL
        pidlNew = (LPITEMIDLIST)m_spMalloc->Alloc(cb1 + cb2);
        if (pidlNew)
        {
            ::ZeroMemory(pidlNew, cb1 + cb2);

            //copy the first PIDL
            ::CopyMemory(pidlNew, pidl1, cb1);
            //copy the second PIDL
            ::CopyMemory(((LPBYTE)pidlNew) + cb1, pidl2, cb2);
        }
        return pidlNew;
    }

    LPITEMIDLIST Copy(LPCITEMIDLIST pidlSrc)
    {
        LPITEMIDLIST pidlTarget = NULL;
        UINT Size = 0;

        if (pidlSrc == NULL)
            return NULL;

        // Allocate memory for the new PIDL.
        Size = GetByteSize(pidlSrc);
        pidlTarget = (LPITEMIDLIST)m_spMalloc->Alloc(Size);

        if (pidlTarget == NULL)
            return NULL;

        // Copy the source PIDL to the target PIDL.
        //memset((void*)pidlTarget,0,Size);
        ::ZeroMemory(pidlTarget, Size);

        ::CopyMemory(pidlTarget, pidlSrc, Size);

        return pidlTarget;
    }

    UINT GetByteSize(LPCITEMIDLIST pidl)
    {
        UINT Size = 0;
        LPITEMIDLIST pidlTemp = (LPITEMIDLIST)pidl;

        ATLASSERT(pidl != NULL);
        if (!pidl)
            return 0;

        while (pidlTemp->mkid.cb != 0)
        {
            Size += pidlTemp->mkid.cb;
            pidlTemp = GetNextItem(pidlTemp);
        }

        // add the size of the NULL terminating ITEMIDLIST
        Size += sizeof(ITEMIDLIST);

        return Size;
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

    static HRESULT copy(LPITEMIDLIST* pTo, const RPF::Directory* pDirectory)
    {
        *pTo = s_PIDLManager.Create(pDirectory);
        return (NULL != *pTo) ? S_OK : E_OUTOFMEMORY;
    }

    static void destroy(LPITEMIDLIST* p)
    {
        s_PIDLManager.Delete(*p);
    }
};

typedef CComEnumOnSTL<IEnumIDList, &IID_IEnumIDList, LPITEMIDLIST, CCopyTcharToPidl, std::vector<RPF::Directory>> CEnumIDListImpl;

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
    if (data == NULL || data->m_pDir == NULL)
        return E_POINTER;

    pNewSelf->m_pActiveRPF = m_pActiveRPF;
    pNewSelf->m_pActiveRPFReader = m_pActiveRPFReader;
    pNewSelf->m_pActiveDirectory = (RPF::Directory*)data->m_pDir;
    pNewSelf->m_pWorkingPidl = m_pWorkingPidl;

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
    hr = pEnum->Init(GetUnknown(), m_pActiveDirectory->m_vSubDirectories);

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

        if (data->m_pDir != NULL)
        {
            dwAttr |= SFGAO_FOLDER | SFGAO_COMPRESSED | SFGAO_ENCRYPTED;

            if (!data->m_pDir->m_vSubDirectories.empty())
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
            if (data->m_pDir != NULL)
            {
                hr = SHCreateFileExtractIconW(L"/", FILE_ATTRIBUTE_DIRECTORY, riid, ppvReturn);
            }
            else
            {
                std::wstring name = std::convert(data->m_pFile->m_sName);
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

    auto& name = s_PIDLManager.GetData(pidl)->m_pDir->m_sName;
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

STDMETHODIMP CShellFolderImpl::GetDefaultSearchGUID(GUID* pguid)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::EnumSearches(IEnumExtraSearch** ppenum)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::GetDefaultColumn(DWORD dwRes, ULONG* pSort, ULONG* pDisplay)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::GetDefaultColumnState(UINT iColumn, SHCOLSTATEF* pcsFlags)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::GetDetailsEx(PCUITEMID_CHILD pidl, const SHCOLUMNID* pscid, VARIANT* pv)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::GetDetailsOf(PCUITEMID_CHILD pidl, UINT iColumn, SHELLDETAILS* psd)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

STDMETHODIMP CShellFolderImpl::MapColumnToSCID(UINT iColumn, SHCOLUMNID* pscid)
{
    QUICK_DBG;

    return E_NOTIMPL;
}

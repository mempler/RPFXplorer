#include "pch.h"
#include "CRAGEFolder.h"

HRESULT CreateRPFEnumIDL(IRPF* pRPF, REFIID riid, LPVOID* ppvOut);

//-----------------------------------------------------------
// IContextMenu
//
STDMETHODIMP CRAGEFolder::QueryContextMenu(_In_ HMENU hMenu, _In_ UINT uIndexMenu, _In_ UINT uIDCmdFirst, _In_ UINT uIDCmdLast, _In_ UINT uFlags)
{
	if (!hMenu && hMenu == INVALID_HANDLE_VALUE)
		return E_HANDLE;

	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::InvokeCommand(_In_ CMINVOKECOMMANDINFO* lpInfo)
{
	if (lpInfo == NULL)
		return E_POINTER;

	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetCommandString(_In_ UINT_PTR pIDCmd, _In_ UINT uType, _Reserved_ UINT* pReserved, _In_ CHAR* pszName, _In_ UINT cchMax)
{
	if (pIDCmd == NULL || pszName == NULL)
		return E_POINTER;

	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IShellExtInit
//
STDMETHODIMP CRAGEFolder::Initialize(_In_opt_ PCIDLIST_ABSOLUTE pidlFolder, _In_opt_ IDataObject* pdtobj, _In_opt_ HKEY hkeyProgID)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IShellFolder
//
STDMETHODIMP CRAGEFolder::ParseDisplayName(_In_opt_ HWND hWnd, _In_opt_ LPBC pbc, _In_ LPOLESTR pszDisplayName, _Reserved_ LPDWORD pchEaten, _Out_ LPITEMIDLIST* ppidl, _Inout_ LPDWORD pdwAttributes)
{
	if (pszDisplayName == NULL || ppidl == NULL)
		return E_POINTER;

	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::EnumObjects(_In_opt_ HWND hWnd, _In_ DWORD grfFlags, _Out_opt_ IEnumIDList** ppenumIDList)
{
	return CreateRPFEnumIDL(this, IID_IEnumIDList, (void**)ppenumIDList);
}

STDMETHODIMP CRAGEFolder::BindToObject(_In_ PCUIDLIST_RELATIVE pidl, _In_opt_ LPBC pbc, _In_ REFIID riid, _Out_opt_ void** ppv)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::BindToStorage(_In_ PCUIDLIST_RELATIVE pidl, _In_opt_ LPBC pbc, _In_ REFIID riid, _Out_opt_ void** ppv)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::CompareIDs(_In_ LPARAM lParam, _In_ PCUIDLIST_RELATIVE pidl1, _In_ PCUIDLIST_RELATIVE pidl2)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::CreateViewObject(_In_opt_ HWND hWndOwner, _In_ REFIID riid, _In_opt_ void** ppv)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetAttributesOf(_In_ UINT cidl, _In_ PCUITEMID_CHILD_ARRAY apidl, _Inout_ LPDWORD rgfInOut)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetUIObjectOf(_In_opt_ HWND hWndOwner, _In_ UINT cidl, _In_ PCUITEMID_CHILD_ARRAY apidl, _In_ REFIID riid, _Reserved_ LPUINT rgfReserved, _Out_opt_ void** ppv)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetDisplayNameOf(_In_opt_ PCUITEMID_CHILD pidl, _In_ DWORD uFlags, _Out_ LPSTRRET pName)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::SetNameOf(_In_opt_ HWND hWnd, _In_ PCUITEMID_CHILD pidl, _In_ LPCWSTR pszName, _In_ SHGDNF uFlags, _Out_opt_ PITEMID_CHILD* ppidlOut)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IShellFolder2
//
STDMETHODIMP CRAGEFolder::GetDefaultSearchGUID(_Out_ LPGUID pguid)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::EnumSearches(_Out_opt_ IEnumExtraSearch** ppenum)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetDefaultColumn(_In_ DWORD dwRes, _Out_ ULONG* pSort, _Out_ ULONG* pDisplay)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetDefaultColumnState(_In_ UINT iColumn, _Out_ SHCOLSTATEF* pcsFlags)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetDetailsEx(_In_opt_ PCUITEMID_CHILD pidl, _In_ const SHCOLUMNID* pscid, _Out_ VARIANT* pv)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::GetDetailsOf(_In_opt_ PCUITEMID_CHILD pidl, _In_ UINT iColumn, _In_ SHELLDETAILS* psd)
{
	return E_NOTIMPL;
}

STDMETHODIMP CRAGEFolder::MapColumnToSCID(_In_ UINT, _Out_ SHCOLUMNID*)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IPersist
//
STDMETHODIMP CRAGEFolder::GetClassID(_Out_ CLSID* pClassID)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IPersistFolder
//
STDMETHODIMP CRAGEFolder::Initialize(_In_ PCIDLIST_ABSOLUTE pidl)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IPersistFolder2
//
STDMETHODIMP CRAGEFolder::GetCurFolder(_Out_ PIDLIST_ABSOLUTE* ppidl)
{
	return E_NOTIMPL;
}

//-----------------------------------------------------------
// IRPF
//
STDMETHODIMP CRAGEFolder::GetRPFReader(_Out_ RPFReader** ppReader)
{
	return E_NOTIMPL;
}

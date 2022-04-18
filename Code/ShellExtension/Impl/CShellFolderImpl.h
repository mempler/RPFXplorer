#pragma once

#include "resource.h"       // main symbols

#include "RPFXplorer_h.h"
#include "RPF.h"

#include <vector>

using namespace ATL;

// CShellFolderImpl

class ATL_NO_VTABLE CShellFolderImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShellFolderImpl, &CLSID_ShellFolderImpl>,
	public IPersistFolder2,
	public IShellFolder2
{
public:

DECLARE_REGISTRY_RESOURCEID(IDR_FILE_HANDLER)
DECLARE_NOT_AGGREGATABLE(CShellFolderImpl)


BEGIN_COM_MAP(CShellFolderImpl)
	COM_INTERFACE_ENTRY(IShellFolder)
	COM_INTERFACE_ENTRY(IShellFolder2)
	COM_INTERFACE_ENTRY(IPersistFolder)
	COM_INTERFACE_ENTRY(IPersistFolder2)
	COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// IPersist
	//-------------------------------------------------------------------------------
	STDMETHOD(GetClassID)(CLSID*);

	// IPersistFolder
	//-------------------------------------------------------------------------------
	STDMETHOD(Initialize)(LPCITEMIDLIST);

	// IPersistFolder2
	//-------------------------------------------------------------------------------
	STDMETHOD(GetCurFolder)(PIDLIST_ABSOLUTE*);

	// IShellFolder
	//-------------------------------------------------------------------------------
	STDMETHOD(BindToObject) (LPCITEMIDLIST, LPBC, REFIID, void**);
	STDMETHOD(CompareIDs) (LPARAM, LPCITEMIDLIST, LPCITEMIDLIST);
	STDMETHOD(CreateViewObject) (HWND, REFIID, void**);
	STDMETHOD(EnumObjects) (HWND, DWORD, LPENUMIDLIST*);
	STDMETHOD(GetAttributesOf) (UINT, LPCITEMIDLIST*, LPDWORD);
	STDMETHOD(GetUIObjectOf) (HWND, UINT, LPCITEMIDLIST*, REFIID, LPUINT, void**);
	STDMETHOD(BindToStorage) (LPCITEMIDLIST, LPBC, REFIID, void**);
	STDMETHOD(GetDisplayNameOf) (LPCITEMIDLIST, DWORD, LPSTRRET);
	STDMETHOD(ParseDisplayName) (HWND, LPBC, LPOLESTR, LPDWORD, LPITEMIDLIST*, LPDWORD);
	STDMETHOD(SetNameOf) (HWND, LPCITEMIDLIST, LPCOLESTR, DWORD, LPITEMIDLIST*);

	// IShellFolder2
	//-------------------------------------------------------------------------------
	STDMETHOD(GetDefaultSearchGUID) (GUID*);
	STDMETHOD(EnumSearches) (IEnumExtraSearch**);
	STDMETHOD(GetDefaultColumn) (DWORD, ULONG*, ULONG*);
	STDMETHOD(GetDefaultColumnState) (UINT, SHCOLSTATEF*);
	STDMETHOD(GetDetailsEx) (PCUITEMID_CHILD, const SHCOLUMNID*, VARIANT*);
	STDMETHOD(GetDetailsOf) (PCUITEMID_CHILD, UINT, SHELLDETAILS*);
	STDMETHOD(MapColumnToSCID) (UINT, SHCOLUMNID*);

private:
	RPFReader* m_pActiveRPFReader;
	RPF* m_pActiveRPF;

	RPF::Directory* m_pActiveDirectory = NULL;
	LPCITEMIDLIST m_pWorkingPidl;
};

OBJECT_ENTRY_AUTO(__uuidof(ShellFolderImpl), CShellFolderImpl)

#pragma once

#include "resource.h"       // main symbols

#include "RPFXplorer_h.h"
#include "RPFReader.h"

#include <vector>

using namespace ATL;

// CShellFolderImpl

class ATL_NO_VTABLE CShellFolderImpl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShellFolderImpl, &CLSID_ShellFolderImpl>,
	public IPersistFolder,
	public IShellFolder
{
public:

DECLARE_REGISTRY_RESOURCEID(IDR_FILE_HANDLER)
DECLARE_NOT_AGGREGATABLE(CShellFolderImpl)


BEGIN_COM_MAP(CShellFolderImpl)
	COM_INTERFACE_ENTRY(IShellFolder)
	COM_INTERFACE_ENTRY(IPersistFolder)
	COM_INTERFACE_ENTRY(IPersist)
END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	// IPersist
	//-------------------------------------------------------------------------------
	STDMETHOD(GetClassID)(CLSID*);

	// IPersistFolder
	//-------------------------------------------------------------------------------
	STDMETHOD(Initialize)(LPCITEMIDLIST);

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

private:
	RPFReader* m_pActiveRPF = NULL;
};

OBJECT_ENTRY_AUTO(__uuidof(ShellFolderImpl), CShellFolderImpl)

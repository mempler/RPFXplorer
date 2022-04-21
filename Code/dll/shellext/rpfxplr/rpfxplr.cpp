#include "pch.h"

#include <initguid.h>

#include "CRAGEFolder.h"

HMODULE g_hModule = NULL;
LONG g_ModuleRefCnt = 0;

class CRPFXplrModule : public CComModule
{
public:
};

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_RPFXplorerStorageHandler,	CRAGEFolder)
	OBJECT_ENTRY(CLSID_RPFXplorerContextMenu,		CRAGEFolder)
END_OBJECT_MAP()

CRPFXplrModule gModule;

EXTERN_C
BOOL WINAPI
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hInstance);
		g_hModule = hInstance;
		gModule.Init(ObjectMap, hInstance, NULL);
		break;
	}

	return TRUE;
}

STDAPI
DllCanUnloadNow(void)
{
	if (g_ModuleRefCnt)
		return S_FALSE;

	return gModule.DllCanUnloadNow();
}

STDAPI
DllGetClassObject(
	IN REFCLSID rclsid,
	IN REFIID riid,
	OUT LPVOID* ppv)
{
	return gModule.DllGetClassObject(rclsid, riid, ppv);
}

STDAPI DllRegisterServer()
{
	HRESULT hr;

	hr = gModule.DllRegisterServer(FALSE);
	if (FAILED(hr))
		return hr;

	hr = gModule.UpdateRegistryFromResource(IDR_REGISTRY, TRUE, NULL);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

STDAPI DllUnregisterServer()
{
	HRESULT hr;

	hr = gModule.DllUnregisterServer(FALSE);
	if (FAILED(hr))
		return hr;

	hr = gModule.UpdateRegistryFromResource(IDR_REGISTRY, FALSE, NULL);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

//
// Workaround for this stupid registry script
//
EXTERN_C
BOOL WINAPI
ForwardToShell(
	IN HWND hWndOwner,
	IN HINSTANCE hInstance,
	IN LPCSTR lpTargetFile,
	IN INT nShowCmd)
{
	ATL::CStringW path(lpTargetFile);

	// Windows being weird :/
	PathRemoveBlanks(path.GetBuffer());
	path.ReleaseBuffer();

	ShellExecute(NULL, L"open", L"explorer.exe", path.GetString(), NULL, SW_SHOWNORMAL);

	return TRUE;
}

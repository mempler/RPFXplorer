// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "RPFXplorer_h.h"
#include "dllmain.h"

CRPFXplorerModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}

HRESULT CRPFXplorerModule::AddCommonRGSReplacements(IRegistrarBase* pRegistrar) throw()
{
	HRESULT hr = __super::AddCommonRGSReplacements(pRegistrar);

	wchar_t systemRoot[MAX_PATH]{};
	GetEnvironmentVariable(L"SystemRoot", systemRoot, MAX_PATH);

	std::wstring explorer = std::wstring(systemRoot) + L"\\Explorer.exe /idlist,%I,%L";
	pRegistrar->AddReplacement(L"EXPLORER", explorer.c_str());

	return hr;
}

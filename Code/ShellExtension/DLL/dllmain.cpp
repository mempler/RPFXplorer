// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "RPFXplorer_h.h"
#include "dllmain.h"

#include <client/windows/handler/exception_handler.h>
#include <client/windows/crash_generation/client_info.h>
#include <client/windows/crash_generation/crash_generation_client.h>
#include <client/windows/crash_generation/crash_generation_server.h>
#include <common/windows/http_upload.h>

CRPFXplorerModule _AtlModule;

static google_breakpad::ExceptionHandler* g_pExceptionHandler;


bool CrashCallback(
	const wchar_t* /*dump_path*/, const wchar_t* /*minidump_id*/,
	void* /*context*/, EXCEPTION_POINTERS* /*exinfo*/, MDRawAssertionInfo* /*assertion*/,
	bool succeeded)
{
	MessageBox(NULL, L"CRASH!!!", L"OOPS", MB_OK);

	return succeeded;
}

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;

	if (g_pExceptionHandler == NULL)
	{
		wchar_t path[MAX_PATH];
		GetModuleFileName(hInstance, path, MAX_PATH);
		*wcsrchr(path, L'\\') = 0;

		std::wstring crashPath = path;
		crashPath += L"\\Dumps";

		CreateDirectory(crashPath.c_str(), NULL);

		g_pExceptionHandler = new google_breakpad::ExceptionHandler(crashPath, NULL, CrashCallback, NULL, google_breakpad::ExceptionHandler::HANDLER_ALL);
	}

	return _AtlModule.DllMain(dwReason, lpReserved);
}

CRPFXplorerModule::CRPFXplorerModule()
{
}

CRPFXplorerModule::~CRPFXplorerModule()
{
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

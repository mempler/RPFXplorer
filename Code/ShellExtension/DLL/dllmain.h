// dllmain.h : Declaration of module class.

#include <atlbase.h>

class CRPFXplorerModule : public ATL::CAtlDllModuleT< CRPFXplorerModule >
{
public :
	DECLARE_LIBID(LIBID_RPFXplorerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_RPFXPLORER, "{0dfd9ea1-e255-4fb0-b40b-98a0a77dc9c8}")

	HRESULT AddCommonRGSReplacements(_Inout_ IRegistrarBase* pRegistrar) throw() override;
};

extern class CRPFXplorerModule _AtlModule;

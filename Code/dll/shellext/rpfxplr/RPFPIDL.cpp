#include "pch.h"
#include "RPFPIDL.h"

LPITEMIDLIST _CreateRPFPIDL(_In_ const RPFEntry& rpfEntry, const RPFReader* prpfReader)
{
    auto name = prpfReader->GetNameW(&rpfEntry);
    int size = sizeof(RPFPidlData) + name.size();

    RPFPidlData* pidl = (RPFPidlData*)SHAlloc(size);
    if (!pidl)
        return NULL;

    ZeroMemory(pidl, size);

    pidl->rpfEntry = rpfEntry;
    pidl->uMagicValue = RPF_PIDL_MAGIC;

    StrCpy(pidl->szName, name.c_str());

    return (LPITEMIDLIST)pidl;
}

const RPFPidlData* _PidlToRPFEntry(_In_ LPCITEMIDLIST pidl)
{
    RPFPidlData* data = (RPFPidlData*)pidl;

    return data->uMagicValue == RPF_PIDL_MAGIC ? data : NULL;
}

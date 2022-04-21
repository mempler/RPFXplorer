#include "pch.h"
#include "RPFPIDL.h"

LPITEMIDLIST _CreateRPFPIDL(_In_ const RPFEntry& rpfEntry, const RPFReader* prpfReader)
{
    auto name = prpfReader->GetName(&rpfEntry);
    int size = sizeof(RPFPidlData) + name.GetLength();

    RPFPidlData* pidl = (RPFPidlData*)SHAlloc(size);
    if (!pidl)
        return NULL;

    ZeroMemory(pidl, size);

    pidl->rpfEntry = rpfEntry;
    pidl->uMagicValue = RPF_PIDL_MAGIC;

    StrCpy(pidl->szName, name.GetString());

    return (LPITEMIDLIST)pidl;
}

const RPFPidlData* _PidlToRPFEntry(_In_ LPCITEMIDLIST pidl)
{
    RPFPidlData* data = (RPFPidlData*)pidl;

    return data->uMagicValue == RPF_PIDL_MAGIC ? data : NULL;
}

#pragma once
#pragma once

#include "RPFReader.h"
#include "RPFStructure.h"

#include <shtypes.h>

#define RPF_PIDL_MAGIC 0xFF020FF

struct RPFPidlData
{
	//
	// SHITEMID
	//
	USHORT cb;

	//
	//
	//
	UINT uMagicValue; // To make sure we're not some other pidl

	RPFEntry rpfEntry;
	WCHAR szName[1];
};

LPITEMIDLIST _CreateRPFPIDL(_In_ const RPFEntry& rpfEntry, RPFReader* prpfReader);
const RPFPidlData* _PidlToRPFEntry(_In_ LPCITEMIDLIST pidl);

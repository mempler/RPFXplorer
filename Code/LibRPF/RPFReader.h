#pragma once

#include "RPFStructure.h"

#include <vector>
#include <string>

//
// low level utility for reading from an RPF archive
//
class RPFReader
{
public:
	RPFHeader Header;
	std::vector<RPFEntry> Entries;
	std::vector<BYTE> NameTable;

	//
	// NOTE: RPFReader must be closed once hFile gets invalid!
	//
	HRESULT			Open(HANDLE hFile);

	//
	// This'll only close the RPFReader, it will no langer access the underlying File
	// however it wont free it's memory stored within RPFReader until RPFReader has been deconstructed
	//
	void			Close();

	const char*		GetNameRAW(RPFEntry*);
	std::string		GetNameA(RPFEntry*);
	std::wstring	GetNameW(RPFEntry*);

	RPFEntry*		GetEntryByNameA(const std::string&);
	RPFEntry*		GetEntryByNameW(const std::wstring&);

	std::vector<BYTE> GetContent(RPFEntry*);

	DWORD GetSizeFromEntry(RPFEntry*);

private:
	DWORD m_nOffset;
	HANDLE m_hFile = NULL;

	HANDLE m_hFileMap;
	BYTE* m_szMappedFile = NULL;

	std::vector<BYTE> m_vTemporaryData;

	HRESULT ReadHeader();
	HRESULT ReadEntry(DWORD dwIndex);
	HRESULT ReadNameTable();
};

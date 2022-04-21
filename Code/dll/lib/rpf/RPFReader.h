#pragma once

#include "RPFStructure.h"
#include "RPF.h"

//
// low level utility for reading from an RPF archive
//
class RPFReader
{
public:
	//
	// NOTE: RPFReader must be closed once hFile gets invalid!
	//
	RPF_API HRESULT					Open(HANDLE hFile);

	//
	// This'll only close the RPFReader, it will no langer access the underlying File
	// however it wont free it's memory stored within RPFReader until RPFReader has been deconstructed
	//
	RPF_API void					Close();

	RPF_API const char*				GetNameRAW(const RPFEntry*) const;
	RPF_API ATL::CString			GetName(const RPFEntry*) const;

	//
	// Please note that following might cause issues if E.G there are 2 entries with the same name
	// in different directories.
	//
	RPF_API RPFEntry*				GetEntryByName(const ATL::CString&);

	RPF_API std::vector<BYTE>		GetContent(const RPFEntry*);

	RPF_API DWORD					GetSizeFromEntry(const RPFEntry*);

	RPF_API inline RPFEntry&		GetRootEntry() { return m_vEntries.at(0); }
	RPF_API std::vector<RPFEntry>	GetSubEntries(const RPFEntry*);

private:
	RPFHeader				m_Header;
	std::vector<RPFEntry>	m_vEntries;
	std::vector<BYTE>		m_vNameTable;

	DWORD					m_nOffset = 0;
	HANDLE					m_hFile = NULL;
	HANDLE					m_hFileMap = NULL;
	BYTE*					m_szMappedFile = NULL;

	std::vector<BYTE>		m_vTemporaryData;

	HRESULT					ReadHeader();
	HRESULT					ReadEntry(DWORD dwIndex);
	HRESULT					ReadNameTable();
};

#include "RPFReader.h"

#include "Utility/String.h"

#include <iostream>
#include <cstring>

HRESULT RPFReader::Open(HANDLE hFile)
{
	if (hFile == INVALID_HANDLE_VALUE)
		return E_INVALIDARG;

	m_hFile = hFile;

	ReadHeader();
	Entries.resize(Header.dwEntryCount);

	// We now know the exact size of every and each component, we'll simply read the whole header into memory
	// with one big swoop which'll speed up the reading process as we no longer rely on the FileSystem

	m_vTemporaryData.resize(static_cast<SIZE_T>(Header.dwEntryCount) * 16 + Header.dwNameLength);
	if (!ReadFile(m_hFile, m_vTemporaryData.data(), (DWORD) m_vTemporaryData.size(), &m_nOffset, NULL))
		return E_UNEXPECTED;

	DWORD offset = m_nOffset;	// Temporarily store the offset
	m_nOffset = 0;				// Reset to 0 for the other read operations

	// Parse the remaining values
	for (DWORD i = 0; i < Header.dwEntryCount; i++)
	{
		ReadEntry(i);
	}

	ReadNameTable();

	// Now we can simply clear the whole mess we made as we no longer need it
	m_vTemporaryData.clear();
	m_vTemporaryData.shrink_to_fit();

	m_nOffset = offset; // Restore the offset

	// Now lets map the file into our memory so we can easily access it.
	m_hFileMap = CreateFileMapping(m_hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (m_hFileMap == INVALID_HANDLE_VALUE || m_hFileMap == NULL)
	{
		Close();
		return E_FAIL;
	}

	m_szMappedFile = (BYTE*) MapViewOfFile(m_hFileMap, FILE_MAP_READ, 0, 0, 0);
	if (m_szMappedFile == NULL)
	{
		Close();
		return E_FAIL;
	}

	return S_OK;
}

void RPFReader::Close()
{
	UnmapViewOfFile(m_szMappedFile);
	CloseHandle(m_hFileMap);
}

//-----------------------------------------------------

const char* RPFReader::GetNameRAW(RPFEntry* pEntry)
{
	DWORD offset = 0;

	switch (pEntry->dwType)
	{
	case RPF_ENTRY_TYPE_RESOURCE:
		offset = pEntry->ResourceFile.wNameOffset;
		break;

	case RPF_ENTRY_TYPE_BINARY:
		offset = pEntry->BinaryFile.wNameOffset;
		break;

	case RPF_ENTRY_TYPE_DIRECTORY:
		offset = pEntry->Directory.dwNameOffset;
		break;
	}

	return (const char*) &NameTable.at(offset);
}

std::string RPFReader::GetNameA(RPFEntry* pEntry)
{
	return GetNameRAW(pEntry);
}

std::wstring RPFReader::GetNameW(RPFEntry* pEntry)
{
	return std::convert(GetNameA(pEntry));
}

//-----------------------------------------------------

RPFEntry* RPFReader::GetEntryByNameA(const std::string& sName)
{
	// Yup, this will be slow :/
	for (auto& entry : Entries)
		if (_stricmp(GetNameRAW(&entry), sName.c_str()) == 0)
			return &entry;

	return nullptr;
}

RPFEntry* RPFReader::GetEntryByNameW(const std::wstring& sName)
{
	return GetEntryByNameA(std::convert(sName));
}

//-----------------------------------------------------

std::vector<BYTE> RPFReader::GetContent(RPFEntry* pEntry)
{
	BYTE* begin = m_szMappedFile + (pEntry->ResourceFile.hwFileOffset * 512);
	BYTE* end = begin + GetSizeFromEntry(pEntry);
	
	return std::vector<BYTE>{ begin, end };
}

DWORD RPFReader::GetSizeFromEntry(RPFEntry* pEntry)
{
	if (pEntry == NULL || pEntry->dwType == RPF_ENTRY_TYPE_DIRECTORY)
		return 0;

	// TODO: figure this out...

	return pEntry->ResourceFile.dwSystemFlags;
}

//-----------------------------------------------------

std::vector<RPFEntry*> RPFReader::GetSubEntries(RPFEntry* pEntry)
{
	if (pEntry->dwType != RPF_ENTRY_TYPE_DIRECTORY)
		return { };

	auto* begin	= &Entries.at(pEntry->Directory.dwEntriesIndex);
	auto* end	= begin + pEntry->Directory.dwEntriesCount;

	return { begin, end };
}

//-----------------------------------------------------

HRESULT RPFReader::ReadHeader()
{
	if (!ReadFile(m_hFile, &Header, sizeof(RPFHeader), &m_nOffset, NULL))
		return E_UNEXPECTED;

	return S_OK;
}

HRESULT RPFReader::ReadEntry(DWORD dwIndex)
{
	union {
		struct
		{
			BYTE buf1[4];
			BYTE buf2[4];
			BYTE buf3[4];
			BYTE buf4[4];
		};

		struct
		{
			DWORD val1;
			DWORD val2;
			DWORD val3;
			DWORD val4;
		};
	} data{};

	CopyMemory(&data, &m_vTemporaryData.at(m_nOffset), 16); m_nOffset += 16;

	RPFEntry& entry = Entries.at(dwIndex);

	// Figure out who we're
	if (data.val2 == 0x7fffff00)
	{
		entry.dwType							= RPF_ENTRY_TYPE_DIRECTORY;
		entry.Directory.dwNameOffset			= data.val1;
		entry.Directory.dwIdentifier			= data.val2;
		entry.Directory.dwEntriesIndex			= data.val3;
		entry.Directory.dwEntriesCount			= data.val4;
	}
	else if (data.val2 & 0x80000000)
	{
		entry.dwType							= RPF_ENTRY_TYPE_BINARY;
		entry.BinaryFile.wNameOffset			= data.buf1[0] | data.buf1[1] << 8;
		entry.BinaryFile.hwFileSize				= data.buf1[2] | data.buf1[3] << 8 | data.buf2[0] << 16;
		entry.BinaryFile.hwFileOffset			= data.buf2[1] | data.buf2[2] << 8 | data.buf2[3] << 16;
		entry.BinaryFile.dwFileUncompressedSize	= data.val3;
		entry.BinaryFile.bIsEncrypted			= data.val4;
	}
	else
	{
		entry.dwType							= RPF_ENTRY_TYPE_RESOURCE;
		entry.ResourceFile.wNameOffset			= data.buf1[0] | data.buf1[1] << 8;
		entry.ResourceFile.hwFileSize			= data.buf1[2] | data.buf1[3] << 8 | data.buf2[0] << 16;
		entry.ResourceFile.hwFileOffset			= data.buf2[1] | data.buf2[2] << 8 | data.buf2[3] << 16;
		entry.ResourceFile.dwSystemFlags		= data.val3;
		entry.ResourceFile.dwGraphicsFlags		= data.val4;
	}

	return S_OK;
}

HRESULT RPFReader::ReadNameTable()
{
	NameTable.resize(Header.dwNameLength);
	CopyMemory(NameTable.data(), &m_vTemporaryData.at(m_nOffset), (DWORD)NameTable.size()); m_nOffset += (DWORD)NameTable.size();
	return S_OK;
}

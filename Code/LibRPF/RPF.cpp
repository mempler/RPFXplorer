#include "RPF.h"

#include <Windows.h>

#include <iostream>
#include <string>
#include <cassert>

RPFReader::~RPFReader()
{
	CloseHandle(m_hFile);
}

void RPFReader::Open(HANDLE hFile)
{
	m_hFile = hFile;

	ReadHeader();
	Entries.resize(Header.dwEntryCount);

	for (DWORD i = 0; i < Header.dwEntryCount; i++)
	{
		ReadEntry(i);
	}

	ReadNameTable();
}

void RPFReader::DumpToLog()
{
	std::cout << "RPF->" << std::endl;

	// Dump Header
	std::wstring version = L"V" + std::to_wstring(Header.dwVersion - RPF_VERSION_V0);
	std::wstring encryption = L"UNKNOWN";
	switch (Header.dwEncryption)
	{
	case RPF_ENCRYPTION_NONE:
		encryption = L"NONE";
		break;

	case RPF_ENCRYPTION_OPEN:
		encryption = L"OPEN";
		break;

	case RPF_ENCRYPTION_AES:
		encryption = L"AES";
		break;

	case RPF_ENCRYPTION_NG:
		encryption = L"NG";
		break;
	}

	std::cout << "  Header ->" << std::endl;
	std::wcout << "    Version: " << version << std::endl;
	std::wcout << "    EntryCount: 0x" << std::hex << Header.dwEntryCount << std::endl;
	std::wcout << "    NameLength: 0x" << std::hex << Header.dwNameLength << std::endl;
	std::wcout << "    Encryption: " << std::hex << encryption << std::endl;

	// Dump Entries
	std::cout << "  Entries(" << Header.dwEntryCount << ") ->" << std::endl;

	for (auto& entry : Entries)
	{
		switch (entry.dwType)
		{
		case RPF_ENTRY_TYPE_DIRECTORY:
			std::wcout << "    Entry (RPF_ENTRY_TYPE_DIRECTORY) -> " << std::endl;
			std::wcout << "      NameOffset: 0x" << std::hex << entry.Directory.dwNameOffset << std::endl;
			std::wcout << "      Identifier: 0x" << std::hex << entry.Directory.dwIdentifier << std::endl;
			std::wcout << "      EntriesIndex: 0x" << std::hex << entry.Directory.dwEntriesIndex << std::endl;
			std::wcout << "      EntriesCount: 0x" << std::hex << entry.Directory.dwEntriesCount << std::endl;
			break;

		case RPF_ENTRY_TYPE_BINARY:
			std::wcout << "    Entry (RPF_ENTRY_TYPE_BINARY) -> " << std::endl;
			std::wcout << "      NameOffset: 0x" << std::hex << entry.BinaryFile.wNameOffset << std::endl;
			std::wcout << "      Size: 0x" << std::hex << entry.BinaryFile.hwFileSize << std::endl;
			std::wcout << "      Offset: 0x" << std::hex << entry.BinaryFile.hwFileOffset << std::endl;
			std::wcout << "      UncompressedSize: 0x" << std::hex << entry.BinaryFile.dwFileUncompressedSize << std::endl;
			std::wcout << "      IsEncrypted: " << (entry.BinaryFile.bIsEncrypted ? "True" : "False") << std::endl;
			break;

		case RPF_ENTRY_TYPE_RESOURCE:
			std::wcout << "    Entry (RPF_ENTRY_TYPE_RESOURCE) -> " << std::endl;
			std::wcout << "      NameOffset: 0x" << std::hex << entry.ResourceFile.wNameOffset << std::endl;
			std::wcout << "      Size: 0x" << std::hex << entry.ResourceFile.hwFileSize << std::endl;
			std::wcout << "      Offset: 0x" << std::hex << entry.ResourceFile.hwFileOffset << std::endl;
			std::wcout << "      SystemFlags: 0x" << std::hex << entry.ResourceFile.dwSystemFlags << std::endl;
			std::wcout << "      GraphicsFlags: 0x" << std::hex << entry.ResourceFile.dwGraphicsFlags << std::endl;
			break;
		}
	}
}

void RPFReader::ReadHeader()
{
	assert(ReadFile(m_hFile, &Header, sizeof(RPFHeader), NULL, &m_OL));
	m_OL.Offset += sizeof(RPFHeader);
}

void RPFReader::ReadEntry(DWORD dwIndex)
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

	assert(ReadFile(m_hFile, &data, 16, NULL, &m_OL)); m_OL.Offset += 16;

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
		entry.BinaryFile.dwFileUncompressedSize = data.val3;
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
}

void RPFReader::ReadNameTable()
{
	NameTable.resize(Header.dwNameLength);
	assert(ReadFile(m_hFile, NameTable.data(), (DWORD)NameTable.size(), NULL, &m_OL)); m_OL.Offset += (DWORD)NameTable.size();
}

//-----------------------------------------------

void RPF::DumpTreeToLog(Directory* pDirectory, size_t iPad)
{
	if (pDirectory == nullptr)
		pDirectory = &m_RootDirectory;

	for (size_t i = 0; i < iPad; i++)
	{
		std::cout << " ";
	}

	std::cout << pDirectory->m_sName << "/" << std::endl;
	for (auto& dir : pDirectory->m_vSubDirectories)
	{
		DumpTreeToLog(&dir, iPad + 2);
	}

	iPad += 2;

	for (auto& file : pDirectory->m_vFiles)
	{
		for (size_t i = 0; i < iPad; i++)
		{
			std::cout << " ";
		}

		std::cout << file.m_sName << std::endl;
	}
}

void RPF::ReadDirRecursive(RPF::Directory& outDir, RPFEntry* pEntry)
{
	outDir.m_sName = (const char*)&m_pReader->NameTable[pEntry->Directory.dwNameOffset];

	for (size_t i = 0; i < pEntry->Directory.dwEntriesCount; i++)
	{
		RPFEntry* nextEntry = &m_pReader->Entries[pEntry->Directory.dwEntriesIndex + i];

		if (nextEntry->dwType == RPF_ENTRY_TYPE_DIRECTORY)
		{
			RPF::Directory& dir = outDir.m_vSubDirectories.emplace_back();
			dir.m_sName = (const char*)&m_pReader->NameTable[nextEntry->Directory.dwNameOffset];
			dir.m_pParent = &outDir;
			dir.m_sPath = outDir.m_sPath + "/" + dir.m_sName;
			m_umHierarchy.insert({ dir.m_sPath, (Entry<0>*) &dir});

			ReadDirRecursive(dir, nextEntry);
		}
		else
		{
			RPF::File& file = outDir.m_vFiles.emplace_back();
			file.m_sName = (const char*)&m_pReader->NameTable[nextEntry->ResourceFile.wNameOffset];
			file.m_pParent = &outDir;
			file.m_sPath = outDir.m_sPath + "/" + file.m_sName;

			m_umHierarchy.insert({ file.m_sPath, (Entry<0>*) &file});
		}
	}
}

RPF::RPF(RPFReader* pReader)
{
	m_pReader = pReader;
	if (pReader == nullptr)
		return;

	// Build Hierarchy
	if (m_pReader->Header.dwEncryption != RPF_ENCRYPTION_OPEN)
		return; // we only support `RPF_ENCRYPTION_OPEN` for now!

	RPFEntry* rootDir = &m_pReader->Entries[0];
	ReadDirRecursive(m_RootDirectory, rootDir);
}

RPF::Directory* RPF::OpenDir(const std::string& path)
{
	if (path == "/" || path.empty())
		return &m_RootDirectory;

	if (m_umHierarchy.contains(path))
	{
		auto* entry = m_umHierarchy.at(path);
		if (entry->Type != RPF_ENTRY_TYPE_DIRECTORY)
			return nullptr;

		return (RPF::Directory*)entry;
	}

	return nullptr;
}

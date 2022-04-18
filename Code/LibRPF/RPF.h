#pragma once

#include <wtypes.h>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

// Very useful resources:
// https://gtamods.com/wiki/RPF_archive
// https://github.com/dexyfex/CodeWalker
// NOTE: We only support V7 at the moment.

#define RPF_VERSION_V0 0x52504630
#define RPF_VERSION_V2 0x52504632
#define RPF_VERSION_V3 0x52504633
#define RPF_VERSION_V4 0x52504634
#define RPF_VERSION_V6 0x52504636
#define RPF_VERSION_V7 0x52504637
#define RPF_VERSION_V8 0x52504638

#define RPF_ENTRY_TYPE_UNKNOWN    0
#define RPF_ENTRY_TYPE_RESOURCE   1
#define RPF_ENTRY_TYPE_BINARY     2
#define RPF_ENTRY_TYPE_DIRECTORY  3

#define RPF_ENCRYPTION_NONE 0
#define RPF_ENCRYPTION_OPEN 0x4E45504F
#define RPF_ENCRYPTION_AES  0x0FFFFFF9
#define RPF_ENCRYPTION_NG   0x0FEFFFFF

/*
Header:
	Version:    4
	EntryCount: 4
	NameLength: 4
	Encryption: 4

ResourceEntry:
	NameOffset: 2
	FileSize: 3
	FileOffset: 3
	SystemFlags: 4
	GraphicsFLags: 4

BinaryFileEntry:
	NameOffset: 2
	FileSize: 3
	FileOffset: 3
	FileUncompressedSize: 4
	EncryptionType: 4

DirectoryEntry:
	NameOffset:   4
	Identifier:   4 # 0x7FFFFF00
	EntriesIndex: 4
	EntriesCount: 4

NameTable:
	\0 terminated strings
*/

struct RPFHeader
{
	DWORD dwVersion;
	DWORD dwEntryCount;
	DWORD dwNameLength;
	DWORD dwEncryption;
};

struct RPFEntry
{
	DWORD dwType;

	union
	{
		struct
		{
			WORD  wNameOffset;
			DWORD hwFileSize : 24;
			DWORD hwFileOffset : 24;
			DWORD dwSystemFlags;
			DWORD dwGraphicsFlags;
		} ResourceFile;

		struct
		{
			WORD wNameOffset;
			DWORD hwFileSize : 24;
			DWORD hwFileOffset : 24;
			DWORD dwFileUncompressedSize;
			BOOL bIsEncrypted;
		} BinaryFile;

		struct
		{
			DWORD dwNameOffset;
			DWORD dwIdentifier;
			DWORD dwEntriesIndex;
			DWORD dwEntriesCount;
		} Directory;
	};
};

//-----------------------------------------------

class RPFReader
{
public:
	~RPFReader();

	RPFHeader Header;
	std::vector<RPFEntry> Entries;
	std::vector<uint8_t> NameTable;

	void Open(HANDLE hFile);

	void DumpToLog();

private:
	OVERLAPPED m_OL{};
	HANDLE m_hFile = NULL;

	void ReadHeader();
	void ReadEntry(DWORD dwIndex);
	void ReadNameTable();
};

//-----------------------------------------------

class RPF
{
public:
	class Directory;

	template <size_t S>
	struct Entry
	{
		const size_t Type = S;

		RPF* m_pOwner = NULL;
		std::string m_sName;
		RPF::Directory* m_pParent = NULL;
		std::string m_sPath;
	};

	class File : public Entry<RPF_ENTRY_TYPE_RESOURCE>
	{
	};

	class Directory : public Entry<RPF_ENTRY_TYPE_DIRECTORY>
	{
	public:
		std::vector<RPF::Directory> m_vSubDirectories;
		std::vector<RPF::File> m_vFiles;
	};

	RPF(RPFReader* pReader = nullptr);

	RPF::Directory* OpenDir(const std::string& path);

	void DumpTreeToLog(Directory* pDirectory = nullptr, size_t iPad = 0);

private:
	RPFReader* m_pReader;

	void ReadDirRecursive(RPF::Directory& outDir, RPFEntry* pEntry);

	Directory m_RootDirectory;
	std::unordered_map<std::string, RPF::Entry<RPF_ENTRY_TYPE_UNKNOWN>*> m_umHierarchy;
};
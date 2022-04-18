#pragma once

#include <wtypes.h>
#include <string>
#include <vector>
#include <optional>
#include <unordered_map>

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
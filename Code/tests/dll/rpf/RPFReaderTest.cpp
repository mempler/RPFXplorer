#include "pch.h"

#include <RPFReader.h>

class RPFReaderTest : public ::testing::Test
{
protected:
	HANDLE		hFile = NULL;
	RPFReader	reader{};

	void SetUp() override
	{
		hFile = CreateFile(L"./Resources/SimpleOPEN.rpf", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		ASSERT_HRESULT_SUCCEEDED(reader.Open(hFile));
	}

	void TearDown() override
	{
		// cleanup
		reader.Close();
		CloseHandle(hFile);
	}
};

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetEntryByName)
{
	RPFEntry* entry = reader.GetEntryByName("some_file.txt");
	ASSERT_NE(nullptr, entry);
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetNameRAW)
{
	RPFEntry* entry = reader.GetEntryByName("some_file.txt");
	ASSERT_NE(nullptr, entry);

	const char* name = reader.GetNameRAW(entry);
	ASSERT_STREQ(name, "some_file.txt");
}

TEST_F(RPFReaderTest, GetName)
{
	RPFEntry* entry = reader.GetEntryByName("some_file.txt");
	ASSERT_NE(nullptr, entry);

	ATL::CString name = reader.GetName(entry);
	ASSERT_STREQ(name.GetString(), L"some_file.txt");
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetContent)
{
	RPFEntry* entry = reader.GetEntryByName("owo.txt");
	ASSERT_NE(nullptr, entry);

	auto data = reader.GetContent(entry);

	ASSERT_THAT(data, ::testing::ElementsAre('o', 'w', 'o'));
}

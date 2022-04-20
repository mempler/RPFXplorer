#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <gmock/gmock-matchers.h>

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

TEST_F(RPFReaderTest, GetEntryByNameA)
{
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);
}

TEST_F(RPFReaderTest, GetEntryByNameW)
{
	RPFEntry* entry = reader.GetEntryByNameW(L"some_file.txt");
	ASSERT_NE(nullptr, entry);
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetNameRAW)
{
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	const char* name = reader.GetNameRAW(entry);
	ASSERT_STREQ(name, "some_file.txt");
}

TEST_F(RPFReaderTest, GetNameA)
{
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	std::string name = reader.GetNameA(entry);
	ASSERT_STREQ(name.c_str(), "some_file.txt");
}

TEST_F(RPFReaderTest, GetNameW)
{
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	std::wstring name = reader.GetNameW(entry);
	ASSERT_STREQ(name.c_str(), L"some_file.txt");
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetContent)
{
	RPFEntry* entry = reader.GetEntryByNameA("owo.txt");
	ASSERT_NE(nullptr, entry);

	auto data = reader.GetContent(entry);

	ASSERT_THAT(data, ::testing::ElementsAre('o', 'w', 'o'));
}

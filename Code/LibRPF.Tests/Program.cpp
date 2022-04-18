#include <gtest/gtest.h>

#include <RPFReader.h>

class RPFReaderTest : public ::testing::Test
{
protected:
	HANDLE hFile;
	RPFReader reader;

	void SetUp() override
	{
		hFile = CreateFile(L"./Resources/SimpleOPEN.rpf", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	void TearDown() override
	{
		// cleanup
		reader.Close();
		CloseHandle(hFile);
	}
};

TEST_F(RPFReaderTest, OpenSimpleRPF)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetEntryByNameA)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);
}

TEST_F(RPFReaderTest, GetEntryByNameW)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameW(L"some_file.txt");
	ASSERT_NE(nullptr, entry);
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetNameRAW)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	const char* name = reader.GetNameRAW(entry);
	ASSERT_STREQ(name, "some_file.txt");
}

TEST_F(RPFReaderTest, GetNameA)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	std::string name = reader.GetNameA(entry);
	ASSERT_STREQ(name.c_str(), "some_file.txt");
}

TEST_F(RPFReaderTest, GetNameW)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	std::wstring name = reader.GetNameW(entry);
	ASSERT_STREQ(name.c_str(), L"some_file.txt");
}

//-----------------------------------------------------------------

TEST_F(RPFReaderTest, GetContent)
{
	ASSERT_TRUE(SUCCEEDED(reader.Open(hFile)));
	RPFEntry* entry = reader.GetEntryByNameA("some_file.txt");
	ASSERT_NE(nullptr, entry);

	auto data = reader.GetContent(entry);

	ASSERT_EQ(TRUE, FALSE);
	//ASSERT_EQ(, { 0 });
}

//-----------------------------------------------------------------

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

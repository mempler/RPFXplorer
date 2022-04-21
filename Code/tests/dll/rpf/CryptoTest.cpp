#include "pch.h"

#include "Crypto/AES.h"
#include "Crypto/Jenkins.h"

TEST(Jenkins32, CalculateChecksum)
{
	DWORD result = Jenkins32((LPCBYTE)"Hello World!", 12);

	ASSERT_EQ(result, 0x2476CEDB);
}

TEST(AES, EncryptAndDecrypt)
{
	BYTE key[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

	BYTE* pBuffer = NULL;
	INT iBufferSize = 0;
	ASSERT_HRESULT_SUCCEEDED(EncryptAES((LPCBYTE)"Hello World", 12, &pBuffer, &iBufferSize, key));

	BYTE* pDBuffer = NULL;
	INT iDBufferSize = 0;
	ASSERT_HRESULT_SUCCEEDED(DecryptAES(pBuffer, iBufferSize, &pDBuffer, &iDBufferSize, key));

	ASSERT_STREQ((const char*)pDBuffer, "Hello World");

	delete[] pBuffer;
	delete[] pDBuffer;
}

#include "RPF.h"

#include "Crypto/Keys.h"

HRESULT RPF::Init(LPCWSTR szGTA5Path)
{
	HANDLE hFile = CreateFile(szGTA5Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == NULL || hFile == INVALID_HANDLE_VALUE)
		return E_ABORT;

	// Read the whole file into memory
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	LPBYTE lpFileData = new BYTE[dwFileSize];

	if (!ReadFile(hFile, lpFileData, dwFileSize, NULL, NULL))
		return E_UNEXPECTED;

	CloseHandle(hFile);

	InitGTA5Keys(lpFileData, dwFileSize);

	delete[] lpFileData;

	return S_OK;
}

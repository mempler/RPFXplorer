#include "pch.h"
#include "SHA.h"

std::array<BYTE, 20> GenerateSHA1(LPCBYTE lpBuffer, DWORD dwBufferSize)
{
	std::array<BYTE, 20> buffer{};
	assert(SHA1(lpBuffer, dwBufferSize, buffer.data()));
	return buffer;
}

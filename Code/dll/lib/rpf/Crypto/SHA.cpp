#include "SHA.h"

#include <openssl/sha.h>
#include <cassert>

std::array<BYTE, 20> GenerateSHA1(LPCBYTE lpBuffer, DWORD dwBufferSize)
{
	std::array<BYTE, 20> buffer{};
	assert(SHA1(lpBuffer, dwBufferSize, buffer.data()));
	return buffer;
}

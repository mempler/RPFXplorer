#pragma once

#include <wtypes.h>
#include <array>

// NOTE: you must delete[] lpOutBuffer after usage
std::array<BYTE, 20> GenerateSHA1(LPCBYTE lpBuffer, DWORD dwBufferSize);

#pragma once

#include "RPF.h"

// NOTE: you must delete[] lpOutBuffer after usage
RPF_API std::array<BYTE, 20> GenerateSHA1(LPCBYTE lpBuffer, DWORD dwBufferSize);

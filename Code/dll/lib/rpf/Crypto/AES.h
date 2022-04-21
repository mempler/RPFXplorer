#pragma once

#include <wtypes.h>

#include "RPF.h"

RPF_API HRESULT EncryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds = 1);
RPF_API HRESULT DecryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds = 1);

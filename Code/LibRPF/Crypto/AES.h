#pragma once

#include <wtypes.h>

HRESULT EncryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds = 1);
HRESULT DecryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds = 1);

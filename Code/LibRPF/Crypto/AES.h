#pragma once

#include <wtypes.h>

inline HRESULT EncryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPDWORD lpOutBufferSize, BYTE key[32], DWORD dwRounds = -1)
{
    HCRYPTPROV hCrypt = NULL;
    HCRYPTKEY hKey = NULL;

    DWORD rounds = dwRounds == -1 ? 1 : dwRounds;
    DWORD length = dwBufferSize;

    BYTE block[16]{};

    struct {
        BLOBHEADER hdr;
        DWORD len;
        BYTE key[32];
    } key_blob{};

    DWORD dwMode = CRYPT_MODE_ECB;
    key_blob.hdr.bType = PLAINTEXTKEYBLOB;
    key_blob.hdr.bVersion = CUR_BLOB_VERSION;
    key_blob.hdr.reserved = 0;
    key_blob.hdr.aiKeyAlg = CALG_AES_256;
    key_blob.len = 32;
    CopyMemory(key_blob.key, key, 32);

    if (!CryptAcquireContext(&hCrypt, NULL, MS_ENH_RSA_AES_PROV, PROV_RSA_AES, 0))
        goto AES_FAIL;

    if (!CryptImportKey(hCrypt, (BYTE*)&key_blob, sizeof(key_blob), NULL, 0, &hKey))
        goto AES_FAIL;

    if (!CryptSetKeyParam(hKey, KP_MODE, (BYTE*)&dwMode, 0))
        goto AES_FAIL;

    *lpOutBufferSize = dwBufferSize + (16 - (dwBufferSize % 16));
    *lpOutBuffer = new BYTE[*lpOutBufferSize];

    for (size_t i = 0; i < rounds; i++)
    {
        ZeroMemory(block, 16);
        DWORD offset = dwBufferSize - length;
        CopyMemory(block, lpBuffer + offset, length % 16);

        DWORD pdwDataLen = length % 16;
        length -= length % 16;

        if (!CryptEncrypt(hKey, NULL, TRUE, 0, block, &pdwDataLen, 16))
            goto AES_FAIL;

        CopyMemory(*lpOutBuffer + offset, block, 16);
    }
    
    goto AES_COMPLETE;

AES_FAIL:
    if (hKey)
        CryptDestroyKey(hKey);

    if (hCrypt)
        CryptReleaseContext(hCrypt, 0);

    return E_FAIL;

AES_COMPLETE:
    if (hKey)
        CryptDestroyKey(hKey);

    if (hCrypt)
        CryptReleaseContext(hCrypt, 0);

    return S_OK;
}

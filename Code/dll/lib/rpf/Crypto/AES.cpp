#include "pch.h"
#include "AES.h"

HRESULT EncryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds)
{
    int paddingLength = 0;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    INT bufferSize = dwBufferSize + AES_BLOCK_SIZE;
    *lpOutBuffer = new BYTE[bufferSize];

    if (!EVP_EncryptInit(ctx, EVP_aes_256_ecb(), key, NULL))
        return E_UNEXPECTED;

    if (!EVP_EncryptUpdate(ctx, *lpOutBuffer, &bufferSize, lpBuffer, dwBufferSize))
        return E_UNEXPECTED;

    if (!EVP_EncryptFinal_ex(ctx, *lpOutBuffer + bufferSize, &paddingLength))
        return E_UNEXPECTED;

    *lpOutBufferSize = bufferSize + AES_BLOCK_SIZE;

    EVP_CIPHER_CTX_free(ctx);

    return S_OK;
}

HRESULT DecryptAES(LPCBYTE lpBuffer, DWORD dwBufferSize, LPBYTE* lpOutBuffer, LPINT lpOutBufferSize, BYTE key[32], DWORD dwRounds)
{
    int paddingLength = 0;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    INT bufferSize = dwBufferSize;
    *lpOutBuffer = new BYTE[bufferSize];

    if (!EVP_DecryptInit(ctx, EVP_aes_256_ecb(), key, NULL))
        return E_UNEXPECTED;

    if (!EVP_DecryptUpdate(ctx, *lpOutBuffer, &bufferSize, lpBuffer, dwBufferSize))
        return E_UNEXPECTED;

    if (!EVP_DecryptFinal_ex(ctx, *lpOutBuffer + bufferSize, &paddingLength))
        return E_UNEXPECTED;

    *lpOutBufferSize = bufferSize + AES_BLOCK_SIZE;

    EVP_CIPHER_CTX_free(ctx);

    return S_OK;
}

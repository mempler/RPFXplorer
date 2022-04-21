#pragma once

#include <wtypes.h>

constexpr DWORD Jenkins32(LPCBYTE key, DWORD length)
{
    DWORD hash = 0;
    for (size_t i = 0; i < length; i++)
    {
        hash += key[i];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

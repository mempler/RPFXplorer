#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <atlbase.h>
#include <atlstr.h>
#include <combaseapi.h>

#ifndef _LPCBYTE_DEFINED
#define _LPCBYTE_DEFINED
typedef const BYTE* LPCBYTE;
#endif
#ifndef _LPCVOID_DEFINED
#define _LPCVOID_DEFINED
typedef const VOID* LPCVOID;
#endif

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include <iostream>
#include <cassert>
#include <future>
#include <vector>
#include <string>
#include <array>

#include "RPF.h"
#include "RPFStructure.h"

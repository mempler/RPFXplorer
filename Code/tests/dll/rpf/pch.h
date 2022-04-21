#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <atlbase.h>
#include <atlstr.h>
#include <combaseapi.h>

#ifndef _LPCBYTE_DEFINED
#define _LPCBYTE_DEFINED
typedef const BYTE *LPCBYTE;
#endif
#ifndef _LPCVOID_DEFINED
#define _LPCVOID_DEFINED
typedef const VOID *LPCVOID;
#endif

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <array>
#include <cassert>
#include <future>
#include <iostream>
#include <string>
#include <vector>

#include "RPF.h"
#include "RPFStructure.h"

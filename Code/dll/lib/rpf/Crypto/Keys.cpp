#include "pch.h"
#include "Keys.h"

#include "SHA.h"

// Copied from https://github.com/dexyfex/CodeWalker/blob/master/CodeWalker.Core/GameFiles/Utils/GTAKeys.cs
// causes wow, i could've not done that lmao
/*
	Copyright(c) 2015 Neodymium

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

struct GTA5NGLUT
{
	BYTE LUT0[256][256] { };
	BYTE LUT1[256][256] { };
	BYTE Indices[65536] { };

	BYTE LookUp(UINT nValue)
	{
		UINT h16 = (nValue & 0xFFFF0000) >> 16;
		UINT l8 = (nValue & 0x0000FF00) >> 8;
		UINT l0 = (nValue & 0x000000FF) >> 0;

		return LUT0[LUT1[Indices[h16]][l8]][l0];
	}
};

BYTE		PC_AES_KEY[0x20];
BYTE		PC_NG_KEYS[0x65][0x110];
UINT		PC_NG_DECRYPT_TABLES[0x11][0x10][0x100];
UINT		PC_NG_ENCRYPT_TABLES[0x11][0x10][0x100];
GTA5NGLUT	PC_NG_ENCRYPT_LUT[0x11][0x10];
BYTE		PC_LUT[0x100];
BYTE		PC_AWC_KEY[0x10];

namespace KeyHashes
{
	constexpr BYTE PC_AES_KEY_HASH[] = { 0xA0, 0x79, 0x61, 0x28, 0xA7, 0x75, 0x72, 0x0A, 0xC2, 0x04, 0xD9, 0x81, 0x9F, 0x68, 0xC1, 0x72, 0xE3, 0x95, 0x2C, 0x6D };
}

namespace HashSearch
{
	constexpr DWORD BLOCK_LENGTH = 1048576;
	constexpr DWORD ALIGN_LENGTH = 16;

	template <DWORD dwHashCount, DWORD dwLength, typename TArr>
	std::array<std::array<BYTE, dwLength>, dwHashCount> SearchHashes(LPBYTE lpBuffer, DWORD dwBufferLength, TArr lpHashes)
	{
		std::array<std::array<BYTE, dwLength>, dwHashCount> result{ };
		std::array<BYTE, dwLength> buffer{};

		// TODO: optimize as this is freaking SLOW!

		for (DWORD k = 0; k < (dwBufferLength / BLOCK_LENGTH); k++)
		{
			for (DWORD i = 0; i < BLOCK_LENGTH / ALIGN_LENGTH; i++)
			{
				DWORD position = k * BLOCK_LENGTH + i * ALIGN_LENGTH;
				if (position >= dwBufferLength)
					continue;

				std::copy(lpBuffer + position, lpBuffer + position + dwLength, buffer.begin());

				auto hash = GenerateSHA1(buffer.data(), dwLength);

				for (DWORD j = 0; j < dwHashCount; j++)
				{
					// hash == lpHashes[j]
					if (std::equal(hash.begin(), hash.end(), lpHashes[j], lpHashes[j] + 20))
					{
						result[j] = buffer;
					}
				}
			}
		}

		return result;
	}

	template <DWORD dwHashCount, DWORD dwLength>
	std::array<BYTE, dwLength> SearchHash(LPBYTE lpBuffer, DWORD dwBufferLength, LPCBYTE lpHash)
	{
		return SearchHashes<dwHashCount, dwLength>(lpBuffer, dwBufferLength, &lpHash).at(0);
	}
}

void InitFromMagic()
{
}

void InitGTA5Keys(LPBYTE lpData, DWORD dwLength)
{
	auto AESKey = HashSearch::SearchHash<1, 0x20>(lpData, dwLength, KeyHashes::PC_AES_KEY_HASH);
	CopyMemory(PC_AES_KEY, AESKey.data(), sizeof(PC_AES_KEY));

	std::cout << "Found AES Key: ";
	for (size_t i = 0; i < 32; i++)
	{
		std::cout << std::hex << (int) PC_AES_KEY[i];
	}
	std::cout << std::endl;

	InitFromMagic();
}

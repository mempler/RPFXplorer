#pragma once

#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace std
{
    inline std::wstring convert(const std::string& str)
    {
        int count = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), NULL, 0);
        std::wstring wstr(count, 0);
        MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), &wstr[0], count);
        return wstr;
    }

    inline std::string convert(const std::wstring& str)
    {
        int count = WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0, NULL, NULL);
        std::string strTo(count, 0);
        WideCharToMultiByte(CP_UTF8, 0, &str[0], (int)str.size(), &strTo[0], count, NULL, NULL);
        return strTo;
    }
}

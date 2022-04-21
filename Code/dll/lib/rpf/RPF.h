#pragma once

#ifdef __RPF
	#define RPF_API __declspec( dllexport )
#else
	#define RPF_API __declspec( dllimport )
#endif

namespace RPF
{
	RPF_API HRESULT Init(LPCWSTR szGTA5Path);
}

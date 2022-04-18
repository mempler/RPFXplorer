

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 04:14:07 2038
 */
/* Compiler settings for RPFXplorer.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IShellFolderImpl,0x4cceecac,0xfbdc,0x4487,0xa6,0xcf,0xc2,0x1f,0x49,0xf8,0xf4,0x77);


MIDL_DEFINE_GUID(IID, IID_IShellViewImpl,0x0EA6B88C,0x6FC4,0x4DBC,0xAE,0x9C,0x7D,0x3B,0xFE,0x2C,0x9F,0xF9);


MIDL_DEFINE_GUID(IID, LIBID_RPFXplorerLib,0x0dfd9ea1,0xe255,0x4fb0,0xb4,0x0b,0x98,0xa0,0xa7,0x7d,0xc9,0xc8);


MIDL_DEFINE_GUID(CLSID, CLSID_ShellFolderImpl,0x397481b8,0x1b95,0x41dc,0xbf,0xe1,0x0c,0x3f,0x98,0xe5,0x04,0xee);


MIDL_DEFINE_GUID(CLSID, CLSID_ShellViewImpl,0xE6B437AF,0xF4E6,0x4731,0xB0,0x4A,0xD5,0x20,0xFD,0x1F,0x4E,0xD6);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif




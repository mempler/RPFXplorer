

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)


#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#include "ndr64types.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "RPFXplorer_h.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _RPFXplorer_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } RPFXplorer_MIDL_TYPE_FORMAT_STRING;

typedef struct _RPFXplorer_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } RPFXplorer_MIDL_PROC_FORMAT_STRING;

typedef struct _RPFXplorer_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } RPFXplorer_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

static const RPC_SYNTAX_IDENTIFIER  _NDR64_RpcTransferSyntax = 
{{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}};



extern const RPFXplorer_MIDL_TYPE_FORMAT_STRING RPFXplorer__MIDL_TypeFormatString;
extern const RPFXplorer_MIDL_PROC_FORMAT_STRING RPFXplorer__MIDL_ProcFormatString;
extern const RPFXplorer_MIDL_EXPR_FORMAT_STRING RPFXplorer__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IShellFolderImpl_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IShellFolderImpl_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IShellViewImpl_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IShellViewImpl_ProxyInfo;



#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const RPFXplorer_MIDL_PROC_FORMAT_STRING RPFXplorer__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const RPFXplorer_MIDL_TYPE_FORMAT_STRING RPFXplorer__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IShellFolderImpl, ver. 0.0,
   GUID={0x4cceecac,0xfbdc,0x4487,{0xa6,0xcf,0xc2,0x1f,0x49,0xf8,0xf4,0x77}} */

#pragma code_seg(".orpc")
static const unsigned short IShellFolderImpl_FormatStringOffsetTable[] =
    {
    0
    };



/* Object interface: IShellViewImpl, ver. 0.0,
   GUID={0x0EA6B88C,0x6FC4,0x4DBC,{0xAE,0x9C,0x7D,0x3B,0xFE,0x2C,0x9F,0xF9}} */

#pragma code_seg(".orpc")
static const unsigned short IShellViewImpl_FormatStringOffsetTable[] =
    {
    0
    };



#endif /* defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)




#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif


#include "ndr64types.h"
#include "pshpack8.h"


typedef 
NDR64_FORMAT_UINT32
__midl_frag1_t;
extern const __midl_frag1_t __midl_frag1;

static const __midl_frag1_t __midl_frag1 =
(NDR64_UINT32) 0 /* 0x0 */;


#include "poppack.h"



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IShellFolderImpl, ver. 0.0,
   GUID={0x4cceecac,0xfbdc,0x4487,{0xa6,0xcf,0xc2,0x1f,0x49,0xf8,0xf4,0x77}} */

#pragma code_seg(".orpc")
static const FormatInfoRef IShellFolderImpl_Ndr64ProcTable[] =
    {
    0
    };


static const MIDL_SYNTAX_INFO IShellFolderImpl_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    RPFXplorer__MIDL_ProcFormatString.Format,
    &IShellFolderImpl_FormatStringOffsetTable[-3],
    RPFXplorer__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &IShellFolderImpl_Ndr64ProcTable[-3],
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO IShellFolderImpl_ProxyInfo =
    {
    &Object_StubDesc,
    RPFXplorer__MIDL_ProcFormatString.Format,
    &IShellFolderImpl_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IShellFolderImpl_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO IShellFolderImpl_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    RPFXplorer__MIDL_ProcFormatString.Format,
    (unsigned short *) &IShellFolderImpl_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IShellFolderImpl_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(3) _IShellFolderImplProxyVtbl = 
{
    0,
    &IID_IShellFolderImpl,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IShellFolderImplStubVtbl =
{
    &IID_IShellFolderImpl,
    &IShellFolderImpl_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IShellViewImpl, ver. 0.0,
   GUID={0x0EA6B88C,0x6FC4,0x4DBC,{0xAE,0x9C,0x7D,0x3B,0xFE,0x2C,0x9F,0xF9}} */

#pragma code_seg(".orpc")
static const FormatInfoRef IShellViewImpl_Ndr64ProcTable[] =
    {
    0
    };


static const MIDL_SYNTAX_INFO IShellViewImpl_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    RPFXplorer__MIDL_ProcFormatString.Format,
    &IShellViewImpl_FormatStringOffsetTable[-3],
    RPFXplorer__MIDL_TypeFormatString.Format,
    0,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &IShellViewImpl_Ndr64ProcTable[-3],
    0,
    0,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO IShellViewImpl_ProxyInfo =
    {
    &Object_StubDesc,
    RPFXplorer__MIDL_ProcFormatString.Format,
    &IShellViewImpl_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IShellViewImpl_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO IShellViewImpl_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    RPFXplorer__MIDL_ProcFormatString.Format,
    (unsigned short *) &IShellViewImpl_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IShellViewImpl_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(3) _IShellViewImplProxyVtbl = 
{
    0,
    &IID_IShellViewImpl,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy
};

const CInterfaceStubVtbl _IShellViewImplStubVtbl =
{
    &IID_IShellViewImpl,
    &IShellViewImpl_ServerInfo,
    3,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    RPFXplorer__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x2000001, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _RPFXplorer_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IShellViewImplProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IShellFolderImplProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _RPFXplorer_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IShellViewImplStubVtbl,
    ( CInterfaceStubVtbl *) &_IShellFolderImplStubVtbl,
    0
};

PCInterfaceName const _RPFXplorer_InterfaceNamesList[] = 
{
    "IShellViewImpl",
    "IShellFolderImpl",
    0
};


#define _RPFXplorer_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _RPFXplorer, pIID, n)

int __stdcall _RPFXplorer_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _RPFXplorer, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _RPFXplorer, 2, *pIndex )
    
}

const ExtendedProxyFileInfo RPFXplorer_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _RPFXplorer_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _RPFXplorer_StubVtblList,
    (const PCInterfaceName * ) & _RPFXplorer_InterfaceNamesList,
    0, /* no delegation */
    & _RPFXplorer_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/


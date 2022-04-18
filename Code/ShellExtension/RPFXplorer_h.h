

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __RPFXplorer_h_h__
#define __RPFXplorer_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IShellFolderImpl_FWD_DEFINED__
#define __IShellFolderImpl_FWD_DEFINED__
typedef interface IShellFolderImpl IShellFolderImpl;

#endif 	/* __IShellFolderImpl_FWD_DEFINED__ */


#ifndef __IShellViewImpl_FWD_DEFINED__
#define __IShellViewImpl_FWD_DEFINED__
typedef interface IShellViewImpl IShellViewImpl;

#endif 	/* __IShellViewImpl_FWD_DEFINED__ */


#ifndef __ShellFolderImpl_FWD_DEFINED__
#define __ShellFolderImpl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellFolderImpl ShellFolderImpl;
#else
typedef struct ShellFolderImpl ShellFolderImpl;
#endif /* __cplusplus */

#endif 	/* __ShellFolderImpl_FWD_DEFINED__ */


#ifndef __ShellViewImpl_FWD_DEFINED__
#define __ShellViewImpl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellViewImpl ShellViewImpl;
#else
typedef struct ShellViewImpl ShellViewImpl;
#endif /* __cplusplus */

#endif 	/* __ShellViewImpl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IShellFolderImpl_INTERFACE_DEFINED__
#define __IShellFolderImpl_INTERFACE_DEFINED__

/* interface IShellFolderImpl */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IShellFolderImpl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4cceecac-fbdc-4487-a6cf-c21f49f8f477")
    IShellFolderImpl : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IShellFolderImplVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellFolderImpl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellFolderImpl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellFolderImpl * This);
        
        END_INTERFACE
    } IShellFolderImplVtbl;

    interface IShellFolderImpl
    {
        CONST_VTBL struct IShellFolderImplVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellFolderImpl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellFolderImpl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellFolderImpl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShellFolderImpl_INTERFACE_DEFINED__ */


#ifndef __IShellViewImpl_INTERFACE_DEFINED__
#define __IShellViewImpl_INTERFACE_DEFINED__

/* interface IShellViewImpl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IShellViewImpl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0EA6B88C-6FC4-4DBC-AE9C-7D3BFE2C9FF9")
    IShellViewImpl : public IUnknown
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct IShellViewImplVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IShellViewImpl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IShellViewImpl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IShellViewImpl * This);
        
        END_INTERFACE
    } IShellViewImplVtbl;

    interface IShellViewImpl
    {
        CONST_VTBL struct IShellViewImplVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellViewImpl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IShellViewImpl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IShellViewImpl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IShellViewImpl_INTERFACE_DEFINED__ */



#ifndef __RPFXplorerLib_LIBRARY_DEFINED__
#define __RPFXplorerLib_LIBRARY_DEFINED__

/* library RPFXplorerLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_RPFXplorerLib;

EXTERN_C const CLSID CLSID_ShellFolderImpl;

#ifdef __cplusplus

class DECLSPEC_UUID("397481b8-1b95-41dc-bfe1-0c3f98e504ee")
ShellFolderImpl;
#endif

EXTERN_C const CLSID CLSID_ShellViewImpl;

#ifdef __cplusplus

class DECLSPEC_UUID("E6B437AF-F4E6-4731-B04A-D520FD1F4ED6")
ShellViewImpl;
#endif
#endif /* __RPFXplorerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



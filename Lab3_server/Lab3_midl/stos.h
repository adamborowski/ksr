

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Thu Mar 13 23:51:39 2014
 */
/* Compiler settings for stos.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __stos_h__
#define __stos_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IStos_FWD_DEFINED__
#define __IStos_FWD_DEFINED__
typedef interface IStos IStos;

#endif 	/* __IStos_FWD_DEFINED__ */


#ifndef __IStos_FWD_DEFINED__
#define __IStos_FWD_DEFINED__
typedef interface IStos IStos;

#endif 	/* __IStos_FWD_DEFINED__ */


#ifndef __Stos_FWD_DEFINED__
#define __Stos_FWD_DEFINED__

#ifdef __cplusplus
typedef class Stos Stos;
#else
typedef struct Stos Stos;
#endif /* __cplusplus */

#endif 	/* __Stos_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IStos_INTERFACE_DEFINED__
#define __IStos_INTERFACE_DEFINED__

/* interface IStos */
/* [uuid][object] */ 


EXTERN_C const IID IID_IStos;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B3AF78D-5998-484D-A863-A164C76AC7BE")
    IStos : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Push( 
            int val) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pop( 
            /* [out] */ int *val) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Top( 
            /* [out] */ int *val) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IStosVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IStos * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IStos * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IStos * This);
        
        HRESULT ( STDMETHODCALLTYPE *Push )( 
            IStos * This,
            int val);
        
        HRESULT ( STDMETHODCALLTYPE *Pop )( 
            IStos * This,
            /* [out] */ int *val);
        
        HRESULT ( STDMETHODCALLTYPE *Top )( 
            IStos * This,
            /* [out] */ int *val);
        
        END_INTERFACE
    } IStosVtbl;

    interface IStos
    {
        CONST_VTBL struct IStosVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStos_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IStos_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IStos_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IStos_Push(This,val)	\
    ( (This)->lpVtbl -> Push(This,val) ) 

#define IStos_Pop(This,val)	\
    ( (This)->lpVtbl -> Pop(This,val) ) 

#define IStos_Top(This,val)	\
    ( (This)->lpVtbl -> Top(This,val) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IStos_INTERFACE_DEFINED__ */



#ifndef __KSRStack_LIBRARY_DEFINED__
#define __KSRStack_LIBRARY_DEFINED__

/* library KSRStack */
/* [version][helpstring][uuid] */ 



EXTERN_C const IID LIBID_KSRStack;

EXTERN_C const CLSID CLSID_Stos;

#ifdef __cplusplus

class DECLSPEC_UUID("E858E187-7687-4A8A-85A7-1A9EF65237AE")
Stos;
#endif
#endif /* __KSRStack_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



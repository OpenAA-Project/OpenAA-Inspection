
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0286 */
/* at Wed Jan 09 10:37:49 2019
 */
/* Compiler settings for .\DTKImage.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __DTKImage_h__
#define __DTKImage_h__

/* Forward Declarations */ 

#ifndef __IAnnotationCollection_FWD_DEFINED__
#define __IAnnotationCollection_FWD_DEFINED__
typedef interface IAnnotationCollection IAnnotationCollection;
#endif 	/* __IAnnotationCollection_FWD_DEFINED__ */


#ifndef __IImageObject_FWD_DEFINED__
#define __IImageObject_FWD_DEFINED__
typedef interface IImageObject IImageObject;
#endif 	/* __IImageObject_FWD_DEFINED__ */


#ifndef __IImageObjectCollection_FWD_DEFINED__
#define __IImageObjectCollection_FWD_DEFINED__
typedef interface IImageObjectCollection IImageObjectCollection;
#endif 	/* __IImageObjectCollection_FWD_DEFINED__ */


#ifndef __IImageViewer_FWD_DEFINED__
#define __IImageViewer_FWD_DEFINED__
typedef interface IImageViewer IImageViewer;
#endif 	/* __IImageViewer_FWD_DEFINED__ */


#ifndef __IAnnotationLine_FWD_DEFINED__
#define __IAnnotationLine_FWD_DEFINED__
typedef interface IAnnotationLine IAnnotationLine;
#endif 	/* __IAnnotationLine_FWD_DEFINED__ */


#ifndef __IAnnotationRectangle_FWD_DEFINED__
#define __IAnnotationRectangle_FWD_DEFINED__
typedef interface IAnnotationRectangle IAnnotationRectangle;
#endif 	/* __IAnnotationRectangle_FWD_DEFINED__ */


#ifndef __ITIFFUtils_FWD_DEFINED__
#define __ITIFFUtils_FWD_DEFINED__
typedef interface ITIFFUtils ITIFFUtils;
#endif 	/* __ITIFFUtils_FWD_DEFINED__ */


#ifndef __ITwain_FWD_DEFINED__
#define __ITwain_FWD_DEFINED__
typedef interface ITwain ITwain;
#endif 	/* __ITwain_FWD_DEFINED__ */


#ifndef __IPDFUtils_FWD_DEFINED__
#define __IPDFUtils_FWD_DEFINED__
typedef interface IPDFUtils IPDFUtils;
#endif 	/* __IPDFUtils_FWD_DEFINED__ */


#ifndef __ImageObject_FWD_DEFINED__
#define __ImageObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageObject ImageObject;
#else
typedef struct ImageObject ImageObject;
#endif /* __cplusplus */

#endif 	/* __ImageObject_FWD_DEFINED__ */


#ifndef __ImageObjectCollection_FWD_DEFINED__
#define __ImageObjectCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageObjectCollection ImageObjectCollection;
#else
typedef struct ImageObjectCollection ImageObjectCollection;
#endif /* __cplusplus */

#endif 	/* __ImageObjectCollection_FWD_DEFINED__ */


#ifndef ___IImageViewerEvents_FWD_DEFINED__
#define ___IImageViewerEvents_FWD_DEFINED__
typedef interface _IImageViewerEvents _IImageViewerEvents;
#endif 	/* ___IImageViewerEvents_FWD_DEFINED__ */


#ifndef __ImageViewer_FWD_DEFINED__
#define __ImageViewer_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImageViewer ImageViewer;
#else
typedef struct ImageViewer ImageViewer;
#endif /* __cplusplus */

#endif 	/* __ImageViewer_FWD_DEFINED__ */


#ifndef __AnnotationLine_FWD_DEFINED__
#define __AnnotationLine_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnnotationLine AnnotationLine;
#else
typedef struct AnnotationLine AnnotationLine;
#endif /* __cplusplus */

#endif 	/* __AnnotationLine_FWD_DEFINED__ */


#ifndef __AnnotationCollection_FWD_DEFINED__
#define __AnnotationCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnnotationCollection AnnotationCollection;
#else
typedef struct AnnotationCollection AnnotationCollection;
#endif /* __cplusplus */

#endif 	/* __AnnotationCollection_FWD_DEFINED__ */


#ifndef __AnnotationRectangle_FWD_DEFINED__
#define __AnnotationRectangle_FWD_DEFINED__

#ifdef __cplusplus
typedef class AnnotationRectangle AnnotationRectangle;
#else
typedef struct AnnotationRectangle AnnotationRectangle;
#endif /* __cplusplus */

#endif 	/* __AnnotationRectangle_FWD_DEFINED__ */


#ifndef ___ITIFFUtilsEvents_FWD_DEFINED__
#define ___ITIFFUtilsEvents_FWD_DEFINED__
typedef interface _ITIFFUtilsEvents _ITIFFUtilsEvents;
#endif 	/* ___ITIFFUtilsEvents_FWD_DEFINED__ */


#ifndef __TIFFUtils_FWD_DEFINED__
#define __TIFFUtils_FWD_DEFINED__

#ifdef __cplusplus
typedef class TIFFUtils TIFFUtils;
#else
typedef struct TIFFUtils TIFFUtils;
#endif /* __cplusplus */

#endif 	/* __TIFFUtils_FWD_DEFINED__ */


#ifndef ___IPDFUtilsEvents_FWD_DEFINED__
#define ___IPDFUtilsEvents_FWD_DEFINED__
typedef interface _IPDFUtilsEvents _IPDFUtilsEvents;
#endif 	/* ___IPDFUtilsEvents_FWD_DEFINED__ */


#ifndef __PDFUtils_FWD_DEFINED__
#define __PDFUtils_FWD_DEFINED__

#ifdef __cplusplus
typedef class PDFUtils PDFUtils;
#else
typedef struct PDFUtils PDFUtils;
#endif /* __cplusplus */

#endif 	/* __PDFUtils_FWD_DEFINED__ */


#ifndef ___ITwainEvents_FWD_DEFINED__
#define ___ITwainEvents_FWD_DEFINED__
typedef interface _ITwainEvents _ITwainEvents;
#endif 	/* ___ITwainEvents_FWD_DEFINED__ */


#ifndef __Twain_FWD_DEFINED__
#define __Twain_FWD_DEFINED__

#ifdef __cplusplus
typedef class Twain Twain;
#else
typedef struct Twain Twain;
#endif /* __cplusplus */

#endif 	/* __Twain_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_DTKImage_0000 */
/* [local] */ 

typedef /* [public][v1_enum] */ 
enum ImageFormatEnum
    {	IF_Unknown	= 0,
	IF_BMP	= 1,
	IF_PNG	= 2,
	IF_JPEG	= 3,
	IF_TIFF	= 4
    }	ImageFormatEnum;

typedef /* [public][v1_enum] */ 
enum AutoSizeModeEnum
    {	ASM_None	= 0,
	ASM_Stretch	= 1,
	ASM_FitToWidth	= 2,
	ASM_FitToHeight	= 3,
	ASM_BestFit	= 4
    }	AutoSizeModeEnum;

typedef /* [public][v1_enum] */ 
enum BinarizationMethodEnum
    {	BM_Simple	= 0,
	BM_ErrorDiffusion	= 1
    }	BinarizationMethodEnum;

typedef /* [public][v1_enum] */ 
enum InterpolationMethodEnum
    {	IM_NEAREST_NEIGHBOUR	= 1,
	IM_BILINEAR	= 2,
	IM_BSPLINE	= 3,
	IM_BICUBIC	= 4,
	IM_BICUBIC2	= 5,
	IM_LANCZOS	= 6,
	IM_BOX	= 7,
	IM_HERMITE	= 8,
	IM_HAMMING	= 9,
	IM_SINC	= 10,
	IM_BLACKMAN	= 11,
	IM_BESSEL	= 12,
	IM_GAUSSIAN	= 13,
	IM_QUADRATIC	= 14,
	IM_MITCHELL	= 15,
	IM_CATROM	= 16
    }	InterpolationMethodEnum;

typedef /* [public][v1_enum] */ 
enum OverflowMethodEnum
    {	OM_COLOR	= 1,
	OM_BACKGROUND	= 2,
	OM_TRANSPARENT	= 3,
	OM_WRAP	= 4,
	OM_REPEAT	= 5,
	OM_MIRROR	= 6
    }	OverflowMethodEnum;

typedef /* [public][v1_enum] */ 
enum TIFFCompressionEnum
    {	TIFFC_Unknown	= 0,
	TIFFC_None	= 1,
	TIFFC_CCITTRLE	= 2,
	TIFFC_CCITTFAX3	= 3,
	TIFFC_CCITTFAX4	= 4,
	TIFFC_LZW	= 5,
	TIFFC_OJPEG	= 6,
	TIFFC_JPEG	= 7,
	TIFFC_PACKBITS	= 32773
    }	TIFFCompressionEnum;




extern RPC_IF_HANDLE __MIDL_itf_DTKImage_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DTKImage_0000_v0_0_s_ifspec;

#ifndef __IAnnotationCollection_INTERFACE_DEFINED__
#define __IAnnotationCollection_INTERFACE_DEFINED__

/* interface IAnnotationCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAnnotationCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6D0552B-EC2F-4268-B870-F3A411DC856C")
    IAnnotationCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG ind,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLine( 
            LONG x1,
            LONG y1,
            LONG x2,
            LONG y2,
            OLE_COLOR color,
            LONG frame) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddRectangle( 
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            OLE_COLOR color,
            LONG frame) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnnotationCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAnnotationCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAnnotationCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IAnnotationCollection __RPC_FAR * This,
            /* [in] */ LONG ind,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddLine )( 
            IAnnotationCollection __RPC_FAR * This,
            LONG x1,
            LONG y1,
            LONG x2,
            LONG y2,
            OLE_COLOR color,
            LONG frame);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddRectangle )( 
            IAnnotationCollection __RPC_FAR * This,
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            OLE_COLOR color,
            LONG frame);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IAnnotationCollection __RPC_FAR * This);
        
        END_INTERFACE
    } IAnnotationCollectionVtbl;

    interface IAnnotationCollection
    {
        CONST_VTBL struct IAnnotationCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnnotationCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnnotationCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnnotationCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnnotationCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnnotationCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnnotationCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnnotationCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnnotationCollection_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IAnnotationCollection_get_Item(This,ind,pVal)	\
    (This)->lpVtbl -> get_Item(This,ind,pVal)

#define IAnnotationCollection_AddLine(This,x1,y1,x2,y2,color,frame)	\
    (This)->lpVtbl -> AddLine(This,x1,y1,x2,y2,color,frame)

#define IAnnotationCollection_AddRectangle(This,left,top,right,bottom,color,frame)	\
    (This)->lpVtbl -> AddRectangle(This,left,top,right,bottom,color,frame)

#define IAnnotationCollection_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationCollection_get_Count_Proxy( 
    IAnnotationCollection __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationCollection_get_Item_Proxy( 
    IAnnotationCollection __RPC_FAR * This,
    /* [in] */ LONG ind,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IAnnotationCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnnotationCollection_AddLine_Proxy( 
    IAnnotationCollection __RPC_FAR * This,
    LONG x1,
    LONG y1,
    LONG x2,
    LONG y2,
    OLE_COLOR color,
    LONG frame);


void __RPC_STUB IAnnotationCollection_AddLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnnotationCollection_AddRectangle_Proxy( 
    IAnnotationCollection __RPC_FAR * This,
    LONG left,
    LONG top,
    LONG right,
    LONG bottom,
    OLE_COLOR color,
    LONG frame);


void __RPC_STUB IAnnotationCollection_AddRectangle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAnnotationCollection_Clear_Proxy( 
    IAnnotationCollection __RPC_FAR * This);


void __RPC_STUB IAnnotationCollection_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnnotationCollection_INTERFACE_DEFINED__ */


#ifndef __IImageObject_INTERFACE_DEFINED__
#define __IImageObject_INTERFACE_DEFINED__

/* interface IImageObject */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IImageObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("305D0862-D37B-4F2B-BFF7-282AD497721A")
    IImageObject : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_xDPI( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_yDPI( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile( 
            BSTR fileName,
            LONG frame) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromBitmap( 
            LONG hBmp,
            LONG hPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromDIB( 
            LONG hDIB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromMemFile( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG dataLen,
            LONG frame) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bpp( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFileTIFF( 
            BSTR fileName,
            TIFFCompressionEnum compression) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFileJPEG( 
            BSTR fileName,
            LONG quality) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFileBMP( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFilePNG( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageViewer( 
            /* [retval][out] */ IImageViewer __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertToGrayScale( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Flip( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Mirror( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Negative( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RotateRight( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RotateLeft( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Rotate( 
            FLOAT angle,
            InterpolationMethodEnum inMethod,
            OverflowMethodEnum ofMethod,
            VARIANT_BOOL bKeepOriginalSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Binarize( 
            BinarizationMethodEnum method) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSkewAngle( 
            FLOAT __RPC_FAR *angle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Despeckle( 
            LONG ksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Dilate( 
            LONG ksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Erode( 
            LONG ksize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsBlank( 
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeBrightnessContrast( 
            LONG brightness,
            LONG contrast) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsGrayScale( 
            VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumColors( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HBITMAP( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FrameCount( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Frame( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFrame( 
            LONG frame) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Handle( 
            /* [retval][out] */ OLE_HANDLE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastErrorText( 
            BSTR __RPC_FAR *errorText) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Save( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Annotations( 
            /* [retval][out] */ IAnnotationCollection __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromBuffer( 
            LONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TooLight( 
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE TooDark( 
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsBlankRect( 
            LONG threshold,
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Crop( 
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            IImageObject __RPC_FAR *__RPC_FAR *image) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromFile2( 
            BSTR fileName,
            LONG frame,
            BSTR password) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFromMemFile2( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG dataLen,
            LONG frame,
            BSTR password) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImageObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImageObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImageObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImageObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_xDPI )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_yDPI )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromFile )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName,
            LONG frame);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromBitmap )( 
            IImageObject __RPC_FAR * This,
            LONG hBmp,
            LONG hPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromDIB )( 
            IImageObject __RPC_FAR * This,
            LONG hDIB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromMemFile )( 
            IImageObject __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG dataLen,
            LONG frame);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bpp )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveToFileTIFF )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName,
            TIFFCompressionEnum compression);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveToFileJPEG )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName,
            LONG quality);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveToFileBMP )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveToFilePNG )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ImageViewer )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ IImageViewer __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertToGrayScale )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Flip )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Mirror )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Negative )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RotateRight )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RotateLeft )( 
            IImageObject __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rotate )( 
            IImageObject __RPC_FAR * This,
            FLOAT angle,
            InterpolationMethodEnum inMethod,
            OverflowMethodEnum ofMethod,
            VARIANT_BOOL bKeepOriginalSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Binarize )( 
            IImageObject __RPC_FAR * This,
            BinarizationMethodEnum method);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSkewAngle )( 
            IImageObject __RPC_FAR * This,
            FLOAT __RPC_FAR *angle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Despeckle )( 
            IImageObject __RPC_FAR * This,
            LONG ksize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Dilate )( 
            IImageObject __RPC_FAR * This,
            LONG ksize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erode )( 
            IImageObject __RPC_FAR * This,
            LONG ksize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsBlank )( 
            IImageObject __RPC_FAR * This,
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeBrightnessContrast )( 
            IImageObject __RPC_FAR * This,
            LONG brightness,
            LONG contrast);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsGrayScale )( 
            IImageObject __RPC_FAR * This,
            VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumColors )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HBITMAP )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FrameCount )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Frame )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFrame )( 
            IImageObject __RPC_FAR * This,
            LONG frame);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Handle )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ OLE_HANDLE __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLastErrorText )( 
            IImageObject __RPC_FAR * This,
            BSTR __RPC_FAR *errorText);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Annotations )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ IAnnotationCollection __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromBuffer )( 
            IImageObject __RPC_FAR * This,
            LONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TooLight )( 
            IImageObject __RPC_FAR * This,
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TooDark )( 
            IImageObject __RPC_FAR * This,
            LONG threshold,
            VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IImageObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsBlankRect )( 
            IImageObject __RPC_FAR * This,
            LONG threshold,
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Crop )( 
            IImageObject __RPC_FAR * This,
            LONG left,
            LONG top,
            LONG right,
            LONG bottom,
            IImageObject __RPC_FAR *__RPC_FAR *image);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromFile2 )( 
            IImageObject __RPC_FAR * This,
            BSTR fileName,
            LONG frame,
            BSTR password);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadFromMemFile2 )( 
            IImageObject __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG dataLen,
            LONG frame,
            BSTR password);
        
        END_INTERFACE
    } IImageObjectVtbl;

    interface IImageObject
    {
        CONST_VTBL struct IImageObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImageObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImageObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImageObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImageObject_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IImageObject_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IImageObject_get_xDPI(This,pVal)	\
    (This)->lpVtbl -> get_xDPI(This,pVal)

#define IImageObject_get_yDPI(This,pVal)	\
    (This)->lpVtbl -> get_yDPI(This,pVal)

#define IImageObject_LoadFromFile(This,fileName,frame)	\
    (This)->lpVtbl -> LoadFromFile(This,fileName,frame)

#define IImageObject_LoadFromBitmap(This,hBmp,hPalette)	\
    (This)->lpVtbl -> LoadFromBitmap(This,hBmp,hPalette)

#define IImageObject_LoadFromDIB(This,hDIB)	\
    (This)->lpVtbl -> LoadFromDIB(This,hDIB)

#define IImageObject_LoadFromMemFile(This,fileData,dataLen,frame)	\
    (This)->lpVtbl -> LoadFromMemFile(This,fileData,dataLen,frame)

#define IImageObject_get_Bpp(This,pVal)	\
    (This)->lpVtbl -> get_Bpp(This,pVal)

#define IImageObject_SaveToFileTIFF(This,fileName,compression)	\
    (This)->lpVtbl -> SaveToFileTIFF(This,fileName,compression)

#define IImageObject_SaveToFileJPEG(This,fileName,quality)	\
    (This)->lpVtbl -> SaveToFileJPEG(This,fileName,quality)

#define IImageObject_SaveToFileBMP(This,fileName)	\
    (This)->lpVtbl -> SaveToFileBMP(This,fileName)

#define IImageObject_SaveToFilePNG(This,fileName)	\
    (This)->lpVtbl -> SaveToFilePNG(This,fileName)

#define IImageObject_get_ImageViewer(This,pVal)	\
    (This)->lpVtbl -> get_ImageViewer(This,pVal)

#define IImageObject_ConvertToGrayScale(This)	\
    (This)->lpVtbl -> ConvertToGrayScale(This)

#define IImageObject_Flip(This)	\
    (This)->lpVtbl -> Flip(This)

#define IImageObject_Mirror(This)	\
    (This)->lpVtbl -> Mirror(This)

#define IImageObject_Negative(This)	\
    (This)->lpVtbl -> Negative(This)

#define IImageObject_RotateRight(This)	\
    (This)->lpVtbl -> RotateRight(This)

#define IImageObject_RotateLeft(This)	\
    (This)->lpVtbl -> RotateLeft(This)

#define IImageObject_Rotate(This,angle,inMethod,ofMethod,bKeepOriginalSize)	\
    (This)->lpVtbl -> Rotate(This,angle,inMethod,ofMethod,bKeepOriginalSize)

#define IImageObject_Binarize(This,method)	\
    (This)->lpVtbl -> Binarize(This,method)

#define IImageObject_GetSkewAngle(This,angle)	\
    (This)->lpVtbl -> GetSkewAngle(This,angle)

#define IImageObject_Despeckle(This,ksize)	\
    (This)->lpVtbl -> Despeckle(This,ksize)

#define IImageObject_Dilate(This,ksize)	\
    (This)->lpVtbl -> Dilate(This,ksize)

#define IImageObject_Erode(This,ksize)	\
    (This)->lpVtbl -> Erode(This,ksize)

#define IImageObject_IsBlank(This,threshold,pVal)	\
    (This)->lpVtbl -> IsBlank(This,threshold,pVal)

#define IImageObject_ChangeBrightnessContrast(This,brightness,contrast)	\
    (This)->lpVtbl -> ChangeBrightnessContrast(This,brightness,contrast)

#define IImageObject_IsGrayScale(This,pVal)	\
    (This)->lpVtbl -> IsGrayScale(This,pVal)

#define IImageObject_get_NumColors(This,pVal)	\
    (This)->lpVtbl -> get_NumColors(This,pVal)

#define IImageObject_get_HBITMAP(This,pVal)	\
    (This)->lpVtbl -> get_HBITMAP(This,pVal)

#define IImageObject_get_FrameCount(This,pVal)	\
    (This)->lpVtbl -> get_FrameCount(This,pVal)

#define IImageObject_get_Frame(This,pVal)	\
    (This)->lpVtbl -> get_Frame(This,pVal)

#define IImageObject_SetFrame(This,frame)	\
    (This)->lpVtbl -> SetFrame(This,frame)

#define IImageObject_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IImageObject_get_Handle(This,pVal)	\
    (This)->lpVtbl -> get_Handle(This,pVal)

#define IImageObject_GetLastErrorText(This,errorText)	\
    (This)->lpVtbl -> GetLastErrorText(This,errorText)

#define IImageObject_Save(This,fileName)	\
    (This)->lpVtbl -> Save(This,fileName)

#define IImageObject_get_Annotations(This,pVal)	\
    (This)->lpVtbl -> get_Annotations(This,pVal)

#define IImageObject_LoadFromBuffer(This,pBuffer,width,height,stride,bpp)	\
    (This)->lpVtbl -> LoadFromBuffer(This,pBuffer,width,height,stride,bpp)

#define IImageObject_TooLight(This,threshold,pVal)	\
    (This)->lpVtbl -> TooLight(This,threshold,pVal)

#define IImageObject_TooDark(This,threshold,pVal)	\
    (This)->lpVtbl -> TooDark(This,threshold,pVal)

#define IImageObject_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IImageObject_IsBlankRect(This,threshold,left,top,right,bottom,pVal)	\
    (This)->lpVtbl -> IsBlankRect(This,threshold,left,top,right,bottom,pVal)

#define IImageObject_Crop(This,left,top,right,bottom,image)	\
    (This)->lpVtbl -> Crop(This,left,top,right,bottom,image)

#define IImageObject_LoadFromFile2(This,fileName,frame,password)	\
    (This)->lpVtbl -> LoadFromFile2(This,fileName,frame,password)

#define IImageObject_LoadFromMemFile2(This,fileData,dataLen,frame,password)	\
    (This)->lpVtbl -> LoadFromMemFile2(This,fileData,dataLen,frame,password)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Width_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Height_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_xDPI_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_xDPI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_yDPI_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_yDPI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromFile_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName,
    LONG frame);


void __RPC_STUB IImageObject_LoadFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromBitmap_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG hBmp,
    LONG hPalette);


void __RPC_STUB IImageObject_LoadFromBitmap_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromDIB_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG hDIB);


void __RPC_STUB IImageObject_LoadFromDIB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromMemFile_Proxy( 
    IImageObject __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
    LONG dataLen,
    LONG frame);


void __RPC_STUB IImageObject_LoadFromMemFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Bpp_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Bpp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_SaveToFileTIFF_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName,
    TIFFCompressionEnum compression);


void __RPC_STUB IImageObject_SaveToFileTIFF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_SaveToFileJPEG_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName,
    LONG quality);


void __RPC_STUB IImageObject_SaveToFileJPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_SaveToFileBMP_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName);


void __RPC_STUB IImageObject_SaveToFileBMP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_SaveToFilePNG_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName);


void __RPC_STUB IImageObject_SaveToFilePNG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_ImageViewer_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ IImageViewer __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_ImageViewer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_ConvertToGrayScale_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_ConvertToGrayScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Flip_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_Flip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Mirror_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_Mirror_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Negative_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_Negative_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_RotateRight_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_RotateRight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_RotateLeft_Proxy( 
    IImageObject __RPC_FAR * This);


void __RPC_STUB IImageObject_RotateLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Rotate_Proxy( 
    IImageObject __RPC_FAR * This,
    FLOAT angle,
    InterpolationMethodEnum inMethod,
    OverflowMethodEnum ofMethod,
    VARIANT_BOOL bKeepOriginalSize);


void __RPC_STUB IImageObject_Rotate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Binarize_Proxy( 
    IImageObject __RPC_FAR * This,
    BinarizationMethodEnum method);


void __RPC_STUB IImageObject_Binarize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_GetSkewAngle_Proxy( 
    IImageObject __RPC_FAR * This,
    FLOAT __RPC_FAR *angle);


void __RPC_STUB IImageObject_GetSkewAngle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Despeckle_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG ksize);


void __RPC_STUB IImageObject_Despeckle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Dilate_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG ksize);


void __RPC_STUB IImageObject_Dilate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Erode_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG ksize);


void __RPC_STUB IImageObject_Erode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_IsBlank_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG threshold,
    VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageObject_IsBlank_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_ChangeBrightnessContrast_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG brightness,
    LONG contrast);


void __RPC_STUB IImageObject_ChangeBrightnessContrast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_IsGrayScale_Proxy( 
    IImageObject __RPC_FAR * This,
    VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageObject_IsGrayScale_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_NumColors_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_NumColors_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_HBITMAP_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_HBITMAP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_FrameCount_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_FrameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Frame_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_SetFrame_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG frame);


void __RPC_STUB IImageObject_SetFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Size_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Handle_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ OLE_HANDLE __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Handle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_GetLastErrorText_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR __RPC_FAR *errorText);


void __RPC_STUB IImageObject_GetLastErrorText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Save_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName);


void __RPC_STUB IImageObject_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_Annotations_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ IAnnotationCollection __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_Annotations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromBuffer_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG pBuffer,
    LONG width,
    LONG height,
    LONG stride,
    LONG bpp);


void __RPC_STUB IImageObject_LoadFromBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_TooLight_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG threshold,
    VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageObject_TooLight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_TooDark_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG threshold,
    VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageObject_TooDark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObject_get_FileName_Proxy( 
    IImageObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IImageObject_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_IsBlankRect_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG threshold,
    LONG left,
    LONG top,
    LONG right,
    LONG bottom,
    VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageObject_IsBlankRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_Crop_Proxy( 
    IImageObject __RPC_FAR * This,
    LONG left,
    LONG top,
    LONG right,
    LONG bottom,
    IImageObject __RPC_FAR *__RPC_FAR *image);


void __RPC_STUB IImageObject_Crop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromFile2_Proxy( 
    IImageObject __RPC_FAR * This,
    BSTR fileName,
    LONG frame,
    BSTR password);


void __RPC_STUB IImageObject_LoadFromFile2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObject_LoadFromMemFile2_Proxy( 
    IImageObject __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
    LONG dataLen,
    LONG frame,
    BSTR password);


void __RPC_STUB IImageObject_LoadFromMemFile2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageObject_INTERFACE_DEFINED__ */


#ifndef __IImageObjectCollection_INTERFACE_DEFINED__
#define __IImageObjectCollection_INTERFACE_DEFINED__

/* interface IImageObjectCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IImageObjectCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDD8D93F-CFEE-4CD2-A82E-EA8CB26E409E")
    IImageObjectCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            LONG index,
            /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            IImageObject __RPC_FAR *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            IImageObject __RPC_FAR *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAt( 
            LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Insert( 
            LONG index,
            IImageObject __RPC_FAR *item) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveToFileTIFF( 
            BSTR fileName,
            TIFFCompressionEnum compression) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageObjectCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageObjectCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageObjectCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IImageObjectCollection __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IImageObjectCollection __RPC_FAR * This,
            LONG index,
            /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IImageObjectCollection __RPC_FAR * This,
            IImageObject __RPC_FAR *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IImageObjectCollection __RPC_FAR * This,
            IImageObject __RPC_FAR *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAt )( 
            IImageObjectCollection __RPC_FAR * This,
            LONG index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IImageObjectCollection __RPC_FAR * This,
            LONG index,
            IImageObject __RPC_FAR *item);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveToFileTIFF )( 
            IImageObjectCollection __RPC_FAR * This,
            BSTR fileName,
            TIFFCompressionEnum compression);
        
        END_INTERFACE
    } IImageObjectCollectionVtbl;

    interface IImageObjectCollection
    {
        CONST_VTBL struct IImageObjectCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageObjectCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageObjectCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageObjectCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageObjectCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImageObjectCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImageObjectCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImageObjectCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImageObjectCollection_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IImageObjectCollection_get_Item(This,index,pVal)	\
    (This)->lpVtbl -> get_Item(This,index,pVal)

#define IImageObjectCollection_Add(This,item)	\
    (This)->lpVtbl -> Add(This,item)

#define IImageObjectCollection_Remove(This,item)	\
    (This)->lpVtbl -> Remove(This,item)

#define IImageObjectCollection_RemoveAt(This,index)	\
    (This)->lpVtbl -> RemoveAt(This,index)

#define IImageObjectCollection_Insert(This,index,item)	\
    (This)->lpVtbl -> Insert(This,index,item)

#define IImageObjectCollection_SaveToFileTIFF(This,fileName,compression)	\
    (This)->lpVtbl -> SaveToFileTIFF(This,fileName,compression)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_get_Count_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IImageObjectCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_get_Item_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    LONG index,
    /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IImageObjectCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_Add_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    IImageObject __RPC_FAR *item);


void __RPC_STUB IImageObjectCollection_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_Remove_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    IImageObject __RPC_FAR *item);


void __RPC_STUB IImageObjectCollection_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_RemoveAt_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    LONG index);


void __RPC_STUB IImageObjectCollection_RemoveAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_Insert_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    LONG index,
    IImageObject __RPC_FAR *item);


void __RPC_STUB IImageObjectCollection_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageObjectCollection_SaveToFileTIFF_Proxy( 
    IImageObjectCollection __RPC_FAR * This,
    BSTR fileName,
    TIFFCompressionEnum compression);


void __RPC_STUB IImageObjectCollection_SaveToFileTIFF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageObjectCollection_INTERFACE_DEFINED__ */


#ifndef __IImageViewer_INTERFACE_DEFINED__
#define __IImageViewer_INTERFACE_DEFINED__

/* interface IImageViewer */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IImageViewer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77E33D44-5387-4EB9-AA11-2E193D63999C")
    IImageViewer : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Image( 
            /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Image( 
            /* [in] */ IImageObject __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Smooth( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Smooth( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AutoSizeMode( 
            /* [retval][out] */ AutoSizeModeEnum __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AutoSizeMode( 
            /* [in] */ AutoSizeModeEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ZoomFactor( 
            /* [retval][out] */ FLOAT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ZoomFactor( 
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowToolbar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowToolbar( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetPages( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomIn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomOut( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NoImageText( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NoImageText( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageViewerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageViewer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageViewer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImageViewer __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HWND )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Image )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Image )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ IImageObject __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Smooth )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Smooth )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoSizeMode )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ AutoSizeModeEnum __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoSizeMode )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ AutoSizeModeEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ZoomFactor )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ FLOAT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ZoomFactor )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ FLOAT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IImageViewer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowToolbar )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowToolbar )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPages )( 
            IImageViewer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZoomIn )( 
            IImageViewer __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZoomOut )( 
            IImageViewer __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NoImageText )( 
            IImageViewer __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NoImageText )( 
            IImageViewer __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IImageViewerVtbl;

    interface IImageViewer
    {
        CONST_VTBL struct IImageViewerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageViewer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageViewer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageViewer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageViewer_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImageViewer_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImageViewer_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImageViewer_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImageViewer_get_HWND(This,pHWND)	\
    (This)->lpVtbl -> get_HWND(This,pHWND)

#define IImageViewer_get_Image(This,pVal)	\
    (This)->lpVtbl -> get_Image(This,pVal)

#define IImageViewer_put_Image(This,newVal)	\
    (This)->lpVtbl -> put_Image(This,newVal)

#define IImageViewer_get_Smooth(This,pVal)	\
    (This)->lpVtbl -> get_Smooth(This,pVal)

#define IImageViewer_put_Smooth(This,newVal)	\
    (This)->lpVtbl -> put_Smooth(This,newVal)

#define IImageViewer_get_AutoSizeMode(This,pVal)	\
    (This)->lpVtbl -> get_AutoSizeMode(This,pVal)

#define IImageViewer_put_AutoSizeMode(This,newVal)	\
    (This)->lpVtbl -> put_AutoSizeMode(This,newVal)

#define IImageViewer_get_ZoomFactor(This,pVal)	\
    (This)->lpVtbl -> get_ZoomFactor(This,pVal)

#define IImageViewer_put_ZoomFactor(This,newVal)	\
    (This)->lpVtbl -> put_ZoomFactor(This,newVal)

#define IImageViewer_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IImageViewer_get_ShowToolbar(This,pVal)	\
    (This)->lpVtbl -> get_ShowToolbar(This,pVal)

#define IImageViewer_put_ShowToolbar(This,newVal)	\
    (This)->lpVtbl -> put_ShowToolbar(This,newVal)

#define IImageViewer_ResetPages(This)	\
    (This)->lpVtbl -> ResetPages(This)

#define IImageViewer_ZoomIn(This)	\
    (This)->lpVtbl -> ZoomIn(This)

#define IImageViewer_ZoomOut(This)	\
    (This)->lpVtbl -> ZoomOut(This)

#define IImageViewer_get_NoImageText(This,pVal)	\
    (This)->lpVtbl -> get_NoImageText(This,pVal)

#define IImageViewer_put_NoImageText(This,newVal)	\
    (This)->lpVtbl -> put_NoImageText(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_HWND_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND);


void __RPC_STUB IImageViewer_get_HWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_Image_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ IImageObject __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_Image_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ IImageObject __RPC_FAR *newVal);


void __RPC_STUB IImageViewer_put_Image_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_Smooth_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_Smooth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_Smooth_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IImageViewer_put_Smooth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_AutoSizeMode_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ AutoSizeModeEnum __RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_AutoSizeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_AutoSizeMode_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ AutoSizeModeEnum newVal);


void __RPC_STUB IImageViewer_put_AutoSizeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_ZoomFactor_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ FLOAT __RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_ZoomFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_ZoomFactor_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ FLOAT newVal);


void __RPC_STUB IImageViewer_put_ZoomFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageViewer_Refresh_Proxy( 
    IImageViewer __RPC_FAR * This);


void __RPC_STUB IImageViewer_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_ShowToolbar_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_ShowToolbar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_ShowToolbar_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IImageViewer_put_ShowToolbar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageViewer_ResetPages_Proxy( 
    IImageViewer __RPC_FAR * This);


void __RPC_STUB IImageViewer_ResetPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageViewer_ZoomIn_Proxy( 
    IImageViewer __RPC_FAR * This);


void __RPC_STUB IImageViewer_ZoomIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImageViewer_ZoomOut_Proxy( 
    IImageViewer __RPC_FAR * This);


void __RPC_STUB IImageViewer_ZoomOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImageViewer_get_NoImageText_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IImageViewer_get_NoImageText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImageViewer_put_NoImageText_Proxy( 
    IImageViewer __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IImageViewer_put_NoImageText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageViewer_INTERFACE_DEFINED__ */


#ifndef __IAnnotationLine_INTERFACE_DEFINED__
#define __IAnnotationLine_INTERFACE_DEFINED__

/* interface IAnnotationLine */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAnnotationLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC822C0B-1801-40CF-BC4D-D298C48F65C8")
    IAnnotationLine : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_x1( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_x1( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_y1( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_y1( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_x2( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_x2( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_y2( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_y2( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Frame( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Frame( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnnotationLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAnnotationLine __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAnnotationLine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAnnotationLine __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x1 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x1 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y1 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y1 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_x2 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_x2 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_y2 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_y2 )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Frame )( 
            IAnnotationLine __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Frame )( 
            IAnnotationLine __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IAnnotationLineVtbl;

    interface IAnnotationLine
    {
        CONST_VTBL struct IAnnotationLineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnnotationLine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnnotationLine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnnotationLine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnnotationLine_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnnotationLine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnnotationLine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnnotationLine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnnotationLine_get_x1(This,pVal)	\
    (This)->lpVtbl -> get_x1(This,pVal)

#define IAnnotationLine_put_x1(This,newVal)	\
    (This)->lpVtbl -> put_x1(This,newVal)

#define IAnnotationLine_get_y1(This,pVal)	\
    (This)->lpVtbl -> get_y1(This,pVal)

#define IAnnotationLine_put_y1(This,newVal)	\
    (This)->lpVtbl -> put_y1(This,newVal)

#define IAnnotationLine_get_x2(This,pVal)	\
    (This)->lpVtbl -> get_x2(This,pVal)

#define IAnnotationLine_put_x2(This,newVal)	\
    (This)->lpVtbl -> put_x2(This,newVal)

#define IAnnotationLine_get_y2(This,pVal)	\
    (This)->lpVtbl -> get_y2(This,pVal)

#define IAnnotationLine_put_y2(This,newVal)	\
    (This)->lpVtbl -> put_y2(This,newVal)

#define IAnnotationLine_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IAnnotationLine_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IAnnotationLine_get_Frame(This,pVal)	\
    (This)->lpVtbl -> get_Frame(This,pVal)

#define IAnnotationLine_put_Frame(This,newVal)	\
    (This)->lpVtbl -> put_Frame(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_x1_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_x1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_x1_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationLine_put_x1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_y1_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_y1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_y1_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationLine_put_y1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_x2_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_x2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_x2_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationLine_put_x2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_y2_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_y2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_y2_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationLine_put_y2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_Color_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_Color_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IAnnotationLine_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_get_Frame_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationLine_get_Frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationLine_put_Frame_Proxy( 
    IAnnotationLine __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationLine_put_Frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnnotationLine_INTERFACE_DEFINED__ */


#ifndef __IAnnotationRectangle_INTERFACE_DEFINED__
#define __IAnnotationRectangle_INTERFACE_DEFINED__

/* interface IAnnotationRectangle */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAnnotationRectangle;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1BEFB84E-E7F1-42AE-9A5B-296CEEC1843C")
    IAnnotationRectangle : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Right( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bottom( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Color( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Color( 
            /* [in] */ OLE_COLOR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Frame( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Frame( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnnotationRectangleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAnnotationRectangle __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAnnotationRectangle __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Right )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Right )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bottom )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Bottom )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Color )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Color )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ OLE_COLOR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Frame )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Frame )( 
            IAnnotationRectangle __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } IAnnotationRectangleVtbl;

    interface IAnnotationRectangle
    {
        CONST_VTBL struct IAnnotationRectangleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAnnotationRectangle_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnnotationRectangle_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnnotationRectangle_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnnotationRectangle_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAnnotationRectangle_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAnnotationRectangle_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAnnotationRectangle_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAnnotationRectangle_get_Left(This,pVal)	\
    (This)->lpVtbl -> get_Left(This,pVal)

#define IAnnotationRectangle_put_Left(This,newVal)	\
    (This)->lpVtbl -> put_Left(This,newVal)

#define IAnnotationRectangle_get_Top(This,pVal)	\
    (This)->lpVtbl -> get_Top(This,pVal)

#define IAnnotationRectangle_put_Top(This,newVal)	\
    (This)->lpVtbl -> put_Top(This,newVal)

#define IAnnotationRectangle_get_Right(This,pVal)	\
    (This)->lpVtbl -> get_Right(This,pVal)

#define IAnnotationRectangle_put_Right(This,newVal)	\
    (This)->lpVtbl -> put_Right(This,newVal)

#define IAnnotationRectangle_get_Bottom(This,pVal)	\
    (This)->lpVtbl -> get_Bottom(This,pVal)

#define IAnnotationRectangle_put_Bottom(This,newVal)	\
    (This)->lpVtbl -> put_Bottom(This,newVal)

#define IAnnotationRectangle_get_Color(This,pVal)	\
    (This)->lpVtbl -> get_Color(This,pVal)

#define IAnnotationRectangle_put_Color(This,newVal)	\
    (This)->lpVtbl -> put_Color(This,newVal)

#define IAnnotationRectangle_get_Frame(This,pVal)	\
    (This)->lpVtbl -> get_Frame(This,pVal)

#define IAnnotationRectangle_put_Frame(This,newVal)	\
    (This)->lpVtbl -> put_Frame(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Left_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Left_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationRectangle_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Top_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Top_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationRectangle_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Right_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Right_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationRectangle_put_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Bottom_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Bottom_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationRectangle_put_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Color_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Color_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ OLE_COLOR newVal);


void __RPC_STUB IAnnotationRectangle_put_Color_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_get_Frame_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB IAnnotationRectangle_get_Frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAnnotationRectangle_put_Frame_Proxy( 
    IAnnotationRectangle __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IAnnotationRectangle_put_Frame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnnotationRectangle_INTERFACE_DEFINED__ */


#ifndef __ITIFFUtils_INTERFACE_DEFINED__
#define __ITIFFUtils_INTERFACE_DEFINED__

/* interface ITIFFUtils */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITIFFUtils;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("66E408AF-3D0F-41A8-BA4E-0EEDE82ACE94")
    ITIFFUtils : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitByPage( 
            BSTR sourceFileName,
            LONG pageNumber,
            BSTR destFileName1,
            BSTR destFileName2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitByPages( 
            BSTR sourceFileName,
            BSTR nameTemplate,
            BSTR pageSequenceStr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitToPortions( 
            BSTR sourceFileName,
            BSTR nameTemplate,
            LONG portionSize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            BSTR fileName1,
            BSTR fileName2,
            BSTR outputFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePage( 
            BSTR fileName,
            LONG pageNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitByPageBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
            LONG pageNumber,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MergeBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
            SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePageBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG pageNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITIFFUtilsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITIFFUtils __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITIFFUtils __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITIFFUtils __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITIFFUtils __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITIFFUtils __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITIFFUtils __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITIFFUtils __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitByPage )( 
            ITIFFUtils __RPC_FAR * This,
            BSTR sourceFileName,
            LONG pageNumber,
            BSTR destFileName1,
            BSTR destFileName2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitByPages )( 
            ITIFFUtils __RPC_FAR * This,
            BSTR sourceFileName,
            BSTR nameTemplate,
            BSTR pageSequenceStr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitToPortions )( 
            ITIFFUtils __RPC_FAR * This,
            BSTR sourceFileName,
            BSTR nameTemplate,
            LONG portionSize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Merge )( 
            ITIFFUtils __RPC_FAR * This,
            BSTR fileName1,
            BSTR fileName2,
            BSTR outputFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletePage )( 
            ITIFFUtils __RPC_FAR * This,
            BSTR fileName,
            LONG pageNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitByPageBuffer )( 
            ITIFFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
            LONG pageNumber,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MergeBuffer )( 
            ITIFFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
            SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletePageBuffer )( 
            ITIFFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG pageNumber);
        
        END_INTERFACE
    } ITIFFUtilsVtbl;

    interface ITIFFUtils
    {
        CONST_VTBL struct ITIFFUtilsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITIFFUtils_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITIFFUtils_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITIFFUtils_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITIFFUtils_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITIFFUtils_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITIFFUtils_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITIFFUtils_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITIFFUtils_SplitByPage(This,sourceFileName,pageNumber,destFileName1,destFileName2)	\
    (This)->lpVtbl -> SplitByPage(This,sourceFileName,pageNumber,destFileName1,destFileName2)

#define ITIFFUtils_SplitByPages(This,sourceFileName,nameTemplate,pageSequenceStr)	\
    (This)->lpVtbl -> SplitByPages(This,sourceFileName,nameTemplate,pageSequenceStr)

#define ITIFFUtils_SplitToPortions(This,sourceFileName,nameTemplate,portionSize)	\
    (This)->lpVtbl -> SplitToPortions(This,sourceFileName,nameTemplate,portionSize)

#define ITIFFUtils_Merge(This,fileName1,fileName2,outputFileName)	\
    (This)->lpVtbl -> Merge(This,fileName1,fileName2,outputFileName)

#define ITIFFUtils_DeletePage(This,fileName,pageNumber)	\
    (This)->lpVtbl -> DeletePage(This,fileName,pageNumber)

#define ITIFFUtils_SplitByPageBuffer(This,sourceFileData,pageNumber,destFileData1,destFileData2)	\
    (This)->lpVtbl -> SplitByPageBuffer(This,sourceFileData,pageNumber,destFileData1,destFileData2)

#define ITIFFUtils_MergeBuffer(This,fileData1,fileData2,outputFileData)	\
    (This)->lpVtbl -> MergeBuffer(This,fileData1,fileData2,outputFileData)

#define ITIFFUtils_DeletePageBuffer(This,fileData,pageNumber)	\
    (This)->lpVtbl -> DeletePageBuffer(This,fileData,pageNumber)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_SplitByPage_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    BSTR sourceFileName,
    LONG pageNumber,
    BSTR destFileName1,
    BSTR destFileName2);


void __RPC_STUB ITIFFUtils_SplitByPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_SplitByPages_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    BSTR sourceFileName,
    BSTR nameTemplate,
    BSTR pageSequenceStr);


void __RPC_STUB ITIFFUtils_SplitByPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_SplitToPortions_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    BSTR sourceFileName,
    BSTR nameTemplate,
    LONG portionSize);


void __RPC_STUB ITIFFUtils_SplitToPortions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_Merge_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    BSTR fileName1,
    BSTR fileName2,
    BSTR outputFileName);


void __RPC_STUB ITIFFUtils_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_DeletePage_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    BSTR fileName,
    LONG pageNumber);


void __RPC_STUB ITIFFUtils_DeletePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_SplitByPageBuffer_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
    LONG pageNumber,
    SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
    SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2);


void __RPC_STUB ITIFFUtils_SplitByPageBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_MergeBuffer_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
    SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData);


void __RPC_STUB ITIFFUtils_MergeBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITIFFUtils_DeletePageBuffer_Proxy( 
    ITIFFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
    LONG pageNumber);


void __RPC_STUB ITIFFUtils_DeletePageBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITIFFUtils_INTERFACE_DEFINED__ */


#ifndef __ITwain_INTERFACE_DEFINED__
#define __ITwain_INTERFACE_DEFINED__

/* interface ITwain */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ITwain;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("502F44F6-FADA-42AD-8E94-58DBC0B45A30")
    ITwain : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Acquire( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceCount( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeviceName( 
            LONG index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentDeviceName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentDeviceName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentDeviceIndex( 
            /* [retval][out] */ LONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentDeviceIndex( 
            /* [in] */ LONG newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITwainVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITwain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITwain __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITwain __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITwain __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITwain __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITwain __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITwain __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HWND )( 
            ITwain __RPC_FAR * This,
            /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Acquire )( 
            ITwain __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceCount )( 
            ITwain __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeviceName )( 
            ITwain __RPC_FAR * This,
            LONG index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentDeviceName )( 
            ITwain __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentDeviceName )( 
            ITwain __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentDeviceIndex )( 
            ITwain __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentDeviceIndex )( 
            ITwain __RPC_FAR * This,
            /* [in] */ LONG newVal);
        
        END_INTERFACE
    } ITwainVtbl;

    interface ITwain
    {
        CONST_VTBL struct ITwainVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITwain_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITwain_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITwain_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITwain_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITwain_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITwain_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITwain_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITwain_get_HWND(This,pHWND)	\
    (This)->lpVtbl -> get_HWND(This,pHWND)

#define ITwain_Acquire(This)	\
    (This)->lpVtbl -> Acquire(This)

#define ITwain_get_DeviceCount(This,pVal)	\
    (This)->lpVtbl -> get_DeviceCount(This,pVal)

#define ITwain_get_DeviceName(This,index,pVal)	\
    (This)->lpVtbl -> get_DeviceName(This,index,pVal)

#define ITwain_get_CurrentDeviceName(This,pVal)	\
    (This)->lpVtbl -> get_CurrentDeviceName(This,pVal)

#define ITwain_put_CurrentDeviceName(This,newVal)	\
    (This)->lpVtbl -> put_CurrentDeviceName(This,newVal)

#define ITwain_get_CurrentDeviceIndex(This,pVal)	\
    (This)->lpVtbl -> get_CurrentDeviceIndex(This,pVal)

#define ITwain_put_CurrentDeviceIndex(This,newVal)	\
    (This)->lpVtbl -> put_CurrentDeviceIndex(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE ITwain_get_HWND_Proxy( 
    ITwain __RPC_FAR * This,
    /* [retval][out] */ LONG_PTR __RPC_FAR *pHWND);


void __RPC_STUB ITwain_get_HWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITwain_Acquire_Proxy( 
    ITwain __RPC_FAR * This);


void __RPC_STUB ITwain_Acquire_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITwain_get_DeviceCount_Proxy( 
    ITwain __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ITwain_get_DeviceCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITwain_get_DeviceName_Proxy( 
    ITwain __RPC_FAR * This,
    LONG index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITwain_get_DeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITwain_get_CurrentDeviceName_Proxy( 
    ITwain __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITwain_get_CurrentDeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITwain_put_CurrentDeviceName_Proxy( 
    ITwain __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITwain_put_CurrentDeviceName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITwain_get_CurrentDeviceIndex_Proxy( 
    ITwain __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pVal);


void __RPC_STUB ITwain_get_CurrentDeviceIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITwain_put_CurrentDeviceIndex_Proxy( 
    ITwain __RPC_FAR * This,
    /* [in] */ LONG newVal);


void __RPC_STUB ITwain_put_CurrentDeviceIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITwain_INTERFACE_DEFINED__ */


#ifndef __IPDFUtils_INTERFACE_DEFINED__
#define __IPDFUtils_INTERFACE_DEFINED__

/* interface IPDFUtils */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IPDFUtils;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8512900F-3D05-49E2-8BCC-0FBF1CE737CA")
    IPDFUtils : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitByPage( 
            BSTR sourceFileName,
            LONG pageNumber,
            BSTR destFileName1,
            BSTR destFileName2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SplitByPageBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
            LONG pageNumber,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Merge( 
            BSTR fileName1,
            BSTR fileName2,
            BSTR outputFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE MergeBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
            SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePage( 
            BSTR fileName,
            LONG pageNumber) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeletePageBuffer( 
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG pageNumber) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPDFUtilsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPDFUtils __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPDFUtils __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPDFUtils __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPDFUtils __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPDFUtils __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPDFUtils __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPDFUtils __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitByPage )( 
            IPDFUtils __RPC_FAR * This,
            BSTR sourceFileName,
            LONG pageNumber,
            BSTR destFileName1,
            BSTR destFileName2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitByPageBuffer )( 
            IPDFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
            LONG pageNumber,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Merge )( 
            IPDFUtils __RPC_FAR * This,
            BSTR fileName1,
            BSTR fileName2,
            BSTR outputFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MergeBuffer )( 
            IPDFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
            SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletePage )( 
            IPDFUtils __RPC_FAR * This,
            BSTR fileName,
            LONG pageNumber);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeletePageBuffer )( 
            IPDFUtils __RPC_FAR * This,
            SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
            LONG pageNumber);
        
        END_INTERFACE
    } IPDFUtilsVtbl;

    interface IPDFUtils
    {
        CONST_VTBL struct IPDFUtilsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPDFUtils_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPDFUtils_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPDFUtils_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPDFUtils_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPDFUtils_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPDFUtils_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPDFUtils_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPDFUtils_SplitByPage(This,sourceFileName,pageNumber,destFileName1,destFileName2)	\
    (This)->lpVtbl -> SplitByPage(This,sourceFileName,pageNumber,destFileName1,destFileName2)

#define IPDFUtils_SplitByPageBuffer(This,sourceFileData,pageNumber,destFileData1,destFileData2)	\
    (This)->lpVtbl -> SplitByPageBuffer(This,sourceFileData,pageNumber,destFileData1,destFileData2)

#define IPDFUtils_Merge(This,fileName1,fileName2,outputFileName)	\
    (This)->lpVtbl -> Merge(This,fileName1,fileName2,outputFileName)

#define IPDFUtils_MergeBuffer(This,fileData1,fileData2,outputFileData)	\
    (This)->lpVtbl -> MergeBuffer(This,fileData1,fileData2,outputFileData)

#define IPDFUtils_DeletePage(This,fileName,pageNumber)	\
    (This)->lpVtbl -> DeletePage(This,fileName,pageNumber)

#define IPDFUtils_DeletePageBuffer(This,fileData,pageNumber)	\
    (This)->lpVtbl -> DeletePageBuffer(This,fileData,pageNumber)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_SplitByPage_Proxy( 
    IPDFUtils __RPC_FAR * This,
    BSTR sourceFileName,
    LONG pageNumber,
    BSTR destFileName1,
    BSTR destFileName2);


void __RPC_STUB IPDFUtils_SplitByPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_SplitByPageBuffer_Proxy( 
    IPDFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *sourceFileData,
    LONG pageNumber,
    SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData1,
    SAFEARRAY __RPC_FAR * __RPC_FAR *destFileData2);


void __RPC_STUB IPDFUtils_SplitByPageBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_Merge_Proxy( 
    IPDFUtils __RPC_FAR * This,
    BSTR fileName1,
    BSTR fileName2,
    BSTR outputFileName);


void __RPC_STUB IPDFUtils_Merge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_MergeBuffer_Proxy( 
    IPDFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData1,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData2,
    SAFEARRAY __RPC_FAR * __RPC_FAR *outputFileData);


void __RPC_STUB IPDFUtils_MergeBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_DeletePage_Proxy( 
    IPDFUtils __RPC_FAR * This,
    BSTR fileName,
    LONG pageNumber);


void __RPC_STUB IPDFUtils_DeletePage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IPDFUtils_DeletePageBuffer_Proxy( 
    IPDFUtils __RPC_FAR * This,
    SAFEARRAY __RPC_FAR * __RPC_FAR *fileData,
    LONG pageNumber);


void __RPC_STUB IPDFUtils_DeletePageBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPDFUtils_INTERFACE_DEFINED__ */



#ifndef __DTKImageLib_LIBRARY_DEFINED__
#define __DTKImageLib_LIBRARY_DEFINED__

/* library DTKImageLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DTKImageLib;

EXTERN_C const CLSID CLSID_ImageObject;

#ifdef __cplusplus

class DECLSPEC_UUID("FB592E29-EF46-4BBA-A15C-8249ECD70AE9")
ImageObject;
#endif

EXTERN_C const CLSID CLSID_ImageObjectCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("2A4DB1F5-4B2E-4C88-A9A6-F84FAC49A73A")
ImageObjectCollection;
#endif

#ifndef ___IImageViewerEvents_DISPINTERFACE_DEFINED__
#define ___IImageViewerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IImageViewerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IImageViewerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5055B371-3B77-4BFB-BCA4-676A0C73892D")
    _IImageViewerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IImageViewerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IImageViewerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IImageViewerEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IImageViewerEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IImageViewerEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IImageViewerEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IImageViewerEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IImageViewerEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IImageViewerEventsVtbl;

    interface _IImageViewerEvents
    {
        CONST_VTBL struct _IImageViewerEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IImageViewerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IImageViewerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IImageViewerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IImageViewerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IImageViewerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IImageViewerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IImageViewerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IImageViewerEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ImageViewer;

#ifdef __cplusplus

class DECLSPEC_UUID("19DF1950-F74D-4834-BAC7-8972BD5A9EF4")
ImageViewer;
#endif

EXTERN_C const CLSID CLSID_AnnotationLine;

#ifdef __cplusplus

class DECLSPEC_UUID("94391FF5-748D-4544-96FF-BAA168CC631C")
AnnotationLine;
#endif

EXTERN_C const CLSID CLSID_AnnotationCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("1D0FA59D-A405-4DC5-93B4-1B3EFAEC6D4A")
AnnotationCollection;
#endif

EXTERN_C const CLSID CLSID_AnnotationRectangle;

#ifdef __cplusplus

class DECLSPEC_UUID("F10AF0E9-626C-4B13-A24B-B2A629E5C010")
AnnotationRectangle;
#endif

#ifndef ___ITIFFUtilsEvents_DISPINTERFACE_DEFINED__
#define ___ITIFFUtilsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITIFFUtilsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITIFFUtilsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("C6F7E45B-4095-4895-B96C-D3BDA8C1A6D4")
    _ITIFFUtilsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITIFFUtilsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ITIFFUtilsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ITIFFUtilsEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ITIFFUtilsEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ITIFFUtilsEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ITIFFUtilsEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ITIFFUtilsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ITIFFUtilsEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ITIFFUtilsEventsVtbl;

    interface _ITIFFUtilsEvents
    {
        CONST_VTBL struct _ITIFFUtilsEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITIFFUtilsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITIFFUtilsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITIFFUtilsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITIFFUtilsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITIFFUtilsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITIFFUtilsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITIFFUtilsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITIFFUtilsEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_TIFFUtils;

#ifdef __cplusplus

class DECLSPEC_UUID("85EE5D41-C409-429A-87AB-B2E3062B638C")
TIFFUtils;
#endif

#ifndef ___IPDFUtilsEvents_DISPINTERFACE_DEFINED__
#define ___IPDFUtilsEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IPDFUtilsEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IPDFUtilsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("D502E946-301C-4232-AD74-F301B107D00E")
    _IPDFUtilsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IPDFUtilsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IPDFUtilsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IPDFUtilsEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IPDFUtilsEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IPDFUtilsEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IPDFUtilsEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IPDFUtilsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IPDFUtilsEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IPDFUtilsEventsVtbl;

    interface _IPDFUtilsEvents
    {
        CONST_VTBL struct _IPDFUtilsEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IPDFUtilsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IPDFUtilsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IPDFUtilsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IPDFUtilsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IPDFUtilsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IPDFUtilsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IPDFUtilsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IPDFUtilsEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PDFUtils;

#ifdef __cplusplus

class DECLSPEC_UUID("20500A16-DCFE-495D-B457-D7DD2DCF6A17")
PDFUtils;
#endif

#ifndef ___ITwainEvents_DISPINTERFACE_DEFINED__
#define ___ITwainEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITwainEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__ITwainEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("6098AD6D-1A23-49B5-AACC-28AE1929DCAA")
    _ITwainEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITwainEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ITwainEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ITwainEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ITwainEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ITwainEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ITwainEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ITwainEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ITwainEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ITwainEventsVtbl;

    interface _ITwainEvents
    {
        CONST_VTBL struct _ITwainEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITwainEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITwainEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITwainEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITwainEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITwainEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITwainEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITwainEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITwainEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Twain;

#ifdef __cplusplus

class DECLSPEC_UUID("E01EC6D2-86F6-4276-9AB3-8764729310C1")
Twain;
#endif
#endif /* __DTKImageLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



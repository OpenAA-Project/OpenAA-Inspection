

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Sep 21 13:02:35 2021
 */
/* Compiler settings for .\DTKBarReader.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __DTKBarReader_h__
#define __DTKBarReader_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IBarcode_FWD_DEFINED__
#define __IBarcode_FWD_DEFINED__
typedef interface IBarcode IBarcode;
#endif 	/* __IBarcode_FWD_DEFINED__ */


#ifndef __IBarcodeCollection_FWD_DEFINED__
#define __IBarcodeCollection_FWD_DEFINED__
typedef interface IBarcodeCollection IBarcodeCollection;
#endif 	/* __IBarcodeCollection_FWD_DEFINED__ */


#ifndef __ILicManager_FWD_DEFINED__
#define __ILicManager_FWD_DEFINED__
typedef interface ILicManager ILicManager;
#endif 	/* __ILicManager_FWD_DEFINED__ */


#ifndef __IBarcodeReader_FWD_DEFINED__
#define __IBarcodeReader_FWD_DEFINED__
typedef interface IBarcodeReader IBarcodeReader;
#endif 	/* __IBarcodeReader_FWD_DEFINED__ */


#ifndef ___IBarcodeReaderEvents_FWD_DEFINED__
#define ___IBarcodeReaderEvents_FWD_DEFINED__
typedef interface _IBarcodeReaderEvents _IBarcodeReaderEvents;
#endif 	/* ___IBarcodeReaderEvents_FWD_DEFINED__ */


#ifndef __BarcodeReader_FWD_DEFINED__
#define __BarcodeReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class BarcodeReader BarcodeReader;
#else
typedef struct BarcodeReader BarcodeReader;
#endif /* __cplusplus */

#endif 	/* __BarcodeReader_FWD_DEFINED__ */


#ifndef __Barcode_FWD_DEFINED__
#define __Barcode_FWD_DEFINED__

#ifdef __cplusplus
typedef class Barcode Barcode;
#else
typedef struct Barcode Barcode;
#endif /* __cplusplus */

#endif 	/* __Barcode_FWD_DEFINED__ */


#ifndef __BarcodeCollection_FWD_DEFINED__
#define __BarcodeCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class BarcodeCollection BarcodeCollection;
#else
typedef struct BarcodeCollection BarcodeCollection;
#endif /* __cplusplus */

#endif 	/* __BarcodeCollection_FWD_DEFINED__ */


#ifndef __LicManager_FWD_DEFINED__
#define __LicManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class LicManager LicManager;
#else
typedef struct LicManager LicManager;
#endif /* __cplusplus */

#endif 	/* __LicManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_DTKBarReader_0000_0000 */
/* [local] */ 

typedef /* [public][v1_enum] */ 
enum BarcodeOrientationEnum
    {	BO_Unknown	= 0,
	BO_LeftToRight	= 0x1,
	BO_RightToLeft	= 0x2,
	BO_TopToBottom	= 0x4,
	BO_BottomToTop	= 0x8,
	BO_All	= 0xff
    } 	BarcodeOrientationEnum;

typedef /* [public][v1_enum] */ 
enum BarcodeTypeEnum
    {	BT_Unknown	= 0,
	BT_Code11	= 0x1,
	BT_Code39	= 0x2,
	BT_Code93	= 0x4,
	BT_Code128	= 0x8,
	BT_Codabar	= 0x10,
	BT_Inter2of5	= 0x20,
	BT_PatchCode	= 0x40,
	BT_EAN8	= 0x80,
	BT_UPCE	= 0x100,
	BT_EAN13	= 0x200,
	BT_UPCA	= 0x400,
	BT_Plus2	= 0x800,
	BT_Plus5	= 0x1000,
	BT_PDF417	= 0x2000,
	BT_DataMatrix	= 0x4000,
	BT_QRCode	= 0x8000,
	BT_Postnet	= 0x10000,
	BT_Planet	= 0x20000,
	BT_RM4SCC	= 0x40000,
	BT_AustraliaPost	= 0x80000,
	BT_IntelligentMail	= 0x100000,
	BT_Code39Extended	= 0x200000,
	BT_MicroQRCode	= 0x400000,
	BT_PharmaCode	= 0x800000,
	BT_UCC128	= 0x1000000,
	BT_RSS14	= 0x2000000,
	BT_RSSLimited	= 0x4000000,
	BT_RSSExpanded	= 0x8000000,
	BT_All	= 0xffffffff,
	BT_All_1D	= 0xfbf1fff,
	BT_All_2D	= 0x40e000
    } 	BarcodeTypeEnum;

typedef /* [public][v1_enum] */ 
enum QuietZoneSizeEnum
    {	QZ_ExtraSmall	= 0x1,
	QZ_Small	= 0x2,
	QZ_Normal	= 0x3,
	QZ_Large	= 0x4
    } 	QuietZoneSizeEnum;

typedef /* [public][v1_enum] */ 
enum PDFReadingTypeEnum
    {	PDF_Render	= 0x1,
	PDF_Images	= 0x2
    } 	PDFReadingTypeEnum;

typedef /* [public][v1_enum] */ 
enum ThresholdModeEnum
    {	TM_Automatic	= 0x1,
	TM_Fixed	= 0x2,
	TM_Multiple	= 0x3,
	TM_Adaptive	= 0x4
    } 	ThresholdModeEnum;



extern RPC_IF_HANDLE __MIDL_itf_DTKBarReader_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DTKBarReader_0000_0000_v0_0_s_ifspec;

#ifndef __IBarcode_INTERFACE_DEFINED__
#define __IBarcode_INTERFACE_DEFINED__

/* interface IBarcode */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBarcode;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C76302A7-E7D3-4173-905B-19DE2C74315D")
    IBarcode : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BarcodeTypeEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Orientation( 
            /* [retval][out] */ BarcodeOrientationEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Page( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataMatrix_Dim1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataMatrix_Dim2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DataMatrix_NumErrorsCorrected( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeData( 
            /* [retval][out] */ SAFEARRAY * *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeDataLen( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TypeString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeInfoString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OrientationString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Angle( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStartX1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStartY1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStartX2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderStartY2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderEndX1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderEndY1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderEndX2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BorderEndY2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Threshold( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Checksum( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dim1( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Dim2( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ErrorCorrectionLevel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumErrorsCorrected( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QRVersion( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RSSExpandedStacked( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBarcodeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBarcode * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBarcode * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBarcode * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBarcode * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBarcode * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBarcode * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBarcode * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeString )( 
            IBarcode * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Type )( 
            IBarcode * This,
            /* [retval][out] */ BarcodeTypeEnum *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Orientation )( 
            IBarcode * This,
            /* [retval][out] */ BarcodeOrientationEnum *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Right )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bottom )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Page )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataMatrix_Dim1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataMatrix_Dim2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DataMatrix_NumErrorsCorrected )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeData )( 
            IBarcode * This,
            /* [retval][out] */ SAFEARRAY * *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeDataLen )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TypeString )( 
            IBarcode * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeInfoString )( 
            IBarcode * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OrientationString )( 
            IBarcode * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Angle )( 
            IBarcode * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStartX1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStartY1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStartX2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderStartY2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderEndX1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderEndY1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderEndX2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BorderEndY2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Threshold )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Checksum )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dim1 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Dim2 )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ErrorCorrectionLevel )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_NumErrorsCorrected )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QRVersion )( 
            IBarcode * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RSSExpandedStacked )( 
            IBarcode * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } IBarcodeVtbl;

    interface IBarcode
    {
        CONST_VTBL struct IBarcodeVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBarcode_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBarcode_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBarcode_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBarcode_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBarcode_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBarcode_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBarcode_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBarcode_get_BarcodeString(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeString(This,pVal) ) 

#define IBarcode_get_Type(This,pVal)	\
    ( (This)->lpVtbl -> get_Type(This,pVal) ) 

#define IBarcode_get_Orientation(This,pVal)	\
    ( (This)->lpVtbl -> get_Orientation(This,pVal) ) 

#define IBarcode_get_Left(This,pVal)	\
    ( (This)->lpVtbl -> get_Left(This,pVal) ) 

#define IBarcode_get_Top(This,pVal)	\
    ( (This)->lpVtbl -> get_Top(This,pVal) ) 

#define IBarcode_get_Right(This,pVal)	\
    ( (This)->lpVtbl -> get_Right(This,pVal) ) 

#define IBarcode_get_Bottom(This,pVal)	\
    ( (This)->lpVtbl -> get_Bottom(This,pVal) ) 

#define IBarcode_get_Page(This,pVal)	\
    ( (This)->lpVtbl -> get_Page(This,pVal) ) 

#define IBarcode_get_DataMatrix_Dim1(This,pVal)	\
    ( (This)->lpVtbl -> get_DataMatrix_Dim1(This,pVal) ) 

#define IBarcode_get_DataMatrix_Dim2(This,pVal)	\
    ( (This)->lpVtbl -> get_DataMatrix_Dim2(This,pVal) ) 

#define IBarcode_get_DataMatrix_NumErrorsCorrected(This,pVal)	\
    ( (This)->lpVtbl -> get_DataMatrix_NumErrorsCorrected(This,pVal) ) 

#define IBarcode_get_BarcodeData(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeData(This,pVal) ) 

#define IBarcode_get_BarcodeDataLen(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeDataLen(This,pVal) ) 

#define IBarcode_get_TypeString(This,pVal)	\
    ( (This)->lpVtbl -> get_TypeString(This,pVal) ) 

#define IBarcode_get_BarcodeInfoString(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeInfoString(This,pVal) ) 

#define IBarcode_get_OrientationString(This,pVal)	\
    ( (This)->lpVtbl -> get_OrientationString(This,pVal) ) 

#define IBarcode_get_Angle(This,pVal)	\
    ( (This)->lpVtbl -> get_Angle(This,pVal) ) 

#define IBarcode_get_BorderStartX1(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderStartX1(This,pVal) ) 

#define IBarcode_get_BorderStartY1(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderStartY1(This,pVal) ) 

#define IBarcode_get_BorderStartX2(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderStartX2(This,pVal) ) 

#define IBarcode_get_BorderStartY2(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderStartY2(This,pVal) ) 

#define IBarcode_get_BorderEndX1(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderEndX1(This,pVal) ) 

#define IBarcode_get_BorderEndY1(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderEndY1(This,pVal) ) 

#define IBarcode_get_BorderEndX2(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderEndX2(This,pVal) ) 

#define IBarcode_get_BorderEndY2(This,pVal)	\
    ( (This)->lpVtbl -> get_BorderEndY2(This,pVal) ) 

#define IBarcode_get_Threshold(This,pVal)	\
    ( (This)->lpVtbl -> get_Threshold(This,pVal) ) 

#define IBarcode_get_Checksum(This,pVal)	\
    ( (This)->lpVtbl -> get_Checksum(This,pVal) ) 

#define IBarcode_get_Dim1(This,pVal)	\
    ( (This)->lpVtbl -> get_Dim1(This,pVal) ) 

#define IBarcode_get_Dim2(This,pVal)	\
    ( (This)->lpVtbl -> get_Dim2(This,pVal) ) 

#define IBarcode_get_ErrorCorrectionLevel(This,pVal)	\
    ( (This)->lpVtbl -> get_ErrorCorrectionLevel(This,pVal) ) 

#define IBarcode_get_NumErrorsCorrected(This,pVal)	\
    ( (This)->lpVtbl -> get_NumErrorsCorrected(This,pVal) ) 

#define IBarcode_get_QRVersion(This,pVal)	\
    ( (This)->lpVtbl -> get_QRVersion(This,pVal) ) 

#define IBarcode_get_RSSExpandedStacked(This,pVal)	\
    ( (This)->lpVtbl -> get_RSSExpandedStacked(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBarcode_INTERFACE_DEFINED__ */


#ifndef __IBarcodeCollection_INTERFACE_DEFINED__
#define __IBarcodeCollection_INTERFACE_DEFINED__

/* interface IBarcodeCollection */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBarcodeCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2AACECAE-390B-4BCD-B29D-C09A7531A733")
    IBarcodeCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ LONG index,
            /* [retval][out] */ IBarcode **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBarcodeCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBarcodeCollection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBarcodeCollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBarcodeCollection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBarcodeCollection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBarcodeCollection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBarcodeCollection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBarcodeCollection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IBarcodeCollection * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IBarcodeCollection * This,
            /* [in] */ LONG index,
            /* [retval][out] */ IBarcode **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Clear )( 
            IBarcodeCollection * This);
        
        END_INTERFACE
    } IBarcodeCollectionVtbl;

    interface IBarcodeCollection
    {
        CONST_VTBL struct IBarcodeCollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBarcodeCollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBarcodeCollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBarcodeCollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBarcodeCollection_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBarcodeCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBarcodeCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBarcodeCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBarcodeCollection_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IBarcodeCollection_get_Item(This,index,pVal)	\
    ( (This)->lpVtbl -> get_Item(This,index,pVal) ) 

#define IBarcodeCollection_Clear(This)	\
    ( (This)->lpVtbl -> Clear(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBarcodeCollection_INTERFACE_DEFINED__ */


#ifndef __ILicManager_INTERFACE_DEFINED__
#define __ILicManager_INTERFACE_DEFINED__

/* interface ILicManager */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILicManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3B8A43CD-B3AA-460D-8828-600F8D9300A1")
    ILicManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddLicenseKey( 
            BSTR licenseKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateLicenseOnline( 
            BSTR LicenseKey,
            BSTR *errorMessage) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetActivationLink( 
            BSTR licenseKey,
            BSTR *ActivationLink) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetActivationCode( 
            BSTR ActivationCode) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsLicensed( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILicManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILicManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILicManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILicManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILicManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILicManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILicManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILicManager * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddLicenseKey )( 
            ILicManager * This,
            BSTR licenseKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ActivateLicenseOnline )( 
            ILicManager * This,
            BSTR LicenseKey,
            BSTR *errorMessage);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetActivationLink )( 
            ILicManager * This,
            BSTR licenseKey,
            BSTR *ActivationLink);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetActivationCode )( 
            ILicManager * This,
            BSTR ActivationCode);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsLicensed )( 
            ILicManager * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        END_INTERFACE
    } ILicManagerVtbl;

    interface ILicManager
    {
        CONST_VTBL struct ILicManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILicManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILicManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILicManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILicManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILicManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILicManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILicManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILicManager_AddLicenseKey(This,licenseKey)	\
    ( (This)->lpVtbl -> AddLicenseKey(This,licenseKey) ) 

#define ILicManager_ActivateLicenseOnline(This,LicenseKey,errorMessage)	\
    ( (This)->lpVtbl -> ActivateLicenseOnline(This,LicenseKey,errorMessage) ) 

#define ILicManager_GetActivationLink(This,licenseKey,ActivationLink)	\
    ( (This)->lpVtbl -> GetActivationLink(This,licenseKey,ActivationLink) ) 

#define ILicManager_SetActivationCode(This,ActivationCode)	\
    ( (This)->lpVtbl -> SetActivationCode(This,ActivationCode) ) 

#define ILicManager_get_IsLicensed(This,pVal)	\
    ( (This)->lpVtbl -> get_IsLicensed(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILicManager_INTERFACE_DEFINED__ */


#ifndef __IBarcodeReader_INTERFACE_DEFINED__
#define __IBarcodeReader_INTERFACE_DEFINED__

/* interface IBarcodeReader */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IBarcodeReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B391A095-0FD0-4982-A203-C3D59E31277D")
    IBarcodeReader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromFile( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromMemFile( 
            SAFEARRAY * *fileData,
            LONG dataLen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromBitmap( 
            LONG hBitmap,
            LONG hPalette) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromDIB( 
            LONG hDIB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromImage( 
            IUnknown *imageObject) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeTypes( 
            /* [retval][out] */ BarcodeTypeEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BarcodeTypes( 
            /* [in] */ BarcodeTypeEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScanInterval( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScanInterval( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Threshold( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Threshold( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ThresholdStep( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ThresholdStep( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ThresholdCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ThresholdCount( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodesToRead( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BarcodesToRead( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QuietZoneSize( 
            /* [retval][out] */ QuietZoneSizeEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QuietZoneSize( 
            /* [in] */ QuietZoneSizeEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BarcodeOrientation( 
            /* [retval][out] */ BarcodeOrientationEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BarcodeOrientation( 
            /* [in] */ BarcodeOrientationEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScanPage( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScanPage( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetScanRectangle( 
            LONG left,
            LONG top,
            LONG right,
            LONG bottom) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Code11Checksum( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Code11Checksum( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Code39Checksum( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Code39Checksum( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_I2of5Checksum( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_I2of5Checksum( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Code93Checksum( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Code93Checksum( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageDespeckle( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageDespeckle( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageDilate( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageDilate( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageErode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageErode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageInvert( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageInvert( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PDFReadingType( 
            /* [retval][out] */ PDFReadingTypeEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PDFReadingType( 
            /* [in] */ PDFReadingTypeEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LicenseManager( 
            /* [retval][out] */ ILicManager **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLastErrorText( 
            BSTR *errorText) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ThresholdMode( 
            /* [retval][out] */ ThresholdModeEnum *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ThresholdMode( 
            /* [in] */ ThresholdModeEnum newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PDFRenderDPI( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PDFRenderDPI( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ImageSharp( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ImageSharp( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Barcodes( 
            /* [retval][out] */ IBarcodeCollection **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromBuffer( 
            LONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetExtraParam( 
            BSTR paramName,
            LONG paramValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RecognitionTimeout( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RecognitionTimeout( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetExtraParam( 
            /* [in] */ BSTR paramName,
            /* [out] */ LONG *paramValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ BSTR *sVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConvertUPCEtoUPCA( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConvertUPCEtoUPCA( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PDFPassword( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PDFPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_QRCodeRequiredECCLevel( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_QRCodeRequiredECCLevel( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Code39NoStartStop( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Code39NoStartStop( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromBuffer2( 
            LONGLONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadFromBitmap2( 
            LONGLONG hBitmap,
            LONGLONG hPalette) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBarcodeReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBarcodeReader * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBarcodeReader * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBarcodeReader * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IBarcodeReader * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IBarcodeReader * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IBarcodeReader * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IBarcodeReader * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromFile )( 
            IBarcodeReader * This,
            BSTR fileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromMemFile )( 
            IBarcodeReader * This,
            SAFEARRAY * *fileData,
            LONG dataLen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromBitmap )( 
            IBarcodeReader * This,
            LONG hBitmap,
            LONG hPalette);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromDIB )( 
            IBarcodeReader * This,
            LONG hDIB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromImage )( 
            IBarcodeReader * This,
            IUnknown *imageObject);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeTypes )( 
            IBarcodeReader * This,
            /* [retval][out] */ BarcodeTypeEnum *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BarcodeTypes )( 
            IBarcodeReader * This,
            /* [in] */ BarcodeTypeEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScanInterval )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScanInterval )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Threshold )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Threshold )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThresholdStep )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ThresholdStep )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThresholdCount )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ThresholdCount )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodesToRead )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BarcodesToRead )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QuietZoneSize )( 
            IBarcodeReader * This,
            /* [retval][out] */ QuietZoneSizeEnum *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QuietZoneSize )( 
            IBarcodeReader * This,
            /* [in] */ QuietZoneSizeEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BarcodeOrientation )( 
            IBarcodeReader * This,
            /* [retval][out] */ BarcodeOrientationEnum *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BarcodeOrientation )( 
            IBarcodeReader * This,
            /* [in] */ BarcodeOrientationEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ScanPage )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ScanPage )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetScanRectangle )( 
            IBarcodeReader * This,
            LONG left,
            LONG top,
            LONG right,
            LONG bottom);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code11Checksum )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code11Checksum )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code39Checksum )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code39Checksum )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_I2of5Checksum )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_I2of5Checksum )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code93Checksum )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code93Checksum )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageDespeckle )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageDespeckle )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageDilate )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageDilate )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageErode )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageErode )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageInvert )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageInvert )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PDFReadingType )( 
            IBarcodeReader * This,
            /* [retval][out] */ PDFReadingTypeEnum *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PDFReadingType )( 
            IBarcodeReader * This,
            /* [in] */ PDFReadingTypeEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_LicenseManager )( 
            IBarcodeReader * This,
            /* [retval][out] */ ILicManager **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetLastErrorText )( 
            IBarcodeReader * This,
            BSTR *errorText);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ThresholdMode )( 
            IBarcodeReader * This,
            /* [retval][out] */ ThresholdModeEnum *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ThresholdMode )( 
            IBarcodeReader * This,
            /* [in] */ ThresholdModeEnum newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PDFRenderDPI )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PDFRenderDPI )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ImageSharp )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ImageSharp )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Barcodes )( 
            IBarcodeReader * This,
            /* [retval][out] */ IBarcodeCollection **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromBuffer )( 
            IBarcodeReader * This,
            LONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetExtraParam )( 
            IBarcodeReader * This,
            BSTR paramName,
            LONG paramValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_RecognitionTimeout )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_RecognitionTimeout )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetExtraParam )( 
            IBarcodeReader * This,
            /* [in] */ BSTR paramName,
            /* [out] */ LONG *paramValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IBarcodeReader * This,
            /* [retval][out] */ BSTR *sVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConvertUPCEtoUPCA )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConvertUPCEtoUPCA )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PDFPassword )( 
            IBarcodeReader * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PDFPassword )( 
            IBarcodeReader * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_QRCodeRequiredECCLevel )( 
            IBarcodeReader * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_QRCodeRequiredECCLevel )( 
            IBarcodeReader * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Code39NoStartStop )( 
            IBarcodeReader * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Code39NoStartStop )( 
            IBarcodeReader * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromBuffer2 )( 
            IBarcodeReader * This,
            LONGLONG pBuffer,
            LONG width,
            LONG height,
            LONG stride,
            LONG bpp);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadFromBitmap2 )( 
            IBarcodeReader * This,
            LONGLONG hBitmap,
            LONGLONG hPalette);
        
        END_INTERFACE
    } IBarcodeReaderVtbl;

    interface IBarcodeReader
    {
        CONST_VTBL struct IBarcodeReaderVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBarcodeReader_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBarcodeReader_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBarcodeReader_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBarcodeReader_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IBarcodeReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IBarcodeReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IBarcodeReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IBarcodeReader_ReadFromFile(This,fileName)	\
    ( (This)->lpVtbl -> ReadFromFile(This,fileName) ) 

#define IBarcodeReader_ReadFromMemFile(This,fileData,dataLen)	\
    ( (This)->lpVtbl -> ReadFromMemFile(This,fileData,dataLen) ) 

#define IBarcodeReader_ReadFromBitmap(This,hBitmap,hPalette)	\
    ( (This)->lpVtbl -> ReadFromBitmap(This,hBitmap,hPalette) ) 

#define IBarcodeReader_ReadFromDIB(This,hDIB)	\
    ( (This)->lpVtbl -> ReadFromDIB(This,hDIB) ) 

#define IBarcodeReader_ReadFromImage(This,imageObject)	\
    ( (This)->lpVtbl -> ReadFromImage(This,imageObject) ) 

#define IBarcodeReader_get_BarcodeTypes(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeTypes(This,pVal) ) 

#define IBarcodeReader_put_BarcodeTypes(This,newVal)	\
    ( (This)->lpVtbl -> put_BarcodeTypes(This,newVal) ) 

#define IBarcodeReader_get_ScanInterval(This,pVal)	\
    ( (This)->lpVtbl -> get_ScanInterval(This,pVal) ) 

#define IBarcodeReader_put_ScanInterval(This,newVal)	\
    ( (This)->lpVtbl -> put_ScanInterval(This,newVal) ) 

#define IBarcodeReader_get_Threshold(This,pVal)	\
    ( (This)->lpVtbl -> get_Threshold(This,pVal) ) 

#define IBarcodeReader_put_Threshold(This,newVal)	\
    ( (This)->lpVtbl -> put_Threshold(This,newVal) ) 

#define IBarcodeReader_get_ThresholdStep(This,pVal)	\
    ( (This)->lpVtbl -> get_ThresholdStep(This,pVal) ) 

#define IBarcodeReader_put_ThresholdStep(This,newVal)	\
    ( (This)->lpVtbl -> put_ThresholdStep(This,newVal) ) 

#define IBarcodeReader_get_ThresholdCount(This,pVal)	\
    ( (This)->lpVtbl -> get_ThresholdCount(This,pVal) ) 

#define IBarcodeReader_put_ThresholdCount(This,newVal)	\
    ( (This)->lpVtbl -> put_ThresholdCount(This,newVal) ) 

#define IBarcodeReader_get_BarcodesToRead(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodesToRead(This,pVal) ) 

#define IBarcodeReader_put_BarcodesToRead(This,newVal)	\
    ( (This)->lpVtbl -> put_BarcodesToRead(This,newVal) ) 

#define IBarcodeReader_get_QuietZoneSize(This,pVal)	\
    ( (This)->lpVtbl -> get_QuietZoneSize(This,pVal) ) 

#define IBarcodeReader_put_QuietZoneSize(This,newVal)	\
    ( (This)->lpVtbl -> put_QuietZoneSize(This,newVal) ) 

#define IBarcodeReader_get_BarcodeOrientation(This,pVal)	\
    ( (This)->lpVtbl -> get_BarcodeOrientation(This,pVal) ) 

#define IBarcodeReader_put_BarcodeOrientation(This,newVal)	\
    ( (This)->lpVtbl -> put_BarcodeOrientation(This,newVal) ) 

#define IBarcodeReader_get_ScanPage(This,pVal)	\
    ( (This)->lpVtbl -> get_ScanPage(This,pVal) ) 

#define IBarcodeReader_put_ScanPage(This,newVal)	\
    ( (This)->lpVtbl -> put_ScanPage(This,newVal) ) 

#define IBarcodeReader_SetScanRectangle(This,left,top,right,bottom)	\
    ( (This)->lpVtbl -> SetScanRectangle(This,left,top,right,bottom) ) 

#define IBarcodeReader_get_Code11Checksum(This,pVal)	\
    ( (This)->lpVtbl -> get_Code11Checksum(This,pVal) ) 

#define IBarcodeReader_put_Code11Checksum(This,newVal)	\
    ( (This)->lpVtbl -> put_Code11Checksum(This,newVal) ) 

#define IBarcodeReader_get_Code39Checksum(This,pVal)	\
    ( (This)->lpVtbl -> get_Code39Checksum(This,pVal) ) 

#define IBarcodeReader_put_Code39Checksum(This,newVal)	\
    ( (This)->lpVtbl -> put_Code39Checksum(This,newVal) ) 

#define IBarcodeReader_get_I2of5Checksum(This,pVal)	\
    ( (This)->lpVtbl -> get_I2of5Checksum(This,pVal) ) 

#define IBarcodeReader_put_I2of5Checksum(This,newVal)	\
    ( (This)->lpVtbl -> put_I2of5Checksum(This,newVal) ) 

#define IBarcodeReader_get_Code93Checksum(This,pVal)	\
    ( (This)->lpVtbl -> get_Code93Checksum(This,pVal) ) 

#define IBarcodeReader_put_Code93Checksum(This,newVal)	\
    ( (This)->lpVtbl -> put_Code93Checksum(This,newVal) ) 

#define IBarcodeReader_get_ImageDespeckle(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageDespeckle(This,pVal) ) 

#define IBarcodeReader_put_ImageDespeckle(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageDespeckle(This,newVal) ) 

#define IBarcodeReader_get_ImageDilate(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageDilate(This,pVal) ) 

#define IBarcodeReader_put_ImageDilate(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageDilate(This,newVal) ) 

#define IBarcodeReader_get_ImageErode(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageErode(This,pVal) ) 

#define IBarcodeReader_put_ImageErode(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageErode(This,newVal) ) 

#define IBarcodeReader_get_ImageInvert(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageInvert(This,pVal) ) 

#define IBarcodeReader_put_ImageInvert(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageInvert(This,newVal) ) 

#define IBarcodeReader_get_PDFReadingType(This,pVal)	\
    ( (This)->lpVtbl -> get_PDFReadingType(This,pVal) ) 

#define IBarcodeReader_put_PDFReadingType(This,newVal)	\
    ( (This)->lpVtbl -> put_PDFReadingType(This,newVal) ) 

#define IBarcodeReader_get_LicenseManager(This,pVal)	\
    ( (This)->lpVtbl -> get_LicenseManager(This,pVal) ) 

#define IBarcodeReader_GetLastErrorText(This,errorText)	\
    ( (This)->lpVtbl -> GetLastErrorText(This,errorText) ) 

#define IBarcodeReader_get_ThresholdMode(This,pVal)	\
    ( (This)->lpVtbl -> get_ThresholdMode(This,pVal) ) 

#define IBarcodeReader_put_ThresholdMode(This,newVal)	\
    ( (This)->lpVtbl -> put_ThresholdMode(This,newVal) ) 

#define IBarcodeReader_get_PDFRenderDPI(This,pVal)	\
    ( (This)->lpVtbl -> get_PDFRenderDPI(This,pVal) ) 

#define IBarcodeReader_put_PDFRenderDPI(This,newVal)	\
    ( (This)->lpVtbl -> put_PDFRenderDPI(This,newVal) ) 

#define IBarcodeReader_get_ImageSharp(This,pVal)	\
    ( (This)->lpVtbl -> get_ImageSharp(This,pVal) ) 

#define IBarcodeReader_put_ImageSharp(This,newVal)	\
    ( (This)->lpVtbl -> put_ImageSharp(This,newVal) ) 

#define IBarcodeReader_get_Barcodes(This,pVal)	\
    ( (This)->lpVtbl -> get_Barcodes(This,pVal) ) 

#define IBarcodeReader_ReadFromBuffer(This,pBuffer,width,height,stride,bpp)	\
    ( (This)->lpVtbl -> ReadFromBuffer(This,pBuffer,width,height,stride,bpp) ) 

#define IBarcodeReader_SetExtraParam(This,paramName,paramValue)	\
    ( (This)->lpVtbl -> SetExtraParam(This,paramName,paramValue) ) 

#define IBarcodeReader_get_RecognitionTimeout(This,pVal)	\
    ( (This)->lpVtbl -> get_RecognitionTimeout(This,pVal) ) 

#define IBarcodeReader_put_RecognitionTimeout(This,newVal)	\
    ( (This)->lpVtbl -> put_RecognitionTimeout(This,newVal) ) 

#define IBarcodeReader_GetExtraParam(This,paramName,paramValue)	\
    ( (This)->lpVtbl -> GetExtraParam(This,paramName,paramValue) ) 

#define IBarcodeReader_get_Version(This,sVersion)	\
    ( (This)->lpVtbl -> get_Version(This,sVersion) ) 

#define IBarcodeReader_get_ConvertUPCEtoUPCA(This,pVal)	\
    ( (This)->lpVtbl -> get_ConvertUPCEtoUPCA(This,pVal) ) 

#define IBarcodeReader_put_ConvertUPCEtoUPCA(This,newVal)	\
    ( (This)->lpVtbl -> put_ConvertUPCEtoUPCA(This,newVal) ) 

#define IBarcodeReader_get_PDFPassword(This,pVal)	\
    ( (This)->lpVtbl -> get_PDFPassword(This,pVal) ) 

#define IBarcodeReader_put_PDFPassword(This,newVal)	\
    ( (This)->lpVtbl -> put_PDFPassword(This,newVal) ) 

#define IBarcodeReader_get_QRCodeRequiredECCLevel(This,pVal)	\
    ( (This)->lpVtbl -> get_QRCodeRequiredECCLevel(This,pVal) ) 

#define IBarcodeReader_put_QRCodeRequiredECCLevel(This,newVal)	\
    ( (This)->lpVtbl -> put_QRCodeRequiredECCLevel(This,newVal) ) 

#define IBarcodeReader_get_Code39NoStartStop(This,pVal)	\
    ( (This)->lpVtbl -> get_Code39NoStartStop(This,pVal) ) 

#define IBarcodeReader_put_Code39NoStartStop(This,newVal)	\
    ( (This)->lpVtbl -> put_Code39NoStartStop(This,newVal) ) 

#define IBarcodeReader_ReadFromBuffer2(This,pBuffer,width,height,stride,bpp)	\
    ( (This)->lpVtbl -> ReadFromBuffer2(This,pBuffer,width,height,stride,bpp) ) 

#define IBarcodeReader_ReadFromBitmap2(This,hBitmap,hPalette)	\
    ( (This)->lpVtbl -> ReadFromBitmap2(This,hBitmap,hPalette) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBarcodeReader_INTERFACE_DEFINED__ */



#ifndef __DTKBarReaderLib_LIBRARY_DEFINED__
#define __DTKBarReaderLib_LIBRARY_DEFINED__

/* library DTKBarReaderLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DTKBarReaderLib;

#ifndef ___IBarcodeReaderEvents_DISPINTERFACE_DEFINED__
#define ___IBarcodeReaderEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IBarcodeReaderEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IBarcodeReaderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("81825B19-76E7-4f41-AF45-3EB34991B510")
    _IBarcodeReaderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IBarcodeReaderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IBarcodeReaderEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IBarcodeReaderEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IBarcodeReaderEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IBarcodeReaderEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IBarcodeReaderEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IBarcodeReaderEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IBarcodeReaderEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IBarcodeReaderEventsVtbl;

    interface _IBarcodeReaderEvents
    {
        CONST_VTBL struct _IBarcodeReaderEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IBarcodeReaderEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IBarcodeReaderEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IBarcodeReaderEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IBarcodeReaderEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IBarcodeReaderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IBarcodeReaderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IBarcodeReaderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IBarcodeReaderEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_BarcodeReader;

#ifdef __cplusplus

class DECLSPEC_UUID("4EC4B50D-6CCE-4822-8041-A3C9530E2549")
BarcodeReader;
#endif

EXTERN_C const CLSID CLSID_Barcode;

#ifdef __cplusplus

class DECLSPEC_UUID("20C7881D-7BD9-48DB-B5EC-4C7F818ADBE4")
Barcode;
#endif

EXTERN_C const CLSID CLSID_BarcodeCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("D991D60A-959B-479D-B987-1A397E45D955")
BarcodeCollection;
#endif

EXTERN_C const CLSID CLSID_LicManager;

#ifdef __cplusplus

class DECLSPEC_UUID("64F9C23E-14E8-4D86-86AE-DC5A045AEC39")
LicManager;
#endif
#endif /* __DTKBarReaderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif



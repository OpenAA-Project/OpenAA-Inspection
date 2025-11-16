//#include "stdafx.h"
//#include "ipm8540.h"
//#include "screenformat.h"
#include	"RunLen.h"
//#include "resource.h"

// ====================================================================
// STATIC¡¦¡¦¡¦`
// ====================================================================
static	ULONG		g_ulRlOffset			= 0;				// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦FFSET
static	HANDLE	g_hRlOffset_Lst		= NULL;			// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦FFSETØ½ÄÊÝÄÞÙ
static	ULONG		*g_ulRlOffset_Lst	= NULL;			// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦FFSETØ½¡¦
static	ULONG		g_ulDestX					= 0;				// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u
static	ULONG		g_ulDestY					= 0;				// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u
static	ULONG		g_ulDestCnt				= 0;				// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦f¡¦¡¦

// ×ÝÚÝ¸Þ½ÃÞ°¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
BOOL		ConvertRL( DWORD dwRlBuff, ULONG ulRlSize, ULONG ulRlBuffSize, ULONG *pulRlOffset, DWORD dwImgBuff,
									ULONG ulImgSizeX, ULONG ulImgSizeY, ULONG *pulImgOffset, ULONG *pulDestX, ULONG *pulDestY,
									ULONG ulFrmNo, ULONG *pulRlCnt, BOOL fChk, BOOL *pfFrmEnd );


// ********************************************************************
// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦m¡¦¡¦
// ********************************************************************
BOOL	RL_Alloc( ULONG ulFrmCnt )
{
	BOOL	fStatus	= false;
//	CString	strMsg;
	// ¡¦¡¦¡¦m¡¦¡¦¡¦¡¦¡¦¡¦¡¦J¡¦¡¦
	RL_Free();

	//##################################################################################
	//                   ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦Ø½ÄÊÞ¯Ì§¡¦¡¦m¡¦¡¦
	//##################################################################################
	g_hRlOffset_Lst		= GlobalAlloc(GMEM_FIXED, sizeof(ULONG)*ulFrmCnt );
	if( !g_hRlOffset_Lst ){
		// "×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦¡¦m¡¦Û´×°"
//		strMsg.LoadString( IDS_ERR_RL_MEM_GET );
//		AfxMessageBox( strMsg );
		goto END;
	}
	g_ulRlOffset_Lst	= (ULONG*)GlobalLock( g_hRlOffset_Lst );
	memset( g_ulRlOffset_Lst, 0, sizeof(ULONG)*ulFrmCnt );
	fStatus	= TRUE;
END:
	return( fStatus );
}

// ********************************************************************
// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦J¡¦¡¦
// ********************************************************************
BOOL	RL_Free()
{
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦
	if( g_ulRlOffset_Lst )	GlobalUnlock( g_hRlOffset_Lst );
	g_ulRlOffset_Lst	= NULL;

	// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦
	if( g_hRlOffset_Lst )		GlobalFree( g_hRlOffset_Lst );
	g_hRlOffset_Lst		= NULL;

	return( TRUE );
}

// ********************************************************************
// ×ÝÚÝ¸Þ½ÃÞ°¡¦Ì¸Ø±
// ********************************************************************
void	RL_Clr()
{
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦
	g_ulRlOffset	= 0;
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u
	g_ulDestX			= 0;
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u
	g_ulDestY			= 0;
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦f¡¦¡¦
	g_ulDestCnt		= 0;
	// ×ÝÚÝ¸Þ¡¦¡¦¡¦FFSET
	g_ulRlOffset_Lst[0]	= 0;
}
/*
// ********************************************************************
// ÃÞ°À¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
//¡¦E¡¦¡¦¡¦]¡¦¡¦¡¦¡¦PÌÚ°Ñ¡¦¡¦¡¦
//¡¦E¡¦¡¦¡¦]¡¦¡¦¡¦¡¦A¡¦¡¦¡¦¡¦¡¦¡¦
//¡¦E¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦
//¡¦E¡¦¡¦¡¦]¡¦¡¦¡¦¡¦ÌÌ§²¡¦¡¦¡¦
//¡¦EÙ°Ìß¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
//¡¦EÙ°Ìß¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦
//¡¦EÙ°Ìß¡¦]¡¦¡¦¡¦¡¦ÌÌ§²¡¦¡¦¡¦
// ********************************************************************
BOOL	RL_Cnv(
HANDLE				hDev,					// i) ÃÞÊÞ²½ÊÝÄÞ¡¦
BYTE					*bMem,				// i) ²Ò°¼¡¦Æ×ÝÚÝ¸Þ½¡¦¡¦¡¦
IPMFRAMEINFO	*pFramePar,		// i) ÌÚ°Ñ¡¦¡¦¡¦
ULONG					ulRlStart,		// i) ×ÝÚÝ¸Þ¡¦¡¦¡¦FFSET
ULONG					ulRlSize,			// i) ×ÝÚÝ¸Þ¡¦¡¦æ»²½¡¦
ULONG					ulFrmCnt,			// i) ¡¦¡¦ÌÚ°Ñ¡¦¡¦
ULONG					ulFrmNo,			// i) ¡¦\Ž¦¡¦¡¦éÌÚ°¡¦¡¦¡¦
BOOL					fLoop,				// i) Ù°Ìß¡¦]¡¦¡¦Ó°ÄÞÌ×¸Þ
BOOL					fGrabber,			// i) ¡¦¡¦¡¦¡¦¡¦Ì×¸Þ
BYTE					*bImg					// o) ×ÝÚÝ¸Þ¡¦W¡¦J¡¦¡¦¡¦¡¦
){
	BYTE					*pSrc;
	IPMGRABSTS		Sts;
	BOOL					fStatus	= TRUE;
	ULONG					ulRlCnt;
	ULONG					ulRlOutCnt;
	ULONG					ulFrmNoWk;
	ULONG					ulRlOffsetWk;
	BOOL					fChk;
	BOOL					fFrmEnd;

	// ÓÉ¸Û¡¦¡¦O¡¦¡¦APIXCNT=8¡¦¡¦O¡¦¡¦APIXBYTE=1¡¦¡¦O¡¦¡¦¡¦¡¦
	if(  (pFramePar->TYPE & COLORMSK)!=MONOTONE || pFramePar->PIXBIT!=8 || pFramePar->PIXBYTE!=1 ){
		goto END;
	}

	// Ù°Ìß¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
	if( fLoop && fGrabber ){
		mgGetRLStatus( hDev, &Sts );

		// ¡¦¡¦¡¦Ì×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦+¡¦¡¦¡¦Z¡¦o(mgGetRLStatus¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦Amposition¡¦¡¦¡¦¡¦i¡¦¡¦¡¦¡¦¡¦
		// ¡¦¡¦u¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
		if( Sts.mposition < g_ulRlOffset ){
			ulRlCnt		= ((Sts.mposition + ulRlSize) - g_ulRlOffset) / 2;
		} else {
			ulRlCnt		= (Sts.mposition - g_ulRlOffset) / 2;
		}

		// ¡¦¡¦o¡¦·ÌÚ°¡¦¡¦¡¦¡¦¡¦A0
		ulFrmNoWk			= 0;
		// ×ÝÚÝ¸Þ¡¦¡¦¡¦FFSET
		ulRlOffsetWk	= g_ulRlOffset;
		// Áª¡¦¡¦¡¦¡¦¡¦
		fChk				= false;

	// ¡¦¡¦¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
	} else if( fGrabber ){
		mgGetRLStatus( hDev, &Sts );

		// ¡¦¡¦¡¦Ì×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦+¡¦¡¦¡¦Z¡¦o(mgGetRLStatus¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦Amposition¡¦¡¦¡¦¡¦i¡¦¡¦¡¦¡¦¡¦
		// ¡¦¡¦u¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
		if( Sts.mposition < g_ulRlOffset ){
			ulRlCnt		= ((Sts.mposition + ulRlSize) - g_ulRlOffset) / 2;
		} else {
			ulRlCnt		= (Sts.mposition - g_ulRlOffset) / 2;
		}

		// ¡¦¡¦o¡¦·ÌÚ°¡¦¡¦¡¦
		ulFrmNoWk			= ulFrmNo;
		// ×ÝÚÝ¸Þ¡¦¡¦¡¦FFSET
		ulRlOffsetWk	= g_ulRlOffset;
		// Áª¡¦¡¦¡¦¡¦
		fChk				= TRUE;

	// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
	} else {
		// ¡¦¡¦o¡¦·ÌÚ°¡¦¡¦¡¦
		ulFrmNoWk			= 0;
		// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦
		ulRlOffsetWk	= g_ulRlOffset_Lst[ulFrmNo];
		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
		ulRlCnt			= ulRlSize - ulRlOffsetWk;
		// Áª¡¦¡¦¡¦¡¦¡¦
		fChk				= false;
	}

	// ×ÝÚÝ¸Þ½ÃÞ°¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
	pSrc		= bMem + ulRlStart;
	fStatus	= ConvertRL(
							(DWORD)pSrc,			// i) ¡¦]¡¦¡¦¡¦³ÊÞ¯Ì§
							ulRlCnt,					// i) ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
							ulRlSize,					// i) ×ÝÚÝ¸Þ¡¦¡¦æÊÞ¯Ì§»²½Þ			// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&ulRlOffsetWk,		// i/o) ×ÝÚÝ¸Þ¡¦Ì½À°¡¦FFSET			// Ù°Ìß¡¦]¡¦¡¦¡¦p
							(DWORD)bImg,			// o) ¡¦]¡¦¡¦¡¦æÊÞ¯Ì§
							pFramePar->XSIZE,	// i) ²Ò°¼¡¦¡¦SIZE
							pFramePar->YSIZE,	// i) ²Ò°¼¡¦¡¦SIZE
							&g_ulDestCnt,			// i/o) ²Ò°¼¡¦Ì½À°¡¦FFSET				// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&g_ulDestX,				// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&g_ulDestY,				// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
							ulFrmNoWk,					// i) ¡¦\Ž¦¡¦J¡¦ÌÚ°Ñ¡¦¡¦¡¦					// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦p Ì§²Ù¡¦¡¦¡¦p
							&ulRlOutCnt,			// o) ¡¦¡¦o¡¦¡¦½×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦			// Ì§²Ù¡¦¡¦¡¦p
							fChk,							// i) Áª¡¦¡¦¡¦ìÌ×¸¡¦
							&fFrmEnd					// o) ¡¦PÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¹Ì×¸¡¦
							);

	// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
	if( fGrabber ){
		// ×ÝÚÝ¸Þ¡¦FFSET¡¦¡¦¡¦¡¦
		g_ulRlOffset		= ulRlOffsetWk;
	}
	// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦ÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¡¦¡¦¡¦¡¦
	if( fGrabber && fFrmEnd ){
		// Ù°Ìß¡¦]¡¦¡¦¡¦¡¦¡¦¡¦A¡¦¡¦¡¦ÌÌÚ°¡¦¡¦O¡¦¡¦¡¦¡¦
		if( fLoop || ulFrmNo<ulFrmCnt-1 ){
			// ¡¦¡¦ÌÌÚ°¡¦¡¦¡¦
			ulFrmNoWk	= ulFrmNo + 1;
			if( ulFrmNoWk >= (ULONG)ulFrmCnt )	ulFrmNoWk	= 0;
			// ¡¦¡¦ÌÌÚ°¡¦Ì×ÝÚÝ¸Þ½¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦¡¦
			g_ulRlOffset_Lst[ulFrmNoWk]	= ulRlOffsetWk;
		}
	}
END:
	return( fStatus );
}
*/
// ********************************************************************
// ×ÝÚÝ¸Þ½ÃÞ°¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
// ********************************************************************
BOOL		ConvertRL(
DWORD		dwRlBuff,				// i) ¡¦]¡¦¡¦¡¦³ÊÞ¯Ì§
ULONG		ulRlSize,				// i) ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
ULONG		ulRlBuffSize,		// i) ×ÝÚÝ¸Þ¡¦¡¦æÊÞ¯Ì§»²½Þ			// Ù°Ìß¡¦]¡¦¡¦¡¦p
ULONG		*pulRlOffset,		// i/o) ×ÝÚÝ¸Þ¡¦Ì½À°¡¦FFSET			// Ù°Ìß¡¦]¡¦¡¦¡¦p
DWORD		dwImgBuff,			// o) ¡¦]¡¦¡¦¡¦æÊÞ¯Ì§
ULONG		ulImgSizeX,			// i) ²Ò°¼¡¦¡¦SIZE
ULONG		ulImgSizeY,			// i) ²Ò°¼¡¦¡¦SIZE
ULONG		*pulImgOffset,	// i/o) ²Ò°¼¡¦Ì½À°¡¦FFSET				// Ù°Ìß¡¦]¡¦¡¦¡¦p
ULONG		*pulDestX,			// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
ULONG		*pulDestY,			// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
ULONG		ulFrmNo,				// i) ¡¦\Ž¦¡¦J¡¦ÌÚ°Ñ¡¦¡¦¡¦					// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦p Ì§²Ù¡¦¡¦¡¦p
ULONG		*pulRlCnt,			// o) ¡¦¡¦o¡¦¡¦½×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦			// Ì§²Ù¡¦¡¦¡¦p
BOOL		fChk,						// i) Áª¡¦¡¦¡¦ìÌ×¸¡¦
BOOL		*pfFrmEnd				// o) ¡¦PÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¹Ì×¸¡¦
){
	BYTE		*p_dest;		// ¡¦]¡¦¡¦¡¦æ±ÄÞÚ½
	BYTE		color;
	WORD		*p_wtemp;		// ¡¦]¡¦¡¦¡¦³±ÄÞÚ½
	WORD		rldata;
	int			adr, adr_zen;
	int			xx;
	ULONG		ulRlCnt;		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
	ULONG		ulSrc;			// ¡¦]¡¦¡¦¡¦³ÊÞ¯Ì§¡¦¡¦u
	ULONG		ulDest;			// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦f¡¦¡¦
	DWORD		line;
	ULONG		ulFrmSize	= ulImgSizeX * ulImgSizeY;
	ULONG		ulStartLine;			// ¡¦\Ž¦¡¦J¡¦¡¦s¡¦¡¦¡¦
	BOOL		fFrmEnd	= false;	// 1ÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¹Ì×¸¡¦
	BOOL		fStatus	= TRUE;
//	CString	strMsg;

	// ¡¦]¡¦¡¦¡¦³±ÄÞÚ½¡¦¡¦¡¦¡¦
	p_wtemp		= (WORD*)dwRlBuff;
	// ¡¦]¡¦¡¦¡¦æ±ÄÞÚ½¡¦¡¦¡¦¡¦
	p_dest		= (BYTE*)dwImgBuff;

	// ¡¦\Ž¦¡¦J¡¦ÌÚ°Ñ¡¦¡¦¡¦¡¦¡¦s¡¦¡¦¡¦¡¦¡¦¡¦¡¦
	ulStartLine	= ulFrmNo * ulImgSizeY;

	xx			= *pulDestX;					// X ¡¦¡¦u
	line		= *pulDestY;					// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦s
	ulDest	= *pulImgOffset;			// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦f¡¦¡¦
	ulSrc		= (*pulRlOffset) / 2;	// ¡¦]¡¦¡¦¡¦¡¦¡¦u
	ulRlCnt	= 0;									// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦

	// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦f¡¦¡¦¡¦Ì¸Ø±
	if( ulDest >= ulFrmSize )		ulDest	= 0;

	adr_zen	= 0;									// ¡¦O¡¦¡¦¡¦¡¦¡¦u

	// ×ÝÚÝ¸Þ½ÃÞ°À»²½¡¦¡¦°Ì¡¦
	while( ulRlCnt<ulRlSize ){
		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦¡¦
		rldata	= *(p_wtemp + ulSrc);
		ulSrc++;			// ¡¦]¡¦¡¦¡¦³ÊÞ¯Ì§¡¦¡¦u
		ulRlCnt++;		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦¡¦

		// ¡¦]¡¦¡¦ÊÞ¡¦¡¦¡¦u¡¦¡¦AÊÞ¡¦¡¦¡¦¡¦¡¦¡¦B¡¦¡¦¡¦¡¦¡¦
		if( ulSrc*2 >= ulRlBuffSize ){
			// ¡¦¡¦¡¦¡¦o¡¦¡¦¡¦u¡¦¡¦AÊÞ¡¦¡¦¡¦¡¦¡¦¡¦
			ulSrc		= 0;
			// Áª¡¦¡¦¡¦¡¦¡¦¡¦
			if( fChk ){
				goto END;
			}
		}

		// ¡¦¡¦¡¦Þ°¡¦¡¦¡¦¡¦¡¦¡¦¡¦
		if((rldata & 0xC000) == 0xC000){
			continue;
		}
		// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦u¡¦¡¦¡¦
		adr		=	(rldata & 0x3fff);
		// ¡¦F¡¦¡¦¡¦¡¦¡¦
		color	=	((rldata >> 14) & 0x3) * 0x7f;

		// X¡¦¡¦¡¦u¡¦¡¦¡¦¡¦¡¦¡¦u¡¦¡¦z¡¦¡¦¡¦¡¦¡¦
		if( adr > (int)ulImgSizeX ){
			goto END;
		}
		// X¡¦¡¦¡¦u¡¦¡¦O¡¦¡¦¡¦¡¦u¡¦¡¦¡¦¡¦O¡¦¡¦¡¦¡¦
		if( adr <= adr_zen ){
			goto END;
		}
		adr_zen	= adr;

		// ¡¦\Ž¦¡¦J¡¦¡¦s¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦
		if( line >= ulStartLine ){
			// ¡¦¡¦¡¦¡¦u¡¦¡¦¡¦F¡¦¡¦h¡¦¡¦¡¦¡¦¡¦
			for( ;xx<adr;xx++)
			{
				if( ulDest < ulFrmSize ){
					// NULL¡¦¡¦¡¦¡¦¡¦¡¦
					if( p_dest )	*p_dest++	= color;
				} else {
					goto END;
				}
				ulDest++;
			}
		}

		// X¡¦¡¦¡¦u¡¦¡¦¡¦¡¦¡¦¡¦u¡¦¡¦¡¦¡¦
		if( xx == (int)ulImgSizeX ){
			xx			= 0;
			adr_zen	= 0;		// ¡¦O¡¦¡¦¡¦¡¦u
			// ¡¦¡¦¡¦s¡¦¡¦
			line++;
		}

		// Áª¡¦¡¦¡¦¡¦¡¦¡¦A¡¦s¡¦¡¦¡¦¡¦¡¦s¡¦¡¦B¡¦¡¦¡¦¡¦¡¦
		if( !fChk && line==ulStartLine+ulImgSizeY ){
			// ¡¦¡¦¡¦I¡¦¡¦
			break;
		// ¡¦s¡¦¡¦¡¦¡¦¡¦s¡¦¡¦¡¦¡¦¡¦¡¦¡¦
		} else if( line > ulStartLine+ulImgSizeY){
			goto END;
		}
	}
	// 1ÌÚ°Ñ¡¦¡¦¡¦¡¦¡¦B¡¦¡¦¡¦¡¦¡¦
	if( line==ulStartLine+ulImgSizeY ){
		line		= 0;
		fFrmEnd	= TRUE;
	}

END:
	*pulRlOffset	= ulSrc * 2;		// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦FFSET
	*pulDestX			= xx;						// X ¡¦¡¦u
	*pulDestY			= line;					// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦s
	*pulImgOffset	= ulDest;				// ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦f¡¦¡¦
	*pulRlCnt			= ulRlCnt;			// ¡¦¡¦o¡¦¡¦½×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦
	*pfFrmEnd			= fFrmEnd;			// 1ÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¹Ì×¸¡¦

	return (fStatus);
}
/*
// ********************************************************************
// ×ÝÚÝ¸Þ¡¦¡¦¡¦
// ********************************************************************
BOOL	RL_Save(
CString				*strFname,
BYTE					*bMem,				// i) ²Ò°¼¡¦Æ×ÝÚÝ¸Þ½¡¦¡¦¡¦
IPMFRAMEINFO	*pFramePar,		// i) ÌÚ°Ñ¡¦¡¦¡¦
ULONG					ulRlStart,		// i) ×ÝÚÝ¸Þ¡¦¡¦¡¦FFSET
ULONG					ulRlSize,			// i) ×ÝÚÝ¸Þ¡¦¡¦æ»²½¡¦
ULONG					ulFrmNo,			// i) ¡¦\Ž¦¡¦¡¦éÌÚ°¡¦¡¦¡¦
BOOL					fLoop					// i) Ù°Ìß¡¦]¡¦¡¦Ó°ÄÞÌ×¸Þ
){
	CFile			File;
	CString		strMsg;
	BOOL			fStatus		= false;
	BYTE			*pSrc;
	ULONG			ulDestX, ulDestY, ulDestCnt;
	ULONG			ulFrmNoWk;
	ULONG			ulRlOffsetWk;
	ULONG			ulRlCnt;
	ULONG			ulRlOutCnt;
	BOOL			fChk;
	BOOL			fFrmEnd;

	// ÓÉ¸Û¡¦¡¦O¡¦¡¦APIXCNT=8¡¦¡¦O¡¦¡¦APIXBYTE=1¡¦¡¦O¡¦¡¦¡¦¡¦
	if(  (pFramePar->TYPE & COLORMSK)!=MONOTONE || pFramePar->PIXBIT!=8 || pFramePar->PIXBYTE!=1 ){
		// "×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦A¡¦ ¡¦¡¦¡¦¡¦¡¦B"
		strMsg.LoadString( IDS_ERR_NOT_RL );
		AfxMessageBox( strMsg );
		goto END;
	}

	// Ù°ÌßÓ°ÄÞ¡¦¡¦¡¦¡¦
	if( fLoop ){
		// ¡¦¡¦o¡¦·ÌÚ°¡¦¡¦¡¦
		ulFrmNo			= 0;
		// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦
		ulRlOffsetWk	= g_ulRlOffset_Lst[ulFrmNo];
		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
		ulRlCnt			= ulRlSize - ulRlOffsetWk;
		// Áª¡¦¡¦¡¦¡¦¡¦
		fChk				= false;

	// ¡¦¡¦íÓ°Ä¡¦¡¦¡¦¡¦
	} else {
		// ¡¦¡¦o¡¦·ÌÚ°¡¦¡¦¡¦
		ulFrmNoWk		= ulFrmNo;
		// ×ÝÚÝ¸Þ¡¦¡¦¡¦Ì¾¡¦¡¦¡¦¡¦
		ulRlOffsetWk	= 0;
		// ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
		ulRlCnt			= ulRlSize;
		// Áª¡¦¡¦¡¦¡¦¡¦
		fChk				= false;
	}

	// ×ÝÚÝ¸Þ½ÃÞ°¡¦ð²Ò°¼Þ¡¦¡¦¡¦¡¦
	ulDestX	= ulDestY	= ulDestCnt = 0;
	pSrc		= bMem + ulRlStart;
	fStatus	= ConvertRL(
							(DWORD)pSrc,			// i) ¡¦]¡¦¡¦¡¦³ÊÞ¯Ì§
							ulRlCnt,					// i) ×ÝÚÝ¸Þ½ÃÞ°¡¦¡¦
							ulRlSize,					// i) ×ÝÚÝ¸Þ¡¦¡¦æÊÞ¯Ì§»²½Þ			// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&ulRlOffsetWk,		// i/o) ×ÝÚÝ¸Þ¡¦Ì½À°¡¦FFSET			// Ù°Ìß¡¦]¡¦¡¦¡¦p
							NULL,							// o) ¡¦]¡¦¡¦¡¦æÊÞ¯Ì§
							pFramePar->XSIZE,	// i) ²Ò°¼¡¦¡¦SIZE
							pFramePar->YSIZE,	// i) ²Ò°¼¡¦¡¦SIZE
							&ulDestCnt,				// i/o) ²Ò°¼¡¦Ì½À°¡¦FFSET				// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&ulDestX,					// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
							&ulDestY,					// i/o) ¡¦]¡¦¡¦¡¦¡¦¡¦¡¦u							// Ù°Ìß¡¦]¡¦¡¦¡¦p
							ulFrmNoWk,				// i) ¡¦\Ž¦¡¦J¡¦ÌÚ°Ñ¡¦¡¦¡¦					// ¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦p Ì§²Ù¡¦¡¦¡¦p
							&ulRlOutCnt,			// o) ¡¦¡¦o¡¦¡¦½×ÝÚÝ¸Þ½ÃÞ°À¡¦¡¦			// Ì§²Ù¡¦¡¦¡¦p
							fChk,							// i) Áª¡¦¡¦¡¦ìÌ×¸¡¦
							&fFrmEnd					// o) ¡¦PÌÚ°Ñ¡¦¡¦¡¦W¡¦J¡¦I¡¦¹Ì×¸¡¦
							);

	if( fStatus == TRUE ){
		// Ì§²Ù¡¦Ìµ°ÌßÝ
		if( !File.Open( *strFname, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary ) ){
			strMsg.Format( "File Open Error !!\n%s", *strFname );
			AfxMessageBox( strMsg );
			goto END;
		}
		File.Write( pSrc, ulRlOutCnt*2 );
		File.Close();
	}
END:
	return( fStatus );
}
*/

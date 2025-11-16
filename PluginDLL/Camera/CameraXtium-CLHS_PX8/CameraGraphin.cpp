/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\CameraGraphin.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "windows.h"
#include "windows.h"
//#include "winbase.h"
//#define _AFXDLL
//#undef UNICODE
//#include "stdafx.h"
#include "atlstr.h"
#include "math.h"
#include "CameraGraphin.h"
#include "CameraSetting.h"
#include "XDLLType.h"
#include "XCameraDLL.h"
#include "XMainSchemeMemory.h"
#include "screenformat.h"
//#include "ipm8540.h"
//#include "global.h"
#include "RunLen.h"

#define		MYPROCESSYOYU	(0x4000000)//64M

CameraGraphin::CameraGraphin()
{

}

CameraGraphin::~CameraGraphin()
{

}

//HANDLE			g_hDev;					// IPM・銘淙涓淑歡湶
BOOL			m_fAorD;				// 8540A 8540D ・・別弩・IPMCAMCONFIG	m_CameraPar;			// 巾・・・IPMCAMCONFIG	m_CameraParB;			// 巾・・・IPMANALOGPAR	m_AnalogPar;			// 嬰杆・・・IPMCLPAR		m_CLPar;
IPMCLPAR		m_CLParB;
OSVERSIONINFO	g_osVer;				// OS舗絢洳・ULONG_PTR		m_processMinSizeDef, m_processMaxSizeDef;
DWORD			m_dwAllocSize;			// ・・・・蚋嗹参殉
DWORD			m_prcSts;
LPVOID			g_pHandle		= NULL;	// NT・p厶慂歡湶
BOOL			m_fContFlg;				// ・A・・・・耗五
BOOL			m_fLoopStartEnb;		// 抂餅・・]・・・J・耗五
BOOL			m_fLoopIntEnb;			// 抂餅・・・・・・・・・・J・耗五
BOOL			m_fExit;				// ・・・耗五
ULONG			m_ulTim;				// ・・・・v・・p
HANDLE			g_hEvent		= NULL;	// ・]・・・p
HANDLE			g_hLocalEvent	= NULL;	// ・]・・・p
HANDLE			g_hEventB		= NULL;	// ・]・・・p
HANDLE			g_hLocalEventB	= NULL;	// ・]・・・p
DWORD			m_dwTimeout		= 0;	// 晴儕劃・l
//CDlgSetLoop		m_DlgSetLoop;			// 抂餅・・・OVERLAPPED		g_Ov;					// 軌舗易・・\・・・//afx_msg void OnExit();
//BOOL			m_fRdyLoop;				// 抂餅・・・・\耗五

//global.h
BOOL			g_f8530;				// IPM-8530D・面弩・BOOL			g_f8530CL;				// IPM-8530CL・面弩・BOOL			g_CL_B;
BOOL			g_CL_M;
BOOL			g_CL_F;
IPMFRAMEINFO	g_FramePar;				// 木委・・・IPMFRAMEINFO	g_FrameParB;			// 木委・・・BOOL			g_fRdyRL;				// 忿旱五・・・p・・\耗五
int				g_iFrmCnt	=1;			// 木委・・・・
int				g_iFrmCntB	=1;			// 木委・・・・
IPMUSERMEMORY	g_mtbl;					// 厶悵丹勿・ULONG			g_ulRlStart;			// 忿旱五・・・FFSET
ULONG			g_ulRlSize;				// 忿旱五・・羯化・BYTE			*g_bMem;				// 禍絢・惇毓欷渊・・・BOOL			g_fEnbRL;				// 忿旱五・・・・・・nable
//CRFrm			*g_pRFrm;				// 忿旱五縮攬・//CChildFrame		*g_pCFrm;				// 禍絢淕攬・//CChildView		*g_pCView;				// 禍絢淤洵・//CTView			*g_pTView;				// 准・・爪凡��
//CTViewB			*g_pTViewB;				// 准・・爪凡��
//CRView			*g_pRView;				// 忿旱五祝洵・//CTFrmB			*g_pTFrmB;				// 准・・爪木委
BOOL			g_fLoop;				// 抂餅・・贄按・int				g_iFrmNo;				// ・・・\ｦ・・木委・・・
BOOL			g_fGrabber;				// ・・・・・耗五
ULONG			g_ulIntCnt;				// 弉・・・・・・・・
BOOL			g_ConvFlag;				//Convert・t・・・O
BOOL			g_AdjustFlag;			//Convert・t・・・O

//LUT
const int	CamDepth=256;		//8bit
int			RedCustomLut	[CamDepth];
int			GreenCustomLut	[CamDepth];
int			BlueCustomLut	[CamDepth];
int			RedBrightness;			//Red
int			RedContrast;
int			RedGamma;
int			RedFloor;
int			RedCeiling;
bool		RedApply;
int			GreenBrightness;		//Green
int			GreenContrast;
int			GreenGamma;
int			GreenFloor;
int			GreenCeiling;
bool		GreenApply;
int			BlueBrightness;		//Blue
int			BlueContrast;
int			BlueGamma;
int			BlueFloor;
int			BlueCeiling;
bool		BlueApply;

int			exposureTime=7795;
int			ProofDataInt[8192];
int			ProofDataDecim[8192];
QString		ProofDataFile;
bool		pbProofFlag;
bool		pbProofCancelFlag;
int			RtoL=0;				//・・E・・]

// 厶・m・・//BOOL		MemorySecure(HANDLE handle);
// 朦源化・・・X
void		ChangeLockSize(HANDLE handle);
// 厶・・J・・void		FreeMem();
// 忿旱五・・\・s・・\・・・X
void		ChgRl();
// 禍絢淹化・・・・void		SetImgSize();
// 木委・・・・・・・X・・・・
void		ChgFrmCnt(HANDLE handle, int iFrmCnt );
// ・・・准・・//UINT		GrabThread();
UINT		GrabThread(void *handle);
// ・・・]・・・・・・
void		NormalPrc(void *handle);
// 抂餅・]・・・・・・
void		LoopPrc(void *handle);
// 抂餅・・]・・・J・准・・UINT		LoopStartThread(void *handle);
// 抂餅・・]・・・J・・・・・
void		LoopStartPrc(void *handle);
// 抂餅・・・・・・欟掛坪・・UINT		LoopIntCntThread(void *handle);
// 抂餅・・・・・・・・・恭歡・・・・
void		LoopIntCntPrc(void *handle);
// ・I・・・・・
void		ExitProcess(HANDLE handle);
// 厶・・nlock
void		UnlockMem();
// 涙按涵・欷・・X・V
void		UpdateSetting(void *handle);

#if 0
// ********************************************************************
// 厶・・m・・丹勿・・・・・・\・・// ********************************************************************
BOOL MemorySecure(HANDLE handle)
{
	HANDLE					hProcess	= NULL;
	BOOL					fResult		= TRUE;
	LONG					lRet;
	CHAR					ctemp[255];
	DWORD					processMinSize, processMaxSize;
//	CString					strMsg;
	DWORD					errorCode;
	ULONG					ulSize;
	BYTE					*bMem		= NULL;

	// NT,2000,XP・・・・	if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){
		//###########################################################
		//        ・・面炳晶・・AM朦源化・・・・・・・・・l・・・・
		//###########################################################
		hProcess	= GetCurrentProcess();
		fResult		= GetProcessWorkingSetSize( hProcess, &m_processMinSizeDef, &m_processMaxSizeDef );
		if( !fResult ){
//			MessageBox("Failed GetProcessWorkingSetSize !!");
		}

		//###############################################
		//        ・・面炳晶・・AM朦源化・・・X
		//###############################################
		m_dwAllocSize	= (g_FramePar.XSIZE * g_FramePar.YSIZE * g_FramePar.PIXBYTE * g_iFrmCnt) + (g_FrameParB.XSIZE * g_FrameParB.YSIZE * g_FrameParB.PIXBYTE * g_iFrmCntB);
		processMinSize	= m_dwAllocSize + MYPROCESSYOYU;
		processMaxSize	= m_dwAllocSize + MYPROCESSYOYU;
		fResult		= SetProcessWorkingSetSize( hProcess, processMinSize, processMaxSize );
		if( !fResult ){
//			MessageBox("Failed SetProcessWorkingSetSize !!");
		}
		else{
			m_prcSts = 1L;
		}

		//###############################################
		//    ・・z営湍・・・・∈亊・・・\・・  
		//    ・・z営湍・・・雕亊・・・・・・厶・・m・・
		//###############################################
		g_pHandle		= VirtualAlloc( NULL, m_dwAllocSize, MEM_COMMIT, PAGE_READWRITE );
		if( !g_pHandle ){
//			MessageBox("Failed getting virtual address space!!"); 
			ChangeLockSize(handle);
			goto INITEND;
		}
		fResult		= VirtualLock( g_pHandle, m_dwAllocSize );
		bMem			= (BYTE*)g_pHandle;

		//###############################################
		//                 ・・・・・\ｦ
		//###############################################
//		strMsg.Format( "[result] : %x , [pHandle] : %x !!\n", fResult, g_pHandle );
		if( fResult==false ){
//			MessageBox("Virtual Lock Error!!");
			errorCode = GetLastError();
//			strMsg.Format( "[Error Code] : %x !!\n", errorCode );
//			MessageBox( strMsg );
			if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){
				FreeMem();
			}
			goto INITEND;
		}

		//###################################################################################  
		//                    ・・・・・・・e・[・u・・・・・・・・・・・・・・ 
		//###################################################################################  
		g_mtbl.off			= 0L;
		g_mtbl.lm			= (ULONG_PTR)g_pHandle;					// 06/02/06 ULONG=>ULONG_PTR・・・X
		g_mtbl.size			= m_dwAllocSize;
		g_mtbl.tableNum		= 0L;
		if( g_fRdyRL ){
			// Ach筑粟・・・羯化・			ulSize			= ( ( g_FramePar.XSIZE * g_FramePar.YSIZE * g_FramePar.PIXBYTE ) * g_iFrmCnt );
			// Bch・p・・・・・・爪攴
			g_ulRlStart		= ulSize;
			// Bch・p・・・婿化・			g_ulRlSize		= ( ( g_FrameParB.XSIZE * g_FrameParB.YSIZE * g_FrameParB.PIXBYTE ) * g_iFrmCntB );
			lRet	= mgCreateMemoryTableEx( handle, &g_mtbl, ulSize, g_ulRlSize );
			wsprintf(ctemp,"Create Table Ex Error!!%x",lRet);
		/* Bch・・・p・s・・\ */
		} else {
			lRet	= mgCreateMemoryTable( handle, &g_mtbl );
			wsprintf(ctemp,"Create Table Error!!%x",lRet);
		}
		if( lRet!=IPM_NOERROR ){
//			MessageBox(ctemp);
			fResult = false;
			goto INITEND;
		}
	}
	// 98,ME・・・・	else{
		// "・・・・S・・・g・p・s・・・・
//		strMsg.LoadString( IDS_ERR_OS );
//		MessageBox( strMsg );
		fResult = IPM_ERROR;
		goto INITEND;
	}
	// for DEBUG
	IPMCAMCONFIG	CamPar, CamParB;
	// for DEBUG
	
	lRet	= mgTempToMyHardware( handle, &m_CameraPar);
	lRet	= mgMyHardwareToTemp( handle, &CamPar);
	if(g_CL_M){
		lRet	= mgTempToMyHardwareB( handle, &m_CameraParB);
		lRet	= mgMyHardwareToTempB( handle, &CamParB);
	}
	if(g_f8530CL){
		lRet	= mgTempToMyHardware_CL( handle, &m_CLPar, &m_CameraPar );
		if(g_CL_M){
			lRet	= mgTempToMyHardwareB_CL( handle, &m_CLParB, &m_CameraParB );
		}
	}
	if(m_fAorD)		mgTempToMyHardware_A( handle, &m_AnalogPar);  // IPM-8540A・・p
	// ・m・・・・・・・・・	g_bMem	= bMem;
//	maketable();
INITEND:
  return( fResult );
}
#endif

// ********************************************************************
// 朦源化・・・X
// ********************************************************************
void ChangeLockSize(HANDLE handle) 
{
	BOOL		result;
	LONG		lRet;
	HANDLE	hProcess;

	//###############################################
	//        ・・面炳晶・・AM朦源化・・・X
	//###############################################
	if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){		// WinNT Ver
		if(m_prcSts){
			hProcess	= GetCurrentProcess();
			result		= SetProcessWorkingSetSize(hProcess, m_processMinSizeDef, m_processMaxSizeDef);
			if(!result){
//				AfxMessageBox("Failed ResetProcessWorkingSetSize !!");
			}
		}
		m_prcSts = NULL;

		lRet	= mgReleaseMemoryTable(handle, &g_mtbl);
	}
}

// ********************************************************************
// 厶・・J・・// ********************************************************************
void FreeMem() 
{
	BOOL result;
	result = VirtualFree(g_pHandle, 0, MEM_RELEASE);	
	if(result==false){
//		AfxMessageBox("Return Failed [VirtualFree]");
	}
	g_pHandle	= NULL;
	g_bMem		= NULL;
	RL_Free();
}

// ********************************************************************
// 2ch・・\・s・・\・・・X
// ********************************************************************
void ChgRl()
{
	// 2ch・s・・\・・・・・・・	if( !g_fRdyRL )	g_fEnbRL		= false;
	// 2ch・・・・・・・・・・・//	if( g_pRFrm ){		g_pRFrm->ChgRl();}
	// 禍絢・・・・・u・・・X
//	if( g_pCFrm )		g_pCFrm->ChgRl();
}

// ********************************************************************
// 禍絢淹化・・・・// ********************************************************************
void SetImgSize()
{
	ULONG	ulFrmByte	= g_FramePar.XSIZE * g_FramePar.YSIZE * g_FramePar.PIXBYTE;
	// ・・・P・x・・Z・o
	int	iMaxKido;
	// 喇雇
	if((g_FramePar.TYPE & COLORMSK)==MONOTONE){
		iMaxKido	= (int)pow(2.0,(int)g_FramePar.PIXBIT)-1;
	// 琴・	} else {
		iMaxKido	= (int)pow(2.0,(int)(g_FramePar.PIXBIT/3))-1;
	}

	// 禍絢・・・婿化・・X
//	if( g_pCView )		g_pCView->SetImgSize();
	// 准・・爪・・・・X・V
//	if( g_pTView )		g_pTView->SetImgSize();
	if( g_CL_M && g_fRdyRL){
//		if( g_pTViewB )		g_pTViewB->SetImgSize();
//		if( g_pRView )		g_pRView->SetImgSize();
//		if( g_pTFrmB )		g_pTFrmB->ChgRl();
	}
	return;
}

// ********************************************************************
// 木委・・・・・・・X・・・・
// ********************************************************************
void ChgFrmCnt(HANDLE handle, int iFrmCnt )
{
	DWORD	result;
	int		fbak = g_iFrmCnt;			// ・・・・・・・l・綿洒険・・//	CString	strMsg;
	// ・・・・・m・・・・・・・	if(g_bMem){
		ExitProcess(handle);
	}
	g_iFrmCnt	= iFrmCnt;
	// ・・殘攬・・・・・z・・・・・・
	if( g_iFrmNo > g_iFrmCnt-1 )	g_iFrmNo	= g_iFrmCnt-1;
	// 厶・・・・m・・	result = MemorySecure(handle);
	if(result = false){
		// "厶・m・・・・s・・・・・
//		strMsg.LoadString( IDS_ERR_MEM_GET );
//		MessageBox( strMsg );

		g_iFrmCnt = fbak;
		result = MemorySecure(handle);
		if(result = false){
			// "厶・・・m・・・・s・・・・・I・・・・・
//			strMsg.LoadString( IDS_ERR_MEMGET_END );
//			MessageBox( strMsg );
//			OnExit();
		}
	}
	else{
		// ・・・・・・X・V
//		m_DlgReview.ChgFrmCnt();
	}
}

// ********************************************************************
// ・I・・・・・
// ********************************************************************
void ExitProcess(HANDLE handle) 
{
	//###############################################
	//    ・・z営湍・・・霖涅亊・・・・・・厶・・m・・
	//    ・・z営湍・・・・J・・  
	//###############################################
	if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){
		UnlockMem();
		FreeMem();
	}
	ChangeLockSize(handle);	
}

// ********************************************************************
// 厶・・nlock
// ********************************************************************
void UnlockMem() 
{
	BOOL result;
	result = VirtualUnlock(g_pHandle, m_dwAllocSize);
	if(result==false){
//		MessageBox("Return Failed [VirtualUnlock]");
	}
}

//*********************************************************************
// ・・・准・・・・・・・・・・・
//*********************************************************************
//UINT  GrabThread(LPVOID Prm)
UINT  GrabThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;
	// ・・・・・・・・・	pWnd->GrabPrc();
*/
	// ・・・]・・・・・・	if( !g_fLoop )
		NormalPrc(handle);
	// 抂餅・]・・・・・・	else
		LoopPrc(handle);

	return( 0 );
}

// ********************************************************************
// ・・・]・・・・・・
// ********************************************************************
void NormalPrc(void *handle)
{
	DWORD		dwRet, dwRet2;
//	CString	strMsg;
	ULONG		ret;
	m_ulTim				= GetTickCount();								// ・J・・・・
	// 耳庵洶欷・・・・X・V
//	m_DlgShd.Enable( false );

	do {
		ret=ResetEvent(g_hEvent);
		g_Ov.hEvent		= g_hEvent;// OVERLAPPED・・g・・		g_ConvFlag		=	TRUE;
		g_AdjustFlag	=	TRUE;
		dwRet			= mgGrabberStart( handle,
			&g_FramePar,
			&g_mtbl,
			&g_Ov,
			MGGRAB_COUNT_NORMAL,
			1L,
			g_iFrmCnt,
			m_dwTimeout,
			(PVOID)0L );
		// ・]・・・J・閑・		if( dwRet!=IPM_NOERROR )	break;

		// ・I・・・・//		dwRet2					= WaitForSingleObject(g_hEvent,INFINITE);
		dwRet2					= WaitForSingleObject(g_hEvent,IGNORE);
		
		if( dwRet2==WAIT_OBJECT_0 ){
			// ・・・耗五
			if( m_fExit ){
				m_fContFlg	= false;
				break;
			}
			// ・`・・・・・
//			g_pCView->DrawScreen();
//			DrawScreen();
		}
	// ・A・・・・・・・・	} while( m_fContFlg );

/* D-20061116
	// ・・・・I・・	g_fGrabber		= false;

	// ・・・I・・	mgGrabberCancel( handle );

	// 弉・・・・・欸・訟
	mgCancelLineIntWaitEvent( handle );

	// 耳庵洶欷・・・・X・V
//	m_DlgShd.Enable( TRUE );

	// ・]・・・J・閑・	if( dwRet!=IPM_NOERROR )
	{
//		strMsg.Format( "mgGrabberStart=%X", dwRet );
//		MessageBox( strMsg );
	}
*/
}

// ********************************************************************
// 抂餅・]・・・・・・
// ********************************************************************
void LoopPrc(void *handle)
{
	DWORD		dwRet;
	BOOL		fFirstFrm;		// ・・・・面攬・・\ｦ耗五
	ULONG		ulLine;				// ・・・・・・s・・
	ULONG		ulFrmCnt;			// ・・・・・鰐攬・・
	ULONG		ulFrmNo;			// ・\ｦ・・虧攬・・・
	BOOL		fStatus		= TRUE;
//	CString	strMsg;
	ULONG		ulIntCnt;			// ・・・・・・・・
	ULONG		ret;
	// ・・・・面攬・・\ｦ耗五
	fFirstFrm			= TRUE;

	// ・・・・・・・・
	ulIntCnt			= 0;

	// ・・・・・・・・・\ｦ・・・・X・V
//	m_DlgSetLoop.Enable( false );
	// 耳庵洶欷・・・・X・V
//	m_DlgShd.Enable( false );

	m_ulTim				= GetTickCount();								// ・J・・・・
	do {
		// 弉・・・・・・・・		ret=ResetEvent(g_hLocalEvent);
		// ・]・・・J・・・・・		m_fLoopIntEnb	= TRUE;

		if(m_dwTimeout){
			dwRet					= WaitForSingleObject(g_hLocalEvent,m_dwTimeout);
		}
		else{
			dwRet					= WaitForSingleObject(g_hLocalEvent,INFINITE);
		}

		if( dwRet==WAIT_OBJECT_0 ){
			// ・・・耗五
			if( m_fExit ){
				m_fContFlg	= false;
				break;
			}
/*
			// --------------------------------
			// ・・・・・・・・・・\ｦ
			// --------------------------------
			ulIntCnt++;
			m_DlgSetLoop.DspCnt( g_ulIntCnt, ulIntCnt );

			// ・\ｦ木委・・・・・Z・o
			ulLine		= (g_ulIntCnt-1) * g_ulLineCnt;
			ulFrmCnt	= ulLine / g_FramePar.YSIZE;
			ulFrmNo		= ulFrmCnt==0 ? 0 : ulFrmCnt-1;
			ulFrmNo		= ulFrmNo % g_iFrmCnt;

			// ・\ｦ・・・面攬・・・・・・・・・A・・・・面攬・・・・			if( g_iFrmNo != (int)ulFrmNo || fFirstFrm ){
				g_iFrmNo	= ulFrmNo;
				// ・`・・・・・
				g_pCView->DrawScreen();
			}

			// 木委・・・・・Q木委・・・・・			if( g_iFrmNo > 0 ){
				// ・・・・面攬・・A・\ｦ・・・				fFirstFrm	= false;
			}
*/
		}
		else {
			// ・`・・・・・
//			g_pCView->DrawScreen();
			mgGrabberCancel( handle );			// ・・・I・・			m_fContFlg	= false;
			fStatus			= false;
			// "晴儕劃・・・
//			strMsg.LoadString( IDS_ERR_TIMEOUT );
			break;
		}
	// ・A・・・・・・・・	} while( m_fContFlg );

	// ・・・・I・・	g_fGrabber		= false;

	// ・・・I・・	mgGrabberCancel( handle );

	// 弉・・・・・欸・訟
	mgCancelLineIntWaitEvent( handle );

	// ・・・・・・・・・\ｦ・・・・X・V
//	m_DlgSetLoop.Enable( TRUE );
	// 耳庵洶欷・・・・X・V
//	m_DlgShd.Enable( TRUE );

	// 閑威・絢・・\ｦ
	if( !fStatus ){
//		MessageBox( strMsg );
	}
}

//*********************************************************************
// 抂餅・・・]・・・J・准・・//*********************************************************************
//UINT  LoopStartThread(LPVOID Prm)
//UINT  LoopStartThread()
UINT  LoopStartThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;

	// 抂餅・・]・・・J・・・・・・・	pWnd->LoopStartPrc();
*/
	LoopStartPrc(handle);
	return( 0 );
}

// ********************************************************************
// 抂餅・・]・・・J・・・・・
// ********************************************************************
void LoopStartPrc(void *handle)
{
	DWORD		dwRet;
//	CString	strMsg;

	// ・]・・・J・・・・	while( !m_fLoopStartEnb )		Sleep(1);

	// Grabber ・J・
		dwRet	= mgGrabberStart( handle, &g_FramePar, &g_mtbl, NULL,
							MGGRAB_INFINITE, 1L, g_iFrmCnt, 0, (PVOID)0L );

	// ・]・・・J・閑・	if( dwRet!=IPM_NOERROR ){

		// ・・・I・・		mgGrabberCancel( handle );

		// 弉・・・・・欸・訟
		mgCancelLineIntWaitEvent( handle );

		// 2ch・・・		if( !g_fEnbRL ){
//			strMsg.Format( "mgGrabberStart=%X", dwRet );
		}
//		MessageBox( strMsg );
	}
}

//*********************************************************************
// 抂餅・・・・・・・・・・恭歡准・・//*********************************************************************
//UINT  LoopIntCntThread(LPVOID Prm)
UINT  LoopIntCntThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;
	// 抂餅・・・・・・・・・恭歡・・・・・・	pWnd->LoopIntCntPrc();
*/
	LoopIntCntPrc(handle);
	return( 0 );
}

// ********************************************************************
// 抂餅・・・・・・・・恭歡・・・・
// ********************************************************************
void LoopIntCntPrc(void *handle)
{
	DWORD		dwRet;
	ULONG		ret;
	// ・・・・・・・・
	g_ulIntCnt		= 0;

	// 架渺・・・	g_Ov.hEvent		= g_hEvent;

	// ・・・・・・・・・J・・・・	while( !m_fLoopIntEnb )		Sleep(1);

	do {
		ret=ResetEvent(g_hEvent);
		// 弉・・・・・・・J・
		mgSetLineIntWaitEvent( handle, &g_Ov );
		// ・]・・・J・・・・・		m_fLoopStartEnb	= TRUE;
		// 弉・・・・・・・・		if(m_dwTimeout){
			dwRet					= WaitForSingleObject(g_hEvent,m_dwTimeout);
		}
		else{
			dwRet					= WaitForSingleObject(g_hEvent,INFINITE);
		}

		if( dwRet==WAIT_OBJECT_0 ){
			// ・・・耗五
			if( m_fExit ){
				SetEvent( g_hLocalEvent );
				break;
			}
			// ・・・・・・・・
			g_ulIntCnt++;
			SetEvent( g_hLocalEvent );
		}
		else {
			SetEvent( g_hLocalEvent );
			break;
		}
	// ・A・・・・・・・・	} while( m_fContFlg );
}
/*
// ********************************************************************
// ・I・・// ********************************************************************
void OnExit() 
{
	DWORD lret;
	CHAR *myFile;

	// ・・・・
	if( g_fGrabber ){
		// ・・・耗五
		m_fExit			= TRUE;
		// ・A・・・・耗五
		m_fContFlg	= false;
		// ・・・I・・		mgGrabberCancel( handle );
	}
/*
	// ・・・・
	if( g_fGrabber_B ){
		// ・・・耗五
		m_fExit_B			= TRUE;
		// ・A・・・・耗五
		m_fContFlg_B	= false;
		// ・・・I・・		mgGrabberCancelB( handle );
	}
*/
/*
//	SearchPath(NULL,"myconfig\0",NULL,255,myDir.GetBuffer(255),&myFile);
//	lret = SetCurrentDirectory("c:\\");

	mgTempToConfigFile("XCM80_8bit4tap.dat\0", &m_CameraPar,&g_FramePar);
	if(g_f8530CL){mgTempToConfigFile_CL( "XCM80_8bit4tap.dat\0", &m_CLPar);}
//	DestroyWindow();
}
*/
void UpdateSetting(void *handle)
{
	LONG	lRet;
	m_CameraPar.PADIS=exposureTime;
	lRet	= mgTempToMyHardware( handle, &m_CameraPar);
	if(g_CL_M)
		lRet	= mgTempToMyHardwareB( handle, &m_CameraParB);
	if(g_f8530CL){
		lRet	= mgTempToMyHardware_CL( handle, &m_CLPar, &m_CameraPar );
		if(g_CL_M)
			lRet	= mgTempToMyHardwareB_CL( handle, &m_CLParB, &m_CameraParB );
	}
	if(m_fAorD)
		mgTempToMyHardware_A( handle, &m_AnalogPar);  // IPM-8540A・・p
}

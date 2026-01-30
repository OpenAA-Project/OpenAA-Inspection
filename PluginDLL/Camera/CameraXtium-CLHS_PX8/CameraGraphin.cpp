/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



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

//HANDLE			g_hDev;					// IPM������޲������
BOOL			m_fAorD;				// 8540A 8540D ������׸��IPMCAMCONFIG	m_CameraPar;			// �ҡ�����IPMCAMCONFIG	m_CameraParB;			// �ҡ�����IPMANALOGPAR	m_AnalogPar;			// ��۸������IPMCLPAR		m_CLPar;
IPMCLPAR		m_CLParB;
OSVERSIONINFO	g_osVer;				// OS�ް�ޮ��ULONG_PTR		m_processMinSizeDef, m_processMaxSizeDef;
DWORD			m_dwAllocSize;			// �����������ػ���
DWORD			m_prcSts;
LPVOID			g_pHandle		= NULL;	// NT��p��������
BOOL			m_fContFlg;				// ��A���������׸�
BOOL			m_fLoopStartEnb;		// ٰ�ߡ���]������J���׸�
BOOL			m_fLoopIntEnb;			// ٰ�ߡ�������������������J���׸�
BOOL			m_fExit;				// �������׸�
ULONG			m_ulTim;				// ��������v����p
HANDLE			g_hEvent		= NULL;	// ��]������p
HANDLE			g_hLocalEvent	= NULL;	// ��]������p
HANDLE			g_hEventB		= NULL;	// ��]������p
HANDLE			g_hLocalEventB	= NULL;	// ��]������p
DWORD			m_dwTimeout		= 0;	// ��ѱ�ġ�l
//CDlgSetLoop		m_DlgSetLoop;			// ٰ�ߡ�����OVERLAPPED		g_Ov;					// ���ްס���\������//afx_msg void OnExit();
//BOOL			m_fRdyLoop;				// ٰ�ߡ�������\�׸�

//global.h
BOOL			g_f8530;				// IPM-8530D����׸��BOOL			g_f8530CL;				// IPM-8530CL����׸��BOOL			g_CL_B;
BOOL			g_CL_M;
BOOL			g_CL_F;
IPMFRAMEINFO	g_FramePar;				// �ڰѡ�����IPMFRAMEINFO	g_FrameParB;			// �ڰѡ�����BOOL			g_fRdyRL;				// ���ݸޡ�����p����\�׸�
int				g_iFrmCnt	=1;			// �ڰѡ�������
int				g_iFrmCntB	=1;			// �ڰѡ�������
IPMUSERMEMORY	g_mtbl;					// ��ذð�ޡ�ULONG			g_ulRlStart;			// ���ݸޡ�����FFSET
ULONG			g_ulRlSize;				// ���ݸޡ���滲���BYTE			*g_bMem;				// �Ұ�������ݸ޽������BOOL			g_fEnbRL;				// ���ݸޡ�����������nable
//CRFrm			*g_pRFrm;				// ���ݸ޽�ڰ��//CChildFrame		*g_pCFrm;				// �Ұ���ڰ��//CChildView		*g_pCView;				// �Ұ���ޭ��//CTView			*g_pTView;				// �ڡ������ޭ�
//CTViewB			*g_pTViewB;				// �ڡ������ޭ�
//CRView			*g_pRView;				// ���ݸ޽�ޭ��//CTFrmB			*g_pTFrmB;				// �ڡ������ڰ�
BOOL			g_fLoop;				// ٰ�ߡ����Ӱġ�int				g_iFrmNo;				// ������\�������ڰѡ�����
BOOL			g_fGrabber;				// �����������׸�
ULONG			g_ulIntCnt;				// ײ����������������
BOOL			g_ConvFlag;				//Convert��t������O
BOOL			g_AdjustFlag;			//Convert��t������O

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
int			RtoL=0;				//����E����]

// �ӡ�m����//BOOL		MemorySecure(HANDLE handle);
// ۯ����������X
void		ChangeLockSize(HANDLE handle);
// �ӡ���J����void		FreeMem();
// ���ݸޡ���\��s����\������X
void		ChgRl();
// �Ұ�޻����������void		SetImgSize();
// �ڰѡ�������������X��������
void		ChgFrmCnt(HANDLE handle, int iFrmCnt );
// �������ڡ���//UINT		GrabThread();
UINT		GrabThread(void *handle);
// ������]������������
void		NormalPrc(void *handle);
// ٰ�ߡ�]������������
void		LoopPrc(void *handle);
// ٰ�ߡ���]������J���ڡ���UINT		LoopStartThread(void *handle);
// ٰ�ߡ���]������J����������
void		LoopStartPrc(void *handle);
// ٰ�ߡ�����������ݶ���ڡ���UINT		LoopIntCntThread(void *handle);
// ٰ�ߡ��������������������ġ�������
void		LoopIntCntPrc(void *handle);
// ��I����������
void		ExitProcess(HANDLE handle);
// �ӡ���nlock
void		UnlockMem();
// �ް�޾��ݸ����X��V
void		UpdateSetting(void *handle);

#if 0
// ********************************************************************
// �ӡ���m����ð�ޡ�����������\����// ********************************************************************
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

	// NT,2000,XP��������	if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){
		//###########################################################
		//        �������۾�����AMۯ����������������������l��������
		//###########################################################
		hProcess	= GetCurrentProcess();
		fResult		= GetProcessWorkingSetSize( hProcess, &m_processMinSizeDef, &m_processMaxSizeDef );
		if( !fResult ){
//			MessageBox("Failed GetProcessWorkingSetSize !!");
		}

		//###############################################
		//        �������۾�����AMۯ����������X
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
		//    ����z���ڡ���������Я������\����  
		//    ����z���ڡ�������Я�������������ӡ���m����
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
		//                 ����������\��
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
		//                    ��������������e��[��u���������������������������� 
		//###################################################################################  
		g_mtbl.off			= 0L;
		g_mtbl.lm			= (ULONG_PTR)g_pHandle;					// 06/02/06 ULONG=>ULONG_PTR������X
		g_mtbl.size			= m_dwAllocSize;
		g_mtbl.tableNum		= 0L;
		if( g_fRdyRL ){
			// Ach�ް�������滲���			ulSize			= ( ( g_FramePar.XSIZE * g_FramePar.YSIZE * g_FramePar.PIXBYTE ) * g_iFrmCnt );
			// Bch��p��������������ڽ
			g_ulRlStart		= ulSize;
			// Bch��p������̻����			g_ulRlSize		= ( ( g_FrameParB.XSIZE * g_FrameParB.YSIZE * g_FrameParB.PIXBYTE ) * g_iFrmCntB );
			lRet	= mgCreateMemoryTableEx( handle, &g_mtbl, ulSize, g_ulRlSize );
			wsprintf(ctemp,"Create Table Ex Error!!%x",lRet);
		/* Bch������p��s����\ */
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
	// 98,ME��������	else{
		// "��������S������g��p��s��������
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
	if(m_fAorD)		mgTempToMyHardware_A( handle, &m_AnalogPar);  // IPM-8540A����p
	// ��m������������������	g_bMem	= bMem;
//	maketable();
INITEND:
  return( fResult );
}
#endif

// ********************************************************************
// ۯ����������X
// ********************************************************************
void ChangeLockSize(HANDLE handle) 
{
	BOOL		result;
	LONG		lRet;
	HANDLE	hProcess;

	//###############################################
	//        �������۾�����AMۯ����������X
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
// �ӡ���J����// ********************************************************************
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
// 2ch����\��s����\������X
// ********************************************************************
void ChgRl()
{
	// 2ch��s����\��������������	if( !g_fRdyRL )	g_fEnbRL		= false;
	// 2ch����������������������//	if( g_pRFrm ){		g_pRFrm->ChgRl();}
	// �Ұ�����������u������X
//	if( g_pCFrm )		g_pCFrm->ChgRl();
}

// ********************************************************************
// �Ұ�޻����������// ********************************************************************
void SetImgSize()
{
	ULONG	ulFrmByte	= g_FramePar.XSIZE * g_FramePar.YSIZE * g_FramePar.PIXBYTE;
	// ������P��x����Z��o
	int	iMaxKido;
	// �ɸ�
	if((g_FramePar.TYPE & COLORMSK)==MONOTONE){
		iMaxKido	= (int)pow(2.0,(int)g_FramePar.PIXBIT)-1;
	// �ס�	} else {
		iMaxKido	= (int)pow(2.0,(int)(g_FramePar.PIXBIT/3))-1;
	}

	// �Ұ�������̻������X
//	if( g_pCView )		g_pCView->SetImgSize();
	// �ڡ����ޡ�������X��V
//	if( g_pTView )		g_pTView->SetImgSize();
	if( g_CL_M && g_fRdyRL){
//		if( g_pTViewB )		g_pTViewB->SetImgSize();
//		if( g_pRView )		g_pRView->SetImgSize();
//		if( g_pTFrmB )		g_pTFrmB->ChgRl();
	}
	return;
}

// ********************************************************************
// �ڰѡ�������������X��������
// ********************************************************************
void ChgFrmCnt(HANDLE handle, int iFrmCnt )
{
	DWORD	result;
	int		fbak = g_iFrmCnt;			// ��������������l����ޯ������//	CString	strMsg;
	// ����������m��������������	if(g_bMem){
		ExitProcess(handle);
	}
	g_iFrmCnt	= iFrmCnt;
	// ������ڰ����������z������������
	if( g_iFrmNo > g_iFrmCnt-1 )	g_iFrmNo	= g_iFrmCnt-1;
	// �ӡ�������m����	result = MemorySecure(handle);
	if(result = false){
		// "�ӡ�m��������s����������
//		strMsg.LoadString( IDS_ERR_MEM_GET );
//		MessageBox( strMsg );

		g_iFrmCnt = fbak;
		result = MemorySecure(handle);
		if(result = false){
			// "�ӡ�����m��������s����������I����������
//			strMsg.LoadString( IDS_ERR_MEMGET_END );
//			MessageBox( strMsg );
//			OnExit();
		}
	}
	else{
		// ������������X��V
//		m_DlgReview.ChgFrmCnt();
	}
}

// ********************************************************************
// ��I����������
// ********************************************************************
void ExitProcess(HANDLE handle) 
{
	//###############################################
	//    ����z���ڡ�������޺Я�������������ӡ���m����
	//    ����z���ڡ�������J����  
	//###############################################
	if(g_osVer.dwPlatformId==VER_PLATFORM_WIN32_NT){
		UnlockMem();
		FreeMem();
	}
	ChangeLockSize(handle);	
}

// ********************************************************************
// �ӡ���nlock
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
// �������ڡ���������������������
//*********************************************************************
//UINT  GrabThread(LPVOID Prm)
UINT  GrabThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;
	// ������������������	pWnd->GrabPrc();
*/
	// ������]������������	if( !g_fLoop )
		NormalPrc(handle);
	// ٰ�ߡ�]������������	else
		LoopPrc(handle);

	return( 0 );
}

// ********************************************************************
// ������]������������
// ********************************************************************
void NormalPrc(void *handle)
{
	DWORD		dwRet, dwRet2;
//	CString	strMsg;
	ULONG		ret;
	m_ulTim				= GetTickCount();								// ��J��������
	// ����ިݸ��������X��V
//	m_DlgShd.Enable( false );

	do {
		ret=ResetEvent(g_hEvent);
		g_Ov.hEvent		= g_hEvent;// OVERLAPPED����g����		g_ConvFlag		=	TRUE;
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
		// ��]������J���ס�		if( dwRet!=IPM_NOERROR )	break;

		// ��I��������//		dwRet2					= WaitForSingleObject(g_hEvent,INFINITE);
		dwRet2					= WaitForSingleObject(g_hEvent,IGNORE);
		
		if( dwRet2==WAIT_OBJECT_0 ){
			// �������׸�
			if( m_fExit ){
				m_fContFlg	= false;
				break;
			}
			// ��`����������
//			g_pCView->DrawScreen();
//			DrawScreen();
		}
	// ��A����������������	} while( m_fContFlg );

/* D-20061116
	// ��������I����	g_fGrabber		= false;

	// ������I����	mgGrabberCancel( handle );

	// ײ����������ݷ����
	mgCancelLineIntWaitEvent( handle );

	// ����ިݸ��������X��V
//	m_DlgShd.Enable( TRUE );

	// ��]������J���ס�	if( dwRet!=IPM_NOERROR )
	{
//		strMsg.Format( "mgGrabberStart=%X", dwRet );
//		MessageBox( strMsg );
	}
*/
}

// ********************************************************************
// ٰ�ߡ�]������������
// ********************************************************************
void LoopPrc(void *handle)
{
	DWORD		dwRet;
	BOOL		fFirstFrm;		// ����������ڰ����\���׸�
	ULONG		ulLine;				// ������������s����
	ULONG		ulFrmCnt;			// ������������ڰ����
	ULONG		ulFrmNo;			// ��\��������ڰ������
	BOOL		fStatus		= TRUE;
//	CString	strMsg;
	ULONG		ulIntCnt;			// ����������������
	ULONG		ret;
	// ����������ڰ����\���׸�
	fFirstFrm			= TRUE;

	// ����������������
	ulIntCnt			= 0;

	// ������������������\����������X��V
//	m_DlgSetLoop.Enable( false );
	// ����ިݸ��������X��V
//	m_DlgShd.Enable( false );

	m_ulTim				= GetTickCount();								// ��J��������
	do {
		// ײ����������������		ret=ResetEvent(g_hLocalEvent);
		// ��]������J����������		m_fLoopIntEnb	= TRUE;

		if(m_dwTimeout){
			dwRet					= WaitForSingleObject(g_hLocalEvent,m_dwTimeout);
		}
		else{
			dwRet					= WaitForSingleObject(g_hLocalEvent,INFINITE);
		}

		if( dwRet==WAIT_OBJECT_0 ){
			// �������׸�
			if( m_fExit ){
				m_fContFlg	= false;
				break;
			}
/*
			// --------------------------------
			// ��������������������\��
			// --------------------------------
			ulIntCnt++;
			m_DlgSetLoop.DspCnt( g_ulIntCnt, ulIntCnt );

			// ��\���ڰѡ���������Z��o
			ulLine		= (g_ulIntCnt-1) * g_ulLineCnt;
			ulFrmCnt	= ulLine / g_FramePar.YSIZE;
			ulFrmNo		= ulFrmCnt==0 ? 0 : ulFrmCnt-1;
			ulFrmNo		= ulFrmNo % g_iFrmCnt;

			// ��\����������ڰ������������������A����������ڰ��������			if( g_iFrmNo != (int)ulFrmNo || fFirstFrm ){
				g_iFrmNo	= ulFrmNo;
				// ��`����������
				g_pCView->DrawScreen();
			}

			// �ڰѡ���������Q�ڰѡ���������			if( g_iFrmNo > 0 ){
				// ����������ڰ����A��\��������				fFirstFrm	= false;
			}
*/
		}
		else {
			// ��`����������
//			g_pCView->DrawScreen();
			mgGrabberCancel( handle );			// ������I����			m_fContFlg	= false;
			fStatus			= false;
			// "��ѱ�ġ�����
//			strMsg.LoadString( IDS_ERR_TIMEOUT );
			break;
		}
	// ��A����������������	} while( m_fContFlg );

	// ��������I����	g_fGrabber		= false;

	// ������I����	mgGrabberCancel( handle );

	// ײ����������ݷ����
	mgCancelLineIntWaitEvent( handle );

	// ������������������\����������X��V
//	m_DlgSetLoop.Enable( TRUE );
	// ����ިݸ��������X��V
//	m_DlgShd.Enable( TRUE );

	// �װҡ�������\��
	if( !fStatus ){
//		MessageBox( strMsg );
	}
}

//*********************************************************************
// ٰ�ߡ�����]������J���ڡ���//*********************************************************************
//UINT  LoopStartThread(LPVOID Prm)
//UINT  LoopStartThread()
UINT  LoopStartThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;

	// ٰ�ߡ���]������J��������������	pWnd->LoopStartPrc();
*/
	LoopStartPrc(handle);
	return( 0 );
}

// ********************************************************************
// ٰ�ߡ���]������J����������
// ********************************************************************
void LoopStartPrc(void *handle)
{
	DWORD		dwRet;
//	CString	strMsg;

	// ��]������J��������	while( !m_fLoopStartEnb )		Sleep(1);

	// Grabber ��J��
		dwRet	= mgGrabberStart( handle, &g_FramePar, &g_mtbl, NULL,
							MGGRAB_INFINITE, 1L, g_iFrmCnt, 0, (PVOID)0L );

	// ��]������J���ס�	if( dwRet!=IPM_NOERROR ){

		// ������I����		mgGrabberCancel( handle );

		// ײ����������ݷ����
		mgCancelLineIntWaitEvent( handle );

		// 2ch������		if( !g_fEnbRL ){
//			strMsg.Format( "mgGrabberStart=%X", dwRet );
		}
//		MessageBox( strMsg );
	}
}

//*********************************************************************
// ٰ�ߡ����������������������Ľڡ���//*********************************************************************
//UINT  LoopIntCntThread(LPVOID Prm)
UINT  LoopIntCntThread(void *handle)
{
/*
	CMainFrame	*pWnd		= (CMainFrame*)Prm;
	// ٰ�ߡ��������������������ġ�����������	pWnd->LoopIntCntPrc();
*/
	LoopIntCntPrc(handle);
	return( 0 );
}

// ********************************************************************
// ٰ�ߡ������������������ġ�������
// ********************************************************************
void LoopIntCntPrc(void *handle)
{
	DWORD		dwRet;
	ULONG		ret;
	// ����������������
	g_ulIntCnt		= 0;

	// ���ݡ�����	g_Ov.hEvent		= g_hEvent;

	// ������������������J��������	while( !m_fLoopIntEnb )		Sleep(1);

	do {
		ret=ResetEvent(g_hEvent);
		// ײ��������������J��
		mgSetLineIntWaitEvent( handle, &g_Ov );
		// ��]������J����������		m_fLoopStartEnb	= TRUE;
		// ײ����������������		if(m_dwTimeout){
			dwRet					= WaitForSingleObject(g_hEvent,m_dwTimeout);
		}
		else{
			dwRet					= WaitForSingleObject(g_hEvent,INFINITE);
		}

		if( dwRet==WAIT_OBJECT_0 ){
			// �������׸�
			if( m_fExit ){
				SetEvent( g_hLocalEvent );
				break;
			}
			// ����������������
			g_ulIntCnt++;
			SetEvent( g_hLocalEvent );
		}
		else {
			SetEvent( g_hLocalEvent );
			break;
		}
	// ��A����������������	} while( m_fContFlg );
}
/*
// ********************************************************************
// ��I����// ********************************************************************
void OnExit() 
{
	DWORD lret;
	CHAR *myFile;

	// ��������
	if( g_fGrabber ){
		// �������׸�
		m_fExit			= TRUE;
		// ��A���������׸�
		m_fContFlg	= false;
		// ������I����		mgGrabberCancel( handle );
	}
/*
	// ��������
	if( g_fGrabber_B ){
		// �������׸�
		m_fExit_B			= TRUE;
		// ��A���������׸�
		m_fContFlg_B	= false;
		// ������I����		mgGrabberCancelB( handle );
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
		mgTempToMyHardware_A( handle, &m_AnalogPar);  // IPM-8540A����p
}
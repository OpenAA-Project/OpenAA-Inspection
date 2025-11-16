#ifndef _GLOBAL_H_

#define	_GLOBAL_H_

#include "ChildFrm.h"
#include "ChildView.h"					// ｲﾒｰｼﾞﾋﾞｭｰ
#include "TFrm.h"								// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
#include "TView.h"							// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
#include "TFrmB.h"								// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
#include "TViewB.h"							// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
#include "RFrm.h"								// ﾗﾝﾚﾝｸﾞｽﾌﾚｰﾑ
#include "RView.h"							// ﾗﾝﾚﾝｸﾞﾋﾞｭｰ
#include "MainFrm.h"						// ﾒｲﾝﾌﾚｰﾑ
#include "ShdFrm.h"							// ｼｪｰﾃﾞｨﾝｸﾞﾌﾚｰﾑ
#include "ShdView.h"						// ｼｪｰﾃﾞｨﾝｸﾞﾋﾞｭｰ
#include "DlgShd.h"							// ｼｪｰﾃﾞｨﾝｸﾞ編集
#include "DlgSaveRect.h"				// 指定領域保存
#include "AVIFunc.h"
// ====================================================================
// DEFINE定義
// ====================================================================
// ｽﾃｰﾀｽﾊﾞｰ各ﾍﾟｲﾝのｲﾝﾃﾞｯｸｽ
#define		ID_XSIZE			(1)			// ｲﾒｰｼﾞXSIZE
#define		ID_YSIZE			(2)			// ｲﾒｰｼﾞYSIZE
#define		ID_PIXBIT			(3)			// ｲﾒｰｼﾞPIXBIT
#define		ID_KIDO				(4)			// 輝度線位置
#define		ID_UPPER			(5)			// 上限値
#define		ID_LOWER			(6)			// 下限値
#define		ID_TIME				(7)			// 取込時間

#define		ID_XSIZE_B			(1)			// ｲﾒｰｼﾞXSIZE
#define		ID_YSIZE_B			(2)		// ｲﾒｰｼﾞYSIZE
#define		ID_PIXBIT_B			(3)			// ｲﾒｰｼﾞPIXBIT
#define		ID_KIDO_B			(4)			// 輝度線位置
#define		ID_UPPER_B			(5)			// 上限値
#define		ID_LOWER_B			(6)			// 下限値
#define		ID_TIME_B			(7)			// 取込時間

#define		SHD_SIZE				(16384)	// ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀｻｲｽﾞ
#define		SHD_SIZE_8530D	(4096)	// ｼｪｰﾃﾞｨﾝｸﾞﾃﾞｰﾀｻｲｽﾞ IPM-8530D

// ﾒｯｾｰｼﾞID
#define		WM_MENUCHG		(WM_USER + 0x100)	// MainFrame ﾒﾆｭｰ更新用
#define		WM_INIT_FRM		(WM_USER + 0x101)	// 各Frame 初期化用

#define		MASK_10BIT		(0x3ff)		// ｺﾞﾐ除去用
#define		MASK_12BIT		(0xfff)		// ｺﾞﾐ除去用
#define		MASK_14BIT		(0x3fff)		// ｺﾞﾐ除去用
#define		MASK_16BIT		(0xffff)		// ｺﾞﾐ除去用

// ====================================================================
// GLOBAL定義
// ====================================================================
#ifdef _MAIN_

BOOL					g_f8530					= FALSE;		// IPM-8530のﾌﾗｸﾞ
BOOL					g_f8530CL				= FALSE;		// IPM-8530CLのﾌﾗｸﾞ
BOOL					g_CL_B					= FALSE;
BOOL					g_CL_M					= FALSE;
BOOL					g_CL_F					= FALSE;
HANDLE					g_hDev					= NULL;			// IPMのﾃﾞﾊﾞｲｽﾊﾝﾄﾞﾙ
IPMFRAMEINFO			g_FramePar;									// ﾌﾚｰﾑ情報
IPMFRAMEINFO			g_FrameParB;									// ﾌﾚｰﾑ情報
IPMUSERMEMORY			g_mtbl;											// ﾒﾓﾘｰﾃｰﾌﾞﾙ
BYTE					*g_bMem					= NULL;			// ｲﾒｰｼﾞとﾗﾝﾚﾝｸﾞｽ領域
int						g_iFrmCnt				= 1;				// ﾌﾚｰﾑ枚数
int						g_iFrmNo				= 0;				// 現在表示中ﾌﾚｰﾑ番号
int						g_iFrmCntB				= 1;				// ﾌﾚｰﾑ枚数
int						g_iFrmNoB				= 0;				// 現在表示中ﾌﾚｰﾑ番号
CChildFrame				*g_pCFrm				= NULL;			// ｲﾒｰｼﾞﾌﾚｰﾑ
CChildView				*g_pCView				= NULL;			// ｲﾒｰｼﾞﾋﾞｭｰ
int						g_iKidoX				= 255;			// 輝度線の位置X
int						g_iKidoY				= 255;			// 輝度線の位置Y
int						g_iKidoBX				= 255;			// 輝度線の位置X
int						g_iKidoBY				= 255;			// 輝度線の位置Y
BOOL					g_fDspGraph				= FALSE;		// ｲﾒｰｼﾞ画面上での輝度ｸﾞﾗﾌ表示ﾌﾗｸﾞ
IPMVIEWPAR				g_ViewPar;									// ｲﾒｰｼﾞ画面上での表示領域
IPMVIEWPAR				g_ViewParB;									// ｲﾒｰｼﾞ画面上での表示領域
CTFrm					*g_pTFrm				= NULL;			// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
CTView					*g_pTView				= NULL;			// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
CTFrmB					*g_pTFrmB				= NULL;			// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
CTViewB					*g_pTViewB				= NULL;			// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
int						g_iUpper				= 0;				// 上限値
int						g_iLower				= 0;				// 下限値
int						g_iUpperB				= 0;				// 上限値
int						g_iLowerB				= 0;				// 下限値
BOOL					g_fUpMovMod				= FALSE;		// 上限値移動ﾓｰﾄﾞﾌﾗｸﾞ
BOOL					g_fLoMovMod				= FALSE;		// 下限値移動ﾓｰﾄﾞﾌﾗｸﾞ
BOOL					g_fUpMovMod_B				= FALSE;		// 上限値移動ﾓｰﾄﾞﾌﾗｸﾞ
BOOL					g_fLoMovMod_B				= FALSE;		// 下限値移動ﾓｰﾄﾞﾌﾗｸﾞ
CRFrm					*g_pRFrm				= NULL;			// ﾗﾝﾚﾝｸﾞｽﾌﾚｰﾑ
CRView					*g_pRView				= NULL;			// ﾗﾝﾚﾝｸﾞｽﾋﾞｭｰ
CMainFrame				*g_pMainFrm			= NULL;			// ﾒｲﾝﾌﾚｰﾑ(ｽﾃｰﾀｽﾊﾞｰ表示用)
BOOL					g_fSavePartFlg	= TRUE;			// 表示領域のみ保存ﾌﾗｸﾞ
BOOL					g_fDlgReview		= FALSE;		// 再生画面のOPEN
BOOL					g_fDlgReviewB		= FALSE;		// 再生画面のOPEN
BOOL					g_fRdyRL				= FALSE;		// ﾗﾝﾚﾝｸﾞｽ利用可能ﾌﾗｸﾞ
BOOL					g_fEnbRL				= TRUE;			// ﾗﾝﾚﾝｸﾞｽ処理のEnable
BOOL					g_fLoop					= FALSE;		// ﾙｰﾌﾟ動作ﾓｰﾄﾞ
BOOL					g_fLoop_B					= FALSE;		// ﾙｰﾌﾟ動作ﾓｰﾄﾞ
ULONG_PTR					g_ulRlStart			= NULL;			// ﾗﾝﾚﾝｸﾞｽ領域OFFSET
ULONG_PTR					g_ulRlSize			= 0;				// ﾗﾝﾚﾝｸﾞｽ領域ｻｲｽﾞ
ULONG					g_ulLineCnt			= 100;			// ﾗｲﾝ割込みの行数
ULONG					g_ulIntCnt			= 0;				// ﾗｲﾝ割込み回数
ULONG					g_ulLineCnt_B			= 100;			// ﾗｲﾝ割込みの行数
ULONG					g_ulIntCnt_B			= 0;				// ﾗｲﾝ割込み回数
BOOL					g_fGrabber			= FALSE;		// 取込中ﾌﾗｸﾞ
BOOL					g_fGrabber_B			= FALSE;		// 取込中ﾌﾗｸﾞ
CShdFrm					*g_pShdFrm			= NULL;			// ｼｪｰﾃﾞｨﾝｸﾞﾌﾚｰﾑ
CShdView				*g_pShdView			= NULL;			// ｼｪｰﾃﾞｨﾝｸﾞﾋﾞｭｰ
HANDLE					g_hShd					= NULL;			// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧ
long					*g_lShd					= NULL;			// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧ
ULONG					g_ulShdSize			= SHD_SIZE;	// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧｻｲｽﾞ
int						g_iShdLeft			= 0;				// ｼｪｰﾃﾞｨﾝｸﾞ編集範囲左
int						g_iShdRight			= 0;				// ｼｪｰﾃﾞｨﾝｸﾞ編集範囲右
CDlgShd					*g_pDlgShd			= NULL;			// ｼｪｰﾃﾞｨﾝｸﾞ編集画面
BOOL					g_fShdLeftMovMod	= FALSE;	// ｼｪｰﾃﾞｨﾝｸﾞ範囲左移動ﾓｰﾄﾞ
BOOL					g_fShdRightMovMod	= FALSE;	// ｼｪｰﾃﾞｨﾝｸﾞ範囲右移動ﾓｰﾄﾞ
CDlgSaveRect			*g_pDlgSaveRect	= NULL;			// 指定領域保存画面
BOOL					g_fSaveRect			= FALSE;		// 指定領域保存ﾓｰﾄﾞ
RECT					g_rcSaveRect;								// 指定領域保存領域
CString	rcvtext;
BOOL					g_CrsCursor			=TRUE;
CString					g_Config_A;
CString					g_Config_B;
BOOL					g_THScrollV_A	=TRUE;				//Ach側輝度値縦圧縮
BOOL					g_THScrollV_B	=TRUE;				//Bch側輝度値縦圧縮
BOOL					g_ConvFlag[65536];//	=FALSE;					//Convertフラグ
BOOL					g_AdjustFlag	=FALSE;				//Convertフラグ
BOOL					g_AdjustFlagB	=FALSE;				//Convertフラグ
BOOL					g_ConvFlagB[65536];//	=FALSE;					//Convertフラグ
BOOL					g_Gamma=FALSE;
BOOL					g_GammaB=FALSE;
BOOL					g_RGBset=FALSE;
BOOL					g_RGBsetB=FALSE;
UCHAR					tabler[256];							//ガンマ変換用テーブル
UCHAR					tableg[256];							//ガンマ変換用テーブル
UCHAR					tableb[256];							//ガンマ変換用テーブル
WORD					tabler2[65536];
WORD					tableg2[65536];
WORD					tableb2[65536];
WORD					table2[65536];
UCHAR					tablerb[256];							//ガンマ変換用テーブル
UCHAR					tablegb[256];							//ガンマ変換用テーブル
UCHAR					tablebb[256];							//ガンマ変換用テーブル
WORD					tablerb2[65536];
WORD					tablegb2[65536];
WORD					tablebb2[65536];
WORD					table2b[65536];
ULONG					g_fTrgA_A=0;
ULONG					g_fTrgA_B=0;
ULONG					g_fTrgB_A=0;
ULONG					g_fTrgB_B=0;

float	rgain=1.0;
float	ggain=1.0;
float	bgain=1.0;
short	roff=0;
short	goff=0;
short	boff=0;
float	rbgain=1.0;
float	gbgain=1.0;
float	bbgain=1.0;
short	rboff=0;
short	gboff=0;
short	bboff=0;


#else // _MAIN_

extern	BOOL			g_f8530;						// IPM-8530Dのﾌﾗｸﾞ
extern	BOOL			g_f8530CL;						// IPM-8530CLのﾌﾗｸﾞ
extern	BOOL			g_CL_B;
extern	BOOL			g_CL_M;
extern	BOOL			g_CL_F;
extern	HANDLE			g_hDev;							// IPMのﾃﾞﾊﾞｲｽﾊﾝﾄﾞﾙ
extern	IPMFRAMEINFO	g_FramePar;					// ﾌﾚｰﾑ情報
extern	IPMFRAMEINFO	g_FrameParB;					// ﾌﾚｰﾑ情報
extern	IPMUSERMEMORY	g_mtbl;							// ﾒﾓﾘｰﾃｰﾌﾞﾙ
extern	BYTE			*g_bMem;						// ｲﾒｰｼﾞとﾗﾝﾚﾝｸﾞｽ領域
extern	int				g_iFrmCnt;					// ﾌﾚｰﾑ枚数
extern	int				g_iFrmNo;						// 現在表示中ﾌﾚｰﾑ番号
extern	int				g_iFrmCntB;					// ﾌﾚｰﾑ枚数
extern	int				g_iFrmNoB;						// 現在表示中ﾌﾚｰﾑ番号
extern	CChildFrame		*g_pCFrm;						// ｲﾒｰｼﾞﾌﾚｰﾑ
extern	CChildView		*g_pCView;					// ｲﾒｰｼﾞﾋﾞｭｰ
extern	int				g_iKidoX;						// 輝度線の位置X
extern	int				g_iKidoY;						// 輝度線の位置Y
extern	int				g_iKidoBX;						// 輝度線の位置X
extern	int				g_iKidoBY;						// 輝度線の位置Y
extern	BOOL			g_fDspGraph;				// ｲﾒｰｼﾞ画面上での輝度ｸﾞﾗﾌ表示ﾌﾗｸﾞ
extern	IPMVIEWPAR		g_ViewPar;					// ｲﾒｰｼﾞ画面上での表示領域
extern	IPMVIEWPAR		g_ViewParB;					// ｲﾒｰｼﾞ画面上での表示領域
extern	CTFrm			*g_pTFrm;						// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
extern	CTView			*g_pTView;					// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
extern	CTFrmB			*g_pTFrmB;						// ｽﾚｯｼｮﾙﾄﾞﾌﾚｰﾑ
extern	CTViewB			*g_pTViewB;					// ｽﾚｯｼｮﾙﾄﾞﾋﾞｭｰ
extern	int				g_iUpper;						// 上限値
extern	int				g_iLower;						// 下限値
extern	int				g_iUpperB;						// 上限値
extern	int				g_iLowerB;						// 下限値
extern	BOOL			g_fUpMovMod;				// 上限値移動ﾓｰﾄﾞﾌﾗｸﾞ
extern	BOOL			g_fLoMovMod;				// 下限値移動ﾓｰﾄﾞﾌﾗｸﾞ
extern	BOOL			g_fUpMovMod_B;				// 上限値移動ﾓｰﾄﾞﾌﾗｸﾞ
extern	BOOL			g_fLoMovMod_B;				// 下限値移動ﾓｰﾄﾞﾌﾗｸﾞ
extern	CRFrm			*g_pRFrm;						// ﾗﾝﾚﾝｸﾞｽﾌﾚｰﾑ
extern	CRView			*g_pRView;					// ﾗﾝﾚﾝｸﾞｽﾋﾞｭｰ
extern	CMainFrame		*g_pMainFrm;				// ﾒｲﾝﾌﾚｰﾑ(ｽﾃｰﾀｽﾊﾞｰ表示用)
extern	BOOL			g_fSavePartFlg;			// 表示領域のみ保存ﾌﾗｸﾞ
extern	BOOL			g_fDlgReview;				// 再生画面のOPEN
extern	BOOL			g_fDlgReviewB;				// 再生画面のOPEN
extern	BOOL			g_fRdyRL;						// ﾗﾝﾚﾝｸﾞｽ利用可能ﾌﾗｸﾞ
extern	BOOL			g_fEnbRL;						// ﾗﾝﾚﾝｸﾞｽ処理のEnable
extern	BOOL			g_fLoop;						// ﾙｰﾌﾟ動作ﾓｰﾄﾞ
extern	BOOL			g_fLoop_B;						// ﾙｰﾌﾟ動作ﾓｰﾄﾞ
extern	ULONG_PTR			g_ulRlStart;				// ﾗﾝﾚﾝｸﾞｽ領域OFFSET
extern	ULONG_PTR			g_ulRlSize;					// ﾗﾝﾚﾝｸﾞｽ領域ｻｲｽﾞ
extern	ULONG			g_ulLineCnt;				// ﾗｲﾝ割込みの行数
extern	ULONG			g_ulIntCnt;					// ﾗｲﾝ割込み回数
extern	ULONG			g_ulLineCnt_B;				// ﾗｲﾝ割込みの行数
extern	ULONG			g_ulIntCnt_B;					// ﾗｲﾝ割込み回数
extern	BOOL			g_fGrabber;					// 取込中ﾌﾗｸﾞ
extern	BOOL			g_fGrabber_B;					// 取込中ﾌﾗｸﾞ
extern	CShdFrm			*g_pShdFrm;					// ｼｪｰﾃﾞｨﾝｸﾞﾌﾚｰﾑ
extern	CShdView		*g_pShdView;				// ｼｪｰﾃﾞｨﾝｸﾞﾋﾞｭｰ
extern	HANDLE			g_hShd;							// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧ
extern	long			*g_lShd;						// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧ
extern	ULONG			g_ulShdSize;				// ｼｪｰﾃﾞｨﾝｸﾞ用ﾊﾞｯﾌｧｻｲｽﾞ
extern	int				g_iShdLeft;					// ｼｪｰﾃﾞｨﾝｸﾞ編集範囲左
extern	int				g_iShdRight;				// ｼｪｰﾃﾞｨﾝｸﾞ編集範囲右
extern	CDlgShd			*g_pDlgShd;					// ｼｪｰﾃﾞｨﾝｸﾞ編集画面
extern	BOOL			g_fShdLeftMovMod;		// ｼｪｰﾃﾞｨﾝｸﾞ範囲左移動ﾓｰﾄﾞ
extern	BOOL			g_fShdRightMovMod;	// ｼｪｰﾃﾞｨﾝｸﾞ範囲右移動ﾓｰﾄﾞ
extern	CDlgSaveRect	*g_pDlgSaveRect;		// 指定領域保存画面
extern	BOOL			g_fSaveRect;				// 指定領域保存ﾓｰﾄﾞ
extern	RECT			g_rcSaveRect;				// 指定領域保存領域
extern	CString			g_SerialRecerve;
extern	BOOL			g_CrsCursor;				//ｸﾛｽｶｰｿﾙ表示
extern	CString			g_Config_A;					//Ach側ｶﾒﾗｺﾝﾌｨｸﾞ
extern	CString			g_Config_B;					//Bch側ｶﾒﾗｺﾝﾌｨｸﾞ
extern	BOOL			g_THScrollV_A;				//Ach側輝度値縦圧縮
extern	BOOL			g_THScrollV_B;				//Bch側輝度値縦圧縮
extern	BOOL			g_ConvFlag[65536];					//Convertフラグ
extern	BOOL			g_AdjustFlag;					//Convertフラグ
extern	BOOL			g_AdjustFlagB;					//Convertフラグ
extern	BOOL			g_ConvFlagB[65536];					//Convertフラグ
extern	BOOL			g_Gamma;
extern	BOOL			g_GammaB;
extern	BOOL			g_RGBset;
extern	BOOL			g_RGBsetB;
extern		float	rgain,ggain,bgain;
extern		short	roff,goff,boff;
extern		float	rbgain,gbgain,bbgain;
extern		short	rboff,gboff,bboff;
extern	UCHAR		tabler[256];
extern	UCHAR		tableg[256];
extern	UCHAR		tableb[256];
extern	WORD					tabler2[65536];
extern	WORD					tableg2[65536];
extern	WORD					tableb2[65536];
extern	WORD					table2[65536];
extern	UCHAR		tablerb[256];
extern	UCHAR		tablegb[256];
extern	UCHAR		tablebb[256];
extern	WORD					tablerb2[65536];
extern	WORD					tablegb2[65536];
extern	WORD					tablebb2[65536];
extern	WORD					table2b[65536];
extern	ULONG					g_fTrgA_A;
extern	ULONG					g_fTrgA_B;
extern	ULONG					g_fTrgB_A;
extern	ULONG					g_fTrgB_B;

#endif // _MAIN_

#endif // _GLOBAL_H_

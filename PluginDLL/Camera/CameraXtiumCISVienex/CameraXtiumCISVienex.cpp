/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtiumCISVienex\CameraXtiumCISVienex.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumCISVienex.h"
#include "saperaCtrl.h"
#include "CameraSettingDialog.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"
#include "XGUIFormBase.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
//#define	DEF_CONFIG_DEFAULT_PATH		/**/"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		/**/"VienexNVB300CL-F.ccf"

QFile debugFile(/**/"CameraDebug.txt");
QTextStream debugStream;

QString		ProofDataFile;
bool		pbProofFlag;
bool		pbProofCancelFlag;


bool debugInit()
{
	static QMutex mutex;
	static bool ok = false;
	static bool initialized = false;

	QMutexLocker locker(&mutex);
	
	if(initialized==true){
		return true;
	}
	if(debugFile.isOpen()==false){
		ok = debugFile.open(QIODevice::WriteOnly);
	}else{
		ok = true;
	}
	if(ok==true && debugFile.isOpen()==true && debugStream.device()==NULL){
		debugStream.setDevice(&debugFile);
		ok = true;
	}

	if(ok==true){
		initialized = true;
	}
	ProofDataFile = DEF_CONFIG_DEFAULT_PATH;

	return ok;
}

void debugOutput(const QString &txt, int deviceID)
{
	static QMutex mutex;
	QMutexLocker locker(&mutex);
	if(debugStream.device()!=NULL){
		QString str(QString::number(deviceID) + /**/" : ");
		str += txt;
		debugStream << QString(/**/"%1%2%3").arg(str).arg(QChar(0x0D)).arg(QChar(0x0A));
	}
}

CameraXtiumCISVienex::CameraXtiumCISVienex(int CamNo ,LayersBase *base)
	:AbstructOriginateClass(true),CameraHandle(CamNo,base)
	,CISVienexData(this)
{
	MatrixRX	=NULL;
	MatrixGX	=NULL;
	MatrixBX	=NULL;

	GainOffsetTableRL=NULL;
	GainOffsetTableGL=NULL;
	GainOffsetTableBL=NULL;
	GainOffsetTableRR=NULL;
	GainOffsetTableGR=NULL;
	GainOffsetTableBR=NULL;
	CamDotPerLine=-1;

	_Acq		= NULL;
	_AcqDevice	= NULL;
	_Buffers	= NULL;
	_Xfer		= NULL;
	_View		= NULL;
	_Bayer		= NULL;
	_FeatureInfo= NULL;
	_Gio		= NULL;
	_bLinked	= false;
	//_nStatus	= EN_CTRLSTS_IDLE;		// §Œä—p
	_nGioDev	= 0;
	_nStartReserve = 0;
	fc			=NULL;
	GCount		=1;
	//CurrentGPos	=0;
	LineValid	=true;
	Calibrated	=false;

	Terminated	=false;
	Halted		=false;
	RepeatON	=true;

	//setPriority(QThread::HighPriority);
}

CameraXtiumCISVienex::~CameraXtiumCISVienex(void)
{
	//Terminated=true;
	//wait(1000);

	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
		MatrixRX=NULL;
	}
	if(MatrixGX!=NULL){
		delete	[]MatrixGX;
		MatrixGX=NULL;
	}
	if(MatrixBX!=NULL){
		delete	[]MatrixBX;
		MatrixBX=NULL;
	}

	if(GainOffsetTableRL!=NULL){
		delete	[]GainOffsetTableRL;
		GainOffsetTableRL=NULL;
	}
	if(GainOffsetTableRR!=NULL){
		delete	[]GainOffsetTableRR;
		GainOffsetTableRR=NULL;
	}
	if(GainOffsetTableGL!=NULL){
		delete	[]GainOffsetTableGL;
		GainOffsetTableGL=NULL;
	}
	if(GainOffsetTableGR!=NULL){
		delete	[]GainOffsetTableGR;
		GainOffsetTableGR=NULL;
	}
	if(GainOffsetTableBL!=NULL){
		delete	[]GainOffsetTableBL;
		GainOffsetTableBL=NULL;
	}
	if(GainOffsetTableBR!=NULL){
		delete	[]GainOffsetTableBR;
		GainOffsetTableBR=NULL;
	}
}
void	CameraXtiumCISVienex::InitialXTable(void)
{
	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
		MatrixRX=NULL;
	}
	if(MatrixGX!=NULL){
		delete	[]MatrixGX;
		MatrixGX=NULL;
	}
	if(MatrixBX!=NULL){
		delete	[]MatrixBX;
		MatrixBX=NULL;
	}


	MatrixRX=new int[CamDotPerLine];
	MatrixGX=new int[CamDotPerLine];
	MatrixBX=new int[CamDotPerLine];

	for(int x=0;x<CamDotPerLine;x++){
		double	X=x;
		double	kr=(X-Setting.OffsetXRed	)/Setting.MultipleRed	;
		MatrixRX[x]		=Clipping((int)kr ,0 ,CamDotPerLine-1)*4+2;
		double	kg=(X-Setting.OffsetXGreen	)/Setting.MultipleGreen	;
		MatrixGX[x]		=Clipping((int)kg ,0 ,CamDotPerLine-1)*4+2;
		double	kb=(X-Setting.OffsetXBlue	)/Setting.MultipleBlue	;
		MatrixBX[x]		=Clipping((int)kb ,0 ,CamDotPerLine-1)*4+2;

	}
	GainOffsetTableRL=new BYTE[256];
	GainOffsetTableRR=new BYTE[256];
	GainOffsetTableGL=new BYTE[256];
	GainOffsetTableGR=new BYTE[256];
	GainOffsetTableBL=new BYTE[256];
	GainOffsetTableBR=new BYTE[256];
	for(int i=0;i<256;i++){
		GainOffsetTableRL[i]=Clipping((int)(i*Setting.GainRedL	+Setting.OffsetRedL		),0,255);
		GainOffsetTableRR[i]=Clipping((int)(i*Setting.GainRedR	+Setting.OffsetRedR		),0,255);
		GainOffsetTableGL[i]=Clipping((int)(i*Setting.GainGreenL+Setting.OffsetGreenL	),0,255);
		GainOffsetTableGR[i]=Clipping((int)(i*Setting.GainGreenR+Setting.OffsetGreenR	),0,255);
		GainOffsetTableBL[i]=Clipping((int)(i*Setting.GainBlueL	+Setting.OffsetBlueL	),0,255);
		GainOffsetTableBR[i]=Clipping((int)(i*Setting.GainBlueR	+Setting.OffsetBlueR	),0,255);
	}
}


void	CameraXtiumCISVienex::AfterPrepare(void)
{
}
void	CameraXtiumCISVienex::AfterStartSequence(void)
{
}

void	CameraXtiumCISVienex::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	CameraXtiumCISVienex::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
}
void	CameraXtiumCISVienex::ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)
{
}

bool	CameraXtiumCISVienex::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver	)==false)
		return false;
	if(Setting.Load(f)		==false)	return false;
	if(CISVienexData.Load(f)==false)	return false;

	return true;
}
bool	CameraXtiumCISVienex::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver	)==false)
		return false;
	if(Setting.Save(f)		==false)	return false;
	if(CISVienexData.Save(f)==false)	return false;
	return true;
}


/* ////////////////////////////////////////////////////////////////////////////////////////////////
 DLL FUNCTIONS
//////////////////////////////////////////////////////////////////////////////////////////////// */
WORD DLL_GetDLLType(void)
//	return	DLL type for CameraDLL
{
	return(DLLCameraMode);
}

bool cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str=/**/"Vienex CIS NVB300CL-F";
	return(true);
}

WORD _cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

extern int cameraCallbackCount;

/*
   make
   */
CameraHandle *_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	static bool first = true;

	int deviceID = CameraNoInThisComputer+1;

	if (first==false) return NULL;

	first = false;
	debugInit();
	debugOutput(/**/"DLL_Initial", deviceID);

	CameraXtiumCISVienex	*Px=new CameraXtiumCISVienex(CameraNoInThisComputer,base);


	QString	path=base->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+::GetSeparator()+ProofDataFile;

	QByteArray str_arr = FileName.toLocal8Bit();
	const char* c_str = str_arr.constData();
	if(Px->link((char*)c_str)==false){
		CamInfo.ErrorCode=1;	//ErrorCode
		return NULL;
	}

	Px->DeviceID	=CameraNoInThisComputer;
	Px->InitialXTable();
	Px->CISVienexData.LoadFromROMonCam();
	return Px;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	//if(Px!=NULL){
	//	Px->CISVienexData.LoadFromCam();
	//}
	bool	Ret=Px->Setting.Load(&str);
	if(Ret==true){
		Ret=Px->CISVienexData.Load(&str);
		if(Ret==true){
			if(Px->Setting.CameraControl==true){
				Ret=Px->CISVienexData.StoreToCam();
			}
		}
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	bool	Ret=Px->Setting.Save(&str);
	if(Ret==true){
		Ret=Px->CISVienexData.Save(&str);
	}
	return Ret;
}


DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	bool	Ret=Px->ChangeLineCount(caminfo.XLen,caminfo.YLen,caminfo.LayerNumber);

	if(Ret==true){
		Px->startCapture();
		//Px->_sapera->ClearCenterLine();
	}

	return Ret;
}

bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	CameraSettingDialog SettingDialog(Px);
	if(SettingDialog.exec()==false)
		return(false);
	Px->InitialXTable();
	return(true);
}

bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	return  Px->prepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	return Px->startCapture();
}

/*
   make
   ‚¨‚»‚ç‚­‚»‚Ì‚Ü‚Ü
   */
bool _cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;

	 Px->stopCapture();
	return true;	//Px->_sapera->unlink();
}

int _cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;

	return Px->getStatusInside();
}

bool _cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool _cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[],int BufferDimCounts,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	Px->GetImage(Buff,BufferDimCounts,Info);
}
DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	//CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	//CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	//if(CmdGetStockedCountVar!=NULL){
	//	CmdGetStockedCountVar->Count=Px->_sapera->CurrentWTop;
	//	return;
	//}
	//CmdSetImageToTarget	*CmdSetImageToTargetVar=dynamic_cast<CmdSetImageToTarget *>(packet);
	//if(CmdSetImageToTargetVar!=NULL){
	//	ImageBuffer	&Tb=Px->GetLayersBase()->GetPageData(0)->GetLayerData(0)->GetTargetBuff();
	//	Tb=Px->_sapera->ImageStack[CmdSetImageToTargetVar->Number];
	//	return;
	//}

}

DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base)
{
	CameraXtiumCISVienex	*Px=(CameraXtiumCISVienex *)handle;
	Px->InitialXTable();
	return _ER_true;
}

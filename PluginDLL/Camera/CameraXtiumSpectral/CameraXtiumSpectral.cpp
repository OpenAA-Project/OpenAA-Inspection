/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtiumSpectral\CameraXtiumSpectral.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumSpectral.h"
#include "saperaCtrl.h"
#include "SettingCameraDialog.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "ThreadSequence.h"
//#include "XSequenceLocal.h"
//#include "XExecuteInspectBase.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
//#define	DEF_CONFIG_DEFAULT_PATH		"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		"T_PX-HM-16K12T-00-R_LineFrameTrigger.ccf"


QFile debugFile("CameraDebug.txt");
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
		debugStream << QString("%1%2%3").arg(str).arg(QChar(0x0D)).arg(QChar(0x0A));
	}
}

CameraXtiumSpectral::CameraXtiumSpectral(int CamNo ,LayersBase *base ,bool original=false)
	:QObject(base->GetMainWidget())
	,AbstructOriginateClass(original)
	,CameraHandle(CamNo,base)
{
	_sapera	= new saperaCtrl(CamNo,base,this);

	CamDotPerLine=-1;
	LoadFirst	=true;
}

CameraXtiumSpectral::~CameraXtiumSpectral()
{
	if (_sapera) {
		delete _sapera;
		_sapera = NULL;
	}
}
bool	CameraXtiumSpectral::Reset(void)
{
	if(_sapera!=NULL){
		_sapera->Reset();
		return true;
	}
	return false;
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
	str="Piranha XL Mono PX-MC-16K12T-00-R";
	return(true);
}

WORD _cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
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
	int ret;

	int deviceID = CameraNoInThisComputer+1;

	if (first==false) return NULL;

	first = false;
	debugInit();
	debugOutput("DLL_Initial", deviceID);

	CameraXtiumSpectral		*Px=new CameraXtiumSpectral(CameraNoInThisComputer,base);

	QString	path=base->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+/**/QString("\\")+ProofDataFile;

	QByteArray str_arr = FileName.replace('/',"\\").toLocal8Bit();
	const char* c_str = str_arr.constData();
	if(Px->_sapera->link((char*)c_str)==false){
		CamInfo.ErrorCode=1;	//ErrorCode
		return NULL;
	}

	Px->DeviceID	=CameraNoInThisComputer;
	return Px;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		Ret=Px->Setting.Load(&str);
		Px->LoadFirst=false;

		//Px->_sapera->ControlCamera();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Px->Setting.Save(&Buff);
		Px->Setting.LoadFromCam(Px->_sapera->fc);
		Buff.seek(0);
		Px->Setting.Load(&Buff);

		if(Ret==true){
			Ret=Px->Setting.StoreToCam(Px->_sapera->fc);
		}
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	return Px->Setting.Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	bool	Ret=Px->_sapera->ChangeLineCount(caminfo.YLen);

	if(Ret==true){
		Px->_sapera->startCapture();
		//Px->_sapera->ClearCenterLine();
	}

	return Ret;
}

bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	SettingCameraDialog SettingDialog(&Px->Setting, Px->_sapera->fc);
	if(SettingDialog.exec()==false)
		return(false);
	return(true);
}

//bool	_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue)
//{
//	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
//	return Px->Setting.SetQuickProperty(Px->_sapera->fc,Attr, RelativeValue);
//}


bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	return  Px->_sapera->prepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	return Px->_sapera->startCapture();
}



bool _cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;

	 Px->_sapera->stopCapture();
	return true;	//Px->_sapera->unlink();
}

DEFFUNCEX	int _cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	int	Ret=Px->_sapera->getStatus();
	return Ret;
}

bool _cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool _cdecl	DLL_GetImageTR(CameraHandle *handle ,ImageBuffer *Buff[],ImageBuffer *TRBuff[],int BufferDimCounts,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	Px->_sapera->getImage(Buff,TRBuff);
	return true;
}
DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraXtiumSpectral	*Px=(CameraXtiumSpectral *)handle;
	CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	if(CmdGetStockedCountVar!=NULL){
		CmdGetStockedCountVar->Count=Px->_sapera->CurrentWTop;
		return;
	}
}
DEFFUNCEX	void		_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v)
{
	CameraXtiumSpectral	*Px=(CameraXtiumSpectral *)handle;
	SpecifiedBroadcasterSendResetCamera	*f=dynamic_cast<SpecifiedBroadcasterSendResetCamera *>(v);
	if(f!=NULL){
		Px->Reset();
		return;
	}
}

DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base)
{
	CameraXtiumSpectral		*Px=(CameraXtiumSpectral *)handle;
	return _ER_true;
}

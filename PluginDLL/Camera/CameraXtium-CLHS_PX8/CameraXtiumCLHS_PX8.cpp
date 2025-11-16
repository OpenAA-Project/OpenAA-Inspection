/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraMightex\CameraMightex\CameraMightex.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumCLHS_PX8.h"
#include "saperaCtrl.h"
#include "CameraSetting.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
//#define	DEF_CONFIG_DEFAULT_PATH		"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		"T_PX-HC-16K04T-00-R_Default_Default.ccf"


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

CameraXtiumCLHS_PX8::CameraXtiumCLHS_PX8(int CamNo ,LayersBase *base ,bool original=false)
	:AbstructOriginateClass(original),CameraHandle(CamNo,base)
{
	_sapera	= new saperaCtrl(CamNo,base);
}

CameraXtiumCLHS_PX8::~CameraXtiumCLHS_PX8()
{
	if (_sapera) {
		delete _sapera;
		_sapera = NULL;
	}
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
	str="Piranha XL Color PX-HC-16K04T-00-R";
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
CameraHandle *_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base, CameraReqInfo &CamInfo,const QString &CameraParameter)
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
	debugOutput("DLL_Initial", deviceID);

	CameraXtiumCLHS_PX8		*Px=new CameraXtiumCLHS_PX8(CameraNoInThisComputer,base);

	QByteArray str_arr = ProofDataFile.toLocal8Bit();
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
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	if(Px!=NULL){
		Px->Setting.LoadFromCam(Px->_sapera->fc);
	}
	bool	Ret=Px->Setting.Load(&str);
	if(Ret==true){
		
		Ret=Px->Setting.StoreToCam(Px->_sapera->fc);
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	return Px->Setting.Save(&str);
}


bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	CameraSetting SettingDialog(&Px->Setting, Px->_sapera->fc);
	if(SettingDialog.exec()==false)
		return(false);

	return(true);
}

bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	return  Px->_sapera->prepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	return Px->_sapera->startCapture();
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
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;

	 Px->_sapera->stopCapture();
	return Px->_sapera->unlink();
}

int _cdecl	DLL_GetStatus(CameraHandle *handle,CameraScanInfo *Info)
//	Return camera status
//		return :	Bit0		1:Preparing for capturing
//					Bit1		1:Waiting for Frame(Line) trigger
//					Bit2		1:Transmitting image data by DMA
//					Bit3		1:Over-run error occured. Error bit must be kept till DLL_ClearError function
//					Bit4		1:Other error occured.  Error bit must be kept till DLL_ClearError function
{
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	debugOutput("DLL_GetStatus", Px->DeviceID);

	return Px->_sapera->getStatus();
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
	CameraXtiumCLHS_PX8		*Px=(CameraXtiumCLHS_PX8 *)handle;
	return Px->_sapera->getImage(Buff);
}

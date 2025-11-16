#include "CameraXtiumPx8MonoLineTriggerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtiumPx8MonoLineTrigger\CameraXtiumPx8MonoLineTrigger.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumPx8MonoLineTrigger.h"
#include "saperaCtrl.h"
#include "CameraSetting.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
//#define	DEF_CONFIG_DEFAULT_PATH		/**/"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		/**/"T_PX-HM-16K12T-00-R_LineFrameTrigger.ccf"

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

CameraXtiumPx8MonoLineTrigger::CameraXtiumPx8MonoLineTrigger(int CamNo ,LayersBase *base ,bool original=false)
	:AbstructOriginateClass(original),CameraHandle(CamNo,base)
{
	ioLightControlEnable=NULL;
	ioLightControlOFF	=NULL;

	_sapera	= new saperaCtrl(CamNo,base,this);
	MatrixRX=NULL;
	MatrixRXTR=NULL;
	GainOffsetTableRL=NULL;
	GainOffsetTableRR=NULL;
	CamDotPerLine=-1;
	ColorAllocation=false;
	AllocatedColor=qRgb(255,255,210);
}

CameraXtiumPx8MonoLineTrigger::~CameraXtiumPx8MonoLineTrigger()
{
	if (_sapera) {
		delete _sapera;
		_sapera = NULL;
	}
	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
		MatrixRX=NULL;
	}
	if(MatrixRXTR!=NULL){
		delete	[]MatrixRXTR;
		MatrixRXTR=NULL;
	}
	if(GainOffsetTableRL!=NULL){
		delete	[]GainOffsetTableRL;
		GainOffsetTableRL=NULL;
	}
	if(GainOffsetTableRR!=NULL){
		delete	[]GainOffsetTableRR;
		GainOffsetTableRR=NULL;
	}

}
void	CameraXtiumPx8MonoLineTrigger::InitialXTable(void)
{
	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
	}

	if(MatrixRXTR!=NULL){
		delete	[]MatrixRXTR;
	}

	MatrixRX=new int[CamDotPerLine];
	MatrixRXTR=new int[CamDotPerLine];

	for(int x=0;x<CamDotPerLine;x++){
		double	X=x;
		double	kr=(X-Setting.OffsetXRed	)/Setting.MultipleRed	;
		MatrixRX[x]		=Clipping((int)kr ,0 ,CamDotPerLine-1)*4+2;
		MatrixRXTR[x]	=Clipping((int)kr ,0 ,GetDotPerLine()-1);
	}
	GainOffsetTableRL=new BYTE[256];
	GainOffsetTableRR=new BYTE[256];
	for(int i=0;i<256;i++){
		GainOffsetTableRL[i]=Clipping((int)(i*Setting.GainRedL	+Setting.OffsetRedL	),0,255);
		GainOffsetTableRR[i]=Clipping((int)(i*Setting.GainRedR	+Setting.OffsetRedR	),0,255);
	}
}

void	CameraXtiumPx8MonoLineTrigger::AfterPrepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioLightControlOFF		=new SignalOperandBit(this,295,"LightControl bit");
			ioLightControlEnable	=new SignalOperandBit(this,296,"LightControl Enable");
			ioLightControlOFF		->Set(false);
			ioLightControlEnable		->Set(false);

			Param->SetSpecialOperand(ioLightControlOFF);
			Param->SetSpecialOperand(ioLightControlEnable);
		}
	}
}
void	CameraXtiumPx8MonoLineTrigger::AfterStartSequence(void)
{
	if(ioLightControlEnable!=NULL){
		if(ioLightControlEnable->Get()==true){
			Calibrate();
		}
	}
}
void	CameraXtiumPx8MonoLineTrigger::Calibrate(void)
{
	if(ioLightControlEnable!=NULL){
		_sapera->Calibrated=false;
		_sapera->SetCalibration();
		ioLightControlEnable->Set(false);
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
	str=/**/"Piranha XL Color PX-HM-16K12T-00-R";
	return(true);
}

WORD _cdecl	DLL_GetVersion(void)
//	return Camera DLL version
{
	return(1);
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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

	CameraXtiumPx8MonoLineTrigger	*Px=new CameraXtiumPx8MonoLineTrigger(CameraNoInThisComputer,base);

	if(CameraParameter==/**/"ColorAllocation")
		Px->ColorAllocation=true;

	QString	path=base->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+::GetSeparator()+ProofDataFile;

	QByteArray str_arr = FileName.toLocal8Bit();
	const char* c_str = str_arr.constData();
	if(Px->_sapera->link((char*)c_str)==false){
		CamInfo.ErrorCode=1;	//ErrorCode
		return NULL;
	}

	Px->DeviceID	=CameraNoInThisComputer;
	Px->InitialXTable();
	return Px;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
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
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	return Px->Setting.Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
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
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	CameraSetting SettingDialog(&Px->Setting, Px->_sapera->fc);
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
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	return  Px->_sapera->prepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	return Px->_sapera->startCapture();
}

/*
   make
   おそらくそのまま
   */
bool _cdecl	DLL_HaltCapture(CameraHandle *handle)
//	Halt to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;

	 Px->_sapera->stopCapture();
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
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;

	return Px->_sapera->getStatus();
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
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	if(Px->ColorAllocation==true && BufferDimCounts==3){
		Px->_sapera->getImage(Buff[0],TRBuff[0]);
		BYTE	ColTable[3];
		ColTable[0]=Px->AllocatedColor.red();
		ColTable[1]=Px->AllocatedColor.green();
		ColTable[2]=Px->AllocatedColor.blue();
		Px->ExecuteColorAllocation(Buff,BufferDimCounts,ColTable);
		return true;
	}
	else{
		return Px->_sapera->getImage(Buff[0],TRBuff[0]);
	}
}
DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	if(CmdGetStockedCountVar!=NULL){
		CmdGetStockedCountVar->Count=Px->_sapera->CurrentWTop;
		return;
	}
	CmdSetImageToTarget	*CmdSetImageToTargetVar=dynamic_cast<CmdSetImageToTarget *>(packet);
	if(CmdSetImageToTargetVar!=NULL){
		ImageBuffer	&Tb=Px->GetLayersBase()->GetPageData(0)->GetLayerData(0)->GetTargetBuff();
		Tb=Px->_sapera->ImageStack[CmdSetImageToTargetVar->Number];
		return;
	}

}

DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base)
{
	CameraXtiumPx8MonoLineTrigger	*Px=(CameraXtiumPx8MonoLineTrigger *)handle;
	Px->InitialXTable();
	return _ER_true;
}

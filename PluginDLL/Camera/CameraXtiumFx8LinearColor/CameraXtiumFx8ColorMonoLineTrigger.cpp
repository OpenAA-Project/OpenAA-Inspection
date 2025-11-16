//#include "CameraXtumiPx8LineTriggerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtiumFx8ColorMonoLineTrigger\CameraXtiumFx8ColorMonoLineTrigger.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
//#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumFx8ColorMonoLineTrigger.h"
#include "saperaCtrlColor.h"
#include "saperaCtrlMono.h"
#include "CameraSettingColor.h"
#include "CameraSettingMono.h"
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
//#define	DEF_CONFIG_DEFAULT_PATH		"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		/**/"T_PX-HC-08K07T-00-R_LineFrameTrigger.ccf"


//QFile debugFile(/**/"CameraDebug.txt");
//QTextStream debugStream;
//
//QString		ProofDataFile;
//bool		pbProofFlag;
//bool		pbProofCancelFlag;


CameraXtiumFx8ColorMonoLineTrigger::CameraXtiumFx8ColorMonoLineTrigger(LayersBase *base)
	:AbstructOriginateClass(true)
	,ServiceForLayers(base)
	,CamColor(0,base,this),CamMono(1,base,this)
{
}

CameraXtiumFx8ColorMonoLineTrigger::~CameraXtiumFx8ColorMonoLineTrigger()
{
}

void	CameraXtiumFx8ColorMonoLineTrigger::InitialXTable(void)
{
}
void	CameraXtiumFx8ColorMonoLineTrigger::AfterPrepare(void)
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
void	CameraXtiumFx8ColorMonoLineTrigger::AfterStartSequence(void)
{
	if(ioLightControlEnable!=NULL){
		if(ioLightControlEnable->Get()==true){
			CamColor.CalibrateStart();
			CamMono .CalibrateStart();
		}
	}
}

void	CameraXtiumFx8ColorMonoLineTrigger::Calibrate(void)
{
	if(ioLightControlEnable!=NULL){
		//_sapera->Calibrated=false;
		//_sapera->SetCalibration();
		ioLightControlEnable->Set(false);
	}
}

//----------------------------------------------------------
CameraXtiumFx::CameraXtiumFx(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent)
:CameraHandle(CamNo,base),Parent(_Parent)
{
	initialized=false;
}

void CameraXtiumFx::debugOutput(const QString &txt, int deviceID)
{
	static QMutex mutex;
	QMutexLocker locker(&mutex);
	if(debugStream.device()!=NULL){
		QString str(QString::number(deviceID) + /**/" : ");
		str += txt;
		debugStream << QString(/**/"%1%2%3").arg(str).arg(QChar(0x0D)).arg(QChar(0x0A));
	}
}

bool CameraXtiumFx::debugInit(const QString &DebugFileName ,const QString &ConfigFileName)
{
	static QMutex mutex;
	bool ok = false;

	QMutexLocker locker(&mutex);
	
	if(initialized==true){
		return true;
	}
	debugFile.setFileName(DebugFileName);
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
	ProofDataFile = ConfigFileName;

	return ok;
}

//----------------------------------------------------------

CameraXtiumFx8Color::CameraXtiumFx8Color(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent)
	:CameraXtiumFx(CamNo,base,_Parent),Setting(true)
{
	_sapera	= new saperaCtrlColor(CamNo,base,this);
	MatrixRX=NULL;
	MatrixGX=NULL;
	MatrixBX=NULL;
	MatrixRXTR=NULL;
	MatrixGXTR=NULL;
	MatrixBXTR=NULL;
	GainOffsetTableRL=NULL;
	GainOffsetTableGL=NULL;
	GainOffsetTableBL=NULL;
	GainOffsetTableRR=NULL;
	GainOffsetTableGR=NULL;
	GainOffsetTableBR=NULL;
	CamDotPerLine=-1;
	DupLineMode	=false;
	LoadFirst	=true;
	Shrink2		=1;
}

CameraXtiumFx8Color::~CameraXtiumFx8Color()
{
	if (_sapera) {
		delete _sapera;
		_sapera = NULL;
	}
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
	if(MatrixRXTR!=NULL){
		delete	[]MatrixRXTR;
		MatrixRXTR=NULL;
	}
	if(MatrixGXTR!=NULL){
		delete	[]MatrixGXTR;
		MatrixGXTR=NULL;
	}
	if(MatrixBXTR!=NULL){
		delete	[]MatrixBXTR;
		MatrixBXTR=NULL;
	}
	if(GainOffsetTableRL!=NULL){
		delete	[]GainOffsetTableRL;
		GainOffsetTableRL=NULL;
	}
	if(GainOffsetTableGL!=NULL){
		delete	[]GainOffsetTableGL;
		GainOffsetTableGL=NULL;
	}
	if(GainOffsetTableBL!=NULL){
		delete	[]GainOffsetTableBL;
		GainOffsetTableBL=NULL;
	}
	if(GainOffsetTableRR!=NULL){
		delete	[]GainOffsetTableRR;
		GainOffsetTableRR=NULL;
	}
	if(GainOffsetTableGR!=NULL){
		delete	[]GainOffsetTableGR;
		GainOffsetTableGR=NULL;
	}
	if(GainOffsetTableBR!=NULL){
		delete	[]GainOffsetTableBR;
		GainOffsetTableBR=NULL;
	}
}
void	CameraXtiumFx8Color::InitialXTable(void)
{
	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
	}
	if(MatrixGX!=NULL){
		delete	[]MatrixGX;
	}
	if(MatrixBX!=NULL){
		delete	[]MatrixBX;
	}
	if(MatrixRXTR!=NULL){
		delete	[]MatrixRXTR;
	}
	if(MatrixGXTR!=NULL){
		delete	[]MatrixGXTR;
	}
	if(MatrixBXTR!=NULL){
		delete	[]MatrixBXTR;
	}
	MatrixRX=new int[CamDotPerLine];
	MatrixGX=new int[CamDotPerLine];
	MatrixBX=new int[CamDotPerLine];
	MatrixRXTR=new int[CamDotPerLine];
	MatrixGXTR=new int[CamDotPerLine];
	MatrixBXTR=new int[CamDotPerLine];
	for(int x=0;x<CamDotPerLine;x++){
		double	X=x;
		double	kr=(X-Setting.OffsetXRed	)/Setting.MultipleRed	;
		MatrixRX[x]		=Clipping((int)kr ,0 ,CamDotPerLine-1)*4+2;
		MatrixRXTR[x]	=Clipping((int)kr ,0 ,GetDotPerLine()-1);
		double	kg=(X-Setting.OffsetXGreen	)/Setting.MultipleGreen	;
		MatrixGX[x]		=Clipping((int)kg ,0 ,CamDotPerLine-1)*4+1;
		MatrixGXTR[x]	=Clipping((int)kg ,0 ,GetDotPerLine()-1);
		double	kb=(X-Setting.OffsetXBlue	)/Setting.MultipleBlue	;
		MatrixBX[x]		=Clipping((int)kb ,0 ,CamDotPerLine-1)*4+0;
		MatrixBXTR[x]	=Clipping((int)kb ,0 ,GetDotPerLine()-1);
	}
	GainOffsetTableRL=new BYTE[256];
	GainOffsetTableGL=new BYTE[256];
	GainOffsetTableBL=new BYTE[256];
	GainOffsetTableRR=new BYTE[256];
	GainOffsetTableGR=new BYTE[256];
	GainOffsetTableBR=new BYTE[256];
	for(int i=0;i<256;i++){
		GainOffsetTableBL[i]=Clipping((int)(i*Setting.GainBlueL	+Setting.OffsetBlueL	),0,255);
		GainOffsetTableGL[i]=Clipping((int)(i*Setting.GainGreenL+Setting.OffsetGreenL	),0,255);
		GainOffsetTableRL[i]=Clipping((int)(i*Setting.GainRedL	+Setting.OffsetRedL		),0,255);
		GainOffsetTableBR[i]=Clipping((int)(i*Setting.GainBlueR	+Setting.OffsetBlueR	),0,255);
		GainOffsetTableGR[i]=Clipping((int)(i*Setting.GainGreenR+Setting.OffsetGreenR	),0,255);
		GainOffsetTableRR[i]=Clipping((int)(i*Setting.GainRedR	+Setting.OffsetRedR		),0,255);
	}
}


void	CameraXtiumFx8Color::CalibrateStart(void)
{
}
void	CameraXtiumFx8Color::Calibrate(void)
{

}

bool	CameraXtiumFx8Color::Initial(void)
{
	debugInit(/**/"DebugColorText",/**/"ConfigXtiumColor.ccf");
	debugOutput(/**/"DLL_Initial", DeviceID);

	QString	path=GetLayersBase()->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+/**/QString(/**/"\\")+ProofDataFile;

	QByteArray str_arr = FileName.replace(/**/'/',/**/"\\").toLocal8Bit();
	const char* c_str = str_arr.constData();
	if(_sapera->link((char*)c_str)==false){
		return false;
	}

	InitialXTable();
	return true;
}
bool	CameraXtiumFx8Color::Load(QIODevice *f)
{
	bool	Ret=false;
	
	bool	CameraControl=Setting.CameraControl;
	Ret=Setting.Load(f);
	if(LoadFirst==false){
		Setting.CameraControl=CameraControl;
	}
	LoadFirst=false;

	_sapera->ControlCamera();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Setting.Save(&Buff);
	Setting.LoadFromCam(_sapera->fc);
	Buff.seek(0);
	Setting.Load(&Buff);

	if(Ret==true){
		Ret=Setting.StoreToCam(_sapera->fc);
		//Ret=Setting.StoreToCam(_sapera->fc);	//For Power ON
	}
	InitialXTable();
	return true;
}
bool	CameraXtiumFx8Color::Save(QIODevice *f)
{
	return Setting.Save(f);
}

void	CameraXtiumFx8Color::SetLineCount(int YLen)
{
	bool	Ret=_sapera->ChangeLineCount(YLen);

	if(Ret==true){
		_sapera->startCapture();
		//Px->_sapera->ClearCenterLine();
	}
}
bool	CameraXtiumFx8Color::ShowSetting(void)
{
	CameraSettingColor SettingDialog(this,_sapera->fc);
	if(SettingDialog.exec()==false)
		return(false);
	return true;
}

bool	CameraXtiumFx8Color::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	return Setting.SetQuickProperty(_sapera->fc,Attr, RelativeValue);
}

bool	CameraXtiumFx8Color::PrepareCapture(void)
{
	return _sapera->prepareCapture();
}
bool	CameraXtiumFx8Color::StartCapture(void)
{
	return _sapera->startCapture();
}
bool	CameraXtiumFx8Color::SetAutoRepeat(bool RepeatON)
{
	_sapera->RepeatON=RepeatON;
	return true;
}
bool	CameraXtiumFx8Color::HaltCapture(void)
{
	return _sapera->stopCapture();
}
int		CameraXtiumFx8Color::GetStatus(CameraScanInfo *Info)
{
	int	Ret=_sapera->getStatus();
	return Ret;
}
bool	CameraXtiumFx8Color::GetImageTR(	 ImageBuffer *Buff[]
					,ImageBuffer *TRBuff[],int BufferDimCounts
					,CameraScanInfo *Info)
{
	return _sapera->getImage(Buff,TRBuff);
}

void	CameraXtiumFx8Color::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	if(CmdGetStockedCountVar!=NULL){
		CmdGetStockedCountVar->Count=_sapera->CurrentWTop;
		return;
	}
	CmdSetImageToTarget	*CmdSetImageToTargetVar=dynamic_cast<CmdSetImageToTarget *>(packet);
	if(CmdSetImageToTargetVar!=NULL){
		//int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		for(int layer=0;layer<3;layer++){
			ImageBuffer	&Tb=GetLayersBase()->GetPageData(0)->GetLayerData(layer)->GetTargetBuff();
			Tb=_sapera->ImageStack[CmdSetImageToTargetVar->Number][layer];
		}
		return;
	}
}
void	CameraXtiumFx8Color::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	SpecifiedBroadcasterCalibrateCamera	*CC=dynamic_cast<SpecifiedBroadcasterCalibrateCamera *>(v);
	if(CC!=NULL){
		Calibrate();
		return;
	}
}
void	CameraXtiumFx8Color::ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)
{
	InitialXTable();
}

//---------------------------------------------------

CameraXtiumFx8Mono::CameraXtiumFx8Mono(int CamNo ,LayersBase *base,CameraXtiumFx8ColorMonoLineTrigger *_Parent)
	:CameraXtiumFx(CamNo,base,_Parent),Setting(false)
{
	_sapera	= new saperaCtrlMono(CamNo,base,this);
	MatrixRX=NULL;
	GainOffsetTableRL=NULL;
	GainOffsetTableRR=NULL;
	CamDotPerLine=-1;
	DupLineMode	=false;
	LoadFirst	=true;
	Shrink2		=1;
}

CameraXtiumFx8Mono::~CameraXtiumFx8Mono()
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
void	CameraXtiumFx8Mono::InitialXTable(void)
{
	if(MatrixRX!=NULL){
		delete	[]MatrixRX;
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
		GainOffsetTableRL[i]=Clipping((int)(i*Setting.GainRedL	+Setting.OffsetRedL		),0,255);
		GainOffsetTableRR[i]=Clipping((int)(i*Setting.GainRedR	+Setting.OffsetRedR		),0,255);
	}
}

bool	CameraXtiumFx8Mono::Initial(void)
{
	debugInit(/**/"DebugMonoText",/**/"ConfigXtiumMono.ccf");
	debugOutput(/**/"DLL_Initial", DeviceID);

	QString	path=GetLayersBase()->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+/**/QString(/**/"\\")+ProofDataFile;

	QByteArray str_arr = FileName.replace(/**/'/',/**/"\\").toLocal8Bit();
	const char* c_str = str_arr.constData();
	if(_sapera->link((char*)c_str)==false){
		return false;
	}

	InitialXTable();
	return true;
}
void	CameraXtiumFx8Mono::CalibrateStart(void)
{
}
void	CameraXtiumFx8Mono::Calibrate(void)
{
	//if(ioLightControlEnable!=NULL){
	//	_sapera->Calibrated=false;
	//	_sapera->SetCalibration();
	//	ioLightControlEnable->Set(false);
	//}
}
bool	CameraXtiumFx8Mono::Load(QIODevice *f)
{
	//Setting.LoadFromCam(_sapera->fc);
	//
	//bool	Ret=Setting.Load(f);
	//if(Ret==true){	
	//	Ret=Setting.StoreToCam(_sapera->fc);
	//}
	//return Ret;
	//
	//bool	Ret=false;
	
	bool	CameraControl=Setting.CameraControl;
	bool	Ret=Setting.Load(f);
	if(LoadFirst==false){
		Setting.CameraControl=CameraControl;
	}
	LoadFirst=false;

	_sapera->ControlCamera();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	Setting.Save(&Buff);
	Setting.LoadFromCam(_sapera->fc);
	Buff.seek(0);
	Setting.Load(&Buff);

	if(Ret==true){
		Ret=Setting.StoreToCam(_sapera->fc);
		//Ret=Setting.StoreToCam(_sapera->fc);	//For Power ON
	}
	//InitialXTable();
	return true;
}
bool	CameraXtiumFx8Mono::Save(QIODevice *f)
{
	return Setting.Save(f);
}

void	CameraXtiumFx8Mono::SetLineCount(int YLen)
{
	bool	Ret=_sapera->ChangeLineCount(YLen);

	if(Ret==true){
		_sapera->startCapture();
		//Px->_sapera->ClearCenterLine();
	}
}

bool	CameraXtiumFx8Mono::ShowSetting(void)
{
	CameraSettingMono SettingDialog(this,_sapera->fc);
	if(SettingDialog.exec()==false)
		return(false);
	return true;
}

bool	CameraXtiumFx8Mono::SetQuickProperty(CameraQuickProperty Attr, double RelativeValue)
{
	return Setting.SetQuickProperty(_sapera->fc,Attr, RelativeValue);
}

bool	CameraXtiumFx8Mono::PrepareCapture(void)
{
	return _sapera->prepareCapture();
}
bool	CameraXtiumFx8Mono::StartCapture(void)
{
	return _sapera->startCapture();
}
bool	CameraXtiumFx8Mono::SetAutoRepeat(bool RepeatON)
{
	//_sapera->RepeatON=RepeatON;
	return true;
}
bool	CameraXtiumFx8Mono::HaltCapture(void)
{
	return _sapera->stopCapture();
}
int		CameraXtiumFx8Mono::GetStatus(CameraScanInfo *Info)
{
	int	Ret=_sapera->getStatus();
	return Ret;
}
bool	CameraXtiumFx8Mono::GetImageTR(	 ImageBuffer *Buff[]
					,ImageBuffer *TRBuff[],int BufferDimCounts
					,CameraScanInfo *Info)
{
	return _sapera->getImage(Buff[0],TRBuff[0]);
}

void	CameraXtiumFx8Mono::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	if(CmdGetStockedCountVar!=NULL){
		CmdGetStockedCountVar->Count=_sapera->CurrentWTop;
		return;
	}
	CmdSetImageToTarget	*CmdSetImageToTargetVar=dynamic_cast<CmdSetImageToTarget *>(packet);
	if(CmdSetImageToTargetVar!=NULL){
		ImageBuffer	&Tb=GetLayersBase()->GetPageData(0)->GetLayerData(0)->GetTargetBuff();
		Tb=_sapera->ImageStack[CmdSetImageToTargetVar->Number];
		return;
	}
}
void	CameraXtiumFx8Mono::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	SpecifiedBroadcasterCalibrateCamera	*CC=dynamic_cast<SpecifiedBroadcasterCalibrateCamera *>(v);
	if(CC!=NULL){
		Calibrate();
		return;
	}
}
void	CameraXtiumFx8Mono::ExecuteInitialAfterEdit	(int ExeID ,LayersBase *base)
{
	InitialXTable();
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
	str=/**/"Linear Color and Monochrome by FX8";
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

CameraXtiumFx8ColorMonoLineTrigger		*GlobalPx=NULL;

CameraHandle *_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	static bool first = true;
	int ret;

	if(first==true){
		GlobalPx=new CameraXtiumFx8ColorMonoLineTrigger(base);
		first=false;
	}
	if(CameraNoInThisComputer==0){
		if(GlobalPx->CamColor.Initial()==false)
			return NULL;
		return &GlobalPx->CamColor;
	}
	else
	if(CameraNoInThisComputer==1){
		if(GlobalPx->CamMono.Initial()==false)
			return NULL;
		return &GlobalPx->CamMono;
	}
	return NULL;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	//CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	//delete	Px;
	if(GlobalPx!=NULL){
		delete	GlobalPx;
		GlobalPx=NULL;
	}
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		Ret=true;
		if(Px->Load(&str)==false)
			Ret=false;
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		Ret=true;
		if(Px->Save(&str)==false)
			Ret=false;
	}
	return Ret;
}

DEFFUNCEX	bool	_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	if(Px!=NULL){
		Px->SetLineCount(caminfo.YLen);
	}

	return true;
}


bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	if(Px->ShowSetting()==true){
		Px->InitialXTable();
	}
	return(true);
}

bool	_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue)
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	return Px->SetQuickProperty(Attr, RelativeValue);
}


bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	return  Px->PrepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	return Px->StartCapture();
}

bool _cdecl	DLL_SetAutoRepeat(CameraHandle *handle ,bool RepeatON)
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	Px->SetAutoRepeat(RepeatON);
	return true;
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
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;

	 Px->HaltCapture();
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
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	int	Ret=Px->GetStatus(Info);
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
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	return Px->GetImageTR(Buff,TRBuff,BufferDimCounts,Info);
}
DEFFUNCEX	void	_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	Px->TransmitDirectly(packet);
}
DEFFUNCEX	void	_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v)
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	Px->SpecifiedDirectly(v);
}


DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base)
{
	CameraXtiumFx		*Px=(CameraXtiumFx *)handle;
	Px->ExecuteInitialAfterEdit	(ExeID ,base);
	return _ER_true;
}

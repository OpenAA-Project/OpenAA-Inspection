/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtumiPx8LineTrigger\CameraXtumiPx8LineTrigger.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumPx8Repeat.h"
#include "saperaCtrl.h"
#include "CameraSetting.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XEntryPoint.h"
#include "XExecuteInspectBase.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
//#define	DEF_CONFIG_DEFAULT_PATH		"C:\\Program Files\\Teledyne DALSA\\Sapera\\CamFiles\\User\\T_PX-HC-16K04T-00-R_Default_Default.ccf"
#define	DEF_CONFIG_DEFAULT_PATH		"T_PX-HC-08K07T-00-R_LineFrameTrigger.ccf"


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

CameraXtiumPx8Repeat::CameraXtiumPx8Repeat(int CamNo ,LayersBase *base ,bool original=false)
	:AbstructOriginateClass(original)
	,CameraHandle(CamNo,base)
{
	ioCurrentPage		=NULL;
	ioDoneCapturePage	=NULL;
	ioCameraError		=NULL;

	_sapera	= new saperaCtrl(CamNo,base,this);
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
	LoadFirst	=true;
	connect(_sapera,SIGNAL(SignalLinkOut()),this,SLOT(SlotLinkOut()),Qt::QueuedConnection);
}

CameraXtiumPx8Repeat::~CameraXtiumPx8Repeat()
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
void	CameraXtiumPx8Repeat::InitialXTable(void)
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
void	CameraXtiumPx8Repeat::AfterPrepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioCurrentPage		=new SignalOperandInt(this,290,"CurrentPage in CameraXtiumPx8Repeat");
			ioDoneCapturePage	=new SignalOperandInt(this,291,"DoneCapturePage in CameraXtiumPx8Repeat");
			ioEnableRPage		=new SignalOperandInt(this,292,"Enable ReadablePage in CameraXtiumPx8Repeat");
			ioCameraError		=new SignalOperandBit(this,290,"CameraError in CameraXtiumPx8Repeat");
			ioCurrentPage		->Set(0);
			ioDoneCapturePage	->Set(0);
			ioEnableRPage		->Set(0);
			ioCameraError		->Set(0);

			Param->SetSpecialOperand(ioCurrentPage);
			Param->SetSpecialOperand(ioDoneCapturePage);
			Param->SetSpecialOperand(ioEnableRPage);
			Param->SetSpecialOperand(ioCameraError);
		}
	}
	BottomArea[0].Set(0,0,GetDotPerLine(),OverlapYLen+OverlapAddedYLen);
	BottomArea[1].Set(0,0,GetDotPerLine(),OverlapYLen+OverlapAddedYLen);
	BottomArea[2].Set(0,0,GetDotPerLine(),OverlapYLen+OverlapAddedYLen);
}
	
void	CameraXtiumPx8Repeat::OutputCurrentPage(int page)
{
	if(ioCurrentPage!=NULL){
		ioCurrentPage->Set(page);
	}
}

void	CameraXtiumPx8Repeat::OutputDoneCapturePage(int page)
{
	if(ioDoneCapturePage!=NULL){
		ioDoneCapturePage->Set(page);
	}
}

int		CameraXtiumPx8Repeat::GetReadablePage(void)
{
	if(ioEnableRPage!=NULL){
		return ioEnableRPage->Get();
	}
	return 1000000;
}

void	CameraXtiumPx8Repeat::SlotLinkOut()
{
	if(ioCameraError!=NULL){
		ioCameraError->Set(1);
	}
}
void	CameraXtiumPx8Repeat::Calibrate(void)
{
	_sapera->Calibrated=false;
	_sapera->SetCalibration();
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

	CameraXtiumPx8Repeat		*Px=new CameraXtiumPx8Repeat(CameraNoInThisComputer,base);
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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	bool	Ret=false;
	if(Px!=NULL){
		bool	CameraControl=Px->Setting.CameraControl;
		Ret=Px->Setting.Load(&str);
		if(Px->LoadFirst==false){
			Px->Setting.CameraControl=CameraControl;
		}
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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	return Px->Setting.Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	CameraSetting SettingDialog(&Px->Setting, Px->_sapera->fc);
	if(SettingDialog.exec()==false)
		return(false);
	Px->InitialXTable();
	return(true);
}

bool	_cdecl	DLL_SetQuickProperty(CameraHandle *handle,CameraQuickProperty Attr, double RelativeValue)
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	return Px->Setting.SetQuickProperty(Px->_sapera->fc,Attr, RelativeValue);
}


bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	return  Px->_sapera->prepareCapture();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	return Px->_sapera->startCapture();
}

bool _cdecl	DLL_SetAutoRepeat(CameraHandle *handle ,bool RepeatON)
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	Px->_sapera->RepeatON=RepeatON;
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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;

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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
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
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	return Px->_sapera->getImage(Buff,TRBuff);
}
DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;

	CmdResetPoint	*CmdResetPointVar=dynamic_cast<CmdResetPoint *>(packet);
	if(CmdResetPointVar!=NULL){
		Px->_sapera->ResetPoint();
		return;
	}
}
DEFFUNCEX	void	_cdecl	DLL_SpecifiedDirectly(CameraHandle *handle ,SpecifiedBroadcaster *v)
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	SpecifiedBroadcasterCalibrateCamera	*CC=dynamic_cast<SpecifiedBroadcasterCalibrateCamera *>(v);
	if(CC!=NULL){
		Px->Calibrate();
		return;
	}
}

DEFFUNCEX	ExeResult	_cdecl	DLL_ExecuteInitialAfterEdit	(CameraHandle *handle ,int ExeID ,LayersBase *base)
{
	CameraXtiumPx8Repeat		*Px=(CameraXtiumPx8Repeat *)handle;
	Px->InitialXTable();
	return _ER_true;
}

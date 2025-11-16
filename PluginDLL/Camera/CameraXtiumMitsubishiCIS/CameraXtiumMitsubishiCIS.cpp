/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraXtiumMitsubishiCIS\CameraXtiumMitsubishiCIS.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "swap.h"
#include <QFile>
#include <QTextStream>
#include <Windows.h>
#include "XCameraDLL.h"
#include "XDLLType.h"
#include "CameraXtiumMitsubishiCIS.h"
#include "saperaCtrl.h"
#include "SettingDialog.h"
#include "XDataInLayer.h"

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */
static void UpdateSetting(CameraHandle *handle);
static void loadDefaultSetting(void);

/* --------------------------------------------------------------------------
   static function
   -------------------------------------------------------------------------- */

QFile debugFile("CameraDebug.txt");
QTextStream debugStream;

QString		ProofDataFile=/**/"MitsubishiCIS.ccf";
bool		pbProofFlag;
bool		pbProofCancelFlag;


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
	str="MitsubishiCIS";
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

#define	XtiumMitsubishiCIS_BoardNumb	1

CameraHandle *_cdecl	DLL_Initial(int CameraNoInThisComputer ,LayersBase *base,CameraReqInfo &CamInfo,const QString &CameraParameter)
//	Initialize Camera DLL. 
//		This function must create and open handle. 
//	return:		Camera handle(memory block)
//				if proocess fails, return 0
{
	static bool first = true;
	int ret;

	int deviceID = CameraNoInThisComputer+1;

	if (first==false) return false;

	first = false;

	CameraXtiumMitsubishiCIS	*PxBase=new CameraXtiumMitsubishiCIS(CameraNoInThisComputer,base ,XtiumMitsubishiCIS_BoardNumb);

	QString	path=base->GetUserPath();
	QDir::setCurrent(path);

	QString	FileName=path+/**/QString("\\")+ProofDataFile;

	QByteArray str_arr = FileName.toLocal8Bit();
	const char* c_str = str_arr.constData();
	for(int i=0;i<XtiumMitsubishiCIS_BoardNumb;i++){
		PxBase->Board[i]=new CameraXtiumBoard(base ,PxBase ,i);
		if(PxBase->Board[i]->_sapera->link((char*)c_str)==false){
			CamInfo.ErrorCode=1;	//ErrorCode
			return NULL;
		}
		PxBase->Board[i]->DeviceID	=i;
		PxBase->Board[i]->InitialXTable();
	}

	PxBase->Board[0]->OpenCOM();

	return PxBase;
}

/*
   make
   */
bool _cdecl	DLL_Close(CameraHandle *handle)
//	Release handle and close DLL
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	delete	Px;
	return(true);
}

bool _cdecl	DLL_Load(CameraHandle *handle ,QIODevice &str)
//	Load camera attribution(setting) information of handle
//	This function must load information from stream
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;

	bool	Ret=Px->Load(&str);
	if(Ret==true){		
		Ret=Px->Reflect();
	}
	return Ret;
}

bool _cdecl	DLL_Save(CameraHandle *handle ,QIODevice &str)
//	Save camera attribution(setting) information of handle
//	This function must save information to stream
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	Px->LoadFromCamera();
	return Px->Save(&str);
}

DEFFUNCEX	bool		_cdecl	DLL_ChangeInfo(CameraHandle *handle ,CameraReqInfo &caminfo)
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	bool	Ret=Px->ChangeLineCount(caminfo.YLen);

	if(Ret==true){
		Px->GrabStart();
		//Px->_sapera->ClearCenterLine();
	}

	return Ret;
}

bool _cdecl	DLL_ShowSetting(CameraHandle *handle, QWidget *parent)
//	This function shows dialog to set camera(handle) information
//	if dialog can't be shown, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	SettingDialog D(Px);
	if(D.exec()==false)
		return(false);

	return(true);
}

bool _cdecl	DLL_PrepareCapture(CameraHandle *handle,CameraScanInfo *Info)
//	prepare to capture
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	return  Px->GrabPrepare();
}

bool _cdecl	DLL_StartCapture(CameraHandle *handle, CameraScanInfo *Info)
//	Start capruting. 
//	This function must return soon
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	return Px->GrabStart();
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
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;

	 Px->StopGrab();
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
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;

	return Px->IsCaptured();
}

bool _cdecl	DLL_ClearError(CameraHandle *handle)
//	Clear error bit
//	This function must return soon
//	if process fails, it returns false
{
	return(true);
}

bool _cdecl	DLL_GetImage(CameraHandle *handle ,ImageBuffer *Buff[] ,int BufferDimCounts,CameraScanInfo *Info)
//	Transmit image data to Image buffer
//	if process fails, it returns false
{
	CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	return Px->getImage(Buff);
}

DEFFUNCEX	void		_cdecl	DLL_TransmitDirectly(CameraHandle *handle ,GUIDirectMessage *packet)
//	Transmit
{
	//CameraXtiumMitsubishiCIS		*Px=(CameraXtiumMitsubishiCIS *)handle;
	//CmdGetStockedCount	*CmdGetStockedCountVar=dynamic_cast<CmdGetStockedCount *>(packet);
	//if(CmdGetStockedCountVar!=NULL){
	//	CmdGetStockedCountVar->Count=Px->_sapera->CurrentWTop;
	//	return;
	//}
	//CmdSetImageToTarget	*CmdSetImageToTargetVar=dynamic_cast<CmdSetImageToTarget *>(packet);
	//if(CmdSetImageToTargetVar!=NULL){
	//	for(int layer=0;layer<Px->GetLayerNumb();layer++){
	//		ImageBuffer	&Tb=Px->GetLayersBase()->GetPageData(0)->GetLayerData(layer)->GetTargetBuff();
	//		Tb=Px->_sapera->ImageStack[CmdSetImageToTargetVar->Number][layer];
	//	}
	//	return;
	//}

}


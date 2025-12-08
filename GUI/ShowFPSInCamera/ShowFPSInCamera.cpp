/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowFPSInCamera\ShowFPSInCamera.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowFPSInCamera.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include <QIcon>
#include <QPixmap>
#include "XEntryPoint.h"
#include "XCameraClass.h"
#include "swap.h"

const	char	*sRoot=/**/"Action";
const	char	*sName=/**/"ShowFPSInCamera";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show FPS in each camera");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowFPSInCamera(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ShowFPSInCamera *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ShowFPSInCamera *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ShowFPSInCamera *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ShowFPSInCamera *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxFPS";
	Data[4].Pointer				 =&((ShowFPSInCamera *)Instance)->MaxFPS;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"Precision";
	Data[5].Pointer				 =&((ShowFPSInCamera *)Instance)->Precision;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowFPSInCamera.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

ShowFPSInCamera::ShowFPSInCamera(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	MaxFPS			=-1;
	Precision		=1;
	AllocatedCamCount	=0;
	CamDim			=NULL;

	Button.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()),Qt::QueuedConnection);
}

ShowFPSInCamera::~ShowFPSInCamera(void)
{
	if(CamDim!=NULL){
		delete	[]CamDim;
		CamDim=NULL;
	}
	AllocatedCamCount	=0;
}

void	ShowFPSInCamera::ReadyParam(void)
{
	bool	Ret=false;
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		if(CamDim!=NULL){
			delete	[]CamDim;
			CamDim=NULL;
		}
		AllocatedCamCount=E->GetAllocatedCameraCount();	
		CamDim=new CapturedInfoInCam[AllocatedCamCount];
		for(int cam=0;cam<AllocatedCamCount;cam++){
			CamDim[cam].Parent	= this;
			CamDim[cam].CamNo	= cam;
			CameraClass		*C=E->GetCamera(cam);
			if(C!=NULL){
				switch(cam){
				case 0:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera0()));	break;
				case 1:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera1()));	break;
				case 2:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera2()));	break;
				case 3:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera3()));	break;
				case 4:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera4()));	break;
				case 5:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera5()));	break;
				case 6:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera6()));	break;
				case 7:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera7()));	break;
				case 8:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera8()));	break;
				case 9:	connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera9()));	break;
				case 10:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera10()));break;
				case 11:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera11()));break;
				case 12:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera12()));break;
				case 13:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera13()));break;
				case 14:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera14()));break;
				case 15:connect(C,SIGNAL(SignalCaptured()),this,SLOT(SlotCapturedInCamera15()));break;
				default:	break;
				}
			}
		}
	}
}
void	ShowFPSInCamera::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	QPalette	Pal=Button.palette();
	Pal.setColor(QPalette::Button,BackColor);
	Button.setPalette(Pal);
	Button.setObjectName(QString(/**/"ShowFPSInCamera"));
	ResizeAction();
}

static	int	SortFunc(const void *a ,const void *b)
{
	DWORD	*ai=(DWORD *)a;
	DWORD	*bi=(DWORD *)b;

	if(*ai<*bi)
		return -1;
	if(*ai>*bi)
		return 1;
	return 0;
}

ShowFPSInCamera::CapturedInfoInCam::CapturedInfoInCam(void)
{
	memset(TimeDim,0,sizeof(TimeDim));
	Pointer=0;
	StockedCount=0;
}

double	ShowFPSInCamera::CapturedInfoInCam::GetFPS(void)
{
	double	MaxFPS=10000000;
	ExecuteInspectBase	*E=Parent->GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		CameraClass		*C=E->GetCamera(CamNo);
		if(C!=NULL){
			CameraReqInfo RetInfo;
			if(C->GetCurrentInfo(RetInfo)==true){
				MaxFPS=RetInfo.MaxFPS;
			}
		}
	}

	DWORD	STimeDim[100];
	memcpy(STimeDim,TimeDim,sizeof(TimeDim));
	if(StockedCount!=0){
		QSort(STimeDim,StockedCount,sizeof(DWORD),SortFunc);

		qint64	Added=STimeDim[StockedCount-1]-STimeDim[0];
		double	d=((double)Added)/((double)StockedCount);
		if(d>0){
			double	FPS=min(MaxFPS,1000.0/d);
			return FPS;
		}
	}
	return 0;
}

void	ShowFPSInCamera::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqFPSInCamera	*CmdReqFPSInCameraVar=dynamic_cast<CmdReqFPSInCamera *>(packet);
	if(CmdReqFPSInCameraVar!=NULL){
		if(0<=CmdReqFPSInCameraVar->CamNo && CmdReqFPSInCameraVar->CamNo<AllocatedCamCount){
			CmdReqFPSInCameraVar->FPS=CamDim[CmdReqFPSInCameraVar->CamNo].GetFPS();
		}
		else{
			CmdReqFPSInCameraVar->FPS=0;
		}
		return;
	}
}

void	ShowFPSInCamera::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	ShowFPSInCamera::CapturedInCameraFromSlot(int CamNo)
{
	if(0<=CamNo & CamNo<AllocatedCamCount){
		CapturedInfoInCam	*p=&CamDim[CamNo];
		p->TimeDim[p->Pointer]=::GetComputerMiliSec();
		p->Pointer++;
		if(p->Pointer>=100){
			p->Pointer=0;
		}
		p->StockedCount++;
		if(p->StockedCount>100){
			p->StockedCount=100;
		}
	}
}

void	ShowFPSInCamera::SlotCapturedInCamera0()	{	CapturedInCameraFromSlot(0);	}
void	ShowFPSInCamera::SlotCapturedInCamera1()	{	CapturedInCameraFromSlot(1);	}
void	ShowFPSInCamera::SlotCapturedInCamera2()	{	CapturedInCameraFromSlot(2);	}
void	ShowFPSInCamera::SlotCapturedInCamera3()	{	CapturedInCameraFromSlot(3);	}
void	ShowFPSInCamera::SlotCapturedInCamera4()	{	CapturedInCameraFromSlot(4);	}
void	ShowFPSInCamera::SlotCapturedInCamera5()	{	CapturedInCameraFromSlot(5);	}
void	ShowFPSInCamera::SlotCapturedInCamera6()	{	CapturedInCameraFromSlot(6);	}
void	ShowFPSInCamera::SlotCapturedInCamera7()	{	CapturedInCameraFromSlot(7);	}
void	ShowFPSInCamera::SlotCapturedInCamera8()	{	CapturedInCameraFromSlot(8);	}
void	ShowFPSInCamera::SlotCapturedInCamera9()	{	CapturedInCameraFromSlot(9);	}
void	ShowFPSInCamera::SlotCapturedInCamera10()	{	CapturedInCameraFromSlot(10);	}
void	ShowFPSInCamera::SlotCapturedInCamera11()	{	CapturedInCameraFromSlot(11);	}
void	ShowFPSInCamera::SlotCapturedInCamera12()	{	CapturedInCameraFromSlot(12);	}
void	ShowFPSInCamera::SlotCapturedInCamera13()	{	CapturedInCameraFromSlot(13);	}
void	ShowFPSInCamera::SlotCapturedInCamera14()	{	CapturedInCameraFromSlot(14);	}
void	ShowFPSInCamera::SlotCapturedInCamera15()	{	CapturedInCameraFromSlot(15);	}

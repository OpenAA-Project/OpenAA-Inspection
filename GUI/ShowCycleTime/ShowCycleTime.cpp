/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowCycleTime\ShowCycleTime.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowCycleTime.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include <QIcon>
#include <QPixmap>
#include "XEntryPoint.h"

const	char	*sRoot=/**/"Action";
const	char	*sName=/**/"ShowCycleTime";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show cycle time");
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
	return(new ShowCycleTime(Base,parent));
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
	Data[0].Pointer				 =&((ShowCycleTime *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ShowCycleTime *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ShowCycleTime *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ShowCycleTime *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"MaxFPS";
	Data[4].Pointer				 =&((ShowCycleTime *)Instance)->MaxFPS;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"Precision";
	Data[5].Pointer				 =&((ShowCycleTime *)Instance)->Precision;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowCycleTime.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

ShowCycleTime::ShowCycleTime(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	CapturedCount	=0;
	CapturedWIndex	=0;
	LastTime		=0;
	CurrentTime		=0;
	MaxFPS			=-1;
	Precision		=1;
	UpdateCounter	=0;
	ModeSignalCaptured=false;
	Button.setParent(this);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()),Qt::QueuedConnection);
}
void	ShowCycleTime::ReadyParam(void)
{
	bool	Ret=false;
	ExecuteInspectBase	*E=GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		Ret=(connect(E,SIGNAL(SignalCaptured(int))	,this,SLOT(SlotCaptured(int))	,Qt::QueuedConnection))?true:false;
	}
}
void	ShowCycleTime::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	QPalette	Pal=Button.palette();
	Pal.setColor(QPalette::Button,BackColor);
	Button.setPalette(Pal);
	Button.setObjectName(QString(/**/"ShowCycleTime"));
	ResizeAction();
}

void	ShowCycleTime::ShowMessage(void)
{
	DWORD	Sum=0;

	DWORD	D=::GetComputerMiliSec();
	if(D-CurrentTime>500){
		CurrentTime=D;
		if(CapturedCount>0){
			for(int i=0;i<CapturedCount;i++){
				Sum+=CapturedTime[i];
			}
			double	V=((double)Sum)/((double)CapturedCount);
			if(V>0){
				FPS=1000.0/V;
				if(MaxFPS>=0 && MaxFPS<FPS){
					FPS=MaxFPS;
				}
				QString	s=QString::number(FPS,'f',Precision)+QString(" FPS");
				Button.setText(s);

				emit	SignalCycleTime(FPS);
			}
		}
	}
}

void	ShowCycleTime::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqCycleTimeFPS	*CmdReqCycleTimeFPSVar=dynamic_cast<CmdReqCycleTimeFPS *>(packet);
	if(CmdReqCycleTimeFPSVar!=NULL){
		CmdReqCycleTimeFPSVar->FPS=FPS;
		return;
	}
}

void	ShowCycleTime::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	ShowCycleTime::SlotCaptured(int)
{
	ModeSignalCaptured=true;
	DWORD	D=::GetComputerMiliSec();
	if(LastTime==0)
		LastTime=D;
	else{
		CapturedTime[CapturedWIndex]=D-LastTime;
		LastTime=D;
		CapturedWIndex++;
		if(CapturedWIndex>=sizeof(CapturedTime)/sizeof(CapturedTime[0]))
			CapturedWIndex=0;
		CapturedCount++;
		if(CapturedCount>sizeof(CapturedTime)/sizeof(CapturedTime[0])){
			CapturedCount=sizeof(CapturedTime)/sizeof(CapturedTime[0]);
		}
		ShowMessage();
	}
}

void	ShowCycleTime::ShowInPlayer(int64 shownInspectionID)
{
	UpdateCounter++;
	if(ModeSignalCaptured==false){
		SlotCaptured(0);
		ModeSignalCaptured=false;
	}
	if(UpdateCounter>=10){
		if(ModeSignalCaptured==true){
			ShowMessage();
		}
		UpdateCounter=0;
	}
}

void	ShowCycleTime::SetSignal(QObject *target,const char *signal,const char *slotfunc)
{
	disconnect(this,SLOT(SlotCaptured(int)));
	connect(target,signal,this,SLOT(SlotCaptured(int)));
}

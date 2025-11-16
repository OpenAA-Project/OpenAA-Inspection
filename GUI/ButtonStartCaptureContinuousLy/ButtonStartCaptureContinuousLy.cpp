/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonStartCaptureContinuousLy\ButtonStartCaptureContinuousLy.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonStartCaptureContinuousLy.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XMacroFunction.h"
#include "XSyncGUI.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"StartCaptureContinuousLy";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Start to capture image continuously");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetStartCaptureContinuousLy(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonStartCaptureContinuousLy(Base,parent));
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
	Data[0].Pointer				 =&((ButtonStartCaptureContinuousLy *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonStartCaptureContinuousLy *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonStartCaptureContinuousLy *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonStartCaptureContinuousLy *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonStartCaptureContinuousLy *)Instance)->DefaultPushed;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonStartCaptureContinuousLy.png")));
}


static	bool	MacroStartCaptureContinuously(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonStartCaptureContinuousLy	*V=dynamic_cast<ButtonStartCaptureContinuousLy *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandStartCaptureContinuously();

	return true;
}

static	bool	MacroStopCaptureContinuously(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonStartCaptureContinuousLy	*V=dynamic_cast<ButtonStartCaptureContinuousLy *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandStopCaptureContinuously();

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"StartCaptureContinuously";
		Functions[ret].Explain.append(/**/"Start to capture continuously");
		Functions[ret].DLL_ExcuteMacro	=MacroStartCaptureContinuously;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"StopCaptureContinuously";
		Functions[ret].Explain.append(/**/"Stop to capture continuously");
		Functions[ret].DLL_ExcuteMacro	=MacroStopCaptureContinuously;
		ret++;
	}
	return ret;
}
//==================================================================================================
ButtonStartCaptureContinuousLy::ButtonStartCaptureContinuousLy(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	DefaultPushed	=false;
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonStartCaptureContinuousLy");
	Msg=/**/"Start capture";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonStartCaptureContinuousLy::~ButtonStartCaptureContinuousLy(void)
{
}

void	ButtonStartCaptureContinuousLy::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(DefaultPushed);
	ResizeAction();
}

void	ButtonStartCaptureContinuousLy::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonStartCaptureContinuousLy::SlotToggled( bool checked )
{
	ExecuteToggled(checked);

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			GetLayersBase()->ShowProcessingForm("Synchronize",false);
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			::Save(&Buff,checked);
			TxSync(Buff.buffer());
			GetLayersBase()->DelayedCloseProcessingForm(1);
		}
	}
	if(checked==true){
		QPalette	P=Button.palette();
		P.setColor(QPalette::Light,Qt::red);
		Button.setPalette(P);
	}
	else{
		QPalette	P=Button.palette();
		P.setColor(QPalette::Light,Qt::white);
		Button.setPalette(P);
	}

	if(GetLayersBase()->IsLocalCamera()==true){
		if(checked==true){
			SpecifiedBroadcasterAutoModeStart	RCmd;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				BroadcastSpecifiedDirectly(&RCmd);
			}
		}
		else{
			SpecifiedBroadcasterAutoModeStart	RCmd;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				BroadcastSpecifiedDirectly(&RCmd);
			}
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetStartCaptureContinuousLy	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.Clicked	=checked;
			RCmd.Send(NULL,page,0);
		}
	}
}
void	ButtonStartCaptureContinuousLy::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStateOnStartCaptureContinuousLy *CmdGetStateOnStartCaptureContinuousLyVar=dynamic_cast<CmdGetStateOnStartCaptureContinuousLy *>(packet);
	if(CmdGetStateOnStartCaptureContinuousLyVar!=NULL){
		if(Button.isChecked()==true){
			CmdGetStateOnStartCaptureContinuousLyVar->ModeOn=true;
		}
		else{
			CmdGetStateOnStartCaptureContinuousLyVar->ModeOn=false;
		}
		return;
	}
	CmdSetStateOnStartCaptureContinuousLy *CmdSetStateOnStartCaptureContinuousLyVar=dynamic_cast<CmdSetStateOnStartCaptureContinuousLy *>(packet);
	if(CmdSetStateOnStartCaptureContinuousLyVar!=NULL){
		if(CmdSetStateOnStartCaptureContinuousLyVar->ModeOn==true){
			Button.setChecked(true);
		}
		else{
			Button.setChecked(false);
		}
		return;
	}
	CmdLockStartCaptureContinuousLy	*CmdLockStartCaptureContinuousLyVar=dynamic_cast<CmdLockStartCaptureContinuousLy *>(packet);
	if(CmdLockStartCaptureContinuousLyVar!=NULL){
		if(CmdLockStartCaptureContinuousLyVar->Enabled==true)
			Button.setEnabled(true);
		else
			Button.setEnabled(false);
		return;
	}
}
	
void	ButtonStartCaptureContinuousLy::CommandStartCaptureContinuously(void)
{
	Button.setChecked(true);
}
void	ButtonStartCaptureContinuousLy::CommandStopCaptureContinuously(void)
{
	Button.setChecked(false);
}
void	ButtonStartCaptureContinuousLy::ExecuteToggled( bool checked )
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(checked==true){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_AutoCaptureInspect);
		}
		else{
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_NoAutoRepeat);
			GetLayersBase()->CloseProcessingForm();
		}
	}
}

void	ButtonStartCaptureContinuousLy::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool checked;
	::Load(&Buff,checked);

	SyncMode=true;
	Button.setChecked(checked);
	SyncMode=true;
}

//================================================================================================================

GUICmdSetStartCaptureContinuousLy::GUICmdSetStartCaptureContinuousLy(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetStartCaptureContinuousLy::Load(QIODevice *f)
{
	if(::Load(f,Clicked)==false)
		return false;
	return true;
}

bool	GUICmdSetStartCaptureContinuousLy::Save(QIODevice *f)
{
	if(::Save(f,Clicked)==false)
		return false;
	return true;
}


void	GUICmdSetStartCaptureContinuousLy::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(Clicked==true){
		SpecifiedBroadcasterAutoModeStart	RCmd;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&RCmd);
		}
	}
	else{
		SpecifiedBroadcasterAutoModeEnd	RCmd;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&RCmd);
		}
	}
}
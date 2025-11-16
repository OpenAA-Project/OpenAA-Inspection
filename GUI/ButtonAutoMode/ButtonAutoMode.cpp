#include "ButtonAutoModeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoMode\ButtonAutoMode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAutoMode.h"
#include "ButtonAutoScanningMode.h"
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
static	const	char	*sName=/**/"AutoMode";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Auto Mode Button");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetAutoMode(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonAutoMode(Base,parent));
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
	Data[0].Pointer				 =&((ButtonAutoMode *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAutoMode *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAutoMode *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAutoMode *)Instance)->CFont;
	Data[4].Type				 =/**/"QImage";
	Data[4].VariableNameWithRoute=/**/"ButtonIconUp";
	Data[4].Pointer				 =&((ButtonAutoMode *)Instance)->ButtonIconUp;
	Data[5].Type				 =/**/"QImage";
	Data[5].VariableNameWithRoute=/**/"ButtonIconDown";
	Data[5].Pointer				 =&((ButtonAutoMode *)Instance)->ButtonIconDown;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"DefaultPushed";
	Data[6].Pointer				 =&((ButtonAutoMode *)Instance)->DefaultPushed;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"RegNoInFlagSet";
	Data[7].Pointer				 =&((ButtonAutoMode *)Instance)->RegNoInFlagSet;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAutoMode.png")));
}


static	bool	MacroAutoModeON(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonAutoMode	*V=dynamic_cast<ButtonAutoMode *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandAutoModeON();

	return true;
}

static	bool	MacroAutoModeOFF(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonAutoMode	*V=dynamic_cast<ButtonAutoMode *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandAutoModeOFF();

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoModeON";
		Functions[ret].Explain.append(/**/"Push AutoMode button");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoModeON;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoModeOFF";
		Functions[ret].Explain.append(/**/"Release AutoMode button");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoModeOFF;
		ret++;
	}
	return ret;
}
//==================================================================================================
ButtonAutoMode::ButtonAutoMode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	DefaultPushed	=false;
	iFlagSet		=NULL;
	RegNoInFlagSet	=-1;
	CurrentState	=false;

	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonToggleAutoMode");
	Msg=/**/"AutoMode";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonAutoMode::~ButtonAutoMode(void)
{
}

void	ButtonAutoMode::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	if(ButtonIconUp  .isNull()==false 
	|| ButtonIconDown.isNull()==false){
		QIcon	Icon;
		int	W=width();
		int	H=height();
		if(ButtonIconUp  .isNull()==false){
			QPixmap IconMapUp=QPixmap::fromImage(ButtonIconUp.scaled(W,H));
			Icon.addPixmap(IconMapUp,QIcon::Normal,QIcon::Off);
		}
		if(ButtonIconDown.isNull()==false){
			QPixmap IconMapDown=QPixmap::fromImage(ButtonIconDown.scaled(W,H));
			Icon.addPixmap(IconMapDown,QIcon::Active,QIcon::On);
		}
		Button.setIconSize(QSize(W,H));
		Button.setIcon(Icon);
	}

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL && RegNoInFlagSet>=0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iFlagSet	=new SignalOperandBit(this,RegNoInFlagSet,/**/"ButtonAutoMode:iFlagSet");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iFlagSet,&Error)==false){
				iFlagSet->ShowErrorMessage(Error);
			}
		}
	}

	ResizeAction();
}

void	ButtonAutoMode::AfterStartSequence(void)
{
	Button.setChecked(DefaultPushed);
	SlotToggled(DefaultPushed);
}

void	ButtonAutoMode::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAutoMode::SlotToggled( bool checked )
{
	CurrentState=checked;
	if(checked==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoScanningMode",/**/"");
		if(f!=NULL){
			CmdSetScanningStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=false;
			f->TransmitDirectly(&RCmd);
		}
	}

	ExecuteToggled(checked);

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonAutoMode_LS,LID_0)/*"Synchronize"*/,false);
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
			GUICmdSetAutoMode	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.Clicked	=checked;
			RCmd.Send(NULL,page,0);
		}
	}
}
void	ButtonAutoMode::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetStateOnAutoMode *CmdGetStateOnAutoModeVar=dynamic_cast<CmdGetStateOnAutoMode *>(packet);
	if(CmdGetStateOnAutoModeVar!=NULL){
		//if(Button.isChecked()==true){
		if(CurrentState==true){
			CmdGetStateOnAutoModeVar->AutoModeOn=true;
		}
		else{
			CmdGetStateOnAutoModeVar->AutoModeOn=false;
		}
		return;
	}
	CmdSetStateOnAutoMode *CmdSetStateOnAutoModeVar=dynamic_cast<CmdSetStateOnAutoMode *>(packet);
	if(CmdSetStateOnAutoModeVar!=NULL){
		if(CmdSetStateOnAutoModeVar->AutoModeOn==true){
			Button.setChecked(true);
		}
		else{
			Button.setChecked(false);
		}
		return;
	}
	CmdLockAutoMode	*CmdLockAutoModeVar=dynamic_cast<CmdLockAutoMode *>(packet);
	if(CmdLockAutoModeVar!=NULL){
		if(CmdLockAutoModeVar->Enabled==true)
			Button.setEnabled(true);
		else
			Button.setEnabled(false);
		return;
	}
}
	
void	ButtonAutoMode::CommandAutoModeON(void)
{
	Button.setChecked(true);
}
void	ButtonAutoMode::CommandAutoModeOFF(void)
{
	Button.setChecked(false);
}
void	ButtonAutoMode::ExecuteToggled( bool checked )
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(checked==true){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_AutoCaptureInspect);
			if(iFlagSet!=NULL){
				iFlagSet->Set(true);
			}
		}
		else{
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_NoAutoRepeat);
			}
			GetLayersBase()->CloseProcessingForm();
			if(iFlagSet!=NULL){
				iFlagSet->Set(false);
			}
		}
	}
}

void	ButtonAutoMode::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool checked;
	::Load(&Buff,checked);

	SyncMode=true;
	Button.setChecked(checked);
	SyncMode=false;
}

GUICmdSetAutoMode::GUICmdSetAutoMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAutoMode::Load(QIODevice *f)
{
	if(::Load(f,Clicked)==false)
		return false;
	return true;
}

bool	GUICmdSetAutoMode::Save(QIODevice *f)
{
	if(::Save(f,Clicked)==false)
		return false;
	return true;
}


void	GUICmdSetAutoMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
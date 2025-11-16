/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoScanningMode\ButtonAutoScanningMode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAutoScanningMode.h"
#include "ButtonAutoMode.h"
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
static	const	char	*sName=/**/"AutoScanningMode";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Auto scanning mode Button");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetAutoScanningMode(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonAutoScanningMode(Base,parent));
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
	Data[0].Pointer				 =&((ButtonAutoScanningMode *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonAutoScanningMode *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonAutoScanningMode *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonAutoScanningMode *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonAutoScanningMode *)Instance)->DefaultPushed;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"RegNoInFlagSet";
	Data[5].Pointer				 =&((ButtonAutoScanningMode *)Instance)->RegNoInFlagSet;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAutoScanningMode.png")));
}


static	bool	MacroAutoModeON(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonAutoScanningMode	*V=dynamic_cast<ButtonAutoScanningMode *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandAutoModeON();

	return true;
}

static	bool	MacroAutoModeOFF(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonAutoScanningMode	*V=dynamic_cast<ButtonAutoScanningMode *>(Instance);
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
ButtonAutoScanningMode::ButtonAutoScanningMode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	DefaultPushed	=false;
	iFlagSet		=NULL;
	RegNoInFlagSet	=-1;

	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonToggleAutoScanningMode");
	Msg=/**/"AutoScanningMode";
	resize(60,25);
	connect(&Button,SIGNAL(toggled(bool)), this ,SLOT(SlotToggled(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonAutoScanningMode::~ButtonAutoScanningMode(void)
{
}

void	ButtonAutoScanningMode::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL && RegNoInFlagSet>=0
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iFlagSet	=new SignalOperandBit(this,RegNoInFlagSet,/**/"ButtonAutoScanningMode:iFlagSet");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iFlagSet,&Error)==false){
				iFlagSet->ShowErrorMessage(Error);
			}
		}
	}

	ResizeAction();
}

void	ButtonAutoScanningMode::AfterStartSequence(void)
{
	Button.setChecked(DefaultPushed);
	SlotToggled(DefaultPushed);
}

void	ButtonAutoScanningMode::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAutoScanningMode::SlotToggled( bool checked )
{
	if(checked==true){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"AutoMode",/**/"");
		if(f!=NULL){
			CmdSetStateOnAutoMode	RCmd(GetLayersBase());
			RCmd.AutoModeOn=false;
			f->TransmitDirectly(&RCmd);
		}
	}
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
			GUICmdSetAutoScanningMode	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.Clicked	=checked;
			RCmd.Send(NULL,page,0);
		}
	}
}
void	ButtonAutoScanningMode::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetScanningStateOnAutoMode *CmdGetScanningStateOnAutoModeVar=dynamic_cast<CmdGetScanningStateOnAutoMode *>(packet);
	if(CmdGetScanningStateOnAutoModeVar!=NULL){
		if(Button.isChecked()==true){
			CmdGetScanningStateOnAutoModeVar->AutoModeOn=true;
		}
		else{
			CmdGetScanningStateOnAutoModeVar->AutoModeOn=false;
		}
		return;
	}
	CmdSetScanningStateOnAutoMode *CmdSetScanningStateOnAutoModeVar=dynamic_cast<CmdSetScanningStateOnAutoMode *>(packet);
	if(CmdSetScanningStateOnAutoModeVar!=NULL){
		if(CmdSetScanningStateOnAutoModeVar->AutoModeOn==true){
			Button.setChecked(true);
		}
		else{
			Button.setChecked(false);
		}
		return;
	}
	CmdLockAutoScanningMode	*CmdLockAutoScanningModeVar=dynamic_cast<CmdLockAutoScanningMode *>(packet);
	if(CmdLockAutoScanningModeVar!=NULL){
		if(CmdLockAutoScanningModeVar->Enabled==true)
			Button.setEnabled(true);
		else
			Button.setEnabled(false);
		return;
	}
}
	
void	ButtonAutoScanningMode::CommandAutoModeON(void)
{
	Button.setChecked(true);
}
void	ButtonAutoScanningMode::CommandAutoModeOFF(void)
{
	Button.setChecked(false);
}
void	ButtonAutoScanningMode::ExecuteToggled( bool checked )
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(checked==true){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_AutoCaptureOnlyTarget);
			if(iFlagSet!=NULL){
				iFlagSet->Set(true);
			}
		}
		else{
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureOnlyTarget){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_NoAutoRepeat);
			}
			GetLayersBase()->CloseProcessingForm();
			if(iFlagSet!=NULL){
				iFlagSet->Set(false);
			}
		}
	}
}

void	ButtonAutoScanningMode::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	bool checked;
	::Load(&Buff,checked);

	SyncMode=true;
	Button.setChecked(checked);
	SyncMode=false;
}

//==============================================================================

GUICmdSetAutoScanningMode::GUICmdSetAutoScanningMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetAutoScanningMode::Load(QIODevice *f)
{
	if(::Load(f,Clicked)==false)
		return false;
	return true;
}

bool	GUICmdSetAutoScanningMode::Save(QIODevice *f)
{
	if(::Save(f,Clicked)==false)
		return false;
	return true;
}


void	GUICmdSetAutoScanningMode::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
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
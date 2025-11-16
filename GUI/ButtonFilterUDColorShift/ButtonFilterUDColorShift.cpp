#include "ButtonFilterUDColorShiftResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonFilterUDColorShift\ButtonFilterUDColorShift.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonFilterUDColorShift.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XFilterInstance.h"
#include "XGUIDLL.h"
#include "XCommonFilterUDColorShift.h"
#include "XSyncGUI.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"FilterUDColorShift";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for Filter-UpsideDown");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdFilterUDColorShift		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdFilterClearUDColorShift	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonFilterUDColorShift(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->DefaultPushed;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[5].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->SystemRegisterNo;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"SystemRegisterIntNo";
	Data[6].Pointer				 =&((ButtonFilterUDColorShift *)Instance)->SystemRegisterIntNo;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonFilterUDColorShift.png")));
}

//==================================================================================================
ButtonFilterUDColorShift::ButtonFilterUDColorShift(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	SystemRegisterNo=52;
	ioMode			=NULL;
	SystemRegisterIntNo=572;
	ioShift			=NULL;
	VShift			=-3666;
	ioEveryTime		=NULL;

	DefaultPushed	=false;
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	//Button.setObjectName(QString(/**/"ButtonFilterUDColorShift"));
	Msg=/**/"UDColorShift";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonFilterUDColorShift::~ButtonFilterUDColorShift(void)
{
}

void	ButtonFilterUDColorShift::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"FilterUDColorShift")+QString::number(SystemRegisterNo));
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo		,/**/"ButtonFilterUDColorShift:ioMode");
			ioEveryTime	=new SignalOperandBit(this,SystemRegisterNo+1	,/**/"ButtonFilterUDColorShift:ioEveryTime");
			ioShift		=new SignalOperandInt(this,SystemRegisterIntNo	,/**/"ButtonFilterUDColorShift:ioShift");
			connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			connect(ioEveryTime		,SIGNAL(changed())	,this	,SLOT(ioEveryTimeOperandChanged()));
			connect(ioShift			,SIGNAL(changed())	,this	,SLOT(OperandChangedShift()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode		,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioEveryTime,&Error)==false){
				ioEveryTime->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(ioShift	,&Error)==false){
				ioShift->ShowErrorMessage(Error);
			}
		}
	}
}

void	ButtonFilterUDColorShift::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonFilterUDColorShift::SlotClicked()
{
	SendClicked(VShift);
}
void	ButtonFilterUDColorShift::SendClicked(int	_VShift)
{
	if(Button.isChecked()==true){
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterUDColorShift	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.VShift	=_VShift;
			RCmd.Send(NULL,GlobalPage ,0);
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterClearUDColorShift	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.VShift	=_VShift;
			RCmd.Send(NULL,GlobalPage ,0);
		}
	}
}

void	ButtonFilterUDColorShift::OperandChanged()
{
	if(ioMode!=NULL && ioMode->Get()==true){		
		Button.setChecked(true);
		SlotClicked();
		SetButtonColor(true);
	}
	else{
		Button.setChecked(false);
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterClearUDColorShift	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.VShift	=VShift;
			RCmd.Send(NULL,GlobalPage ,0);
		}
		SetButtonColor(false);
	}
}

void	ButtonFilterUDColorShift::OperandChangedShift()
{
	if(ioShift!=NULL){
		VShift	=ioShift->Get();
		SendClicked(VShift);
	}
	Button.setText(Msg+QString::number(VShift));
	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			::Save(&Buff,VShift);
			TxSync(Buff.buffer());
		}
	}
}
void	ButtonFilterUDColorShift::ioEveryTimeOperandChanged()
{
	if(ioEveryTime!=NULL && ioEveryTime->Get()==true){		
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterUDColorShiftEveryTime	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.MasterTime	=XDateTime::currentDateTime();
			RCmd.Send(NULL,GlobalPage ,0);
		}
		SetButtonColor(true);
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterClearUDColorShiftEveryTime	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.MasterTime	=XDateTime::currentDateTime();
			RCmd.Send(NULL,GlobalPage ,0);
		}
		SetButtonColor(false);
	}
}
void	ButtonFilterUDColorShift::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	::Load(&Buff,VShift);

	SyncMode=true;
	Button.setText(Msg+QString::number(VShift));
	SendClicked(VShift);
	SyncMode=false;
}

void	ButtonFilterUDColorShift::SetButtonColor(bool mode)
{
	if(mode==true){
		QPalette	P=Button.palette();
		P.setColor(QPalette::Button,Qt::red);
		Button.setPalette(P);
	}
	else{
		QPalette	P=Button.palette();
		P.setColor(QPalette::Button,Qt::gray);
		Button.setPalette(P);
	}
}

//========================================================================================================

GUICmdFilterUDColorShift::GUICmdFilterUDColorShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdFilterUDColorShift::Load(QIODevice *f)
{
	if(::Load(f,VShift)==false)
		return false;
	if(::Load(f,MasterTime)==false)
		return false;
	return true;
}

bool	GUICmdFilterUDColorShift::Save(QIODevice *f)
{
	if(::Save(f,VShift)==false)
		return false;
	if(::Save(f,MasterTime)==false)
		return false;
	return true;
}

void	GUICmdFilterUDColorShift::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UDColorShift");
		if(F!=NULL){
			CmdExecuteFilter	Cmd(GetLayersBase());
			Cmd.VShift=VShift;
			F->TransmitDirectly(&Cmd);

			GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
			if(f!=NULL){
				((ButtonFilterUDColorShift *)f)->SetButtonColor(true);
			}
		}
	}
	SendAck(localPage);
}
//========================================================================================================

GUICmdFilterClearUDColorShift::GUICmdFilterClearUDColorShift(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdFilterClearUDColorShift::Load(QIODevice *f)
{
	if(::Load(f,VShift)==false)
		return false;
	if(::Load(f,MasterTime)==false)
		return false;
	return true;
}

bool	GUICmdFilterClearUDColorShift::Save(QIODevice *f)
{
	if(::Save(f,VShift)==false)
		return false;
	if(::Save(f,MasterTime)==false)
		return false;
	return true;
}
void	GUICmdFilterClearUDColorShift::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UDColorShift");
		if(F!=NULL){
			CmdExecuteClearFilter	Cmd(GetLayersBase());
			Cmd.VShift=VShift;
			F->TransmitDirectly(&Cmd);

			GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
			if(f!=NULL){
				((ButtonFilterUDColorShift *)f)->SetButtonColor(false);
			}
		}
	}
	//GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	SendAck(localPage);
}

//========================================================================================================

GUICmdFilterUDColorShiftEveryTime::GUICmdFilterUDColorShiftEveryTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdFilterUDColorShiftEveryTime::Load(QIODevice *f)
{
	if(::Load(f,MasterTime)==false)
		return false;
	return true;
}

bool	GUICmdFilterUDColorShiftEveryTime::Save(QIODevice *f)
{
	if(::Save(f,MasterTime)==false)
		return false;
	return true;
}

void	GUICmdFilterUDColorShiftEveryTime::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UDColorShift");
		if(F!=NULL){
			CmdExecuteFilterEveryTime	Cmd(GetLayersBase());
			Cmd.MasterTime=MasterTime;
			F->TransmitDirectly(&Cmd);

			GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
			if(f!=NULL){
				((ButtonFilterUDColorShift *)f)->SetButtonColor(true);
			}
		}
	}
}
//========================================================================================================

GUICmdFilterClearUDColorShiftEveryTime::GUICmdFilterClearUDColorShiftEveryTime(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdFilterClearUDColorShiftEveryTime::Load(QIODevice *f)
{
	if(::Load(f,MasterTime)==false)
		return false;
	return true;
}

bool	GUICmdFilterClearUDColorShiftEveryTime::Save(QIODevice *f)
{
	if(::Save(f,MasterTime)==false)
		return false;
	return true;
}

void	GUICmdFilterClearUDColorShiftEveryTime::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UDColorShift");
		if(F!=NULL){
			CmdExecuteClearFilterEveryTime	Cmd(GetLayersBase());
			Cmd.MasterTime=MasterTime;
			F->TransmitDirectly(&Cmd);

			GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
			if(f!=NULL){
				((ButtonFilterUDColorShift *)f)->SetButtonColor(true);
			}
		}
	}
}

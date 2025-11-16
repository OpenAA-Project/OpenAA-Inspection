#include "ButtonFilterUpsideDownResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonFilterUpsideDown\ButtonFilterUpsideDown.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonFilterUpsideDown.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XFilterInstance.h"
#include "XGUIDLL.h"
#include "XCommonFilterUpsideDown.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"FilterUpsideDown";


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
	(*Base)=new GUICmdFilterUpsideDown(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdFilterClearUpsideDown(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonFilterUpsideDown(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"DefaultPushed";
	Data[4].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->DefaultPushed;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[5].Pointer				 =&((ButtonFilterUpsideDown *)Instance)->SystemRegisterNo;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonFilterUpsideDown.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonFilterUpsideDown::ButtonFilterUpsideDown(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=52;
	ioMode			=NULL;

	DefaultPushed	=false;
	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Msg=/**/"UpsideDown";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonFilterUpsideDown::~ButtonFilterUpsideDown(void)
{
}

void	ButtonFilterUpsideDown::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"FilterUpsideDown")+QString::number(SystemRegisterNo));
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"ButtonFilterUpsideDown:ioMode");
			connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
		}
	}
}

void	ButtonFilterUpsideDown::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonFilterUpsideDown::SlotClicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdFilterUpsideDown	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.SendOnly(GlobalPage ,0);
	}
}

void	ButtonFilterUpsideDown::OperandChanged()
{
	if(ioMode->Get()==true){
		SlotClicked();
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdFilterClearUpsideDown	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.SendOnly(GlobalPage ,0);
		}
	}
}
	
//========================================================================================================

GUICmdFilterUpsideDown::GUICmdFilterUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdFilterUpsideDown::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UpsideDown");
		if(F!=NULL){
			CmdExecuteFilter	Cmd(GetLayersBase());
			F->TransmitDirectly(&Cmd);
		}
	}
	//GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	SendAck(localPage);
}
//========================================================================================================

GUICmdFilterClearUpsideDown::GUICmdFilterClearUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdFilterClearUpsideDown::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
	FilterInstanceContainer	*Pc=Ph->GetFilterContainer(localPage);
	if(Pc!=NULL){
		FilterInstanceList	*F=Pc->Search(/**/"UpsideDown");
		if(F!=NULL){
			CmdExecuteClearFilter	Cmd(GetLayersBase());
			F->TransmitDirectly(&Cmd);
		}
	}
	//GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	SendAck(localPage);
}

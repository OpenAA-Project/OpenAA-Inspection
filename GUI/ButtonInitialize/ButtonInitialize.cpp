/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonInitialize\ButtonInitialize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonInitialize.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XFilterInstance.h"
#include "XGUIDLL.h"
#include "XAlgorithmBase.h"
#include "XWriteResultThread.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"Initialize";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Initialize");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqInitialize(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonInitialize(Base,parent));
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
	Data[0].Pointer				 =&((ButtonInitialize *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonInitialize *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonInitialize *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonInitialize *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[4].Pointer				 =&((ButtonInitialize *)Instance)->SystemRegisterNo;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonInitialize.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

static	bool	MacroInitialize(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonInitialize	*V=dynamic_cast<ButtonInitialize *>(Instance);
	if(V==NULL){
		return false;
	}

	V->CommandInitialize();

	return true;
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Initialize";
		Functions[ret].Explain.append(/**/"Clear all items");
		Functions[ret].DLL_ExcuteMacro	=MacroInitialize;
		ret++;
	}

	return ret;
}
//==================================================================================================
ButtonInitialize::ButtonInitialize(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=58;
	ioMode			=NULL;

	Button.setObjectName(/**/"ButtonInitialize");
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Initialize";
	resize(60,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonInitialize::~ButtonInitialize(void)
{
}

void	ButtonInitialize::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setObjectName(QString(/**/"Initialize")+QString::number(SystemRegisterNo));
	ResizeAction();

	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandBit(this,SystemRegisterNo,/**/"ButtonInitialize:ioMode");
			//connect(ioMode			,SIGNAL(changed())	,this	,SLOT(OperandChanged()));
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
			ioMode->Set(false);
		}
	}
}

void	ButtonInitialize::ResizeAction()
{
	Button.resize(width(),height());
}
void	ButtonInitialize::CommandInitialize(void)
{
	SlotClicked();
}
void	ButtonInitialize::SlotClicked()
{
	GetLayersBase()->GetResultThread()->SetCastAll();
	GetLayersBase()->GetResultThread()->WaitForFinishingCast();

	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqInitialize	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
		RCmd.SendOnly(GlobalPage ,0);
	}
	GetLayersBase()->InitializeToStart();
	GetLayersBase()->SetMasterCode(-1);
	GetLayersBase()->SetMasterName(/**/"");
	GetLayersBase()->SetRemark(/**/"");

	InitializedSpecifiedBroadcaster	ICmd;
	BroadcastSpecifiedDirectly(&ICmd);

	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
	if(ioMode!=NULL){
		ioMode->Set(true);
	}
	BroadcastDirectly(_BC_BuildForShow	,0);
}

//========================================================================================================

GUICmdReqInitialize::GUICmdReqInitialize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdReqInitialize::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
		AlgorithmBase	*ABase=DLL->GetInstance();
		ABase->InitializeToStart();
	}
	GetLayersBase()->InitializeToStart();
	GetLayersBase()->SetMasterCode(-1);
	GetLayersBase()->SetMasterName(/**/"");
	GetLayersBase()->SetRemark(/**/"");
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit(EInfo);

	SendAck(localPage);
}

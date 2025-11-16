#include "ResetCameraSeqResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ResetCameraSeq\ResetCameraSeq.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ResetCameraSeq.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XCameraCommon.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Camera";
static	const	char	*sName=/**/"ResetCameraSeq";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Reset camera from Sequence");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdResetCameraSeq(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ResetCameraSeq(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SystemRegisterNo";
	Data[0].Pointer				 =&((ResetCameraSeq *)Instance)->SystemRegisterNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ResetCameraSeq.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ResetCameraSeq::ResetCameraSeq(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SystemRegisterNo=60;
	ioMode			=NULL;
}

ResetCameraSeq::~ResetCameraSeq(void)
{
}

void	ResetCameraSeq::Prepare(void)
{
	if(GetLayersBase()->GetInsideLearningEditor()==false 
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			ioMode		=new SignalOperandInt(this,SystemRegisterNo,/**/"ResetCameraSeq:ioMode");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(ioMode,&Error)==false){
				ioMode->ShowErrorMessage(Error);
			}
			connect(ioMode	,SIGNAL(changed())	,this	,SLOT(OperandChanged())	,Qt::QueuedConnection);
		}
	}
}

void	ResetCameraSeq::OperandChanged()
{
	if(ioMode!=NULL){
		int	Cmd=ioMode->Get();
		if(GetLayersBase()->IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				SpecifiedBroadcasterSendResetCamera	RCmd;
				RCmd.Page	=page;
				RCmd.Cmd	=Cmd;
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
					BroadcastSpecifiedDirectly(&RCmd);
				}
			}
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdResetCameraSeq	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
				RCmd.Cmd	=Cmd;
				RCmd.Send(NULL,page,0);
			}
		}
	}
}

GUICmdResetCameraSeq::GUICmdResetCameraSeq(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdResetCameraSeq::Load(QIODevice *f)
{
	if(::Load(f,Cmd)==false)
		return false;
	return true;
}

bool	GUICmdResetCameraSeq::Save(QIODevice *f)
{
	if(::Save(f,Cmd)==false)
		return false;
	return true;
}


void	GUICmdResetCameraSeq::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	SpecifiedBroadcasterSendResetCamera	RCmd;
	RCmd.Page	=localPage;
	RCmd.Cmd	=Cmd;
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&RCmd);
	}
}
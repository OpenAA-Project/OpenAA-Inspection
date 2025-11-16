/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCalcAlignment\ButtonCalcAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonCalcAlignmentResource.h"
#include "ButtonCalcAlignment.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"CalcAlignment";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to calculate Alignment only");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushedAlignment(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonCalcAlignment(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonCalcAlignment *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonCalcAlignment *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonCalcAlignment *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonCalcAlignment *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonCalcAlignment.png")));
}


//==================================================================================================
ButtonCalcAlignment::ButtonCalcAlignment(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonCalcAlignment");
	Msg=/**/"Calc Alignment";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonCalcAlignment::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonCalcAlignment::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonCalcAlignment::SlotClicked (bool checked)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonCalcAlignment_LS,LID_2)/*"Calc alignment"*/);
	GetLayersBase()->AddMaxProcessing(-1,0);
	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushedAlignment	PushRequester(GetLayersBase(),sRoot,sName);
			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);
	}
	else{
		GUICmdPushedAlignment	PushRequester(GetLayersBase(),sRoot,sName);
		PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);
	}
	GetLayersBase()->CloseProcessingForm ();

	//????????????????????????????????????????????????s???????????????????????????????A????????????????????????????????XML???????o????????????????????????????????????
	//GetLayersBase()->PutCurrentResult();

	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	//BroadcastDirectly(_BC_Show			,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	ButtonCalcAlignment::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonCalcAlignment_LS,LID_0)/*"Execute"*/,LangSolver.GetString(ButtonCalcAlignment_LS,LID_1)/*"Calc Alignment"*/,this);
	p->SetMenuNumber(1050);
	Info.AppendList(p);
}
void	ButtonCalcAlignment::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
void	ButtonCalcAlignment::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked(true);
	SyncMode=false;
}


//======================================================================================
GUICmdPushedAlignment::GUICmdPushedAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPushedAlignment::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdPushedAlignment::Save(QIODevice *f)
{
	return true;
}

void	GUICmdPushedAlignment::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){

		//GetLayersBase()->SetCurrentInspectID(InspectionID);

		GetLayersBase()->AddMaxProcessing(localPage,4);
		int	TempStrategy=GetParamGlobal()->GetMaxScanStrategy();
		GetParamGlobal()->SetMaxScanStrategy(1);

		GetLayersBase()->PushExecuterState();
		GetLayersBase()->StepProcessing(localPage);
		//if(IsExecInitialAfterEdit==true)
		//	GetLayersBase()->ExecuteInitialAfterEdit(GetLayersBase()->GetEntryPoint());

		GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
		//GetLayersBase()->GetCurrentResultForCalc().SetStartTimeForInspection(GetLayersBase()->GetStartInspectionTime());
		GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

//		GetLayersBase()->SetForceChangedInspectID();
//		XDateTime	NowD=GetLayersBase()->GetStartInspectionTime();
//		GetLayersBase()->GetLogicDLLBase()->SetStartTimeForInspection(NowD);

		GetLayersBase()->StepProcessing(localPage);
		GetLayersBase()->ExecuteStartByInspection	(GetLayersBase()->GetEntryPoint());
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();

		GetLayersBase()->StepProcessing(localPage);
		GetLayersBase()->ExecutePreAlignment		(GetLayersBase()->GetEntryPoint());
		GetLayersBase()->StepProcessing(localPage);
		GetLayersBase()->ExecuteAlignment			(GetLayersBase()->GetEntryPoint());

		GetParamGlobal()->SetMaxScanStrategy(TempStrategy);
		GetLayersBase()->SendAckToMaster(localPage);
		GetLayersBase()->PopExecuterState();

	}
	else{
		SendAck(localPage);
	}
}

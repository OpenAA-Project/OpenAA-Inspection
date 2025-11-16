/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\StartProcessAgainButtonForDesktop\StartProcessAgainButtonForDesktop.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartProcessAgainButtonForDesktop.h"
#include "StartProcessAgainButtonResource.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"
#include "XIntClass.h"


static	const	char	*sRoot=/**/"Action";
static	const	char	*sName=/**/"StartProcessAgainButtonForDesktop";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for starting processing again");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushed(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdInspectionAgainReplied(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartProcessAgainButtonForDesktop(Base,parent));
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
	Data[0].Pointer				 =&((StartProcessAgainButtonForDesktop *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartProcessAgainButtonForDesktop *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartProcessAgainButtonForDesktop *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartProcessAgainButtonForDesktop *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ExecInitialAfterEdit";
	Data[4].Pointer				 =&((StartProcessAgainButtonForDesktop *)Instance)->ExecInitialAfterEdit;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartProcessAgainForDesktop.png")));
}

static	bool	MacroPush(GUIFormBase *Instance ,QStringList &Args)
{
	StartProcessAgainButtonForDesktop	*V=dynamic_cast<StartProcessAgainButtonForDesktop *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SlotClicked (true);
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Push";
		Functions[ret].Explain.append(/**/"Push and execute process again");
		Functions[ret].DLL_ExcuteMacro	=MacroPush;
		ret++;
	}
	return ret;
}
//==================================================================================================
StartProcessAgainButtonForDesktop::StartProcessAgainButtonForDesktop(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Retry";
	ExecInitialAfterEdit=true;
	resize(40,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

StartProcessAgainButtonForDesktop::~StartProcessAgainButtonForDesktop()
{

}

void	StartProcessAgainButtonForDesktop::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartProcessAgainButtonForDesktop::ResizeAction()
{
	Button.resize(width(),height());
}

void StartProcessAgainButtonForDesktop::SlotClicked (bool checked)
{
	for(int phase=0;phase<GetLayersBase()->GetPhaseNumb();phase++){
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(phase);
		GetLayersBase()->ClearAllAckFlag();
		GetLayersBase()->ShowProcessingForm("Processing again");
		GetLayersBase()->AddMaxProcessing(-1,8);
		if(GetParamComm()->ConnectedPCNumb!=0){
			for(int page=0;page<GetPageNumb();page++){
				GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
				PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
				PushRequester.IsExecInitialAfterEdit=ExecInitialAfterEdit;
				PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
			}
			GetLayersBase()->WaitAllAcknowledged(60*20);
		}
		else{
			GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
			PushRequester.IsExecInitialAfterEdit=ExecInitialAfterEdit;
			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);

			GetLayersBase()->SetShouldWriteResult(false);
			GetLayersBase()->PutCurrentResult();
			GetLayersBase()->SetShouldWriteResult(true);
		}
		GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
		GetLayersBase()->CloseProcessingForm ();

		BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
	GetLayersBase()->TF_SetCurrentScanPhaseNumber(0);
}
void	StartProcessAgainButtonForDesktop::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(StartProcessAgainButton_LS,LID_0)/*"Execute"*/,LangSolver.GetString(StartProcessAgainButton_LS,LID_1)/*"Retry processing"*/,this);
	p->SetMenuNumber(200);
	Info.AppendList(p);
}
void	StartProcessAgainButtonForDesktop::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

GUICmdPushed::GUICmdPushed(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	InspectionID=0;
	IsExecInitialAfterEdit=true;
}

bool	GUICmdPushed::Load(QIODevice *f)
{
	if(::Load(f,InspectionID)==false)
		return false;
	if(::Load(f,IsExecInitialAfterEdit)==false)
		return false;
	return true;
}
bool	GUICmdPushed::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,IsExecInitialAfterEdit)==false)
		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
		if(localPage==0){
			if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
				for(int page=0;page<GetPageNumb();page++){
					for(int Layer=0;Layer<GetLayerNumb();Layer++){
						GetLayersBase()->GetPageData(page)->GetLayerData(Layer)->RestoreTargetImageFromRaw();
					}
				}
			}

			GetLayersBase()->SetCurrentInspectID(InspectionID);


			GetLayersBase()->AddMaxProcessing(localPage,8);
			int	TempStrategy=GetParamGlobal()->GetMaxScanStrategy();
			GetParamGlobal()->SetMaxScanStrategy(1);

			int	CPoint[6];
			GetLayersBase()->GetCalcPoint(CPoint);
			CPoint[1]=CPoint[0];
			int	CurrentCalcPoint=CPoint[0];
			CurrentCalcPoint--;
			if(CurrentCalcPoint<0)
				CurrentCalcPoint=GetParamGlobal()->NGCacheNumb-1;
			if(GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByInspection
			|| GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByScanOnly){
				GetLayersBase()->DecPoint();
				CPoint[1]--;
				if(CPoint[1]<0)
					CPoint[1]=GetParamGlobal()->NGCacheNumb-1;
			}

			GetLayersBase()->PushExecuterState();
			GetLayersBase()->StepProcessing(localPage);
			if(IsExecInitialAfterEdit==true){
				ExecuteInitialAfterEditInfo EInfo;
				GetLayersBase()->ExecuteInitialAfterEdit(EInfo);
			}

			XDateTime	SaveTm=GetLayersBase()->GetStartInspectTime();
			DWORD		SaveRm=GetLayersBase()->GetStartInspectionTimeMilisec();

			GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
			GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteStartByInspection	(false);
			ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
			if(CurrentResult!=NULL){
				CurrentResult->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());

				DWORD	C=GetComputerMiliSec();
				DWORD	Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->ExecutePreAlignment		(false);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecutePreAlignment=Cn-C;
				C=Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->ExecuteAlignment			(false);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecuteAlignment=Cn-C;
				C=Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->ExecutePreProcessing		(false);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecutePreProcessing=Cn-C;
				C=Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->ExecuteProcessing			(false);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecuteProcessing=Cn-C;
				C=Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->ExecuteProcessingRevived	(false);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
				C=Cn;

				GetLayersBase()->StepProcessing(localPage);
				GetLayersBase()->SetShouldWriteResult(false);
				GetLayersBase()->ExecutePostProcessing		(false);		
				GetLayersBase()->SetShouldWriteResult(true);
				Cn=GetComputerMiliSec();
				CurrentResult->ExecTime.TM_ExecutePostProcessing=Cn-C;
				C=Cn;

				GetParamGlobal()->SetMaxScanStrategy(TempStrategy);

				GetLayersBase()->SendAckToMaster(localPage);

				CmdInspectionAgainReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
				PacketReplied.Result		=CmdInspectionAgainReplied::_OK;
				PacketReplied.NGCounts		=CurrentResult->GetNGCount();
				PacketReplied.TimeOutBreak	=CurrentResult->GetTimeOutBreak()	;
				PacketReplied.MaxErrorBreak	=CurrentResult->GetMaxErrorBreak()	;
				DataInExecuter	*Re			=GetLayersBase()->GetExecuter(CurrentResult);
				PacketReplied.ExecuterID	=Re->GetID();
				if(GetParamComm()->Mastered==true){
					for(int page=0;page<GetPageNumb();page++){
						Re->SetResultReceivedFlag(page,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
					}
				}
				else{
					Re->SetResultReceivedFlag(localPage,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
				}
				GetLayersBase()->PopExecuterState();
				GetLayersBase()->SetCalcPoint(CPoint);
				GetLayersBase()->SetStartInspectTime(SaveTm);
				GetLayersBase()->SetStartInspectionTimeMilisec(SaveRm);
			}
		}
		else{
			ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
			if(CurrentResult!=NULL){
				DataInExecuter	*Re			=GetLayersBase()->GetExecuter(CurrentResult);
				Re->SetResultReceivedFlag(localPage,0,false,false);
			}
		}
	SendAck(localPage);
}

CmdInspectionAgainReplied::CmdInspectionAgainReplied(LayersBase *base,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdInspectionAgainReplied::Load(QIODevice *f)
{
	BYTE	ResultData;
	if(::Load(f,ResultData)==false)
		return false;
	Result=(__Result)ResultData;
	if(::Load(f,NGCounts)==false)
		return false;
	if(::Load(f,TimeOutBreak)==false)
		return false;
	if(::Load(f,MaxErrorBreak)==false)
		return false;
	if(::Load(f,ExecuterID)==false)
		return false;
	return true;
}
bool	CmdInspectionAgainReplied::Save(QIODevice *f)
{
	BYTE	ResultData=(BYTE)Result;
	if(::Save(f,ResultData)==false)
		return false;
	if(::Save(f,NGCounts)==false)
		return false;
	if(::Save(f,TimeOutBreak)==false)
		return false;
	if(::Save(f,MaxErrorBreak)==false)
		return false;
	if(::Save(f,ExecuterID)==false)
		return false;
	return true;
}

void	CmdInspectionAgainReplied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=L->GetExecuter(ExecuterID);
	Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	SendAck(localPage);
}


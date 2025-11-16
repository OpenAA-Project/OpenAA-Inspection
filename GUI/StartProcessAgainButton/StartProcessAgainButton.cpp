/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartProcessAgainButton\StartProcessAgainButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "StartProcessAgainButtonResource.h"
#include "StartProcessAgainButton.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"
#include "StartProcessAgainButtonPacket.h"


static	const	char	*sRoot=/**/"Action";
static	const	char	*sName=/**/"StartProcessAgainButton";

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
	return(new StartProcessAgainButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<8)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((StartProcessAgainButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartProcessAgainButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartProcessAgainButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartProcessAgainButton *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ExecInitialAfterEdit";
	Data[4].Pointer				 =&((StartProcessAgainButton *)Instance)->ExecInitialAfterEdit;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MaxInspectMilisec";
	Data[5].Pointer				 =&((StartProcessAgainButton *)Instance)->MaxInspectMilisec;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"OutputResult";
	Data[6].Pointer				 =&((StartProcessAgainButton *)Instance)->OutputResult;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ForceBindAllPhase";
	Data[7].Pointer				 =&((StartProcessAgainButton *)Instance)->ForceBindAllPhase;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartProcessAgain.png")));
}

static	bool	MacroPush(GUIFormBase *Instance ,QStringList &Args)
{
	StartProcessAgainButton	*V=dynamic_cast<StartProcessAgainButton *>(Instance);
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
StartProcessAgainButton::StartProcessAgainButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MaxInspectMilisec=1000000;
	OutputResult	 =false;
	ForceBindAllPhase=false;
	NowOnRunning	=false;

	Button.setParent(this);
	Button.setObjectName(/**/"StartProcessAgainButtonBtn");
	Button.move(0,0);
	Msg=/**/"Retry";
	ExecInitialAfterEdit=true;
	resize(40,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	RepeatCount_StartByInspection=1;
	RepeatCount_Captured		=1;
	RepeatCount_PreAlignent		=1;
	RepeatCount_Alignent		=1;
	RepeatCount_PreProcessing	=1;
	RepeatCount_Processing		=1;
	RepeatCount_PostProcessing	=1;

	GetParamGUI()->SetParam(&RepeatCount_StartByInspection, /**/"StartProcessAgain",/**/"RepeatCount_StartByInspection"	
												,"Count of repeated turn for StartByInspection"		);
	GetParamGUI()->SetParam(&RepeatCount_PreAlignent, /**/"StartProcessAgain",/**/"RepeatCount_Captured"	
												,"Count of repeated turn for Captured"		);
	GetParamGUI()->SetParam(&RepeatCount_PreAlignent, /**/"StartProcessAgain",/**/"RepeatCount_PreAlignent"	
												,"Count of repeated turn for PreAlignment"		);
	GetParamGUI()->SetParam(&RepeatCount_Alignent, /**/"StartProcessAgain",/**/"RepeatCount_Alignent"	
												,"Count of repeated turn for Alignment"		);
	GetParamGUI()->SetParam(&RepeatCount_PreProcessing, /**/"StartProcessAgain",/**/"RepeatCount_PreProcessing"	
												,"Count of repeated turn for PreProcessing"		);
	GetParamGUI()->SetParam(&RepeatCount_Processing, /**/"StartProcessAgain",/**/"RepeatCount_Processing"	
												,"Count of repeated turn for Processing"		);
	GetParamGUI()->SetParam(&RepeatCount_PostProcessing, /**/"StartProcessAgain",/**/"RepeatCount_PostProcessing"	
												,"Count of repeated turn for PostProcessing"		);

}

StartProcessAgainButton::~StartProcessAgainButton(void)
{
}

void	StartProcessAgainButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartProcessAgainButton::ResizeAction()
{
	Button.resize(width(),height());
}

void StartProcessAgainButton::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetShadowLevel()>0){
		return;
	}
	NowOnRunning=true;
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	int	CurrentPhase=0;
	if(PhaseCodes.GetCount()>0)
		CurrentPhase=PhaseCodes[0];
	else
		CurrentPhase=GetLayersBase()->GetCurrentPhase();

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(StartProcessAgainButton_LS,LID_3)/*"Processing again"*/);
	GetLayersBase()->SetMaxProcessing(0);

	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
//			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForDisplay();
			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
			PushRequester.IsExecInitialAfterEdit=ExecInitialAfterEdit;
			PushRequester.MaxInspectMilisec		=MaxInspectMilisec;
			PushRequester.ForceBindAllPhase		=ForceBindAllPhase;

			PushRequester.RepeatCount_StartByInspection	=RepeatCount_StartByInspection	;
			PushRequester.RepeatCount_Captured			=RepeatCount_Captured		;
			PushRequester.RepeatCount_PreAlignent		=RepeatCount_PreAlignent	;
			PushRequester.RepeatCount_Alignent			=RepeatCount_Alignent		;
			PushRequester.RepeatCount_PreProcessing		=RepeatCount_PreProcessing	;
			PushRequester.RepeatCount_Processing		=RepeatCount_Processing		;
			PushRequester.RepeatCount_PostProcessing	=RepeatCount_PostProcessing	;

			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);
	}
	else{
		GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
//		PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForDisplay();
		PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		PushRequester.IsExecInitialAfterEdit=ExecInitialAfterEdit;
		PushRequester.MaxInspectMilisec		=MaxInspectMilisec;
		PushRequester.ForceBindAllPhase		=ForceBindAllPhase;

		PushRequester.RepeatCount_StartByInspection	=RepeatCount_StartByInspection	;
		PushRequester.RepeatCount_Captured		=RepeatCount_Captured		;
		PushRequester.RepeatCount_PreAlignent	=RepeatCount_PreAlignent	;
		PushRequester.RepeatCount_Alignent		=RepeatCount_Alignent		;
		PushRequester.RepeatCount_PreProcessing	=RepeatCount_PreProcessing	;
		PushRequester.RepeatCount_Processing	=RepeatCount_Processing		;
		PushRequester.RepeatCount_PostProcessing=RepeatCount_PostProcessing	;

		PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);

		GetLayersBase()->SetShouldWriteResult(false);
		if(OutputResult==true)
			GetLayersBase()->PutForceResult(PushRequester.InspectionID,true,false);
		GetLayersBase()->SetShouldWriteResult(true);
	}
	GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	GetLayersBase()->CloseProcessingForm ();
	//GetLayersBase()->SetCurrentPhase(CurrentPhase);

	//??}?e?d?A?s??E?e?A?A?A????C?AXML?E?o?I?3?e?A??E?U??
	//GetLayersBase()->PutCurrentResult();

	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	//BroadcastDirectly(_BC_Show			,GetLayersBase()->GetCurrentInspectIDForDisplay());
	NowOnRunning=false;
}

void	StartProcessAgainButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
									,LangSolver.GetString(StartProcessAgainButton_LS,LID_0)/*"Execute"*/
									,LangSolver.GetString(StartProcessAgainButton_LS,LID_1)/*"Retry processing"*/
									,this);
	p->SetMenuNumber(200);
	Info.AppendList(p);
}
void	StartProcessAgainButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	StartProcessAgainButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqPush	*CmdReqPushVar=dynamic_cast<CmdReqPush *>(packet);
	if(CmdReqPushVar!=NULL){
		SlotClicked(true);
		return;
	}
}

//===================================================================================================================

GUICmdPushed::GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
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
	if(::Load(f,MaxInspectMilisec)==false)
		return false;
	if(::Load(f,ForceBindAllPhase)==false)
		return false;
	if(::Load(f,RepeatCount_StartByInspection)==false)		return false;
	if(::Load(f,RepeatCount_Captured		)==false)		return false;
	if(::Load(f,RepeatCount_PreAlignent		)==false)		return false;
	if(::Load(f,RepeatCount_Alignent		)==false)		return false;
	if(::Load(f,RepeatCount_PreProcessing	)==false)		return false;
	if(::Load(f,RepeatCount_Processing		)==false)		return false;
	if(::Load(f,RepeatCount_PostProcessing	)==false)		return false;
	return true;
}
bool	GUICmdPushed::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,IsExecInitialAfterEdit)==false)
		return false;
	if(::Save(f,MaxInspectMilisec)==false)
		return false;
	if(::Save(f,ForceBindAllPhase)==false)
		return false;
	if(::Save(f,RepeatCount_StartByInspection)==false)		return false;
	if(::Save(f,RepeatCount_Captured		)==false)		return false;
	if(::Save(f,RepeatCount_PreAlignent		)==false)		return false;
	if(::Save(f,RepeatCount_Alignent		)==false)		return false;
	if(::Save(f,RepeatCount_PreProcessing	)==false)		return false;
	if(::Save(f,RepeatCount_Processing		)==false)		return false;
	if(::Save(f,RepeatCount_PostProcessing	)==false)		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
//	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){

	if(localPage==0){
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			for(int page=0;page<GetPageNumb();page++){
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					GetLayersBase()->GetPageData(page)->GetLayerData(Layer)->RestoreTargetImageFromRaw();
				}
			}
		}

		//if(GetParamGlobal()->AllocateTargetBuff==true
		//&& GetParamGlobal()->AllocCamTargetBuffer==true){
		//	GetLayersBase()->CopyTargetToCameraBuff();
		//}

		GetLayersBase()->SetCurrentInspectID(InspectionID);
		int32	TmpMaxInspectMilisec	=GetParamGlobal()->MaxInspectMilisec;
		GetParamGlobal()->MaxInspectMilisec	=MaxInspectMilisec;

		GetLayersBase()->AddMaxProcessing(localPage,7);
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
		int32	tModePhaseExecuteStartByInspection	=GetParamGlobal()->ModePhaseExecuteStartByInspection	;
		int32	tModePhaseExecuteCaptured			=GetParamGlobal()->ModePhaseExecuteCaptured				;
		int32	tModePhaseExecutePreAlignment		=GetParamGlobal()->ModePhaseExecutePreAlignment			;
		int32	tModePhaseExecuteAlignment			=GetParamGlobal()->ModePhaseExecuteAlignment			;
		int32	tModePhaseExecutePreProcessing		=GetParamGlobal()->ModePhaseExecutePreProcessing		;
		int32	tModePhaseExecuteProcessing			=GetParamGlobal()->ModePhaseExecuteProcessing			;
		int32	tModePhaseExecuteProcessingRevived	=GetParamGlobal()->ModePhaseExecuteProcessingRevived	;
		int32	tModePhaseExecutePostProcessing		=GetParamGlobal()->ModePhaseExecutePostProcessing		;
		int32	tModePhaseExecuteManageResult		=GetParamGlobal()->ModePhaseExecuteManageResult			;
		int32	tModePhaseOutputResult				=GetParamGlobal()->ModePhaseOutputResult				;
		int32	tModePhaseAdaptChangingThreshold	=GetParamGlobal()->ModePhaseAdaptChangingThreshold		;
		if(ForceBindAllPhase==true){
			GetParamGlobal()->ModePhaseExecuteStartByInspection		=-2;
			GetParamGlobal()->ModePhaseExecuteCaptured				=-2;
			GetParamGlobal()->ModePhaseExecutePreAlignment			=-2;
			GetParamGlobal()->ModePhaseExecuteAlignment				=-2;
			GetParamGlobal()->ModePhaseExecutePreProcessing			=-2;
			GetParamGlobal()->ModePhaseExecuteProcessing			=-2;
			GetParamGlobal()->ModePhaseExecuteProcessingRevived		=-2;
			GetParamGlobal()->ModePhaseExecutePostProcessing		=-2;
			GetParamGlobal()->ModePhaseExecuteManageResult			=-2;
			GetParamGlobal()->ModePhaseOutputResult					=-2;
			GetParamGlobal()->ModePhaseAdaptChangingThreshold		=-2;
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

//		GetLayersBase()->SetForceChangedInspectID();
//		XDateTime	NowD=GetLayersBase()->GetStartInspectionTime();
//		GetLayersBase()->GetLogicDLLBase()->SetStartTimeForInspection(NowD);

		ListPhasePageLayerPack	CapturedList;
		for(int phase=0;phase<GetPhaseNumb();phase++){
			for(int page=0;page<GetPageNumb();page++){
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					CapturedList.Add(phase,page,layer);
				}
			}
		}

		GetLayersBase()->StepProcessing(localPage);
		int	LastCurrentCalcPoint=GetLayersBase()->GetCurrentCalcPoint();
		for(int t=0;t<RepeatCount_StartByInspection;t++){
			GetLayersBase()->SetProcessDone(false);
			GetLayersBase()->SetCurrentCalcPoint(LastCurrentCalcPoint);
			GetLayersBase()->ExecuteStartByInspection	(false);
		}
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			CurrentResult->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());

			DWORD	C=GetComputerMiliSec();
			DWORD	Cn;

			GetLayersBase()->StepProcessing(localPage);
			for(int t=0;t<RepeatCount_Captured;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->ExecuteCaptured		(CapturedList,false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteCaptured=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			int	Index=GetLayersBase()->GetIndexInCurrentStateExecuter(DataInExecuter::FinExecuteStartByInspection);
			for(int t=0;t<RepeatCount_PreAlignent;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteStartByInspection);
				GetLayersBase()->ExecutePreAlignment		(false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			for(int t=0;t<RepeatCount_Alignent;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreAlignment);
				GetLayersBase()->ExecuteAlignment			(false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			for(int t=0;t<RepeatCount_PreProcessing;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteAlignment);
				GetLayersBase()->ExecutePreProcessing		(false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreProcessing=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			for(int t=0;t<RepeatCount_Processing;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreProcessing);
				GetLayersBase()->ExecuteProcessing			(false);
			}
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
			for(int t=0;t<RepeatCount_PostProcessing;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteProcessingRevived);
				GetLayersBase()->ExecutePostProcessing		(false);		
			}
			GetLayersBase()->SetShouldWriteResult(true);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePostProcessing=Cn-C;
			C=Cn;

			GetParamGlobal()->SetMaxScanStrategy(TempStrategy);

			GetLayersBase()->SendAckToMaster(localPage);
	
			CmdInspectionAgainReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
			PacketReplied.Result	=CmdInspectionAgainReplied::_OK;
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
			/*
			PacketReplied.SendFromSlaveToMaster(
						GetLayersBase()->GetGlobalPageFromLocal(localPage)
						,0);
			*/
		}
		GetLayersBase()->PopExecuterState();
		GetLayersBase()->SetCalcPoint(CPoint);
		GetLayersBase()->SetStartInspectTime(SaveTm);
		GetLayersBase()->SetStartInspectionTimeMilisec(SaveRm);
		GetParamGlobal()->MaxInspectMilisec=TmpMaxInspectMilisec;

		GetParamGlobal()->ModePhaseExecuteStartByInspection	=tModePhaseExecuteStartByInspection	;
		GetParamGlobal()->ModePhaseExecuteCaptured			=tModePhaseExecuteCaptured			;
		GetParamGlobal()->ModePhaseExecutePreAlignment		=tModePhaseExecutePreAlignment		;
		GetParamGlobal()->ModePhaseExecuteAlignment			=tModePhaseExecuteAlignment			;
		GetParamGlobal()->ModePhaseExecutePreProcessing		=tModePhaseExecutePreProcessing		;
		GetParamGlobal()->ModePhaseExecuteProcessing		=tModePhaseExecuteProcessing		;
		GetParamGlobal()->ModePhaseExecuteProcessingRevived	=tModePhaseExecuteProcessingRevived	;
		GetParamGlobal()->ModePhaseExecutePostProcessing	=tModePhaseExecutePostProcessing	;
		GetParamGlobal()->ModePhaseExecuteManageResult		=tModePhaseExecuteManageResult		;
		GetParamGlobal()->ModePhaseOutputResult				=tModePhaseOutputResult				;
		GetParamGlobal()->ModePhaseAdaptChangingThreshold	=tModePhaseAdaptChangingThreshold	;

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

CmdInspectionAgainReplied::CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
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

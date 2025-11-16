/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartScanningAgain\StartScanningAgain.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "StartScanningAgainResource.h"
#include "StartScanningAgain.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Action";
static	const	char	*sName=/**/"StartScanningAgain";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for scanning again");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushed			(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdScanningAgainReplied	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartScanningAgain(Base,parent));
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
	Data[0].Pointer				 =&((StartScanningAgain *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((StartScanningAgain *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((StartScanningAgain *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((StartScanningAgain *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ExecInitialAfterEdit";
	Data[4].Pointer				 =&((StartScanningAgain *)Instance)->ExecInitialAfterEdit;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MaxInspectMilisec";
	Data[5].Pointer				 =&((StartScanningAgain *)Instance)->MaxInspectMilisec;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartProcessAgain.png")));
}

static	bool	MacroPush(GUIFormBase *Instance ,QStringList &Args)
{
	StartScanningAgain	*V=dynamic_cast<StartScanningAgain *>(Instance);
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
		Functions[ret].Explain.append(/**/"Push and execute scanning again");
		Functions[ret].DLL_ExcuteMacro	=MacroPush;
		ret++;
	}
	return ret;
}
//==================================================================================================
StartScanningAgain::StartScanningAgain(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MaxInspectMilisec=1000000;

	Button.setParent(this);
	Button.setObjectName(/**/"StartScanningAgainBtn");
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
	RepeatCount_PreScanning		=1;
	RepeatCount_Scanning		=1;
	RepeatCount_PostScanning	=1;

	GetParamGUI()->SetParam(&RepeatCount_StartByInspection, /**/"StartScanningAgain",/**/"RepeatCount_StartByInspection"	
												,"Count of repeated turn for StartByInspection"		);
	GetParamGUI()->SetParam(&RepeatCount_Captured, /**/"StartScanningAgain",/**/"RepeatCount_Captured"	
												,"Count of repeated turn for Captured"		);
	GetParamGUI()->SetParam(&RepeatCount_PreAlignent, /**/"StartScanningAgain",/**/"RepeatCount_PreAlignent"	
												,"Count of repeated turn for PreAlignment"		);
	GetParamGUI()->SetParam(&RepeatCount_Alignent, /**/"StartScanningAgain",/**/"RepeatCount_Alignent"	
												,"Count of repeated turn for Alignment"		);
	GetParamGUI()->SetParam(&RepeatCount_PreScanning, /**/"StartScanningAgain",/**/"RepeatCount_PreScanning"	
														,"Count of repeated turn for PreScanning"		);
	GetParamGUI()->SetParam(&RepeatCount_Scanning, /**/"StartScanningAgain",/**/"RepeatCount_Scanning"	
														,"Count of repeated turn for Scanning"		);
	GetParamGUI()->SetParam(&RepeatCount_PostScanning, /**/"StartScanningAgain",/**/"RepeatCount_PostScanning"	
														,"Count of repeated turn for PostScanning"		);

}

StartScanningAgain::~StartScanningAgain(void)
{
}

void	StartScanningAgain::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	StartScanningAgain::ResizeAction()
{
	Button.resize(width(),height());
}

void StartScanningAgain::SlotClicked (bool checked)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	int	CurrentPhase=0;
	if(PhaseCodes.GetCount()>0)
		CurrentPhase=PhaseCodes[0];
	else
		CurrentPhase=GetLayersBase()->GetCurrentPhase();

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Processing again");
	GetLayersBase()->SetMaxProcessing(0);
	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
//			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForDisplay();
			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
			PushRequester.IsExecInitialAfterEdit=ExecInitialAfterEdit;
			PushRequester.MaxInspectMilisec		=MaxInspectMilisec;

			PushRequester.RepeatCount_StartByInspection	=RepeatCount_StartByInspection	;
			PushRequester.RepeatCount_Captured			=RepeatCount_Captured		;
			PushRequester.RepeatCount_PreAlignent		=RepeatCount_PreAlignent	;
			PushRequester.RepeatCount_Alignent			=RepeatCount_Alignent		;
			PushRequester.RepeatCount_PreScanning		=RepeatCount_PreScanning	;
			PushRequester.RepeatCount_Scanning			=RepeatCount_Scanning		;
			PushRequester.RepeatCount_PostScanning		=RepeatCount_PostScanning	;

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

		PushRequester.RepeatCount_StartByInspection	=RepeatCount_StartByInspection	;
		PushRequester.RepeatCount_Captured		=RepeatCount_Captured		;
		PushRequester.RepeatCount_PreAlignent	=RepeatCount_PreAlignent	;
		PushRequester.RepeatCount_Alignent		=RepeatCount_Alignent		;
		PushRequester.RepeatCount_PreScanning	=RepeatCount_PreScanning	;
		PushRequester.RepeatCount_Scanning		=RepeatCount_Scanning		;
		PushRequester.RepeatCount_PostScanning	=RepeatCount_PostScanning	;

		PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);

		GetLayersBase()->SetShouldWriteResult(false);
		GetLayersBase()->SetShouldWriteResult(true);
	}
	GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());
	GetLayersBase()->CloseProcessingForm ();
	//GetLayersBase()->SetCurrentPhase(CurrentPhase);

	//??}?e?d?A?s??E?e?A?A?A????C?AXML?E?o?I?3?e?A??E?U??
	//GetLayersBase()->PutCurrentResult();

	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	//BroadcastDirectly(_BC_Show			,GetLayersBase()->GetCurrentInspectIDForDisplay());
}
void	StartScanningAgain::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"Execute"
										,"Retry processing",this);
	p->SetMenuNumber(200);
	Info.AppendList(p);
}
void	StartScanningAgain::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

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
	if(::Load(f,RepeatCount_StartByInspection)==false)		return false;
	if(::Load(f,RepeatCount_Captured		)==false)		return false;
	if(::Load(f,RepeatCount_PreAlignent		)==false)		return false;
	if(::Load(f,RepeatCount_Alignent		)==false)		return false;
	if(::Load(f,RepeatCount_PreScanning		)==false)		return false;
	if(::Load(f,RepeatCount_Scanning		)==false)		return false;
	if(::Load(f,RepeatCount_PostScanning	)==false)		return false;
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
	if(::Save(f,RepeatCount_StartByInspection)==false)		return false;
	if(::Save(f,RepeatCount_Captured		)==false)		return false;
	if(::Save(f,RepeatCount_PreAlignent		)==false)		return false;
	if(::Save(f,RepeatCount_Alignent		)==false)		return false;
	if(::Save(f,RepeatCount_PreScanning		)==false)		return false;
	if(::Save(f,RepeatCount_Scanning		)==false)		return false;
	if(::Save(f,RepeatCount_PostScanning	)==false)		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
//	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){

	if(localPage==0){
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			for(int page=0;page<GetPageNumb();page++){
				for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
					GetLayersBase()->GetPageData(page)->GetLayerData(Layer)->RestoreTargetImageFromRaw();
				}
			}
		}

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
			
			ListPhasePageLayerPack	CapturedList;
			GetLayersBase()->MakeCapturedAllList(CapturedList);

			GetLayersBase()->StepProcessing(localPage);
			//int	Index=GetLayersBase()->GetIndexInCurrentStateExecuter(DataInExecuter::FinExecuteStartByInspection);
			for(int t=0;t<RepeatCount_Captured;t++){
				GetLayersBase()->SetProcessDone(false);
				//GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteStartByInspection);
				GetLayersBase()->ExecuteCaptured(CapturedList,false);
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
			for(int t=0;t<RepeatCount_PreScanning;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteAlignment);
				GetLayersBase()->ExecutePreScanning		(false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreScanning=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			for(int t=0;t<RepeatCount_Scanning;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecutePreScanning);
				GetLayersBase()->ExecuteScanning			(false);
			}
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteScanning=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->SetShouldWriteResult(false);
			for(int t=0;t<RepeatCount_PostScanning;t++){
				GetLayersBase()->SetProcessDone(false);
				GetLayersBase()->SetCurrentStateInExecuter(Index ,DataInExecuter::FinExecuteScanning);
				GetLayersBase()->ExecutePostScanning		(false);		
			}
			GetLayersBase()->SetShouldWriteResult(true);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePostScanning=Cn-C;
			C=Cn;

			GetParamGlobal()->SetMaxScanStrategy(TempStrategy);

			GetLayersBase()->SendAckToMaster(localPage);

			CmdScanningAgainReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
			DataInExecuter	*Re			=GetLayersBase()->GetExecuter(CurrentResult);
			PacketReplied.ExecuterID	=Re->GetID();

			GetLayersBase()->PopExecuterState();
			GetLayersBase()->SetCalcPoint(CPoint);
			GetLayersBase()->SetStartInspectTime(SaveTm);
			GetLayersBase()->SetStartInspectionTimeMilisec(SaveRm);
			GetParamGlobal()->MaxInspectMilisec=TmpMaxInspectMilisec;
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

CmdScanningAgainReplied::CmdScanningAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdScanningAgainReplied::Load(QIODevice *f)
{
	if(::Load(f,ExecuterID)==false)
		return false;
	return true;
}
bool	CmdScanningAgainReplied::Save(QIODevice *f)
{
	if(::Save(f,ExecuterID)==false)
		return false;
	return true;
}

void	CmdScanningAgainReplied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase();
	SendAck(localPage);
}

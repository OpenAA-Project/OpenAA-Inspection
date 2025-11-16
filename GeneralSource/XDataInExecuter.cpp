/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XDataInExecuter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//---------------------------------------------------------------------------

#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "swap.h"
#include "XPointer.h"
#include "XAlgorithmBase.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "Regulus64Version.h"
#include "XResultDLLManager.h"
#include <omp.h>
#include "XCriticalFunc.h"
#include "XGUIFormBase.h"
#include "XErrorCode.h"
#include "XFileRegistry.h"
#include "XAnyData.h"
#include <QMessageBox>
#include "XGeneralStocker.h"
#include "XServiceForLayers.h"
#include "XResultAnalizer.h"
#include "XWriteResultThread.h"
#include "XEntryPoint.h"

//==================================================================================================
DataInExecuter::DataInExecuter(int id ,LayersBase *Base)
:ServiceForLayers(Base)
{
	ID					=id;	
	CurrentResultForCalc=NULL;
	Calculating			=true;
	InsideReEntrant		=0;
	DonePutCurrentResult=false;
	ReceivedResultCounts=NULL;
	State				=_None;
}
DataInExecuter::~DataInExecuter(void)
{
	if(ReceivedResultCounts!=NULL){
		delete	[]ReceivedResultCounts;
		ReceivedResultCounts=NULL;
	}
}

void	DataInExecuter::Initial(void)
{
	if(ReceivedResultCounts!=NULL){
		delete	[]ReceivedResultCounts;
	}
	ReceivedResultCounts=new ReceivedResultCountsParam[GetPageNumb()];
	InitializeState();
}

void	DataInExecuter::SetCurrentResultForCalc(ResultInspection *L){	CurrentResultForCalc=L;	}

void	DataInExecuter::SetStartTimeForInspect(XDateTime &d)
{
	CurrentResultForCalc->SetStartTimeForInspect(d);
}

void	DataInExecuter::ExecuteInitialAfterEditLoop	(int ExeID)
{
	if(InsideReEntrant==0){
		if(State==FinExecutePostProcessing && DonePutCurrentResult==false){
			//While idling
			State=NowExecuteInitialAfterEdit;
			Calculating=true;
			InsideReEntrant++;
			if(GetLayersBase()->GetResultThread()!=NULL){
				GetLayersBase()->GetResultThread()->ExecuteInitialAfterEdit(ExeID ,CurrentResultForCalc);
			}
			//CurrentResultForCalc=NULL;
			//CurrentResultForDraw=NULL;
			InsideReEntrant--;
			Calculating=false;
			State=FinExecutePostProcessing;
		}
		else{
			State=NowExecuteInitialAfterEdit;
			Calculating=true;
			InsideReEntrant++;
			if(GetLayersBase()->GetResultThread()!=NULL){
				GetLayersBase()->GetResultThread()->ExecuteInitialAfterEdit(ExeID ,CurrentResultForCalc);
			}
			//CurrentResultForCalc=NULL;
			//CurrentResultForDraw=NULL;
			InsideReEntrant--;
			Calculating=false;
			State=FinExecuteInitialAfterEdit;
		}

	}
}
ExeResult	DataInExecuter::ExecuteInitialAfterEdit	(int ExeID,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_true;
	if(InsideReEntrant==0){
		State=NowExecuteInitialAfterEdit;
		Calculating=true;
		InsideReEntrant++;
		if(GetLayersBase()->GetResultThread()!=NULL){
			GetLayersBase()->GetResultThread()->ExecuteInitialAfterEdit(ExeID ,CurrentResultForCalc);
			if(GetLayersBase()->GetGeneralStocker()!=NULL){
				GetLayersBase()->GetGeneralStocker()->ExecuteInitialAfterEditPrev(ExeID,CurrentResultForCalc);
			}
		}

		if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-1){
			PageDataInOnePhase	*Ph=GetLayersBase()->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecuteInitialAfterEdit();
			for(int Page=0;Page<GetPageNumb();Page++){
				GetLayersBase()->GetPageData(Page)->ClearDynamicMaskMap();
			}
		}
		else if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-2){
			for(int Phase=0;Phase<GetPhaseNumb();Phase++){
				PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(Phase);
				Ph->ExecuteFilterExecuteInitialAfterEdit();
				for(int Page=0;Page<GetPageNumb();Page++){
					Ph->GetPageData(Page)->ClearDynamicMaskMap();
				}
			}
		}
		else if(0<=GetParamGlobal()->ModePhaseExecuteInitialAfterEdit && GetParamGlobal()->ModePhaseExecuteInitialAfterEdit<GetPhaseNumb()){
			PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit);
			Ph->ExecuteFilterExecuteInitialAfterEdit();
			for(int Page=0;Page<GetPageNumb();Page++){
				Ph->GetPageData(Page)->ClearDynamicMaskMap();
			}
		}

		if(GetLayersBase()->GetLogicDLLBase()!=NULL){
			ExeResult	RR=GetLayersBase()->GetLogicDLLBase()->ExecuteInitialAfterEditPrev(ExeID,CurrentResultForCalc,EInfo);
		}

		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLayersBase()->GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLayersBase()->GetLogicDLLBase()->ExecuteInitialAfterEdit(ExeID,CurrentResultForCalc,EInfo);	
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
			if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-1){
				for(int Page=0;Page<GetPageNumb();Page++){
					GetLayersBase()->GetPageData(Page)->ExecuteInitialAfterEdit(EInfo,false);
				}
			}
			else if(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit==-2){
				for(int Phase=0;Phase<GetPhaseNumb();Phase++){
					for(int Page=0;Page<GetPageNumb();Page++){
						GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->ExecuteInitialAfterEdit(EInfo,false);
					}
				}
			}
			else if(0<=GetParamGlobal()->ModePhaseExecuteInitialAfterEdit && GetParamGlobal()->ModePhaseExecuteInitialAfterEdit<GetPhaseNumb()){
				for(int Page=0;Page<GetPageNumb();Page++){
					GetLayersBase()->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteInitialAfterEdit)->GetPageData(Page)->ExecuteInitialAfterEdit(EInfo,false);
				}
			}
		}while(RetryMode==true);

		if(GetLayersBase()->GetLogicDLLBase()!=NULL){
			ExeResult	RR=GetLayersBase()->GetLogicDLLBase()->ExecuteInitialAfterEditPost(ExeID,CurrentResultForCalc,EInfo);
		}
		InsideReEntrant--;
		if(GetLayersBase()->GetGeneralStocker()!=NULL){
			GetLayersBase()->GetGeneralStocker()->ExecuteInitialAfterEditPost(ExeID,CurrentResultForCalc);
		}
		Calculating=false;
		State=FinExecuteInitialAfterEdit;
	}
	return Ret;
}

ExeResult	DataInExecuter::ExecuteStartByScanOnly	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecuteStartByScanOnly;
	ClearReceivedResultCounts();
	State=FinExecuteStartByScanOnly;
	return Ret;
}
ExeResult	DataInExecuter::ExecuteStartByInspection(int ExeID)
{
	ExeResult	Ret=_ER_true;

	State=NowExecuteStartByInspection;
	DonePutCurrentResult=false;
//	while(CurrentResultForCalc->IsCompressing()==true){
//		GSleep(100);
//	}
	Result=_Result_None;
	LayersBase	*LBase=GetLayersBase();

	if(CurrentResultForCalc!=NULL){
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteStartByInspectionPrev(ExeID,CurrentResultForCalc);
		}

		if(GetParamGlobal()->GetMaxScanStrategy()<=1){
			if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
				if(LBase->GetCurrentPhase()==0){
					CurrentResultForCalc->ResetCalcDone();
				}
				for(int Page=0;Page<GetPageNumb();Page++){
					LBase->GetPageData(Page)->ClearDynamicMaskMap();
				}
			}
			else if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
				CurrentResultForCalc->ResetCalcDone();
				for(int Phase=0;Phase<GetPhaseNumb();Phase++){
					PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
					for(int Page=0;Page<GetPageNumb();Page++){
						Ph->GetPageData(Page)->ClearDynamicMaskMap();
					}
				}
			}
			else if(0<=GetParamGlobal()->ModePhaseExecuteStartByInspection && GetParamGlobal()->ModePhaseExecuteStartByInspection<GetPhaseNumb()){
				CurrentResultForCalc->ResetCalcDone();
				PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteStartByInspection);
				for(int Page=0;Page<GetPageNumb();Page++){
					Ph->GetPageData(Page)->ClearDynamicMaskMap();
				}
			}
			if(GetReceivedResultCounts()!=NULL){
				for(int page=0;page<GetPageNumb();page++){
					GetReceivedResultCounts()[page].Result= -1;
					GetReceivedResultCounts()[page].MaxErrorBreak=false;
					GetReceivedResultCounts()[page].TimeOutBreak	=false;
				}
			}
			CurrentResultForCalc->StartByInspection(ExeID);
			bool	RetryMode;
			do{
				RetryMode=false;
				if(GetLogicDLLBase()!=NULL){
					ExeResult	RR=GetLogicDLLBase()->ExecuteStartByInspection(ExeID,CurrentResultForCalc);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}while(RetryMode==true);
		}
		else if(GetParamComm()->Mastered==true){
			if(LBase->GetCurrentStrategicNumber()==0){
				if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
					for(int Page=0;Page<GetPageNumb();Page++){
						LBase->GetPageData(Page)->ClearDynamicMaskMap();
					}
				}
				else if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
					for(int Phase=0;Phase<GetPhaseNumb();Phase++){
						PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
						for(int Page=0;Page<GetPageNumb();Page++){
							Ph->GetPageData(Page)->ClearDynamicMaskMap();
						}
					}
				}
				else if(0<=GetParamGlobal()->ModePhaseExecuteStartByInspection && GetParamGlobal()->ModePhaseExecuteStartByInspection<GetPhaseNumb()){
					PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteStartByInspection);
					for(int Page=0;Page<GetPageNumb();Page++){
						Ph->GetPageData(Page)->ClearDynamicMaskMap();
					}
				}
				if(GetReceivedResultCounts()!=NULL){
					for(int page=0;page<GetPageNumb();page++){
						GetReceivedResultCounts()[page].Result= -1;
						GetReceivedResultCounts()[page].MaxErrorBreak=false;
						GetReceivedResultCounts()[page].TimeOutBreak	=false;
					}
				}
				CurrentResultForCalc->StartByInspection(ExeID);
			}
			bool	RetryMode;
			do{
				RetryMode=false;
				if(GetLogicDLLBase()!=NULL){
					ExeResult	RR=GetLogicDLLBase()->ExecuteStartByInspection(ExeID,CurrentResultForCalc);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}while(RetryMode==true);
		}
		else if(GetParamComm()->Mastered==false){
			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (LBase->GetCurrentStrategicNumberInExe()
												,PageList);
			IntClass *s=PageList.GetItem(0);
			if(s!=NULL){
				int	page=s->GetValue();
				LBase->GetPageData(page)->ClearDynamicMaskMap();
				if(GetReceivedResultCounts()!=NULL){
					GetReceivedResultCounts()[page].Result= -1;
					GetReceivedResultCounts()[page].MaxErrorBreak=false;
					GetReceivedResultCounts()[page].TimeOutBreak	=false;
				}
				CurrentResultForCalc->StartByInspection(ExeID);
				bool	RetryMode;
				do{
					RetryMode=false;
					if(GetLogicDLLBase()!=NULL){
						ExeResult	RR=GetLogicDLLBase()->ExecuteStartByInspection(ExeID,CurrentResultForCalc);
						if(RR==_ER_ReqRetryLater){
							RetryMode=true;
						}
						else{
							Ret=RR;
						}
					}
				}while(RetryMode==true);
			}
			else{
				LBase->SetErrorOccurs(Error_MismatchStrategyCode);
			}
		}
	}

	if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-1){
		CurrentResultForCalc->StartByInspection(ExeID);
		PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
		Ph->ExecuteFilterExecuteStartByInspection();
		int	iPageNumb=GetPageNumb();
		for(int Page=0;Page<iPageNumb;Page++){
			LBase->GetPageData(Page)->ExecuteStartByInspection(false);
		}
	}
	else if(GetParamGlobal()->ModePhaseExecuteStartByInspection==-2){
		CurrentResultForCalc->StartByInspection(ExeID);
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
			Ph->ExecuteFilterExecuteStartByInspection();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				Ph->GetPageData(Page)->ExecuteStartByInspection(false);
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecuteStartByInspection && GetParamGlobal()->ModePhaseExecuteStartByInspection<GetPhaseNumb()){
		CurrentResultForCalc->StartByInspection(ExeID);
		PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteStartByInspection);
		Ph->ExecuteFilterExecuteStartByInspection();
		int	iPageNumb=GetPageNumb();
		for(int Page=0;Page<iPageNumb;Page++){
			Ph->GetPageData(Page)->ExecuteStartByInspection(false);
		}
	}
	if(CurrentResultForCalc!=NULL){
		CurrentResultForCalc->SetAliveTillPush(true); 
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteStartByInspectionPost(ExeID,CurrentResultForCalc);
		}
	}
	State=FinExecuteStartByInspection;
	return Ret;
}

ExeResult	DataInExecuter::ExecuteCaptured		(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	ExeResult	Ret=_ER_true;
	if(CurrentResultForCalc!=NULL){
		if(GetLayersBase()->GetGeneralStocker()!=NULL){
			GetLayersBase()->GetGeneralStocker()->ExecuteCapturedPrev(ExeID,CurrentResultForCalc,CapturedList);
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecuteCaptured(ExeID,CurrentResultForCalc,CapturedList);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	if(GetLayersBase()->GetGeneralStocker()!=NULL && CurrentResultForCalc!=NULL){
		GetLayersBase()->GetGeneralStocker()->ExecuteCapturedPost(ExeID,CurrentResultForCalc,CapturedList);
	}
	return Ret;
}

ExeResult	DataInExecuter::ExecutePreAlignment		(int ExeID)
{
	ExeResult	Ret=_ER_true;

	State=NowExecutePreAlignment;
	Calculating=true;
	LayersBase	*LBase=GetLayersBase();
	if(CurrentResultForCalc!=NULL){

		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecutePreAlignmentPrev(ExeID,CurrentResultForCalc);
		}

		StartInspectionTimeMilisec=GetComputerMiliSec();
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			if(GetParamGlobal()->GetMaxScanStrategy()<=1){
				if(GetParamGlobal()->ModePhaseExecutePreAlignment==-1){
					for(int phase=0;phase<GetPhaseNumb();phase++){
						PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(phase);
						for(int page=0;page<GetPageNumb();page++){
							DataInPage *P=Ph->GetPageData(page);
							P->CopyTargetImageToRaw();
						}
					}	
				}
				else if(GetParamGlobal()->ModePhaseExecutePreAlignment==-2){
					for(int phase=0;phase<GetPhaseNumb();phase++){
						PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(phase);
						for(int page=0;page<GetPageNumb();page++){
							DataInPage *P=Ph->GetPageData(page);
							P->CopyTargetImageToRaw();
						}
					}	
				}
				else if(0<=GetParamGlobal()->ModePhaseExecutePreAlignment && GetParamGlobal()->ModePhaseExecutePreAlignment<GetPhaseNumb()){
					PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecutePreAlignment);
					for(int page=0;page<GetPageNumb();page++){
						DataInPage *P=Ph->GetPageData(page);
						P->CopyTargetImageToRaw();
					}
				}
			}
			else{
				IntList	PageList;
				GetParamGlobal()->GetStrategyPage (LBase->GetCurrentStrategicNumberInExe()
													,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					for(int phase=0;phase<GetPhaseNumb();phase++){
						PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(phase);
						DataInPage *P=Ph->GetPageData(page);
						P->CopyTargetImageToRaw();
					}
				}
			}
		}

		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecutePreAlignment(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	if(GetParamGlobal()->ModePhaseExecutePreAlignment==-1){
		PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
		Ph->ExecuteFilterExecutePreAlignment();
		int	iPageNumb=GetPageNumb();
		for(int Page=0;Page<iPageNumb;Page++){
			LBase->GetPageData(Page)->ExecutePreAlignment(false);
		}
	}
	else if(GetParamGlobal()->ModePhaseExecutePreAlignment==-2){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
			Ph->ExecuteFilterExecutePreAlignment();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				Ph->GetPageData(Page)->ExecutePreAlignment(false);
			}
		}
	}
	else if(0<=GetParamGlobal()->ModePhaseExecutePreAlignment && GetParamGlobal()->ModePhaseExecutePreAlignment<GetPhaseNumb()){
		PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecutePreAlignment);
		Ph->ExecuteFilterExecutePreAlignment();
		int	iPageNumb=GetPageNumb();
		for(int Page=0;Page<iPageNumb;Page++){
			Ph->GetPageData(Page)->ExecutePreAlignment(false);
		}
	}
	if(LBase->GetGeneralStocker()!=NULL && CurrentResultForCalc!=NULL){
		LBase->GetGeneralStocker()->ExecutePreAlignmentPost(ExeID,CurrentResultForCalc);
	}
	State=FinExecutePreAlignment;
	return Ret;
}
ExeResult	DataInExecuter::ExecuteAlignment		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecuteAlignment;

	if(CurrentResultForCalc!=NULL){
		LayersBase	*LBase=GetLayersBase();
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteAlignmentPrev(ExeID,CurrentResultForCalc);
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecuteAlignment(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		if(GetParamGlobal()->ModePhaseExecuteAlignment==-1){
			PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecuteAlignment();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				LBase->GetPageData(Page)->ExecuteAlignment(false);
			}
		}
		else if(GetParamGlobal()->ModePhaseExecuteAlignment==-2){
			for(int Phase=0;Phase<GetPhaseNumb();Phase++){
				PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
				Ph->ExecuteFilterExecuteAlignment();
				int	iPageNumb=GetPageNumb();
				for(int Page=0;Page<iPageNumb;Page++){
					Ph->GetPageData(Page)->ExecuteAlignment(false);
				}
			}
		}
		else if(0<=GetParamGlobal()->ModePhaseExecuteAlignment && GetParamGlobal()->ModePhaseExecuteAlignment<GetPhaseNumb()){
			PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecuteAlignment);
			Ph->ExecuteFilterExecuteAlignment();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				Ph->GetPageData(Page)->ExecuteAlignment(false);
			}
		}
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteAlignmentPost(ExeID,CurrentResultForCalc);
		}
	}
	State=FinExecuteAlignment;
	return Ret;
}
ExeResult	DataInExecuter::ExecutePreProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecutePreProcessing;
	if(CurrentResultForCalc!=NULL){
		LayersBase	*LBase=GetLayersBase();
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecutePreProcessingPrev(ExeID,CurrentResultForCalc);
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecutePreProcessing(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		if(GetParamGlobal()->ModePhaseExecutePreProcessing==-1){
			PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecutePreProcessing();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				LBase->GetPageData(Page)->ExecutePreProcessing(false);
			}
		}
		else if(GetParamGlobal()->ModePhaseExecutePreProcessing==-2){
			for(int Phase=0;Phase<GetPhaseNumb();Phase++){
				PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(Phase);
				Ph->ExecuteFilterExecuteAlignment();
				int	iPageNumb=GetPageNumb();
				for(int Page=0;Page<iPageNumb;Page++){
					Ph->GetPageData(Page)->ExecutePreProcessing(false);
				}
			}
		}
		else if(0<=GetParamGlobal()->ModePhaseExecutePreProcessing && GetParamGlobal()->ModePhaseExecutePreProcessing<GetPhaseNumb()){
			PageDataInOnePhase	*Ph=LBase->GetPageDataPhase(GetParamGlobal()->ModePhaseExecutePreProcessing);
			Ph->ExecuteFilterExecuteAlignment();
			int	iPageNumb=GetPageNumb();
			for(int Page=0;Page<iPageNumb;Page++){
				Ph->GetPageData(Page)->ExecutePreProcessing(false);
			}
		}
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecutePreProcessingPost(ExeID,CurrentResultForCalc);
		}
	}
	State=FinExecutePreProcessing;
	return Ret;
}
ExeResult	DataInExecuter::ExecuteProcessing		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecuteProcessing;
	if(CurrentResultForCalc!=NULL){
		LayersBase	*LBase=GetLayersBase();
		CurrentResultForCalc->InitialForInspection();


		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteProcessingPrev(ExeID,CurrentResultForCalc);
		}

		if(GetParamGlobal()->GetMaxScanStrategy()<=1){
			PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecuteProcessing();
			int	iPageNumb=GetPageNumb();
			for(int page=0;page<iPageNumb;page++){
				DataInPage *P=LBase->GetPageData(page);
				P->ClearNGCounterWithMutex();
			}	
		}
		else{
			PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecuteProcessing();

			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (LBase->GetCurrentStrategicNumberInExe()
												,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();
				DataInPage *P=LBase->GetPageData(page);
				P->ClearNGCounterWithMutex();
			}
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecuteProcessing(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		for(int page=0;page<GetPageNumb();page++){
			DataInPage *P=LBase->GetPageData(page);
			for(int layer=0;layer<GetLayerNumb(page);layer++){
				P->ClearAllMarkToProceed(layer);
			}
		}
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteProcessingPost(ExeID,CurrentResultForCalc);
		}
	}
	State=FinExecuteProcessing;
	return Ret;
}
ExeResult	DataInExecuter::ExecuteProcessingRevived(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecuteProcessingRevived;
	if(CurrentResultForCalc!=NULL){
		LayersBase	*LBase=GetLayersBase();
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteProcessingRevivedPrev(ExeID,CurrentResultForCalc);
		}
		int	iPageNumb=GetPageNumb();
		if(GetParamGlobal()->GetMaxScanStrategy()<=1){
			for(int page=0;page<iPageNumb;page++){
				DataInPage *P=LBase->GetPageData(page);
				for(int layer=0;layer<GetLayerNumb(page);layer++){
					P->ClearResultMark(layer);
				}
				CurrentResultForCalc->SetResultMarkForLearning(page);
			}	
		}
		else{
			IntList	PageList;
			GetParamGlobal()->GetStrategyPage (LBase->GetCurrentStrategicNumberInExe()
												,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();

				DataInPage *P=LBase->GetPageData(page);
				IntList	LayerList;
				GetParamGlobal()->GetStrategyLayer(LBase->GetCurrentStrategicNumberInExe()
												,page
												,LayerList);
				for(IntClass *c=LayerList.GetFirst();c!=NULL;c=c->GetNext()){
					P->ClearResultMark(c->GetValue());
				}
				CurrentResultForCalc->SetResultMarkForLearning(page);
			}
		}
		if(CurrentResultForCalc->IsResultMaxError()==false && CurrentResultForCalc->IsResultTimeOut()==false){
			PageDataInOnePhase	*Ph=LBase->GetCurrentPageDataPhase();
			Ph->ExecuteFilterExecuteProcessingRevived();
			for(int page=0;page<iPageNumb;page++){
				DataInPage *P=LBase->GetPageData(page);
				P->ClearNGCounterWithMutex();
				P->ExecuteProcessing(CurrentResultForCalc,false);
			}
			bool	RetryMode;
			do{
				RetryMode=false;
				if(GetLogicDLLBase()!=NULL){
					ExeResult	RR=GetLogicDLLBase()->ExecuteProcessingRevived(ExeID,CurrentResultForCalc);
					if(RR==_ER_ReqRetryLater){
						RetryMode=true;
					}
					else{
						Ret=RR;
					}
				}
			}while(RetryMode==true);
			
			for(int page=0;page<iPageNumb;page++){
				CurrentResultForCalc->CalcNGCounterAgain();
			}
		}
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecuteProcessingRevivedPost(ExeID,CurrentResultForCalc);
		}
	}
	State=FinExecuteProcessingRevived;
	return Ret;
}
ExeResult	DataInExecuter::ExecutePostProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecutePostProcessing;
	if(CurrentResultForCalc!=NULL){
		LayersBase	*LBase=GetLayersBase();

		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecutePostProcessingPrev(ExeID,CurrentResultForCalc);
		}
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecutePostProcessing(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);

		for(int Page=0;Page<GetPageNumb();Page++){
			LBase->GetPageData(Page)->ExecutePostProcessing(false);
		}

		//if(GetEntryPoint()->IsMasterPC()==false && GetParamComm()->GetConnectedPCNumb()==0){
		if(GetEntryPoint()->IsMasterPC()==false || GetParamComm()->GetConnectedPCNumb()==0){
			if(CurrentResultForCalc->GetNGCount()>=LBase->GetParamGlobal()->MaxNGCountsPerCam){
				CurrentResultForCalc->SetMaxErrorBreak(true);
			}
			else{
				CurrentResultForCalc->SetMaxErrorBreak(false);
			}
			if(GetComputerMiliSec()-StartInspectionTimeMilisec>=LBase->GetParamGlobal()->MaxInspectMilisec){
				CurrentResultForCalc->SetTimeOutBreak(true);
			}
			else{
				CurrentResultForCalc->SetTimeOutBreak(false);
			}
		}
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecuteManageResult	(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
		//}

		if(GetParamComm()->Mastered==false){
			if((GetParamGlobal()->GetMaxScanStrategy()<=1) 
				|| (GetParamGlobal()->GetMaxScanStrategy()<=(LBase->GetCurrentStrategicNumberInExe()+1))){
				if((LBase->GetCurrentScanPhaseNumber()+1)>=GetParamGlobal()->GetScanPhaseCount()){
					PutCurrentResult();
				}
			}
		}
		if(LBase->GetGeneralStocker()!=NULL){
			LBase->GetGeneralStocker()->ExecutePostProcessingPost(ExeID,CurrentResultForCalc);
		}
		CurrentResultForCalc->SetCurentCalcDone(true);
	}
	Calculating=false;
	State=FinExecutePostProcessing;
	return Ret;
}
ExeResult	DataInExecuter::PretendFinishProcessing	(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=FinExecutePostProcessing;
	return Ret;
}

ExeResult	DataInExecuter::ExecutePreScanning		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecutePreScanning;
	if(CurrentResultForCalc!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecutePreScanning(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	for(int Page=0;Page<GetPageNumb();Page++){
		GetLayersBase()->GetPageData(Page)->ExecutePreScanning(false);
	}
	State=FinExecutePreScanning;
	return Ret;
}
ExeResult	DataInExecuter::ExecuteScanning			(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecuteScanning;
	if(CurrentResultForCalc!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecuteScanning(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	for(int Page=0;Page<GetPageNumb();Page++){
		GetLayersBase()->GetPageData(Page)->ExecuteScanning(false);
	}
	State=FinExecuteScanning;
	return Ret;
}
ExeResult	DataInExecuter::ExecutePostScanning		(int ExeID)
{
	ExeResult	Ret=_ER_true;
	State=NowExecutePostScanning;
	if(CurrentResultForCalc!=NULL){
		bool	RetryMode;
		do{
			RetryMode=false;
			if(GetLogicDLLBase()!=NULL){
				ExeResult	RR=GetLogicDLLBase()->ExecutePostScanning(ExeID,CurrentResultForCalc);
				if(RR==_ER_ReqRetryLater){
					RetryMode=true;
				}
				else{
					Ret=RR;
				}
			}
		}while(RetryMode==true);
	}
	for(int Page=0;Page<GetPageNumb();Page++){
		GetLayersBase()->GetPageData(Page)->ExecutePostScanning(false);
	}
	State=FinExecutePostScanning;
	return Ret;
}

void	DataInExecuter::PushState(void)
{
	PushedState=State;
	State=_None;
}
void	DataInExecuter::PopState(void)
{
	State=PushedState;
}


LogicDLLBaseClass	*DataInExecuter::GetLogicDLLBase(void)
{
	return GetLayersBase()->GetLogicDLLBase();
}

void	DataInExecuter::PutCurrentResult(void)
{
	if(GetLayersBase()->GetResultThread()!=NULL){
		GetLayersBase()->GetResultThread()->PutCurrentToStock(GetLayersBase(),*CurrentResultForCalc);
	}

	DonePutCurrentResult=true;
}

void	DataInExecuter::PutForceCurrentResult(bool DependOnPhaseMode,bool DependOnPageMode)
{
	bool3	OK;
	bool MaxError , TimeOver;
	CurrentResultForCalc->GatherResult(OK ,MaxError , TimeOver,DependOnPhaseMode,DependOnPageMode);
	if(OK==true3 && MaxError==false && TimeOver==false){
		CurrentResultForCalc->SetOutputCode(1);
	}
	else{
		CurrentResultForCalc->SetOutputCode(2);
	}

	if(GetLayersBase()->GetResultThread()!=NULL){
		GetLayersBase()->GetResultThread()->PutForceToStock(GetLayersBase(),*CurrentResultForCalc);
	}

	DonePutCurrentResult=true;
}

void	DataInExecuter::InitializeState(void)
{
	if(State==_None)
		State=_None;
	else
		State=NowExecuteInitialAfterEdit;
}

void	DataInExecuter::ClearReceivedResultCounts(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			GetReceivedResultCounts()[page].Result= -1;
			GetReceivedResultCounts()[page].MaxErrorBreak=false;
			GetReceivedResultCounts()[page].TimeOutBreak	=false;
		}
	}
	else if(GetParamComm()->Mastered==true){
		if(GetLayersBase()->GetCurrentStrategicNumber()==0){
			for(int page=0;page<GetPageNumb();page++){
				GetReceivedResultCounts()[page].Result= -1;
				GetReceivedResultCounts()[page].MaxErrorBreak=false;
				GetReceivedResultCounts()[page].TimeOutBreak	=false;
			}
		}
	}
	else if(GetParamComm()->Mastered==false){
		IntList	PageList;
		GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		IntClass *s=PageList.GetItem(0);
		if(s!=NULL){
			int	page=s->GetValue();
			GetReceivedResultCounts()[page].Result= -1;
			GetReceivedResultCounts()[page].MaxErrorBreak=false;
			GetReceivedResultCounts()[page].TimeOutBreak	=false;
		}
	}
}

void	DataInExecuter::SetResultReceivedFlag(int Page ,int64 resultCounts,bool TimeOutBreak,bool MaxErrorBreak)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		GetReceivedResultCounts()[Page].Result			=resultCounts;
		GetReceivedResultCounts()[Page].MaxErrorBreak	=MaxErrorBreak	;
		GetReceivedResultCounts()[Page].TimeOutBreak	=TimeOutBreak	;
		CurrentResultForCalc->SetResultReceivedFlag(Page ,resultCounts,TimeOutBreak,MaxErrorBreak);
		GetLayersBase()->ShadowSetResultReceivedFlag(Page);
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		//IntClass *s=PageList.GetItem(Page);
		//if(s!=NULL){
		//	int	page=s->GetValue();
			int	page=Page;
			GetReceivedResultCounts()[page].Result=resultCounts;
			GetReceivedResultCounts()[page].MaxErrorBreak	=MaxErrorBreak	;
			GetReceivedResultCounts()[page].TimeOutBreak	=TimeOutBreak	;
			//LogicDLLBase->ResultData.SetResultReceivedFlag(page ,resultCounts,TimeOutBreak,MaxErrorBreak);
			CurrentResultForCalc->SetResultReceivedFlag(page ,resultCounts,TimeOutBreak,MaxErrorBreak);
			GetLayersBase()->ShadowSetResultReceivedFlag(Page);
		//}
	}
	else{
		GetReceivedResultCounts()[Page].Result=resultCounts;
		GetReceivedResultCounts()[Page].MaxErrorBreak	=MaxErrorBreak	;
		GetReceivedResultCounts()[Page].TimeOutBreak	=TimeOutBreak	;
		//LogicDLLBase->ResultData.SetResultReceivedFlag(Page ,resultCounts,TimeOutBreak,MaxErrorBreak);
		CurrentResultForCalc->SetResultReceivedFlag(Page ,resultCounts,TimeOutBreak,MaxErrorBreak);
		GetLayersBase()->ShadowSetResultReceivedFlag(Page);
	}
}
void	DataInExecuter::CopyResultCountFrom(DataInExecuter &src)
{
	for(int page=0;page<GetPageNumb();page++){
		GetReceivedResultCounts()[page].Result			= src.GetReceivedResultCounts()[page].Result;
		GetReceivedResultCounts()[page].MaxErrorBreak	= src.GetReceivedResultCounts()[page].MaxErrorBreak;
		GetReceivedResultCounts()[page].TimeOutBreak	= src.GetReceivedResultCounts()[page].TimeOutBreak;
	}
}
bool	DataInExecuter::IsAllFinishedResultReceiving(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if(GetReceivedResultCounts()[page].Result==-1){
			return false;
		}
	}

	return true;
}
bool	DataInExecuter::IsStrategicFinishedResultReceiving(void)
{
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			if(GetReceivedResultCounts()[page].Result==-1){
				return false;
			}
		}
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			if(GetReceivedResultCounts()[page].Result==-1){
				return false;
			}
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			if(GetReceivedResultCounts()[page].Result==-1){
				return false;
			}
		}
	}

	return true;
}
int32	DataInExecuter::GetCountOfFinishedResultReceiving(void)
{
	int32	Count=0;
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		for(int page=0;page<GetPageNumb();page++){
			if(GetReceivedResultCounts()[page].Result!=-1){
				Count++;
			}
		}
	}
	else if(GetParamGlobal()->BufferedProcessing==false){
		IntList	PageList;
		GetParamGlobal()->GetStrategyPage (GetLayersBase()->GetCurrentStrategicNumberForCalc()
											,PageList);
		for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
			int	page=s->GetValue();
			if(GetReceivedResultCounts()[page].Result!=-1){
				Count++;
			}
		}
	}
	else{
		for(int page=0;page<GetPageNumb();page++){
			if(GetReceivedResultCounts()[page].Result!=-1){
				Count++;
			}
		}
	}

	return Count;
}

bool	DataInExecuter::IsStrategicFinishedResultReceiving(int strategicNumber)
{
	IntList	PageList;
	GetParamGlobal()->GetStrategyPage (strategicNumber
										,PageList);
	for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
		int	page=s->GetValue();
		if(GetReceivedResultCounts()[page].Result==-1){
			return false;
		}
	}
	return true;
}


bool	DataInExecuter::IsResultOK(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if((GetReceivedResultCounts()[page].Result>0) || (GetReceivedResultCounts()[page].MaxErrorBreak==true) || (GetReceivedResultCounts()[page].TimeOutBreak==true)){
			return false;
		}
	}
	if(Result==_Result_TimeOut || Result==_Result_MaxNG || Result==_Result_NG){
		return false;
	}
	return true;
}
bool	DataInExecuter::IsResultTimeOut(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if(GetReceivedResultCounts()[page].TimeOutBreak==true){
			return true;
		}
	}
	if(Result==_Result_TimeOut){
		return true;
	}
	return false;
}
bool	DataInExecuter::IsResultMaxError(void)
{
	for(int page=0;page<GetPageNumb();page++){
		if(GetReceivedResultCounts()[page].MaxErrorBreak==true){
			return true;
		}
	}
	if(Result==_Result_MaxNG){
		return false;
	}
	return false;
}

QString	DataInExecuter::GetExecutingStateString(void)
{
	switch(State){
		case _None						:
			return /**/"_None";
		case NowExecuteInitialAfterEdit	:
			return /**/"NowExecuteInitialAfterEdit";
		case NowExecuteStartByScanOnly	:
			return /**/"NowExecuteStartByScanOnly";
		case NowExecuteStartByInspection:
			return /**/"NowExecuteStartByInspection";
		case NowExecuteCaptured		:
			return /**/"NowExecuteCaptured";
		case NowExecutePreAlignment		:
			return /**/"NowExecutePreAlignment";
		case NowExecuteAlignment		:
			return /**/"NowExecuteAlignment";
		case NowExecutePreProcessing	:
			return /**/"NowExecutePreProcessing";
		case NowExecuteProcessing		:
			return /**/"NowExecuteProcessing";
		case NowExecuteProcessingRevived:
			return /**/"NowExecuteProcessingRevived";
		case NowExecutePostProcessing	:
			return /**/"NowExecutePostProcessing";
		case NowExecutePreScanning		:
			return /**/"NowExecutePreScanning";
		case NowExecuteScanning			:
			return /**/"NowExecuteScanning";
		case NowExecutePostScanning		:
			return /**/"NowExecutePostScanning";

//		case FinExecuteInitialAfterEdit	:
//			return /**/"FinExecuteInitialAfterEdit";
//		case FinExecuteStartByScanOnly	:
//			return /**/"FinExecuteStartByScanOnly";
//		case FinExecuteStartByInspection:
//			return /**/"FinExecuteStartByInspection";
//		case FinExecuteCaptured		:
//			return /**/"FinExecuteCaptured";
//		case FinExecutePreAlignment		:
//			return /**/"FinExecutePreAlignment";
//		case FinExecuteAlignment		:
//			return /**/"FinExecuteAlignment";
//		case FinExecutePreProcessing	:
//			return /**/"FinExecutePreProcessing";
//		case FinExecuteProcessing		:
//			return /**/"FinExecuteProcessing";
//		case FinExecuteProcessingRevived:
//			return /**/"FinExecuteProcessingRevived";
//		case FinExecutePostProcessing	:
//			return /**/"FinExecutePostProcessing";
//		case FinExecutePreScanning		:
//			return /**/"FinExecutePreScanning";
//		case FinExecuteScanning			:
//			return /**/"FinExecuteScanning";
//		case FinExecutePostScanning		:
//			return /**/"FinExecutePostScanning";
	}
	return /**/"";
}
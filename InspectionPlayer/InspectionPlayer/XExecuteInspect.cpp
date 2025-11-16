/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XExecuteInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <cmath>
#include "XDateTime.h"
#include <QThread>
//#include "XCameraInterfaceDLL.h"
#include "XCameraClass.h"
#include "XExecuteInspect.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include <stdio.h>
#include "XParamGlobal.h"
#include "XSequenceLocal.h"
#include "XFileRegistry.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XCriticalFunc.h"
#include "XResultDLLManager.h"
//#include "XFilterManager.h"
#include "XIntClass.h"
#include "XForWindows.h"
#include "XLogOut.h"
#include "swap.h"
#include <omp.h>

const	int		MAXBUFFERCOUNTS=10000;
const	int		ExeSleepTimeMilisec=2;

ExecuteInspect	*ExecuteInspect::StaticInstance=NULL;
void	KickAutoStart(LayersBase *base);


ExecuteInspect::ExecuteInspect(QObject *parent ,EntryPointBase *_EntryPoint ,SeqControlParam *_SeqParam) 
: ExecuteInspectBase(parent,_EntryPoint,_SeqParam) ,GoSlotAutomodeStart(false)
{
	Cam						=NULL;

	SeqParam				=_SeqParam;
	AllocatedCamNumb		=0;
	StaticInstance			=this;
	StackedCountInAutoMode	=0;
	ResultInspectionToAccessInSlotAutomodeStart	=NULL;
	StatusCameraHalt		=false;

	PacketReplied			=new CmdInspectionReplied(_EntryPoint->GetLayersBase(),/**/"ANY",/**/"ANY");
	CapturedReplied			=new CmdCapturedOnly	(_EntryPoint->GetLayersBase(),/**/"ANY",/**/"ANY");
	CaptureBeginsReplied	=new CmdCaptureBegins	(_EntryPoint->GetLayersBase(),/**/"ANY",/**/"ANY");
	CmdCheckReplied			=new CmdCheckReply		(_EntryPoint->GetLayersBase(),/**/"ANY",/**/"ANY");

	GUIExecuteCmdStartInspectPoint	=NULL;
	GUIExecuteCmdReplyInspectPoint	=NULL;
	GUIExecuteCmdCancelCapturePoint	=NULL;
	AllocatedPage		=0;
	TriggeredCapture	=false;
	setPriority(QThread::HighestPriority);
}

ExecuteInspect::~ExecuteInspect(void)
{
	Release();
}

bool	ExecuteInspect::InitialCamera(int32 &ErrorCode)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]==NULL){
				CameraErrorCode=Error_CameraDLL;
				return(false);
			}
			if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
				CameraErrorCode=ErrorCode;
				return(false);
			}
			int	LanguageCode=GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
			Cam[i]->SetLanguageCode(LanguageCode);
			CameraErrorCode=ErrorCode;
		}
	}
	return(true);
}
bool	ExecuteInspect::ChangeCameraInfo(CameraReqInfoAnyData *anydata)
{
	if(IsLocalCamera()==true){
		int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
		ChangingCameraInfo.lock();
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->ChangeInfo(GetParamGlobal()->GetDotPerLineInCamera(i) 
								 ,GetParamGlobal()->GetMaxLinesInCamera(i)
								 , LayerNumb,GetPageNumb()
								 ,anydata)==false){
				ChangingCameraInfo.unlock();
				return(false);
			}
		}
		ChangingCameraInfo.unlock();
	}
	return true;
}

bool	ExecuteInspect::CheckCameraDLL(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->CheckCameraDLL()==false){
				return false;
			}
		}
	}
	return true;
}

QString	ExecuteInspect::MakeCamDefaultName(void)
{
	QString	Str1=GetLayersBase()->GetUserPath()+QDir::separator()+GetParamGlobal()->CameraSetting_FileName;
	QFileInfo	Info(Str1);
	if(Info.isRelative()==true){
		Info.makeAbsolute();
	}
	QString	ComputerName;
	while(::MtGetComputerName(ComputerName)==false){
		GSleep(100);
	}
	QString	FName=Info.path()+GetSeparator()+Info.completeBaseName()
				+ QString("_")+ComputerName
				+ QString(".")+Info.suffix();
	return FName;
}

bool	ExecuteInspect::LoadDefault(void)
{
	QString	Str1=MakeCamDefaultName();
	QFile	file1(Str1);
	if(file1.open(QIODevice::ReadOnly)==true){
		if(Load(&file1)==true){
			ChangeCameraInfo();
			return true;
		}
	}
	QString	Str2=GetLayersBase()->GetUserPath()+QDir::separator()+GetParamGlobal()->CameraSetting_FileName;
	QFile	file2(Str2);
	if(file2.open(QIODevice::ReadOnly)==true){
		if(Load(&file2)==true){
			ChangeCameraInfo();
			return true;
		}
	}
	return false;
}

bool	ExecuteInspect::Load(QIODevice *file)
{
	for(int i=0;i<GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID) && i<AllocatedCamNumb;i++){
		int32	Len;
		if(::Load(file,Len)==false){
			return false;
		}
		QByteArray	AR;
		if(::Load(file,AR)==false){
			return false;
		}
		QBuffer	TmpBuff(&AR);
		TmpBuff.open(QIODevice::ReadOnly);
		if(Cam[i]->Load(TmpBuff)==false){
			return false;
		}
	}
	return true;
}
bool	ExecuteInspect::LoadDefaultOldVer(void)
{
	QString	Str=GetLayersBase()->GetUserPath()+QDir::separator()+GetParamGlobal()->CameraSetting_FileName;
	QFile	file(Str);
	if(file.open(QIODevice::ReadOnly)==true){
		for(int i=0;i<GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID) && i<AllocatedCamNumb;i++){
			if(Cam[i]->Load(file)==false){
				return(false);
			}
		}
		return(true);
	}
	return(false);
}
bool	ExecuteInspect::SaveDefault(void)
{
	QString	Str=MakeCamDefaultName();
	QFile	file(Str);
	if(file.open(QIODevice::WriteOnly)==true){
		if(Save(&file)==false)
			return false;
		return true;
	}
	return false;
}

bool	ExecuteInspect::Save(QIODevice *file)
{
	for(int i=0;i<AllocatedCamNumb;i++){
		QBuffer	TmpBuff;
		TmpBuff.open(QIODevice::WriteOnly);
		if(Cam[i]->Save(TmpBuff)==false){
			return false;
		}
		int32	Len=TmpBuff.size();
		if(::Save(file,Len)==false){
			return false;
		}
		QByteArray	AR=TmpBuff.buffer();
		if(::Save(file,AR)==false){
			return false;
		}
	}
	return true;
}

void	ExecuteInspect::Initial(void)
{
	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
	Cam=new CameraClass*[AllocatedCamNumb];
	for(int i=0;i<AllocatedCamNumb;i++){
		Cam[i]=new CameraClass(i,GetLayersBase());
	}
	bool ret;
	ret=(connect(this,SIGNAL(SignalFinishCalc(ResultInspection *,int,int))				,this,SLOT(FinishCalcFunc(ResultInspection *,int,int)) ,Qt::QueuedConnection)	)?true:false;
	ret=(connect(this,SIGNAL(SignalFinishCaptureOnly(ResultInspection *,int ,int,int))	,this,SLOT(FinishCaptureOnlyFunc(ResultInspection *,int,int,int)),Qt::QueuedConnection))?true:false;
	ret=(connect(this,SIGNAL(SignalAutomodeStart())	,this,SLOT(SlotAutomodeStart())	,Qt::QueuedConnection))?true:false;
	ret=(connect(this,SIGNAL(SignalCaptureHalt())	,this,SLOT(SlotCaptureHalt())	,Qt::QueuedConnection))?true:false;
	ret=(connect(this,SIGNAL(SignalCaptured(int))	,this,SLOT(SlotCaptured(int))	,Qt::QueuedConnection))?true:false;
	ret=(connect(this,SIGNAL(SignalCaptureStart())	,this,SLOT(SlotCaptureStart())	,Qt::QueuedConnection))?true:false;
	ret=(connect(this,SIGNAL(SignalCheckCycle(int))	,this,SLOT(SlotCheckCycle(int))	,Qt::QueuedConnection))?true:false;

	if(GUIExecuteCmdStartInspectPoint==NULL){
		AllocatedPage	=GetPageNumb();
		GUIExecuteCmdStartInspectPoint	=new GUIExecuteCmdStartInspect*[AllocatedPage];
		GUIExecuteCmdReplyInspectPoint	=new GUIExecuteCmdReplyInspect*[AllocatedPage];
		GUIExecuteCmdCancelCapturePoint	=new GUIExecuteCmdCancelCapture*[AllocatedPage];
		for(int page=0;page<AllocatedPage;page++){
			GUIExecuteCmdStartInspectPoint[page]	=new GUIExecuteCmdStartInspect(GetLayersBase(),/**/"ANY",/**/"ANY");
			GUIExecuteCmdReplyInspectPoint[page]	=new GUIExecuteCmdReplyInspect(GetLayersBase(),/**/"ANY",/**/"ANY");
			GUIExecuteCmdCancelCapturePoint[page]	=new GUIExecuteCmdCancelCapture(GetLayersBase(),/**/"ANY",/**/"ANY");
		}
	}
}

IntList	DbgFinList;
IntList	DbgStrFinList;

void	ExecuteInspect::FinishCalcFunc(ResultInspection *Res,int localPage,int CurrentStrategic)
{
	if((GetParamGlobal()->DebugLevel & 0x04)!=0){
		DbgFinList.Add(localPage);
		DbgStrFinList.Add(CurrentStrategic);
	}

	//if(GetEntryPoint()->IsMasterPC()==false){
	if(IsLocalCamera()==true){
		if(GetParamGlobal()->BufferedProcessing==true && GetParamGlobal()->GetMaxScanStrategy()>1)
			PacketReplied->CountUpID=false;

		if(GetParamGlobal()->GetMaxScanStrategy()<=(CurrentStrategic+1)
		|| GetParamGlobal()->BufferedProcessing==false){
			PacketReplied->Result	=CmdInspectionRepliedBase::_OK;
			PacketReplied->NGCounts		=Res->GetNGCount();
			PacketReplied->NGImageCount	=Res->GetNGImageCount();
			PacketReplied->TimeOutBreak	=Res->GetTimeOutBreak();
			PacketReplied->MaxErrorBreak=Res->GetMaxErrorBreak();
			DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
			PacketReplied->ExecuterID	=Re->GetID();
			PacketReplied->StrategicNumber	=CurrentStrategic;
			
			Re->SetResultReceivedFlag(localPage,PacketReplied->NGCounts,PacketReplied->TimeOutBreak,PacketReplied->MaxErrorBreak);
			PacketReplied->SendFromSlaveToMaster(
							GetLayersBase()->GetGlobalPageFromLocal(localPage)
							,(int32)_CaptureInspect);
			if(GetParamComm()->Mastered==false)
				GetLayersBase()->GetResultHistryData()->AddHistry((PacketReplied->NGCounts==0)?1:2
											,Res->GetStartTimeForInspection()
											,Res->GetInspectionID()
											,Res->GetIDStr()
											,Res->IsResultTimeOut()
											,Res->IsResultMaxError()
											,Res->ExecTime.TM_TotalProcessMilisec);
			if(GetParamGlobal()->ReDrawByInspection==true){
				if(GetParamComm()->Mastered==false){
					GetLayersBase()->GetGuiInitializer()->RefreshByEveryInspection	(Res->GetInspectionID());
					GetLayersBase()->GetGuiInitializer()->ViewRefreshInPlayer		(Res->GetInspectionID());
				}
			}
		}
		else{
			PacketReplied->Result	=CmdInspectionRepliedBase::_OK;
			PacketReplied->NGCounts		=0;
			PacketReplied->NGImageCount	=0;
			PacketReplied->TimeOutBreak	=false;
			PacketReplied->MaxErrorBreak=false;
			DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
			PacketReplied->ExecuterID	=Re->GetID();
			PacketReplied->StrategicNumber	=CurrentStrategic;
			Re->SetResultReceivedFlag(localPage,PacketReplied->NGCounts,PacketReplied->TimeOutBreak,PacketReplied->MaxErrorBreak);
			PacketReplied->SendFromSlaveToMaster(
						GetLayersBase()->GetGlobalPageFromLocal(localPage)
						,(int32)_CaptureInspect);

			if(GetParamComm()->Mastered==false)
				GetLayersBase()->GetResultHistryData()->AddHistry((PacketReplied->NGCounts==0)?1:2
											,Res->GetStartTimeForInspection()
											,Res->GetInspectionID()
											,Res->GetIDStr()
											,false
											,false
											,Res->ExecTime.TM_TotalProcessMilisec);
		}
	}
}
int		ExecuteInspect::GetAllocatedCameraCount(void)
{
	return min(GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID),AllocatedCamNumb);
}
CameraClass		*ExecuteInspect::GetCamera(int n)
{	
	if(0<=n && n<GetParamGlobal()->TotalCameraNumb){
		return Cam[n];
	}
	return NULL;
}

int		ExecuteInspect::GetCameraDim(CameraClass *CamDim[])
{
	int	n=0;
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb;i++){
		CamDim[i]=Cam[i];
		n++;
	}
	return n;
}

void	ExecuteInspect::SetCameraDim(CameraClass *CamDim[])
{
	GetLayersBase()->LockWChangingDataStructure();
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb;i++){
		Cam[i]=CamDim[i];
	}
	GetLayersBase()->UnlockChangingDataStructure();
}

void	ExecuteInspect::FinishCaptureOnlyFunc(ResultInspection *Res,int localPage,int CurrentStrategic,int motionMode)
{
	if((GetParamGlobal()->DebugLevel & 0x04)!=0){
		DbgFinList.Add(localPage);
		DbgStrFinList.Add(CurrentStrategic);
	}

	MotionMode mode=(MotionMode)motionMode;
	if(IsLocalCamera()==true){
	//if(GetEntryPoint()->IsMasterPC()==false){
		PacketReplied->Result=CmdInspectionRepliedBase::_OK;
		PacketReplied->NGCounts	=0;
		PacketReplied->NGImageCount	=0;
		PacketReplied->TimeOutBreak	=false;
		PacketReplied->MaxErrorBreak=false;
		DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
		PacketReplied->ExecuterID	=Re->GetID();
		PacketReplied->StrategicNumber	=CurrentStrategic;
		PacketReplied->SendFromSlaveToMaster(
					GetLayersBase()->GetGlobalPageFromLocal(localPage)
					,(int32)mode);

		if(GetParamGlobal()->GetMaxScanStrategy()<=(CurrentStrategic+1)){
			GetLayersBase()->ClearCurrentStrategicNumberForCalc();
		}
		if(GetParamComm()->Mastered==false){
			GetLayersBase()->GetGuiInitializer()->RefreshByEveryInspection	(GetLayersBase()->GetCurrentInspectIDForDisplay());
			GetLayersBase()->GetGuiInitializer()->ViewRefreshInPlayer		(GetLayersBase()->GetCurrentInspectIDForDisplay());
		}
	}
}

void	ExecuteInspect::SlotCaptured(int CStrategic)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				CapturedReplied->SendFromSlaveToMaster( GetLayersBase()->GetGlobalPageFromLocal(page) ,0);
			}
		}
	}
	else{
		if(IsLocalCamera()==true){
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(CStrategic,SList);
			int	N=0;
			int	PageType[100];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}
			for(int i=0;i<PageTypeNumb;i++){
				CapturedReplied->SendFromSlaveToMaster( GetLayersBase()->GetGlobalPageFromLocal(PageType[i]) ,0);
			}
		}
	}
}

void	ExecuteInspect::SetCaptured(int CStrategic)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	SeqParam->DoneCapture=true;

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				SeqParam->Captured(GetLayersBase()->GetGlobalPageFromLocal(page));
			}
		}
	}
	else{
		if(IsLocalCamera()==true){
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(CStrategic,SList);
			int	N=0;
			int	PageType[100];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}
			for(int i=0;i<PageTypeNumb;i++){
				SeqParam->Captured(GetLayersBase()->GetGlobalPageFromLocal(PageType[i]));
			}
		}
	}
	SeqParam->NowProcessing	=true;
}

void	KickAutoStart(LayersBase *base)
{
	ExecuteInspect	*E=(ExecuteInspect *)base->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL && E->GoSlotAutomodeStart==true){
		E->SlotAutomodeStart();
		E->StackedCountInAutoMode++;
		E->GoSlotAutomodeStart=false;
	}
}

void	ExecuteInspect::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SpecifiedDirectly(v);
			}
		}
	}
}

void	ExecuteInspect::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SetScanInfo(ScanNumber ,ScanMastered);
			}
		}
	}
}


void	ExecuteInspect::SlotAutomodeStart()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;

	static	char	buff[50];
	ReEntrant=true;
	if(GetParamComm()->Mastered==true){

		GetLayersBase()->GetLogCreater()->PutLog(__LINE__	,"ExecuteInspect::SlotAutomodeStart-1");
			
		QString	LStr=GetLayersBase()->GetStartInspectTime().toString("hhmmss");
		QString2Char(LStr,buff ,sizeof(buff));

		for(int page=0;page<GetPageNumb();page++){
			GUIExecuteCmdStartInspectPoint[page]->StartInspectionTime	=GetLayersBase()->GetStartInspectTime();
			GUIExecuteCmdStartInspectPoint[page]->CurrentInspectID		=GetLayersBase()->GetCurrentInspectIDForExecute();
			GUIExecuteCmdStartInspectPoint[page]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumber();
		}

		for(int page=0;page<GetPageNumb();page++){
			GUIExecuteCmdStartInspectPoint[page]->Send(page ,0,*GUIExecuteCmdReplyInspectPoint[page]);
		}

		if(GetParamGlobal()->ViewProcessingWindow==true){
			GetLayersBase()->ShowProcessingForm ("Waiting image in AutoMode");
		}
		GetLayersBase()->SetMaxProcessing(0);
		CapturePrepare();

		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int page=0;page<GetPageNumb();page++){
				if(GUIExecuteCmdReplyInspectPoint[page]->IsReceived()==false){
					ReadyAll=false;
				}
			}

			if(GetLayersBase()->GetOnTerminating()==true){
				SetMode(_CaptureNone);
				ReEntrant=false;
				return;
			}
			QCoreApplication::processEvents();
			if(GetLayersBase()->GetOnTerminating()==true){
				ReEntrant=false;
				return;
			}
		}while(ReadyAll==false);

		GetLayersBase()->GetLogCreater()->PutLog(__LINE__	,"ExecuteInspect::SlotAutomodeStart-2");

		SeqParam->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		SeqParam->ReadyForScan=true;
//		GetLayersBase()->ExecuteStartByInspection();

		SetMode(_CaptureInspect);
	}
	ReEntrant=false;
}

void	ExecuteInspect::Release(void)
{
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
	//CamRelease();
}

void	ExecuteInspect::CamRelease(void)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			delete	Cam[i];
		}
		delete	[]Cam;
	}
	Cam=NULL;
}

bool	ExecuteInspect::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}

int		ExecuteInspect::GetCameraCount(void)
{
	int	n=0;
	for(int i=0;i<AllocatedCamNumb;i++){
		switch(i){
		case 0:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter);
			if(n>0){
				return n;
			}
			break;
		case 1:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter2);
			if(n>0){
				return n;
			}
			break;
		case 2:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter3);
			if(n>0){
				return n;
			}
			break;
		case 3:
			n=Cam[i]->GetCameraCount(GetParamGlobal()->CameraDLL_FileName,GetParamGlobal()->CameraParameter4);
			if(n>0){
				return n;
			}
			break;
		default:
			return -1;
		}
	}
	return -1;
}

bool	ExecuteInspect::CheckCamera(int32 &ErrorCode)
{
	if(IsLocalCamera()==true){
		bool	Reallocation=false;
		ChangingCameraInfo.lock();
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->ShouldRealloc(GetParamGlobal())==true){
				delete	Cam[i];
				Cam[i]=NULL;
				Reallocation=true;
			}
		}
		if(Reallocation==true){
			LoopToWait:;
			GSleep(2000);
			PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(0);
			if(Ph==NULL)
				goto	LoopToWait;
			for(int page=0;page<GetPageNumb();page++){
				DataInPage *Pg=Ph->GetPageData(page);
				if(Pg==NULL)
					goto	LoopToWait;
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					DataInLayer	*Ly=Pg->GetLayerData(Layer);
					if(Ly==NULL)
						goto	LoopToWait;
					if(GetParamGlobal()->AllocateMasterBuff==true && Ly->IsMasterBuffEnabled()==false)
						goto	LoopToWait;
					if(GetParamGlobal()->AllocateTargetBuff==true && Ly->IsTargetBuffEnabled()==false)
						goto	LoopToWait;
				}
			}
			for(int i=0;i<AllocatedCamNumb;i++){
				Cam[i]=new CameraClass(i,GetLayersBase());
				if(Cam[i]->Initial(GetParamGlobal(),ErrorCode)==false){
					return false;
				}
			}
		}
		ChangingCameraInfo.unlock();
		return true;
	}
	return false;
}

bool	ExecuteInspect::CapturePrepare(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->PrepareCapture();
		}
		return(true);
	}
	return(false);
}
bool	ExecuteInspect::CaptureStart(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->StartCapture();
		}
		//qWarning(/**/"CaptureStart\n");

		StatusCameraHalt=false;
		SeqParam->CaptureStartCounter++;
		if(SeqParam->CaptureStartCounter>GetParamGlobal()->GetMaxScanStrategy()){
			SeqParam->CaptureStartCounter=1;
		}
		emit	SignalCaptureStart();

		TriggeredCapture=true;
		return(true);
	}
	return(false);
}

void	ExecuteInspect::SlotCaptureStart()
{
	for(int i=0;i<AllocatedCamNumb;i++){
		CaptureBeginsReplied->SendFromSlaveToMaster(
						GetLayersBase()->GetGlobalPageFromLocal(i)
						,SeqParam->CaptureStartCounter);
	}
}

bool	ExecuteInspect::CaptureHalt(void)
{
	if(IsLocalCamera()==true){
		StatusCameraHalt=true;
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->HaltCapture();
		}
		TriggeredCapture=false;
		return(true);
	}
	GetLayersBase()->CloseProcessingForm();
	return(false);
}
void	ExecuteInspect::SlotCaptureHalt()
{
	if(GetEntryPoint()->IsMasterPC()==true){
		for(int page=0;page<GetPageNumb();page++){
			GUIExecuteCmdCancelCapturePoint[page]->Send(NULL,page ,0);
		}

		int	LPage=-1;
		do{
			LPage=GetLayersBase()->GetTopPageInCapturedPageLayer(true);
			if(LPage>=0){
				GetLayersBase()->PopCurrentStrategicNumberForCalc();
			}
		}while(LPage>=0);
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
		SeqParam->CaptureStartCounter=0;
	}
	//if(IsLocalCamera()==false){
	//	GoHalt();
	//}
}

int		ExecuteInspect::CaptureGetState(void)
{
	if(IsLocalCamera()==true){
		if(StatusCameraHalt==true){
			GoHalt();
		}
		int	ret=0;
		for(int i=0;i<AllocatedCamNumb;i++){
			ret|=Cam[i]->GetStatus();
		}
		return(ret);
	}
	return(0);
}

IntList	PDbgSlotList;

bool	ExecuteInspect::CaptureGetMasterImage(int CStrategic,ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
				ImageBuffer	**Buff = (ImageBuffer **)alloca(P->GetLayerNumb() * sizeof(ImageBuffer**));;
				int			BuffNumb=0;
				for(int layer=0;layer<P->GetLayerNumb();layer++){
					DataInLayer	*L=P->GetLayerData(layer);
					if(SeqParam->InspectionStrategy==GetParamGlobal()->GetStrategyCode(page ,layer)){
						Buff[BuffNumb]=L->GetMasterBuffPointer();
						CapturedList.Merge(CPhase,page,layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
				}
				if(page<AllocatedCamNumb){
					bool XDirReverse ,YDirReverse;
					GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
					bool tXDirReverse	=XDirReverse;
					bool tYDirReverse	=YDirReverse;
					Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
					if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
						ImageReverse(page,Buff ,BuffNumb);
					}
					ImageYDelay(page,Buff ,BuffNumb);
				}
			}
			if(PhaseCodes.GetCount()>1){
				for(int i=1;i<PhaseCodes.GetCount();i++){
					int	phase=PhaseCodes[i];
					for(int page=0;page<GetPageNumb();page++){
						DataInPage	*Ps=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
						DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
						for(int layer=0;layer<Ps->GetLayerNumb();layer++){
							DataInLayer	*Ls=Ps->GetLayerData(layer);
							DataInLayer	*Ld=Pd->GetLayerData(layer);
							if(SeqParam->InspectionStrategy==GetParamGlobal()->GetStrategyCode(page ,layer)){
								Ld->GetMasterBuff()=Ls->GetMasterBuff();
								CapturedList.Merge(phase,page,layer);
							}
						}
					}
				}
			}
		}
	}
	else{
		if(IsLocalCamera()==true){
			if((GetParamGlobal()->DebugLevel & 0x04)!=0){
				PDbgSlotList.Add(CStrategic);
			}
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(CStrategic,SList);
			int	N=0;
			int	PageType[10];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}

			//Žæ‚èž‚Ý‚ð‘‚­‚·‚é‚½‚ß‚Éæ‚ÉGetImage‚¾‚¯‚ðs‚¤
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
			bool XDirReverse ,YDirReverse;
			GetLayersBase()->GetParamGlobal()->GetPageDir(GetLayersBase()->GetCurrentStrategicNumber() ,XDirReverse ,YDirReverse);
			bool tXDirReverse	=XDirReverse;
			bool tYDirReverse	=YDirReverse;
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					int	BuffNumb=0;
					ImageBuffer	**Buff	=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
					int	CamNo=GetParamGlobal()->GetCameraNo(PageType[camcode]);
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetMasterBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					if(CamNo<AllocatedCamNumb){
						tXDirReverse	=XDirReverse;
						tYDirReverse	=YDirReverse;
						Cam[CamNo]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
					}
				}
			//}
			if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					int	BuffNumb=0;
					ImageBuffer	**Buff	=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetMasterBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					ImageReverse(GetLayersBase()->GetCurrentStrategicNumber(),Buff ,BuffNumb);
				}
			}
				
			for(int camcode=0;camcode<PageTypeNumb;camcode++){
				int	BuffNumb=0;
				ImageBuffer	**Buff	=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
				for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
					if(PageType[camcode]!=s->Page)
						continue;
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
					DataInLayer	*L=P->GetLayerData(s->Layer);
					Buff[BuffNumb]=L->GetMasterBuffPointer();
					CapturedList.Merge(CPhase,s->Page,s->Layer);
					BuffNumb++;
					//if(BuffNumb>=MAXBUFFERCOUNTS)
					//	break;
				}
				ImageYDelay(PageType[camcode],Buff ,BuffNumb);
			}
		}
	}
	GetLayersBase()->ExecuteFilteringMaster();
	GetLayersBase()->SetEdited(true);
	if(IsLocalCamera()==true){
		SeqParam->DoneCapture=true;
	}
	return(true);
}
static	int	CaptureGetTargetImageCounter=0;
static	int	CaptureGetTargetImageDbg=0;
static	IntList	CaptureGetTargetImageList;
DWORD	FilteringMilisec;

bool	ExecuteInspect::CaptureGetTargetImage(ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];

	CurrentCapturedPageLayer.RemoveAll();
	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			int	N=GetPageNumb();
			if(N==1){
				for(int page=0;page<N;page++){
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
					ImageBuffer	**Buff=(ImageBuffer **)alloca(P->GetLayerNumb()*sizeof(ImageBuffer**));//MAXBUFFERCOUNTS];
					ImageBuffer	**TRBuff=(ImageBuffer **)alloca(P->GetLayerNumb()*sizeof(ImageBuffer**));//MAXBUFFERCOUNTS];
					int			BuffNumb=0;
					for(int layer=0;layer<P->GetLayerNumb();layer++){
						DataInLayer	*L=P->GetLayerData(layer);
						if(SeqParam->InspectionStrategy==GetParamGlobal()->GetStrategyCode(page ,layer)){
							Buff  [BuffNumb]=L->GetTargetBuffPointer();
							TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
							CapturedList.Merge(CPhase,page,layer);
							BuffNumb++;
							//if(BuffNumb>=MAXBUFFERCOUNTS)
							//	break;
						}
					}
					if(page<AllocatedCamNumb){
						bool XDirReverse ,YDirReverse;
						GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
						bool tXDirReverse	=XDirReverse;
						bool tYDirReverse	=YDirReverse;
						if(Cam[page]->IsTREffective()==true){
							Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
						}
						else{
							Cam[page]->GetImage(Buff ,TRBuff ,BuffNumb,tXDirReverse ,tYDirReverse);
						}
						if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
							ImageReverse(page,Buff ,BuffNumb);
						}
						ImageYDelay(page,Buff ,BuffNumb);
					}
					if(GetParamGlobal()->BufferedProcessing==true){
						CurrentCapturedPageLayer.AppendList(new PageAndLayerFlagList(page ,-1));
					}
					if(GetParamGlobal()->AllocCamTargetBuffer==true){
						for(int layer=0;layer<P->GetLayerNumb();layer++){
							DataInLayer	*L=P->GetLayerData(layer);
							L->GetCamTargetBuff()=L->GetTargetBuff();
						}
					}
				}
			}
			else{
				if(GetParamGlobal()->GetMaxScanStrategy()==1 && GetPageNumb()>AllocatedCamNumb){						
					for(int CamNo=0;CamNo<AllocatedCamNumb;CamNo++){
						int			BuffNumb=0;
						ImageBuffer	*Buff[1000];
						ImageBuffer	*TRBuff[1000];
						IntList PageList;
						GetParamGlobal()->GetPageListFromCameraNo(CamNo ,PageList);
						for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
							int	page=p->GetValue();
							DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								Buff  [BuffNumb]=L->GetTargetBuffPointer();
								TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
								CapturedList.Merge(CPhase,page,layer);
								BuffNumb++;
								if(BuffNumb>1000)
									break;
							}
						}
						bool XDirReverse=false ,YDirReverse=false;
						if(Cam[CamNo]->IsTREffective()==false)
							Cam[CamNo]->GetImage(Buff ,BuffNumb,XDirReverse ,YDirReverse);
						else
							Cam[CamNo]->GetImage(Buff ,TRBuff,BuffNumb,XDirReverse ,YDirReverse);
						if(XDirReverse==true || YDirReverse==true){
							for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
								int	page=p->GetValue();
								ImageReverse(page,Buff ,BuffNumb);
							}
						}
						if(GetParamGlobal()->BufferedProcessing==true){
							for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
								int	page=p->GetValue();
								DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
								CurrentCapturedPageLayer.AppendList(new PageAndLayerFlagList(page ,-1));
								if(GetParamGlobal()->AllocCamTargetBuffer==true){
									for(int layer=0;layer<P->GetLayerNumb();layer++){
										DataInLayer	*L=P->GetLayerData(layer);
										L->GetCamTargetBuff()=L->GetTargetBuff();
									}
								}
							}
						}
					}
				}
				else{
					#pragma omp parallel for
					for(int page=0;page<N;page++){
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
						ImageBuffer	**Buff	=(ImageBuffer **)alloca(P->GetLayerNumb()*sizeof(ImageBuffer**));
						ImageBuffer	**TRBuff=(ImageBuffer **)alloca(P->GetLayerNumb()*sizeof(ImageBuffer**));
						int			BuffNumb=0;
						for(int layer=0;layer<P->GetLayerNumb();layer++){
							DataInLayer	*L=P->GetLayerData(layer);
							if(SeqParam->InspectionStrategy==GetParamGlobal()->GetStrategyCode(page ,layer)){
								Buff  [BuffNumb]=L->GetTargetBuffPointer();
								TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
								#pragma omp critical
								{
									CapturedList.Merge(CPhase,page,layer);
								}
								BuffNumb++;
								//if(BuffNumb>=MAXBUFFERCOUNTS)
								//	break;
							}
						}
						if(page<AllocatedCamNumb){
							bool XDirReverse ,YDirReverse;
							GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
							bool tXDirReverse	=XDirReverse;
							bool tYDirReverse	=YDirReverse;
							if(Cam[page]->IsTREffective()==false)
								Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
							else
								Cam[page]->GetImage(Buff ,TRBuff ,BuffNumb,tXDirReverse ,tYDirReverse);
							if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
								ImageReverse(page,Buff ,BuffNumb);
							}
							ImageYDelay(page,Buff ,BuffNumb);
						}
						if(GetParamGlobal()->BufferedProcessing==true)
							CurrentCapturedPageLayer.AppendList(new PageAndLayerFlagList(page ,-1));
						if(GetParamGlobal()->AllocCamTargetBuffer==true){
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								L->GetCamTargetBuff()=L->GetTargetBuff();
							}
						}
					}
				}
			}
			if(PhaseCodes.GetCount()>1){
				for(int i=1;i<PhaseCodes.GetCount();i++){
					int	phase=PhaseCodes[i];
					for(int page=0;page<GetPageNumb();page++){
						DataInPage	*Ps=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
						DataInPage	*Pd=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page);
						for(int layer=0;layer<Ps->GetLayerNumb();layer++){
							DataInLayer	*Ls=Ps->GetLayerData(layer);
							DataInLayer	*Ld=Pd->GetLayerData(layer);
							if(SeqParam->InspectionStrategy==GetParamGlobal()->GetStrategyCode(page ,layer)){
								Ld->GetTargetBuff()		=Ls->GetTargetBuff();
								CapturedList.Merge(phase,page,layer);
								if(GetParamGlobal()->AllocCamTargetBuffer==true){
									Ld->GetCamTargetBuff()	=Ls->GetTargetBuff();
								}
							}
						}
					}
				}
			}
		}
	}	
	else{
		if(CaptureGetTargetImageCounter==2)
			CaptureGetTargetImageDbg++;

		if(IsLocalCamera()==true){
			StrategicListContainer SList;
			GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),SList);
			int	N=0;
			int	PageType[10];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				int	i;
				for(i=0;i<PageTypeNumb;i++){
					if(PageType[i]==s->Page){
						break;
					}
				}
				if(i>=PageTypeNumb){
					PageType[PageTypeNumb]=s->Page;
					PageTypeNumb++;
					if(PageTypeNumb>sizeof(PageType)/sizeof(PageType[0]))
						break;
				}
			}
	
			//Žæ‚èž‚Ý‚ð‘‚­‚·‚é‚½‚ß‚Éæ‚ÉGetImage‚¾‚¯‚ðs‚¤
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
			bool XDirReverse ,YDirReverse;
			GetLayersBase()->GetParamGlobal()->GetPageDir(GetLayersBase()->GetCurrentStrategicNumber() ,XDirReverse ,YDirReverse);
			bool tXDirReverse	=XDirReverse;
			bool tYDirReverse	=YDirReverse;
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					ImageBuffer	**Buff	=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
					ImageBuffer	**TRBuff=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
					int	BuffNumb=0;
					int	CamNo=GetParamGlobal()->GetCameraNo(PageType[camcode]);
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						if(GetParamGlobal()->BufferedProcessing==true)
							CurrentCapturedPageLayer.AppendList(new PageAndLayerFlagList(s->Page ,s->Layer));
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetTargetBuffPointer();
						TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					if(CamNo<AllocatedCamNumb){
						tXDirReverse	=XDirReverse;
						tYDirReverse	=YDirReverse;
						if(Cam[CamNo]->IsTREffective()==false)
							Cam[CamNo]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
						else
							Cam[CamNo]->GetImage(Buff ,TRBuff ,BuffNumb,tXDirReverse ,tYDirReverse);
						CaptureGetTargetImageList.Add(CamNo);
					}
				}
			//}
			if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					ImageBuffer	**Buff=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
					int	BuffNumb=0;
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						if(GetParamGlobal()->BufferedProcessing==true)
							CurrentCapturedPageLayer.AppendList(new PageAndLayerFlagList(s->Page ,s->Layer));
						DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						Buff[BuffNumb]=L->GetTargetBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					ImageReverse(GetLayersBase()->GetCurrentStrategicNumber(),Buff ,BuffNumb);
				}
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					if(GetParamGlobal()->AllocCamTargetBuffer==true){
						for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
							if(PageType[camcode]!=s->Page)
								continue;
							DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
							DataInLayer	*L=P->GetLayerData(s->Layer);
							L->GetCamTargetBuff()=L->GetTargetBuff();
						}
					}
				}
			}
			for(int camcode=0;camcode<PageTypeNumb;camcode++){
				int	BuffNumb=0;
				ImageBuffer	**Buff	=(ImageBuffer **)alloca(SList.GetCount()*sizeof(ImageBuffer**));
				for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
					if(PageType[camcode]!=s->Page)
						continue;
					DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(s->Page);
					DataInLayer	*L=P->GetLayerData(s->Layer);
					Buff[BuffNumb]=L->GetTargetBuffPointer();
					BuffNumb++;
					//if(BuffNumb>=MAXBUFFERCOUNTS)
					//	break;
				}
				ImageYDelay(PageType[camcode],Buff ,BuffNumb);
			}
		}
	}
	FilteringMilisec=GetComputerMiliSec();
	GetLayersBase()->ExecuteFilteringTarget();
	FilteringMilisec=GetComputerMiliSec()-FilteringMilisec;

	if(IsLocalCamera()==true){
		SeqParam->DoneCapture=true;
	}
	CaptureGetTargetImageCounter++;
	return(true);
}


void	ExecuteInspect::GoInspect(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspect);
}
void	ExecuteInspect::GoInspectWithoutCapture(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspectWithoutCapture);
}
void	ExecuteInspect::GoMasterCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyMaster);
}
void	ExecuteInspect::GoTargetCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyTarget);
}
void	ExecuteInspect::GoGray(void)
{
	ClearHaltMode();
	SetMode(_CaptureGray);
}

void	ExecuteInspect::ExecuteHalt(void)
{
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	GetLayersBase()->SetCurrentStrategicNumber(0);
	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);

	GetLayersBase()->ClearTopInCapturedPageLayer();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	GetLayersBase()->PopCurrentStrategicNumberForCalc();
}


void	ExecuteInspect::CamShowSetting(int CamNo)
{
	if(Cam[CamNo]->ShowSetting(GetLayersBase()->GetMainWidget())==true){
		SaveDefault();
	}
}

void	ExecuteInspect::Exit(GUIFormBase *)
{
	if(GetLayersBase()->GetResultDLLBase()!=NULL)
		GetLayersBase()->GetResultDLLBase()->Release();
}

bool	ExecuteInspect::LoadCameraSetting(QIODevice *f)
{
	if(ExecuteInspectBase::LoadCameraSetting(f)==false){
		return false;
	}
	MotionMode	tMode=GetMode();
	if(tMode==_CaptureInspect || tMode==_CaptureInspectWithoutCapture || tMode==_CaptureOnlyMaster || tMode==_CaptureOnlyTarget){
		if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
			TriggeredCapture=true;
			CapturePrepare();
			CaptureStart();
		}
	}
	return(true);
}

void	ExecuteInspect::ClearCameraBuffer(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->ClearBuffer();
		}
	}
}
bool	ExecuteInspect::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	for(int page=0;page<AllocatedPage;page++){
		delete	GUIExecuteCmdStartInspectPoint[page];
		delete	GUIExecuteCmdReplyInspectPoint[page];
		delete	GUIExecuteCmdCancelCapturePoint[page];
	}
	delete	[]GUIExecuteCmdStartInspectPoint;
	delete	[]GUIExecuteCmdReplyInspectPoint;
	delete	[]GUIExecuteCmdCancelCapturePoint;

	AllocatedPage=newPageNumb;
	GUIExecuteCmdStartInspectPoint	=new GUIExecuteCmdStartInspect*[AllocatedPage];
	GUIExecuteCmdReplyInspectPoint	=new GUIExecuteCmdReplyInspect*[AllocatedPage];
	GUIExecuteCmdCancelCapturePoint	=new GUIExecuteCmdCancelCapture*[AllocatedPage];
	for(int page=0;page<AllocatedPage;page++){
		GUIExecuteCmdStartInspectPoint[page]	=new GUIExecuteCmdStartInspect(GetLayersBase(),/**/"ANY",/**/"ANY");
		GUIExecuteCmdReplyInspectPoint[page]	=new GUIExecuteCmdReplyInspect(GetLayersBase(),/**/"ANY",/**/"ANY");
		GUIExecuteCmdCancelCapturePoint[page]	=new GUIExecuteCmdCancelCapture(GetLayersBase(),/**/"ANY",/**/"ANY");
	}

	int	iAllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
	if(AllocatedCamNumb!=iAllocatedCamNumb){
		for(int i=0;i<AllocatedCamNumb;i++){
			delete	Cam[i];
		}
		delete	[]Cam;
		AllocatedCamNumb=iAllocatedCamNumb;
		Cam=new CameraClass*[AllocatedCamNumb];
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]=new CameraClass(i,GetLayersBase());
		}
	}
	return true;
}
//==================================================================

static	int	TrunCaptured=0;
static	int	TrunStarted=0;
static	int	TrunStartStarted1=0;
static	int	TrunStartStarted2=0;
static	int	TrunStartStarted3=0;
IntList	StrategicStartList;

void ExecuteInspect::OccurCamError(int CamStatus)
{
	QString	Msg;
	if((CamStatus & BitCamErrorOverRun)!=0){
		Msg = "OverRun error in Camera";
	}
	else if((CamStatus & BitCamErrorElse)!=0){
		Msg = "Something error in Camera";
	}
	GetLayersBase()->SendErrorToMaster(1 , Msg ,ErrorCodeList::_Critical);
}


static	DWORD		C,Cn;

void ExecuteInspect::run()
{
	GUIInstancePack	*GUI=GetLayersBase()->GetGUIInstancePack();
	if(GUI!=NULL){
		GUI->AppendTimerFunc(KickAutoStart);
	}
	SeqParam->CaptureStartCounter=0;
IdleTurn:;
	for(;;){
		PushOnIdle();
		if(GetPermitToRun()==true){
			C=GetComputerMiliSec();

			SeqParam->InspactionStatus=0;
			if(GetAutoRepeat()==_AutoCaptureOnlyMaster)
				SetMode(_CaptureOnlyMaster);
			else if(GetAutoRepeat()==_AutoCaptureOnlyTarget)
				SetMode(_CaptureOnlyTarget);
			else if(GetAutoRepeat()==_AutoCaptureInspect){
				//GetLayersBase()->ExecuteStartByInspection();
 				GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
				GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

				SeqParam->InspactionStatus=33;
				SeqParam->CaptureMode=3;
				CurrentState=_EI_Prepare;

				//SeqParam->ReadyForScan=true;
				if(GetEntryPoint()->IsMasterPC()==true){

					while(SeqParam->PermitCapture==false){
						msleep(10);
						//QCoreApplication::processEvents();
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							//GSleep(100);
							//QCoreApplication::processEvents();
							//GSleep(100);
							//QCoreApplication::processEvents();
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}

				//SeqParam->CaptureMode=0;
				for(int page=0;page<GetPageNumb();page++){
					GUIExecuteCmdStartInspectPoint[page]->StartInspectionTime	=GetLayersBase()->GetStartInspectTime();
					GUIExecuteCmdStartInspectPoint[page]->CurrentInspectID		=GetLayersBase()->GetCurrentInspectIDForExecute();
					GUIExecuteCmdStartInspectPoint[page]->StrategicNumber		=GetLayersBase()->GetCurrentStrategicNumber();
				}			
				//emit	SignalAutomodeStart();
				//GoSlotAutomodeStart=true;

				if(GetParamComm()->Mastered==true){
					GetLayersBase()->SetCurrentStrategicNumber(GetLayersBase()->GetCurrentStrategicNumberForSeq());
					ResultInspection	*Res=GetLayersBase()->GetNextResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());
						ResultInspectionToAccessInSlotAutomodeStart=Res;
						GoSlotAutomodeStart=true;
					}
				}
				if(GetParamGlobal()->BufferedProcessing==false){
					if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
						GetLayersBase()->ExecuteStartByInspection();
						GetLayersBase()->ExecuteFilterBeforeScan();
					}
				}
			}
			Cn=GetComputerMiliSec();
			DWORD	t=Cn-C;

			if(GetMode()==_CaptureOnlyTarget){
				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(GetLayersBase()->GetCurrentStrategicNumber() ,false);

				SeqParam->InspactionStatus=17;
				SeqParam->CaptureMode=1;
				SeqParam->StartScanOnly=true;
				GetLayersBase()->ExecuteStartByScanOnly();
				if(GetEntryPoint()->IsMasterPC()==true){
					while(SeqParam->PermitCapture==false){
						msleep(10);
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				CurrentState=_EI_Prepare;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CapturePrepare();
					GetLayersBase()->ExecuteFilterBeforeScan();
				}
				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CaptureStart();
				}
				SeqParam->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
				SeqParam->ReadyForScan=true;
				CurrentState=_EI_OnCapturing;
				int	CamStatus;
				while((CamStatus=CaptureGetState())!=0){
					if(GetHaltMode()==true){
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					if((CamStatus & BitCamError)!=0){
						OccurCamError(CamStatus);
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					msleep(ExeSleepTimeMilisec);
					if(GetLayersBase()->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
				}
				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					goto	IdleTurn;
				}				
				if(GetEntryPoint()->IsMasterPC()==true){
					SetCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					EmitSignalCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}

				int	CStrategic=GetLayersBase()->GetCurrentStrategicNumber();
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					CurrentState=_EI_OnTransmit;
					TriggeredCapture=false;
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
						TriggeredCapture=true;
						CapturePrepare();
						CaptureStart();
					}
					SeqParam->InspactionStatus=18;
					ListPhasePageLayerPack CapturedList;
					CaptureGetTargetImage(CapturedList);
					FuncContainerInCaptureOnlyTarget.ExecuteFunc();

					if(GetParamGlobal()->AutoIncrementScanPhaseNumber==true){
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							GetLayersBase()->IncreaseCurrentScanPhaseNumber();
						}
						else{
							if((GetLayersBase()->GetCurrentStrategicNumber()+1)>=GetParamGlobal()->GetMaxScanStrategy()){
								GetLayersBase()->IncreaseCurrentScanPhaseNumber();
							}
						}
					}
					SeqParam->PermitCapture=false;
		
					ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
					if(Res!=NULL){
						GetLayersBase()->ExecuteCaptured		(CapturedList);
						GetLayersBase()->ExecutePreAlignment	();
						GetLayersBase()->ExecuteAlignment		();
						GetLayersBase()->ExecutePreScanning		();
						GetLayersBase()->ExecuteScanning		();
						GetLayersBase()->ExecutePostScanning	();

						SeqParam->InspactionStatus=19;
						while(GetComputerMiliSec()-StartCalcTime<GetParamGlobal()->WaitMilisecAfterScan){
							GSleep(20);
						}
						emit	SignalFinishCaptureOnly(Res,0,CStrategic,(int)_CaptureOnlyTarget);
					}
				}
				else{	//Master‚Ì‚Æ‚«
					//if(CStrategic==0)
					//	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
					if(GetParamGlobal()->GetMaxScanStrategy()<=1){
						ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
						if(Res!=NULL){
							DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);

							while(Re->IsStrategicFinishedResultReceiving()==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
					}
					else{
						ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
						if(Res!=NULL){
							DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
							while(Re->IsStrategicFinishedResultReceiving(CStrategic)==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
					}
				}
				if(GetEntryPoint()->IsMasterPC()==true){
					SeqParam->InspectionResult=1;

					if(GetParamGlobal()->GetMaxScanStrategy()>1){
						if(GetParamGlobal()->GetMaxScanStrategy()>(CStrategic+1)){
							GetLayersBase()->SetCurrentStrategicNumber(CStrategic+1);
						}
						else{
							GetLayersBase()->SetCurrentStrategicNumber(0);
						}
					}
				}
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
			else if(GetMode()==_CaptureOnlyMaster){
				SetCurrentTypeOfCapture(ExecuteInspectBase::_Master);
				SetScanInfo(GetLayersBase()->GetCurrentStrategicNumber() ,true);

				SeqParam->InspactionStatus=1;
				SeqParam->CaptureMode=2;
				SeqParam->StartScanOnly=true;
				GetLayersBase()->ExecuteStartByScanOnly();
				CurrentState=_EI_Prepare;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CapturePrepare();
					GetLayersBase()->ExecuteFilterBeforeScan();
				}
				if(GetEntryPoint()->IsMasterPC()==true){
					while(SeqParam->PermitCapture==false){
						msleep(10);
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				if(GetParamComm()->Mastered==true){
					//GetLayersBase()->SetCurrentStrategicNumber(GetLayersBase()->GetCurrentStrategicNumberForSeq());
				}
				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CaptureStart();
				}
				SeqParam->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
				SeqParam->ReadyForScan=true;
				CurrentState=_EI_OnCapturing;
				int	CamStatus;
				while((CamStatus=CaptureGetState())!=0){
					if(GetHaltMode()==true){
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					if((CamStatus & BitCamError)!=0){
						OccurCamError(CamStatus);
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					msleep(ExeSleepTimeMilisec);
					if(GetLayersBase()->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
				}
				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					goto	IdleTurn;
				}
			
				if(GetEntryPoint()->IsMasterPC()==true){
					SetCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					EmitSignalCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
					int	CStrategic=GetLayersBase()->GetCurrentStrategicNumber();
					Re->ClearReceivedResultCounts();
				
					if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
						DWORD	StartCalcTime=GetComputerMiliSec();
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
						TriggeredCapture=false;
						if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
							TriggeredCapture=true;
							CapturePrepare();
							CaptureStart();
						}
						CurrentState=_EI_OnTransmit;
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
						SeqParam->InspactionStatus=2;
						ListPhasePageLayerPack CapturedList;
						CaptureGetMasterImage(CStrategic,CapturedList);
						FuncContainerInCaptureOnlyMaster.ExecuteFunc();

						SeqParam->PermitCapture=false;
						SeqParam->InspactionStatus=3;
						CurrentState=_EI_IDLE;
						while(GetComputerMiliSec()-StartCalcTime<GetParamGlobal()->WaitMilisecAfterScan){
							GSleep(20);
						}

						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							emit	SignalFinishCaptureOnly(Res,0,CStrategic,(int)_CaptureOnlyMaster);
						}
						else{
							StrategicListContainer SList;
							GetParamGlobal()->GetStrategy(CStrategic,SList);
							//ŒŸ¸Š®—¹Žž

							for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
								emit	SignalFinishCaptureOnly(Res,s->Page,CStrategic,(int)_CaptureOnlyMaster);
							}
						}
						SeqParam->InspectionResult=1;
						if(GetEntryPoint()->IsMasterPC()==true){
							if(GetParamGlobal()->GetMaxScanStrategy()>1 
							&& GetParamGlobal()->GetMaxScanStrategy()>(GetLayersBase()->GetCurrentStrategicNumber()+1)){
								//GetLayersBase()->SetCurrentStrategicNumber(CStrategic+1);
								//GoMasterCaptureOnly();
								//goto	ConditionOut;
								GetLayersBase()->IncreaseCurrentStrategicNumber();
								GetLayersBase()->PopCurrentStrategicNumberForCalc();
								GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
								//goto	ConditionOut;
							}
							else{
								GetLayersBase()->IncreaseCurrentStrategicNumber();
								GetLayersBase()->PopCurrentStrategicNumberForCalc();
								GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
							}
						}
					}
					else{	//Master‚Ì‚Æ‚«
						//if(CStrategic==0)
						//	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							while(Re->IsStrategicFinishedResultReceiving()==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
						else{
							while(Re->IsStrategicFinishedResultReceiving(CStrategic)==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
						SeqParam->InspectionResult=1;
						/*
						if(GetParamGlobal()->GetMaxScanStrategy()>1){
							if(GetParamGlobal()->GetMaxScanStrategy()>(CStrategic+1)){
								GetLayersBase()->SetCurrentStrategicNumber(CStrategic+1);
							}
							else{
								GetLayersBase()->SetCurrentStrategicNumber(0);
							}
						}
						*/
						if(GetParamGlobal()->GetMaxScanStrategy()>1){
							GetLayersBase()->IncreaseCurrentStrategicNumber();
						}
						GetLayersBase()->PopCurrentStrategicNumberForCalc();
						GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
					}
				}
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
			else if(GetMode()==_CaptureInspect || GetMode()==_CaptureInspectWithoutCapture){
				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(GetLayersBase()->GetCurrentStrategicNumber() ,false);

				SeqParam->StartInspection=true;
				TrunStarted++;

				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspactionStatus=33;
					SeqParam->CaptureMode=3;
					CurrentState=_EI_Prepare;
					if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
						CapturePrepare();
					}
					if(GetEntryPoint()->IsMasterPC()==true){
						DWORD	t1=GetComputerMiliSec();
						while(SeqParam->PermitCapture==false){
							msleep(10);
							if(GetHaltMode()==true){
								emit	SignalCaptureHalt();
								ClearHaltMode();
								ExecuteHalt();
								CurrentState=_EI_IDLE;
								SetMode(_CaptureNone);
								goto	IdleTurn;
							}
							if(GetLayersBase()->GetOnTerminating()==true){
								//CamRelease();
								return;
							}
						}
						DWORD	t2=GetComputerMiliSec()-t1;
						t2++;
					}
				}


				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					TrunStartStarted1++;
					CaptureStart();
				}

				if(GetParamGlobal()->BufferedProcessing==false || GetEntryPoint()->IsMasterPC()==true){
					if(GetAutoRepeat()!=_AutoCaptureInspect){
						GetLayersBase()->ExecuteStartByInspection();
						GetLayersBase()->ExecuteFilterBeforeScan();
					}
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
					SeqParam->ReadyForScan=true;
				}
				CurrentState=_EI_OnCapturing;
				int	CamStatus;
				if(GetMode()==_CaptureInspect){
					while((CamStatus=CaptureGetState())!=0){
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							TriggeredCapture=false;
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if((CamStatus & BitCamError)!=0){
							OccurCamError(CamStatus);
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							TriggeredCapture=false;
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						msleep(ExeSleepTimeMilisec);
 						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					TriggeredCapture=false;
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					goto	IdleTurn;
				}
				DWORD	TimeInThisPoint=::GetComputerMiliSec();
			
				if(GetEntryPoint()->IsMasterPC()==true){
					SetCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					EmitSignalCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				TrunCaptured++;
				CurrentState=_EI_OnCalc;
				TriggeredCapture=false;
				if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true && GetLayersBase()->GetOnTerminating()==false){
					if(GetParamGlobal()->WaitMilisecAfterScan==0){
						if(GetAutoRepeat()==_AutoCaptureInspect
						|| GetParamGlobal()->GetMaxScanStrategy()>(GetLayersBase()->GetCurrentStrategicNumberForCalc()+2)
						|| (IsLocalCamera()==true && GetParamGlobal()->UnconditionalCaptureBackground==true)
						|| (GetParamGlobal()->GetMaxScanStrategy()<=1 && GetEntryPoint()->IsMasterPC()==false)){
							TriggeredCapture=true;
							TrunStartStarted2++;
							//StrategicStartList.Add(GetLayersBase()->GetCurrentStrategicNumberForCalc());
							CapturePrepare();
							CaptureStart();
						}
					}
				}
			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"XExecuteInspect:Captured");

					SeqParam->InspactionStatus=34;
					if(GetLayersBase()->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
					
					GetLayersBase()->LockRChangingDataStructure();
					ListPhasePageLayerPack CapturedList;
					if(GetCurrentCaptureSource()==_Target)
						CaptureGetTargetImage(CapturedList);
					else if(GetCurrentCaptureSource()==_Master){
						int	CStrategic=GetLayersBase()->GetCurrentStrategicNumber();
						CaptureGetMasterImage(CStrategic,CapturedList);
					}
					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=GetLayersBase()->GetCurrentScanPhaseNumber();
					if(GetParamGlobal()->AutoIncrementScanPhaseNumber==true){
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							tCurrentScanPhaseNumber++;
							if(tCurrentScanPhaseNumber>=GetLayersBase()->GetPhaseNumb()){
								tCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((GetLayersBase()->GetCurrentStrategicNumber()+1)>=GetParamGlobal()->GetMaxScanStrategy()){
								tCurrentScanPhaseNumber++;
								if(tCurrentScanPhaseNumber>=GetLayersBase()->GetPhaseNumb()){
									tCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

					SeqParam->InspactionStatus=35;
									
					if(GetParamGlobal()->BufferedProcessing==false){
						int	CStrNumber=GetLayersBase()->GetCurrentStrategicNumber();

						DWORD	StartCalcTime=GetComputerMiliSec();
						if(GetParamGlobal()->GetMaxScanStrategy()<=1 
						|| GetParamGlobal()->GetMaxScanStrategy()<=(GetLayersBase()->GetCurrentStrategicNumberForCalc()+1)){
							GetLayersBase()->SetLatchedInspectionNumber(GetLayersBase()->GetInspectionNumber());
						}
						if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
							GetLayersBase()->ExecuteStartByInspection();
						}
						ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
						if(Res!=NULL){
							GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspect:StartCalc",Res->GetInspectionID());

							DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
							GetLayersBase()->PopCurrentStrategicNumberForCalc();

							C=GetComputerMiliSec();
							DWORD	ProcessStartTime=C;

							GetLayersBase()->ExecuteCaptured	(CapturedList);
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteCaptured=Cn-C;
							C=Cn;

							GetLayersBase()->ExecutePreAlignment	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
							C=Cn;

							GetLayersBase()->ExecuteAlignment		();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteAlignment=Cn-C;
							C=Cn;

							GetLayersBase()->ExecutePreProcessing	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreProcessing=Cn-C;
							C=Cn;

							GetLayersBase()->ExecuteProcessing		();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessing=Cn-C;
							C=Cn;

							GetLayersBase()->ExecuteProcessingRevived();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
							C=Cn;

							//ŒŸ¸Š®—¹Žž
							Res->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());

							GetLayersBase()->ExecutePostProcessing	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePostProcessing=Cn-C;
							Res->ExecTime.TM_TotalProcessMilisec=Cn-ProcessStartTime;
							C=Cn;

							GetLayersBase()->SetCurrentScanPhaseNumber(tCurrentScanPhaseNumber);
							EmitCalcDone(CStrNumber);
						
							CurrentState=_EI_IDLE;
				
							while(GetComputerMiliSec()-StartCalcTime<GetParamGlobal()->WaitMilisecAfterScan){
								GSleep(20);
							}
							if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
								if(GetParamGlobal()->WaitMilisecAfterScan!=0){
									TrunStartStarted3++;
									CapturePrepare();
									CaptureStart();
								}
							}
							DWORD	t10=GetComputerMiliSec()-StartCalcTime;
							if(GetParamGlobal()->GetMaxScanStrategy()>1){
								while(Re->IsStrategicFinishedResultReceiving(CStrNumber)==false){
									msleep(20);
									if(GetHaltMode()==true){
										emit	SignalCaptureHalt();
										CurrentState=_EI_IDLE;
										SetMode(_CaptureNone);
										msleep(500);
										ClearHaltMode();
										ExecuteHalt();
										GetLayersBase()->UnlockChangingDataStructure();
										goto	IdleTurn;
									}
									if(GetLayersBase()->GetOnTerminating()==true){
										//CamRelease();
										GetLayersBase()->UnlockChangingDataStructure();
										return;
									}
								}
								if(GetEntryPoint()->IsMasterPC()==true){
									if(GetParamGlobal()->GetMaxScanStrategy()>(CStrNumber+1)){
										GetLayersBase()->IncreaseCurrentStrategicNumber();
										//GetLayersBase()->SetCurrentStrategicNumberForSeq(CStrNumber);
										GetLayersBase()->SetCurrentStrategicNumberForSeq(CStrNumber+1);
										//GoInspect();
									}
									else{
										GetLayersBase()->IncreaseCurrentStrategicNumber();
										//GetLayersBase()->SetCurrentStrategicNumberForSeq(CStrNumber);
										GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
									}
									//goto	ConditionOut;
								}
								else{
									if(GetParamGlobal()->AutoIncreaseStrategicNumberInSlave==true){
										GetLayersBase()->IncreaseCurrentStrategicNumber();
										CStrNumber=GetLayersBase()->GetCurrentStrategicNumber();
										GetLayersBase()->SetCurrentStrategicNumberForSeq(CStrNumber);
										GetLayersBase()->PopCurrentStrategicNumberForCalc();
									}
								}
							}
						}
						//CurrentState=_EI_OnResult;
					}
					else{
						ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
						if(Res!=NULL){
							DWORD	StartCalcTime=GetComputerMiliSec();
							//while(GetLayersBase()->GetTopPageInCapturedPageLayer()>=0)
							//	GSleep(100);
							GetLayersBase()->PushCapturedPageLayer(CurrentCapturedPageLayer);
							StrategicListContainer SList;
							GetParamGlobal()->GetStrategy(GetLayersBase()->GetCurrentStrategicNumber(),SList);
							//ŒŸ¸Š®—¹Žž
							Res->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());
	
							GetLayersBase()->SetCurrentScanPhaseNumber(tCurrentScanPhaseNumber);
							//while(GetComputerMiliSec()-StartCalcTime<GetParamGlobal()->WaitMilisecAfterScan){
							//	GSleep(20);
							//}
							if(GetParamComm()->Mastered==false){
								for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
									emit	SignalFinishCalc(Res,s->Page,GetLayersBase()->GetCurrentStrategicNumber());
								}
							}
							if(GetParamGlobal()->GetMaxScanStrategy()>1 
							&& GetParamGlobal()->GetMaxScanStrategy()>(GetLayersBase()->GetCurrentStrategicNumber()+1)){
								if(GetParamGlobal()->AutoIncreaseStrategicNumberInSlave==true){
									GetLayersBase()->IncreaseCurrentStrategicNumber();
								}
								GoInspect();
								GetLayersBase()->UnlockChangingDataStructure();
								goto	ConditionOut;
							}

							/*
							GetLayersBase()->ExecutePreAlignment	();
							GetLayersBase()->ExecuteAlignment		();
							GetLayersBase()->ExecutePreProcessing	();
							GetLayersBase()->ExecuteProcessing		();
							GetLayersBase()->ExecutePostProcessing	();
							*/
						}
					}
					GetLayersBase()->UnlockChangingDataStructure();
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
				}
				else{	//Master‚Ì‚Æ‚«
					DWORD	StartCalcTime=GetComputerMiliSec();
					ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
					if(Res!=NULL){
						DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
						if(GetLayersBase()->GetCurrentStrategicNumber()==0){
							GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
						}
						GetLayersBase()->PretendFinishProcessing(GetEntryPoint());
						
						DWORD	wCheckTime=::GetComputerMiliSec();
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							for(;;){
								if(Re->IsStrategicFinishedResultReceiving()==true){
									break;
								}
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									TriggeredCapture=false;
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
								if(::GetComputerMiliSec()-wCheckTime>=GetParamGlobal()->RetryTimeToCycleFinish){
									if(GetParamGlobal()->ConfirmResult==true){
										emit	SignalCheckCycle(GetLayersBase()->GetCurrentStrategicNumber());
									}
									wCheckTime=::GetComputerMiliSec();
								}
							}
						}
						else{
							while(Re->IsStrategicFinishedResultReceiving(GetLayersBase()->GetCurrentStrategicNumber())==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									TriggeredCapture=false;
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
								if(::GetComputerMiliSec()-wCheckTime>=GetParamGlobal()->RetryTimeToCycleFinish){
									if(GetParamGlobal()->ConfirmResult==true){
										emit	SignalCheckCycle(GetLayersBase()->GetCurrentStrategicNumber());
									}
									wCheckTime=::GetComputerMiliSec();
								}
							}
							if(GetParamGlobal()->GetMaxScanStrategy()>(GetLayersBase()->GetCurrentStrategicNumber()+1)){
								SeqParam->InspectionResult=1;
							}
							if(GetEntryPoint()->IsMasterPC()==true){
								GetLayersBase()->IncreaseCurrentStrategicNumber();
								GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumber());
							}
						}
						GetLayersBase()->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspect:ReceivedAll",Res->GetInspectionID());
						//SeqParam->PermitCapture=false;
						while(GetComputerMiliSec()-StartCalcTime<GetParamGlobal()->WaitMilisecAfterScan){
							GSleep(20);
						}
					}
				}
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
			else if(GetMode()==_CaptureContinuously){
				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(GetLayersBase()->GetCurrentStrategicNumber() ,false);

				SeqParam->InspactionStatus=1;
				SeqParam->CaptureMode=2;
				SeqParam->StartScanOnly=true;
				GetLayersBase()->ExecuteStartByScanOnly();
				CurrentState=_EI_Prepare;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CapturePrepare();
					GetLayersBase()->ExecuteFilterBeforeScan();
				}
				/*
				if(GetEntryPoint()->IsMasterPC()==true){
					while(SeqParam->PermitCapture==false){
						msleep(10);
						if(GetHaltMode()==true){
							emit	SignalCaptureHalt();
							ClearHaltMode();
							ExecuteHalt();
							CurrentState=_EI_IDLE;
							SetMode(_CaptureNone);
							goto	IdleTurn;
						}
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				*/
				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
					CaptureStart();
				}
				SeqParam->InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
				SeqParam->ReadyForScan=true;
				CurrentState=_EI_OnCapturing;
				int	CamStatus;
				while((CamStatus=CaptureGetState())!=0){
					if(GetHaltMode()==true){
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					if((CamStatus & BitCamError)!=0){
						OccurCamError(CamStatus);
						emit	SignalCaptureHalt();
						ClearHaltMode();
						ExecuteHalt();
						CurrentState=_EI_IDLE;
						SetMode(_CaptureNone);
						goto	IdleTurn;
					}
					msleep(ExeSleepTimeMilisec);
					if(GetLayersBase()->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
				}
				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					goto	IdleTurn;
				}
			
				if(GetEntryPoint()->IsMasterPC()==true){
					SetCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					EmitSignalCaptured(GetLayersBase()->GetCurrentStrategicNumber());
				}
				ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);
					int	CStrategic=GetLayersBase()->GetCurrentStrategicNumber();
					Re->ClearReceivedResultCounts();
					if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
						DWORD	StartCalcTime=GetComputerMiliSec();
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
						TriggeredCapture=false;
						if(GetLayersBase()->GetParamGlobal()->CaptureInBackground==true){
							TriggeredCapture=true;
							CapturePrepare();
							CaptureStart();
						}
						CurrentState=_EI_OnTransmit;
						if(GetLayersBase()->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
						SeqParam->InspactionStatus=2;
						ListPhasePageLayerPack CapturedList;
						CaptureGetTargetImage(CapturedList);
						FuncContainerInCaptureContinuously.ExecuteFunc();

						SeqParam->PermitCapture=false;
						SeqParam->InspactionStatus=3;
						CurrentState=_EI_IDLE;

						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							emit	SignalFinishCaptureOnly(Res,0,CStrategic,(int)_CaptureContinuously);
						}
						else{
							StrategicListContainer SList;
							GetParamGlobal()->GetStrategy(CStrategic,SList);
							//ŒŸ¸Š®—¹Žž

							for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext()){
								emit	SignalFinishCaptureOnly(Res,s->Page,CStrategic,(int)_CaptureContinuously);
							}
						}
						SeqParam->InspectionResult=1;
						if(GetEntryPoint()->IsMasterPC()==true){
							if(GetParamGlobal()->GetMaxScanStrategy()>1 
							&& GetParamGlobal()->GetMaxScanStrategy()>(GetLayersBase()->GetCurrentStrategicNumber()+1)){
								//GetLayersBase()->SetCurrentStrategicNumber(CStrategic+1);
								//GoMasterCaptureOnly();
								//goto	ConditionOut;
								GetLayersBase()->IncreaseCurrentStrategicNumber();
								GetLayersBase()->PopCurrentStrategicNumberForCalc();
								GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
								//goto	ConditionOut;
							}
							else{
								GetLayersBase()->IncreaseCurrentStrategicNumber();
								GetLayersBase()->PopCurrentStrategicNumberForCalc();
								GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
							}
						}
					}
					else{	//Master‚Ì‚Æ‚«
						//if(CStrategic==0)
						//	GetLayersBase()->SetCurrentStrategicNumberForSeq(0);
						if(GetParamGlobal()->GetMaxScanStrategy()<=1){
							while(Re->IsStrategicFinishedResultReceiving()==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
						else{
							while(Re->IsStrategicFinishedResultReceiving(CStrategic)==false){
								msleep(50);
								if(GetHaltMode()==true){
									emit	SignalCaptureHalt();
									CurrentState=_EI_IDLE;
									SetMode(_CaptureNone);
									msleep(500);
									ClearHaltMode();
									ExecuteHalt();
									goto	IdleTurn;
								}
								if(GetLayersBase()->GetOnTerminating()==true){
									//CamRelease();
									return;
								}
							}
						}
						SeqParam->InspectionResult=1;

						GetLayersBase()->PopCurrentStrategicNumberForCalc();
						GetLayersBase()->SetCurrentStrategicNumberForSeq(GetLayersBase()->GetCurrentStrategicNumberForCalc());
					}
					CurrentState=_EI_IDLE;
					//SetMode(_CaptureNone);
				}
			}
ConditionOut:;
		}
		if(GetLayersBase()->GetEntryPoint()->NoCamDevice==false){
			CheckCamera(CameraErrorCode);
		}
		msleep(ExeSleepTimeMilisec);
		if(GetLayersBase()->GetOnTerminating()==true){
			//CamRelease();
			return;
		}
		if(GetHaltMode()==true){
			ExecuteHalt();
			emit	SignalCaptureHalt();
			ClearHaltMode();
			msleep(800);
		}
	}
}

void	ExecuteInspect::EmitCalcDone(int32 nStrategicNumber)
{
	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
	if(Res!=NULL){
		if(GetParamGlobal()->GetMaxScanStrategy()>1){
			IntList PageList;
			GetParamGlobal()->GetStrategyPage(nStrategicNumber,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				emit	SignalFinishCalc(Res,s->GetValue(),nStrategicNumber);
			}
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				emit	SignalFinishCalc(Res,page,nStrategicNumber);
			}
		}
	}
}

void	ExecuteInspect::SlotCheckCycle(int nStrategicNumber)
{
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		CmdCheckReply	ReqReply(GetLayersBase(),"ANY","ANY",globalPage);
		ReqReply.StrategicNumber	=nStrategicNumber;
		ReqReply.Send(NULL,globalPage,0);
	}
}

void	ExecuteInspect::ChangeLot(void)
{
	if(GetMode()==_CaptureInspect || GetMode()==_CaptureInspectWithoutCapture){
		if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
			//GetLayersBase()->ExecuteStartByInspection();
		}
	}
}



//=================================================================================================

CmdInspectionRepliedBase::CmdInspectionRepliedBase(const QString &ClassName ,LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,ClassName ,globalPage)
{
	CountUpID=true;
}
bool	CmdInspectionRepliedBase::Load(QIODevice *f)
{
	BYTE	ResultData;
	if(::Load(f,ResultData)==false)
		return false;
	Result=(__Result)ResultData;
	if(::Load(f,NGCounts)==false)
		return false;
	if(::Load(f,NGImageCount)==false)
		return false;
	if(::Load(f,TimeOutBreak)==false)
		return false;
	if(::Load(f,MaxErrorBreak)==false)
		return false;
	if(::Load(f,CountUpID)==false)
		return false;
	if(::Load(f,ExecuterID)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	CmdInspectionRepliedBase::Save(QIODevice *f)
{
	BYTE	ResultData=(BYTE)Result;
	if(::Save(f,ResultData)==false)
		return false;
	if(::Save(f,NGCounts)==false)
		return false;
	if(::Save(f,NGImageCount)==false)
		return false;
	if(::Save(f,TimeOutBreak)==false)	
		return false;
	if(::Save(f,MaxErrorBreak)==false)
		return false;
	if(::Save(f,CountUpID)==false)
		return false;
	if(::Save(f,ExecuterID)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}
IntList	DbgList;
IntList	DbgList2;

static	XDateTime	LastStartTimeForInspection;
static	int			eRepliedCounter=0;
static	int			eOutputCounter=0;

void	CmdInspectionRepliedBase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if((GetParamGlobal()->DebugLevel & 0x04)!=0){
		DbgList.Add(localPage);
	}
	eRepliedCounter++;

	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=L->GetExecuter(ExecuterID);
	ResultInspection	*Res=Re->GetResultInspection();
	L->GetEntryPoint()->GetExecuteInspect()->FinishCapture(localPage);
	Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);



	//GetLayersBase()->GetLogCreater()->PutLogA2(__LINE__	,"CmdInspectionRepliedBase::Receive"
	//													,buff
	//													,Res->GetInspectionID());




	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	ExecuteInspect	*EP=(ExecuteInspect *)EPBase;
	//if(_CrtCheckMemory()==false)
	//	return;
	if(((ExecuteInspectBase::MotionMode)cmd)==ExecuteInspectBase::_CaptureInspect){
		if(Re->IsAllFinishedResultReceiving()==true){
		//	if(LastStartTimeForInspection==Res->GetStartTimeForInspection()){
		//		return;
		//	}
			LastStartTimeForInspection=Res->GetStartTimeForInspection();

			if(GetParamGlobal()->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
				L->SetLatchedInspectionNumber(GetLayersBase()->GetInspectionNumber());
			}
			EP->StackedCountInAutoMode--;
			eOutputCounter++;

			//ŒŸ¸Š®—¹Žž

			if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
				//|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(L->GetCurrentStrategicNumber()+1))
				|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
				|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){

				EP->SeqParam->InspectionID=L->GetCurrentInspectIDForExecute();
				EP->SeqParam->PermitCapture=false;
				EP->SeqParam->NowProcessing	=false;

				bool3	ShadowOk;
				bool	ShadowTimeOver;
				bool	ShadowMaxError;
				L->GetShadowResult(Res
								,ShadowOk ,ShadowTimeOver, ShadowMaxError
								,true,false);

				EP->SeqParam->InspectionResultSub=0;
				Res->SetTimeOutBreak(false);
				Res->SetMaxErrorBreak(false);
				ResultPkNgPacket	ResultPacket(GetLayersBase());

				if(Re->IsResultTimeOut()==true || ShadowTimeOver==true){
					Res->SetTimeOutBreak(true);
					ResultPacket.TimeOver=true;
					if(Re->IsResultMaxError()==true){
						ResultPacket.MaxError=true;
						Res->SetMaxErrorBreak(true);
						EP->SeqParam->InspectionResultSub=5;
					}
					else{
						EP->SeqParam->InspectionResultSub=3;
					}
				}
				else{
					if(Re->IsResultMaxError()==true || ShadowMaxError==true){
						ResultPacket.MaxError=true;
						Res->SetMaxErrorBreak(true);
						EP->SeqParam->InspectionResultSub=4;
					}
				}
				int	ResultCode=0;
				if(Re->IsResultOK()==true && ShadowOk==true3){
					EP->SeqParam->InspectionResultSub=1;
					EP->SeqParam->InspectionResult=1;
					EP->SeqParam->InspectionFinalResult	=1;
					ResultPacket.Ok=true3;
					GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(-1,Res,&ResultPacket);
					ResultCode=1;
					Res->SetOutputCode(ResultCode);
				}
				else{
					if(EP->SeqParam->InspectionResultSub==0)
						EP->SeqParam->InspectionResultSub=2;
					EP->SeqParam->InspectionResult=2;
					EP->SeqParam->InspectionFinalResult	=2;
					ResultPacket.Ok=false3;
					GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(-1,Res,&ResultPacket);
					ResultCode=2;
					Res->SetOutputCode(ResultCode);
				}
				
				if(EP->IsLocalCamera()==false){	//MASTER‚Ì‚Æ‚«
					GetLayersBase()->ExecutePostProcessing		();
				}
				ResultInspection	*eRes=GetLayersBase()->GetCurrentResultForCalc();
				if(eRes!=NULL){
					DataInExecuter	*eRe=GetLayersBase()->GetExecuter(eRes);
					if(eRe!=Re){
						eRe->CopyResultCountFrom(*Re);
					}
					if(CountUpID==true){
						//if((GetParamGlobal()->AutoIncrementScanPhaseNumber==false && (L->GetCurrentScanPhaseNumber()+1)>=GetParamGlobal()->GetScanPhaseCount())
						if((((L->GetCurrentScanPhaseNumber()+1)>=GetParamGlobal()->GetScanPhaseCount())
						 || (GetParamGlobal()->AutoIncrementScanPhaseNumber==true && L->GetCurrentScanPhaseNumber()==0))
						&& (GetParamGlobal()->OutputOnlyPhase==-1 || GetParamGlobal()->OutputOnlyPhase==GetLayersBase()->GetCurrentScanPhaseNumber())){
							DWORD InspectionTimeMilisec=GetComputerMiliSec() - L->GetStartInspectionTimeMilisec();
							L->SetInspectionTimeMilisec(InspectionTimeMilisec);
							L->SetEndInspectionTime(XDateTime::currentDateTime());
							L->GetResultHistryData()->AddHistry(EP->SeqParam->InspectionResult
														,Res->GetStartTimeForInspection()
														,L->GetCurrentInspectIDForExecute()
														,Res->GetIDStr()
														,Re->IsResultTimeOut()
														,Re->IsResultMaxError()
														,Res->ExecTime.TM_TotalProcessMilisec);
	
							//L->LogicDLLBase->ResultData.StartTimeForInspection	=L->CurrentInspectID;
							Res->SetInspectionID(L->GetCurrentInspectIDForExecute());
							//GSleep(1000);
							if(EP->SeqParam->NotOutputResult==false){
								Re->PutCurrentResult();
							}
							L->IncrementInspectID();
							L->ShowShadowHistory(ResultCode,true,false, InspectionTimeMilisec);
						}
					}
				}
				L->CloseProcessingForm();
				EP->SeqParam->AllFinishInProcess=false;
				if(GetParamGlobal()->ReDrawByInspection==true){
					GetLayersBase()->GetGuiInitializer()->RefreshByEveryInspection(L->GetCurrentInspectIDForDisplay());
					if(GetParamGlobal()->WaitmilisecForDelayedView!=0){
						GetLayersBase()->GetGuiInitializer()->DelayedViewRefreshInPlayer(L->GetCurrentInspectIDForDisplay(),GetParamGlobal()->WaitmilisecForDelayedView);
					}
					else{
						GetLayersBase()->GetGuiInitializer()->ViewRefreshInPlayer(L->GetCurrentInspectIDForDisplay());
					}
				}
				//GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->ViewRefreshShown(L->GetCurrentInspectIDForDisplay());

			}
			else{
				EP->SeqParam->PermitCapture=false;
				if(Re->IsResultOK()==true){
					EP->SeqParam->InspectionResult=1;
					Res->SetOutputCode(1);
				}
				else{
					EP->SeqParam->InspectionResult=2;
					Res->SetOutputCode(2);
				}
			L->CloseProcessingForm();
			}
			//GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->GetFirstForm()->BroadcastDirectly(_BC_DoneCalc,LastInspectID);
		}
		else{
			EP->StackedCountInAutoMode--;
			eOutputCounter++;
			if(L->GetParamGlobal()->GetMaxScanStrategy()>1){
				EP->SeqParam->PermitCapture=false;
				EP->SeqParam->InspectionResult=1;
			}
			if(Re->GetCountOfFinishedResultReceiving()==1){
				L->SetLatchedInspectionNumber(L->GetInspectionNumber());
			}
		}
	}
	else{
		if(Re->IsAllFinishedResultReceiving()==true){
			L->CloseProcessingForm();
			//GetLayersBase()->GetEntryPoint()->GetGUIInstancePack()->ViewRefreshInPlayer(L->GetCurrentInspectIDForDisplay());
		}
		if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
		//|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(L->GetCurrentStrategicNumber()+1))
		|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){
			EP->SeqParam->InspectionResultSub=1;
			EP->SeqParam->InspectionResult=1;
			if((GetParamGlobal()->DebugLevel & 0x04)!=0){
				DbgList2.Add(localPage);
			}
		}
		if(Re->IsAllFinishedResultReceiving()==true){
			GetLayersBase()->GetGuiInitializer()->RefreshByEveryInspection(L->GetCurrentInspectIDForDisplay());
			GetLayersBase()->GetGuiInitializer()->ViewRefreshInPlayer		(L->GetCurrentInspectIDForDisplay());
		}
	}
}

CmdInspectionReplied::CmdInspectionReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:CmdInspectionRepliedBase(typeid(this).name(),base,EmitterRoot,EmitterName ,globalPage)
{
}
CmdInspectionRepliedBuffered::CmdInspectionRepliedBuffered(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:CmdInspectionRepliedBase(typeid(this).name(),base,EmitterRoot,EmitterName ,globalPage)
{
}
//=================================================================================================

GUIExecuteCmdStartInspect::GUIExecuteCmdStartInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUIExecuteCmdStartInspect::~GUIExecuteCmdStartInspect(void)
{
}

bool	GUIExecuteCmdStartInspect::Load(QIODevice *f)
{
	if(::Load(f,StartInspectionTime)==false)
		return false;
	if(::Load(f,CurrentInspectID)==false)
		return false;
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	GUIExecuteCmdStartInspect::Save(QIODevice *f)
{
	if(::Save(f,StartInspectionTime)==false)
		return false;
	if(::Save(f,CurrentInspectID)==false)
		return false;
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}

void	GUIExecuteCmdStartInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetStartInspectTime(StartInspectionTime);
	GetLayersBase()->SetCurrentInspectID(CurrentInspectID);
	GetLayersBase()->SetCurrentStrategicNumber(StrategicNumber);
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		ExecuteInspect	*E=(ExecuteInspect	*)GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
		if(E->GetMode()==ExecuteInspectBase::_CaptureInspect){
			if(E->TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
				E->CapturePrepare();
			}
			if(E->TriggeredCapture==false || GetLayersBase()->GetParamGlobal()->CaptureInBackground==false){
				E->CaptureStart();
			}
			/*
			if(GetParamGlobal()->BufferedProcessing==false){
				if(E->IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
					GetLayersBase()->ExecuteStartByInspection();
					GetLayersBase()->ExecuteFilterBeforeScan();
				}
			}
			*/
		}
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoInspect();
	}
	
	GUIExecuteCmdReplyInspect	*SendBack=GetSendBack(GUIExecuteCmdReplyInspect,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIExecuteCmdReplyInspect::GUIExecuteCmdReplyInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUIExecuteCmdReplyInspect::~GUIExecuteCmdReplyInspect(void)
{
}

bool	GUIExecuteCmdReplyInspect::Load(QIODevice *f)
{
	return true;
}
bool	GUIExecuteCmdReplyInspect::Save(QIODevice *f)
{
	return true;
}

void	GUIExecuteCmdReplyInspect::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//=================================================================================================
CmdCheckReply::CmdCheckReply(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	StrategicNumber=0;
}
bool	CmdCheckReply::Load(QIODevice *f)
{
	if(::Load(f,StrategicNumber)==false)
		return false;
	return true;
}
bool	CmdCheckReply::Save(QIODevice *f)
{
	if(::Save(f,StrategicNumber)==false)
		return false;
	return true;
}
void	CmdCheckReply::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
	if(Res!=NULL){
		DataInExecuter	*Re=GetLayersBase()->GetExecuter(Res);

		if(Re->IsStrategicFinishedResultReceiving(StrategicNumber)==true){
			ExecuteInspect	*E=(ExecuteInspect	*)GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
			if(E!=NULL){
				E->EmitCalcDone(StrategicNumber);
			}
		}
	}
}


//=================================================================================================

GUIExecuteCmdCancelCapture::GUIExecuteCmdCancelCapture(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
GUIExecuteCmdCancelCapture::~GUIExecuteCmdCancelCapture(void)
{
}
void	GUIExecuteCmdCancelCapture::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ExecuteInspect	*E=(ExecuteInspect	*)GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		//E->GoHalt();		
		E->CaptureHalt();

		GetLayersBase()->ClearTopInCapturedPageLayer();
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
		GetLayersBase()->PopCurrentStrategicNumberForCalc();
		E->SeqParam->CaptureStartCounter=0;

		E->ClearHaltMode();
	}
	//SendAck(localPage);
}
//=================================================================================================

CmdCapturedOnly::CmdCapturedOnly(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	CmdCapturedOnly::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ExecuteInspect	*E=(ExecuteInspect	*)GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		E->SeqParam->DoneCapture=true;
		if(GetEntryPoint()->IsMasterPC()==false){
			E->SeqParam->Captured(localPage);
		}
		E->SeqParam->NowProcessing	=true;
	}
}

//=================================================================================================
CmdCaptureBegins::CmdCaptureBegins(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
void	CmdCaptureBegins::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	ExecuteInspect	*E=(ExecuteInspect	*)GetLayersBase()->GetEntryPoint()->GetExecuteInspect();
	if(E!=NULL){
		E->SeqParam->SetCaptureBegins(localPage);
		E->SeqParam->CaptureStartCounter=cmd;
	}
}


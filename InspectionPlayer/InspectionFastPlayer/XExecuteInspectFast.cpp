/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XExecuteInspectFast.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XDateTime.h"
#include <QThread>
//#include "XCameraInterfaceDLL.h"
#include "XCameraClass.h"
#include "XExecuteInspectFast.h"
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
//#include "XSequence.h"
#include "XPIOButton.h"
#include "XLogOut.h"
#include "XResult.h"
#include "swap.h"
#include <omp.h>

const	int		MAXBUFFERCOUNTS=10000;
const	int		ExeSleepTimeMilisec=1;

ExecuteInspectFast	*ExecuteInspectFast::StaticInstance=NULL;
void	KickAutoStart(LayersBase *base);


ThreadOutputResult::ThreadOutputResult(QObject *obj ,LayersBase *Base)
	:QThread(obj),ServiceForLayers(Base),ResultPacket(Base)
{
	Res=NULL;
	AddedMilisec	=0;
	Terminated		=false;
	InspectionStart	=false;
	EndOfInspection	=false;
	ThreadMode		=true;
	setPriority(QThread::HighestPriority);
}

ThreadOutputResult::~ThreadOutputResult(void)
{
}

void	ThreadOutputResult::StartThreadMode(bool _ThreadMode)
{
	ThreadMode=_ThreadMode;
	if(ThreadMode==true){
		start();
	}
}
	
void	ThreadOutputResult::run()
{
	while(Terminated==false){
		while(InspectionStart==true && Terminated==false){
			DWORD	CurrentTime=::GetComputerMiliSec();
			if((CurrentTime-StartMilisec+AddedMilisec)>=GetParamGlobal()->MaxInspectMilisec){
				MutexOutput.lock();
				ResultPacket.Ok=false3;
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				ResultPacket.MaxError=false;
				GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(-1,Res,&ResultPacket);
				InspectionStart=false;
				MutexOutput.unlock();
			}
			else{
				if(EndOfInspection==true){
					MutexOutput.lock();
					GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(ResultMode,Res,&ResultPacket);
					InspectionStart=false;
					MutexOutput.unlock();
				}
				else{
					msleep(5);
				}
			}
		}
		msleep(10);
	}
}
void	ThreadOutputResult::Terminate(void)
{
	Terminated=true;
	if(ThreadMode==true){
		wait(1000);
	}
}
void	ThreadOutputResult::SetStart(ResultInspection *R,DWORD _AddedMilisec)
{
	if(R!=NULL){
		AddedMilisec=_AddedMilisec;
		Res=R;
		EndOfInspection	=false;
		StartMilisec=::GetComputerMiliSec();
		InspectionStart=true;

		if(ThreadMode==false){
			DWORD	CurrentTime=::GetComputerMiliSec();
			if((CurrentTime-StartMilisec+AddedMilisec)>=GetParamGlobal()->MaxInspectMilisec){
				MutexOutput.lock();
				ResultPacket.Ok=false3;
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				ResultPacket.MaxError=false;
				//etLayersBase()->GetResultDLLBase()->OutputResultDirectly(-1,Res,&ResultPacket);
				InspectionStart=false;
				MutexOutput.unlock();
			}
		}
	}
}

void	ThreadOutputResult::SetOutput(int RMode ,ResultPkNgPacket &P)
{
	MutexOutput.lock();
	ResultMode=RMode;
	ResultPacket=P;
	EndOfInspection=true;
	MutexOutput.unlock();

	if(ThreadMode==false){
		MutexOutput.lock();
		DWORD	CurrentTime=::GetComputerMiliSec();
		GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(ResultMode,Res,&ResultPacket);
		InspectionStart=false;
		ExecutedTime=::GetComputerMiliSec()-CurrentTime;

		MutexOutput.unlock();
	}
}

//================================================================================================

ExecuteInspectFast::ExecuteInspectFast(QObject *parent ,EntryPointBase *_EntryPoint ,SeqControlParam *_SeqParam) 
: ExecuteInspectBase(parent,_EntryPoint,_SeqParam)
,ThreadOutputResultInst(parent,_EntryPoint->GetLayersBase())
,GoSlotAutomodeStart(false)
{
	Cam						=NULL;

	SeqParam				=_SeqParam;
	AllocatedCamNumb		=0;
	StaticInstance			=this;
	StackedCountInAutoMode	=0;
	ResultInspectionToAccessInSlotAutomodeStart	=NULL;
	StatusCameraHalt		=false;
	NowOnWorking			=false;
	SignalCounter			=0;

	AllocatedPage		=0;
	TriggeredCapture	=false;
	setPriority(QThread::HighestPriority);
}

ExecuteInspectFast::~ExecuteInspectFast(void)
{
	ThreadOutputResultInst.Terminate();
	Release();
}

bool	ExecuteInspectFast::InitialCamera(int32 &ErrorCode)
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
bool	ExecuteInspectFast::ChangeCameraInfo(CameraReqInfoAnyData *anydata)
{
	if(IsLocalCamera()==true){
		ChangingCameraInfo.lock();
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]->ChangeInfo(GetParamGlobal()->GetDotPerLineInCamera(i) 
								 ,GetParamGlobal()->GetMaxLinesInCamera(i)
								 , GetLayersBase()->GetMaxLayerNumb(),GetPageNumb()
								 ,anydata)==false){
				ChangingCameraInfo.unlock();
				return(false);
			}
		}
		ChangingCameraInfo.unlock();
	}
	return true;
}

bool	ExecuteInspectFast::CheckCameraDLL(void)
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

QString	ExecuteInspectFast::MakeCamDefaultName(void)
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

bool	ExecuteInspectFast::LoadDefault(void)
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

bool	ExecuteInspectFast::Load(QIODevice *file)
{
	for(int i=0;i<GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID) && i<AllocatedCamNumb;i++){
		int32	Len;
		if(::Load(file,Len)==false){
			return(false);
		}
		QByteArray	AR;
		if(::Load(file,AR)==false){
			return(false);
		}
		QBuffer	TmpBuff(&AR);
		TmpBuff.open(QIODevice::ReadOnly);
		if(Cam[i]->Load(TmpBuff)==false){
			return(false);
		}
	}
	return(true);
}
bool	ExecuteInspectFast::LoadDefaultOldVer(void)
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
bool	ExecuteInspectFast::SaveDefault(void)
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
bool	ExecuteInspectFast::Save(QIODevice *file)
{
	for(int i=0;i<AllocatedCamNumb;i++){
		QBuffer	TmpBuff;
		TmpBuff.open(QIODevice::WriteOnly);
		if(Cam[i]->Save(TmpBuff)==false){
			return(false);
		}
		int32	Len=TmpBuff.size();
		if(::Save(file,Len)==false){
			return(false);
		}
		QByteArray	AR=TmpBuff.buffer();
		if(::Save(file,AR)==false){
			return(false);
		}
	}
	return true;
}


void	ExecuteInspectFast::Initial(void)
{
	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
	Cam=new CameraClass*[AllocatedCamNumb];
	for(int i=0;i<AllocatedCamNumb;i++){
		Cam[i]=new CameraClass(i,GetLayersBase());
	}
	connect( this,SIGNAL(SignalCaptureHalt())							
			,this,SLOT(SlotCaptureHalt())							,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalInspectionRefresh(LayersBase *,int64))	
			,this,SLOT(SlotInspectionRefresh(LayersBase *,int64))	,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalInspectionOnTheWay(int64))				
			,this,SLOT(SlotInspectionOnTheWay(int64))				,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalScanningRefresh(int64))					
			,this,SLOT(SlotScanningRefresh(int64))					,Qt::QueuedConnection);
	connect( this,SIGNAL(SignalRunByEveryInspection(LayersBase *,int64))	
			,this,SLOT(SlotRunByEveryInspection(LayersBase *,int64)),Qt::QueuedConnection);
	connect( this,SIGNAL(SignalOccurError(int))
			,this,SLOT(SlotOccurError(int))							,Qt::QueuedConnection);
}

IntList	DbgFinList;
IntList	DbgStrFinList;

CameraClass		*ExecuteInspectFast::GetCamera(int n)
{	
	if(0<=n && n<GetParamGlobal()->TotalCameraNumb && n<AllocatedCamNumb)
		return Cam[n];
	return NULL;
}

int		ExecuteInspectFast::GetCameraDim(CameraClass *CamDim[])
{
	int	n=0;
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb && i<AllocatedCamNumb;i++){
		CamDim[i]=Cam[i];
		n++;
	}
	return n;
}

void	ExecuteInspectFast::SetCameraDim(CameraClass *CamDim[])
{
	GetLayersBase()->LockWChangingDataStructure();
	for(int i=0;i<GetParamGlobal()->TotalCameraNumb && i<AllocatedCamNumb;i++){
		Cam[i]=CamDim[i];
	}
	GetLayersBase()->UnlockChangingDataStructure();
}

void	ExecuteInspectFast::SetCaptured(int CStrategic)
{
	LayersBase	*LBase=GetLayersBase();
	IntList PhaseCodes;
	LBase->GetCurrentPhaseFromScanPhase(PhaseCodes);

	SeqParam->DoneCapture=true;

	if(LBase->GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				SeqParam->Captured(LBase->GetGlobalPageFromLocal(page));
			}
		}
	}
	else{
		if(IsLocalCamera()==true){
			StrategicListContainer SList;
			LBase->GetParamGlobal()->GetStrategy(CStrategic,SList);
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
				SeqParam->Captured(LBase->GetGlobalPageFromLocal(PageType[i]));
			}
		}
	}
	SeqParam->NowProcessing	=true;
}

void	ExecuteInspectFast::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SpecifiedDirectly(v);
			}
		}
	}
	CmdReqInspectionRefresh	*CmdReqInspectionRefreshVar=dynamic_cast<CmdReqInspectionRefresh *>(v);
	if(CmdReqInspectionRefreshVar!=NULL){
		emit	SignalInspectionRefresh(GetLayersBase(),CmdReqInspectionRefreshVar->InspectionID);
		for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
			emit	SignalInspectionRefresh(L->Base,CmdReqInspectionRefreshVar->InspectionID);
		}
		return;
	}
}

void	ExecuteInspectFast::SetScanInfo(int ScanNumber ,bool ScanMastered)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			if(Cam[i]!=NULL){
				Cam[i]->SetScanInfo(ScanNumber ,ScanMastered);
			}
		}
	}
}

void	ExecuteInspectFast::Release(void)
{
	if(isFinished()==false){
		terminate();
		wait(1000);
	}
	//CamRelease();
}

void	ExecuteInspectFast::CamRelease(void)
{
	if(Cam!=NULL){
		for(int i=0;i<AllocatedCamNumb;i++){
			delete	Cam[i];
		}
		delete	[]Cam;
	}
	Cam=NULL;
}

bool	ExecuteInspectFast::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}

int		ExecuteInspectFast::GetCameraCount(void)
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

bool	ExecuteInspectFast::CheckCamera(int32 &ErrorCode)
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

bool	ExecuteInspectFast::CapturePrepare(void)
{
	if(IsLocalCamera()==true && GetEntryPoint()->NoCamDevice==false){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->PrepareCapture();
		}
		return(true);
	}
	return(false);
}
bool	ExecuteInspectFast::CaptureStart(void)
{
	if(IsLocalCamera()==true && GetEntryPoint()->NoCamDevice==false){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->StartCapture();
		}
		//qWarning(/**/"CaptureStart\n");

		StatusCameraHalt=false;
		SeqParam->CaptureStartCounter++;
		if(SeqParam->CaptureStartCounter>GetParamGlobal()->GetMaxScanStrategy()){
			SeqParam->CaptureStartCounter=1;
		}

		TriggeredCapture=true;
		return(true);
	}
	return(false);
}


bool	ExecuteInspectFast::CaptureHalt(void)
{
	if(IsLocalCamera()==true && GetEntryPoint()->NoCamDevice==false){
		StatusCameraHalt=true;
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->HaltCapture();
		}
		GetLayersBase()->ClearTopInCapturedPageLayer();
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();
		GetLayersBase()->PopCurrentStrategicNumberForCalc();
		SeqParam->CaptureStartCounter=0;

		ClearHaltMode();
		TriggeredCapture=false;
		return(true);
	}
	GetLayersBase()->CloseProcessingForm();
	return(false);
}
void	ExecuteInspectFast::SlotCaptureHalt()
{
	if(GetEntryPoint()->IsMasterPC()==true){

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
}

int		ExecuteInspectFast::CaptureGetState(void)
{
	if(IsLocalCamera()==true && GetEntryPoint()->NoCamDevice==false){
		if(StatusCameraHalt==true){
			GoHalt();
		}
		if(GetParamGlobal()->GetMaxScanStrategy()<=1){
			if(AllocatedCamNumb>0){
				for(int i=0;i<AllocatedCamNumb;i++){
					int	W=Cam[i]->GetStatus();
					if(W!=0){
						return W;
					}
				}
				return 0;
				//int	ret=Cam[0]->GetStatus();
				//for(int i=1;i<AllocatedCamNumb;i++){
				//	int	W=Cam[i]->GetStatus();
				//	ret&=W;
				//}
				//return(ret);
			}
			return 0;
		}
		else{
			int	ret=0;
			for(int i=0;i<AllocatedCamNumb;i++){
				int	W=Cam[i]->GetStatus();
				ret|=W;
			}
			return(ret);
		}
	}
	return(0);
}

IntList	PDbgSlotList;

bool	ExecuteInspectFast::CaptureGetMasterImage(int CStrategic,ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];

	if(GetParamGlobal()->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			for(int page=0;page<GetPageNumb();page++){
				DataInPage	*P=GetLayersBase()->GetPageDataPhase(CPhase)->GetPageData(page);
				ImageBuffer	*Buff[P->GetLayerNumb()];
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
					ImageBuffer	*Buff[SList.GetCount()];
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
					ImageBuffer	*Buff[SList.GetCount()];
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
				ImageBuffer	*Buff[SList.GetCount()];
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

bool	ExecuteInspectFast::CaptureGetTargetImage(ListPhasePageLayerPack &CapturedList)
{
	IntList PhaseCodes;
	LayersBase	*LBase	=GetLayersBase();
	ParamGlobal	*ParamG	=GetParamGlobal();

	LBase->GetCurrentPhaseFromScanPhase(PhaseCodes);
	int	CPhase=PhaseCodes[0];
	LBase->LockTarget();

	CurrentCapturedPageLayer.RemoveAll();
	if(ParamG->GetMaxScanStrategy()<=1){
		if(IsLocalCamera()==true){
			int	N=GetPageNumb();
			if(N==1){
				for(int page=0;page<N;page++){
					DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(page);
					if(P->GetEnableCapture()==true){
						//ImageBuffer	*Buff[P->GetLayerNumb()];//MAXBUFFERCOUNTS];
						ImageBuffer	*Buff[1000];
						ImageBuffer	*TRBuff[P->GetLayerNumb()];//MAXBUFFERCOUNTS];
						int			BuffNumb=0;
						for(int layer=0;layer<P->GetLayerNumb();layer++){
							DataInLayer	*L=P->GetLayerData(layer);
							if(SeqParam->InspectionStrategy==ParamG->GetStrategyCode(page ,layer)){
								L->StoringStartTargetBuff();
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
							ParamG->GetPageDir(page ,XDirReverse ,YDirReverse);
							bool tXDirReverse	=XDirReverse;
							bool tYDirReverse	=YDirReverse;
							if(Cam[page]->IsTREffective()==false){
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
						if(ParamG->AllocCamTargetBuffer==true){
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								L->GetCamTargetBuff()=L->GetTargetBuff();
							}
						}
					}
				}
			}
			else{
				if(ParamG->GetMaxScanStrategy()==1 && GetPageNumb()<=AllocatedCamNumb) {
					for(int CamNo=0;CamNo<AllocatedCamNumb;CamNo++){
						int			BuffNumb=0;
						ImageBuffer	*Buff[1000];
						ImageBuffer	*TRBuff[1000];
						IntList PageList;
						ParamG->GetPageListFromCameraNo(CamNo ,PageList);
						for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
							int	page=p->GetValue();
							DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(page);
							if(P->GetEnableCapture()==true){
								for(int layer=0;layer<P->GetLayerNumb();layer++){
									DataInLayer	*L=P->GetLayerData(layer);
									L->StoringStartTargetBuff();
									Buff  [BuffNumb]=L->GetTargetBuffPointer();
									TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
									CapturedList.Merge(CPhase,page,layer);
									BuffNumb++;
									if(BuffNumb>1000)
										break;
								}
							}
						}
						if(BuffNumb>0){
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
						}
					}
				}
				else{
					//#pragma omp parallel for
					for(int page=0;page<N;page++){
						DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(page);
						if(P->GetEnableCapture()==true){
							ImageBuffer	*Buff[P->GetLayerNumb()];
							ImageBuffer	*TRBuff[P->GetLayerNumb()];
							int			BuffNumb=0;
							for(int layer=0;layer<P->GetLayerNumb();layer++){
								DataInLayer	*L=P->GetLayerData(layer);
								if(SeqParam->InspectionStrategy==ParamG->GetStrategyCode(page ,layer)){
									L->StoringStartTargetBuff();
									Buff[BuffNumb]=L->GetTargetBuffPointer();
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
								ParamG->GetPageDir(page ,XDirReverse ,YDirReverse);
								bool tXDirReverse	=XDirReverse;
								bool tYDirReverse	=YDirReverse;

								if(Cam[page]->IsTREffective()==false)
									Cam[page]->GetImage(Buff ,BuffNumb,tXDirReverse ,tYDirReverse);
								else
									Cam[page]->GetImage(Buff ,TRBuff,BuffNumb,tXDirReverse ,tYDirReverse);

								if((XDirReverse==true && tXDirReverse==true) || (tYDirReverse==true && YDirReverse==true)){
									ImageReverse(page,Buff ,BuffNumb);
								}
								ImageYDelay(page,Buff ,BuffNumb);
							}
							if(ParamG->AllocCamTargetBuffer==true){
								for(int layer=0;layer<P->GetLayerNumb();layer++){
									DataInLayer	*L=P->GetLayerData(layer);
									L->GetCamTargetBuff()=L->GetTargetBuff();
								}
							}
						}
					}
				}
			}
			if(PhaseCodes.GetCount()>1){
				for(int i=1;i<PhaseCodes.GetCount();i++){
					int	phase=PhaseCodes[i];
					for(int page=0;page<GetPageNumb();page++){
						if(LBase->GetPageDataPhase(phase)->GetFromSourcePhase()==CPhase){
							DataInPage	*Ps=LBase->GetPageDataPhase(CPhase)->GetPageData(page);
							DataInPage	*Pd=LBase->GetPageDataPhase(phase)->GetPageData(page);
							if(Pd->GetEnableCapture()==true){
								for(int layer=0;layer<Ps->GetLayerNumb();layer++){
									DataInLayer	*Ls=Ps->GetLayerData(layer);
									DataInLayer	*Ld=Pd->GetLayerData(layer);
									
									if(SeqParam->InspectionStrategy==ParamG->GetStrategyCode(page ,layer)){
										if(ParamG->CommonTargetBetweenPhases==false){
											Ld->StoringStartTargetBuff();
											Ld->GetTargetBuff()		=Ls->GetTargetBuff();
											CapturedList.Merge(phase,page,layer);
										}
										if(ParamG->AllocCamTargetBuffer==true){
											Ld->GetCamTargetBuff()	=Ls->GetTargetBuff();
										}
									}
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
			ParamG->GetStrategy(LBase->GetCurrentStrategicNumber(),SList);
			int	N=0;
			int	PageType[10];
			int	PageTypeNumb=0;
			for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
				DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(s->Page);
				if(P->GetEnableCapture()==true){
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
			}
	
			//Žæ‚èž‚Ý‚ð‘‚­‚·‚é‚½‚ß‚Éæ‚ÉGetImage‚¾‚¯‚ðs‚¤
			//#pragma omp parallel                             
			//{                                                
			//	#pragma omp for
			bool XDirReverse ,YDirReverse;
			ParamG->GetPageDir(LBase->GetCurrentStrategicNumber() ,XDirReverse ,YDirReverse);
			bool tXDirReverse	=XDirReverse;
			bool tYDirReverse	=YDirReverse;
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					ImageBuffer	*Buff[SList.GetCount()];
					ImageBuffer	*TRBuff[SList.GetCount()];
					int	BuffNumb=0;
					int	CamNo=ParamG->GetCameraNo(PageType[camcode]);
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						L->StoringStartTargetBuff();
						Buff  [BuffNumb]=L->GetTargetBuffPointer();
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
					ImageBuffer	*Buff[SList.GetCount()];
					ImageBuffer	*TRBuff[SList.GetCount()];
					int	BuffNumb=0;
					for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
						if(PageType[camcode]!=s->Page)
							continue;
						DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(s->Page);
						DataInLayer	*L=P->GetLayerData(s->Layer);
						L->StoringStartTargetBuff();
						Buff  [BuffNumb]=L->GetTargetBuffPointer();
						TRBuff[BuffNumb]=L->GetTargetTRBuffPointer();
						CapturedList.Merge(CPhase,s->Page,s->Layer);
						BuffNumb++;
						//if(BuffNumb>=MAXBUFFERCOUNTS)
						//	break;
					}
					ImageReverse(LBase->GetCurrentStrategicNumber(),Buff ,BuffNumb);
				}
				for(int camcode=0;camcode<PageTypeNumb;camcode++){
					if(ParamG->AllocCamTargetBuffer==true){
						for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
							if(PageType[camcode]!=s->Page)
								continue;
							DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(s->Page);
							DataInLayer	*L=P->GetLayerData(s->Layer);
							L->GetCamTargetBuff()=L->GetTargetBuff();
						}
					}
				}
			}
			for(int camcode=0;camcode<PageTypeNumb;camcode++){
				int	BuffNumb=0;
				ImageBuffer	*Buff[SList.GetCount()];
				for(StrategicList *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
					if(PageType[camcode]!=s->Page)
						continue;
					DataInPage	*P=LBase->GetPageDataPhase(CPhase)->GetPageData(s->Page);
					DataInLayer	*L=P->GetLayerData(s->Layer);
					L->StoringStartTargetBuff();
					Buff[BuffNumb]=L->GetTargetBuffPointer();
					CapturedList.Merge(CPhase,s->Page,s->Layer);
					BuffNumb++;
					//if(BuffNumb>=MAXBUFFERCOUNTS)
					//	break;
				}
				ImageYDelay(PageType[camcode],Buff ,BuffNumb);
			}
		}
	}
	FilteringMilisec=GetComputerMiliSec();
	for(ListPhasePageLayer *a=CapturedList.GetFirst();a!=NULL;a=a->GetNext()){
		DataInPage	*P=LBase->GetPageDataPhase(a->Phase)->GetPageData(a->Page);
		DataInLayer	*L=P->GetLayerData(a->Layer);
		L->StoringFinishTargetBuff();
	}
	LBase->ExecuteFilteringTarget();
	FilteringMilisec=GetComputerMiliSec()-FilteringMilisec;
	LBase->UnlockTarget();

	if(IsLocalCamera()==true){
		SeqParam->DoneCapture=true;
	}
	CaptureGetTargetImageCounter++;
	return(true);
}


void	ExecuteInspectFast::GoInspect(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspect);
}
void	ExecuteInspectFast::GoInspectWithoutCapture(void)
{
	ClearHaltMode();
	SetMode(_CaptureInspectWithoutCapture);
}
void	ExecuteInspectFast::GoMasterCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyMaster);
}
void	ExecuteInspectFast::GoTargetCaptureOnly(void)
{
	ClearHaltMode();
	SetMode(_CaptureOnlyTarget);
}
void	ExecuteInspectFast::GoGray(void)
{
	ClearHaltMode();
	SetMode(_CaptureGray);
}

void	ExecuteInspectFast::ExecuteHalt(void)
{
	LayersBase	*LBase=GetLayersBase();
	LBase->ClearCurrentStrategicNumberForCalc();
	LBase->SetCurrentStrategicNumber(0);
	LBase->SetCurrentStrategicNumberForSeq(0);

	LBase->ClearTopInCapturedPageLayer();
	LBase->ClearCurrentStrategicNumberForCalc();
	LBase->PopCurrentStrategicNumberForCalc();
	GoHalt();
}


void	ExecuteInspectFast::CamShowSetting(int CamNo)
{
	if(Cam[CamNo]->ShowSetting(GetLayersBase()->GetMainWidget())==true){
		SaveDefault();
	}
}

void	ExecuteInspectFast::Exit(GUIFormBase *)
{
	if(GetLayersBase()->GetResultDLLBase()!=NULL)
		GetLayersBase()->GetResultDLLBase()->Release();
}

int		ExecuteInspectFast::GetAllocatedCameraCount(void)
{
	return min(GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID),AllocatedCamNumb);
}
bool	ExecuteInspectFast::LoadCameraSetting(QIODevice *f)
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

void	ExecuteInspectFast::ClearCameraBuffer(void)
{
	if(IsLocalCamera()==true){
		for(int i=0;i<AllocatedCamNumb;i++){
			Cam[i]->ClearBuffer();
		}
	}
}
bool	ExecuteInspectFast::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	AllocatedPage=newPageNumb;

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
	if(AllocatedCamNumb==1){
		for(int page=0;page<newPageNumb;page++){
			GetParamGlobal()->SetCameraNo(page,0);
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

void ExecuteInspectFast::OccurCamError(int CamStatus)
{
	QString	Msg;
	if((CamStatus & BitCamErrorOverRun)!=0){
		Msg = "OverRun error in Camera";
	}
	else if((CamStatus & BitCamErrorElse)!=0){
		Msg = "Something error in Camera";
	}
	else if((CamStatus & BitLineInvalid)!=0) {
		Msg = "Line invalid in Camera";
	}
	GetLayersBase()->SendErrorToMaster(1 , Msg ,ErrorCodeList::_Critical);
	//emit	SignalOccurError(CamStatus);
}

void	ExecuteInspectFast::SlotOccurError(int CamStatus)
{
	if((CamStatus & BitLineInvalid)!=0) {
		GUIFormBase* F=GetLayersBase()->GetMainWidget();
		if(F!=NULL) {
			QPalette	P=F->palette();
			P.setColor(QPalette::Window, Qt::red);
			F->setPalette(P);
		}
	}
}

static	DWORD		C,Cn;
static	volatile	DWORD	ExecTimeDim[100];
static	volatile	int		ExecTimeDimCount = 0;
static	int			CalcCount	=0;

void ExecuteInspectFast::run()
{
	IntList	TestStrategy;
	int		DbgCounter=0;
	DWORD	TimeInThisPoint;
	SeqParam->CaptureStartCounter=0;
	ThreadOutputResultInst.StartThreadMode(false);
IdleTurn:;
	for(;;){
		LayersBase	*Layer=GetLayersBase();
		ParamGlobal	*ParamG	=GetParamGlobal();
		
		PushOnIdle();
		if(GetPermitToRun()==true){
			C=GetComputerMiliSec();

			SeqParam->InspactionStatus=0;
			if(GetAutoRepeat()==_AutoCaptureInspect){
 				Layer->SetStartInspectTime(XDateTime::currentDateTime());
				Layer->SetInspectionTimeMilisec(GetComputerMiliSec());

				SeqParam->InspactionStatus=33;
				SeqParam->CaptureMode=3;
				CurrentState=_EI_Prepare;

				if(GetParamComm()->Mastered==true){
					Layer->SetCurrentStrategicNumber(Layer->GetCurrentStrategicNumberForSeq());
					ResultInspection	*Res=Layer->GetNextResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());
						ResultInspectionToAccessInSlotAutomodeStart=Res;
						GoSlotAutomodeStart=true;
					}
				}
				if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				SetMode (ExecuteInspectBase::_CaptureInspect);
			}
			else
			if(GetAutoRepeat()==_AutoCaptureOnlyTarget){
 				Layer->SetStartInspectTime(XDateTime::currentDateTime());
				Layer->SetInspectionTimeMilisec(GetComputerMiliSec());

				SeqParam->InspactionStatus=33;
				SeqParam->CaptureMode=4;
				CurrentState=_EI_Prepare;

				if(GetParamComm()->Mastered==true){
					Layer->SetCurrentStrategicNumber(Layer->GetCurrentStrategicNumberForSeq());
					ResultInspection	*Res=Layer->GetNextResultForCalc();
					if(Res!=NULL){
						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());
						ResultInspectionToAccessInSlotAutomodeStart=Res;
						GoSlotAutomodeStart=true;
					}
				}
				if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				SetMode (ExecuteInspectBase::_CaptureOnlyTarget);
			}
			Cn=GetComputerMiliSec();

			MotionMode	CurrentModeN=GetMode();
			if(CurrentModeN==_CaptureInspect){
				Layer->GetLogCreater()->PutLog(__LINE__,"XExecuteInspectFast:Enter");

				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(Layer->GetCurrentStrategicNumber() ,false);
				
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspactionStatus=33;
					SeqParam->CaptureMode=3;
					CurrentState=_EI_Prepare;
					if(TriggeredCapture==false || ParamG->CaptureInBackground==false){
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
							if(Layer->GetOnTerminating()==true){
								//CamRelease();
								return;
							}
						}
						DWORD	t2=GetComputerMiliSec()-t1;
						t2++;
					}
				}
				
				SeqParam->StartInspection=true;
				TrunStarted++;

				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || ParamG->CaptureInBackground==false){
					TrunStartStarted1++;
					CaptureStart();
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspectionID=Layer->GetCurrentInspectIDForExecute();
					SeqParam->ReadyForScan=true;
				}



				CurrentState=_EI_OnCapturing;
				DWORD	StartWaitingPoint=::GetComputerMiliSec();
				int	CamStatus;
				if(CurrentModeN==_CaptureInspect){
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
						if((CamStatus & BitLineInvalid)!=0) {
							OccurCamError(CamStatus);
						}
						msleep(ExeSleepTimeMilisec);
 						if(Layer->GetOnTerminating()==true){
							//CamRelease();
							return;
						}
					}
				}
				Layer->SetStartInspectTime(XDateTime::currentDateTime());

				ExecTimeDim[ExecTimeDimCount]=::GetComputerMiliSec()-StartWaitingPoint;
				ExecTimeDimCount++;
				if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
					ExecTimeDimCount=0;
				}

				TimeInThisPoint=::GetComputerMiliSec();
				Layer->LockForLoadSave();
				DWORD	WaitingMilisec=TimeInThisPoint-StartWaitingPoint;

				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					TriggeredCapture=false;
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					Layer->UnlockForLoadSave();
					goto	IdleTurn;
				}
			
				if(GetEntryPoint()->IsMasterPC()==true){
					//SetCaptured(Layer->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					//EmitSignalCaptured(Layer->GetCurrentStrategicNumber());
				}

				TrunCaptured++;
				if(TrunCaptured==16){
					TrunCaptured=0;
				}
				CurrentState=_EI_OnCalc;
				TriggeredCapture=false;
				if(ParamG->CaptureInBackground==true && Layer->GetOnTerminating()==false){
					if(ParamG->WaitMilisecAfterScan==0){
						if(GetAutoRepeat()==_AutoCaptureInspect
						|| ParamG->GetMaxScanStrategy()>(Layer->GetCurrentStrategicNumberForCalc()+2)
						|| (IsLocalCamera()==true && ParamG->UnconditionalCaptureBackground==true)
						|| (ParamG->GetMaxScanStrategy()<=1 && GetEntryPoint()->IsMasterPC()==false)){
							TriggeredCapture=true;
							TrunStartStarted2++;
							CapturePrepare();
							CaptureStart();
						}
					}
				}

			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«

					IntList PhaseCodes;
					Layer->GetCurrentPhaseFromScanPhase(PhaseCodes);
					int	CPhase=PhaseCodes[0];
					Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:Captured",CPhase);

					SeqParam->InspactionStatus=34;
					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						Layer->UnlockForLoadSave();
						return;
					}

					ListPhasePageLayerPack CapturedList;
					if(GetCurrentCaptureSource()==_Target)
						CaptureGetTargetImage(CapturedList);
					else if(GetCurrentCaptureSource()==_Master){
						int	CStrategic=Layer->GetCurrentStrategicNumber();
						CaptureGetMasterImage(CStrategic,CapturedList);
					}
					SeqParam->PermitCapture=false;

					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					int	NextCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					if(ParamG->AutoIncrementScanPhaseNumber==true){
						if(ParamG->GetMaxScanStrategy()<=1){
							NextCurrentScanPhaseNumber++;
							if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
								NextCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((Layer->GetCurrentStrategicNumber()+1)>=ParamG->GetMaxScanStrategy()){
								NextCurrentScanPhaseNumber++;
								if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
									NextCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					Layer->SetStartInspectionTimeMilisec(GetComputerMiliSec());
					SeqParam->InspactionStatus=35;
									
					int	CStrNumber=Layer->GetCurrentStrategicNumber();
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(ParamG->GetMaxScanStrategy()<=1 
					|| ParamG->GetMaxScanStrategy()<=(Layer->GetCurrentStrategicNumberForCalc()+1)){
						Layer->SetLatchedInspectionNumber(Layer->GetInspectionNumber());
					}
					GUIInitializer	*Gn=Layer->GetGuiInitializer();
					if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
						Layer->ExecuteStartByInspection();
						if(Gn!=NULL){
							Gn->ExecuteStartByInspection();
						}
					}
					if(Layer->IsEnableProcess()==true){
						ResultInspection	*Res=Layer->GetCurrentResultForCalc();
						if(Res!=NULL){
							Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

							ThreadOutputResultInst.SetStart(Res,GetComputerMiliSec()-TimeInThisPoint);
							Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:StartCalc",Res->GetInspectionID());

							Layer->PopCurrentStrategicNumberForCalc();

							C=TimeInThisPoint;
							DWORD	ProcessStartTime=C;
							if(ParamG->UseExecuteCaptured==true){
								Layer->ExecuteCaptured(CapturedList);
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteCaptured=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteCaptured");

							Layer->ExecutePreAlignment	();
							if(Gn!=NULL){
								Gn->ExecutePreAlignment();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePreAlignment");

							Layer->ExecuteAlignment		();
							if(Gn!=NULL){
								Gn->ExecuteAlignment();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteAlignment=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteAlignment");


							Layer->ExecutePreProcessing	();
							if(Gn!=NULL){
								Gn->ExecutePreProcessing();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreProcessing=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePreProcessing");


							Layer->ExecuteProcessing		();
							if(Gn!=NULL){
								Gn->ExecuteProcessing();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessing=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteProcessing");


							Layer->ExecuteProcessingRevived();
							if(Gn!=NULL){
								Gn->ExecuteProcessingRevived();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecuteProcessingRevived");


							//ŒŸ¸Š®—¹Žž
							Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

							Layer->ExecutePostProcessing();
							if(Gn!=NULL){
								Gn->ExecutePostProcessing();
							}
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePostProcessing=Cn-C;
							Res->ExecTime.TM_TotalProcessMilisec=Cn-ProcessStartTime;
							C=Cn;
							Layer->GetLogCreater()->PutLog(__LINE__,"ExecutePostProcessing");

							DWORD	CalcTotalMilisec=::GetComputerMiliSec()-TimeInThisPoint;

							TestStrategy.Add(CStrNumber);
							if(TestStrategy.GetCount()==8){
								DbgCounter++;
							}
							EmitCalcDone(*Res,tCurrentScanPhaseNumber,CStrNumber);
							if(Gn!=NULL){
								Gn->ExecuteFinished();
							}
							Layer->GetLogCreater()->PutLog(__LINE__,"EmitCalcDone");

							Layer->SetCurrentScanPhaseNumber(NextCurrentScanPhaseNumber);
							Layer->SetCurrentStrategicNumberInExe(Layer->GetCurrentStrategicNumberInExe()+1);

							DWORD	CalcTotalMilisec2=::GetComputerMiliSec()-TimeInThisPoint;
							//
							//ExecTimeDim[ExecTimeDimCount]=CalcTotalMilisec2;	//::GetComputerMiliSec()-StartCalcTime;
							//ExecTimeDimCount++;
							//if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
							//	ExecTimeDimCount=0;
							//}
							CurrentState=_EI_IDLE;
				
							if(ParamG->CaptureInBackground==true){
								if(ParamG->WaitMilisecAfterScan!=0){
									TrunStartStarted3++;
									CapturePrepare();
									CaptureStart();
								}
							}

							if(ParamG->GetMaxScanStrategy()>1){
								if(ParamG->GetMaxScanStrategy()>(CStrNumber+1)){
									Layer->IncreaseCurrentStrategicNumber();
									Layer->SetCurrentStrategicNumberForSeq(CStrNumber+1);
								}
								else{
									Layer->IncreaseCurrentStrategicNumber();
									Layer->SetCurrentStrategicNumberForSeq(0);
								}
							}
							Layer->GetLogCreater()->PutLog(__LINE__,"EndLoop");
						}
					}
				}
				Layer->UnlockForLoadSave();
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
			else
			if(CurrentModeN==_CaptureInspectWithoutCapture){
				Layer->GetLogCreater()->PutLog(__LINE__,"XExecuteInspectFast:Enter");

				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(Layer->GetCurrentStrategicNumber() ,false);
				
				CurrentState=_EI_StartCamera;
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				CurrentState=_EI_OnCapturing;

				DWORD	StartWaitingPoint=::GetComputerMiliSec();
				DWORD	TimeInThisPoint	 =::GetComputerMiliSec();
				DWORD	WaitingMilisec=TimeInThisPoint-StartWaitingPoint;
			
				if(GetEntryPoint()->IsMasterPC()==true){
					//SetCaptured(Layer->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					//EmitSignalCaptured(Layer->GetCurrentStrategicNumber());
				}
				Layer->SetStartInspectTime(XDateTime::currentDateTime());

				CurrentState=_EI_OnCalc;
			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					IntList PhaseCodes;
					Layer->GetCurrentPhaseFromScanPhase(PhaseCodes);
					int	CPhase=PhaseCodes[0];
					Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:Captured",CPhase);

					SeqParam->InspactionStatus=34;
					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
					
					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					int	NextCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					if(ParamG->AutoIncrementScanPhaseNumber==true){
						if(ParamG->GetMaxScanStrategy()<=1){
							NextCurrentScanPhaseNumber++;
							if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
								NextCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((Layer->GetCurrentStrategicNumber()+1)>=ParamG->GetMaxScanStrategy()){
								NextCurrentScanPhaseNumber++;
								if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
									NextCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					Layer->LockForLoadSave();

					Layer->SetStartInspectionTimeMilisec(GetComputerMiliSec());
					SeqParam->InspactionStatus=35;
									
					int	CStrNumber=Layer->GetCurrentStrategicNumber();
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(ParamG->GetMaxScanStrategy()<=1 
					|| ParamG->GetMaxScanStrategy()<=(Layer->GetCurrentStrategicNumberForCalc()+1)){
						Layer->SetLatchedInspectionNumber(Layer->GetInspectionNumber());
					}
					if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
						Layer->ExecuteStartByInspection();
					}

					if(Layer->IsEnableProcess()==true){
						ResultInspection	*Res=Layer->GetCurrentResultForCalc();
						if(Res!=NULL){
							Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

							ThreadOutputResultInst.SetStart(Res,GetComputerMiliSec()-TimeInThisPoint);
							Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:StartCalc",Res->GetInspectionID());

							Layer->PopCurrentStrategicNumberForCalc();

							C=GetComputerMiliSec();
							DWORD	ProcessStartTime=C;
							Layer->ExecutePreAlignment	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
							C=Cn;

							Layer->ExecuteAlignment		();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteAlignment=Cn-C;
							C=Cn;

							Layer->ExecutePreProcessing	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePreProcessing=Cn-C;
							C=Cn;

							Layer->ExecuteProcessing		();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessing=Cn-C;
							C=Cn;

							Layer->ExecuteProcessingRevived();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
							C=Cn;

							//ŒŸ¸Š®—¹Žž
							Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

							Layer->ExecutePostProcessing	();
							Cn=GetComputerMiliSec();
							Res->ExecTime.TM_ExecutePostProcessing=Cn-C;
							Res->ExecTime.TM_TotalProcessMilisec=Cn-ProcessStartTime;
							C=Cn;

							DWORD	CalcTotalMilisec=::GetComputerMiliSec()-TimeInThisPoint;
							EmitCalcDone(*Res,tCurrentScanPhaseNumber,CStrNumber);

							Layer->SetCurrentScanPhaseNumber(NextCurrentScanPhaseNumber);
							Layer->SetCurrentStrategicNumberInExe(Layer->GetCurrentStrategicNumberInExe()+1);
							DWORD	CalcTotalMilisec2=::GetComputerMiliSec()-TimeInThisPoint;

							ExecTimeDim[ExecTimeDimCount]=::GetComputerMiliSec()-StartCalcTime;
							ExecTimeDimCount++;
							if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
								ExecTimeDimCount=0;
							}
							CurrentState=_EI_IDLE;
				
							if(ParamG->CaptureInBackground==true){
								if(ParamG->WaitMilisecAfterScan!=0){
									TrunStartStarted3++;
									CapturePrepare();
									CaptureStart();
								}
							}

							if(ParamG->GetMaxScanStrategy()>1){
								if(ParamG->GetMaxScanStrategy()>(CStrNumber+1)){
									Layer->IncreaseCurrentStrategicNumber();
									Layer->SetCurrentStrategicNumberForSeq(CStrNumber+1);
								}
								else{
									Layer->IncreaseCurrentStrategicNumber();
									Layer->SetCurrentStrategicNumberForSeq(0);
								}
							}
						}
					}
					Layer->UnlockForLoadSave();
				}
				SeqParam->StartInspection=false;
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}

			else
			if(CurrentModeN==_CaptureOnlyTarget){
				Layer->GetLogCreater()->PutLog(__LINE__,"XExecuteInspectFast:Enter");

				SetCurrentTypeOfCapture(ExecuteInspectBase::_Target);
				SetScanInfo(Layer->GetCurrentStrategicNumber() ,false);
				
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspactionStatus=33;
					SeqParam->CaptureMode=1;
					CurrentState=_EI_Prepare;
					if(TriggeredCapture==false || ParamG->CaptureInBackground==false){
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
							if(Layer->GetOnTerminating()==true){
								//CamRelease();
								return;
							}
						}
						DWORD	t2=GetComputerMiliSec()-t1;
						t2++;
					}
				}
				
				SeqParam->StartInspection=true;
				TrunStarted++;

				CurrentState=_EI_StartCamera;
				if(TriggeredCapture==false || ParamG->CaptureInBackground==false){
					TrunStartStarted1++;
					CaptureStart();
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					Layer->ExecuteStartByInspection();
					Layer->ExecuteFilterBeforeScan();
				}
				if(GetAutoRepeat()!=_AutoCaptureInspect){
					SeqParam->InspectionID=Layer->GetCurrentInspectIDForExecute();
					SeqParam->ReadyForScan=true;
				}
				CurrentState=_EI_OnCapturing;
				DWORD	StartWaitingPoint=::GetComputerMiliSec();
				int	CamStatus;
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
 					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
				}
				
				DWORD	TimeInThisPoint=::GetComputerMiliSec();
				DWORD	WaitingMilisec=TimeInThisPoint-StartWaitingPoint;

				if(GetHaltMode()==true){
					emit	SignalCaptureHalt();
					ClearHaltMode();
					ExecuteHalt();
					TriggeredCapture=false;
					CurrentState=_EI_IDLE;
					SetMode(_CaptureNone);
					goto	IdleTurn;
				}
		
				if(GetEntryPoint()->IsMasterPC()==true){
					//SetCaptured(Layer->GetCurrentStrategicNumber());
				}
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					//EmitSignalCaptured(Layer->GetCurrentStrategicNumber());
				}

				TrunCaptured++;
				CurrentState=_EI_OnCalc;
				TriggeredCapture=false;
				if(ParamG->CaptureInBackground==true && Layer->GetOnTerminating()==false){
					if(ParamG->WaitMilisecAfterScan==0){
						if(GetAutoRepeat()==_AutoCaptureInspect
						|| ParamG->GetMaxScanStrategy()>(Layer->GetCurrentStrategicNumberForCalc()+2)
						|| (IsLocalCamera()==true && ParamG->UnconditionalCaptureBackground==true)
						|| (ParamG->GetMaxScanStrategy()<=1 && GetEntryPoint()->IsMasterPC()==false)){
							TriggeredCapture=true;
							TrunStartStarted2++;
							CapturePrepare();
							CaptureStart();
						}
					}
				}
			
				if(IsLocalCamera()==true){	//SLAVE‚Ì‚Æ‚«
					IntList PhaseCodes;
					Layer->GetCurrentPhaseFromScanPhase(PhaseCodes);
					int	CPhase=PhaseCodes[0];
					Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:Captured",CPhase);

					SeqParam->InspactionStatus=34;
					if(Layer->GetOnTerminating()==true){
						//CamRelease();
						return;
					}
					ListPhasePageLayerPack CapturedList;
					if(GetCurrentCaptureSource()==_Target){
						CaptureGetTargetImage(CapturedList);
						EmitSignalTargetImageCaptured();
					}
					else if(GetCurrentCaptureSource()==_Master){
						int	CStrategic=Layer->GetCurrentStrategicNumber();
						CaptureGetMasterImage(CStrategic,CapturedList);
						EmitSignalMasterImageCaptured();
					}
					SeqParam->PermitCapture=false;
					FuncContainerInCaptureInspect.ExecuteFunc();

					int	tCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					int	NextCurrentScanPhaseNumber=Layer->GetCurrentScanPhaseNumber();
					if(ParamG->AutoIncrementScanPhaseNumber==true){
						if(ParamG->GetMaxScanStrategy()<=1){
							NextCurrentScanPhaseNumber++;
							if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
								NextCurrentScanPhaseNumber=0;
							}
						}
						else{
							if((Layer->GetCurrentStrategicNumber()+1)>=ParamG->GetMaxScanStrategy()){
								NextCurrentScanPhaseNumber++;
								if(NextCurrentScanPhaseNumber>=Layer->GetPhaseNumb()){
									NextCurrentScanPhaseNumber=0;
								}
							}
						}
					}
					Layer->SetStartInspectionTimeMilisec(GetComputerMiliSec());
					SeqParam->InspactionStatus=35;
									
					int	CStrNumber=Layer->GetCurrentStrategicNumber();
					DWORD	StartCalcTime=GetComputerMiliSec();
					if(ParamG->GetMaxScanStrategy()<=1 
					|| ParamG->GetMaxScanStrategy()<=(Layer->GetCurrentStrategicNumberForCalc()+1)){
						Layer->SetLatchedInspectionNumber(Layer->GetInspectionNumber());
					}
					if(GetParamComm()->Mastered==true && GetAutoRepeat()==_AutoCaptureInspect){
						Layer->ExecuteStartByInspection();
					}
					ResultInspection	*Res=Layer->GetCurrentResultForCalc();
					if(Res!=NULL){
						Layer->GetLogCreater()->PutLogA1(__LINE__,"XExecuteInspectFast:StartCalc",Res->GetInspectionID());

						Layer->PopCurrentStrategicNumberForCalc();

						C=GetComputerMiliSec();
						Layer->ExecutePreAlignment	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreAlignment=Cn-C;
						C=Cn;

						Layer->ExecuteAlignment		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteAlignment=Cn-C;
						C=Cn;

						Layer->ExecutePreScanning	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePreScanning=Cn-C;
						C=Cn;

						Layer->ExecuteScanning		();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecuteScanning=Cn-C;
						C=Cn;

						Res->SetStartTimeForInspect(Layer->GetStartInspectTime());

						Layer->ExecutePostScanning	();
						Cn=GetComputerMiliSec();
						Res->ExecTime.TM_ExecutePostScanning=Cn-C;
						C=Cn;

						DWORD	CalcTotalMilisec=::GetComputerMiliSec()-TimeInThisPoint;
						EmitScanDone(*Res,tCurrentScanPhaseNumber,CStrNumber);
											
						Layer->SetCurrentScanPhaseNumber(NextCurrentScanPhaseNumber);
						DWORD	CalcTotalMilisec2=::GetComputerMiliSec()-TimeInThisPoint;

						ExecTimeDim[ExecTimeDimCount]=::GetComputerMiliSec()-StartCalcTime;
						ExecTimeDimCount++;
						if(ExecTimeDimCount>sizeof(ExecTimeDim)/sizeof(ExecTimeDim[0])){
							ExecTimeDimCount=0;
						}
						CurrentState=_EI_IDLE;
				
						if(ParamG->CaptureInBackground==true){
							if(ParamG->WaitMilisecAfterScan!=0){
								TrunStartStarted3++;
								CapturePrepare();
								CaptureStart();
							}
						}

						if(ParamG->GetMaxScanStrategy()>1){
							if(ParamG->GetMaxScanStrategy()>(CStrNumber+1)){
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(CStrNumber+1);
							}
							else{
								Layer->IncreaseCurrentStrategicNumber();
								Layer->SetCurrentStrategicNumberForSeq(0);
							}
						}
					}
				}
				CurrentState=_EI_IDLE;
				SetMode(_CaptureNone);
			}
		}
		if(GetEntryPoint()->NoCamDevice==false){
			//CheckCamera(CameraErrorCode);
		}
		//msleep(ExeSleepTimeMilisec);
		if(Layer->GetOnTerminating()==true){
			//CamRelease();
			return;
		}
		if(GetHaltMode()==true){
			ExecuteHalt();
			emit	SignalCaptureHalt();
			ClearHaltMode();
			msleep(100);
		}
		msleep(3);
	}
}

void	ExecuteInspectFast::EmitCalcDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber)
{
	IntList	PhaseCodes;
	LayersBase	*LBase=GetLayersBase();
	ParamGlobal	*ParamG	=GetParamGlobal();

	LBase->GetPhaseFromScanPhase(tCurrentScanPhaseNumber,PhaseCodes);
	for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
		Res.SetCalcDone(c->GetValue());
	}

	if(ParamG->ModePhaseOutputResult==-4 ){
		DataInExecuter	*Re=LBase->GetExecuter(&Res);
		NGCounts		=Res.GetNGCount();
		TimeOutBreak	=Res.GetTimeOutBreak();
		MaxErrorBreak	=Res.GetMaxErrorBreak();
		ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
		
		if(LBase->GetCurrentStrategicNumber()>=(ParamG->GetMaxScanStrategy()-1)
		&& LBase->GetCurrentPhase()>=(LBase->GetPhaseNumb()-1)){
			IntList PageList;
			ParamG->GetStrategyPage(nStrategicNumber,PageList);
			for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
				int	page=s->GetValue();
				EPBase->FinishCapture(page);
				Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
			}
			FinishInspection(&Res,nStrategicNumber);
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				EPBase->FinishCapture(page);
				Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
			}
			PreFinishInspection(&Res,nStrategicNumber);
		}
	}
	else
	if(ParamG->ModePhaseOutputResult==-3 || GetPhaseNumb()<=1){
		if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
			DataInExecuter	*Re=LBase->GetExecuter(&Res);
			NGCounts		=Res.GetNGCount();
			TimeOutBreak	=Res.GetTimeOutBreak();
			MaxErrorBreak	=Res.GetMaxErrorBreak();
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
			
			if(ParamG->GetMaxScanStrategy()>1){
				IntList PageList;
				ParamG->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=LBase->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=LBase->GetExecuter(Res);
				NGCounts		=Res->GetNGCount();
				TimeOutBreak	=Res->GetTimeOutBreak();
				MaxErrorBreak	=Res->GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishInspection(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult==-2){
		if(Res.IsAllCalcDone()==true){
			if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
				DataInExecuter	*Re=LBase->GetExecuter(&Res);
				NGCounts		=Res.GetNGCount();
				TimeOutBreak	=Res.GetTimeOutBreak();
				MaxErrorBreak	=Res.GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=LBase->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=LBase->GetExecuter(Res);
					NGCounts		=Res->GetNGCount();
					TimeOutBreak	=Res->GetTimeOutBreak();
					MaxErrorBreak	=Res->GetMaxErrorBreak();
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(ParamG->GetMaxScanStrategy()>1){
						IntList PageList;
						ParamG->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult==-1){
		if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
			DataInExecuter	*Re=LBase->GetExecuter(&Res);
			NGCounts		=Res.GetNGCount();
			TimeOutBreak	=Res.GetTimeOutBreak();
			MaxErrorBreak	=Res.GetMaxErrorBreak();
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

			if(ParamG->GetMaxScanStrategy()>1){
				IntList PageList;
				ParamG->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishInspection(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=LBase->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=LBase->GetExecuter(Res);
				NGCounts		=Res->GetNGCount();
				TimeOutBreak	=Res->GetTimeOutBreak();
				MaxErrorBreak	=Res->GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					//PreFinishInspection(Res,nStrategicNumber);
					FinishInspection(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					//PreFinishInspection(Res,nStrategicNumber);
					FinishInspection(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult>=0){
		int	phase=ParamG->ModePhaseOutputResult;
		if(Res.IsCalcDone(phase)==true){
			if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
				DataInExecuter	*Re=LBase->GetExecuter(&Res);
				NGCounts		=Res.GetNGCount();
				TimeOutBreak	=Res.GetTimeOutBreak();
				MaxErrorBreak	=Res.GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishInspection(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=LBase->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=LBase->GetExecuter(Res);
					NGCounts		=Res->GetNGCount();
					TimeOutBreak	=Res->GetTimeOutBreak();
					MaxErrorBreak	=Res->GetMaxErrorBreak();
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(ParamG->GetMaxScanStrategy()>1){
						IntList PageList;
						ParamG->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishInspection(Res,nStrategicNumber);
					}
				}
			}
		}
	}
}

void	ExecuteInspectFast::EmitScanDone(ResultInspection &Res,int tCurrentScanPhaseNumber ,int32 nStrategicNumber)
{
	IntList	PhaseCodes;
	LayersBase	*LBase	=GetLayersBase();
	ParamGlobal	*ParamG	=GetParamGlobal();

	LBase->GetPhaseFromScanPhase(tCurrentScanPhaseNumber,PhaseCodes);
	for(IntClass *c=PhaseCodes.GetFirst();c!=NULL;c=c->GetNext()){
		Res.SetCalcDone(c->GetValue());
	}

	if(ParamG->ModePhaseOutputResult==-3 || GetPhaseNumb()<=1){
		if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
			DataInExecuter	*Re=LBase->GetExecuter(&Res);
			NGCounts		=Res.GetNGCount();
			TimeOutBreak	=Res.GetTimeOutBreak();
			MaxErrorBreak	=Res.GetMaxErrorBreak();
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
			
			if(ParamG->GetMaxScanStrategy()>1){
				IntList PageList;
				ParamG->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishScanning(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishScanning(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=LBase->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=LBase->GetExecuter(Res);
				NGCounts		=Res->GetNGCount();
				TimeOutBreak	=Res->GetTimeOutBreak();
				MaxErrorBreak	=Res->GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishScanning(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishScanning(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult==-2){
		if(Res.IsAllCalcDone()==true){
			if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
				DataInExecuter	*Re=LBase->GetExecuter(&Res);
				NGCounts		=Res.GetNGCount();
				TimeOutBreak	=Res.GetTimeOutBreak();
				MaxErrorBreak	=Res.GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishScanning(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishScanning(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=LBase->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=LBase->GetExecuter(Res);
					NGCounts		=Res->GetNGCount();
					TimeOutBreak	=Res->GetTimeOutBreak();
					MaxErrorBreak	=Res->GetMaxErrorBreak();
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(ParamG->GetMaxScanStrategy()>1){
						IntList PageList;
						ParamG->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishScanning(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishScanning(Res,nStrategicNumber);
					}
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult==-1){
		if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
			DataInExecuter	*Re=LBase->GetExecuter(&Res);
			NGCounts		=Res.GetNGCount();
			TimeOutBreak	=Res.GetTimeOutBreak();
			MaxErrorBreak	=Res.GetMaxErrorBreak();
			ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

			if(ParamG->GetMaxScanStrategy()>1){
				IntList PageList;
				ParamG->GetStrategyPage(nStrategicNumber,PageList);
				for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
					int	page=s->GetValue();
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishScanning(&Res,nStrategicNumber);
			}
			else{
				for(int page=0;page<GetPageNumb();page++){
					EPBase->FinishCapture(page);
					Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
				}
				FinishScanning(&Res,nStrategicNumber);
			}
		}
		else{
			ResultInspection	*Res=LBase->GetCurrentResultForCalc();
			if(Res!=NULL){
				DataInExecuter	*Re=LBase->GetExecuter(Res);
				NGCounts		=Res->GetNGCount();
				TimeOutBreak	=Res->GetTimeOutBreak();
				MaxErrorBreak	=Res->GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishScanning(Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					PreFinishScanning(Res,nStrategicNumber);
				}
			}
		}
	}
	else
	if(ParamG->ModePhaseOutputResult>=0){
		int	phase=ParamG->ModePhaseOutputResult;
		if(Res.IsCalcDone(phase)==true){
			if(tCurrentScanPhaseNumber>=ParamG->GetScanPhaseCount()-1){
				DataInExecuter	*Re=LBase->GetExecuter(&Res);
				NGCounts		=Res.GetNGCount();
				TimeOutBreak	=Res.GetTimeOutBreak();
				MaxErrorBreak	=Res.GetMaxErrorBreak();
				ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

				if(ParamG->GetMaxScanStrategy()>1){
					IntList PageList;
					ParamG->GetStrategyPage(nStrategicNumber,PageList);
					for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
						int	page=s->GetValue();
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishScanning(&Res,nStrategicNumber);
				}
				else{
					for(int page=0;page<GetPageNumb();page++){
						EPBase->FinishCapture(page);
						Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
					}
					FinishScanning(&Res,nStrategicNumber);
				}
			}
			else{
				ResultInspection	*Res=LBase->GetCurrentResultForCalc();
				if(Res!=NULL){
					DataInExecuter	*Re=LBase->GetExecuter(Res);
					NGCounts		=Res->GetNGCount();
					TimeOutBreak	=Res->GetTimeOutBreak();
					MaxErrorBreak	=Res->GetMaxErrorBreak();
					ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();

					if(ParamG->GetMaxScanStrategy()>1){
						IntList PageList;
						ParamG->GetStrategyPage(nStrategicNumber,PageList);
						for(IntClass *s=PageList.GetFirst();s!=NULL;s=s->GetNext()){
							int	page=s->GetValue();
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishScanning(Res,nStrategicNumber);
					}
					else{
						for(int page=0;page<GetPageNumb();page++){
							EPBase->FinishCapture(page);
							Re->SetResultReceivedFlag(page,NGCounts,TimeOutBreak,MaxErrorBreak);
						}
						PreFinishScanning(Res,nStrategicNumber);
					}
				}
			}
		}
	}
}
void	ExecuteInspectFast::ChangeLot(void)
{
	if(GetMode()==_CaptureInspect || GetMode()==_CaptureInspectWithoutCapture){
		if(IsLocalCamera()==false || GetEntryPoint()->IsMasterPC()==false){
			//GetLayersBase()->ExecuteStartByInspection();
		}
	}
}

static	XDateTime	LastStartTimeForInspection;
static	int			eRepliedCounter=0;
static	int			eOutputCounter=0;

void	ExecuteInspectFast::FinishInspection(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L		=GetLayersBase();
	ParamGlobal	*ParamG	=GetParamGlobal();

	//PacketReplied->Result	=CmdInspectionRepliedBase::_OK;
	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;

	DWORD	MiliSecTable[10];
	DWORD	C=::GetComputerMiliSec();
	DWORD	Cn;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	//EPBase->FinishCapture(localPage);
	//Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	ExecuteInspectFast	*EP=(ExecuteInspectFast *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(ParamG->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(L->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		//ŒŸ¸Š®—¹Žž

		if(ParamG->GetMaxScanStrategy()<=1
		|| (ParamG->BufferedProcessing==false && ParamG->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (ParamG->GetMaxScanStrategy()>1 && ParamG->BufferedProcessing==true)){

			EP->SeqParam->InspectionID=L->GetCurrentInspectIDForExecute();
			EP->SeqParam->NowProcessing	=false;

			Cn=::GetComputerMiliSec();
			MiliSecTable[0]=Cn-C;
			C=Cn;

			bool3 eOK;
			bool eMaxError;
			bool eTimeOver;
			Res->GatherResultInPhase(L->GetCurrentPhase(),eOK ,eMaxError , eTimeOver);

			bool3	ShadowOk;
			bool	ShadowTimeOver;
			bool	ShadowMaxError;
			L->GetShadowResult(Res
							,ShadowOk ,ShadowTimeOver, ShadowMaxError,true,false);

			Cn=::GetComputerMiliSec();
			MiliSecTable[1]=Cn-C;
			C=Cn;

			EP->SeqParam->InspectionResultSub=0;
			ResultPkNgPacket	ResultPacket(L);
			if(eTimeOver==true || ShadowTimeOver==true){
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				if(eMaxError==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
					EP->SeqParam->InspectionResultSub=5;
				}
				else{
					Res->SetMaxErrorBreak(false);
					EP->SeqParam->InspectionResultSub=3;
				}
			}
			else{
				Res->SetTimeOutBreak(false);
				if(eMaxError==true || ShadowMaxError==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
					EP->SeqParam->InspectionResultSub=4;
				}
				else{
					Res->SetMaxErrorBreak(false);
					EP->SeqParam->InspectionResultSub=3;
				}
			}

			int	ResultCode=0;
			if(eOK==true3 && ShadowOk==true3){
				EP->SeqParam->InspectionResultSub=1;
				EP->SeqParam->InspectionResult=1;
				EP->SeqParam->InspectionFinalResult	=1;
				ResultCode=1;
				ResultPacket.Ok=true3;
				ThreadOutputResultInst.SetOutput(-1,ResultPacket);

				Res->SetOutputCode(1);
			}
			else{
				if(EP->SeqParam->InspectionResultSub==0)
					EP->SeqParam->InspectionResultSub=2;
				EP->SeqParam->InspectionResult=2;
				EP->SeqParam->InspectionFinalResult	=2;
				ResultCode=2;
				ResultPacket.Ok=false3;
				ThreadOutputResultInst.SetOutput(-1,ResultPacket);

				Res->SetOutputCode(2);
			}
			
			Cn=::GetComputerMiliSec();
			MiliSecTable[2]=Cn-C;
			C=Cn;

			ResultInspection	*eRes=L->GetCurrentResultForCalc();
			if(eRes!=NULL){
				DataInExecuter	*eRe=L->GetExecuter(eRes);
				if(eRe!=Re){
					eRe->CopyResultCountFrom(*Re);
				}
				DWORD InspectionTimeMilisec=GetComputerMiliSec() - L->GetStartInspectionTimeMilisec();
				L->SetInspectionTimeMilisec(InspectionTimeMilisec);
				L->SetEndInspectionTime(XDateTime::currentDateTime());
				L->GetResultHistryData()->AddHistry(ResultCode
													,Res->GetStartTimeForInspection()
													,L->GetCurrentInspectIDForExecute()
													,Res->GetIDStr()
													,((Re->IsResultTimeOut()==true) || (Res->GetTimeOutBreak()==true))?true:false
													,((Re->IsResultMaxError()==true) || (Res->GetMaxErrorBreak()==true))?true:false
													,Res->ExecTime.TM_TotalProcessMilisec);
			
				Res->SetInspectionID(L->GetCurrentInspectIDForExecute());

				Cn=::GetComputerMiliSec();
				MiliSecTable[3]=Cn-C;
				C=Cn;

				L->ShowShadowHistory(ResultCode, InspectionTimeMilisec,true,false);

				Cn=::GetComputerMiliSec();
				MiliSecTable[4]=Cn-C;
				C=Cn;
			}
			if(EP->SeqParam->NotOutputResult==false){
				Re->PutCurrentResult();
			}

			Cn=::GetComputerMiliSec();
			MiliSecTable[5]=Cn-C;
			C=Cn;

			L->IncrementInspectID();
			
			L->CloseProcessingForm();
			EP->SeqParam->AllFinishInProcess=false;
			if(ParamG->ReDrawByInspection==true){
				int64	tInspectID=L->GetCurrentInspectIDForDisplay();
				emit	SignalRunByEveryInspection(L,tInspectID);

				Cn=::GetComputerMiliSec();
				MiliSecTable[6]=Cn-C;
				C=Cn;

				for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
					emit	SignalRunByEveryInspection(L->Base,tInspectID);
				}
				Cn=::GetComputerMiliSec();
				MiliSecTable[7]=Cn-C;
				C=Cn;

				if(NowOnWorking==false && SignalCounter==0){
					int64	tInspectID=L->GetCurrentInspectIDForDisplay();
					SignalCounter+=1+ShadowLayersBasePointer.GetCount();
					emit	SignalInspectionRefresh(L,tInspectID);

					Cn=::GetComputerMiliSec();
					MiliSecTable[8]=Cn-C;
					C=Cn;

					for(LayersBasePointerList *L=ShadowLayersBasePointer.GetFirst();L!=NULL;L=L->GetNext()){
						emit	SignalInspectionRefresh(L->Base,tInspectID);
					}

					Cn=::GetComputerMiliSec();
					MiliSecTable[9]=Cn-C;
					C=Cn;
				}
			}
		}
		else{
			bool3 eOK;
			bool eMaxError;
			bool eTimeOver;
			Res->GatherResult(eOK ,eMaxError , eTimeOver,true,true);

			if(eOK==true3){
				EP->SeqParam->InspectionResult=1;
				Res->SetOutputCode(1);
			}
			else{
				EP->SeqParam->InspectionResult=2;
				Res->SetOutputCode(2);
			}
		}
}

void	ExecuteInspectFast::PreFinishInspection(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L		=GetLayersBase();
	ParamGlobal	*ParamG	=GetParamGlobal();

	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	ExecuteInspectFast	*EP=(ExecuteInspectFast *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(ParamG->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(L->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		//ŒŸ¸Š®—¹Žž

		if(ParamG->GetMaxScanStrategy()<=1
		|| (ParamG->BufferedProcessing==false && ParamG->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (ParamG->GetMaxScanStrategy()>1 && ParamG->BufferedProcessing==true)){

			EP->SeqParam->InspectionID=L->GetCurrentInspectIDForExecute();
			EP->SeqParam->NowProcessing	=false;

			EP->SeqParam->InspectionResultSub=0;
			ResultPkNgPacket	ResultPacket(L);

			bool3 eOK;
			bool eMaxError;
			bool eTimeOver;
			Res->GatherResult(eOK ,eMaxError , eTimeOver,true,false);

			if(eTimeOver==true){
				Res->SetTimeOutBreak(true);
				ResultPacket.TimeOver=true;
				if(eMaxError==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
					EP->SeqParam->InspectionResultSub=5;
				}
				else{
					Res->SetMaxErrorBreak(false);
					EP->SeqParam->InspectionResultSub=3;
				}
			}
			else{
				Res->SetTimeOutBreak(false);
				if(eMaxError==true){
					ResultPacket.MaxError=true;
					Res->SetMaxErrorBreak(true);
					EP->SeqParam->InspectionResultSub=4;
				}
				else{
					Res->SetMaxErrorBreak(false);
					EP->SeqParam->InspectionResultSub=3;
				}
			}

			if(eOK==true3){
				EP->SeqParam->InspectionResultSub=1;
				EP->SeqParam->InspectionResult=1;
				EP->SeqParam->InspectionFinalResult	=1;
				ResultPacket.Ok=true3;
				ThreadOutputResultInst.SetOutput(-2,ResultPacket);
				//GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(-2,Res,&ResultPacket);

				Res->SetOutputCode(1);
			}
			else{
				if(EP->SeqParam->InspectionResultSub==0)
					EP->SeqParam->InspectionResultSub=2;
				EP->SeqParam->InspectionResult=2;
				EP->SeqParam->InspectionFinalResult	=2;
				ResultPacket.Ok=true3;
				ThreadOutputResultInst.SetOutput(-2,ResultPacket);
				//GetLayersBase()->GetResultDLLBase()->OutputResultDirectly(-2,Res,&ResultPacket);

				Res->SetOutputCode(2);
			}
			ResultInspection	*eRes=L->GetCurrentResultForCalc();
			if(eRes!=NULL){
				DataInExecuter	*eRe=L->GetExecuter(eRes);
				if(eRe!=Re){
					eRe->CopyResultCountFrom(*Re);
				}
				/*
				L->SetInspectionTimeMilisec(GetComputerMiliSec() - L->GetStartInspectionTimeMilisec());
				L->SetEndInspectionTime(XDateTime::currentDateTime());
				L->GetResultHistryData()->AddHistry(EP->SeqParam->InspectionResult
													,Res->GetStartTimeForInspection()
													,L->GetCurrentInspectIDForExecute()
													,Res->GetIDStr()
													,Re->IsResultTimeOut()
													,Re->IsResultMaxError()
													,Res->ExecTime.TM_TotalProcessMilisec);
	
				Res->SetInspectionID(L->GetCurrentInspectIDForExecute());
				*/
			}
			L->CloseProcessingForm();
			EP->SeqParam->AllFinishInProcess=false;
		}
		else{
			bool3 eOK;
			bool eMaxError;
			bool eTimeOver;
			Res->GatherResult(eOK ,eMaxError , eTimeOver,true,true);

			if(eOK==true3){
				EP->SeqParam->InspectionResult=1;
				Res->SetOutputCode(1);
			}
			else{
				EP->SeqParam->InspectionResult=2;
				Res->SetOutputCode(2);
			}
		}
		if(ParamG->ReDrawByInspection==true){
			emit	SignalInspectionOnTheWay(L->GetCurrentInspectIDForDisplay());
		}

}

void	ExecuteInspectFast::FinishScanning(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L=GetLayersBase();
	//PacketReplied->Result	=CmdInspectionRepliedBase::_OK;
	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	//EPBase->FinishCapture(localPage);
	//Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	ExecuteInspectFast	*EP=(ExecuteInspectFast *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(GetParamGlobal()->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(L->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		int	ResultCode=GetParamGlobal()->ResultCodeInScanning;

		if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
		|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){

			EP->SeqParam->InspectionID=L->GetCurrentInspectIDForExecute();
			EP->SeqParam->NowProcessing	=false;
			Res->SetTimeOutBreak(false);
			Res->SetMaxErrorBreak(false);

			EP->SeqParam->InspectionResultSub=ResultCode;
			EP->SeqParam->InspectionResult=ResultCode;
			EP->SeqParam->InspectionFinalResult	=ResultCode;
			Res->SetOutputCode(ResultCode);

			L->SetInspectionTimeMilisec(GetComputerMiliSec() - L->GetStartInspectionTimeMilisec());
			L->SetEndInspectionTime(XDateTime::currentDateTime());
	
			Res->SetInspectionID(L->GetCurrentInspectIDForExecute());

			//L->IncrementInspectID();
			
			L->CloseProcessingForm();
			EP->SeqParam->AllFinishInProcess=false;
			if(GetParamGlobal()->ReDrawByInspection==true){
				if(NowOnWorking==false && SignalCounter==0){
					SignalCounter++;
					emit	SignalScanningRefresh(L->GetCurrentInspectIDForDisplay());
				}
			}
		}
		else{
			EP->SeqParam->InspectionResult=ResultCode;
			Res->SetOutputCode(ResultCode);
		}
}

void	ExecuteInspectFast::PreFinishScanning(ResultInspection *Res ,int32 CurrentStrategic)
{
	eRepliedCounter++;
	
	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=L->GetExecuter(Res);
	ExecuterID		=Re->GetID();
	int32	StrategicNumber	=CurrentStrategic;
			
	ExecuteInspectBase	*EPBase=GetEntryPoint()->GetExecuteInspect();
	ExecuteInspectFast	*EP=(ExecuteInspectFast *)EPBase;

	//if(Re->IsAllFinishedResultReceiving()==true){
		LastStartTimeForInspection=Res->GetStartTimeForInspection();

		if(GetParamGlobal()->GetMaxScanStrategy()<=1 && GetPageNumb()==1){
			L->SetLatchedInspectionNumber(L->GetInspectionNumber());
		}
		EP->StackedCountInAutoMode--;
		eOutputCounter++;

		int	ResultCode=GetParamGlobal()->ResultCodeInScanning;

		if(L->GetParamGlobal()->GetMaxScanStrategy()<=1
		|| (GetParamGlobal()->BufferedProcessing==false && GetParamGlobal()->GetMaxScanStrategy()<=(StrategicNumber+1))
		|| (L->GetParamGlobal()->GetMaxScanStrategy()>1 && GetParamGlobal()->BufferedProcessing==true)){

			EP->SeqParam->InspectionID=L->GetCurrentInspectIDForExecute();
			EP->SeqParam->NowProcessing	=false;
			Res->SetTimeOutBreak(false);
			Res->SetMaxErrorBreak(false);


			EP->SeqParam->InspectionResultSub	=ResultCode;
			EP->SeqParam->InspectionResult		=ResultCode;
			EP->SeqParam->InspectionFinalResult	=ResultCode;
			Res->SetOutputCode(ResultCode);

			L->CloseProcessingForm();
			EP->SeqParam->AllFinishInProcess=false;
		}
		else{
			EP->SeqParam->InspectionResult=ResultCode;
			Res->SetOutputCode(ResultCode);
		}
}
void	ExecuteInspectFast::SlotInspectionRefresh(LayersBase *base,int64 InspectionID)
{
	NowOnWorking=true;
	GUIInitializer	*G=base->GetGuiInitializer();
	if(G!=NULL){
		if(base->GetParamGlobal()->WaitmilisecForDelayedView!=0){
			G->DelayedViewRefreshInPlayer(InspectionID,base->GetParamGlobal()->WaitmilisecForDelayedView);
		}
		else{
			G->ViewRefreshInPlayer(InspectionID);
		}
	}
	NowOnWorking=false;
	SignalCounter--;
}
void	ExecuteInspectFast::SlotInspectionOnTheWay(int64 InspectionID)
{
	NowOnWorking=true;
	GUIInitializer	*G=GetLayersBase()->GetGuiInitializer();
	if(G!=NULL){
		G->ViewOnTheWayInPlayer(InspectionID);
	}
	NowOnWorking=false;
}
void	ExecuteInspectFast::SlotRunByEveryInspection(LayersBase *base,int64 InspectionID)
{
	NowOnWorking=true;
	GUIInitializer	*G=base->GetGuiInitializer();
	if(G!=NULL){
		G->RefreshByEveryInspection(InspectionID);
	}
	NowOnWorking=false;
}
void	ExecuteInspectFast::SlotScanningRefresh(int64 InspectionID)
{
	NowOnWorking=true;
	GUIInitializer	*G=GetLayersBase()->GetGuiInitializer();
	if(G!=NULL){
		G->ViewRefreshInScanning(InspectionID);
	}
	NowOnWorking=false;
	SignalCounter--;

}
//=================================================================================================


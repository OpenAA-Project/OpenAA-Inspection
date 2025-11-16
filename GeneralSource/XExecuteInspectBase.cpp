/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XExecuteInspectBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XExecuteInspectBase.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayerCmdLocal.h"
#include "XMainSchemeMemory.h"
#include "XCameraInterfaceDLL.h"
#include "XCameraClass.h"
#include "XCriticalFunc.h"
#include "omp.h"
#include "swap.h"
#include "XEntryPoint.h"

ExecuteInspectBase::ExecuteInspectBase(QObject *parent ,EntryPointBase *_EntryPointBaseData ,SeqLocalParam *_SeqParam)
	:QThread(parent)
	,ServiceForLayers(_EntryPointBaseData->GetLayersBase())
	,EntryPointBaseData(_EntryPointBaseData)
	,LocalParam(_SeqParam)
	,TimeStocker(10000)
{
	AutoRepeatFlag=_NoAutoRepeat;
	HaltMode		=false;
	PermitToRun		=true;
	CurrentState	=_EI_IDLE;
	CurrentMode		=_CaptureNone;
	IdleLoopCounter	=0;

	CurrentTypeOfCapture	=_Master;
	CurrentCaptureSource	=_Target;
}

ExecuteInspectBase::~ExecuteInspectBase(void)
{
}

ExecuteInspectBase::ExecuteInspectState	ExecuteInspectBase::GetState(void)
{
	MutexStateMode.lockForRead();
	ExecuteInspectState	ret=CurrentState;
	MutexStateMode.unlock();
	return(ret);
}
ExecuteInspectBase::MotionMode			ExecuteInspectBase::GetMode(void)
{
	MutexStateMode.lockForRead();
	MotionMode	ret=CurrentMode;
	MutexStateMode.unlock();
	return(ret);
}

void	ExecuteInspectBase::SetState(ExecuteInspectBase::ExecuteInspectState b)
{
	MutexStateMode.lockForWrite();
	CurrentState=b;
	MutexStateMode.unlock();
}
void	ExecuteInspectBase::SetMode (ExecuteInspectBase::MotionMode b)
{
	MutexStateMode.lockForWrite();
	ClearHaltMode();
	CurrentMode=b;
	MutexStateMode.unlock();
}

void	ExecuteInspectBase::InitialPrepare(void)
{
	int	N=GetAllocatedCameraCount();
	for(int CamNo=0;CamNo<N;CamNo++){
		CameraClass	*c=GetCamera(CamNo);
		if(c!=NULL){
			c->InitialPrepare();
		}
	}
}
void	ExecuteInspectBase::Prepare(void)		
{
	int	N=GetAllocatedCameraCount();
	for(int CamNo=0;CamNo<N;CamNo++){
		CameraClass	*c=GetCamera(CamNo);
		if(c!=NULL){
			c->Prepare();
		}
	}
}
void	ExecuteInspectBase::AfterPrepare(void)	
{
	int	N=GetAllocatedCameraCount();
	for(int CamNo=0;CamNo<N;CamNo++){
		CameraClass	*c=GetCamera(CamNo);
		if(c!=NULL){
			c->AfterPrepare();
		}
	}
}
void	ExecuteInspectBase::ReadyParam(void)	
{
	int	N=GetAllocatedCameraCount();
	for(int CamNo=0;CamNo<N;CamNo++){
		CameraClass	*c=GetCamera(CamNo);
		if(c!=NULL){
			c->ReadyParam();
		}
	}
}
void	ExecuteInspectBase::AfterStartSequence(void)
{
	int	N=GetAllocatedCameraCount();
	for(int CamNo=0;CamNo<N;CamNo++){
		CameraClass	*c=GetCamera(CamNo);
		if(c!=NULL){
			c->AfterStartSequence();
		}
	}
}

void	ExecuteInspectBase::StartAllCamera(void)
{
	for(int page=0;page<EntryPointBaseData->GetLayersBase()->GetPageNumb();page++){
		IntClass	*d=CameraStates.GetItem(page);
		if(d==NULL){
			CameraStates.Add(0);
		}
		else{
			d->SetValue(0);
		}
	}
}
void	ExecuteInspectBase::FinishCapture(int PageNo)
{
	IntClass	*d=CameraStates.GetItem(PageNo);
	if(d!=NULL){
		d->SetValue(1);
	}
}
bool	ExecuteInspectBase::IsAllFinished(void)
{
	for(int page=0;page<EntryPointBaseData->GetLayersBase()->GetPageNumb();page++){
		IntClass	*d=CameraStates.GetItem(page);
		if(d!=NULL){
			if(d->GetValue()!=1){
				return false;
			}
		}
	}
	return true;
}
LayersBase			*ExecuteInspectBase::GetLayersBase(void)		{	return EntryPointBaseData->GetLayersBase();			}
EntryPointBase		*ExecuteInspectBase::GetEntryPoint(void)		{	return EntryPointBaseData;	}
ParamGlobal			*ExecuteInspectBase::GetParamGlobal(void)		{	return GetLayersBase()->GetParamGlobal();		}
ParamComm			*ExecuteInspectBase::GetParamComm(void)			{	return GetLayersBase()->GetParamComm();			}
ThreadSequence		*ExecuteInspectBase::GetThreadSequence(void)	{	return EntryPointBaseData->GetThreadSequence();		}
GUIInstancePack		*ExecuteInspectBase::GetGUIInstancePack(void)	{	return EntryPointBaseData->GetGUIInstancePack();	}


void	ExecuteInspectBase::SetAutoRepeat(AutoRepeatMode mode)
{
	if(mode==_NoAutoRepeat && AutoRepeatFlag!=_NoAutoRepeat){
		AutoRepeatFlag=mode;	
		if(GetMode()==_CaptureInspect){
			//GetLayersBase()->RewindCalcPoint();
			for(int page=0;page<GetPageNumb();page++){
				GUICmdReqRewindExecuter	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",page);
				GetLayersBase()->GetCalcPoint(Cmd.CPoint);
				Cmd.Send(NULL,page,0);
			}
		}
		GoHalt();
	}
	else{
		AutoRepeatFlag=mode;	
	}
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSetAutoRepeat	Cmd(GetLayersBase(),/**/"ANY",/**/"ANY",page);
		if(mode==_NoAutoRepeat){
			Cmd.RepeatMode=false;
		}
		else{
			Cmd.RepeatMode=true;
		}
		Cmd.Send(NULL,page,0);
	}
}
bool	ExecuteInspectBase::ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)
{
	if(IsLocalCamera()==true){
		if(GetParamComm()->IsMastered()==true){
			for(int cam=0;cam<GetParamGlobal()->TotalCameraNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					IntList PageList;
					GetParamGlobal()->GetPageListFromCameraNo(cam,PageList);
					int	TmpDotPerLine=0;
					int	TmpMaxLines=0;
					for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
						int	Page=p->GetValue();
						TmpDotPerLine	=max(TmpDotPerLine,GetLayersBase()->GetDotPerLine(Page));
						TmpMaxLines		=max(TmpMaxLines	,GetLayersBase()->GetMaxLines(Page));
					}
					int32 ErrorCode;
					
					GetParamGlobal()->DotPerLine	=NewDotPerLine;
					GetParamGlobal()->MaxLines		=NewMaxLines;
					if(C->Realloc(GetParamGlobal(),ErrorCode)==false){
						return false;
					}

					GetParamGlobal()->DotPerLine=TmpDotPerLine;
					GetParamGlobal()->MaxLines	=TmpMaxLines;
				}
			}
		}
		else{
			int	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
			for(int cam=0;cam<AllocatedCamNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					IntList PageList;
					GetParamGlobal()->GetPageListFromCameraNo(cam,PageList);
					int	TmpDotPerLine=0;
					int	TmpMaxLines=0;
					for(IntClass *p=PageList.GetFirst();p!=NULL;p=p->GetNext()){
						int	Page=p->GetValue();
						TmpDotPerLine	=max(TmpDotPerLine,GetLayersBase()->GetDotPerLine(Page));
						TmpMaxLines		=max(TmpMaxLines	,GetLayersBase()->GetMaxLines(Page));
					}
					int32 ErrorCode;
					
					GetParamGlobal()->DotPerLine	=NewDotPerLine;
					GetParamGlobal()->MaxLines		=NewMaxLines;
					if(C->Realloc(GetParamGlobal(),ErrorCode)==false){
						return false;
					}

					GetParamGlobal()->DotPerLine=TmpDotPerLine;
					GetParamGlobal()->MaxLines	=TmpMaxLines;
				}
			}
		}
	}
	return true;
}

bool	ExecuteInspectBase::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(IsLocalCamera()==true){
		if(GetParamComm()->IsMastered()==true){
			for(int cam=0;cam<GetParamGlobal()->TotalCameraNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					if(C->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
						return false;
					}
				}
			}
		}
		else{
			int	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
			for(int cam=0;cam<AllocatedCamNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					if(C->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool	ExecuteInspectBase::Reallocate(int newPhaseNumb)
{
	if(IsLocalCamera()==true){
		if(GetParamComm()->IsMastered()==true){
			for(int cam=0;cam<GetParamGlobal()->TotalCameraNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					if(C->Reallocate(newPhaseNumb,GetPageNumb(),GetLayerNumb(0))==false){
						return false;
					}
				}
			}
		}
		else{
			int	AllocatedCamNumb=GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID);
			for(int cam=0;cam<AllocatedCamNumb;cam++){
				CameraClass		*C=GetCamera(cam);
				if(C!=NULL){
					if(C->Reallocate(newPhaseNumb,GetPageNumb(),GetLayerNumb(0))==false){
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool	ExecuteInspectBase::RemovePhase(int RemovedPhaseCode)	
{
	return true;
}


bool	ExecuteInspectBase::ReallocXYPixelsPage(int Phase ,int Page ,int NewDotPerLine ,int NewMaxLines)
{
	int globalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
	int32	CamNo=GetParamGlobal()->GetCameraNo(globalPage);
	if(0<=CamNo){
		CameraClass		*C=GetCamera(CamNo);
		if(C!=NULL){
			int32 ErrorCode;
			if(C->Realloc(GetParamGlobal(),ErrorCode)==false){
				return false;
			}
		}
	}
	return true;
}
	
bool	ExecuteInspectBase::InsertPage(int IndexPage)	//Create page before Indexed page
{
	int32	CamNo=GetParamGlobal()->GetCameraNo(IndexPage);
	if(0<=CamNo){
		CameraClass		*C=GetCamera(CamNo);
		if(C!=NULL){
			int32 ErrorCode;
			if(C->InsertPage(IndexPage)==false){
				return false;
			}
		}
	}
	return true;
}
	
bool	ExecuteInspectBase::RemovePage(int IndexPage)
{
	int32	CamNo=GetParamGlobal()->GetCameraNo(IndexPage);
	if(0<=CamNo){
		CameraClass		*C=GetCamera(CamNo);
		if(C!=NULL){
			int32 ErrorCode;
			if(C->RemovePage(IndexPage)==false){
				return false;
			}
		}
	}
	return true;
}


static	DWORD	ImageReverseMilisec;

void	ExecuteInspectBase::ImageReverse(int page,ImageBuffer *Buff[] ,int BuffDimCount)
{
	ImageReverseMilisec=GetComputerMiliSec();
	bool XDirReverse ,YDirReverse;
	GetLayersBase()->GetParamGlobal()->GetPageDir(page ,XDirReverse ,YDirReverse);
	if(XDirReverse==true && YDirReverse==false){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<BuffDimCount;i++){
				Buff[i]->LeftsideRight();
			}
		}
	}
	else if(XDirReverse==false && YDirReverse==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<BuffDimCount;i++){
				Buff[i]->TopsideBottom();
			}
		}
	}
	else if(XDirReverse==true && YDirReverse==true){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<BuffDimCount;i++){
				Buff[i]->TopsideBottomLeftsideRight();
			}
		}
	}	
	ImageReverseMilisec=GetComputerMiliSec()-ImageReverseMilisec;
}
void	ExecuteInspectBase::ImageYDelay(int page,ImageBuffer *Buff[] ,int BuffDimCount)
{
	if(GetLayersBase()->GetParamGlobal()->GetPageYDelay(page)!=0){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int i=0;i<BuffDimCount;i++){
				Buff[i]->MoveImage(0,i*GetLayersBase()->GetParamGlobal()->GetPageYDelay(page));
			}
		}
	}
}

void	CallBackFunctionContainer::ExecuteFunc(void)
{
	for(CallBackFunctionList *f=GetFirst();f!=NULL;f=f->GetNext()){
		f->CallBackFunc(f->GBase);
	}
}

void	ExecuteInspectBase::AddCallbackInCaptureOnlyMaster	(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f))
{
	CallBackFunctionList	*f=new CallBackFunctionList();
	f->GBase		=GBase;
	f->CallBackFunc	=CallBackFunc;
	FuncContainerInCaptureOnlyMaster.AppendList(f);
}
void	ExecuteInspectBase::AddCallbackInCaptureOnlyTarget	(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f))
{
	CallBackFunctionList	*f=new CallBackFunctionList();
	f->GBase		=GBase;
	f->CallBackFunc	=CallBackFunc;
	FuncContainerInCaptureOnlyTarget.AppendList(f);
}
void	ExecuteInspectBase::AddCallbackInCaptureInspect		(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f))
{
	CallBackFunctionList	*f=new CallBackFunctionList();
	f->GBase		=GBase;
	f->CallBackFunc	=CallBackFunc;
	FuncContainerInCaptureInspect.AppendList(f);
}
void	ExecuteInspectBase::AddCallbackInCaptureContinuously(GUIFormBase	*GBase ,void (*CallBackFunc)(GUIFormBase *f))
{
	CallBackFunctionList	*f=new CallBackFunctionList();
	f->GBase		=GBase;
	f->CallBackFunc	=CallBackFunc;
	FuncContainerInCaptureContinuously.AppendList(f);
}
int		ExecuteInspectBase::GetAllocatedCameraCount(void)
{
	return min(GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID)
			  ,GetParamGlobal()->TotalCameraNumb);
}
bool	ExecuteInspectBase::LoadCameraSetting(const QString &CamFileName)
{
	if(CamFileName==LastCamFileName){
		return true;
	}
	QFile	file(CamFileName);
	if(file.open(QIODevice::ReadOnly)==true){
		if(LoadCameraSetting(&file)==true){
			LastCamFileName=CamFileName;
			return true;
		}
	}
	return false;
}
bool	ExecuteInspectBase::SaveCameraSetting(const QString &CamFileName)
{
	QFile	file(CamFileName);
	if(file.open(QIODevice::WriteOnly)==true){
		if(SaveCameraSetting(&file)==true){
			return true;
		}
	}
	return false;
}
bool	ExecuteInspectBase::LoadCameraSetting(QIODevice *f)
{
	int	CamNumb=GetAllocatedCameraCount();
	for(int i=0;i<CamNumb;i++){
		int32	Len;
		if(::Load(f,Len)==false){
			return(false);
		}
		QByteArray	AR;
		if(::Load(f,AR)==false){
			return(false);
		}
		if(GetEntryPoint()->NoCamDevice==false){
			QBuffer	TmpBuff(&AR);
			TmpBuff.open(QIODevice::ReadOnly);
			CameraClass		*Cam=GetCamera(i);
			if(Cam!=NULL){
				if(Cam->Load(TmpBuff)==false){
					return(false);
				}
			}
		}
	}
	return true;
}

bool	ExecuteInspectBase::SaveCameraSetting(QIODevice *f)
{
	int	CamNumb=GetAllocatedCameraCount();
	for(int i=0;i<CamNumb;i++){
		int32	Len=1;
		if(::Save(f,Len)==false){
			return(false);
		}
		QBuffer	TmpBuff;
		TmpBuff.open(QIODevice::WriteOnly);
		CameraClass		*Cam=GetCamera(i);
		if(Cam!=NULL){
			if(Cam->Save(TmpBuff)==false){
				return(false);
			}
		}
		QByteArray	AR=TmpBuff.buffer();
		if(::Save(f,AR)==false){
			return(false);
		}
	}
	return true;
}
ExeResult	ExecuteInspectBase::ExecuteInitialAfterEdit	(int ExeID)
{	
	ShadowLayersBasePointer.RemoveAll();
	GetLayersBase()->MakeShadowLayersBasePointer(ShadowLayersBasePointer);

	if(IsLocalCamera()==true && GetEntryPoint()->NoCamDevice==false){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteInitialAfterEdit(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteStartByInspection(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteStartByInspection(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteCaptured	(int ExeID,ListPhasePageLayerPack &CapturedList)
{
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteCaptured(ExeID,CapturedList);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecutePreAlignment		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecutePreAlignment(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteAlignment		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteAlignment(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecutePreProcessing	(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecutePreProcessing(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteProcessing		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteProcessing(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteProcessingRevived(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteProcessingRevived(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecutePostProcessing	(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecutePostProcessing(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecutePreScanning		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecutePreScanning(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteScanning			(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteScanning(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecutePostScanning		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecutePostScanning(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
ExeResult	ExecuteInspectBase::ExecuteManageResult		(int ExeID)
{	
	if(IsLocalCamera()==true){
		ExeResult	Ret=_ER_true;
		for(int page=0;page<GetPageNumb();page++){
			int	CamNo=GetParamGlobal()->GetCameraNo(page);
			if(CamNo<0){
				break;
			}
			CameraClass		*cam=GetCamera(CamNo);
			if(cam!=NULL){
				ExeResult	R=cam->ExecuteManageResult(ExeID);
				if(R!=_ER_true){
					Ret=R;
				}
			}
		}
		return Ret;
	}
	return _ER_true;
}
void	ExecuteInspectBase::EmitSignalCaptured(int CStrategic)
{
	emit	SignalCaptured(CStrategic);
}

void	ExecuteInspectBase::EmitSignalTargetImageCaptured(void)
{
	if(GetLayersBase()->GetOnTerminating()==false){
		emit	SignalTargetImageCaptured();
	}
}

void	ExecuteInspectBase::EmitSignalMasterImageCaptured(void)
{
	if(GetLayersBase()->GetOnTerminating()==false){
		emit	SignalMasterImageCaptured();
	}
}

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XWriteResultThread.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include <time.h>
#include "XWriteResultThread.h"
#include "XDataInLayer.h"
#include "XResultDLLManager.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XLotInformation.h"
#include "XDateTime.h"
#include "XGUIFormBase.h"
#include "XLogOut.h"

//=============================================================================================
ResultStock::ResultStock(LayersBase *base) : ServiceForLayers(base)
{
	AllocatedNumb=0;
	CurrentRPoint=0;
	CurrentWPoint=0;
}
ResultStock::~ResultStock(void)
{
	ResultBaseDim.RemoveAll();
}
void	ResultStock::Initial(LayersBase *Base)
{
	//ResultBaseDim.RemoveAll();
	AllocatedNumb=GetParamGlobal()->NGCacheNumb;
	CurrentRPoint=0;
	CurrentWPoint=0;

	for(;;){
		int	N=ResultBaseDim.GetNumber();
		if(N<=AllocatedNumb){
			break;
		}
		ResultInspectionForStock *r=ResultBaseDim.GetLast();
		ResultBaseDim.RemoveList(r);
		delete	r;
	}
	int	N=ResultBaseDim.GetNumber();
	for(int i=N;i<GetParamGlobal()->NGCacheNumb;i++){
		ResultInspectionForStock *r=new ResultInspectionForStock(i,GetLayersBase());
		r->Initial(GetLayersBase()->GetLogicDLLBase());
		ResultBaseDim.AppendList(r);
	}
	int	n=0;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();n<N && r!=NULL;r=r->GetNext(),n++){
		r->Initial(GetLayersBase()->GetLogicDLLBase());
	}

	GetLayersBase()->InitialExecuter();
}
bool	ResultStock::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	bool	Ret=true;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ResultStock::Reallocate(int newPhaseNumb)
{
	bool	Ret=true;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->Reallocate(newPhaseNumb)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ResultStock::RemovePhase(int RemovedPhaseCode)
{
	bool	Ret=true;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->RemovePhase(RemovedPhaseCode)==false){
			Ret=false;
		}
	}
	return Ret;
}
	
bool	ResultStock::InsertPage(int IndexPage)	//Create page before Indexed page
{
	bool	Ret=true;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->InsertPage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}
bool	ResultStock::RemovePage(int IndexPage)
{
	bool	Ret=true;
	for(ResultInspectionForStock *r=ResultBaseDim.GetFirst();r!=NULL;r=r->GetNext()){
		if(r->RemovePage(IndexPage)==false){
			Ret=false;
		}
	}
	return Ret;
}
ResultInspection *ResultStock::NeedDeleteResultOnCurrent(void)
{
	ResultInspectionForStock *r=ResultBaseDim.GetItem(CurrentWPoint);
	bool	enabled,onWrite;
	GetFlag(r,enabled,onWrite);
	if(enabled==true || onWrite==true){
		SetFlag(r ,false,false);
		return r;
	}
	return NULL;
}

ResultInspection *ResultStock::NeedDeleteResult(void)
{
	for(int i=0;i<AllocatedNumb;i++){
		ResultInspectionForStock *r=ResultBaseDim.GetItem(i);
		bool	enabled,onWrite;
		GetFlag(r,enabled,onWrite);
		if(enabled==true || onWrite==true){
			SetFlag(r ,false,false);
			return r;
		}
	}
	return NULL;
}
void	ResultStock::ExecuteInitialAfterEdit	(int ExeID)
{
	for(int i=0;i<AllocatedNumb;i++){
		ResultInspectionForStock *r=ResultBaseDim.GetItem(i);
		r->ExecuteInitialAfterEdit(ExeID);
	}
}
void	ResultStock::InitialInspectionResult(void)
{
	for(int i=0;i<AllocatedNumb;i++){
		ResultInspectionForStock *r=ResultBaseDim.GetItem(i);
		r->Initial(GetLayersBase()->GetLogicDLLBase());
	}
}

void	ResultInspectionForStock::Set(LayersBase *Base)
{
	//SetStartTimeForInspection(Base->GetStartInspectionTime());
	CopyInspectionAttr(Base);
	ShouldWriteResult		=Base->GetShouldWriteResult();
	ConnectedPCs.RemoveAll();
	PushedTime=XDateTime::currentDateTime();
}

bool	ResultStock::SetWriteMode(LayersBase *Base ,ResultInspection &CurrentRes)
{
	ResultInspectionForStock *r=dynamic_cast<ResultInspectionForStock *>(&CurrentRes);
	if(r==NULL){
		return false;
	}
	FlagMutex.lock();
	r->Set(Base);
	bool	enabled,onWrite;
	GetFlag(r,enabled,onWrite);
	r->SetCriticalError(CurrentRes.GetCriticalError());
	if(onWrite==true){
		r->SetCriticalError(ResultInspection::_ErrorOverflowBuffer);
	}
	SetFlag(r ,true,false);

	r->LotID		=GetLayersBase()->GetLotBase()->GetLotID();
	r->LotName		=GetLayersBase()->GetLotBase()->GetLotName();
	r->MachineID	=GetLayersBase()->GetMachineID();
	r->MasterCode	=GetLayersBase()->GetMasterCode();
	r->MasterName	=GetLayersBase()->GetMasterName();
	
	//FILE	*file=fopen("C:\\Test.txt","a+t");
	//fprintf(file,"%d\n",(int)r->GetInspectionID());
	//fclose(file);


	FlagMutex.unlock();
	return true;
}
bool	ResultStock::SetWriteModeForce(LayersBase *Base ,ResultInspection &CurrentRes)
{
	ResultInspectionForStock *r=dynamic_cast<ResultInspectionForStock *>(&CurrentRes);
	if(r==NULL){
		return false;
	}
	FlagMutex.lock();
	r->Set(Base);
	bool	enabled,onWrite;
	GetFlag(r,enabled,onWrite);
	r->SetCriticalError(CurrentRes.GetCriticalError());
	if(onWrite==true){
		r->SetCriticalError(ResultInspection::_ErrorOverflowBuffer);
	}
	SetFlag(r ,true,false);
	r->SetShouldWriteResult(true);

	r->LotID		=GetLayersBase()->GetLotBase()->GetLotID();
	r->LotName		=GetLayersBase()->GetLotBase()->GetLotName();
	r->MachineID	=GetLayersBase()->GetMachineID();
	r->MasterCode	=GetLayersBase()->GetMasterCode();
	r->MasterName	=GetLayersBase()->GetMasterName();
	
	//FILE	*file=fopen("C:\\Test.txt","a+t");
	//fprintf(file,"%d\n",(int)r->GetInspectionID());
	//fclose(file);


	FlagMutex.unlock();
	return true;
}

ResultInspectionForStock	*ResultStock::GetOldestAndClear(void)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true){
			if(Ret==NULL){
				Ret=e;
			}
			else{
				if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	if(Ret!=NULL){
		SetFlag(Ret ,false,false);
	}
	FlagMutex.unlock();
	return Ret;
}
ResultInspectionForStock	*ResultStock::GetOldest(void)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true){
			if(Ret==NULL){
				Ret=e;
			}
			else{
				if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	FlagMutex.unlock();
	return Ret;
}
ResultInspectionForStock	*ResultStock::GetNewest(void)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetLast();e!=NULL;e=e->GetPrev()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true){
			if(Ret==NULL){
				Ret=e;
			}
			else{
				if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	FlagMutex.unlock();
	return Ret;
}
ResultInspectionForStock	*ResultStock::SearchOnMask(bool IDMaskMode10Base,int IDMaskBit,int IDtoWriteOut)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	if(IDMaskMode10Base==false){
		IDtoWriteOut &= IDMaskBit;
		for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
			bool	enabled,onWrite;
			GetFlag(e,enabled,onWrite);
			if(enabled==true && onWrite==false && (e->GetInspectionID()&IDMaskBit)==IDtoWriteOut){
				if(Ret==NULL){
					QString	LStr=e->GetStartTimeForInspection().toString("hhmmss");
					Ret=e;
				}
				else{
					if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
						Ret=e;
					}
				}
			}
		}
	}
	else if(IDMaskMode10Base==true){
		IDtoWriteOut %= IDMaskBit;
		for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
			bool	enabled,onWrite;
			GetFlag(e,enabled,onWrite);
			if(enabled==true && onWrite==false && (e->GetInspectionID()%IDMaskBit)==IDtoWriteOut){
				if(Ret==NULL){
					Ret=e;
				}
				else{
					if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
						Ret=e;
					}
				}
			}
		}
	}

	if(Ret!=NULL){
		SetFlag(Ret ,false,false);
	}
	FlagMutex.unlock();
	return Ret;
}
ResultInspectionForStock	*ResultStock::SearchOnWrite(void)
{
	FlagMutex.lock();
	ResultInspectionForStock *Ret=NULL;
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true && onWrite==true){
			if(Ret==NULL || Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
				Ret=e;
			}
		}
	}
	if(Ret!=NULL){
		SetFlag(Ret ,false,false);
		FlagMutex.unlock();
		return Ret;
	}
	FlagMutex.unlock();
	return NULL;
}
void	ResultStock::SetIDtoWriteOut(bool IDMaskMode10Base,int IDMaskBit,int id)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	if(IDMaskMode10Base==false){
		id &= IDMaskBit;
		for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
			bool	enabled,onWrite;
			GetFlag(e,enabled,onWrite);
			if(enabled==true && onWrite==false && (e->GetInspectionID()&IDMaskBit)==id){
				if(Ret==NULL){
					QString	LStr=e->GetStartTimeForInspection().toString("hhmmss");
					Ret=e;
				}
				else{
					if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
						Ret=e;
					}
				}
			}
		}
	}
	else if(IDMaskMode10Base==true){
		id %= IDMaskBit;
		for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
			bool	enabled,onWrite;
			GetFlag(e,enabled,onWrite);
			if(enabled==true && onWrite==false && (e->GetInspectionID()%IDMaskBit)==id){
				if(Ret==NULL){
					Ret=e;
				}
				else{
					if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
						Ret=e;
					}
				}
			}
		}
	}

	if(Ret!=NULL){
		SetFlag(Ret ,true,true);
	}
	FlagMutex.unlock();
}
ResultInspectionForStock	*ResultStock::PickupForWriteInSlave(const XDateTime &InspectedTime)
{
	ResultInspectionForStock	*Ret=NULL;
	XDateTime					LatestTime;
	ResultInspectionForStock *e;
	FlagMutex.lock();
	for(e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){	
		//bool	enabled, onWrite;
		//GetFlag(e,enabled,onWrite);
		//if(e->GetShouldWriteResult()==false || enabled==false){
		//	continue;
		//}
		//if(enabled==true && onWrite==false && ::IsEqual(e->GetStartTimeForInspection(),InspectedTime)==true){
		if(e->GetStartTimeForInspection()==InspectedTime){
			if(Ret==NULL){
				LatestTime=e->GetPushedTime();			
				Ret=e;
			}
			else{
				if(LatestTime<e->GetPushedTime()){
					LatestTime=e->GetPushedTime();			
					Ret=e;
				}
			}
		}
	}
	if(Ret!=NULL){
		SetFlag(Ret ,false,false);
	}

	FlagMutex.unlock();

	if(Ret!=NULL){
		//QString	LStr=Ret->GetStartTimeForInspection().toString("hhmmss");
		//char	buff[50];
		//QString2Char(LStr,buff ,sizeof(buff));
		//GetLayersBase()->GetLogCreater()->PutLogA2(__LINE__,"PickupForWriteInSlave",buff,Ret->GetInspectionID());
	}
	return Ret;
}

ResultInspectionForStock	*ResultStock::GetResult(int n)
{	
	return ResultBaseDim[n];
}

ResultInspectionForStock	*ResultStock::Pickup(const XDateTime &InspectedTime)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		//bool	enabled,onWrite;
		//GetFlag(e,enabled,onWrite);
		if(e->GetShouldWriteResult()==false){
			continue;
		}
		if(e->GetStartTimeForInspection()==InspectedTime){
			Ret=e;
		}
	}
	FlagMutex.unlock();

	return Ret;
}

void	ResultStock::GetFlag(ResultInspectionForStock *Src ,bool &Enabled ,bool &OnWrite)
{
	Enabled=Src->GetEnabled();
	OnWrite=Src->GetOnWrite();
}
void	ResultStock::SetFlag(ResultInspectionForStock *Src ,bool Enabled ,bool OnWrite)
{
	Src->SetEnabled(Enabled);
	Src->SetOnWrite(OnWrite);
}
int		ResultStock::GetStockedCount(void)
{
	FlagMutex.lock();
	int	N=0;
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true){
			N++;
		}
	}
	FlagMutex.unlock();
	return N;
}
int		ResultStock::GetStockedCountToWrite(void)
{
	FlagMutex.lock();
	int	N=0;
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(onWrite==true){
			N++;
		}
	}
	FlagMutex.unlock();
	return N;
}
ResultInspection	*ResultStock::GetBufferedResult(int64 inspectionID)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->IsFinished()==true){
			if(e->GetInspectionID()==inspectionID){
				if(Ret==NULL){
					Ret=e;
				}
				else if(Ret->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	FlagMutex.unlock();
	return Ret;
}
ResultInspection	*ResultStock::GetBufferedResultAbsolutely(int64 inspectionID)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->IsFinished()==true){
			if(e->GetInspectionID()==inspectionID){
				if(Ret==NULL){
					Ret=e;
				}
				else if(Ret->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	if(Ret==NULL){
		for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
			if(e->GetInspectionID()==inspectionID){
				if(Ret==NULL){
					Ret=e;
				}
				else if(Ret->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	FlagMutex.unlock();
	return Ret;
}

ResultInspection	*ResultStock::GetLatest(void)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->IsFinished()==true){
			if(Ret==NULL){
				Ret=e;
			}
			else if(Ret->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
				Ret=e;
			}
		}
	}
	FlagMutex.unlock();
	return Ret;
}

ResultInspection	*ResultStock::GetBufferedOlderResult(int64 inspectionID, int GenerationLevel)
{
	ResultInspectionForStock	*Ret=NULL;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->IsFinished()==true){
			if(e->GetInspectionID()==inspectionID){
				if(Ret==NULL){
					Ret=e;
				}
				else if(Ret->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
					Ret=e;
				}
			}
		}
	}
	if(Ret!=NULL){
		for(int k=0;k<GenerationLevel;k++){
			ResultInspectionForStock	*p=NULL;
			for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
				if(e->IsFinished()==true){
					if(Ret->GetStartTimeForInspection()>e->GetStartTimeForInspection()){
						if(p==NULL){
							p=e;
						}
						else if(p->GetStartTimeForInspection()<e->GetStartTimeForInspection()){
							p=e;
						}
					}
				}
			}
			Ret=p;
			if(Ret==NULL){
				break;
			}
		}
	}

	FlagMutex.unlock();
	return Ret;
}
void	ResultStock::CastAll(void)
{
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true && onWrite==false){
			SetFlag(e ,false,false);
		}
	}
}
int64	ResultStock::GetUnsavedMinimumID(void)
{
	int64	MinID=99999999;
	FlagMutex.lock();
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		bool	enabled,onWrite;
		GetFlag(e,enabled,onWrite);
		if(enabled==true && onWrite==false){
			if(e->GetInspectionID()<MinID){
				MinID=e->GetInspectionID();
			}
		}
	}
	FlagMutex.unlock();
	if(MinID==99999999){
		return -1;
	}
	return MinID;
}

ResultInspectionForStock	*ResultStock::Ineffective(int CountFromOlder)
{
	ResultInspectionForStock	*r=GetOldest();
	if(r!=NULL){
		int	FirstID=r->GetID();
		if(r!=NULL){
			int	N=ResultBaseDim.GetCount();
			for(int i=0;i<(CountFromOlder-1);i++){
				for(int j=0;j<N;j++){
					if(r->GetNext()==NULL){
						r=ResultBaseDim.GetFirst();
					}
					else{
						r=r->GetNext();
					}
					if(r->GetEnabled()==true){
						break;
					}
				}
				if(r->GetID()==FirstID){
					return NULL;
				}
			}
			if(r->GetEnabled()==false){
				return NULL;
			}
			r->SetEnabled(false);
		}
	}
	return r;
}
void	ResultStock::ClearAllErrorGroup(void)
{
	for(ResultInspectionForStock *e=ResultBaseDim.GetFirst();e!=NULL;e=e->GetNext()){
		e->ClearAllErrorGroup();
	}
}


//=============================================================================================
SlaveOutputResultQueueLeaf::SlaveOutputResultQueueLeaf(LayersBase *_Base
								,int32 _MachineID
								,const XDateTime &_InspectedTime
								,ResultInspection *_RBase
								,int			phase
								,int			_localPage
								,const QByteArray	&_LotData
								,int32		_MasterID
								,const QString &_DeliveryInfo)
{
	Base			=_Base;
	MachineID		=_MachineID;
	InspectedTime	=_InspectedTime;
	RBase			=_RBase;
	Phase			= phase;
	localPage		=_localPage;
	LotData			=_LotData;
	MasterID		=_MasterID;
	DeliveryInfo	=_DeliveryInfo;
}
bool	SlaveOutputResultQueueLeaf::OutputResultSlave (void)
{
	Base->SetMasterCode(MasterID);
	QBuffer	LotBuff(&LotData);
	LotBuff.open(QIODevice::ReadOnly);
	//Base->GetLot()->Load(&LotBuff);
	QString		LotID;
	QString		LotName;
	::Load(&LotBuff,LotID);
	::Load(&LotBuff,LotName);
	RBase->SetDeliveredInfo(DeliveryInfo);

	ResultInspectionForStockPointerContainer ShadowResStocks;
	Base->WriteResultShadowPickupForWriteInSlave(ShadowResStocks
												,InspectedTime);
	bool	ret=Base->GetResultDLLBase()->OutputResultSlave (ShadowResStocks
															,MachineID ,InspectedTime
															,RBase
															,LotID,Phase,localPage);
	if(ret==false){
		RBase->SetCriticalError(ResultInspection::_ErrorCantWrite);
	}
	return ret;
}

//========================================================================================
SlaveWriteThread::SlaveWriteThread(LayersBase *base)
	:ServiceForLayers(base)
{
	CmdFinish=false;
}

void SlaveWriteThread::run()
{
	while(CmdFinish==false){
		if(GetParamGlobal()!=NULL && GetParamGlobal()->OutputResult==true){
			WriteLoop();
			GetLayersBase()->WriteResultSlaveWriteThreadLoop();
			msleep(10);
		}
		else{
			msleep(300);
		}
	}
}
void	SlaveWriteThread::WriteLoop(void)
{
	SlaveWriteQueueMutex.lock();
	SlaveOutputResultQueueLeaf	*WSlave=SlaveWriteQueue.GetFirst();
	SlaveWriteQueue.RemoveList(WSlave);
	SlaveWriteQueueMutex.unlock();

	if(WSlave!=NULL){
		if(GetParamGlobal()->StandardWriteResult==true){
			WSlave->OutputResultSlave();
		}
		delete	WSlave;
	}
	if(GetLayersBase()->GetOnTerminating()==true){
		return;
	}
}
void	SlaveWriteThread::Push(SlaveOutputResultQueueLeaf  *W)
{
	SlaveWriteQueueMutex.lock();
	SlaveWriteQueue.AppendList(W);
	SlaveWriteQueueMutex.unlock();
}

WriteResultThread::WriteResultThread(LayersBase *base ,bool StartThreadWriteMode)
	:ServiceForLayers(base)
{
    EnabledStockedWrite=false;
    IDMaskBit=0xFFFFFFFFU;
    IDMaskMode10Base=false;
    IDtoWriteOut=-1;
	ResultCache=new ResultStock(base);
	setTerminationEnabled(true);
	CmdFinish=false;
	CastFlag		=false;
	ForceWriteFlag	=false;
	Mastered		=true;
	
	SlaveWriteThreadInst=new SlaveWriteThread(base);
	if(GetLayersBase()->GetShadowLevel()==0){
		if(StartThreadWriteMode==true){
			SlaveWriteThreadInst->start();
		}
	}
}
WriteResultThread::~WriteResultThread(void)
{
	if(ResultCache!=NULL){
		delete	ResultCache;
		ResultCache=NULL;
	}
	if(SlaveWriteThreadInst!=NULL){
		SlaveWriteThreadInst->CmdFinish=true;
		SlaveWriteThreadInst->wait(500);
		SlaveWriteThreadInst->terminate();
		delete	SlaveWriteThreadInst;
		SlaveWriteThreadInst=NULL;
	}

}
void	WriteResultThread::Initial(LayersBase *Base)
{
	if(ResultCache!=NULL){
		ResultCache->Initial(Base);
	}
}
bool	WriteResultThread::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(ResultCache!=NULL){
		return ResultCache->Reallocate(newPhaseNumb , newPageNumb ,newLayerNumb);
	}
	return false;
}
bool	WriteResultThread::Reallocate(int newPhaseNumb)
{
	if(ResultCache!=NULL){
		return ResultCache->Reallocate(newPhaseNumb);
	}
	return false;
}
bool	WriteResultThread::RemovePhase(int RemovedPhaseCode)
{
	if(ResultCache!=NULL){
		return ResultCache->RemovePhase(RemovedPhaseCode);
	}
	return false;
}
bool	WriteResultThread::InsertPage(int IndexPage)	//Create page before Indexed page
{
	if(ResultCache!=NULL){
		return ResultCache->InsertPage(IndexPage);
	}
	return false;
}
bool	WriteResultThread::RemovePage(int IndexPage)
{
	if(ResultCache!=NULL){
		return ResultCache->RemovePage(IndexPage);
	}
	return false;
}
void	WriteResultThread::ExecuteInitialAfterEdit	(int ExeID,ResultInspection *Res)
{
	if(ResultCache!=NULL){
		ResultCache->ExecuteInitialAfterEdit	(ExeID);
	}
	ResultInspectionForStock	*R=dynamic_cast<ResultInspectionForStock *>(Res);
	if(R!=NULL){
		for(;;){
			if(R->GetEnabled()==false){
				break;
			}
			ResultInspectionForStock	*W=ResultCache->GetOldestAndClear();
			if(W==NULL){
				break;
			}
			msleep(100);
		}
		//Initial(pInspectionData);
	}
	if(Res!=NULL){
		ResultCache->InitialInspectionResult();
		Res->Initial(GetLayersBase()->GetLogicDLLBase());
	}
}

ResultInspectionForStock	*WriteResultThread::PickupForWriteInSlave(const XDateTime &InspectedTime)
{
	return ResultCache->PickupForWriteInSlave(InspectedTime);
}
ResultInspectionForStock	*WriteResultThread::Pickup(const XDateTime &InspectedTime)
{
	return ResultCache->Pickup(InspectedTime);
}

void	WriteResultThread::PutCurrentToStock(LayersBase *Base ,ResultInspection &currentResultData)
{
	ResultCache->SetWriteMode(Base ,currentResultData);
	if(currentResultData.IsResultOK()==true)
		GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"WriteResultThread::PutCurrentToStock-OK");
	else
		GetLayersBase()->GetLogCreater()->PutLog(__LINE__,"WriteResultThread::PutCurrentToStock-NG");
}

void	WriteResultThread::PutForceToStock(LayersBase *Base ,ResultInspection &currentResultData)
{
	ResultCache->SetWriteModeForce(Base ,currentResultData);
}

ResultInspection *WriteResultThread::NeedDeleteResultOnCurrent(void)
{
	return ResultCache->NeedDeleteResultOnCurrent();
}
ResultInspection *WriteResultThread::NeedDeleteResult(void)
{
	return ResultCache->NeedDeleteResult();
}

void	WriteResultThread::SetCastAll(void)
{
	CastFlag=true;
}
bool	WriteResultThread::WaitForFinishingCast(int MaxMilisec)
{
	DWORD	StartTime=GetComputerMiliSec();
	while(CastFlag==true){
		GSleep(100);
		if(GetComputerMiliSec()-StartTime>MaxMilisec){
			return false;
		}
	}
	return true;
}
void	WriteResultThread::ClearAllErrorGroup(void)
{
	ResultCache->ClearAllErrorGroup();
}

void	WriteResultThread::ForceWrite(void)
{
	ForceWriteFlag=true;
}

void	WriteResultThread::SetIDtoWriteOut(int id)
{
	if(EnabledStockedWrite==true){
		ResultCache->SetIDtoWriteOut(IDMaskMode10Base,IDMaskBit,id);
		//GetLayersBase()->GetLogCreater()->PutLogA2(__LINE__,"SetIDtoWriteOut",IDMaskBit,id);
	}
}

int64	WriteResultThread::GetUnsavedMinimumID(void)
{
	return ResultCache->GetUnsavedMinimumID();
}


bool	WriteResultThread::IsLocalCamera(void)
{
	if((GetParamComm()->Mastered==true && GetParamGlobal()->TotalCameraNumb!=0 && GetParamComm()->ConnectedPCNumb==0)
	|| (GetParamComm()->Mastered==false && GetParamComm()->GetLocalCameraNumb(GetParamComm()->ThisComputerID))!=0){
		return(true);
	}
	return(false);
}


void WriteResultThread::run()
{
	ResultInspectionForStock	*W;
	while(GetLayersBase()->GetOnTerminating()==false){
		if(GetParamGlobal()->OutputResult==true){
			if(CmdFinish==true){
				SlaveWriteThreadInst	->CmdFinish=true;
				return;
			}
			if(Mastered==true && GetParamGlobal()->StandardWriteResult==true){
				if(EnabledStockedWrite==false || ForceWriteFlag==true){
					W=ResultCache->GetOldestAndClear();
					if(W!=NULL && W->GetLayersBase()->GetResultDLLBase()->UnSavedResult()==false && W->GetShouldWriteResult()==true){
						if(IsLocalCamera()==true){
							if(GetParamGlobal()->ModeCompressNGImage==true){
								while(GetLayersBase()->NeedWaitingForCompress()==true){
									if(GetLayersBase()->GetOnTerminating()==true){
										SlaveWriteThreadInst	->CmdFinish=true;
										return;
									}
									msleep(10);
								}
							}
						}
						//if(GetParamComm()->ConnectedPCNumb==0){
						//	ResultCache->SetFlag(W ,true,true);
						//}
						ResultInspectionForStockPointerContainer	ShadowResStocks;
						GetLayersBase()->WriteResultShadowForceWriteCommon(ShadowResStocks);
						if(W->GetLayersBase()->GetResultDLLBase()->OutputResultCommon(W,ShadowResStocks)==false){
							W->SetCriticalError(ResultInspection::_ErrorCantWrite);
						}
						else{
							emit	SignalWroteCommon(W->GetStartTimeForInspection());
						}
					}
				}
				else if(EnabledStockedWrite==true){
					//W=ResultCache->SearchOnMask(IDMaskMode10Base,IDMaskBit,IDtoWriteOut);
					W=ResultCache->SearchOnWrite();	//Find oldest Result(Enable==true && OnWrite==true)	, and set false 
					if(W!=NULL && W->GetLayersBase()->GetResultDLLBase()->UnSavedResult()==false && W->GetShouldWriteResult()==true){
						if(IsLocalCamera()==true){
							if(GetParamGlobal()->ModeCompressNGImage==true){
								while(GetLayersBase()->NeedWaitingForCompress()==true){
									if(GetLayersBase()->GetOnTerminating()==true){
										SlaveWriteThreadInst	->CmdFinish=true;
										return;
									}
									msleep(10);
								}
							}
						}
						ResultInspectionForStockPointerContainer	ShadowResStocks;
						GetLayersBase()->WriteResultShadowStockedWriteCommon(ShadowResStocks);
						if(W->GetLayersBase()->GetResultDLLBase()->OutputResultCommon(W,ShadowResStocks)==false){
							W->SetCriticalError(ResultInspection::_ErrorCantWrite);
						}
						else{
							emit	SignalWroteCommon(W->GetStartTimeForInspection());
						}
						IDtoWriteOut=-1;
					}
				}
				{
					FifoWriteBase	*abase=IsWrittenOldestOne();

					FifoChangeLot	*b=dynamic_cast<FifoChangeLot *>(abase);
					if(b!=NULL){
						GetLayersBase()->GetLot(b->DeliveryNo)->Reserve(b->LotAutoCount
																	  ,b->LotID
																	  ,b->LotName
																	  ,b->Remark);
						emit	SignalChangeLotInfo(b->DeliveryNo);
					}
					else{
						FifoWriteOldest	*a=dynamic_cast<FifoWriteOldest *>(abase);
						if(a!=NULL){
							W=ResultCache->GetOldestAndClear();
							if(W!=NULL){
								W->LotID	=a->LotID;
								W->LotName	=a->LotName;
								W->SetDeliveredInfo(a->DeliveredInfo);
							}
							delete	a;
							if(W!=NULL && W->GetLayersBase()->GetResultDLLBase()->UnSavedResult()==false && W->GetShouldWriteResult()==true){
								if(IsLocalCamera()==true){
									if(GetParamGlobal()->ModeCompressNGImage==true){
										while(GetLayersBase()->NeedWaitingForCompress()==true){
											if(GetLayersBase()->GetOnTerminating()==true){
												SlaveWriteThreadInst	->CmdFinish=true;
												return;
											}
											msleep(10);
										}
									}
								}
								ResultInspectionForStockPointerContainer	ShadowResStocks;
								if(W->GetLayersBase()->GetResultDLLBase()->OutputResultCommon(W,ShadowResStocks)==false){
									W->SetCriticalError(ResultInspection::_ErrorCantWrite);
								}
								else{
									emit	SignalWroteCommon(W->GetStartTimeForInspection());
								}
							}
						}
					}
				}
			}
			SlaveOutputResultQueueLeaf	*WSlave;
			while((WSlave=PopSlaveOutputResultQueueLeaf())!=NULL){
				if(IsLocalCamera()==true){
					if(GetParamGlobal()->ModeCompressNGImage==true){
						while(GetLayersBase()->NeedWaitingForCompress()==true){
							if(GetLayersBase()->GetOnTerminating()==true){
								SlaveWriteThreadInst	->CmdFinish=true;
								return;
							}
							msleep(10);
						}
					}
				}
				//WSlave->OutputResultSlave();
				emit	SignalWroteSlave(WSlave->GetInspectedTime());
				//emit	SignalOutputResultSlave(WSlave);
				SlaveWriteThreadInst	->Push(WSlave);
			}

			if(CastFlag==true){
				ResultCache->CastAll();
				GetLayersBase()->WriteResultShadowCastAll();
				CastFlag=false;
			}
			if(ForceWriteFlag==true){
				if(GetStockedCount()==0
				&& GetLayersBase()->GetWriteResultShadowStockedCount()==0){
					ForceWriteFlag=false;
				}
			}
			msleep (10);
			if(GetLayersBase()->GetOnTerminating()==true){
				return;
			}
		}
		else{
			msleep (200);
		}
	}
}
void	WriteResultThread::PushSlaveWriteThread(SlaveOutputResultQueueLeaf	*WSlave)
{
	SlaveWriteThreadInst->Push(WSlave);
}


void	WriteResultThread::FlushWaitForWrite(void)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	if(Mastered==true){
		if(GetParamGlobal()->StandardWriteResult==true){
			time_t	St=time(NULL);
			if(EnabledStockedWrite==false || ForceWriteFlag==true){
				while(GetStockedCount()!=0){
					int	N=GetStockedCount();
					for(time_t	t=time(NULL);time(NULL)-t<3;){
						if(N!=GetStockedCount()){
							break;
						}
						msleep(100);
						QCoreApplication::processEvents();
					}
					if(time(NULL)-St>60){
						break;
					}
				}
			}
			else if(EnabledStockedWrite==true){
				while(GetStockedCountToWrite()!=0){
					int	N=GetStockedCountToWrite();
					for(time_t	t=time(NULL);time(NULL)-t<3;){
						if(N!=GetStockedCountToWrite()){
							break;
						}
						QCoreApplication::processEvents();
						msleep(100);
					}
					if(time(NULL)-St>60){
						break;
					}
				}
			}
		}
	}
	else{
		if(GetParamGlobal()->StandardWriteResult==true){
			time_t	St=time(NULL);
			if(EnabledStockedWrite==false || ForceWriteFlag==true){
				while(GetStockedCount()!=0){
					int	N=GetStockedCount();
					for(time_t	t=time(NULL);time(NULL)-t<3;){
						if(N!=GetStockedCount()){
							break;
						}
						msleep(100);
						QCoreApplication::processEvents();
					}
					if(time(NULL)-St>30){
						break;
					}
				}
			}
			else if(EnabledStockedWrite==true){
				while(GetStockedCountToWrite()!=0){
					int	N=GetStockedCountToWrite();
					for(time_t	t=time(NULL);time(NULL)-t<3;){
						if(N!=GetStockedCountToWrite()){
							break;
						}
						QCoreApplication::processEvents();
						msleep(100);
					}
					if(time(NULL)-St>30){
						break;
					}
				}
			}
		}
	}
	ReEntrant=false;
}

void	WriteResultThread::SetWriteOldestOne(void)
{
	FifoWriteOldest	*a=new FifoWriteOldest();
	a->LotID		=	GetLayersBase()->GetLotBase()->GetLotID();
	a->LotName		=	GetLayersBase()->GetLotBase()->GetLotName();
	a->EventTime	=	XDateTime::currentDateTime();
	a->DeliveredInfo=	DeliveredInfo;
	MutexWriteOldest.lock();
	DataWriteOldest.AppendList(a);
	MutexWriteOldest.unlock();
}

void	WriteResultThread::ReserveChangeLot(int32 _DeliveryNo
											,int32 _NextLotAutoCount
											,QString _NextLotID
											,QString _NextLotName
											,QString _NextRemark)
{
	FifoChangeLot	*a=new FifoChangeLot();
	a->DeliveryNo	=   _DeliveryNo;
	a->LotAutoCount	=	_NextLotAutoCount;
	a->LotID		=	_NextLotID;
	a->LotName		=	_NextLotName;
	a->Remark		=	_NextRemark;
	a->EventTime	=	XDateTime::currentDateTime();
	MutexWriteOldest.lock();
	DataWriteOldest.AppendList(a);
	MutexWriteOldest.unlock();
}

FifoWriteBase	*WriteResultThread::IsWrittenOldestOne(void)
{
	MutexWriteOldest.lock();
	FifoWriteBase	*Oldest=NULL;
	for(FifoWriteBase	*a=DataWriteOldest.GetFirst();a!=NULL;a=a->GetNext()){
		if(Oldest==NULL || Oldest->EventTime>a->EventTime){
			Oldest=a;
		}
	}
	DataWriteOldest.RemoveList(Oldest);
	MutexWriteOldest.unlock();	
	return Oldest;
}

int		WriteResultThread::GetStockedCount(void)
{
	return ResultCache->GetStockedCount();
}
int		WriteResultThread::GetStockedCountToWrite(void)
{
	return ResultCache->GetStockedCountToWrite();
}

void	WriteResultThread::PushSlaveCommand(SlaveOutputResultQueueLeaf *W)
{
	SlaveOutputResultQueueMutex.lock();
	SlaveOutputResultQueue.AppendList(W);
	SlaveOutputResultQueueMutex.unlock();
}
SlaveOutputResultQueueLeaf	*WriteResultThread::PopSlaveOutputResultQueueLeaf(void)
{
	SlaveOutputResultQueueMutex.lock();
	SlaveOutputResultQueueLeaf	*W=SlaveOutputResultQueue.GetFirst();
	SlaveOutputResultQueue.RemoveList(W);
	SlaveOutputResultQueueMutex.unlock();
	return W;
}

ResultInspectionForStock	*WriteResultThread::RemoveResultFromOldest(int n)
{
	ResultInspectionForStock	*r=ResultCache->Ineffective(n);
	return r;
}
#include "XTypeDef.h"
#include "XLotInformation.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "XDataInLayerCommander.h"
#include "XDataInLayerCmdLocal.h"
#include "XWriteResultThread.h"

LotInformation::LotInformation(LayersBase *base)
	:ServiceForLayers(base)
{
	LotAutoCount=0;
}

LotInformation::LotInformation(void)
	:ServiceForLayers(NULL)
{
	LotAutoCount=0;
}

	
bool	LotInformation::Save(QIODevice *f)
{
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	return true;
}

bool	LotInformation::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	return true;
}

void	LotInformation::ReserveChangeLot(int32 _NextLotAutoCount
										,QString _NextLotID
										,QString _NextLotName
										,QString _NextRemark)
{
	GetLayersBase()->GetResultThread()->ReserveChangeLot(DeliveryNo
							,_NextLotAutoCount
							,_NextLotID
							,_NextLotName
							,_NextRemark);
}

void	LotInformation::Reserve(int32 _NextLotAutoCount
							,QString _NextLotID
							,QString _NextLotName
							,QString _NextRemark)
{
	NextLotAutoCount	=_NextLotAutoCount;
	NextLotID			=_NextLotID;
	NextLotName			=_NextLotName;
	NextRemark			=_NextRemark;
}

void	LotInformation::ChangeLotInfo(void)
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdChangeLotInfo	RCmd(GetLayersBase(),"ANY","ANY" ,GlobalPage);
		RCmd.DeliveryNo		=DeliveryNo;
		RCmd.LotAutoCount	=NextLotAutoCount;
		RCmd.LotID			=NextLotID;
		RCmd.LotName		=NextLotName;
		RCmd.Send(NULL,page,0);
	}

	SetLotAutoCount	(NextLotAutoCount);
	SetLotID			(NextLotID);
	SetLotName		(NextLotName);
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->InitialExecuter();
	GetLayersBase()->InitializeToStart();

	for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
		ResultDLLBaseRoot	*RL=R->GetDLLPoint();
		if(RL!=NULL){
			CmdChangeResultLotInfo	ResCmd(GetLayersBase());
			ResCmd.DeliveryNo	=DeliveryNo;
			ResCmd.LotID		=NextLotID;
			ResCmd.LotName		=NextLotName;
			ResCmd.Remark		=NextRemark;
			RL->TransmitDirectly(&ResCmd);
		}
	}
}

	
LotBase::LotBase(LayersBase *base)
	:ServiceForLayers(base)
{
	LotDim						=NULL;
	AllocatedLotDeliveryCount	=0;
}

LotBase::~LotBase(void)
{
	if(LotDim!=NULL){
		delete	[]LotDim;
		LotDim=NULL;
	}
	AllocatedLotDeliveryCount=0;
}

void	LotBase::Initial(void)
{
	if(LotDim!=NULL){
		delete	[]LotDim;
	}
	AllocatedLotDeliveryCount=GetParamGlobal()->MaxLotDeliveryCount;
	LotDim=new LotInformation[AllocatedLotDeliveryCount];
	for(int i=0;i<AllocatedLotDeliveryCount;i++){
		LotDim[i].SetLayersBase(GetLayersBase());
		LotDim[i].SetDeliveryNo(i);
	}
}

LotInformation	*LotBase::GetLot(int n)	const
{
	if(n<AllocatedLotDeliveryCount){
		return &LotDim[n];
	}
	return NULL;
}

bool	LotBase::Save(QIODevice *f)
{
	int32	Ver=1;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,AllocatedLotDeliveryCount)==false)
		return false;
	for(int i=0;i<AllocatedLotDeliveryCount;i++){
		if(GetLot(i)->Save(f)==false)
			return false;
	}
	return true;
}

bool	LotBase::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,AllocatedLotDeliveryCount)==false)
		return false;

	if(LotDim!=NULL){
		delete	[]LotDim;
	}
	LotDim=new LotInformation[AllocatedLotDeliveryCount];

	for(int i=0;i<AllocatedLotDeliveryCount;i++){
		if(GetLot(i)->Load(f)==false)
			return false;
	}
	return true;
}

IntList	LotBase::GetLotAutoCount(void)	const
{
	IntList	LList;
	for(int i=0;i<AllocatedLotDeliveryCount;i++){
		LList.Add(GetLot(i)->GetLotAutoCount());
	}
	return LList;
}
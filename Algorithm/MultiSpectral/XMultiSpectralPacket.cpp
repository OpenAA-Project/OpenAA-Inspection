/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMultiSpectralItem.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XMultiSpectral.h"
#include "XMultiSpectralLibrary.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralFunc.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XCriticalFunc.h"

MultiSpectralThresholdReq::MultiSpectralThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	MultiSpectralThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	return true;
}
bool	MultiSpectralThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	return true;
}

MultiSpectralThresholdSend::MultiSpectralThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;

	SearchDot		=0;
	ThresholdLength	=0;
	OKDot			=0;
}

void	MultiSpectralThresholdSend::ConstructList(MultiSpectralThresholdReq *reqPacket,MultiSpectralBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;

	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			MultiSpectralItem	*BItem=(MultiSpectralItem *)item;

			const	MultiSpectralThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			SearchDot		=RThr->SearchDot;
			ThresholdLength	=RThr->ThresholdLength;
			OKDot			=RThr->OKDot;
		}
	}
}

bool	MultiSpectralThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;

	if(::Save(f,SearchDot)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,OKDot)==false)
		return false;

	return true;
}
bool	MultiSpectralThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;

	if(::Load(f,SearchDot)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,OKDot)==false)
		return false;

	return true;
}

MultiSpectralReqTryThreshold::MultiSpectralReqTryThreshold(void)
{
	Data.GlobalPage=-1;
	Data.ItemID=-1;
}
bool	MultiSpectralReqTryThreshold::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	MultiSpectralReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

MultiSpectralSendTryThreshold::MultiSpectralSendTryThreshold(void)
{
	Result		=new ResultInItemPI();
}
MultiSpectralSendTryThreshold::~MultiSpectralSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	MultiSpectralSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;

	return true;
}
bool	MultiSpectralSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;

	return true;
}

void	MultiSpectralSendTryThreshold::ConstructList(MultiSpectralReqTryThreshold *reqPacket,MultiSpectralBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	MultiSpectralInPage		*BP=(MultiSpectralInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->Data.GlobalPage));
	if(BP!=NULL){
		MultiSpectralItem		*BI=(MultiSpectralItem *)BP->SearchIDItem(reqPacket->Data.ItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base);
		}
	}
}
void	MultiSpectralSendTryThreshold::Calc(MultiSpectralItem *Target
												,MultiSpectralItem *Src
												,MultiSpectralBase *Base)

{
	MultiSpectralInPage		*BP=(MultiSpectralInPage *)Base->GetPageData(Src->GetPage());
	MultiSpectralBase		*BBase=(MultiSpectralBase *)BP->GetParentBase();
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;


	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;
	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	//Target->CopyArea(*Src);
	MultiSpectralThreshold			*WThr=Target->GetThresholdW();
	const	MultiSpectralThreshold	*RThr=Src	->GetThresholdR();
	WThr->CopyFrom(*RThr);
	
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
	Target->ExecuteStartByInspection(0 ,0,Result);
	Target->ExecuteProcessing		(0 ,0,Result);

	Result->SetAddedData(NULL,0);
	
}
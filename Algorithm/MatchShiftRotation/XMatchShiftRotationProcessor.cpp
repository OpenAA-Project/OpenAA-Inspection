/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MatchShiftRotation\XMatchShiftRotationProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XMatchShiftRotation.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XMatchShiftRotationLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "swap.h"
#include "XCriticalFunc.h"

MatchShiftRotationThresholdReq::MatchShiftRotationThresholdReq(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	MatchShiftRotationThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	MatchShiftRotationThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
MatchShiftRotationThresholdSend::MatchShiftRotationThresholdSend(void)
{
	GlobalPage	=-1;
	ItemID		=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;

	SearchArea			=0;	
	SearchAngle			=0;

	TargetLayer			=0;		//For ring brightness
	SearchLittleInItem	=0;
	MatchingRate		=0;
}

void	MatchShiftRotationThresholdSend::ConstructList(MatchShiftRotationThresholdReq *reqPacket,MatchShiftRotationBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			MatchShiftRotationItem	*BItem=(MatchShiftRotationItem *)item;
			const MatchShiftRotationThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			TargetLayer			=RThr->TargetLayer;
			SearchLittleInItem	=RThr->SearchLittleInItem;
			MatchingRate		=RThr->MatchingRate;

			SearchArea			=BItem->ParentArea	->SearchArea	;
			SearchAngle			=BItem->ParentArea	->SearchAngle	;
		}
	}
}

bool	MatchShiftRotationThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

	if(::Save(f,TargetLayer)==false)
		return false;
	if(::Save(f,SearchLittleInItem)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;

	if(::Save(f,SearchArea)==false)
		return false;
	if(::Save(f,SearchAngle)==false)
		return false;
	return true;
}
bool	MatchShiftRotationThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

	if(::Load(f,TargetLayer)==false)
		return false;
	if(::Load(f,SearchLittleInItem)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;

	if(::Load(f,SearchArea)==false)
		return false;
	if(::Load(f,SearchAngle)==false)
		return false;

	return true;
}

//=====================================================================================================
MatchShiftRotationReqTryThreshold::MatchShiftRotationReqTryThreshold(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	ItemID		=-1;
	AreaID		=-1;
	SearchArea			=0;	
	SearchAngle			=0;

}
bool	MatchShiftRotationReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	if(::Save(f,SearchArea)==false)
		return false;
	if(::Save(f,SearchAngle)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	MatchShiftRotationReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	if(::Load(f,SearchArea)==false)
		return false;
	if(::Load(f,SearchAngle)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

MatchShiftRotationSendTryThreshold::MatchShiftRotationSendTryThreshold(void)
{
	Result	=new ResultInItemPI();
	ResultDx	=0;
	ResultDy	=0;
	ResultAngle	=0;	//Calculated position
	ResultMatchingRate	=0;
}
MatchShiftRotationSendTryThreshold::~MatchShiftRotationSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	MatchShiftRotationSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultDx	)==false)
		return false;
	if(::Save(f,ResultDy	)==false)
		return false;
	if(::Save(f,ResultAngle	)==false)
		return false;
	if(::Save(f,ResultMatchingRate	)==false)
		return false;
	return true;
}
bool	MatchShiftRotationSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ResultDx	)==false)
		return false;
	if(::Load(f,ResultDy	)==false)
		return false;
	if(::Load(f,ResultAngle	)==false)
		return false;
	if(::Load(f,ResultMatchingRate	)==false)
		return false;
	return true;
}

void	MatchShiftRotationSendTryThreshold::ConstructList(MatchShiftRotationReqTryThreshold *reqPacket,MatchShiftRotationBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	MatchShiftRotationInPage	*Ap=(MatchShiftRotationInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		XMatchShiftRotationArea	*a;
		if(reqPacket->AreaID>=0)
			a=Ap->GetMatchShiftRotationArea(reqPacket->AreaID);
		else
			a=Ap->Areas.GetFirst();
		if(a!=NULL){
			MatchShiftRotationItem	*BI=(MatchShiftRotationItem *)Ap->SearchIDItem(reqPacket->ItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				swap(reqPacket->Threshold.GetThresholdW()->TargetLayer			,BI->GetThresholdW()->TargetLayer		);
				swap(reqPacket->Threshold.GetThresholdW()->SearchLittleInItem	,BI->GetThresholdW()->SearchLittleInItem);
				swap(reqPacket->Threshold.GetThresholdW()->MatchingRate			,BI->GetThresholdW()->MatchingRate		);			
				int	SearchArea	=a->SearchArea	;
				int	SearchAngle	=a->SearchAngle	;
				a->SearchArea	=reqPacket->SearchArea;
				a->SearchAngle	=reqPacket->SearchAngle;
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				a->ExecuteInitialAfterEdit(EInfo);
				BI->ExecuteInitialAfterEdit (0,0,Result,EInfo);
				a->ExecuteStartByInspection();
				BI->ExecuteStartByInspection(0,0,Result);

				a->ExecuteProcessing(Ap->GetFirstData());
				BI->ExecuteProcessing		 (0,0,Result);

				a->SearchArea	=SearchArea	;
				a->SearchAngle	=SearchAngle;
				swap(reqPacket->Threshold.GetThresholdW()->TargetLayer			,BI->GetThresholdW()->TargetLayer		);
				swap(reqPacket->Threshold.GetThresholdW()->SearchLittleInItem	,BI->GetThresholdW()->SearchLittleInItem);
				swap(reqPacket->Threshold.GetThresholdW()->MatchingRate			,BI->GetThresholdW()->MatchingRate		);			

				ResultDx			=a->ResultDx;
				ResultDy			=a->ResultDy;
				ResultAngle			=a->ResultAngle;
				ResultMatchingRate	=BI->MatchingRate;
			}
		}
	}
	Result->SetAddedData(NULL,0);
}


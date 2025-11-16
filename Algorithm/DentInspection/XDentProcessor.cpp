/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Dent\XDentProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDentInspection.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XDentLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XCriticalFunc.h"


DentThresholdReq::DentThresholdReq(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Layer		=0;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	DentThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	DentThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
DentThresholdSend::DentThresholdSend(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Layer		=0;
	Mastered	=true;
	Dx=0;
	Dy=0;

	Difference	=0;
	BandWidth	=0;
}

void	DentThresholdSend::ConstructList(DentThresholdReq *reqPacket,DentBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Layer		=reqPacket->Layer;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI	*>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				DentItem	*BItem=(DentItem *)item;

				const	DentThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				Difference	=RThr->Difference	;
				BandWidth	=RThr->BandWidth	;
			}
		}
	}
}

bool	DentThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

	if(::Save(f,Difference)==false)
		return false;
	if(::Save(f,BandWidth)==false)
		return false;

	return true;
}
bool	DentThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

	if(::Load(f,Difference)==false)
		return false;
	if(::Load(f,BandWidth)==false)
		return false;

	return true;
}

//=====================================================================================================
DentReqTryThreshold::DentReqTryThreshold(void)
{
	GlobalPage	=-1;
	Layer		=0;
	BlockItemID	=-1;
}
bool	DentReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	DentReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

DentSendTryThreshold::DentSendTryThreshold(void)
{
	Result	=new ResultInItemPLI();
	ResultNGSize		=0;
}
DentSendTryThreshold::~DentSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	DentSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultNGSize	)==false)
		return false;

	return true;
}
bool	DentSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ResultNGSize	)==false)
		return false;

	return true;
}

void	DentSendTryThreshold::ConstructList(DentReqTryThreshold *reqPacket,DentBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	DentInPage	*Ap=(DentInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		DentInLayer	*AL=((DentInLayer *)Ap->GetLayerData(reqPacket->Layer));
		if(AL!=NULL){
			DentItem	*BI=(DentItem *)AL->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				reqPacket->Threshold.ExecuteInitialAfterEdit	(0,0,Result,EInfo);
				reqPacket->Threshold.ExecuteStartByInspection	(0,0,Result);
				reqPacket->Threshold.AVector	=BI->AVector;
				reqPacket->Threshold.ExecuteProcessing			(0,0,Result);

				ResultNGSize		=reqPacket->Threshold.ResultMaxNGSize		;
			}
		}
	}
	Result->SetAddedData(NULL,0);
}

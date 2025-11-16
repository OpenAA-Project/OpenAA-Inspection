/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\HoleWallInspection\XHoleWallProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XHoleWallInspection.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XHoleWallLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XCriticalFunc.h"

//=====================================================================================

HoleWallThresholdReq::HoleWallThresholdReq(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Layer		=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	HoleWallThresholdReq::Save(QIODevice *f)
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
bool	HoleWallThresholdReq::Load(QIODevice *f)
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
HoleWallThresholdSend::HoleWallThresholdSend(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;

	NGSize		=0;
	SearchDot	=0;
}

void	HoleWallThresholdSend::ConstructList(HoleWallThresholdReq *reqPacket,HoleWallBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				HoleWallItem	*BItem=(HoleWallItem *)item;
				const HoleWallThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				NGSize		=RThr->NGSize; 
				SearchDot	=RThr->SearchDot; 
			}
		}
	}
}

bool	HoleWallThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;

    if(::Save(f,NGSize)==false)
		return false;
    if(::Save(f,SearchDot)==false)
		return false;

	return true;
}
bool	HoleWallThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;

    if(::Load(f,NGSize)==false)
		return false;
    if(::Load(f,SearchDot)==false)
		return false;

	return true;
}

//=====================================================================================================
HoleWallReqTryThreshold::HoleWallReqTryThreshold(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
}
bool	HoleWallReqTryThreshold::Save(QIODevice *f)
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
bool	HoleWallReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
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

HoleWallSendTryThreshold::HoleWallSendTryThreshold(void)
{
	Result	=new ResultInItemPLI();
	NGSize	=0;
}
HoleWallSendTryThreshold::HoleWallSendTryThreshold(const HoleWallSendTryThreshold &src)
{
	Result	=new ResultInItemPLI();
	NGSize	=src.NGSize;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
}
HoleWallSendTryThreshold::~HoleWallSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
HoleWallSendTryThreshold	&HoleWallSendTryThreshold::operator=(const HoleWallSendTryThreshold &src)
{
	Result	=new ResultInItemPLI();

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==false)
		return *this;
	Buff.seek(0);
	if(Result->Load(&Buff)==false)
		return *this;
	NGSize	=src.NGSize;
	return *this;
}
bool	HoleWallSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,NGSize	)==false)
		return false;
	return true;
}
bool	HoleWallSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,NGSize	)==false)
		return false;

	return true;
}

void	HoleWallSendTryThreshold::ConstructList(HoleWallReqTryThreshold *reqPacket,HoleWallBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	HoleWallInPage	*Ap=(HoleWallInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(reqPacket->Layer));
		if(AL!=NULL){
			HoleWallItem	*BI=(HoleWallItem *)AL->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				const HoleWallThreshold	*RThr=BI->GetThresholdR(Ap->GetLayersBase());
				reqPacket->Threshold.GetThresholdW()->NGSize			=RThr->NGSize;
				reqPacket->Threshold.GetThresholdW()->SearchDot			=RThr->NGSize;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				reqPacket->Threshold.ExecuteInitialAfterEdit (0,0,Result,EInfo);
				reqPacket->Threshold.ExecuteStartByInspection(0,0,Result);
				reqPacket->Threshold.AVector	=BI->AVector;
				reqPacket->Threshold.ExecutePreProcessing	 (0,0,Result);
				reqPacket->Threshold.ExecuteProcessing		 (0,0,Result);
			}
		}
	}
	Result->SetAddedData(NULL,0);

	NGSize		=Result->GetResult1();
}


void	HoleWallChangeShift::Reflect(HoleWallBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(Layer));
		if(AL!=NULL){
			AlgorithmItemRoot	*item	=AL->SearchIDItem(BlockItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	HoleWallChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	HoleWallChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


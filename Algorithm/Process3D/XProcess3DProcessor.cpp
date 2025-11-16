/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Process3D\XProcess3DProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XProcess3D.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XProcess3DLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
//#include "XPropertyProcess3DPacket.h"
//#include "TrueColorChangeCreateBlockForm.h"
#include "XMaskingFromGeneral.h"
#include "XCriticalFunc.h"


Process3DThresholdReq::Process3DThresholdReq(void)
{
	GlobalPage	=-1;
	BlockItemID	=-1;
	Layer		=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	Process3DThresholdReq::Save(QIODevice *f)
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
bool	Process3DThresholdReq::Load(QIODevice *f)
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
Process3DThresholdSend::Process3DThresholdSend(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;

	BaseCycleDot	=0;
	HeightPerShift	=0;
	LargeTilt		=0;
	LargeFlatness	=0;
	SmallFlatness	=0;
	SmallAreaSize	=0;
}

void	Process3DThresholdSend::ConstructList(Process3DThresholdReq *reqPacket,Process3DBase *Base)
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
				Process3DItem	*BItem=(Process3DItem *)item;
				const Process3DThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				BaseCycleDot	=RThr->BaseCycleDot	;
				HeightPerShift	=RThr->HeightPerShift	;
				LargeTilt		=RThr->LargeTilt		;
				LargeFlatness	=RThr->LargeFlatness	;
				SmallFlatness	=RThr->SmallFlatness	;
				SmallAreaSize	=RThr->SmallAreaSize	;
			}
		}
	}
}

bool	Process3DThresholdSend::Save(QIODevice *f)
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

	if(::Save(f,BaseCycleDot)==false)
		return false;
	if(::Save(f,HeightPerShift)==false)
		return false;

	if(::Save(f,LargeTilt)==false)
		return false;
	if(::Save(f,LargeFlatness)==false)
		return false;
	if(::Save(f,SmallFlatness)==false)
		return false;
	if(::Save(f,SmallAreaSize)==false)
		return false;

	return true;
}
bool	Process3DThresholdSend::Load(QIODevice *f)
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

	if(::Load(f,BaseCycleDot)==false)
		return false;
	if(::Load(f,HeightPerShift)==false)
		return false;

	if(::Load(f,LargeTilt)==false)
		return false;
	if(::Load(f,LargeFlatness)==false)
		return false;
	if(::Load(f,SmallFlatness)==false)
		return false;
	if(::Load(f,SmallAreaSize)==false)
		return false;

	return true;
}

//=====================================================================================================
Process3DReqTryThreshold::Process3DReqTryThreshold(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
}
bool	Process3DReqTryThreshold::Save(QIODevice *f)
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
bool	Process3DReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
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

Process3DSendTryThreshold::Process3DSendTryThreshold(void)
{
	Result	=new ResultInItemPLI();
	ResultLargeTile		=0;
	ResultLargeFlatness	=0;
	ResultSmallFlatness	=0;
}
Process3DSendTryThreshold::~Process3DSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	Process3DSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ResultLargeTile	)==false)
		return false;
	if(::Save(f,ResultLargeFlatness	)==false)
		return false;
	if(::Save(f,ResultSmallFlatness	)==false)
		return false;

	return true;
}
bool	Process3DSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ResultLargeTile	)==false)
		return false;
	if(::Load(f,ResultLargeFlatness	)==false)
		return false;
	if(::Load(f,ResultSmallFlatness	)==false)
		return false;
	return true;
}

void	Process3DSendTryThreshold::ConstructList(Process3DReqTryThreshold *reqPacket,Process3DBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	Process3DInPage	*Ap=(Process3DInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*AL=dynamic_cast<AlgorithmInLayerPLI *>(Ap->GetLayerData(reqPacket->Layer));
		if(AL!=NULL){
			Process3DItem	*BI=(Process3DItem *)AL->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				ExecuteInitialAfterEditInfo EInfo;
				EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				reqPacket->Threshold.ExecuteInitialAfterEdit (0,0,Result,EInfo);
				reqPacket->Threshold.ExecuteStartByInspection(0,0,Result);
				reqPacket->Threshold.AVector							=BI->AVector;
				reqPacket->Threshold.ExecutePreProcessing	 (0,0,Result);

				ResultLargeTile		=reqPacket->Threshold.ResultLargeTile		;
				ResultLargeFlatness	=reqPacket->Threshold.ResultLargeFlatness	;
				ResultSmallFlatness	=reqPacket->Threshold.ResultSmallFlatness	;
			}
		}
	}
	Result->SetAddedData(NULL,0);
}

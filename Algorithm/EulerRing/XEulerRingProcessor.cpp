/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRing\XEulerRingProcessor.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XEulerRing.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XPointer.h"
#include "XEulerRingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XCriticalFunc.h"

//=====================================================================================

EulerRingHistogramListReq::EulerRingHistogramListReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	EulerRingHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	EulerRingHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


EulerRingHistogramListSend::EulerRingHistogramListSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
void	EulerRingHistogramListSend::ConstructList(EulerRingHistogramListReq *reqPacket ,EulerRingBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			try{
				RGBStock Stocker;
				ImagePointerContainer Images;
				Ap->GetDataInPage()->GetTargetImages(Images);
				item->GetArea().CreateRGBStock(Images, Stocker);
				ColorSphere	*b=new ColorSphere();
				b->Create(Stocker);
				MasterColor.AddBase(b);
			}
			catch(...){}
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				if(Rp!=NULL){
					ResultInItemPI		*rItem=Rp->GetItem(item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						RGBStock Stocker;
						ImagePointerContainer Images;
						Ap->GetDataInPage()->GetTargetImages(Images);
						item->GetArea().CreateRGBStock(Images, Stocker ,sx,sy);
						ColorSphere	*b=new ColorSphere();
						b->Create(Stocker);
						TargetColor.AddBase(b);
					}
					else{
						RGBStock Stocker;
						ImagePointerContainer Images;
						Ap->GetDataInPage()->GetTargetImages(Images);
						item->GetArea().CreateRGBStock(Images, Stocker);
						ColorSphere	*b=new ColorSphere();
						b->Create(Stocker);
						TargetColor.AddBase(b);
					}
				}
			}
		}
	}
}

bool	EulerRingHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(MasterColor.Save(f)==false)
		return false;
	if(TargetColor.Save(f)==false)
		return false;
	return true;
}
bool	EulerRingHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(MasterColor.Load(f)==false)
		return false;
	if(TargetColor.Load(f)==false)
		return false;
	return true;
}

EulerRingThresholdReq::EulerRingThresholdReq(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	EulerRingThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	EulerRingThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}
EulerRingThresholdSend::EulerRingThresholdSend(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	Multiplier=1.0;
}

void	EulerRingThresholdSend::ConstructList(EulerRingThresholdReq *reqPacket,EulerRingBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			EulerRingItem	*BItem=(EulerRingItem *)item;
			InspectionColor	=*((ColorLogic *)&BItem->GetThresholdR(Ap->GetLayersBase())->InspectionColor);
			AbsInspectionColor=InspectionColor;

			Multiplier=BItem->EnAverage(dx,dy ,AbsInspectionColor);
			BItem->EnAverage(dx,dy ,AbsInspectionColor);
		}
	}
}

bool	EulerRingThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(InspectionColor.Save(f)==false)
		return false;
	if(AbsInspectionColor.Save(f)==false)
		return false;
	if(::Save(f,Multiplier)==false)
		return false;
	return true;
}
bool	EulerRingThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(InspectionColor.Load(f)==false)
		return false;
	if(AbsInspectionColor.Load(f)==false)
		return false;
	if(::Load(f,Multiplier)==false)
		return false;
	return true;
}

//=====================================================================================================
EulerRingReqTryThreshold::EulerRingReqTryThreshold(void)
{
	GlobalPage=-1;
	BlockItemID=-1;
}
bool	EulerRingReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	EulerRingReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

EulerRingSendTryThreshold::EulerRingSendTryThreshold(void)
{
	Result		=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
}

bool	EulerRingSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,Result	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	return true;
}
bool	EulerRingSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,Result	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	return true;
}

void	EulerRingSendTryThreshold::ConstructList(EulerRingReqTryThreshold *reqPacket,EulerRingBase *Base)
{
	ResultInItemPI	Res;
	Res.SetAddedData(this,1,sizeof(this));
	EulerRingInPage	*BP=(EulerRingInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		EulerRingItem	*BI=(EulerRingItem *)BP->SearchIDItem(reqPacket->BlockItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			reqPacket->Threshold.AVector							=BI->AVector;
			reqPacket->Threshold.SetParent(BI->GetParent());
			reqPacket->Threshold.GetThresholdW()->InspectionColor.CreateTable(reqPacket->Threshold.GetThresholdW()->Mergin);
			reqPacket->Threshold.ExecuteProcessing(0,0,&Res);
		}
	}
	Res.SetAddedData(NULL,0);

	ResultMoveDx=Res.GetTotalShiftedX();
	ResultMoveDy=Res.GetTotalShiftedY();
}


void	EulerRingChangeShift::Reflect(EulerRingBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(BlockItemID);
		if(item!=NULL){
			if(item->GetCurrentResult()!=NULL){
				item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
			}
		}
	}
}

bool	EulerRingChangeShift::Save(QIODevice *f)
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
bool	EulerRingChangeShift::Load(QIODevice *f)
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


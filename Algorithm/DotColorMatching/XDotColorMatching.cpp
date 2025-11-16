#include "DotColorMatchingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DotColorMatchingInspection\XDotColorMatching.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XCrossObj.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XCriticalFunc.h"
#include "XLearningRegist.h"
#include "XAlgorithmLibrary.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

DotColorMatchingHistogramListReq::DotColorMatchingHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	DotColorMatchingItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	DotColorMatchingHistogramListReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	DotColorMatchingHistogramListReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}


DotColorMatchingHistogramListSend::DotColorMatchingHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	DotColorMatchingItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListTargetB,0,sizeof(ListTargetB));
	CenterBrightR		=0;
	CenterBrightG		=0;
	CenterBrightB		=0;
	CenterTargetBrightR	=0;
	CenterTargetBrightG	=0;
	CenterTargetBrightB	=0;
}
void	DotColorMatchingHistogramListSend::ConstructList(DotColorMatchingHistogramListReq *reqPacket ,DotColorMatchingBase *Base)
{
	memset(ListMasterR,0,sizeof(ListMasterR));
	memset(ListMasterG,0,sizeof(ListMasterG));
	memset(ListMasterB,0,sizeof(ListMasterB));
	memset(ListTargetR,0,sizeof(ListTargetR));
	memset(ListTargetG,0,sizeof(ListTargetG));
	memset(ListTargetB,0,sizeof(ListTargetB));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	DotColorMatchingItemID	=reqPacket->DotColorMatchingItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		int	LayerNumb=Ap->GetLayerNumb();
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(DotColorMatchingItemID);
		if(item!=NULL){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem*>(item);
			bool	BuiltList=false;
			if(BuiltList==false){
				ImagePointerContainer ImageList;			
				Item->GetMasterBuffList(ImageList);
				item->GetArea().MakeBrightList(ListMasterR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],0 ,0);
				if(LayerNumb>=2){
					item->GetArea().MakeBrightList(ListMasterG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],0 ,0);
				}
				if(LayerNumb>=3){
					item->GetArea().MakeBrightList(ListMasterB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],0 ,0);
				}
			}
		
			ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
			if(DRes!=NULL){
				ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
				ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
				ResultInPagePI	*Rp=dynamic_cast<ResultInPagePI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
				ImagePointerContainer ImageList;
				Item->GetTargetBuffList(ImageList);
				if(Rp!=NULL){
					ResultInItemPI		*rItem=Rp->SearchItem(Item->GetID());
					if(rItem!=NULL){
						int	sx,sy;
						rItem->GetTotalShifted(sx,sy);
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],sx ,sy);
						if(LayerNumb>=2){
							item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],sx ,sy);
						}
						if(LayerNumb>=3){
							item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],sx ,sy);
						}
					}
					else{
						item->GetArea().MakeBrightList(ListTargetR ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[0],0 ,0);
						if(LayerNumb>=2){
							item->GetArea().MakeBrightList(ListTargetG ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[1],0 ,0);
						}
						if(LayerNumb>=3){
							item->GetArea().MakeBrightList(ListTargetB ,item->GetDotPerLine(),item->GetMaxLines(),*ImageList[2],0 ,0);
						}
					}
				}
			}
			CenterBrightR		=Item->CenterBrightR;
			CenterBrightG		=Item->CenterBrightG;
			CenterBrightB		=Item->CenterBrightB;
			CenterTargetBrightR	=Item->CenterTargetBrightR;
			CenterTargetBrightG	=Item->CenterTargetBrightG;
			CenterTargetBrightB	=Item->CenterTargetBrightB;
		}
	}
}

bool	DotColorMatchingHistogramListSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(f->write((const char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->write((const char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->write((const char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->write((const char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->write((const char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->write((const char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	if(::Save(f,CenterBrightR)==false)
		return false;
	if(::Save(f,CenterBrightG)==false)
		return false;
	if(::Save(f,CenterBrightB)==false)
		return false;
	if(::Save(f,CenterTargetBrightR)==false)
		return false;
	if(::Save(f,CenterTargetBrightG)==false)
		return false;
	if(::Save(f,CenterTargetBrightB)==false)
		return false;
	return true;
}
bool	DotColorMatchingHistogramListSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(f->read((char *)ListMasterR,sizeof(ListMasterR))!=sizeof(ListMasterR))
		return false;
	if(f->read((char *)ListMasterG,sizeof(ListMasterG))!=sizeof(ListMasterG))
		return false;
	if(f->read((char *)ListMasterB,sizeof(ListMasterB))!=sizeof(ListMasterB))
		return false;
	if(f->read((char *)ListTargetR,sizeof(ListTargetR))!=sizeof(ListTargetR))
		return false;
	if(f->read((char *)ListTargetG,sizeof(ListTargetG))!=sizeof(ListTargetG))
		return false;
	if(f->read((char *)ListTargetB,sizeof(ListTargetB))!=sizeof(ListTargetB))
		return false;
	if(::Load(f,CenterBrightR)==false)
		return false;
	if(::Load(f,CenterBrightG)==false)
		return false;
	if(::Load(f,CenterBrightB)==false)
		return false;
	if(::Load(f,CenterTargetBrightR)==false)
		return false;
	if(::Load(f,CenterTargetBrightG)==false)
		return false;
	if(::Load(f,CenterTargetBrightB)==false)
		return false;
	return true;
}
DotColorMatchingThresholdReq::DotColorMatchingThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	DotColorMatchingItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	DotColorMatchingThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	DotColorMatchingThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

DotColorMatchingThresholdSend::DotColorMatchingThresholdSend(void)
{
	ThresholdValues.GlobalPage=-1;
	ThresholdValues.Layer=-1;
	ThresholdValues.DotColorMatchingItemID=-1;
	ThresholdValues.Mastered=true;
	ThresholdValues.Dx=0;
	ThresholdValues.Dy=0;

	ThresholdValues.CenterBrightR		=0;
	ThresholdValues.CenterBrightG		=0;
	ThresholdValues.CenterBrightB		=0;
	ThresholdValues.CenterTargetBrightR	=0;
	ThresholdValues.CenterTargetBrightG	=0;
	ThresholdValues.CenterTargetBrightB	=0;
	ThresholdValues.BrightWidthBRL		=0;
	ThresholdValues.BrightWidthBRH		=0;
	ThresholdValues.BrightWidthBGL		=0;
	ThresholdValues.BrightWidthBGH		=0;
	ThresholdValues.BrightWidthBBL		=0;
	ThresholdValues.BrightWidthBBH		=0;

	ThresholdValues.BrightWidthNRL		=0;
	ThresholdValues.BrightWidthNRH		=0;
	ThresholdValues.BrightWidthNGL		=0;
	ThresholdValues.BrightWidthNGH		=0;
	ThresholdValues.BrightWidthNBL		=0;
	ThresholdValues.BrightWidthNBH		=0;

	ThresholdValues.TargetSDRL			=0;
	ThresholdValues.TargetSDRH			=0;
	ThresholdValues.TargetSDGL			=0;
	ThresholdValues.TargetSDGH			=0;
	ThresholdValues.TargetSDBL			=0;
	ThresholdValues.TargetSDBH			=0;

	ThresholdValues.AbsBrightWidthBRL	=0;
	ThresholdValues.AbsBrightWidthBRH	=0;
	ThresholdValues.AbsBrightWidthBGL	=0;
	ThresholdValues.AbsBrightWidthBGH	=0;
	ThresholdValues.AbsBrightWidthBBL	=0;
	ThresholdValues.AbsBrightWidthBBH	=0;

	ThresholdValues.OrgBrightWidthBRL	=0;
	ThresholdValues.OrgBrightWidthBRH	=0;
	ThresholdValues.OrgBrightWidthBGL	=0;
	ThresholdValues.OrgBrightWidthBGH	=0;
	ThresholdValues.OrgBrightWidthBBL	=0;
	ThresholdValues.OrgBrightWidthBBH	=0;
	ThresholdValues.OrgOKDotB			=0;

	ThresholdValues.AbsBrightWidthNRL	=0;
	ThresholdValues.AbsBrightWidthNRH	=0;
	ThresholdValues.AbsBrightWidthNGL	=0;
	ThresholdValues.AbsBrightWidthNGH	=0;
	ThresholdValues.AbsBrightWidthNBL	=0;
	ThresholdValues.AbsBrightWidthNBH	=0;

	ThresholdValues.OrgBrightWidthNRL	=0;
	ThresholdValues.OrgBrightWidthNRH	=0;
	ThresholdValues.OrgBrightWidthNGL	=0;
	ThresholdValues.OrgBrightWidthNGH	=0;
	ThresholdValues.OrgBrightWidthNBL	=0;
	ThresholdValues.OrgBrightWidthNBH	=0;
	ThresholdValues.OrgOKDotN			=0;
}

void	DotColorMatchingThresholdSend::ConstructList(DotColorMatchingThresholdReq *reqPacket,DotColorMatchingBase *Base)
{
	ThresholdValues.GlobalPage	=reqPacket->GlobalPage;
	ThresholdValues.Layer		=reqPacket->Layer;
	ThresholdValues.DotColorMatchingItemID	=reqPacket->DotColorMatchingItemID;
	ThresholdValues.Mastered	=reqPacket->Mastered;
	ThresholdValues.Dx			=reqPacket->Dx;
	ThresholdValues.Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(ThresholdValues.GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ThresholdValues.DotColorMatchingItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}

			DotColorMatchingItem	*BItem=(DotColorMatchingItem *)item;
			ImagePointerContainer ImageList;
			BItem->GetMasterBuffList(ImageList);
			int	LayerNumb=Base->GetLayersBase()->GetLayerNumb(localPage);
			if(BItem->CenterBrightR==0){
				BItem->CenterBrightR=BItem->CalcCenterBright(*ImageList[0],0,0,BItem->MasterSDRL,BItem->MasterSDRH);
				BItem->CenterTargetBrightR=BItem->CenterBrightR;
			}
			if(BItem->CenterBrightG==0 && LayerNumb>=2){
				BItem->CenterBrightG=BItem->CalcCenterBright(*ImageList[1],0,0,BItem->MasterSDGL,BItem->MasterSDGH);
				BItem->CenterTargetBrightG=BItem->CenterBrightG;
			}
			if(BItem->CenterBrightB==0 && LayerNumb>=3){
				BItem->CenterBrightB=BItem->CalcCenterBright(*ImageList[2],0,0,BItem->MasterSDBL,BItem->MasterSDBH);
				BItem->CenterTargetBrightB=BItem->CenterBrightB;
			}
			const	DotColorMatchingThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
			ThresholdValues.CenterBrightR	=BItem->CenterBrightR;
			ThresholdValues.CenterBrightG	=BItem->CenterBrightG;
			ThresholdValues.CenterBrightB	=BItem->CenterBrightB;
			ThresholdValues.BrightWidthBRL	=RThr->Broad.BrightWidthRL;
			ThresholdValues.BrightWidthBRH	=RThr->Broad.BrightWidthRH;
			ThresholdValues.BrightWidthBGL	=RThr->Broad.BrightWidthGL;
			ThresholdValues.BrightWidthBGH	=RThr->Broad.BrightWidthGH;
			ThresholdValues.BrightWidthBBL	=RThr->Broad.BrightWidthBL;
			ThresholdValues.BrightWidthBBH	=RThr->Broad.BrightWidthBH;

			ThresholdValues.OrgBrightWidthBRL	=RThr->Broad.OrgBrightWidthRL;
			ThresholdValues.OrgBrightWidthBRH	=RThr->Broad.OrgBrightWidthRH;
			ThresholdValues.OrgBrightWidthBGL	=RThr->Broad.OrgBrightWidthGL;
			ThresholdValues.OrgBrightWidthBGH	=RThr->Broad.OrgBrightWidthGH;
			ThresholdValues.OrgBrightWidthBBL	=RThr->Broad.OrgBrightWidthBL;
			ThresholdValues.OrgBrightWidthBBH	=RThr->Broad.OrgBrightWidthBH;
			ThresholdValues.OrgOKDotB			=RThr->Broad.OrgOKDot		;

			ThresholdValues.BrightWidthNRL	=RThr->Narrow.BrightWidthRL;
			ThresholdValues.BrightWidthNRH	=RThr->Narrow.BrightWidthRH;
			ThresholdValues.BrightWidthNGL	=RThr->Narrow.BrightWidthGL;
			ThresholdValues.BrightWidthNGH	=RThr->Narrow.BrightWidthGH;
			ThresholdValues.BrightWidthNBL	=RThr->Narrow.BrightWidthBL;
			ThresholdValues.BrightWidthNBH	=RThr->Narrow.BrightWidthBH;

			ThresholdValues.OrgBrightWidthNRL	=RThr->Narrow.OrgBrightWidthRL;
			ThresholdValues.OrgBrightWidthNRH	=RThr->Narrow.OrgBrightWidthRH;
			ThresholdValues.OrgBrightWidthNGL	=RThr->Narrow.OrgBrightWidthGL;
			ThresholdValues.OrgBrightWidthNGH	=RThr->Narrow.OrgBrightWidthGH;
			ThresholdValues.OrgBrightWidthNBL	=RThr->Narrow.OrgBrightWidthBL;
			ThresholdValues.OrgBrightWidthNBH	=RThr->Narrow.OrgBrightWidthBH;
			ThresholdValues.OrgOKDotN			=RThr->Narrow.OrgOKDot		;


			int	TmpBrightWidthBRL=ThresholdValues.BrightWidthBRL;
			int	TmpBrightWidthBRH=ThresholdValues.BrightWidthBRH;
			int	TmpBrightWidthBGL=ThresholdValues.BrightWidthBGL;
			int	TmpBrightWidthBGH=ThresholdValues.BrightWidthBGH;
			int	TmpBrightWidthBBL=ThresholdValues.BrightWidthBBL;
			int	TmpBrightWidthBBH=ThresholdValues.BrightWidthBBH;

			int	TmpBrightWidthNRL=ThresholdValues.BrightWidthNRL;
			int	TmpBrightWidthNRH=ThresholdValues.BrightWidthNRH;
			int	TmpBrightWidthNGL=ThresholdValues.BrightWidthNGL;
			int	TmpBrightWidthNGH=ThresholdValues.BrightWidthNGH;
			int	TmpBrightWidthNBL=ThresholdValues.BrightWidthNBL;
			int	TmpBrightWidthNBH=ThresholdValues.BrightWidthNBH;

			ThresholdValues.AbsBrightWidthBRL=ThresholdValues.CenterBrightR-TmpBrightWidthBRL;
			ThresholdValues.AbsBrightWidthBRH=ThresholdValues.CenterBrightR+TmpBrightWidthBRH;
			ThresholdValues.AbsBrightWidthBGL=ThresholdValues.CenterBrightG-TmpBrightWidthBGL;
			ThresholdValues.AbsBrightWidthBGH=ThresholdValues.CenterBrightG+TmpBrightWidthBGH;
			ThresholdValues.AbsBrightWidthBBL=ThresholdValues.CenterBrightB-TmpBrightWidthBBL;
			ThresholdValues.AbsBrightWidthBBH=ThresholdValues.CenterBrightB+TmpBrightWidthBBH;

			ThresholdValues.AbsBrightWidthNRL=ThresholdValues.CenterBrightR-TmpBrightWidthNRL;
			ThresholdValues.AbsBrightWidthNRH=ThresholdValues.CenterBrightR+TmpBrightWidthNRH;
			ThresholdValues.AbsBrightWidthNGL=ThresholdValues.CenterBrightG-TmpBrightWidthNGL;
			ThresholdValues.AbsBrightWidthNGH=ThresholdValues.CenterBrightG+TmpBrightWidthNGH;
			ThresholdValues.AbsBrightWidthNBL=ThresholdValues.CenterBrightB-TmpBrightWidthNBL;
			ThresholdValues.AbsBrightWidthNBH=ThresholdValues.CenterBrightB+TmpBrightWidthNBH;
			
			int	iAbsBBrightWidthBRL=ThresholdValues.AbsBrightWidthBRL;
			int	iAbsBBrightWidthBRH=ThresholdValues.AbsBrightWidthBRH;
			int	iAbsBBrightWidthBGL=ThresholdValues.AbsBrightWidthBGL;
			int	iAbsBBrightWidthBGH=ThresholdValues.AbsBrightWidthBGH;
			int	iAbsBBrightWidthBBL=ThresholdValues.AbsBrightWidthBBL;
			int	iAbsBBrightWidthBBH=ThresholdValues.AbsBrightWidthBBH;
			ThresholdValues.AbsBrightWidthBRL	=iAbsBBrightWidthBRL;
			ThresholdValues.AbsBrightWidthBRH	=iAbsBBrightWidthBRH;
			ThresholdValues.AbsBrightWidthBGL	=iAbsBBrightWidthBGL;
			ThresholdValues.AbsBrightWidthBGH	=iAbsBBrightWidthBGH;
			ThresholdValues.AbsBrightWidthBBL	=iAbsBBrightWidthBBL;
			ThresholdValues.AbsBrightWidthBBH	=iAbsBBrightWidthBBH;
			
			int	iAbsBBrightWidthNRL=ThresholdValues.AbsBrightWidthNRL;
			int	iAbsBBrightWidthNRH=ThresholdValues.AbsBrightWidthNRH;
			int	iAbsBBrightWidthNGL=ThresholdValues.AbsBrightWidthNGL;
			int	iAbsBBrightWidthNGH=ThresholdValues.AbsBrightWidthNGH;
			int	iAbsBBrightWidthNBL=ThresholdValues.AbsBrightWidthNBL;
			int	iAbsBBrightWidthNBH=ThresholdValues.AbsBrightWidthNBH;
			ThresholdValues.AbsBrightWidthNRL	=iAbsBBrightWidthNRL;
			ThresholdValues.AbsBrightWidthNRH	=iAbsBBrightWidthNRH;
			ThresholdValues.AbsBrightWidthNGL	=iAbsBBrightWidthNGL;
			ThresholdValues.AbsBrightWidthNGH	=iAbsBBrightWidthNGH;
			ThresholdValues.AbsBrightWidthNBL	=iAbsBBrightWidthNBL;
			ThresholdValues.AbsBrightWidthNBH	=iAbsBBrightWidthNBH;
			
			BItem->GetTargetBuffList(ImageList);
			ThresholdValues.CenterTargetBrightR=BItem->CalcCenterBright(*ImageList[0],dx,dy,ThresholdValues.TargetSDRL,ThresholdValues.TargetSDRH);
			if(LayerNumb>=2){
				ThresholdValues.CenterTargetBrightG=BItem->CalcCenterBright(*ImageList[1],dx,dy,ThresholdValues.TargetSDGL,ThresholdValues.TargetSDGH);
			}
			if(LayerNumb>=3){
				ThresholdValues.CenterTargetBrightB=BItem->CalcCenterBright(*ImageList[2],dx,dy,ThresholdValues.TargetSDBL,ThresholdValues.TargetSDBH);
			}
		}
	}
}

bool	DotColorMatchingThresholdSend::Save(QIODevice *f)
{
	if(f->write((const char *)&ThresholdValues,sizeof(ThresholdValues))!=sizeof(ThresholdValues))
		return false;

	return true;
}
bool	DotColorMatchingThresholdSend::Load(QIODevice *f)
{
	if(f->read((char *)&ThresholdValues,sizeof(ThresholdValues))!=sizeof(ThresholdValues))
		return false;

	return true;
}

DotColorMatchingReqTryThreshold::DotColorMatchingReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	DotColorMatchingItemID=-1;
}
bool	DotColorMatchingReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	DotColorMatchingReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

DotColorMatchingSendTryThreshold::DotColorMatchingSendTryThreshold(void)
{
	Result					=new DotColorMatchingResultInItemPI();	//ResultInItemPI();
	NGDot					=0;
	NGLength				=0;
	ResultMoveDx			=0;
	ResultMoveDy			=0;
	Error					=0;
	CurrentRotationPatternNo=0;
	ScratchTableDim			=NULL;
	ScratchTableMasterDim	=NULL;
	ScratchTableDimLen		=0;
	ScratchResultAngle		=0;
	ScratchResultWidth		=0;
	ScratchResultPeakH		=0;
	ScratchResultPeakL		=0;
	ScratchResultStartDim	=0;
	ScratchResultEndDim		=0;
	ScratchResultVariety	=0;
	DeviationResultR		=0;
	DeviationResultG		=0;
	DeviationResultB		=0;
}

DotColorMatchingSendTryThreshold::DotColorMatchingSendTryThreshold(const DotColorMatchingSendTryThreshold &src)
{
	Result					=new DotColorMatchingResultInItemPI();	//ResultInItemPI();
	NGDot					=src.NGDot					;
	NGLength				=src.NGLength				;
	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;
	Error					=src.Error					;
	CurrentRotationPatternNo=src.CurrentRotationPatternNo;
	ScratchTableDimLen		=src.ScratchTableDimLen		;
	ScratchTableDim			=new struct	ScratchTable[ScratchTableDimLen];
	ScratchTableMasterDim	=new struct	ScratchTable[ScratchTableDimLen];
	memcpy(ScratchTableDim		,src.ScratchTableDim		,sizeof(struct ScratchTable)*ScratchTableDimLen);
	memcpy(ScratchTableMasterDim,src.ScratchTableMasterDim	,sizeof(struct ScratchTable)*ScratchTableDimLen);
	ScratchResultAngle		=src.ScratchResultAngle		;
	ScratchResultWidth		=src.ScratchResultWidth		;
	ScratchResultPeakH		=src.ScratchResultPeakH		;
	ScratchResultPeakL		=src.ScratchResultPeakL		;
	ScratchResultStartDim	=src.ScratchResultStartDim	;
	ScratchResultEndDim		=src.ScratchResultEndDim	;
	ScratchResultVariety	=src.ScratchResultVariety	;
	DeviationResultR		=src.DeviationResultR		;
	DeviationResultG		=src.DeviationResultG		;
	DeviationResultB		=src.DeviationResultB		;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
}

DotColorMatchingSendTryThreshold::~DotColorMatchingSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
		ScratchTableDim=NULL;
	}
	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
		ScratchTableMasterDim=NULL;
	}
	ScratchTableDimLen	=0;
}
	
DotColorMatchingSendTryThreshold &DotColorMatchingSendTryThreshold::operator=(const DotColorMatchingSendTryThreshold &src)
{
	NGDot					=src.NGDot					;
	NGLength				=src.NGLength				;
	ResultMoveDx			=src.ResultMoveDx			;
	ResultMoveDy			=src.ResultMoveDy			;
	Error					=src.Error					;
	CurrentRotationPatternNo=src.CurrentRotationPatternNo;
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
		ScratchTableDim=NULL;
	}
	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
		ScratchTableMasterDim=NULL;
	}
	ScratchTableDimLen		=src.ScratchTableDimLen		;
	ScratchTableDim			=new struct	ScratchTable[ScratchTableDimLen];
	ScratchTableMasterDim	=new struct	ScratchTable[ScratchTableDimLen];
	memcpy(ScratchTableDim		,src.ScratchTableDim		,sizeof(struct ScratchTable)*ScratchTableDimLen);
	memcpy(ScratchTableMasterDim,src.ScratchTableMasterDim	,sizeof(struct ScratchTable)*ScratchTableDimLen);
	ScratchResultAngle		=src.ScratchResultAngle		;
	ScratchResultWidth		=src.ScratchResultWidth		;
	ScratchResultPeakH		=src.ScratchResultPeakH		;
	ScratchResultPeakL		=src.ScratchResultPeakL		;
	ScratchResultStartDim	=src.ScratchResultStartDim	;
	ScratchResultEndDim		=src.ScratchResultEndDim	;
	ScratchResultVariety	=src.ScratchResultVariety	;
	DeviationResultR		=src.DeviationResultR		;
	DeviationResultG		=src.DeviationResultG		;
	DeviationResultB		=src.DeviationResultB		;

	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	if(src.Result->Save(&Buff)==true){
		Buff.seek(0);
		Result->Load(&Buff);
	}
	return *this;
}

bool	DotColorMatchingSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,NGDot	)==false)
		return false;
	if(::Save(f,NGLength)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(::Save(f,CurrentRotationPatternNo)==false)
		return false;
	if(::Save(f,ScratchTableDimLen)==false)
		return false;
	if(f->write((const char *)ScratchTableDim,ScratchTableDimLen*sizeof(ScratchTableDim[0]))!=ScratchTableDimLen*sizeof(ScratchTableDim[0]))
		return false;
	if(f->write((const char *)ScratchTableMasterDim,ScratchTableDimLen*sizeof(ScratchTableMasterDim[0]))!=ScratchTableDimLen*sizeof(ScratchTableMasterDim[0]))
		return false;
	if(::Save(f,ScratchResultAngle)==false)
		return false;
	if(::Save(f,ScratchResultWidth)==false)
		return false;
	if(::Save(f,ScratchResultPeakH)==false)
		return false;
	if(::Save(f,ScratchResultPeakL)==false)
		return false;
	if(::Save(f,ScratchResultStartDim)==false)
		return false;
	if(::Save(f,ScratchResultEndDim)==false)
		return false;
	if(::Save(f,ScratchResultVariety)==false)
		return false;

	if(::Save(f,DeviationResultR)==false)
		return false;
	if(::Save(f,DeviationResultG)==false)
		return false;
	if(::Save(f,DeviationResultB)==false)
		return false;
	return true;
}
bool	DotColorMatchingSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,NGDot	)==false)
		return false;
	if(::Load(f,NGLength)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(::Load(f,CurrentRotationPatternNo)==false)
		return false;
	if(::Load(f,ScratchTableDimLen)==false)
		return false;
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
	}
	ScratchTableDim=new struct	ScratchTable[ScratchTableDimLen];
	if(f->read((char *)ScratchTableDim,ScratchTableDimLen*sizeof(ScratchTableDim[0]))!=ScratchTableDimLen*sizeof(ScratchTableDim[0]))
		return false;

	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
	}
	ScratchTableMasterDim=new struct	ScratchTable[ScratchTableDimLen];
	if(f->read((char *)ScratchTableMasterDim,ScratchTableDimLen*sizeof(ScratchTableMasterDim[0]))!=ScratchTableDimLen*sizeof(ScratchTableMasterDim[0]))
		return false;

	if(::Load(f,ScratchResultAngle)==false)
		return false;
	if(::Load(f,ScratchResultWidth)==false)
		return false;
	if(::Load(f,ScratchResultPeakH)==false)
		return false;
	if(::Load(f,ScratchResultPeakL)==false)
		return false;
	if(::Load(f,ScratchResultStartDim)==false)
		return false;
	if(::Load(f,ScratchResultEndDim)==false)
		return false;
	if(::Load(f,ScratchResultVariety)==false)
		return false;

	if(::Load(f,DeviationResultR)==false)
		return false;
	if(::Load(f,DeviationResultG)==false)
		return false;
	if(::Load(f,DeviationResultB)==false)
		return false;
	return true;
}

void	DotColorMatchingSendTryThreshold::ConstructList(DotColorMatchingReqTryThreshold *reqPacket,DotColorMatchingBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	DotColorMatchingInPage		*BP=(DotColorMatchingInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		DotColorMatchingItem		*BI=(DotColorMatchingItem *)BP->SearchIDItem(reqPacket->DotColorMatchingItemID);
		if(BI!=NULL){
			Calc(&reqPacket->Threshold,BI,Base);
		}
	}
}
void	DotColorMatchingSendTryThreshold::Calc(DotColorMatchingItem *Target,DotColorMatchingItem *Src,DotColorMatchingBase *Base)
{
	DotColorMatchingInPage		*BP=(DotColorMatchingInPage *)Base->GetPageData(Src->GetPage());
	Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());

	int	SaveMaxInspectMilisec	=Base->GetParamGlobal()->MaxInspectMilisec;
	int	SaveMaxNGCountInBlock	=Base->MaxNGCountInBlock;
	int	SaveRetryItemCount		=Base->RetryItemCount;

	Base->GetParamGlobal()->MaxInspectMilisec	=99999999;
	Base->MaxNGCountInBlock						=9999;
	Base->RetryItemCount						=0;

	BP->RetryCounter=0;
	Target->SetParent(Src->GetParent());

	Target->SetLibID(Src->GetLibID());
	Target->SetMasterNo(Src->GetMasterNo());
	Target->CopyArea(*Src);
	DotColorMatchingThreshold			*WThr=Target->GetThresholdW();
	const	DotColorMatchingThreshold	*RThr=Src	->GetThresholdR();
	WThr->UseMaster2		=RThr->UseMaster2;

	ExecuteInitialAfterEditInfo DummyEInfo;
	DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
	Target->ExecuteInitialAfterEditByThread	(true,0,0,Result,DummyEInfo);
	Target->ExecuteInitialAfterEditPost(0,0,Result,DummyEInfo);

	Target->CenterBrightR		=Src->CenterBrightR;
	Target->CenterBrightG		=Src->CenterBrightG;
	Target->CenterBrightB		=Src->CenterBrightB;
	Target->AVector				=Src->AVector;
	Target->MatchingType		=Src->MatchingType;
	Target->SearchType			=Src->SearchType;
	Target->MaxCoefItem			=Src->MaxCoefItem;
	delete	[]Target->MasterPattern;
	Target->MasterPattern		=Src->MasterPattern;
	Target->PatternCount		=Src->PatternCount;
	Target->CurrentMasterPattern=Src->CurrentMasterPattern;
	Target->RotationDiv			=Src->RotationDiv;
	Target->MasterCx			=Src->MasterCx;
	Target->MasterCy			=Src->MasterCy;
	if(Target->Map!=NULL){
		DeleteMatrixBuff(Target->Map,Target->MapYLen);
	}
	if(Target->DummyMap!=NULL){
		DeleteMatrixBuff(Target->DummyMap,Target->MapYLen);
	}
	Target->Map					=Src->Map;
	Target->DummyMap			=Src->DummyMap;
	Target->MapXByte			=Src->MapXByte;
	Target->MapYLen				=Src->MapYLen;
	Target->OutlineArea			=Src->OutlineArea;
	Target->FoldingArea			=Src->FoldingArea;
	Target->OutlineBlock		=Src->OutlineBlock;
	Target->SetSubBlock(Src->GetSubBlock());

	WThr->AddedBrightness	=RThr->AddedBrightness;
	WThr->AddedOffset		=RThr->AddedOffset;
	WThr->AddedShift		=RThr->AddedShift;
	BP->GetDataInPage()->ClearNGCounterWithMutex();

	Target->ExecuteStartByInspection	(0,0,Result);
	Target->ExecuteProcessing			(10000,0,Result);
	CurrentRotationPatternNo	=Target->CurrentRotationPatternNo;

	Target->MasterPattern		=NULL;
	Target->Map					=NULL;
	Target->DummyMap			=NULL;
	ScratchTableDimLen	=Target->ScratchTableDimLen;
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
	}
	ScratchTableDim=new struct ScratchTable[ScratchTableDimLen];

	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
	}
	ScratchTableMasterDim=new struct ScratchTable[ScratchTableDimLen];

	memcpy(ScratchTableDim		,Target->ScratchTableDim		,ScratchTableDimLen*sizeof(ScratchTableDim[0]));
	memcpy(ScratchTableMasterDim,Target->ScratchTableMasterDim	,ScratchTableDimLen*sizeof(ScratchTableMasterDim[0]));
	ScratchResultAngle		=Target->ScratchResultAngle;
	ScratchResultWidth		=Target->ScratchResultWidth;
	ScratchResultPeakH		=Target->ScratchResultPeakH;
	ScratchResultPeakL		=Target->ScratchResultPeakL;
	ScratchResultStartDim	=Target->ScratchResultStartDim	;
	ScratchResultEndDim		=Target->ScratchResultEndDim	;
	ScratchResultVariety	=Target->ScratchResultVariety	;

	DeviationResultR	=Target->DeviationResultR;
	DeviationResultG	=Target->DeviationResultG;
	DeviationResultB	=Target->DeviationResultB;

	Result->SetAddedData(NULL,0);
	NGDot		=Result->GetResult2();
	NGLength	=Result->GetResultDouble();
	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();

	Base->GetParamGlobal()->MaxInspectMilisec	=SaveMaxInspectMilisec	;
	Base->MaxNGCountInBlock						=SaveMaxNGCountInBlock	;
	Base->RetryItemCount						=SaveRetryItemCount		;
}

DotColorMatchingReqRotationMasterImage::DotColorMatchingReqRotationMasterImage(void)
{
	GlobalPage=-1;
	DotColorMatchingItemID=-1;
	CurrentRotationPatternNo	=0;
}
bool	DotColorMatchingReqRotationMasterImage::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(::Save(f,CurrentRotationPatternNo)==false)
		return false;
	return true;
}
bool	DotColorMatchingReqRotationMasterImage::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(::Load(f,CurrentRotationPatternNo)==false)
		return false;
	return true;
}

DotColorMatchingSendRotationMasterImage::DotColorMatchingSendRotationMasterImage(void)
{
}

bool	DotColorMatchingSendRotationMasterImage::Save(QIODevice *f)
{
	if(::Save(f,MasterImage	)==false)
		return false;
	if(::Save(f,MasterImageSub	)==false)
		return false;
	return true;
}
bool	DotColorMatchingSendRotationMasterImage::Load(QIODevice *f)
{
	if(::Load(f,MasterImage	)==false)
		return false;
	if(::Load(f,MasterImageSub	)==false)
		return false;
	return true;
}

void	DotColorMatchingSendRotationMasterImage::ConstructList(DotColorMatchingReqRotationMasterImage *reqPacket,DotColorMatchingBase *Base)
{
	DotColorMatchingInPage		*BP=(DotColorMatchingInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		DotColorMatchingItem		*BI=(DotColorMatchingItem *)BP->SearchIDItem(reqPacket->DotColorMatchingItemID);
		if(BI!=NULL){
			RotationPattern	*Ptn=BI->GetRotationPattern(reqPacket->CurrentRotationPatternNo);
			if(Ptn!=NULL){
				MasterImage=Ptn->MakeImage();
				MasterImageSub=MasterImage;
				int	Px=BI->GetArea().GetMinX();
				int	Py=BI->GetArea().GetMinY();
				QPainter	Pnt(&MasterImageSub);
				for(SubtractItem *s=BI->GetSubBlock().GetFirst();s!=NULL;s=s->GetNext()){
					DotColorMatchingItem	*L=(DotColorMatchingItem *)s->IndexAfterEdit;
					RotationPattern	*SPtn=L->CurrentMasterPattern;
					if(L->CurrentMasterPattern!=NULL){
						QImage	SImg=SPtn->MakeImage();
						;;AddAlphaChannel(SImg,100);
						int	Sx=L->GetArea().GetMinX();	//+L->ResultDx;
						int	Sy=L->GetArea().GetMinY();	//+L->ResultDy;
						Pnt.drawImage(Sx-Px,Sy-Py,SImg);
						//MasterImageSub.save("Test.png");
						//SImg.save("Test2.png");
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
void	DotColorMatchingResultPosList::DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
												,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)
{
	int	R=ZoomRate;
	if(R<MinimumRadius){
		R=MinimumRadius;
	}
	int	R2=R+R;
	int	x1=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate-R;
	int y1=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate-R;
	int	x2=x1+R2;
	int	y2=y1+R2;
	QColor	RCol=QColor(255-qRed(Col),255-qGreen(Col),255-qBlue(Col));
	if(0<=x2 && x1<IData.width() && 0<=y2 && y1<IData.height()){
		if(ImportanceLevel<100){
			if(CircleWidth==0){
				if(DrawBlueNGMark==true){
					PData.setPen(RCol);
					PData.drawEllipse(x1-7,y1-7,R2+14,R2+14);
				}
				PData.setPen(QColor(Col));
				PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
				PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
				PData.drawEllipse(x1,y1,R2,R2);
			}
			else{
				if(DrawBlueNGMark==true){
					QPen	BPen(RCol,CircleWidth);
					PData.setPen(BPen);
					PData.drawEllipse(x1-7,y1-7,R2+14,R2+14);
				}
				QPen	RPen(QColor(Col),CircleWidth);
				PData.setPen(RPen);
				PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
				PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
				PData.drawEllipse(x1,y1,R2,R2);
			}
		}
		else{
			if(CircleWidth==0){
				if(DrawBlueNGMark==true){
					PData.setPen(RCol);
					PData.drawArc(x1-2,y1-2,R2+4,R2+4,0,5760);
				}
				PData.setPen(QColor(Col));
				PData.drawArc(x1,y1,R2,R2,0,5760);
			}
			else{
				if(DrawBlueNGMark==true){
					QPen	BPen(RCol,CircleWidth);
					PData.setPen(BPen);
					PData.drawArc(x1-2-CircleWidth,y1-2-CircleWidth
								,R2+4+CircleWidth+CircleWidth,R2+4+CircleWidth+CircleWidth
								,0,5760);
				}
				QPen	RPen(QColor(Col),CircleWidth);
				PData.setPen(RPen);
				PData.drawArc(x1,y1,R2,R2,0,5760);
			}
		}
	}
	if(NGLine==true){
		int	Lx1=(X1+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
		int Ly1=(Y1+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
		int	Lx2=(X2+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
		int Ly2=(Y2+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
		PData.setPen(Qt::yellow);
		PData.drawLine(Lx1,Ly1,Lx2,Ly2);
	}
}
bool    DotColorMatchingResultPosList::Load(QIODevice *f)
{
	if(ResultPosList::Load(f)==false)
		return false;
	if(::Load(f,NGLine)==false)
		return false;
	if(::Load(f,X1)==false)
		return false;
	if(::Load(f,Y1)==false)
		return false;
	if(::Load(f,X2)==false)
		return false;
	if(::Load(f,Y2)==false)
		return false;
	return true;
}
bool    DotColorMatchingResultPosList::Save(QIODevice *f)
{
	if(ResultPosList::Save(f)==false)
		return false;
	if(::Save(f,NGLine)==false)
		return false;
	if(::Save(f,X1)==false)
		return false;
	if(::Save(f,Y1)==false)
		return false;
	if(::Save(f,X2)==false)
		return false;
	if(::Save(f,Y2)==false)
		return false;
	return true;
}

//=====================================================================================
void	DotColorMatchingChangeShift::Reflect(DotColorMatchingBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(DotColorMatchingItemID);
		if(item!=NULL){
			if(item->GetCurrentResult()!=NULL){
				item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
			}
		}
	}
}

bool	DotColorMatchingChangeShift::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,DotColorMatchingItemID)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	DotColorMatchingChangeShift::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,DotColorMatchingItemID)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

//===========================================================================================
static	int	DbgID	=23941;
static	int	DbgX	=2733;
static	int	DbgY	=255;
static	int	DbgCode=0;

void	ItemsListForSearch::MakeSearchType(DotColorMatchingInPage *parent
											,FlexArea &MaskArea
											,FlexArea &MaskEdge)
{
	Parent=parent;
	for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
		Item->SearchType=0;
	}
	int	MaxCoeffArea=0;
	MaxCoefItem=NULL;
	DotColorMatchingBase	*BBase=dynamic_cast<DotColorMatchingBase *>(parent->GetParentBase());

	AlgorithmItemPointerList	**ADim=new AlgorithmItemPointerList*[Items.GetCount()];
	int	ADimCount=0;
	for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
		if(Item->IsCoeffType()==true){
			ADim[ADimCount]=a;
			ADimCount++;
		}
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int i=0;i<ADimCount;i++){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)ADim[i]->GetItem();
			int	dx,dy;
			double	D=Item->GetMaxSelfMatch(dx,dy);
			if(D<BBase->CoefSelfSearch){
				RotationPattern	*R=Item->GetRotationPattern(Item->GetCountOfRotationPattern()/2);
				int	PN=R->GetMinDivProjection();
				#pragma omp	critical
				{
					if(MaxCoeffArea<PN && PN>max(R->XLen,R->YLen)*0.3){
						MaxCoeffArea=PN;
						MaxCoefItem=Item;
					}
				}
			}
		}
	}
	delete	[]ADim;

	//if(MaxCoefItem==NULL){
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->GetArea().CheckOverlap(&MaskEdge)==true){
				//if(Item->GetArea().IsInclude(DbgX,DbgY)==true){
				//	DbgCode++;
				//}
				Item->MakeHVLine(MaskArea);
			}
		}
	//}

	if(MaxCoefItem!=NULL){
		MaxCoefItem->SearchType=1;

		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->SearchType==0 && Item->HasHOrVLine()==true){
				Item->SearchType=2;
				Item->MaxCoefItem=MaxCoefItem;
			}
		}
	}
	else{
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->HasHAndVLine()==true){
				Item->SearchType=3;
				MaxCoefItem=Item->MaxCoefItem;
			}
		}
	}
	if(MaxCoefItem!=NULL){
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->SearchType==0){
				Item->SearchType=5;
				Item->MaxCoefItem=MaxCoefItem;
			}
		}
	}
	else{
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			//if(Item->GetID()==DbgID){
			//	DbgCode++;
			//}
			if(Item->SearchType==0){
				if(Item->HasHOrVLine()==true){
					if(Item->MasterPattern[0].DivArea.IsNull()==true){
						Item->SearchType=7;
					}
					else{
						Item->SearchType=8;
					}
				}
				else{
					Item->SearchType=6;
				}
				Item->MaxCoefItem=NULL;
			}
		}
	}

	if(MaxCoefItem!=NULL){
		MaxCoefItem->FollowItems.RemoveAll();
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->MaxCoefItem==MaxCoefItem){
				MaxCoefItem->FollowItems.Add(Item);
			}
		}
	}
}

ExeResult	ItemsListForSearch::ExecuteProcessing(int ExeID ,ResultInPageRoot *Res)
{
	AreaDx=AreaDy=0;
	if(MaxCoefItem!=NULL){
		MaxCoefItem->ExecuteProcessing(ExeID ,0,MaxCoefItem->GetCurrentResult());
		AreaDx=MaxCoefItem->ResultSelfSeachDx;
		AreaDy=MaxCoefItem->ResultSelfSeachDy;

		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->HasHOrVLine()==true){
				const	DotColorMatchingThreshold	*RThr=Item->GetThresholdR(Parent->GetLayersBase());
				int	kx,ky;
				Item->ExecuteSearchByLine(AreaDx,AreaDy,kx,ky,RThr->AreaSearchX/4,RThr->AreaSearchY/4);
				Item->ExecuteProcessing0 (Item->GetCurrentResult()
										 ,RThr,&RThr->Broad
										 ,AreaDx+kx,AreaDy+ky,RThr->AreaSearchX/8,RThr->AreaSearchY/8);
			}
		}
	}
	else{
		for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
			if(Item->HasHAndVLine()==true){
				const	DotColorMatchingThreshold	*RThr=Item->GetThresholdR(Parent->GetLayersBase());
				int	kx,ky;
				Item->ExecuteSearchByLine(AreaDx,AreaDy,kx,ky,RThr->AreaSearchX,RThr->AreaSearchY);
				Item->ExecuteProcessing0(Item->GetCurrentResult()
										,RThr,&RThr->Broad
										,AreaDx+kx,AreaDy+ky ,RThr->AreaSearchX/4,RThr->AreaSearchY/4);
				AreaDx=Item->ResultSelfSeachDx;
				AreaDy=Item->ResultSelfSeachDy;
			}
		}
	}
	for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;a=a->GetNext()){
		DotColorMatchingItem	*Item=(DotColorMatchingItem *)a->GetItem();
		const	DotColorMatchingThreshold	*RThr=Item->GetThresholdR(Parent->GetLayersBase());
		Item->ExecuteProcessing0(Item->GetCurrentResult()
								,RThr,&RThr->Broad
								,AreaDx,AreaDy,RThr->AreaSearchX/4,RThr->AreaSearchY/4);
	}
	return _ER_true;
}


//===========================================================================================
DotColorMatchingInPage::HSVTableClass::HSVTableClass(void)
{
	#pragma omp parallel
	{
		#pragma omp for
		for(int H=0;H<360;H++){
			for(int p=0;p<360;p++){
				for(int d=0;d<360;d++){
					int	MHL=(H*(-p+100)*0.01)-d;
					int	MHH=(H*( p+100)*0.01)+d;
					if(MHH-MHL>=360){
						MHL=0;
						MHH=360;
					}
					else{
						while(MHL<0)
							MHL+=360;
						while(MHL>=360)
							MHL-=360;
						
						while(MHH<0)
							MHH+=360;
						while(MHH>=360)
							MHH-=360;
					}
					HSV_HHTable[H][p][d]=MHH;
					HSV_HLTable[H][p][d]=MHL;
				}
			}
		}
		#pragma omp for
		for(int SV=0;SV<256;SV++){
			for(int p=0;p<256;p++){
				for(int d=0;d<256;d++){
					int	MSL=(SV*(-p+100)*0.01)-d;
					int	MSH=(SV*( p+100)*0.01)+d;
					HSV_SVHTable[SV][p][d]=Clipping(MSH,0,255);
					HSV_SVLTable[SV][p][d]=Clipping(MSL,0,255);
				}
			}
		}
	}
}
DotColorMatchingInPage::DotColorMatchingInPage(AlgorithmBase *parent)
	:AlgorithmInPagePI(parent)
{
	PickupBmp		=NULL;
	PickupBmpYLen	=0;
	PickupBmpXByte	=0;

	//ModeParallel.ModeParallelExecuteInitialAfterEdit=false;
	ModeParallel.ModeParallelExecuteInitialAfterEdit=true;
	RDim=NULL;
	HSVTablePoint=NULL;
}
DotColorMatchingInPage::~DotColorMatchingInPage(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;

	if(RDim!=NULL){
		delete	[]RDim;
		RDim=NULL;
	}
	if(HSVTablePoint!=NULL){
		delete	HSVTablePoint;
		HSVTablePoint=NULL;
	}
}
void	DotColorMatchingInPage::CreatePickupBmpBuff(void)
{
	if(PickupBmp!=NULL && PickupBmpYLen!=GetMaxLines()){
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
		PickupBmp=NULL;
		PickupBmpYLen=0;
	}
	if(PickupBmp==NULL){
		PickupBmpYLen=GetMaxLines();
		PickupBmpXByte=(GetDotPerLine()+7)/8;
		PickupBmp=MakeMatrixBuff(PickupBmpXByte ,PickupBmpYLen);
	}
	MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
}

bool	DotColorMatchingInPage::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfDotColorMatching	RCmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		SlaveCommAckLibraryInMaskOfDotColorMatching	ACmd(GetLayersBase(),sRoot,sName,CurrentGlobalPage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	DotColorMatchingInPage::PickupTest(DotColorMatchingLibrary &LibData)
{
	CreatePickupBmpBuff();
	ConstMapBufferListContainer MaskMap;

	if(GetReflectionMap(_Reflection_Mask,MaskMap,&LibData)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibData.GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&LibData,NULL);
		ImageBuffer *ImageList[100];
		GetMasterBuffList(ImageList);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
			LibData.MakePickupTest(ImageList
				,Map.GetBitMap()
				,PickupBmp,NULL
				,GetPage()
				,PickupBmpXByte ,GetDotPerLine(),PickupBmpYLen
				,((DotColorMatchingBase *)GetParentBase())->OmitZoneDot);
		}
	}
}

int	DotColorMatchingLibrarySortFunc(const void *a , const void *b)
{
	DotColorMatchingLibrary	*pa=((DotColorMatchingLibrary **)a)[0];
	DotColorMatchingLibrary	*pb=((DotColorMatchingLibrary **)b)[0];
	int	n=pa->Priority - pb->Priority;
	return n;
}

void	DotColorMatchingInPage::GenerateDotColorMatchings(DotColorMatchingLibrary *LibDim[],int LibDimNumb)
{
	qsort(LibDim,LibDimNumb,sizeof(DotColorMatchingLibrary *),DotColorMatchingLibrarySortFunc);


	UndoElement<DotColorMatchingInPage>	*UPointer=new UndoElement<DotColorMatchingInPage>(this,&DotColorMatchingInPage::UndoGenerateItems);
	GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

	CreatePickupBmpBuff();
	//Data.RemoveAll();
	int	DeletedItemCount=0;
	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		if(L->GetEditLocked()==false){
			DeletedItemCount++;
		}
	}
	::Save(UPointer->GetWritePointer(),DeletedItemCount);

	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;){
		AlgorithmItemPI	*NextL=L->GetNext();
		if(L->GetEditLocked()==false){
			L->Save(UPointer->GetWritePointer());
			Data.RemoveList(L);
			delete	L;
		}
		L=NextL;
	}

	int	XByte=(GetDotPerLine()+7)/8;

	BYTE **CurrentMap	=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **LastOcupyMap		=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(LastOcupyMap,0,XByte,GetMaxLines());

	BYTE **TempMap	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
	BYTE **TempMap2	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(TempMap2,0,XByte,GetMaxLines());
	BYTE **SubBlockMap	=MakeMatrixBuff(XByte,GetMaxLines());
	
	AlgorithmLibraryStocker	LibStocker;
	AlgorithmLibraryContainer	*Container=GetParentBase()->GetLibraryContainer();
	if(Container!=NULL){
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			AlgorithmLibraryLevelContainer	*Lib=LibStocker.FindLib(GetParentBase()->GetLibType(),L->GetLibID());
			if(Lib==NULL){
				Lib=new AlgorithmLibraryLevelContainer(Container);
				if(Container->GetLibrary(L->GetLibID() ,*Lib)==true){
					LibStocker.AppendList(new AlgorithmLibraryStockerList(Lib));
				}
				else{
					delete	Lib;
					Lib=NULL;
				}
			}
		}
	}

	for(AlgorithmLibraryStockerList *B=LibStocker.GetFirst();B!=NULL;B=B->GetNext()){
		MatrixBuffClear(TempMap ,0,XByte,GetMaxLines());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetLibID()==B->GetLib().GetLibID()){
				L->GetArea().MakeBitData(TempMap,GetDotPerLine() ,GetMaxLines());
			}
		}
		DotColorMatchingLibrary	*BLib=(DotColorMatchingLibrary *)B->GetLib().GetLibrary();
		int	BSpaceToOutline;
		BSpaceToOutline=BLib->SpaceToOutline;
		GetLayersBase()->FatAreaN(TempMap,TempMap2 ,XByte,GetMaxLines(),BSpaceToOutline);

		MatrixBuffOr(LastOcupyMap,(const BYTE **)TempMap,XByte,GetMaxLines());
	}

	BYTE **OcupyMap				=MakeMatrixBuff(XByte,GetMaxLines());
	BYTE **OcupyMapSamePriority	=MakeMatrixBuff(XByte,GetMaxLines());
	MatrixBuffClear(OcupyMap,0,XByte,GetMaxLines());
	MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
	DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();

	ImageBuffer *ImageList[100];
	GetMasterBuffList(ImageList);
	IntList	AddedItemIDList;
	for(int i=0;i<LibDimNumb;i++){
		MatrixBuffClear(CurrentMap,0,XByte,GetMaxLines());

		ConstMapBufferListContainer MaskMap;
		if(LibDim[i]->GenerateOnlyLimitedMask==false){
			GetReflectionMap(_Reflection_Mask,MaskMap,LibDim[i]);
		}
		else{
			GetReflectionMap(_Reflection_MaskOnlyInLimitMask,MaskMap,LibDim[i]);
		}
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		const BYTE	**MaskBitmap=Map.GetBitMap();
				

		if(LibDim[i]->EnableOverlap==false){
			MatrixBuffNotAnd ((BYTE **)MaskBitmap,(const BYTE **)LastOcupyMap ,XByte,GetMaxLines());
		}
		//MatrixBuffClear(SubBlockMap,0,XByte,GetMaxLines());
		//for(IntClass *v=LibDim[i]->SubtractLibID.GetFirst();v!=NULL;v=v->GetNext()){
		//	for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
		//		if(L->GetLibID()==v->GetValue()){
		//			L->GetArea().MakeBitData(SubBlockMap
		//									,GetDotPerLine(),GetMaxLines());
		//		}
		//	}
		//}
		//MatrixBuffOr ((BYTE **)MaskBitmap,(const BYTE **)SubBlockMap ,XByte,GetMaxLines());
	
		bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(LibDim[i]->GetLibID());
		bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,LibDim[i],NULL);
		if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){

			LibDim[i]->MakePickupTest(ImageList
				,MaskBitmap
				,CurrentMap,OcupyMap
				,GetPage()
				,XByte ,GetDotPerLine(),GetMaxLines()
				,((DotColorMatchingBase *)GetParentBase())->OmitZoneDot);



			if(LibDim[i]->GenerateOutlineMode==true){
				MatrixBuffCopy	(TempMap2	,XByte,GetMaxLines()
								,(const BYTE **)CurrentMap ,XByte,GetMaxLines());
				GetLayersBase()->ThinAreaN(TempMap2,TempMap,XByte,GetMaxLines(),ABase->OutlineZoneWidth);
				MatrixBuffCopy	(TempMap	,XByte,GetMaxLines()
								,(const BYTE **)CurrentMap ,XByte,GetMaxLines());
				if(LibDim[i]->EnableOverlap==false){
					MatrixBuffNotAnd(TempMap ,(const BYTE **)TempMap2 ,XByte,GetMaxLines());
				}

				NPListPack<AlgorithmItemPI>	TmpDotColorMatchingDataOutline;
				LibDim[i]->MakeDotColorMatching(
						ImageList
						,TempMap,LastOcupyMap,SubBlockMap
						,GetPage()
						,XByte ,GetDotPerLine(),GetMaxLines()
						,TmpDotColorMatchingDataOutline);

				//驛｢譎｢ｽｭ驛｢譏ｴﾂ｢驍ｵｺ陷会ｽｱ隨ｳｽｹ譎§取ｺｽｹ譏ｴﾂ｢驍ｵｺｽｫ髯晢ｿｽｽｾ驍ｵｺ陷会ｽｱ遯ｶｻ鬯ｩ･陝雜｣ｽ､陟趣ｿｽｸｺｽｮ驛｢譎§取ｺｽｹ譏ｴﾂ｢驛｢ｧ陜｣､陷ｽｽ髫ｰ迹夲ｿｽｽｽ驍ｵｺ雋ｪｽ驍ｵｺ鬯ｩ･鬮ｦｪ邵ｲ蟶晢ｿｽ蠅難ｽｻ骰具ｽｸｺ髴郁ｲｻｽ讙趣ｽｹｧ闕ｵ譎｢ｼｽｸｺｽｨ驛｢ｧ陝ｶ譏ｶ闌憺しｺ闔会ｽ｣ｽ迢暦ｽｸｺ雋∞ｽ竏ｫｸｺｽｮ髯ｷｽｽｦ鬨ｾｽ
				for(AlgorithmItemPI *a=TmpDotColorMatchingDataOutline.GetFirst();a!=NULL;a=a->GetNext()){
					for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
						if(L->GetLibID()==LibDim[i]->GetLibID()){
							if(a->GetArea().CheckOverlap(&L->GetArea())==true){
								FlexArea	&A=a->GetArea();
								A-=L->GetArea();
							}
						}
					}
				}
				for(AlgorithmItemPI *a=TmpDotColorMatchingDataOutline.GetFirst();a!=NULL;){
					AlgorithmItemPI	*b=a->GetNext();
					if(a->GetArea().GetPatternByte()<5){
						TmpDotColorMatchingDataOutline.RemoveList(a);
						delete	a;
					}
					a=b;
				}

				AlgorithmItemPI	*q;
				while((q=TmpDotColorMatchingDataOutline.GetFirst())!=NULL){
					TmpDotColorMatchingDataOutline.RemoveList(q);
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(q);
					Item->OutlineArea=true;
					Item->OutlineBlock=true;
					AppendItem(q);
					AddedItemIDList.Add(q->GetID());
				}

				int	EnSmallDot=(ABase->OutlineZoneWidth>10)?ABase->OutlineZoneWidth-5:ABase->OutlineZoneWidth/2;
				GetLayersBase()->ThinAreaN(CurrentMap,TempMap,XByte,GetMaxLines(),EnSmallDot);

				NPListPack<AlgorithmItemPI>	TmpDotColorMatchingData;
				LibDim[i]->MakeDotColorMatching(
						ImageList
						,CurrentMap,LastOcupyMap,SubBlockMap
						,GetPage()
						,XByte ,GetDotPerLine(),GetMaxLines()
						,TmpDotColorMatchingData);


				int	FoldingAreaWidth=ABase->FoldingAreaWidth;
				int	tFoldingAreaWidth=0;
				for(int i=0;i<FoldingAreaWidth;i+=10){
					GetLayersBase()->ThinAreaN(CurrentMap,TempMap,XByte,GetMaxLines(),10);
					tFoldingAreaWidth+=10;
				}
				if(FoldingAreaWidth-tFoldingAreaWidth>0){
					GetLayersBase()->ThinAreaN(CurrentMap,TempMap,XByte,GetMaxLines(),FoldingAreaWidth-tFoldingAreaWidth);
				}
				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;a=a->GetNext()){
					a->GetArea().MakeBitData(OcupyMap,GetDotPerLine(),GetMaxLines());
				}

				//驛｢譎｢ｽｭ驛｢譏ｴﾂ｢驍ｵｺ陷会ｽｱ隨ｳｽｹ譎§取ｺｽｹ譏ｴﾂ｢驍ｵｺｽｫ髯晢ｿｽｽｾ驍ｵｺ陷会ｽｱ遯ｶｻ鬯ｩ･陝雜｣ｽ､陟趣ｿｽｸｺｽｮ驛｢譎§取ｺｽｹ譏ｴﾂ｢驛｢ｧ陜｣､陷ｽｽ髫ｰ迹夲ｿｽｽｽ驍ｵｺ雋ｪｽ驍ｵｺ鬯ｩ･鬮ｦｪ邵ｲ蟶晢ｿｽ蠅難ｽｻ骰具ｽｸｺ髴郁ｲｻｽ讙趣ｽｹｧ闕ｵ譎｢ｼｽｸｺｽｨ驛｢ｧ陝ｶ譏ｶ闌憺しｺ闔会ｽ｣ｽ迢暦ｽｸｺ雋∞ｽ竏ｫｸｺｽｮ髯ｷｽｽｦ鬨ｾｽ
				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;a=a->GetNext()){
					for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
						if(L->GetLibID()==LibDim[i]->GetLibID()){
							if(a->GetArea().CheckOverlap(&L->GetArea())==true){
								FlexArea	&A=a->GetArea();
								A-=L->GetArea();
							}
						}
					}
				}
				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;){
					AlgorithmItemPI	*b=a->GetNext();
					if(a->GetArea().GetPatternByte()<5){
						TmpDotColorMatchingData.RemoveList(a);
						delete	a;
					}
					a=b;
				}
				while((q=TmpDotColorMatchingData.GetFirst())!=NULL){
					TmpDotColorMatchingData.RemoveList(q);
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(q);
					//if(Item->GetArea().IsInclude(DbgX,DbgY)==true)
					//	DbgCode++;
					if(Item->GetArea().CheckOverlapBit(CurrentMap , GetDotPerLine(),GetMaxLines())==false){
						Item->FoldingArea=true;
					}
					AppendItem(q);
					AddedItemIDList.Add(q->GetID());
				}
			}
			else{
				MatrixBuffCopy	(TempMap	,XByte,GetMaxLines()
								,(const BYTE **)CurrentMap ,XByte,GetMaxLines());
				
				NPListPack<AlgorithmItemPI>	TmpDotColorMatchingData;
				LibDim[i]->MakeDotColorMatching(
						ImageList
						,TempMap,LastOcupyMap,SubBlockMap
						,GetPage()
						,XByte ,GetDotPerLine(),GetMaxLines()
						,TmpDotColorMatchingData);

				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;a=a->GetNext()){
					a->GetArea().MakeBitData(OcupyMap,GetDotPerLine(),GetMaxLines());
				}

				//驛｢譎｢ｽｭ驛｢譏ｴﾂ｢驍ｵｺ陷会ｽｱ隨ｳｽｹ譎§取ｺｽｹ譏ｴﾂ｢驍ｵｺｽｫ髯晢ｿｽｽｾ驍ｵｺ陷会ｽｱ遯ｶｻ鬯ｩ･陝雜｣ｽ､陟趣ｿｽｸｺｽｮ驛｢譎§取ｺｽｹ譏ｴﾂ｢驛｢ｧ陜｣､陷ｽｽ髫ｰ迹夲ｿｽｽｽ驍ｵｺ雋ｪｽ驍ｵｺ鬯ｩ･鬮ｦｪ邵ｲ蟶晢ｿｽ蠅難ｽｻ骰具ｽｸｺ髴郁ｲｻｽ讙趣ｽｹｧ闕ｵ譎｢ｼｽｸｺｽｨ驛｢ｧ陝ｶ譏ｶ闌憺しｺ闔会ｽ｣ｽ迢暦ｽｸｺ雋∞ｽ竏ｫｸｺｽｮ髯ｷｽｽｦ鬨ｾｽ
				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;a=a->GetNext()){
					for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
						if(L->GetLibID()==LibDim[i]->GetLibID()){
							if(a->GetArea().CheckOverlap(&L->GetArea())==true){
								FlexArea	&A=a->GetArea();
								A-=L->GetArea();
							}
						}
					}
				}
				for(AlgorithmItemPI *a=TmpDotColorMatchingData.GetFirst();a!=NULL;){
					AlgorithmItemPI	*b=a->GetNext();
					if(a->GetArea().GetPatternByte()<5){
						TmpDotColorMatchingData.RemoveList(a);
						delete	a;
					}
					a=b;
				}

				AlgorithmItemPI	*q;
				while((q=TmpDotColorMatchingData.GetFirst())!=NULL){
					TmpDotColorMatchingData.RemoveList(q);
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(q);
					Item->OutlineArea=true;
					AppendItem(q);
					AddedItemIDList.Add(q->GetID());
				}
			}
		}
		MatrixBuffOr (OcupyMapSamePriority,(const BYTE **)OcupyMap ,XByte,GetMaxLines());
		if((i+1)<LibDimNumb && LibDim[i]->Priority!=LibDim[i+1]->Priority){
			MatrixBuffOr (LastOcupyMap,(const BYTE **)OcupyMapSamePriority ,XByte,GetMaxLines());
			MatrixBuffClear(OcupyMapSamePriority,0,XByte,GetMaxLines());
		}
	}
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
		if(Item!=NULL){
			Item->GetThresholdW()->SetToOrigin();
		}
	}
	DeleteMatrixBuff(TempMap	,GetMaxLines());
	DeleteMatrixBuff(TempMap2	,GetMaxLines());
	DeleteMatrixBuff(SubBlockMap,GetMaxLines());

	AddedItemIDList.Save(UPointer->GetWritePointer());

	DeleteMatrixBuff(CurrentMap				,GetMaxLines());
	DeleteMatrixBuff(OcupyMap				,GetMaxLines());
	DeleteMatrixBuff(LastOcupyMap			,GetMaxLines());
	DeleteMatrixBuff(OcupyMapSamePriority	,GetMaxLines());
}
bool	DotColorMatchingInPage::Save(QIODevice *f)
{
	if(AlgorithmInPagePI::Save(f)==false)
		return false;
	return true;
}
bool	DotColorMatchingInPage::Load(QIODevice *f)
{
	if(AlgorithmInPagePI::Load(f)==false)
		return false;
	return true;
}

static	int	XDebugID=6741;
static	int	XDbgCode=0;
extern	int	DbgR1;
extern	int	DbgR2;

ExeResult	DotColorMatchingInPage::ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=_ER_false;
	if(EInfo.HasChangedOnlyImage==false){
		ConstMapBufferListContainer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap);
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		EffectiveMap=Map;

		BYTE	**TmpMap=MakeMatrixBuff(EffectiveMap.GetXByte() ,EffectiveMap.GetYLen());
		GetLayersBase()->FatAreaN((BYTE **)EffectiveMap.GetBitMap(),TmpMap
									,EffectiveMap.GetXByte() ,EffectiveMap.GetYLen()
									,((DotColorMatchingBase *)GetParentBase())->BackGroundIsolationToEdge);
		DeleteMatrixBuff(TmpMap,EffectiveMap.GetYLen());

		FlexArea	MaskArea;
		MaskArea.BuildFromRaster((uchar **)Map.GetBitMap()
								 ,Map.GetXByte()
								 ,Map.GetYLen(),0,0);

		FlexArea	MaskInside;
		MaskInside=MaskArea;
		MaskInside.ThinAreaN(4);
		EdgeArea.Sub(MaskArea,MaskInside);
		EdgeArea.FatAreaN(2);

		DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();
		Ret=AlgorithmInPagePI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);
		if(GetParamComm()->ImageBufferNecessary()==true){
			int	NoiseBrightness=((DotColorMatchingBase *)GetParentBase())->NoiseBrightness;
			for(int ThrOffset=-MaxThreOffset;ThrOffset<=MaxThreOffset;ThrOffset++){
				int	DThrOffset=MaxThreOffset+ThrOffset;
				for(int i=0;i<256;i++){
					for(int j=0;j<256;j++){
						BrightWidthTableFlat[DThrOffset][i][j]=Clipping((int)(((i*j*327)>>15)*0.5+NoiseBrightness+ThrOffset),0,255);
						BrightWidthTableComp[DThrOffset][i][j]=Clipping(      ((i*j*327)>>15)    +NoiseBrightness+ThrOffset ,0,255);
					}
				}
			}
			//for(int layer=0;layer<3 && layer<GetLayerNumb();layer++){
			//	BrightnessLow [layer].Set(GetPage(),ImageBufferOther,GetDotPerLine(),GetMaxLines());
			//	BrightnessHigh[layer].Set(GetPage(),ImageBufferOther,GetDotPerLine(),GetMaxLines());
			//}

			if(ABase!=NULL && ABase->MakeYAB==true){
				ImageL.Set(GetPage(),ImageBufferOther,GetDotPerLine(),GetMaxLines());
				ImageA.Set(GetPage(),ImageBufferOther,GetDotPerLine(),GetMaxLines());
				ImageB.Set(GetPage(),ImageBufferOther,GetDotPerLine(),GetMaxLines());
			}
			if(ABase!=NULL){
				ImagePointerContainer MasterImageList;
				GetMasterBuffList(MasterImageList);
				if(ABase->MakeYAB==true && MasterImageList.GetCount()>=3){

				}
			}
		}
		DimItemsListInAreaXLen=GetDotPerLine()/CountOfDimItemsListInArea;
		DimItemsListInAreaYLen=GetMaxLines()/CountOfDimItemsListInArea;

		for(int yn=0;yn<CountOfDimItemsListInArea;yn++){
			for(int xn=0;xn<CountOfDimItemsListInArea;xn++){
				DimItemsListInArea[xn][yn].Items.RemoveAll();
				DimItemsListInArea[xn][yn].x1=DimItemsListInAreaXLen*xn;
				DimItemsListInArea[xn][yn].y1=DimItemsListInAreaXLen*yn;
				DimItemsListInArea[xn][yn].x2=DimItemsListInAreaXLen*(xn+1);
				DimItemsListInArea[xn][yn].y2=DimItemsListInAreaXLen*(yn+1);
			}
		}
		RemoveInvalidItems();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			int	x1,y1,x2,y2;
			Item->GetXY(x1,y1,x2,y2);
			int	xn1=x1/DimItemsListInAreaXLen;
			int	yn1=y1/DimItemsListInAreaYLen;
			int	xn2=x2/DimItemsListInAreaXLen;
			int	yn2=y2/DimItemsListInAreaYLen;
			for(int yn=yn1;yn<CountOfDimItemsListInArea && yn<=yn2;yn++){
				for(int xn=xn1;xn<CountOfDimItemsListInArea && xn<=xn2;xn++){
					DimItemsListInArea[xn][yn].Items.Add(Item);
				}
			}
		}
		for(int yn=0;yn<CountOfDimItemsListInArea;yn++){
			for(int xn=0;xn<CountOfDimItemsListInArea;xn++){
				DimItemsForSearch[xn][yn].Items.RemoveAll();
				DimItemsForSearch[xn][yn].x1=DimItemsListInAreaXLen*xn;
				DimItemsForSearch[xn][yn].y1=DimItemsListInAreaXLen*yn;
				DimItemsForSearch[xn][yn].x2=DimItemsListInAreaXLen*(xn+1);
				DimItemsForSearch[xn][yn].y2=DimItemsListInAreaXLen*(yn+1);
			}
		}
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			int	Cx,Cy;
			Item->GetCenter(Cx,Cy);
			int	xn=Cx/DimItemsListInAreaXLen;
			int	yn=Cy/DimItemsListInAreaYLen;
			DimItemsForSearch[xn][yn].Items.Add(Item);
		}

		for(int yn=0;yn<CountOfDimItemsListInArea;yn++){
			for(int xn=0;xn<CountOfDimItemsListInArea;xn++){
				DimItemsForSearch[xn][yn].MakeSearchType(this,MaskArea,EdgeArea);
			}
		}
		Items1.RemoveAll();
		Items2.RemoveAll();
		Items3.RemoveAll();
		Items4.RemoveAll();
		Items5.RemoveAll();
		Items6.RemoveAll();
		IntList	SubBlockItemID;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==DbgID){
			//	DbgR1++;
			//}
			for(SubtractItem *v=a->GetSubBlock().GetFirst();v!=NULL;v=v->GetNext()){
				SubBlockItemID.Merge(v->ItemID);
			}
		}

		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			//if(a->GetID()==DbgID){
			//	DbgR1++;
			//}
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			if(Item->SearchType==1){
				if(SubBlockItemID.IsInclude(Item->GetID())==true){
					Items1.Add(Item);
				}
				else{
					Items4.Add(Item);
				}
			}
			else
			if(Item->SearchType==3){
				if(Item->MaxCoefItem!=NULL){
					if(SubBlockItemID.IsInclude(Item->GetID())==true){
						Items1.Add(Item);
					}
					else{
						Items4.Add(Item);
					}
				}
				else{
					if(SubBlockItemID.IsInclude(Item->GetID())==true){
						Items2.Add(Item);
					}
					else{
						Items5.Add(Item);
					}
				}
			}
			else
			if(Item->SearchType==5){
				if(SubBlockItemID.IsInclude(Item->GetID())==true){
					Items3.Add(Item);
				}
				else{
					Items6.Add(Item);
				}
			}
			else
			if(Item->SearchType==6){
				if(SubBlockItemID.IsInclude(Item->GetID())==true){
					Items3.Add(Item);
				}
				else{
					Items6.Add(Item);
				}
			}
			else
			if(Item->SearchType==7){
				if(SubBlockItemID.IsInclude(Item->GetID())==true){
					Items3.Add(Item);
				}
				else{
					Items6.Add(Item);
				}
			}
			else
			if(Item->SearchType==8){
				if(SubBlockItemID.IsInclude(Item->GetID())==true){
					Items3.Add(Item);
				}
				else{
					Items6.Add(Item);
				}
			}
		}
		if(RDim!=NULL){
			delete	[]RDim;
		}
		RDim=new ResultInItemPI*[GetItemCount()];

		ConstMapBufferListContainer VMap;
		if(GetReflectionMap(_Reflection_Variety ,VMap)==true){
			for(int layer=0;layer<GetLayerNumb();layer++){
				if(VMap[layer]!=NULL){
					VarietyMap[layer]=*VMap[layer]->GetMapBuffer();

					int	Mergin=ABase->VariationInfluenceArea;
					int	YLen=GetMaxLines();
					int	XLen=GetDotPerLine();
					int	N=YLen-2*Mergin;
					#pragma omp parallel                             
					{                                                
						#pragma omp for
						for(int t=0;t<N;t++){
							int	y=t+Mergin;
						//for(int y=Mergin;y<YLen-Mergin;y++){
							BYTE	*d=VarietyMap[layer].GetY(y);
							for(int dy=-Mergin;dy<Mergin;dy++){
								BYTE	*s=VMap[layer]->GetMapBuffer()->GetY(y+dy);
								for(int x=Mergin;x<XLen-Mergin;x++){
									BYTE	MaxD=0;
									BYTE	*sp=&s[x-Mergin];
									int		JN=Mergin+Mergin;
									for(int j=0;j<JN;j++){
									//for(int dx=-Mergin;dx<Mergin;dx++){
										//BYTE	k=s[x+dx];
										BYTE	k=*sp;
										sp++;
										if(k>MaxD){
											MaxD=k;
										}
									}
									d[x]=MaxD;
								}
							}
						}
					}
				}
				else{
					VarietyMap[layer].ClearAll();
				}
			}
		}

		MultiSpotItemList.RemoveAll();
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			AlgorithmItemPointerListContainerByLib *c;
			for(c=MultiSpotItemList.GetFirst();c!=NULL;c=c->GetNext()){
				if(c->LibID==Item->GetLibID()){
					c->Container.Add(Item);
					break;
				}
			}
			if(c==NULL){
				c=new AlgorithmItemPointerListContainerByLib();
				c->LibID=Item->GetLibID();
				c->Layer=0;
				c->Container.Add(Item);
				MultiSpotItemList.AppendList(c);
			}
		}

		AlgorithmItemPointerListContainerByLibContainer	LibIDs;
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			int	LibID=a->GetLibID();
			AlgorithmItemPointerListContainerByLib	*v=LibIDs.FindByLibID(0 ,LibID);
			if(v==NULL){
				v=new AlgorithmItemPointerListContainerByLib(0 ,LibID);
				LibIDs.AppendList(v);
			}
			v->Container.Add(a);
		}
		{
			AlgorithmItemPI	*ai;
			#pragma omp parallel
			#pragma omp single private(ai)
			for(ai=GetFirstData();ai!=NULL;ai=ai->GetNext()){
				#pragma omp task
				{
					DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(ai);
					Item->ClearSubBlock();
					Item->ExpandedArea=Item->GetArea();
					Item->ExpandedArea.FatAreaN(Item->GetThresholdR()->ExpandToSubBlock);
				}
			}
		}
		IntList	DSubBlockLibID;
		AlgorithmLibraryContainer	*ALibC=ABase->GetLibraryContainer();
		for(AlgorithmItemPointerListContainerByLib *c=LibIDs.GetFirst();c!=NULL;c=c->GetNext()){
			AlgorithmLibraryLevelContainer	LibLevelC(ALibC);
			if(ALibC->GetLibrary(c->LibID,LibLevelC)==true){
				DotColorMatchingLibrary	*L=(DotColorMatchingLibrary *)LibLevelC.GetLibrary();		
				for(AlgorithmItemPointerList *a=c->Container.GetFirst();a!=NULL;a=a->GetNext()){
					DotColorMatchingItem	*ItemS=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
					for(IntClass *v=ItemS->GetThresholdW()->SubtractLibID.GetFirst();v!=NULL;v=v->GetNext()){
						for(AlgorithmItemPointerListContainerByLib *t=LibIDs.GetFirst();t!=NULL;t=t->GetNext()){
							if(t->LibID==v->GetValue()){
								for(AlgorithmItemPointerList *b=t->Container.GetFirst();b!=NULL;b=b->GetNext()){
									DotColorMatchingItem	*ItemD=dynamic_cast<DotColorMatchingItem *>(b->GetItem());
									if(ItemS->ExpandedArea.CheckOverlap(&ItemD->ExpandedArea)==true){
										if(ItemD->GetLibID()==21){
											DbgCode++;
										}
										DSubBlockLibID.Add(ItemD->GetLibID());
										ItemS->GetSubBlock().AppendList(new SubtractItem(ItemD->GetID() 
																						,ItemD->GetLibID()
																						,ItemD));
									}
								}
							}
						}
					}
				}
			}
		}
		for(AlgorithmItemPointerListContainerByLib *t=LibIDs.GetFirst();t!=NULL;t=t->GetNext()){
			if(DSubBlockLibID.IsInclude(t->LibID)==true){
				for(AlgorithmItemPointerList *b=t->Container.GetFirst();b!=NULL;b=b->GetNext()){
					DotColorMatchingItem	*ItemD=dynamic_cast<DotColorMatchingItem *>(b->GetItem());
					if(ItemD->GetID()==XDebugID)
						XDbgCode++;
					ItemD->BuildSubtractionMap();
				}
			}
			else{
				for(AlgorithmItemPointerList *b=t->Container.GetFirst();b!=NULL;b=b->GetNext()){
					DotColorMatchingItem	*ItemD=dynamic_cast<DotColorMatchingItem *>(b->GetItem());
					ItemD->ClearSubtractionMap();
				}
			}
		}
		if(HSVTablePoint==NULL){
			for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
				DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
				if(Item->GetThresholdR()->HsvCheckMode==true){
					HSVTablePoint=new HSVTableClass();
					break;
				}
			}
		}
	}
	else{
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			Item->InitializeOnlyByImage();
		}
	}
	return Ret;
}
ExeResult	DotColorMatchingInPage::ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)
{
	if(HSVTablePoint==NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			if(Item->GetThresholdR()->HsvCheckMode==true){
				HSVTablePoint=new HSVTableClass();
				break;
			}
		}
	}
	return AlgorithmInPagePI::ExecuteStartByInspection(ExeID ,Res);
}

ExeResult	DotColorMatchingInPage::ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)
{
	int		MaxInspectMilisec=GetParamGlobal()->MaxInspectMilisec;
	int		MaxNGCountsPerCam=Parent->GetParamGlobal()->MaxNGCountsPerCam;
	RetryCounter=0;
	//AlgorithmInPagePI::ExecuteProcessing(Res ,pInspectionData);
	int	MaxMilisecInPage=GetParentBase()->GetMaxMilisecInPage();

	DataInExecuter	*Exc=GetLayersBase()->GetExecuter(ExeID);
	DWORD	StartInspectionTimeMilisec=Exc->GetStartInspectionTimeMilisec();
	if(GetParamGlobal()->CalcSingleThread==false){
		if(Items1.GetCount()>=2){
			AlgorithmItemPointerList *a;
			#pragma omp parallel
			#pragma omp single private(a)
			for(a=Items1.GetFirst();a!=NULL;a=a->GetNext()){
				#pragma omp task
				{
					ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}
			}
		}
		else{
			AlgorithmItemPointerList *a1;
			for(a1=Items1.GetFirst();a1!=NULL;a1=a1->GetNext()){
				ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
		DWORD	GNowMilisec=::GetComputerMiliSec();
		if(GetNGCounter()<=MaxNGCountsPerCam && GNowMilisec-StartInspectionTimeMilisec<MaxInspectMilisec){
			if(Items2.GetCount()>=2){
				AlgorithmItemPointerList *a;
				#pragma omp parallel
				#pragma omp single private(a)
				for(a=Items2.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
						DWORD	NowMilisec=::GetComputerMiliSec();
						if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
						|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
							Exc->SetResult(DataInExecuter::_Result_TimeOut);
						}
						else if(GetNGCounter()<=MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
						}
						if(R->GetError()>=2){
							if(GetLayersBase()->GetResultFromAlgorithm()==0){
								GetLayersBase()->SetResultFromAlgorithm(1);
							}
						}
					}
				}
			}
			else{
				AlgorithmItemPointerList *a1;
				for(a1=Items2.GetFirst();a1!=NULL;a1=a1->GetNext()){
					ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}				
			}
		}
		GNowMilisec=::GetComputerMiliSec();
		if(GetNGCounter()<=MaxNGCountsPerCam && GNowMilisec-StartInspectionTimeMilisec<MaxInspectMilisec){
			if(Items3.GetCount()>=2){
				AlgorithmItemPointerList *a;
				#pragma omp parallel
				#pragma omp single private(a)
				for(a=Items3.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
						DWORD	NowMilisec=::GetComputerMiliSec();
						if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
						|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
							Exc->SetResult(DataInExecuter::_Result_TimeOut);
						}
						else if(GetNGCounter()<=MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
						}
						if(R->GetError()>=2){
							if(GetLayersBase()->GetResultFromAlgorithm()==0){
								GetLayersBase()->SetResultFromAlgorithm(1);
							}
						}
					}
				}
			}
			else{
				AlgorithmItemPointerList *a1;
				for(a1=Items3.GetFirst();a1!=NULL;a1=a1->GetNext()){
					ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}
			}
		}
		GNowMilisec=::GetComputerMiliSec();
		if(GetNGCounter()<=MaxNGCountsPerCam && GNowMilisec-StartInspectionTimeMilisec<MaxInspectMilisec){
			if(Items4.GetCount()>=2){
				AlgorithmItemPointerList *a;
				#pragma omp parallel
				#pragma omp single private(a)
				for(a=Items4.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
						DWORD	NowMilisec=::GetComputerMiliSec();
						if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
						|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
							Exc->SetResult(DataInExecuter::_Result_TimeOut);
						}
						else if(GetNGCounter()<=MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
						}
						if(R->GetError()>=2){
							if(GetLayersBase()->GetResultFromAlgorithm()==0){
								GetLayersBase()->SetResultFromAlgorithm(1);
							}
						}
					}
				}
			}
			else{
				AlgorithmItemPointerList *a1;
				for(a1=Items4.GetFirst();a1!=NULL;a1=a1->GetNext()){
					ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}
			}
		}
		GNowMilisec=::GetComputerMiliSec();
		if(GetNGCounter()<=MaxNGCountsPerCam && GNowMilisec-StartInspectionTimeMilisec<MaxInspectMilisec){
			if(Items5.GetCount()>=2){
				AlgorithmItemPointerList *a;
				#pragma omp parallel
				#pragma omp single private(a)
				for(a=Items5.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
						DWORD	NowMilisec=::GetComputerMiliSec();
						if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
						|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
							Exc->SetResult(DataInExecuter::_Result_TimeOut);
						}
						else if(GetNGCounter()<=MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
						}
						if(R->GetError()>=2){
							if(GetLayersBase()->GetResultFromAlgorithm()==0){
								GetLayersBase()->SetResultFromAlgorithm(1);
							}
						}
					}
				}
			}
			else{
				AlgorithmItemPointerList *a1;
				for(a1=Items5.GetFirst();a1!=NULL;a1=a1->GetNext()){
					ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}
			}
		}
		GNowMilisec=::GetComputerMiliSec();
		if(GetNGCounter()<=MaxNGCountsPerCam && GNowMilisec-StartInspectionTimeMilisec<MaxInspectMilisec){
			if(Items6.GetCount()>=2){
				AlgorithmItemPointerList *a;
				#pragma omp parallel
				#pragma omp single private(a)
				for(a=Items6.GetFirst();a!=NULL;a=a->GetNext()){
					#pragma omp task
					{
						ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
						DWORD	NowMilisec=::GetComputerMiliSec();
						if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
						|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
							Exc->SetResult(DataInExecuter::_Result_TimeOut);
						}
						else if(GetNGCounter()<=MaxNGCountsPerCam){
							a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
						}
						if(R->GetError()>=2){
							if(GetLayersBase()->GetResultFromAlgorithm()==0){
								GetLayersBase()->SetResultFromAlgorithm(1);
							}
						}
					}
				}
			}
			else{
				AlgorithmItemPointerList *a1;
				for(a1=Items6.GetFirst();a1!=NULL;a1=a1->GetNext()){
					ResultInItemRoot	*R=a1->GetItem()->GetCurrentResult();
					DWORD	NowMilisec=::GetComputerMiliSec();
					if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
					|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
						Exc->SetResult(DataInExecuter::_Result_TimeOut);
					}
					else if(GetNGCounter()<=MaxNGCountsPerCam){
						a1->GetItem()->ExecuteProcessing	(ExeID ,0,R);
					}
					if(R->GetError()>=2){
						if(GetLayersBase()->GetResultFromAlgorithm()==0){
							GetLayersBase()->SetResultFromAlgorithm(1);
						}
					}
				}
			}
		}
	}
	else{
		AlgorithmItemPointerList *a;
		for(a=Items1.GetFirst();a!=NULL;a=a->GetNext()){
			DWORD	NowMilisec=::GetComputerMiliSec();
			ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
			if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
			|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
				Exc->SetResult(DataInExecuter::_Result_TimeOut);
			}
			else if(GetNGCounter()<=MaxNGCountsPerCam){
				a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
			}
			if(R->GetError()>=2){
				if(GetLayersBase()->GetResultFromAlgorithm()==0){
					GetLayersBase()->SetResultFromAlgorithm(1);
				}
			}
		}
		if(GetNGCounter()<=MaxNGCountsPerCam){
			for(a=Items2.GetFirst();a!=NULL;a=a->GetNext()){
				ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
		if(GetNGCounter()<=MaxNGCountsPerCam){
			for(a=Items3.GetFirst();a!=NULL;a=a->GetNext()){
				ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
		if(GetNGCounter()<=MaxNGCountsPerCam){
			for(a=Items4.GetFirst();a!=NULL;a=a->GetNext()){
				ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
		if(GetNGCounter()<=MaxNGCountsPerCam){
			for(a=Items5.GetFirst();a!=NULL;a=a->GetNext()){
				ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
		if(GetNGCounter()<=MaxNGCountsPerCam){
			for(a=Items6.GetFirst();a!=NULL;a=a->GetNext()){
				ResultInItemRoot	*R=a->GetItem()->GetCurrentResult();
				DWORD	NowMilisec=::GetComputerMiliSec();
				if((NowMilisec-StartInspectionTimeMilisec)>=MaxInspectMilisec
				|| (NowMilisec-GetStartTimeMilisec())>MaxMilisecInPage){
					Exc->SetResult(DataInExecuter::_Result_TimeOut);
				}
				else if(GetNGCounter()<=MaxNGCountsPerCam){
					a->GetItem()->ExecuteProcessing	(ExeID ,0,R);
				}
				if(R->GetError()>=2){
					if(GetLayersBase()->GetResultFromAlgorithm()==0){
						GetLayersBase()->SetResultFromAlgorithm(1);
					}
				}
			}
		}
	}
	DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();
	if(ABase->UseGlobalMultiSpot==true){
		for(AlgorithmItemPointerListContainerByLib *ItemsByLib=MultiSpotItemList.GetFirst();ItemsByLib!=NULL;ItemsByLib=ItemsByLib->GetNext()){
			if(ItemsByLib->Container.GetCount()>0){
				AlgorithmItemPointerList	*Item=ItemsByLib->Container.GetFirst();
				DotColorMatchingItem	*AItem=dynamic_cast<DotColorMatchingItem *>(Item->GetItem());
				const	DotColorMatchingThreshold	*Thr=AItem->GetThresholdR();

				if(Thr->MultiSpotCount>0){
					int	CurrentMultiSpotCount=0;
					for(AlgorithmItemPointerList *a=ItemsByLib->Container.GetFirst();a!=NULL;a=a->GetNext()){
						DotColorMatchingItem	*A=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
						CurrentMultiSpotCount+=A->ResultMultiSpot.GetCount();
					}
					if(CurrentMultiSpotCount>=Thr->MultiSpotCount){
						for(AlgorithmItemPointerList *a=ItemsByLib->Container.GetFirst();a!=NULL;a=a->GetNext()){
							AlgorithmItemRoot	*ARoot=a->GetItem();
							if(ARoot->GetCurrentResult()->IsOk()==true){
								DotColorMatchingItem	*A=dynamic_cast<DotColorMatchingItem *>(ARoot);
								if(A->ResultMultiSpot.GetCount()>0){
									ResultInItemRoot	*Res=ARoot->GetCurrentResult();
									Res->SetError(3);
									Res->SetResult1(A->ResultMultiSpot.GetCount());
									int		MultiSpotMinSize=99999999;
									double	NGLength=0;
									for(ResultPosList *r=A->ResultMultiSpot.GetFirst();r!=NULL;r=r->GetNext()){
										MultiSpotMinSize=min(MultiSpotMinSize,(int)r->NGShape.GetPatternByte());
										NGLength		=max(NGLength,(double)r->NGSize);
									}
									Res->MovePosList(A->ResultMultiSpot);
									Res->SetResult2(MultiSpotMinSize);
									Res->SetResultDouble(NGLength);
								}
							}
						}
					}
				}
			}
		}
	}

	return _ER_true;		
}
void	DotColorMatchingInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedDotColorMatchingFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedDotColorMatchingFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		QBuffer	MBuff(&ModifyItemFromBA->Buff);
		DotColorMatchingItem	TempItem;
		MBuff.open(QIODevice::ReadWrite);
		TempItem.Load(&MBuff,GetLayersBase());
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			DotColorMatchingItem	*B=(DotColorMatchingItem *)L;
			if(B->GetSelected()==true){
				B->CopyThreshold(TempItem);
				B->SetLibID(TempItem.GetLibID());
			}
		}
		return;
	}	
	CmdGetOneSelectedItem	*GOneItem=dynamic_cast<CmdGetOneSelectedItem *>(packet);
	if(GOneItem!=NULL){
		GOneItem->ExistSelected=false;
		for(AlgorithmItemPI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			if(L->GetSelected()==true){
				DotColorMatchingItem	*B=(DotColorMatchingItem *)L;
				QBuffer	MBuff(&GOneItem->Buff);
				MBuff.open(QIODevice::ReadWrite);
				B->Save(&MBuff);
				GOneItem->ExistSelected=true;
				return;
			}
		}
		return;
	}
	CmdClearTestDotColorMatchingPacket	*CmdClearTestDotColorMatchingPacketVar=dynamic_cast<CmdClearTestDotColorMatchingPacket *>(packet);
	if(CmdClearTestDotColorMatchingPacketVar!=NULL){
		if(PickupBmp!=NULL)
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		return;
	}

	CmdGetDotColorMatchingFromList	*CmdGetDotColorMatchingFromListVar=dynamic_cast<CmdGetDotColorMatchingFromList *>(packet);
	if(CmdGetDotColorMatchingFromListVar!=NULL){
		DotColorMatchingItem *Item=(DotColorMatchingItem *)SearchIDItem(CmdGetDotColorMatchingFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetDotColorMatchingFromListVar->DotColorMatchingInfoOnMouse=Item;
		return;
	}
	CmdCreateDotColorMatchingItem	*CmdCreateDotColorMatchingItemVar=dynamic_cast<CmdCreateDotColorMatchingItem *>(packet);
	if(CmdCreateDotColorMatchingItemVar!=NULL){
		CmdCreateDotColorMatchingItemVar->DotColorMatching=(DotColorMatchingItem *)CreateItem(0);
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		DotColorMatchingItem *Item=(DotColorMatchingItem *)SearchIDItem(CmdAlgoSimulateVar->ItemID);
		if(Item!=NULL){
			QColor	Col=Qt::green;
			Col.setAlpha(100);

			RotationPattern	*m=Item->GetRotationPattern(Item->CurrentRotationPatternNo);
			if(m==NULL){
				Item->GetArea().DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
						,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			else{
				m->DrawAlpha(0,0 , CmdAlgoSimulateVar->Image,Col.rgba()
					,CmdAlgoSimulateVar->ZoomRate ,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
			}
			QBuffer	Buff(&CmdAlgoSimulateVar->Something);
			Buff.open(QIODevice::ReadOnly);
			bool	ModeDrawSubtract=false;
			int		SubtractItemID;
			if(::Load(&Buff,ModeDrawSubtract)==true){
				if(ModeDrawSubtract==true){
					if(::Load(&Buff,SubtractItemID)==true){
						QColor	Col=Qt::magenta;
						Col.setAlpha(70);
						if(SubtractItemID>=0){
							DotColorMatchingItem *SItem=(DotColorMatchingItem *)SearchIDItem(SubtractItemID);
							if(SItem!=NULL){
								int	sx=(SItem->ResultDx-Item->ResultDx);
								int	sy=(SItem->ResultDy-Item->ResultDy);
								RotationPattern	*sm=SItem->GetRotationPattern(SItem->CurrentRotationPatternNo);
								if(sm==NULL){
									SItem->GetArea().DrawAlpha(sx,sy, CmdAlgoSimulateVar->Image,Col.rgba()
											,CmdAlgoSimulateVar->ZoomRate 
											,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
								}
								else{
									sm->DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
										,CmdAlgoSimulateVar->ZoomRate 
										,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
								}
							}
						}
						else{
							for(SubtractItem *v=Item->GetSubBlock().GetFirst();v!=NULL;v=v->GetNext()){
								DotColorMatchingItem *SItem=(DotColorMatchingItem *)SearchIDItem(v->ItemID);
								if(SItem!=NULL){
									int	sx=(SItem->ResultDx-Item->ResultDx);
									int	sy=(SItem->ResultDy-Item->ResultDy);
									//int	sx=0;
									//int	sy=0;
									RotationPattern	*sm=SItem->GetRotationPattern(SItem->CurrentRotationPatternNo);
									if(sm==NULL){
										SItem->GetArea().DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
												,CmdAlgoSimulateVar->ZoomRate 
												,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
									}
									else{
										sm->DrawAlpha(sx,sy , CmdAlgoSimulateVar->Image,Col.rgba()
											,CmdAlgoSimulateVar->ZoomRate 
											,CmdAlgoSimulateVar->MovX ,CmdAlgoSimulateVar->MovY);
									}
								}
							}
						}
					}
				}
			}
		}
		return;
	}
	CmdItemListForPageContainer	*CmdItemListForPageContainerVar=dynamic_cast<CmdItemListForPageContainer *>(packet);
	if(CmdItemListForPageContainerVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			ItemListForPage *L;
			for(L=CmdItemListForPageContainerVar->Container->GetFirst();L!=NULL;L=L->GetNext()){
				if(L->LibID==a->GetLibID()){
					L->ItemCount++;
					break;
				}
			}
			if(L==NULL){
				L=new ItemListForPage();
				L->LibID=a->GetLibID();
				L->ItemCount=1;
				CmdItemListForPageContainerVar->Container->AppendList(L);
			}
		}
		return;
	}
	CmdDotColorMatchingSetLevel	*CmdDotColorMatchingSetLevelVar=dynamic_cast<CmdDotColorMatchingSetLevel *>(packet);
	if(CmdDotColorMatchingSetLevelVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			DotColorMatchingThreshold	*t=(DotColorMatchingThreshold *)a->GetThresholdBaseWritable();
			if(CmdDotColorMatchingSetLevelVar->Type==0 && Item->IsCoeffType()==true){
				t->Broad.BrightWidthRL=t->Broad.OrgBrightWidthRL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthRH=t->Broad.OrgBrightWidthRH*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthGL=t->Broad.OrgBrightWidthGL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthGH=t->Broad.OrgBrightWidthGH*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthBL=t->Broad.OrgBrightWidthBL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthBH=t->Broad.OrgBrightWidthBH*CmdDotColorMatchingSetLevelVar->Level;

				t->Narrow.BrightWidthRL=t->Narrow.OrgBrightWidthRL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthRH=t->Narrow.OrgBrightWidthRH*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthGL=t->Narrow.OrgBrightWidthGL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthGH=t->Narrow.OrgBrightWidthGH*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthBL=t->Narrow.OrgBrightWidthBL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthBH=t->Narrow.OrgBrightWidthBH*CmdDotColorMatchingSetLevelVar->Level;
			}
			if(CmdDotColorMatchingSetLevelVar->Type==1 && Item->IsCoeffType()==true){
				t->Broad.OKDot =t->Broad.OrgOKDot*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.OKDot=t->Narrow.OrgOKDot*CmdDotColorMatchingSetLevelVar->Level;
			}
			if(CmdDotColorMatchingSetLevelVar->Type==2 && Item->IsCoeffType()==false){
				t->Broad.BrightWidthRL=t->Broad.OrgBrightWidthRL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthRH=t->Broad.OrgBrightWidthRH*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthGL=t->Broad.OrgBrightWidthGL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthGH=t->Broad.OrgBrightWidthGH*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthBL=t->Broad.OrgBrightWidthBL*CmdDotColorMatchingSetLevelVar->Level;
				t->Broad.BrightWidthBH=t->Broad.OrgBrightWidthBH*CmdDotColorMatchingSetLevelVar->Level;

				t->Narrow.BrightWidthRL=t->Narrow.OrgBrightWidthRL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthRH=t->Narrow.OrgBrightWidthRH*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthGL=t->Narrow.OrgBrightWidthGL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthGH=t->Narrow.OrgBrightWidthGH*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthBL=t->Narrow.OrgBrightWidthBL*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.BrightWidthBH=t->Narrow.OrgBrightWidthBH*CmdDotColorMatchingSetLevelVar->Level;
			}
			if(CmdDotColorMatchingSetLevelVar->Type==3 && Item->IsCoeffType()==false){
				t->Broad.OKDot =t->Broad.OrgOKDot*CmdDotColorMatchingSetLevelVar->Level;
				t->Narrow.OKDot=t->Narrow.OrgOKDot*CmdDotColorMatchingSetLevelVar->Level;
			}
		}
		return;
	}
	CmdTryInspection	*CmdTryInspectionVar=dynamic_cast<CmdTryInspection *>(packet);
	if(CmdTryInspectionVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdTryInspectionVar->ItemID);
		if(a!=NULL){
			DotColorMatchingItem	*AItem=dynamic_cast<DotColorMatchingItem *>(a);
			if(AItem!=NULL){
				QBuffer	BuffEscape;
				BuffEscape.open(QIODevice::ReadWrite);
				AItem->GetThresholdW()->Save(&BuffEscape);
				BuffEscape.seek(0);
				QBuffer	tBuff(&CmdTryInspectionVar->ThresholdData);
				tBuff.open(QIODevice::ReadOnly);
				AItem->GetThresholdW()->Load(&tBuff);
				ResultInItemPI	*r=(ResultInItemPI	*)AItem->GetCurrentResult();
				if(r!=NULL){
					ResultInPagePI	*Rp=r->GetParent();
					if(Rp!=NULL){
						ExecuteInitialAfterEditInfo DummyEInfo;
						DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;

						CmdTryInspectionVar->RetRes=Rp->CreateItem();
						AItem->ExecuteInitialAfterEditPrev	(0,0,CmdTryInspectionVar->RetRes,DummyEInfo);
						AItem->ExecuteInitialAfterEdit		(0,0,CmdTryInspectionVar->RetRes,DummyEInfo);
						AItem->ExecuteInitialAfterEditPost	(0,0,CmdTryInspectionVar->RetRes,DummyEInfo);
						AItem->ResetProcessDone();
						AItem->ExecuteStartByInspection	(0,0,CmdTryInspectionVar->RetRes);
						AItem->ResetProcessDone();
						AItem->ExecuteProcessing		(0,0,CmdTryInspectionVar->RetRes);
						AItem->GetThresholdW()->Load(&BuffEscape);
						CmdTryInspectionVar->RetItem=AItem;
					}
				}
			}
		}
		return;
	}
	CmdResetThresholdDotColorMatching	*CmdResetThresholdDotColorMatchingVar=dynamic_cast<CmdResetThresholdDotColorMatching *>(packet);
	if(CmdResetThresholdDotColorMatchingVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
			Item->GetThresholdW()->SetToOrigin();
		}
		return;
	}
	CmdDotColorMatchingGetItemInfo	*CmdDotColorMatchingGetItemInfoVar=dynamic_cast<CmdDotColorMatchingGetItemInfo *>(packet);
	if(CmdDotColorMatchingGetItemInfoVar!=NULL){
		for(int L=0;L<GetLayerNumb();L++){
			AlgorithmItemPI	*Item=GetItem(CmdDotColorMatchingGetItemInfoVar->LocalX,CmdDotColorMatchingGetItemInfoVar->LocalY);
			if(Item!=NULL){
				DotColorMatchingItem	*BItem=(DotColorMatchingItem *)Item;
				CmdDotColorMatchingGetItemInfoVar->LibIDList.Add(BItem->GetLibID());
				CmdDotColorMatchingGetItemInfoVar->LayerList.Add(L);
			}
		}
		return;
	}
	CmdSetSpecialData	*CmdSetSpecialDataVar=dynamic_cast<CmdSetSpecialData *>(packet);
	if(CmdSetSpecialDataVar!=NULL){
		return;
	}
	CmdAddDotColorMatching	*CmdAddDotColorMatchingVar=dynamic_cast<CmdAddDotColorMatching *>(packet);
	if(CmdAddDotColorMatchingVar!=NULL){
		DotColorMatchingItem	*Item=(DotColorMatchingItem *)CreateItem(0);
		Item->SetArea (CmdAddDotColorMatchingVar->Area);
		Item->SetLibID(CmdAddDotColorMatchingVar->LibID);
		DotColorMatchingBase	*BBase=(DotColorMatchingBase *)GetParentBase(); 
		AlgorithmLibraryLevelContainer	LLib(BBase); 
		if(BBase->GetLibraryContainer()->GetLibrary(CmdAddDotColorMatchingVar->LibID,LLib)==true){ 
			DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(LLib.GetLibrary()); 
			if(ALib!=NULL){ 
				Item->CopyThresholdFromLibrary(&LLib); 
			} 
		}
		Item->SetItemName(CmdAddDotColorMatchingVar->ItemName);
		AppendItem(Item);
	}
	CmdDeleteDotColorMatchingByName	*CmdDeleteDotColorMatchingByNameVar=dynamic_cast<CmdDeleteDotColorMatchingByName *>(packet);
	if(CmdDeleteDotColorMatchingByNameVar!=NULL){
		for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;){
			AlgorithmItemPI	*NextA=a->GetNext();
			if(a->GetItemName()==CmdDeleteDotColorMatchingByNameVar->ItemName){
				RemoveItem(a);
				delete	a;
			}
			a=NextA;
		}
		return;
	}
}

void	DotColorMatchingInPage::Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	DotColorMatchingDrawAttr	*BAttr=dynamic_cast<DotColorMatchingDrawAttr *>(Attr);
			
	if(PickupBmp!=NULL){
		DotColorMatchingBase	*BBase=dynamic_cast<DotColorMatchingBase *>(GetParentBase());
		DrawBitImageOr(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
			,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,BBase->ColorPickup);
	}
	if(BAttr!=NULL){
		DotColorMatchingBase	*BBase=dynamic_cast<DotColorMatchingBase *>(GetParentBase());
		if(BAttr->ModeShowBackGround==true){
			DrawBitImageOr(pnt, EffectiveMap.GetBitMap() ,EffectiveMap.GetXLen() ,EffectiveMap.GetXByte(),EffectiveMap.GetYLen()
				,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
				,0,0
				,BBase->ColorBackGround);
		}
		else{
			AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInPagePI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
	}
}
void	DotColorMatchingInPage::RemoveItemInList(DotColorMatchingItem *Item)
{
	Items1.RemoveItemPoionter(Item);
	Items2.RemoveItemPoionter(Item);
	Items3.RemoveItemPoionter(Item);
	Items4.RemoveItemPoionter(Item);
	Items5.RemoveItemPoionter(Item);
	Items6.RemoveItemPoionter(Item);
}

void	DotColorMatchingInPage::CopyFrom(AlgorithmBase *DestParent
										,AlgorithmInPageRoot *src 
										,int OffsetX,int OffsetY
										,int PartsMaster ,int PartsID
										,bool ReferedThresholdMode)
{



	AlgorithmInPagePI::CopyFrom(DestParent
										,src 
										,OffsetX,OffsetY
										,PartsMaster ,PartsID
										,ReferedThresholdMode);
}

void	DotColorMatchingInPage::MakeOutlineItemsInSelectedItems(int OutlineWidth)
{
	AlgorithmItemPointerListContainer ItemPointers;
	GetSelectedItems(ItemPointers);
	int	XLen	=GetDotPerLine();
	int	XByte	=(XLen+7)/8;
	int	YLen	=GetMaxLines();
	IntList		LibIDList;
	BYTE	**BmpMap=MakeMatrixBuff(XByte ,YLen);
	BYTE	**InsideMap	=MakeMatrixBuff(XByte ,YLen);
	BYTE	**TmpMap	=MakeMatrixBuff(XByte ,YLen);
	BYTE	**OutlineMap=MakeMatrixBuff(XByte ,YLen);

	MatrixBuffClear	(BmpMap ,0 ,XByte ,YLen);
	for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*item=a->GetItem();
		item->GetArea().MakeBitData(BmpMap ,XLen ,YLen);
		LibIDList.Merge(item->GetLibID());
	}
	if(LibIDList.GetCount()==1){
		int64	TestCounter;
		TestCounter=::GetBitCount((const BYTE **)BmpMap ,XByte ,YLen);
		MatrixBuffCopy	(InsideMap,XByte ,YLen
						,(const BYTE **)BmpMap ,XByte ,YLen);
		GetLayersBase()->ThinAreaN(InsideMap,TmpMap,XByte ,YLen,OutlineWidth);
		TestCounter=::GetBitCount((const BYTE **)InsideMap ,XByte ,YLen);

		MatrixBuffCopy	(OutlineMap,XByte ,YLen
						,(const BYTE **)BmpMap ,XByte ,YLen);
		MatrixBuffNotAnd(OutlineMap ,(const BYTE **)InsideMap ,XByte ,YLen);
		TestCounter=::GetBitCount((const BYTE **)OutlineMap ,XByte ,YLen);

		for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*item=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
			if(item!=NULL && item->GetOutlineAttr()==true){
				item->GetArea().MakeNotBitData(OutlineMap ,XLen ,YLen);
			}
		}
		PureFlexAreaListContainer FOutlinePack;
		PickupFlexArea(OutlineMap ,XByte ,XLen,YLen ,FOutlinePack);

		DotColorMatchingBase	*ABase=(DotColorMatchingBase *)GetParentBase();
		AlgorithmLibraryContainer	*ALibC=ABase->GetLibraryContainer();
		AlgorithmLibraryLevelContainer	LibLevelC(ALibC);
		int	LibID=LibIDList.GetFirst()->GetValue();
		if(ALibC->GetLibrary(LibID,LibLevelC)==true){
			DotColorMatchingLibrary	*L=(DotColorMatchingLibrary *)LibLevelC.GetLibrary();
			PureFlexAreaListContainer AreaList;
			L->MakeDotColorMatchingItems(OutlineMap
										,GetPage()
										,XByte ,XLen,YLen
										,AreaList);
			PureFlexAreaList	*m;
			while((m=AreaList.GetFirst())!=NULL){
				AreaList.RemoveList(m);
				for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
					DotColorMatchingItem	*item=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
					if(item!=NULL && item->GetOutlineAttr()==true){
						if(item->GetArea().CheckOverlapNeighbor(m)==true){
							FlexArea	A=item->GetArea();
							A+=*m;
							item->SetArea(A);
							delete	m;
							m=NULL;
							break;
						}
					}
				}
				if(m!=NULL){
					if(m->GetPatternByte()<5){
						delete	m;
						continue;
					}
					DotColorMatchingItem	*v=new DotColorMatchingItem(*m);

					v->CopyThresholdFromLibrary(&LibLevelC);
					v->SetLibID(LibID);
					int	MasterNo=GetLayersBase()->FindBufferInfo(L->MasterNoOriginCode);
					if(MasterNo<0)
						MasterNo=0;
					v->SetMasterNo(MasterNo);
					v->SetOutlineAttr(true);
					AppendItem(v);
					delete	m;
				}
			}
		}
		for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;a=a->GetNext()){
			DotColorMatchingItem	*item=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
			if(item!=NULL && item->GetOutlineAttr()==false){
				for(PureFlexAreaList *t=FOutlinePack.GetFirst();t!=NULL;t=t->GetNext()){
					if(item->GetArea().CheckOverlap(t)==true){
						FlexArea	A=item->GetArea();
						A -= *t;
						item->SetArea(A);
					}
				}
			}
		}
		for(AlgorithmItemPointerList *a=ItemPointers.GetFirst();a!=NULL;){
			AlgorithmItemPointerList *NextA=a->GetNext();
			DotColorMatchingItem	*item=dynamic_cast<DotColorMatchingItem *>(a->GetItem());
			if(item!=NULL && item->GetArea().GetPatternByte()<8){
				ItemPointers.RemoveList(a);
				delete	a;
				RemoveItem(item);
			}
			a=NextA;
		}
	}

	DeleteMatrixBuff(BmpMap		,YLen);
	DeleteMatrixBuff(InsideMap	,YLen);
	DeleteMatrixBuff(TmpMap		,YLen);
	DeleteMatrixBuff(OutlineMap	,YLen);


}
void	DotColorMatchingInPage::UndoAppendManualItem(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		RemoveItem(Item);
		delete	Item;
	}
}

void	DotColorMatchingInPage::UndoGenerateItems(QIODevice *f)
{
	int	DeletedItemCount;
	if(::Load(f,DeletedItemCount)==false)
		return;
	AlgorithmItemPointerListContainer	RemovedItems;
	for(int i=0;i<DeletedItemCount;i++){
		DotColorMatchingItem	*B=(DotColorMatchingItem	*)CreateItem();
		if(B->Load(f,GetLayersBase())==false)
			return;
		RemovedItems.Add(B);
	}
	IntList	AddedItemIDList;
	if(AddedItemIDList.Load(f)==false)
		return;
	for(IntClass *a=AddedItemIDList.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmItemRoot	*Item=SearchIDItem(a->GetValue());
		if(Item!=NULL){
			RemoveItem(Item);
			delete	Item;
		}
	}
	for(AlgorithmItemPointerList *item=RemovedItems.GetFirst();item!=NULL;item=item->GetNext()){
		AppendItem(item->GetItem());
	}
}

void	DotColorMatchingInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		DotColorMatchingItem	*BI=(DotColorMatchingItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}

void	DotColorMatchingInPage::UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)
{
	for(AlgorithmItemPI	*a=GetFirstData();a!=NULL;a=a->GetNext()){
		DotColorMatchingItem	*Item=dynamic_cast<DotColorMatchingItem *>(a);
		if(Item->GetArea().CheckOverlapRectangle(LRes.x1,LRes.y1,LRes.x2,LRes.y2)==true
		&& Item->GetLibID()==LibID){
			Item->UpdateThreshold(LearningMenuID,LRes);
		}
	}
}
//===========================================================================================
DotColorMatchingBase::DotColorMatchingBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	ColorDotColorMatchingNormal	=Qt::darkGreen;
	ColorDotColorMatchingSelected	=Qt::green;
	ColorDotColorMatchingActive	=Qt::red;

	DotColorMatchingColor0	=Qt::green;
	DotColorMatchingColor1	=Qt::yellow;
	DotColorMatchingColor2	=Qt::darkRed;
	DotColorMatchingColor3	=Qt::cyan;
	DotColorMatchingColor4	=Qt::magenta;
	DotColorMatchingColor5	=Qt::darkGreen;
	DotColorMatchingColor6	=Qt::darkYellow;
	DotColorMatchingColor7	=Qt::darkCyan;
	ColorBackGround			=Qt::blue;

	OmitZoneDot			=100;
	NoiseBrightness		=15;
	ClassifiedMethod	=10;
	//SearchDotForBrightnessRange	=1;
	MakeYAB				=false;
	MaxRotation			=15.0;
	
	HookingLineLength	=10;
	EdgeMerginForLine	=8;
	PatternEdgeWidth	=3;
	ThresholdPickupLine	=20;
	LevelDownRateNearOutline	=2.0;
	OutlineZoneWidth	=30;
	FoldingAreaWidth	=150;
	ThresholdComplexPattern	=30;
	//ThresholdFlatPattern	=5;
	RetryItemCount			=20;
	ThresholdWeightForBrDiff=10.0;
	MaxCountOutline			=10;
	CoefSelfSearch			=0.8;
	SearchAreaForVariation	=8;
	ThresholdVariation		=5.0;
	MultiplyParamInOutlineArea	=1.2;
	MultiplyParamInFoldingArea	=1.2;
	ExclusiveLayer				=-1;
	ScratchForBlack				=20;
	MinDivAreaLength		=15;
	MinDivAreaPixels		=10;
	MinTotalDivAreaPixels	=100;
	AcceptionRateGray		=25;
	UseGlobalMultiSpot		=false;
	MasterNoFor2nd			=1;
	MasterScratchFlatness	=3.0;
	DifBrightnessForFlatArea=10;
	MaxAreaSearch			=30;
	MaxNGCountInBlock		=2;
	ModeMatchHighPrecise	=false;
	BackGroundIsolationToEdge=22;
	AdoptedRateForCenterBrightness=95;
	VariationInfluenceArea	=16;

	SetParam(&ColorPickup					, /**/"Color" ,/**/"ColorPickup"					,LangSolver.GetString(XDotColorMatching_LS,LID_0)/*"Color for Image to Pickup-Test "*/);
	SetParam(&ColorDotColorMatchingNormal	, /**/"Color" ,/**/"ColorDotColorMatchingNormal"	,LangSolver.GetString(XDotColorMatching_LS,LID_1)/*"Color for DotColorMatching"*/);
	SetParam(&ColorDotColorMatchingSelected	, /**/"Color" ,/**/"ColorDotColorMatchingSelected"	,LangSolver.GetString(XDotColorMatching_LS,LID_2)/*"Color for Selected DotColorMatching"*/);
	SetParam(&ColorDotColorMatchingActive	, /**/"Color" ,/**/"ColorDotColorMatchingActive"	,LangSolver.GetString(XDotColorMatching_LS,LID_3)/*"Color for Active DotColorMatching"*/);
	SetParam(&ColorBackGround				, /**/"Color" ,/**/"ColorBackGround"				,LangSolver.GetString(XDotColorMatching_LS,LID_20)/*"Color for BackGround"*/);

	SetParam(&DotColorMatchingColor0	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor0"	,LangSolver.GetString(XDotColorMatching_LS,LID_4)/*"DotColorMatching Color 0"*/);
	SetParam(&DotColorMatchingColor1	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor1"	,LangSolver.GetString(XDotColorMatching_LS,LID_5)/*"DotColorMatching Color 1"*/);
	SetParam(&DotColorMatchingColor2	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor2"	,LangSolver.GetString(XDotColorMatching_LS,LID_6)/*"DotColorMatching Color 2"*/);
	SetParam(&DotColorMatchingColor3	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor3"	,LangSolver.GetString(XDotColorMatching_LS,LID_7)/*"DotColorMatching Color 3"*/);
	SetParam(&DotColorMatchingColor4	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor4"	,LangSolver.GetString(XDotColorMatching_LS,LID_8)/*"DotColorMatching Color 4"*/);
	SetParam(&DotColorMatchingColor5	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor5"	,LangSolver.GetString(XDotColorMatching_LS,LID_9)/*"DotColorMatching Color 5"*/);
	SetParam(&DotColorMatchingColor6	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor6"	,LangSolver.GetString(XDotColorMatching_LS,LID_10)/*"DotColorMatching Color 6"*/);
	SetParam(&DotColorMatchingColor7	, /**/"DotColorMatchingColor" ,/**/"DotColorMatchingColor7"	,LangSolver.GetString(XDotColorMatching_LS,LID_11)/*"DotColorMatching Color 7"*/);

	SetParam(&OmitZoneDot				, /**/"Setting"			,/**/"OmitZoneDot"					,LangSolver.GetString(XDotColorMatching_LS,LID_21)/*"Omit zone dot in DotColorMatching generation"*/);
	SetParam(&NoiseBrightness			, /**/"Setting"			,/**/"NoiseBrightness"				,LangSolver.GetString(XDotColorMatching_LS,LID_22)/*"Noise brightness"*/);
	SetParam(&ClassifiedMethod			, /**/"Setting"			,/**/"ClassifiedMethod"				,LangSolver.GetString(XDotColorMatching_LS,LID_23)/*"Variation to classify area matching algorithm"*/);
	SetParam(&MakeYAB					, /**/"Setting"			,/**/"MakeYAB"						,LangSolver.GetString(XDotColorMatching_LS,LID_24)/*"Mode to make YAB map"*/);
	SetParam(&MaxRotation				, /**/"Setting"			,/**/"MaxRotation"					,LangSolver.GetString(XDotColorMatching_LS,LID_25)/*"Max rotated angle (Degree)"*/);
	//SetParam(&ThresholdPickupEdge		, /**/"Setting"			,/**/"ThresholdPickupEdge"			,"Threshold to pick up edge(1.0=standard deviation");
	SetParam(&HookingLineLength			, /**/"Setting"			,/**/"HookingLineLength"			,LangSolver.GetString(XDotColorMatching_LS,LID_26)/*"Line length to hook edge"*/);
	SetParam(&EdgeMerginForLine			, /**/"Setting"			,/**/"EdgeMerginForLine"			,LangSolver.GetString(XDotColorMatching_LS,LID_27)/*"Isolaton to image edge for hook-line"*/);
	SetParam(&PatternEdgeWidth			, /**/"Setting"			,/**/"PatternEdgeWidth"				,LangSolver.GetString(XDotColorMatching_LS,LID_28)/*"Pattern edge(outline) diviation width"*/);
	SetParam(&ThresholdPickupLine		, /**/"Setting"			,/**/"ThresholdPickupLine"			,LangSolver.GetString(XDotColorMatching_LS,LID_29)/*"Threshold brightness to pick up outline lines"*/);
	SetParam(&ExclusiveLayer			, /**/"Setting"			,/**/"ExclusiveLayer"				,LangSolver.GetString(XDotColorMatching_LS,LID_30)/*"Exclusive layer for matching (-1:use all)"*/);
	SetParam(&MasterNoFor2nd			, /**/"Setting"			,/**/"MasterNoFor2nd"				,LangSolver.GetString(XDotColorMatching_LS,LID_31)/*"MasterNo for 2nd master"*/);
	SetParam(&MaxNGCountInBlock			, /**/"Setting"			,/**/"MaxNGCountInBlock"			,LangSolver.GetString(XDotColorMatching_LS,LID_32)/*"Max NG count in one block"*/	,1,100000000);
	SetParam(&AdoptedRateForCenterBrightness, /**/"Setting"		,/**/"AdoptedRateForCenterBrightness",LangSolver.GetString(XDotColorMatching_LS,LID_258)/*"Adopted percentage for center brightness"*/	,0,100);
	SetParam(&LevelDownRateNearOutline	, /**/"Outline"			,/**/"LevelDownRateNearOutline"		,LangSolver.GetString(XDotColorMatching_LS,LID_33)/*"Magnificant value for outline zone"*/);
	SetParam(&OutlineZoneWidth			, /**/"Outline"			,/**/"OutlineZoneWidth"				,LangSolver.GetString(XDotColorMatching_LS,LID_34)/*"Outline zone width"*/);
	SetParam(&FoldingAreaWidth			, /**/"Outline"			,/**/"FoldingAreaWidth"				,LangSolver.GetString(XDotColorMatching_LS,LID_35)/*"Folding area width from outline"*/);
	SetParam(&MaxCountOutline			, /**/"Outline"			,/**/"MaxCountOutline"				,LangSolver.GetString(XDotColorMatching_LS,LID_36)/*"Maximum count of outline in block"*/);
	SetParam(&MultiplyParamInOutlineArea, /**/"Outline"			,/**/"MultiplyParamInOutlineArea"	,LangSolver.GetString(XDotColorMatching_LS,LID_37)/*"Multiply param for SearchArea in Outline area"*/);
	SetParam(&MultiplyParamInFoldingArea, /**/"Outline"			,/**/"MultiplyParamInFoldingArea"	,LangSolver.GetString(XDotColorMatching_LS,LID_38)/*"Multiply param for SearchArea in folding area"*/);

	SetParam(&ThresholdComplexPattern	, /**/"Threshold"		,/**/"ThresholdComplexPattern"		,LangSolver.GetString(XDotColorMatching_LS,LID_39)/*"Threshold for complex pattern (Normally >30)"*/);
	//SetParam(&ThresholdFlatPattern		, /**/"Threshold"		,/**/"ThresholdFlatPattern"			,"Threshold for flat pattern (around 5)");
	SetParam(&ThresholdWeightForBrDiff	, /**/"Threshold"		,/**/"ThresholdWeightForBrDiff"		,LangSolver.GetString(XDotColorMatching_LS,LID_40)/*"Weight threshold for matching by brightness difference"*/);
	SetParam(&CoefSelfSearch			, /**/"Threshold"		,/**/"CoefSelfSearch"				,LangSolver.GetString(XDotColorMatching_LS,LID_41)/*"Threshold of co-efficiency for SelfSearch"*/);
	SetParam(&SearchAreaForVariation	, /**/"Threshold"		,/**/"SearchAreaForVariation"		,LangSolver.GetString(XDotColorMatching_LS,LID_42)/*"Search area to distinguish Flat/Complex area to switch threshold"*/);
	SetParam(&ThresholdVariation		, /**/"Threshold"		,/**/"ThresholdVariation"			,LangSolver.GetString(XDotColorMatching_LS,LID_43)/*"Threshold of Variation to distinguish Flat/Complex area to switch threshold"*/);
	SetParam(&ScratchForBlack			, /**/"Threshold"		,/**/"ScratchForBlack"				,LangSolver.GetString(XDotColorMatching_LS,LID_44)/*"If brightness is less than this, Scratch process doesn't start"*/);
	SetParam(&MinDivAreaLength			, /**/"Threshold"		,/**/"MinDivAreaLength"				, LangSolver.GetString(XDotColorMatching_LS,LID_45)/*"Minimum length of each DivArea"*/);
	SetParam(&MinDivAreaPixels			, /**/"Threshold"		,/**/"MinDivAreaPixels"				, LangSolver.GetString(XDotColorMatching_LS,LID_46)/*"Minimum pixels counts of each DivArea"*/);
	SetParam(&MinTotalDivAreaPixels		, /**/"Threshold"		,/**/"MinTotalDivAreaPixels"		, LangSolver.GetString(XDotColorMatching_LS,LID_47)/*"Minimum pixel counts of total DivArea"*/);
	SetParam(&AcceptionRateGray			, /**/"Threshold"		,/**/"AcceptionRateGray"			, LangSolver.GetString(XDotColorMatching_LS,LID_48)/*"Maximum rate(%) for middle color in UseMaster2"*/);
	SetParam(&MasterScratchFlatness		, /**/"Threshold"		,/**/"MasterScratchFlatness"		, LangSolver.GetString(XDotColorMatching_LS,LID_49)/*"Flatness in Master for Scratch"*/);
	SetParam(&DifBrightnessForFlatArea	, /**/"Threshold"		,/**/"DifBrightnessForFlatArea"		, LangSolver.GetString(XDotColorMatching_LS,LID_50)/*"Magnificant of brightness-difference flatArea"*/);
	SetParam(&MaxAreaSearch				, /**/"Threshold"		,/**/"MaxAreaSearch"				, LangSolver.GetString(XDotColorMatching_LS,LID_51)/*"Maximum search-dot insidely for Block "*/);

	SetParam(&UseGlobalMultiSpot		, /**/"MultiSpot"		,/**/"UseGlobalMultiSpot"			,LangSolver.GetString(XDotColorMatching_LS,LID_52)/*"Use Global MultiSpot"*/);
	SetParam(&BackGroundIsolationToEdge	, /**/"BackGround"		,/**/"BackGroundIsolationToEdge"	,LangSolver.GetString(XDotColorMatching_LS,LID_53)/*"Isolation to edge of Effective-Mask for BackGround"*/);
	SetParam(&VariationInfluenceArea	, /**/"Variation"		,/**/"VariationInfluenceArea"		,LangSolver.GetString(XDotColorMatching_LS,LID_259)/*"Variation Influence Area (Dot)"*/);
	SetParam(&RetryItemCount			, /**/"Retry"			,/**/"RetryItemCount"				,LangSolver.GetString(XDotColorMatching_LS,LID_54)/*"NG Item count to retry by larger area"*/);
	SetParam(&ModeMatchHighPrecise		, /**/"Retry"			,/**/"ModeMatchHighPrecise"			,LangSolver.GetString(XDotColorMatching_LS,LID_55)/*"Retry to match in high precision"*/);

	ModeParallelForPhase.ModeParallelExecuteInitialAfterEdit=false;
}

AlgorithmDrawAttr	*DotColorMatchingBase::CreateDrawAttr(void)
{
	return new DotColorMatchingDrawAttr();
}

void	DotColorMatchingBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetDotColorMatchingLibraryListPacket	*AListPacket=dynamic_cast<CmdGetDotColorMatchingLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
												,AListPacket->AList);
		}
		return;
	}
	CmdGetDotColorMatchingLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetDotColorMatchingLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertDotColorMatchingLibraryPacket	*BInsLib=dynamic_cast<CmdInsertDotColorMatchingLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(DotColorMatchingInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateDotColorMatchingLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateDotColorMatchingLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(DotColorMatchingInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadDotColorMatchingLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadDotColorMatchingLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		return;
	}
	CmdCreateTempDotColorMatchingLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempDotColorMatchingLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearDotColorMatchingLibraryPacket	*CmdClearDotColorMatchingLibraryPacketVar=dynamic_cast<CmdClearDotColorMatchingLibraryPacket *>(packet);
	if(CmdClearDotColorMatchingLibraryPacketVar!=NULL){
		CmdClearDotColorMatchingLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteDotColorMatchingLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteDotColorMatchingLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestDotColorMatchingPacket	*BPickLib=dynamic_cast<CmdPickupTestDotColorMatchingPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		DotColorMatchingInPage	*Bp=dynamic_cast<DotColorMatchingInPage *>(p);
		if(Bp==NULL)
			return;
		DotColorMatchingLibrary	*ALib=dynamic_cast<DotColorMatchingLibrary *>(BPickLib->LibPoint->GetLibrary());
		if(ALib!=NULL){
			Bp->PickupTest(*ALib);
		}
		return;
	}
	CmdGenerateDotColorMatchingPacket	*BGenerated=dynamic_cast<CmdGenerateDotColorMatchingPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			if(GetLibraryContainer()!=NULL){
				GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
			}
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				DotColorMatchingLibrary	*Index1=dynamic_cast<DotColorMatchingLibrary *>(LibDim[i  ]->GetLibrary());
				DotColorMatchingLibrary	*Index2=dynamic_cast<DotColorMatchingLibrary *>(LibDim[i+1]->GetLibrary());
				if(Index1->Priority>Index2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(GetLibraryContainer());
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			DotColorMatchingInPage	*Bp=dynamic_cast<DotColorMatchingInPage *>(p);
			if(Bp!=NULL){
				DotColorMatchingLibrary	**DDim=new DotColorMatchingLibrary*[N];
				for(int i=0;i<N;i++){
					DDim[i]=dynamic_cast<DotColorMatchingLibrary *>(LibDim[i]->GetLibrary());
				}
				Bp->GenerateDotColorMatchings(DDim,N);
				delete	[]DDim;
			}
		}
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempDotColorMatchingItemPacket	*CreateDotColorMatchingItem=dynamic_cast<CmdCreateTempDotColorMatchingItemPacket *>(packet);
	if(CreateDotColorMatchingItem!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		CreateDotColorMatchingItem->Point=(DotColorMatchingItem	*)p->CreateItem(0);
		return;
	}
	CmdCreateByteArrayFromDotColorMatchingItemPacket	*BAFromDotColorMatchingItem=dynamic_cast<CmdCreateByteArrayFromDotColorMatchingItemPacket *>(packet);
	if(BAFromDotColorMatchingItem!=NULL){
		QBuffer	Buff(&BAFromDotColorMatchingItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromDotColorMatchingItem->Point->Save(&Buff);
		return;
	}
	CmdAddByteDotColorMatchingItemPacket	*AddBItem=dynamic_cast<CmdAddByteDotColorMatchingItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePI		*PData=dynamic_cast<AlgorithmInPagePI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			DotColorMatchingInPage	*Bp=dynamic_cast<DotColorMatchingInPage *>(PData);
			if(Bp!=NULL){
				QBuffer	MBuff(&AddBItem->Buff);
				DotColorMatchingItem	*Item=(DotColorMatchingItem	*)PData->CreateItem(0);
				MBuff.open(QIODevice::ReadWrite);
				Item->Load(&MBuff,GetLayersBase());
				Item->SetArea(AddBItem->Area);
				Item->SetManualCreated(true);
				Bp->AppendItem(Item);

				UndoElement<DotColorMatchingInPage>	*UPointer=new UndoElement<DotColorMatchingInPage>(Bp,&DotColorMatchingInPage::UndoAppendManualItem);
				::Save(UPointer->GetWritePointer(),Item->GetID());
				Item->Save(UPointer->GetWritePointer());
				GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
			}
		}
		return;
	}
	CmdLoadDotColorMatchingItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadDotColorMatchingItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
		return;
	}
	CmdModifySelectedDotColorMatchingFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedDotColorMatchingFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}
	CmdGetDotColorMatchingLibName	*PCmdGetLibName=dynamic_cast<CmdGetDotColorMatchingLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdClearTestDotColorMatchingPacket	*CmdClearTestDotColorMatchingPacketVar=dynamic_cast<CmdClearTestDotColorMatchingPacket *>(packet);
	if(CmdClearTestDotColorMatchingPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestDotColorMatchingPacketVar);
		}
		return;
	}

	CmdGetDotColorMatchingFromList	*CmdGetDotColorMatchingFromListVar=dynamic_cast<CmdGetDotColorMatchingFromList *>(packet);
	if(CmdGetDotColorMatchingFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetDotColorMatchingFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateDotColorMatchingItem	*CmdCreateDotColorMatchingItemVar=dynamic_cast<CmdCreateDotColorMatchingItem *>(packet);
	if(CmdCreateDotColorMatchingItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdDotColorMatchingSetAdded	*CmdDotColorMatchingSetAddedVar=dynamic_cast<CmdDotColorMatchingSetAdded *>(packet);
	if(CmdDotColorMatchingSetAddedVar!=NULL){
		for(ListPageLayerID *t=CmdDotColorMatchingSetAddedVar->Items.GetFirst();t!=NULL;t=t->GetNext()){
			AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(GetPageData(t->Page));
			if(Ap!=NULL){
				AlgorithmItemRoot	*item	=Ap->SearchIDItem(t->ID);
				if(item!=NULL){
					DotColorMatchingItem	*d=dynamic_cast<DotColorMatchingItem *>(item);

					DotColorMatchingThreshold	*m=d->GetThresholdW();
					m->AddedBrightness	=Clipping((int)(CmdDotColorMatchingSetAddedVar->AddBrightness),-10,10);
					m->AddedOffset		=Clipping((int)(CmdDotColorMatchingSetAddedVar->AddOffset),-10,10);
					m->AddedShift		=Clipping((int)(CmdDotColorMatchingSetAddedVar->AddShift),-10,10);
				}
			}
		}
		return;
	}
	CmdCreateThreshold	*CmdCreateThresholdVar=dynamic_cast<CmdCreateThreshold *>(packet);
	if(CmdCreateThresholdVar!=NULL){
		CmdCreateThresholdVar->Item=new DotColorMatchingItem();
		CmdCreateThresholdVar->Threshold=(DotColorMatchingThreshold *)CmdCreateThresholdVar->Item->CreateThresholdInstance();
		return;
	}
	CmdDotColorMatchingSendTryThreshold	*CmdDotColorMatchingSendTryThresholdVar=dynamic_cast<CmdDotColorMatchingSendTryThreshold *>(packet);
	if(CmdDotColorMatchingSendTryThresholdVar!=NULL){
		CmdDotColorMatchingSendTryThresholdVar->PTry=new DotColorMatchingSendTryThreshold();
		CmdDotColorMatchingSendTryThresholdVar->Target=new DotColorMatchingItem();
		AlgorithmInPagePI		*Ap=(AlgorithmInPagePI *)(CmdDotColorMatchingSendTryThresholdVar->Src->GetParentInPage());
		CmdDotColorMatchingSendTryThresholdVar->Target->SetParent(Ap);
		QBuffer	Buff(&CmdDotColorMatchingSendTryThresholdVar->ThresholdDataForTarget);
		Buff.open(QIODevice::ReadWrite);
		CmdDotColorMatchingSendTryThresholdVar->Target->GetThresholdW()->Load(&Buff);
		CmdDotColorMatchingSendTryThresholdVar->PTry->Calc( CmdDotColorMatchingSendTryThresholdVar->Target
														   ,CmdDotColorMatchingSendTryThresholdVar->Src
														   ,this);
		return;
	}														
}

bool	DotColorMatchingBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==DotColorMatchingHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingReqRotationMasterImageCommand){
		delete	data;
		return true;
	}
	else if(Command==DotColorMatchingSendRotationMasterImageCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*DotColorMatchingBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==DotColorMatchingHistogramListSendCommand){
		DotColorMatchingHistogramListSend	*pSend=new DotColorMatchingHistogramListSend();
		if(reqData!=NULL){
			DotColorMatchingHistogramListReq	*req=(DotColorMatchingHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==DotColorMatchingHistogramListReqCommand){
		return new DotColorMatchingHistogramListReq();
	}
	else if(Command==DotColorMatchingReqThresholdReqCommand){
		return new DotColorMatchingThresholdReq();
	}
	else if(Command==DotColorMatchingReqThresholdSendCommand){
		DotColorMatchingThresholdSend	*pSend=new DotColorMatchingThresholdSend();
		if(reqData!=NULL){
			DotColorMatchingThresholdReq	*req=(DotColorMatchingThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==DotColorMatchingReqTryThresholdCommand){
		return new DotColorMatchingReqTryThreshold();
	}
	else if(Command==DotColorMatchingSendTryThresholdCommand){
		DotColorMatchingSendTryThreshold	*pSend=new DotColorMatchingSendTryThreshold();
		if(reqData!=NULL){
			DotColorMatchingReqTryThreshold	*req=(DotColorMatchingReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==DotColorMatchingReqChangeShiftCommand){
		return new DotColorMatchingChangeShift();
	}
	else if(Command==DotColorMatchingReqRotationMasterImageCommand){
		return new DotColorMatchingReqRotationMasterImage();
	}
	else if(Command==DotColorMatchingSendRotationMasterImageCommand){
		DotColorMatchingSendRotationMasterImage	*pSend=new DotColorMatchingSendRotationMasterImage();
		if(reqData!=NULL){
			DotColorMatchingReqRotationMasterImage	*req=(DotColorMatchingReqRotationMasterImage *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	DotColorMatchingBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==DotColorMatchingHistogramListSendCommand){
		DotColorMatchingHistogramListSend	*p=(DotColorMatchingHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingHistogramListReqCommand){
		DotColorMatchingHistogramListReq	*p=(DotColorMatchingHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingReqThresholdReqCommand){
		DotColorMatchingThresholdReq	*p=(DotColorMatchingThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingReqThresholdSendCommand){
		DotColorMatchingThresholdSend	*p=(DotColorMatchingThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingReqTryThresholdCommand){
		DotColorMatchingReqTryThreshold	*p=(DotColorMatchingReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==DotColorMatchingSendTryThresholdCommand){
		DotColorMatchingSendTryThreshold	*p=(DotColorMatchingSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingReqChangeShiftCommand){
		DotColorMatchingChangeShift	*p=(DotColorMatchingChangeShift *)data;
		return p->Load(f);
	}
	else if(Command==DotColorMatchingReqRotationMasterImageCommand){
		DotColorMatchingReqRotationMasterImage	*p=(DotColorMatchingReqRotationMasterImage *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==DotColorMatchingSendRotationMasterImageCommand){
		DotColorMatchingSendRotationMasterImage	*p=(DotColorMatchingSendRotationMasterImage *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	DotColorMatchingBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==DotColorMatchingHistogramListSendCommand){
		DotColorMatchingHistogramListSend	*p=(DotColorMatchingHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingHistogramListReqCommand){
		DotColorMatchingHistogramListReq	*p=(DotColorMatchingHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingReqThresholdReqCommand){
		DotColorMatchingThresholdReq	*p=(DotColorMatchingThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingReqThresholdSendCommand){
		DotColorMatchingThresholdSend	*p=(DotColorMatchingThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingReqTryThresholdCommand){
		DotColorMatchingReqTryThreshold	*p=(DotColorMatchingReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingSendTryThresholdCommand){
		DotColorMatchingSendTryThreshold	*p=(DotColorMatchingSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingReqChangeShiftCommand){
		DotColorMatchingChangeShift	*p=(DotColorMatchingChangeShift *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingReqRotationMasterImageCommand){
		DotColorMatchingReqRotationMasterImage	*p=(DotColorMatchingReqRotationMasterImage *)data;
		return p->Save(f);
	}
	else if(Command==DotColorMatchingSendRotationMasterImageCommand){
		DotColorMatchingSendRotationMasterImage	*p=(DotColorMatchingSendRotationMasterImage *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	DotColorMatchingBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==DotColorMatchingHistogramListSendCommand){
		DotColorMatchingHistogramListSend	*p=(DotColorMatchingHistogramListSend *)data;
		return true;
	}
	else if(Command==DotColorMatchingHistogramListReqCommand){
		DotColorMatchingHistogramListReq	*p=(DotColorMatchingHistogramListReq *)data;
		return true;
	}
	else if(Command==DotColorMatchingReqThresholdReqCommand){
		DotColorMatchingThresholdReq	*p=(DotColorMatchingThresholdReq *)data;
		return true;
	}
	else if(Command==DotColorMatchingReqThresholdSendCommand){
		DotColorMatchingThresholdSend	*p=(DotColorMatchingThresholdSend *)data;
		return true;
	}
	else if(Command==DotColorMatchingReqTryThresholdCommand){
		DotColorMatchingReqTryThreshold	*p=(DotColorMatchingReqTryThreshold *)data;
		return true;
	}
	else if(Command==DotColorMatchingSendTryThresholdCommand){
		DotColorMatchingSendTryThreshold	*p=(DotColorMatchingSendTryThreshold *)data;
		return true;
	}
	else if(Command==DotColorMatchingReqChangeShiftCommand){
		DotColorMatchingChangeShift	*p=(DotColorMatchingChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else if(Command==DotColorMatchingReqRotationMasterImageCommand){
		DotColorMatchingReqRotationMasterImage	*p=(DotColorMatchingReqRotationMasterImage *)data;
		return true;
	}
	else if(Command==DotColorMatchingSendRotationMasterImageCommand){
		DotColorMatchingSendRotationMasterImage	*p=(DotColorMatchingSendRotationMasterImage *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

int	DotColorMatchingBase::GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)
{
	if(MaxDimCount>=4){
		MenuPointer[0].MenuMessage	=LangSolver.GetString(XDotColorMatching_LS,LID_56)/*"鬮ｮ雜｣ｽｼｽｶｽｲ鬯ｩ蟷｢ｽ｢髫ｴ雜｣ｽ｢ｽｽｽｻ鬯ｯｮｽｴ髯懈瑳ｺｷ霎｣蜻ｻｽｺｽｦ鬯ｩ謳ｾｽｵｽｺ鬯ｮｦｽｮｽｫK"*/;
		MenuPointer[0].MenuID		=LearningMenu_DotColorMatching_OK_BroadByBrightness;
		MenuPointer[0].OkMode		=true;
		MenuPointer[1].MenuMessage	=LangSolver.GetString(XDotColorMatching_LS,LID_57)/*"鬯ｮｯ隶灘･ｽｽｻ郢ｧ謇假ｽｽｽｽｽｽｧ鬯ｩ謳ｾｽｵｽｺ鬯ｯｮｽｦｽｪｽｸｽｺｽｧOK"*/;
		MenuPointer[1].MenuID		=LearningMenu_DotColorMatching_OK_BroadBySize;
		MenuPointer[1].OkMode		=true;
		MenuPointer[2].MenuMessage	=LangSolver.GetString(XDotColorMatching_LS,LID_58)/*"鬯ｩ蟷｢ｽ｢ｽｧｽｺ鬯ｩ蟷｢ｽ｢髫ｴ雜｣ｽ｢ｽｽｽｬ鬯ｩ謳ｾｽｵｽｺｽｧOK"*/;
		MenuPointer[2].MenuID		=LearningMenu_DotColorMatching_OK_ByShift;
		MenuPointer[2].OkMode		=true;
		MenuPointer[3].MenuMessage	=LangSolver.GetString(XDotColorMatching_LS,LID_59)/*"鬮ｮ雜｣ｽｼｽｶｽｲ鬯ｩ蟷｢ｽ｢髫ｴ雜｣ｽ｢ｽｽｽｻ鬯ｯｮｽｴ髯懈瑳ｺｷ霎｣蜻ｻｽｺｽｦ鬯ｩ謳ｾｽｵｽｺｽｧNG"*/;
		MenuPointer[3].MenuID		=LearningMenu_DotColorMatching_NG_BroadByBrightness;
		MenuPointer[3].OkMode		=false;
		MenuPointer[4].MenuMessage	=LangSolver.GetString(XDotColorMatching_LS,LID_60)/*"鬯ｮｯ隶灘･ｽｽｻ郢ｧ謇假ｽｽｽｽｽｽｧ鬯ｩ謳ｾｽｵｽｺ鬯ｯｮｽｦｽｪｽｸｽｺｽｧNG"*/;
		MenuPointer[4].MenuID		=LearningMenu_DotColorMatching_NG_BroadSize;
		MenuPointer[4].OkMode		=false;
		return 5;
	}
	return 0;
}
QString	DotColorMatchingBase::GetNameByCurrentLanguage(void)
{
	return LangSolver.GetString(XDotColorMatching_LS,LID_12)/*"鬩幢ｽ｢隴取得ｽｳｽｨ驛｢譎｢ｽ｣鬩幢ｽ｢隴惹ｹ暦ｽｲｺｽｯ鬩募争豎夲ｿｽｽｽｼｽ､髫ｲ蟶帶ｲｺｽｸ*/;
}

bool	DotColorMatchingBase::AvailableGenerateBlock(void)	const
{
	return true;
}

//===========================================================================================


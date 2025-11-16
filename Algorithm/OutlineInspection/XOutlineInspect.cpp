/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\OutlineInspection\XOutlineInspect.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "OutlineInspectionResource.h"

#define	_USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include "XOutlineInspect.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XCriticalFunc.h"
#include "XParamGlobal.h"
#include "XPSpline.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "swap.h"
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XDisplayBitImage.h"
#include <omp.h>
#include "XOutlineAlgoPacket.h"

extern	char	*sRoot;
extern	char	*sName;

OutlineHistogramListReq::OutlineHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	OutlineHistogramListReq::Save(QIODevice *f)
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
	return true;
}
bool	OutlineHistogramListReq::Load(QIODevice *f)
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
	return true;
}


OutlineHistogramListSend::OutlineHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMasterInside		,0,sizeof(ListMasterInside));
	memset(ListMasterTrInside	,0,sizeof(ListMasterTrInside));
	memset(ListMasterOutside	,0,sizeof(ListMasterOutside));
	memset(ListMasterTrOutside	,0,sizeof(ListMasterTrOutside));
	memset(ListTargetInside		,0,sizeof(ListTargetInside));
	memset(ListTargetTrInside	,0,sizeof(ListTargetTrInside));
	memset(ListTargetOutside	,0,sizeof(ListTargetOutside));
	memset(ListTargetTrOutside	,0,sizeof(ListTargetTrOutside));

	InsideCenterColorOnMaster	=0;
	InsideTrCenterColorOnMaster	=0;
	OutsideCenterColorOnMaster	=0;
	OutsideTrCenterColorOnMaster=0;
	InsideCenterColorOnTarget	=0;
	InsideTrCenterColorOnTarget	=0;
	OutsideCenterColorOnTarget	=0;
	OutsideTrCenterColorOnTarget=0;
}
void	OutlineHistogramListSend::ConstructList(OutlineHistogramListReq *reqPacket ,OutlineBase *Base)
{
	memset(ListMasterInside		,0,sizeof(ListMasterInside));
	memset(ListMasterTrInside	,0,sizeof(ListMasterTrInside));
	memset(ListMasterOutside	,0,sizeof(ListMasterOutside));
	memset(ListMasterTrOutside	,0,sizeof(ListMasterTrOutside));
	memset(ListTargetInside		,0,sizeof(ListTargetInside));
	memset(ListTargetTrInside	,0,sizeof(ListTargetTrInside));
	memset(ListTargetOutside	,0,sizeof(ListTargetOutside));
	memset(ListTargetTrOutside	,0,sizeof(ListTargetTrOutside));

	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(BlockItemID);
			if(item!=NULL){
				OutlineItem	*Item=dynamic_cast<OutlineItem*>(item);
				bool	BuiltList=false;
				if(Item->IsOriginParts()==true){
					PieceClass	*Pc=NULL;
					Pc=Base->GetLayersBase()->GetPieceStock()->SearchOnly(item->GetPartsID());
					if(Pc!=NULL){
						QString DLLRoot ,DLLName;
						Base->GetAlgorithmRootName(DLLRoot ,DLLName);
						//AlgorithmItemRoot	*PItem=Pc->GetAlgorithmItem(DLLRoot,DLLName,Layer ,item->GetPartsItemID());
						//PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
						BuiltList=true;
					}
				}
				if(BuiltList==false){
					Item->InsideAlgo.Area	.MakeBrightList(ListMasterInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
					Item->InsideAlgo.TrArea	.MakeBrightList(ListMasterTrInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
					Item->OutsideAlgo.Area	.MakeBrightList(ListMasterOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
					Item->OutsideAlgo.TrArea.MakeBrightList(ListMasterTrOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);

					InsideCenterColorOnMaster	=Item->InsideAlgo	.CenterColorOnMaster;
					InsideTrCenterColorOnMaster	=Item->InsideAlgo	.TrCenterColorOnMaster;
					OutsideCenterColorOnMaster	=Item->OutsideAlgo	.CenterColorOnMaster;
					OutsideTrCenterColorOnMaster=Item->OutsideAlgo	.TrCenterColorOnMaster;
					InsideCenterColorOnTarget	=0;
					InsideTrCenterColorOnTarget	=0;
					OutsideCenterColorOnTarget	=0;
					OutsideTrCenterColorOnTarget=0;
				}
				ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());
					ResultBasePhase		*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
					ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
					if(Rp!=NULL){
						ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
						ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());
						if(rItem!=NULL){
							int	sx,sy;
							rItem->GetTotalShifted(sx,sy);
							Item->InsideAlgo.Area	.MakeBrightList(ListTargetInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
							Item->InsideAlgo.TrArea	.MakeBrightList(ListTargetTrInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
							Item->OutsideAlgo.Area	.MakeBrightList(ListTargetOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
							Item->OutsideAlgo.TrArea.MakeBrightList(ListTargetTrOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);

							InsideCenterColorOnTarget	=Item->InsideAlgo	.Area	.GetAverage(Item->GetTargetBuff(),sx ,sy);
							InsideTrCenterColorOnTarget	=Item->InsideAlgo	.TrArea	.GetAverage(Item->GetTargetBuff(),sx ,sy);
							OutsideCenterColorOnTarget	=Item->OutsideAlgo	.Area	.GetAverage(Item->GetTargetBuff(),sx ,sy);
							OutsideTrCenterColorOnTarget=Item->OutsideAlgo	.TrArea	.GetAverage(Item->GetTargetBuff(),sx ,sy);
						}
						else{
							Item->InsideAlgo.Area	.MakeBrightList(ListTargetInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
							Item->InsideAlgo.TrArea	.MakeBrightList(ListTargetTrInside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
							Item->OutsideAlgo.Area	.MakeBrightList(ListTargetOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
							Item->OutsideAlgo.TrArea.MakeBrightList(ListTargetTrOutside	,Item->GetDotPerLine(),Item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);

							InsideCenterColorOnTarget	=Item->InsideAlgo	.Area	.GetAverage(Item->GetTargetBuff(),0 ,0);
							InsideTrCenterColorOnTarget	=Item->InsideAlgo	.TrArea	.GetAverage(Item->GetTargetBuff(),0 ,0);
							OutsideCenterColorOnTarget	=Item->OutsideAlgo	.Area	.GetAverage(Item->GetTargetBuff(),0 ,0);
							OutsideTrCenterColorOnTarget=Item->OutsideAlgo	.TrArea	.GetAverage(Item->GetTargetBuff(),0 ,0);
						}
					}
				}
			}
		}
	}
}

bool	OutlineHistogramListSend::Save(QIODevice *f)
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
	if(f->write((const char *)ListMasterInside		,sizeof(ListMasterInside))	!=sizeof(ListMasterInside))
		return false;
	if(f->write((const char *)ListMasterTrInside	,sizeof(ListMasterTrInside))!=sizeof(ListMasterTrInside))
		return false;
	if(f->write((const char *)ListMasterOutside		,sizeof(ListMasterOutside))	!=sizeof(ListMasterOutside))
		return false;
	if(f->write((const char *)ListMasterTrOutside	,sizeof(ListMasterTrOutside))!=sizeof(ListMasterTrOutside))
		return false;
	if(f->write((const char *)ListTargetInside		,sizeof(ListTargetInside))	!=sizeof(ListTargetInside))
		return false;
	if(f->write((const char *)ListTargetTrInside	,sizeof(ListTargetTrInside))!=sizeof(ListTargetTrInside))
		return false;
	if(f->write((const char *)ListTargetOutside		,sizeof(ListTargetOutside))	!=sizeof(ListTargetOutside))
		return false;
	if(f->write((const char *)ListTargetTrOutside	,sizeof(ListTargetTrOutside))!=sizeof(ListTargetTrOutside))
		return false;
	if(::Save(f,InsideCenterColorOnMaster)==false)
		return false;
	if(::Save(f,InsideTrCenterColorOnMaster)==false)
		return false;
	if(::Save(f,OutsideCenterColorOnMaster)==false)
		return false;
	if(::Save(f,OutsideTrCenterColorOnMaster)==false)
		return false;
	if(::Save(f,InsideCenterColorOnTarget)==false)
		return false;
	if(::Save(f,InsideTrCenterColorOnTarget)==false)
		return false;
	if(::Save(f,OutsideCenterColorOnTarget)==false)
		return false;
	if(::Save(f,OutsideTrCenterColorOnTarget)==false)
		return false;
	return true;
}
bool	OutlineHistogramListSend::Load(QIODevice *f)
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
	if(f->read((char *)ListMasterInside		,sizeof(ListMasterInside))	!=sizeof(ListMasterInside))
		return false;
	if(f->read((char *)ListMasterTrInside	,sizeof(ListMasterTrInside))!=sizeof(ListMasterTrInside))
		return false;
	if(f->read((char *)ListMasterOutside		,sizeof(ListMasterOutside))	!=sizeof(ListMasterOutside))
		return false;
	if(f->read((char *)ListMasterTrOutside	,sizeof(ListMasterTrOutside))!=sizeof(ListMasterTrOutside))
		return false;
	if(f->read((char *)ListTargetInside		,sizeof(ListTargetInside))	!=sizeof(ListTargetInside))
		return false;
	if(f->read((char *)ListTargetTrInside	,sizeof(ListTargetTrInside))!=sizeof(ListTargetTrInside))
		return false;
	if(f->read((char *)ListTargetOutside		,sizeof(ListTargetOutside))	!=sizeof(ListTargetOutside))
		return false;
	if(f->read((char *)ListTargetTrOutside	,sizeof(ListTargetTrOutside))!=sizeof(ListTargetTrOutside))
		return false;
	if(::Load(f,InsideCenterColorOnMaster)==false)
		return false;
	if(::Load(f,InsideTrCenterColorOnMaster)==false)
		return false;
	if(::Load(f,OutsideCenterColorOnMaster)==false)
		return false;
	if(::Load(f,OutsideTrCenterColorOnMaster)==false)
		return false;
	if(::Load(f,InsideCenterColorOnTarget)==false)
		return false;
	if(::Load(f,InsideTrCenterColorOnTarget)==false)
		return false;
	if(::Load(f,OutsideCenterColorOnTarget)==false)
		return false;
	if(::Load(f,OutsideTrCenterColorOnTarget)==false)
		return false;
	return true;
}

OutlineThresholdReq::OutlineThresholdReq(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	OutlineThresholdReq::Save(QIODevice *f)
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
	return true;
}
bool	OutlineThresholdReq::Load(QIODevice *f)
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
	return true;
}

OutlineThresholdSend::OutlineThresholdSend(void)
{
	GlobalPage	=-1;
	Layer		=-1;
	BlockItemID	=-1;
	Mastered	=true;
	Dx=0;
	Dy=0;
}

void	OutlineThresholdSend::ConstructList(OutlineThresholdReq *reqPacket,OutlineBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	Layer		=reqPacket->Layer;
	BlockItemID	=reqPacket->BlockItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	LayersBase	*LBase=Base->GetLayersBase();
	int	localPage=LBase->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*Al=(AlgorithmInLayerPLI *)Ap->GetLayerData(Layer);
		if(Al!=NULL){
			AlgorithmItemRoot	*item	=Al->SearchIDItem(BlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				OutlineItem	*BItem=(OutlineItem *)item;
				const OutlineThreshold	*RThr=BItem->GetThresholdR(LBase);
				MatchSlideOnMaster	=RThr->MatchSlideOnMaster;
				DiffMode			=RThr->DiffMode;

				InsideNOKColor		=RThr->InsideNOKColor;
				InsideNTrOKColor	=RThr->InsideNTrOKColor;
				InsideNOKDot		=RThr->InsideNOKDot;
				InsideNMergin		=RThr->InsideNMergin;
				OutsideNOKColor		=RThr->OutsideNOKColor;
				OutsideNTrOKColor	=RThr->OutsideNTrOKColor;
				OutsideNOKDot		=RThr->OutsideNOKDot;
				OutsideNMergin		=RThr->OutsideNMergin;

				InsideBOKColor		=RThr->InsideBOKColor;
				InsideBTrOKColor	=RThr->InsideBTrOKColor;
				InsideBOKDot		=RThr->InsideBOKDot;
				InsideBMergin		=RThr->InsideBMergin;
				OutsideBOKColor		=RThr->OutsideBOKColor;
				OutsideBTrOKColor	=RThr->OutsideBTrOKColor;
				OutsideBOKDot		=RThr->OutsideBOKDot;
				OutsideBMergin		=RThr->OutsideBMergin;

				EffectiveNInside	=RThr->EffectiveNInside;
				EffectiveNOutside	=RThr->EffectiveNOutside;
				EffectiveBInside	=RThr->EffectiveBInside;
				EffectiveBOutside	=RThr->EffectiveBOutside;

				SelfSearch			=RThr->SelfSearch;
				AdjustMode			=RThr->AdjustMode;
				AdjustLimitLInside	=RThr->AdjustLimitLInside;
				AdjustLimitHInside	=RThr->AdjustLimitHInside;
				AdjustLimitLOutside	=RThr->AdjustLimitLOutside;
				AdjustLimitHOutside	=RThr->AdjustLimitHOutside;
				AbsMode				=RThr->AbsMode;
			}
		}
	}
}

bool	OutlineThresholdSend::Save(QIODevice *f)
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

	if(InsideNOKColor.Save(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideNOKDot)==false){
		return false;
	}
	if(::Save(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Save(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideNMergin)==false){
		return false;
	}

	if(InsideBOKColor.Save(f)==false){
		return false;
	}
	if(InsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideBOKDot)==false){
		return false;
	}
	if(::Save(f,InsideBMergin)==false){
		return false;
	}
	if(OutsideBOKColor.Save(f)==false){
		return false;
	}
	if(OutsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideBOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideBMergin)==false){
		return false;
	}

	if(::Save(f,EffectiveNInside)==false){
		return false;
	}
	if(::Save(f,EffectiveNOutside)==false){
		return false;
	}
	if(::Save(f,EffectiveBInside)==false){
		return false;
	}
	if(::Save(f,EffectiveBOutside)==false){
		return false;
	}

	if(::Save(f,SelfSearch)==false){
		return false;
	}
	if(::Save(f,AdjustMode)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHInside)==false){
		return false;
	}
	if(::Save(f,MatchSlideOnMaster)==false){
		return false;
	}
	if(::Save(f,DiffMode)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLOutside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHOutside)==false){
		return false;
	}
	if(::Save(f,AbsMode)==false){
		return false;
	}
	return true;
}
bool	OutlineThresholdSend::Load(QIODevice *f)
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

	if(InsideNOKColor.Load(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,InsideNOKDot)==false){
		return false;
	}
	if(::Load(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Load(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Load(f,OutsideNMergin)==false){
		return false;
	}

	if(InsideBOKColor.Load(f)==false){
		return false;
	}
	if(InsideBTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,InsideBOKDot)==false){
		return false;
	}
	if(::Load(f,InsideBMergin)==false){
		return false;
	}
	if(OutsideBOKColor.Load(f)==false){
		return false;
	}
	if(OutsideBTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,OutsideBOKDot)==false){
		return false;
	}
	if(::Load(f,OutsideBMergin)==false){
		return false;
	}

	if(::Load(f,EffectiveNInside)==false){
		return false;
	}
	if(::Load(f,EffectiveNOutside)==false){
		return false;
	}
	if(::Load(f,EffectiveBInside)==false){
		return false;
	}
	if(::Load(f,EffectiveBOutside)==false){
		return false;
	}

	if(::Load(f,SelfSearch)==false){
		return false;
	}
	if(::Load(f,AdjustMode)==false){
		return false;
	}
	if(::Load(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Load(f,AdjustLimitHInside)==false){
		return false;
	}
	if(::Load(f,MatchSlideOnMaster)==false){
		return false;
	}
	if(::Load(f,DiffMode)==false){
		return false;
	}
	if(::Load(f,AdjustLimitLOutside)==false){
		return false;
	}
	if(::Load(f,AdjustLimitHOutside)==false){
		return false;
	}
	if(::Load(f,AbsMode)==false){
		return false;
	}
	return true;
}

OutlineReqTryThreshold::OutlineReqTryThreshold(void)
{
	Layer	=0;
	GlobalPage=-1;
	BlockItemID=-1;
}
bool	OutlineReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,Layer			)==false)
		return false;
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,BlockItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	OutlineReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,Layer			)==false)
		return false;
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,BlockItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

OutlineSendTryThreshold::OutlineSendTryThreshold(void)
{
	NGDotInInsideN	=0;
	NGDotInOutsideN	=0;
	NGDotInInsideB	=0;
	NGDotInOutsideB	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error			=0;
}

bool	OutlineSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInInsideN	)==false)
		return false;
	if(::Save(f,NGDotInOutsideN	)==false)
		return false;
	if(::Save(f,NGDotInInsideB	)==false)
		return false;
	if(::Save(f,NGDotInOutsideB	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	return true;
}
bool	OutlineSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInInsideN	)==false)
		return false;
	if(::Load(f,NGDotInOutsideN	)==false)
		return false;
	if(::Load(f,NGDotInInsideB	)==false)
		return false;
	if(::Load(f,NGDotInOutsideB	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	return true;
}

void	OutlineSendTryThreshold::ConstructList(OutlineReqTryThreshold *reqPacket,OutlineBase *Base)
{
	ResultInItemPLI	Res;
	Res.SetAddedData(this,1,sizeof(this));
	OutlineInPage		*BP=(OutlineInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		AlgorithmInLayerPLI	*Al=(AlgorithmInLayerPLI *)BP->GetLayerData(reqPacket->Layer);
		if(Al!=NULL){
			OutlineItem		*BI=(OutlineItem *)Al->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				
				reqPacket->Threshold.MatchingDotCount	=BI->MatchingDotCount;
				reqPacket->Threshold.MatchingLayer		=BI->MatchingLayer;
				reqPacket->Threshold.MasterAdd			=BI->MasterAdd;
				reqPacket->Threshold.MasterAdd2			=BI->MasterAdd2;

				reqPacket->Threshold.InsideCenterColorOnMaster	=BI->InsideCenterColorOnMaster;
				reqPacket->Threshold.OutsideCenterColorOnMaster	=BI->OutsideCenterColorOnMaster;
				reqPacket->Threshold.InsideAlgo			=BI->InsideAlgo;
				reqPacket->Threshold.OutsideAlgo		=BI->OutsideAlgo;
				reqPacket->Threshold.MatchingArea		=BI->MatchingArea;
				reqPacket->Threshold.ClusterID			=BI->ClusterID;

				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.SetArea(BI->GetArea());

				ExecuteInitialAfterEditInfo EInfo;
				reqPacket->Threshold.ExecuteInitialAfterEdit(0,0,&Res,EInfo);
				reqPacket->Threshold.AVector			=BI->AVector;
				reqPacket->Threshold.ExecuteStartByInspection(0,0,&Res);
				reqPacket->Threshold.ExecuteProcessing		 (0,0,&Res);
				NGDotInInsideN	=reqPacket->Threshold.MaxNGDotInsideN;
				NGDotInOutsideN	=reqPacket->Threshold.MaxNGDotOutsideN;
				NGDotInInsideB	=reqPacket->Threshold.MaxNGDotInsideB;
				NGDotInOutsideB	=reqPacket->Threshold.MaxNGDotOutsideB;
			}
		}
	}
	Res.SetAddedData(NULL,0);

	ResultMoveDx=Res.GetTotalShiftedX();
	ResultMoveDy=Res.GetTotalShiftedY();
}

//===============================================================================================

OutlineThreshold::OutlineThreshold(AlgorithmItemRoot *parent)
:AlgorithmThreshold(parent)
{
	MatchSlideOnMaster	=true;
	InsideNOKDot	=5;
	InsideNMergin	=10;
	OutsideNOKDot	=5;
	OutsideNMergin	=10;

	InsideBOKDot	=5;
	InsideBMergin	=10;
	OutsideBOKDot	=5;
	OutsideBMergin	=10;

	EffectiveNInside	=true;
	EffectiveNOutside	=true;
	EffectiveBInside	=false;
	EffectiveBOutside	=true;

	SelfSearch			=0;
	AdjustMode			=true;
	AdjustLimitLInside	=20;
	AdjustLimitHInside	=20;
	AdjustLimitLOutside	=20;
	AdjustLimitHOutside	=20;
	DiffMode			=false;
	AbsMode				=false;
}

void	OutlineThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const OutlineThreshold	*s=dynamic_cast<const OutlineThreshold *>(&src);
	if(s!=NULL){
		MatchSlideOnMaster	=s->MatchSlideOnMaster;
		InsideNOKColor		=s->InsideNOKColor;
		InsideNTrOKColor	=s->InsideNTrOKColor;
		InsideNOKDot		=s->InsideNOKDot;
		InsideNMergin		=s->InsideNMergin;
		OutsideNOKColor		=s->OutsideNOKColor;
		OutsideNTrOKColor	=s->OutsideNTrOKColor;
		OutsideNOKDot		=s->OutsideNOKDot;
		OutsideNMergin		=s->OutsideNMergin;

		InsideBOKColor		=s->InsideBOKColor;
		InsideBTrOKColor	=s->InsideBTrOKColor;
		InsideBOKDot		=s->InsideBOKDot;
		InsideBMergin		=s->InsideBMergin;
		OutsideBOKColor		=s->OutsideBOKColor;
		OutsideBTrOKColor	=s->OutsideBTrOKColor;
		OutsideBOKDot		=s->OutsideBOKDot;
		OutsideBMergin		=s->OutsideBMergin;

		EffectiveNInside	=s->EffectiveNInside;
		EffectiveNOutside	=s->EffectiveNOutside;
		EffectiveBInside	=s->EffectiveBInside;
		EffectiveBOutside	=s->EffectiveBOutside;

		SelfSearch			=s->SelfSearch;		/*	????C???@?T?o?????	*/
		AdjustMode			=s->AdjustMode;
		AdjustLimitLInside	=s->AdjustLimitLInside;
		AdjustLimitHInside	=s->AdjustLimitHInside;
		AdjustLimitLOutside	=s->AdjustLimitLOutside;
		AdjustLimitHOutside	=s->AdjustLimitHOutside;
		DiffMode			=s->DiffMode;
		AbsMode				=s->AbsMode;
	}
}
bool	OutlineThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const OutlineThreshold	*s=dynamic_cast<const OutlineThreshold *>(&src);
	if(s!=NULL){
		if(MatchSlideOnMaster	!=s->MatchSlideOnMaster	)	return false;
		if(InsideNOKColor		!=s->InsideNOKColor		)	return false;
		if(InsideNTrOKColor		!=s->InsideNTrOKColor	)	return false;
		if(InsideNOKDot			!=s->InsideNOKDot		)	return false;
		if(InsideNMergin		!=s->InsideNMergin		)	return false;
		if(OutsideNOKColor		!=s->OutsideNOKColor	)	return false;
		if(OutsideNTrOKColor	!=s->OutsideNTrOKColor	)	return false;
		if(OutsideNOKDot		!=s->OutsideNOKDot		)	return false;
		if(OutsideNMergin		!=s->OutsideNMergin		)	return false;

		if(InsideBOKColor		!=s->InsideBOKColor		)	return false;
		if(InsideBTrOKColor		!=s->InsideBTrOKColor	)	return false;
		if(InsideBOKDot			!=s->InsideBOKDot		)	return false;
		if(InsideBMergin		!=s->InsideBMergin		)	return false;
		if(OutsideBOKColor		!=s->OutsideBOKColor	)	return false;
		if(OutsideBTrOKColor	!=s->OutsideBTrOKColor	)	return false;
		if(OutsideBOKDot		!=s->OutsideBOKDot		)	return false;
		if(OutsideBMergin		!=s->OutsideBMergin		)	return false;

		if(EffectiveNInside		!=s->EffectiveNInside	)	return false;
		if(EffectiveNOutside	!=s->EffectiveNOutside	)	return false;
		if(EffectiveBInside		!=s->EffectiveBInside	)	return false;
		if(EffectiveBOutside	!=s->EffectiveBOutside	)	return false;

		if(SelfSearch			!=s->SelfSearch			)	return false;
		if(AdjustMode			!=s->AdjustMode			)	return false;
		if(AdjustLimitLInside	!=s->AdjustLimitLInside	)	return false;
		if(AdjustLimitHInside	!=s->AdjustLimitHInside	)	return false;
		if(AdjustLimitLOutside	!=s->AdjustLimitLOutside)	return false;
		if(AdjustLimitHOutside	!=s->AdjustLimitHOutside)	return false;
		if(DiffMode				!=s->DiffMode			)	return false;
		if(AbsMode				!=s->AbsMode			)	return false;

		return true;
	}
	return false;
}
bool	OutlineThreshold::Save(QIODevice *f)
{
	int32	Ver=OutlineInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(InsideNOKColor.Save(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideNOKDot)==false){
		return false;
	}
	if(::Save(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Save(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideNMergin)==false){
		return false;
	}

	if(InsideBOKColor.Save(f)==false){
		return false;
	}
	if(InsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,InsideBOKDot)==false){
		return false;
	}
	if(::Save(f,InsideBMergin)==false){
		return false;
	}
	if(OutsideBOKColor.Save(f)==false){
		return false;
	}
	if(OutsideBTrOKColor.Save(f)==false){
		return false;
	}
	if(::Save(f,OutsideBOKDot)==false){
		return false;
	}
	if(::Save(f,OutsideBMergin)==false){
		return false;
	}

	if(::Save(f,EffectiveNInside)==false){
		return false;
	}
	if(::Save(f,EffectiveNOutside)==false){
		return false;
	}
	if(::Save(f,EffectiveBInside)==false){
		return false;
	}
	if(::Save(f,EffectiveBOutside)==false){
		return false;
	}

	if(::Save(f,SelfSearch)==false){
		return false;
	}
	if(::Save(f,AdjustMode)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHInside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitLOutside)==false){
		return false;
	}
	if(::Save(f,AdjustLimitHOutside)==false){
		return false;
	}
	if(::Save(f,MatchSlideOnMaster)==false){
		return false;
	}
	if(::Save(f,DiffMode)==false){
		return false;
	}
	if(::Save(f,AbsMode)==false){
		return false;
	}
	return true;
}
	

bool	OutlineThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(InsideNOKColor.Load(f)==false){
		return false;
	}
	if(InsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,InsideNOKDot)==false){
		return false;
	}
	if(::Load(f,InsideNMergin)==false){
		return false;
	}
	if(OutsideNOKColor.Load(f)==false){
		return false;
	}
	if(OutsideNTrOKColor.Load(f)==false){
		return false;
	}
	if(::Load(f,OutsideNOKDot)==false){
		return false;
	}
	if(::Load(f,OutsideNMergin)==false){
		return false;
	}

	if(Ver>=2){
		if(InsideBOKColor.Load(f)==false){
			return false;
		}
		if(InsideBTrOKColor.Load(f)==false){
			return false;
		}
		if(::Load(f,InsideBOKDot)==false){
			return false;
		}
		if(::Load(f,InsideBMergin)==false){
			return false;
		}
		if(OutsideBOKColor.Load(f)==false){
			return false;
		}
		if(OutsideBTrOKColor.Load(f)==false){
			return false;
		}
		if(::Load(f,OutsideBOKDot)==false){
			return false;
		}
		if(::Load(f,OutsideBMergin)==false){
			return false;
		}
	}

	if(Ver>=3){
		if(::Load(f,EffectiveNInside)==false){
			return false;
		}
		if(::Load(f,EffectiveNOutside)==false){
			return false;
		}
		if(::Load(f,EffectiveBInside)==false){
			return false;
		}
		if(::Load(f,EffectiveBOutside)==false){
			return false;
		}
	}
	else{
		EffectiveNInside	=true;
		EffectiveNOutside	=true;
		EffectiveBInside	=false;
		EffectiveBOutside	=true;
	}

	if(::Load(f,SelfSearch)==false){
		return false;
	}
	if(::Load(f,AdjustMode)==false){
		return false;
	}
	if(::Load(f,AdjustLimitLInside)==false){
		return false;
	}
	if(::Load(f,AdjustLimitHInside)==false){
		return false;
	}
	AdjustLimitLOutside=AdjustLimitLInside;
	AdjustLimitHOutside=AdjustLimitHInside;
	if(Ver>=5){
		if(::Load(f,AdjustLimitLOutside)==false){
			return false;
		}
		if(::Load(f,AdjustLimitHOutside)==false){
			return false;
		}
	}
	if(Ver>=4){
		if(::Load(f,MatchSlideOnMaster)==false){
			return false;
		}
		if(::Load(f,DiffMode)==false){
			return false;
		}
	}
	if(Ver>=6){
		if(::Load(f,AbsMode)==false){
			return false;
		}
	}
	return true;
}

void	OutlineThreshold::FromLibrary(AlgorithmLibrary *src)
{
	OutlineInspectLibrary	*s=dynamic_cast<OutlineInspectLibrary *>(src);
	if(s!=NULL){
		MatchSlideOnMaster	=s->MatchSlideOnMaster;
		InsideNOKColor		=s->InsideNOKColor;
		InsideNTrOKColor	=s->InsideNTrOKColor;
		InsideNOKDot		=s->InsideNOKDot;
		InsideNMergin		=s->InsideNMergin;
		OutsideNOKColor		=s->OutsideNOKColor;
		OutsideNTrOKColor	=s->OutsideNTrOKColor;
		OutsideNOKDot		=s->OutsideNOKDot;
		OutsideNMergin		=s->OutsideNMergin;

		InsideBOKColor		=s->InsideBOKColor;
		InsideBTrOKColor	=s->InsideBTrOKColor;
		InsideBOKDot		=s->InsideBOKDot;
		InsideBMergin		=s->InsideBMergin;
		OutsideBOKColor		=s->OutsideBOKColor;
		OutsideBTrOKColor	=s->OutsideBTrOKColor;
		OutsideBOKDot		=s->OutsideBOKDot;
		OutsideBMergin		=s->OutsideBMergin;

		EffectiveNInside	=s->EffectiveNInside;
		EffectiveNOutside	=s->EffectiveNOutside;
		EffectiveBInside	=s->EffectiveBInside;
		EffectiveBOutside	=s->EffectiveBOutside;

		SelfSearch			=s->SelfSearch;
		AdjustMode			=s->AdjustMode;
		AdjustLimitLInside	=s->AdjustLimitLInside;
		AdjustLimitHInside	=s->AdjustLimitHInside;
		AdjustLimitLOutside	=s->AdjustLimitLOutside;
		AdjustLimitHOutside	=s->AdjustLimitHOutside;
		DiffMode			=s->DiffMode;
		AbsMode				=s->AbsMode;
	}
}
void	OutlineThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	OutlineInspectLibrary	*d=dynamic_cast<OutlineInspectLibrary *>(Dest);
	if(d!=NULL){
		d->MatchSlideOnMaster	=MatchSlideOnMaster;
		d->InsideNOKColor		=InsideNOKColor;
		d->InsideNTrOKColor		=InsideNTrOKColor;
		d->InsideNOKDot			=InsideNOKDot;
		d->InsideNMergin		=InsideNMergin;
		d->OutsideNOKColor		=OutsideNOKColor;
		d->OutsideNTrOKColor	=OutsideNTrOKColor;
		d->OutsideNOKDot		=OutsideNOKDot;
		d->OutsideNMergin		=OutsideNMergin;

		d->InsideBOKColor		=InsideBOKColor;
		d->InsideBTrOKColor		=InsideBTrOKColor;
		d->InsideBOKDot			=InsideBOKDot;
		d->InsideBMergin		=InsideBMergin;
		d->OutsideBOKColor		=OutsideBOKColor;
		d->OutsideBTrOKColor	=OutsideBTrOKColor;
		d->OutsideBOKDot		=OutsideBOKDot;
		d->OutsideBMergin		=OutsideBMergin;

		d->EffectiveNInside		=EffectiveNInside;
		d->EffectiveNOutside	=EffectiveNOutside;
		d->EffectiveBInside		=EffectiveBInside;
		d->EffectiveBOutside	=EffectiveBOutside;

		d->SelfSearch			=SelfSearch;
		d->AdjustMode			=AdjustMode;
		d->AdjustLimitLInside	=AdjustLimitLInside;
		d->AdjustLimitHInside	=AdjustLimitHInside;
		d->AdjustLimitLOutside	=AdjustLimitLOutside;
		d->AdjustLimitHOutside	=AdjustLimitHOutside;
		d->DiffMode				=DiffMode;
		d->AbsMode				=AbsMode;
	}
}

//===============================================================================================
OutlineItem::AlgoCalcStruct::AlgoCalcStruct(OutlineItem	*parent)
:Parent(parent)
{
	BMap=NULL;
}

void	OutlineItem::AlgoCalcStruct::Initial(void)
{
	if(BMap==NULL){
		int	x11=Area.GetMinX();
		int	y11=Area.GetMinY();
		int	x12=Area.GetMaxX();
		int	y12=Area.GetMaxY();
		int	x21=TrArea.GetMinX();
		int	y21=TrArea.GetMinY();
		int	x22=TrArea.GetMaxX();
		int	y22=TrArea.GetMaxY();
		int	W=max(x22,x12)-min(x21,x11);
		int	H=max(y22,y12)-min(y21,y11);
		XByte=(W+7)/8+1;
		YLen=H+1;
		BMap=MakeMatrixBuff(XByte,YLen);
	}
}
void	OutlineItem::AlgoCalcStruct::Release(void)
{
	if(BMap!=NULL){
		DeleteMatrixBuff(BMap,YLen);
		BMap=NULL;
		XByte=0;
		YLen=0;
	}
}
void	OutlineItem::AlgoCalcStruct::MoveTo(int dx, int dy)
{
	Area	.MoveToNoClip(dx,dy);
	TrArea	.MoveToNoClip(dx,dy);
	ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
}

void	OutlineItem::AlgoCalcStruct::ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed)
{
	ImageBuffer	*a=&Parent->GetMasterBuff();

	double	Col;
	double	ColTr;

	Col		=Area.GetAverage(*a,0 ,0);
	ColTr	=TrArea.GetAverage(*a,0 ,0);

	CenterColorOnMaster		=Col;
	TrCenterColorOnMaster	=ColTr;
}
void	OutlineItem::AlgoCalcStruct::ExecuteStartByInspection(void)
{
	Initial();
	MatrixBuffClear(BMap,0,XByte,YLen);
}

OutlineItem::AlgoCalcStruct	&OutlineItem::AlgoCalcStruct::operator=(OutlineItem::AlgoCalcStruct &src)
{
	Area=src.Area;
	TrArea=src.TrArea;
	Initial();
	CenterColorOnMaster		=src.CenterColorOnMaster;
	TrCenterColorOnMaster	=src.TrCenterColorOnMaster;
	
	return *this;
}

OutlineItem::OutlineItem(void)
:InsideAlgo(this),OutsideAlgo(this)
{
	AVector=NULL;
	MatchingLayer=0;
	MasterAdd=0;
	MasterAdd2=0;
	ResultSearchX		=0;	//?A?E?I?U?R?E
	ResultSearchY		=0;
	ResultDotSumInside	=0;
	ResultDotSumOutside	=0;
	MoveXForSelf		=0;
	MoveYForSelf		=0;
}
OutlineItem::~OutlineItem(void)
{
}

void	OutlineItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	OutlineItem	*ASrc=dynamic_cast<OutlineItem *>(src);
	if(ASrc!=NULL){
		InsideAlgo.Area		.SetRefereneFrom(&ASrc->InsideAlgo.Area);
		InsideAlgo.Area		.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		InsideAlgo.TrArea	.SetRefereneFrom(&ASrc->InsideAlgo.Area);
		InsideAlgo.TrArea	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		OutsideAlgo.Area	.SetRefereneFrom(&ASrc->OutsideAlgo.Area);
		OutsideAlgo.Area	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		OutsideAlgo.TrArea	.SetRefereneFrom(&ASrc->OutsideAlgo.Area);
		OutsideAlgo.TrArea	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		int	OmitZoneDot=((OutlineBase *)GetParentBase())->OmitZoneDot;
		GetArea()			.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		InsideAlgo.Area		.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		InsideAlgo.TrArea	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		OutsideAlgo.Area	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		OutsideAlgo.TrArea	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		InsideAlgo.CenterColorOnMaster		=ASrc->InsideAlgo	.CenterColorOnMaster;
		InsideAlgo.TrCenterColorOnMaster	=ASrc->InsideAlgo	.TrCenterColorOnMaster;
		OutsideAlgo.CenterColorOnMaster		=ASrc->OutsideAlgo	.CenterColorOnMaster;
		OutsideAlgo.TrCenterColorOnMaster	=ASrc->OutsideAlgo	.TrCenterColorOnMaster;
	}
}

void	OutlineItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	OutlineDrawAttr	*OAttr=dynamic_cast<OutlineDrawAttr *>(Attr);
	if(OAttr!=NULL){
		if(OAttr->DType==CmdOutlineDrawModePacket::_Edge){
			AlgorithmItemPLI::DrawArea(InsideAlgo.Area,pnt, movx ,movy ,ZoomRate ,OAttr);
			AlgorithmItemPLI::DrawArea(OutsideAlgo.Area,pnt, movx ,movy ,ZoomRate ,OAttr);
		}
		if(OAttr->DType==CmdOutlineDrawModePacket::_Inside){
			AlgorithmItemPLI::DrawArea(InsideAlgo.TrArea,pnt, movx ,movy ,ZoomRate ,OAttr);
			AlgorithmItemPLI::DrawArea(OutsideAlgo.TrArea,pnt, movx ,movy ,ZoomRate ,OAttr);
		}
		if(OAttr->DType==CmdOutlineDrawModePacket::_Area){
			AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,OAttr);
		}
	}
}
void	OutlineItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	a(196,100,0);
			a.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,a.rgba()
							,ZoomRate ,MovX ,MovY);
			QColor	c=Qt::red;
			c.setAlpha(100);
			InsideAlgo.Area.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			OutsideAlgo.Area.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			InsideAlgo.TrArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			OutsideAlgo.TrArea.Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
								,&IData ,c.rgba()
								,ZoomRate ,MovX ,MovY);
			if(ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.setPen(Qt::yellow);
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()!=1){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"I:")+QString::number(Res->GetResult1()) +QString(/**/" O:")+QString::number(Res->GetResult2())
							,&rect);
						PData.drawText(kx,ky+32,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"Unique(")+QString::number(Res->GetItemSearchedX()) +QString(/**/",")+QString::number(Res->GetItemSearchedY())+QString(/**/")")
							,&rect);
					}
				}
			}
		}
	}
}

bool	OutlineItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;
	if(InsideAlgo.Area.Save(file)==false){
		return false;
	}
	if(InsideAlgo.TrArea.Save(file)==false){
		return false;
	}
	if(OutsideAlgo.Area.Save(file)==false){
		return false;
	}
	if(OutsideAlgo.TrArea.Save(file)==false){
		return false;
	}
	if(MatchingArea.Save(file)==false){
		return false;
	}
	if(::Save(file,ClusterID)==false){
		return false;
	}
	if(::Save(file,MoveXForSelf)==false){
		return false;
	}
	if(::Save(file,MoveYForSelf)==false){
		return false;
	}
	return true;
}
bool	OutlineItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	if(InsideAlgo.Area.Load(file)==false){
		return false;
	}
	if(InsideAlgo.TrArea.Load(file)==false){
		return false;
	}
	if(OutsideAlgo.Area.Load(file)==false){
		return false;
	}
	if(OutsideAlgo.TrArea.Load(file)==false){
		return false;
	}
	if(MatchingArea.Load(file)==false){
		return false;
	}
	if(::Load(file,ClusterID)==false){
		return false;
	}
	if(::Load(file,MoveXForSelf)==false){
		return false;
	}
	if(::Load(file,MoveYForSelf)==false){
		return false;
	}
	return true;
}

static	int	DbgID=59;
static	int	DbgNumer=0;

ExeResult	OutlineItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
													,ResultInItemRoot *Res
													,ExecuteInitialAfterEditInfo &EInfo)
{
	if(GetID()==DbgID)
		DbgNumer++;

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL){
		AVector->Set(this);
	}
	InsideAlgo.Initial();
	InsideAlgo.ExecuteInitialAfterEdit(EInfo.ExecuteInitialAfterEdit_Changed);

	OutsideAlgo.Initial();
	OutsideAlgo.ExecuteInitialAfterEdit(EInfo.ExecuteInitialAfterEdit_Changed);

	if(CalcSelf()==false){
		CalcSelf();
	}
	InsideAlgo.ExecuteInitialAfterEdit(EInfo.ExecuteInitialAfterEdit_Changed);
	OutsideAlgo.ExecuteInitialAfterEdit(EInfo.ExecuteInitialAfterEdit_Changed);

	MasterAdd	=0;
	MasterAdd2	=0;
	MatchingDotCount=0;
	ImageBuffer	*MBuff=&GetMasterBuff();
	int	N=MatchingArea.GetFLineLen();
	for(int i=0;i<N;i++){
		int	Y	=MatchingArea.GetFLineAbsY(i);
		int	x1	=MatchingArea.GetFLineLeftX(i);
		int	x2	=MatchingArea.GetFLineRightX(i);
		BYTE	*s=MBuff->GetY(Y);
		int	iAdd=0;
		int	iAdd2=0;
		for(int x=x1;x<x2;x++){
			int	c=s[x];
			iAdd	+=c;
			iAdd2	+=c*c;
			MatchingDotCount++;
		}
		MasterAdd	+=iAdd;
		MasterAdd2	+=iAdd2;
	}

	return _ER_true;
}

ExeResult	OutlineItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{	
	InsideAlgo.ExecuteStartByInspection();
	OutsideAlgo.ExecuteStartByInspection();
	return _ER_true;
}

ExeResult	OutlineItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	if(GetID()==DbgID)
		DbgNumer++;

	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	MatchingFit(mx,my);
	
	CalcDecision(Res ,mx ,my);

	return _ER_true;
}


void	OutlineItem::MatchingFit(int mx,int my)
{
	ImageBuffer	*MBuff=&GetMasterBuff();
	ImageBuffer	*TBuff=&GetTargetBuff();

	if(MBuff->IsNull()==false && TBuff->IsNull()==false){
		int	SearchDot=GetThresholdR()->SelfSearch;
		double	MaxD=0;
		int		ix=0;
		int		iy=0;
		for(int y=-SearchDot;y<=SearchDot;y+=2){
			for(int x=-SearchDot;x<=SearchDot;x+=2){
				double	D=MatchingCalcFull(MBuff,TBuff,mx+x,my+y);
				if(D>MaxD){
					MaxD=D;
					ix=x;
					iy=y;
				}
			}
		}
		MaxD=0;
		int	hx=0;
		int	hy=0;
		for(int y=-1;y<=1;y++){
			for(int x=-1;x<=1;x++){
				double	D=MatchingCalcFull(MBuff,TBuff,mx+ix+x,my+iy+y);
				if(D>MaxD){
					MaxD=D;
					hx=x;
					hy=y;
				}
			}
		}
		ResultSearchX=ix+hx;
		ResultSearchY=iy+hy;
	}
}

void	OutlineItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((OutlineItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((OutlineItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((OutlineItem *)Data));
		}
	}
	else if(Command==SetIndependentItemDataCommand_Optimize){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			QBuffer	Buff(&Something);
			Buff.open(QIODevice::ReadWrite);
			double NExtendRate,BExtendRate;
			::Load(&Buff,NExtendRate);
			::Load(&Buff,BExtendRate);
			bool	AbsMode;
			::Load(&Buff,AbsMode);
			GetThresholdW()->AbsMode=AbsMode;
			OptimizeForMaster(NExtendRate,BExtendRate);
		}
	}
	else if(Command==SetIndependentItemDataCommand_OptimizeAll){
		if(GetLibID()==((OutlineItem *)Data)->GetLibID()){
			QBuffer	Buff(&Something);
			Buff.open(QIODevice::ReadWrite);
			double NExtendRate,BExtendRate;
			::Load(&Buff,NExtendRate);
			::Load(&Buff,BExtendRate);
			bool	AbsMode;
			::Load(&Buff,AbsMode);
			GetThresholdW()->AbsMode=AbsMode;
			OptimizeForMaster(NExtendRate,BExtendRate);
		}
	}
}
void	OutlineItem::CopyThresholdOnly(OutlineItem &src)
{
	GetThresholdW()->CopyFrom(*((OutlineThreshold *)src.GetThresholdR()));
}

void	OutlineItem::OptimizeForMaster(double NExtendRate,double BExtendRate)
/*
	NExtendRate:?P?x???E??}?I?W???d?|??P???l?d?A??E?a?P?x???E?A?Z??E?e
	BExtendRate:?P?x???E??}?I?W???d?|??P???l?d?A??E?a?P?x???E?A?Z??E?e
*/
{
	int	ListMasterInside[256];
	int	ListMasterTrInside[256];
	int	ListMasterOutside[256];
	int	ListMasterTrOutside[256];

	memset(ListMasterInside		,0,sizeof(ListMasterInside));
	memset(ListMasterTrInside	,0,sizeof(ListMasterTrInside));
	memset(ListMasterOutside	,0,sizeof(ListMasterOutside));
	memset(ListMasterTrOutside	,0,sizeof(ListMasterTrOutside));

	InsideAlgo	.Area	.MakeBrightList(ListMasterInside	,GetDotPerLine(),GetMaxLines(),GetMasterBuff(),0 ,0);
	InsideAlgo	.TrArea	.MakeBrightList(ListMasterTrInside	,GetDotPerLine(),GetMaxLines(),GetMasterBuff(),0 ,0);
	OutsideAlgo	.Area	.MakeBrightList(ListMasterOutside	,GetDotPerLine(),GetMaxLines(),GetMasterBuff(),0 ,0);
	OutsideAlgo	.TrArea	.MakeBrightList(ListMasterTrOutside	,GetDotPerLine(),GetMaxLines(),GetMasterBuff(),0 ,0);

	int	ColL,ColH;
	int	iColL,iColH;
	int	W ,WPlus;

	InsideAlgo.Initial();
	InsideAlgo.ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);

	OutsideAlgo.Initial();
	OutsideAlgo.ExecuteInitialAfterEdit(ExecuteInitialAfterEdit_ChangedAlgorithm);
	const OutlineThreshold	*RThr=GetThresholdR();
	if(RThr->DiffMode==true
	|| RThr->AbsMode==true){
		GetTopBottom(ListMasterInside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideNOKColor.SetRelMonoRange(iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideBOKColor.SetRelMonoRange(iColL,iColH);

		GetTopBottom(ListMasterTrInside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideNTrOKColor.SetRelMonoRange(iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideBTrOKColor.SetRelMonoRange(iColL,iColH);
	
		GetTopBottom(ListMasterOutside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideNOKColor.SetRelMonoRange(iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideBOKColor.SetRelMonoRange(iColL,iColH);

		GetTopBottom(ListMasterTrOutside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideNTrOKColor.SetRelMonoRange(iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideBTrOKColor.SetRelMonoRange(iColL,iColH);
	}
	else{
		GetTopBottom(ListMasterInside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideNOKColor.SetAbsMonoRange(InsideAlgo.CenterColorOnMaster,iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideBOKColor.SetAbsMonoRange(InsideAlgo.CenterColorOnMaster,iColL,iColH);

		GetTopBottom(ListMasterTrInside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideNTrOKColor.SetAbsMonoRange(InsideAlgo.TrCenterColorOnMaster,iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->InsideBTrOKColor.SetAbsMonoRange(InsideAlgo.TrCenterColorOnMaster,iColL,iColH);
	
		GetTopBottom(ListMasterOutside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideNOKColor.SetAbsMonoRange(OutsideAlgo.CenterColorOnMaster,iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideBOKColor.SetAbsMonoRange(OutsideAlgo.CenterColorOnMaster,iColL,iColH);

		GetTopBottom(ListMasterTrOutside,ColL,ColH);
		W=ColH-ColL;
		WPlus=W*NExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideNTrOKColor.SetAbsMonoRange(OutsideAlgo.TrCenterColorOnMaster,iColL,iColH);
		WPlus=W*BExtendRate/2;
		iColH=ColH+WPlus;
		iColL=ColL-WPlus;
		GetThresholdW()->OutsideBTrOKColor.SetAbsMonoRange(OutsideAlgo.TrCenterColorOnMaster,iColL,iColH);
	}
}

void	OutlineItem::GetTopBottom(int BrList[] ,int &ColL ,int &ColH)
{
	ColL=0;
	ColH=255;
	for(int i=0;i<256;i++){
		if(BrList[i]!=0){
			ColL=i-1;
			if(ColL<0){
				ColL=0;
			}
			break;
		}
	}
	for(int i=255;i>=0;i--){
		if(BrList[i]!=0){
			ColH=i+1;
			if(ColH>255){
				ColH=255;
			}
			break;
		}
	}
}
void	OutlineItem::CutArea(FlexArea &localArea,bool &_Changed)
{
	if(GetEditLocked()==false  && GetVisible()==true && GetArea().CheckOverlap(&localArea)==true){
		FlexArea	A=GetArea();
		A.Sub(GetArea(), localArea);
		SetArea(A);

		InsideAlgo.CutArea(localArea);
		OutsideAlgo.CutArea(localArea);

		FlexArea	M=MatchingArea;
		M.Sub(MatchingArea, localArea);
		MatchingArea=M;

		_Changed=true;
	}
}

//===============================================================================================

OutlineInLayer::OutlineInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	PickupBmp=NULL;
	PickupBmpYLen=0;
	PickupBmpXByte=0;
}

OutlineInLayer::~OutlineInLayer(void)
{
	if(PickupBmp!=NULL)
		DeleteMatrixBuff(PickupBmp,PickupBmpYLen);
	PickupBmp=NULL;
	PickupBmpYLen=0;
}

void	OutlineInLayer::CreatePickupBmpBuff(void)
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

bool	OutlineInLayer::UseLibraryForMaskingInOtherPage(int LibID)
{
	bool	LimitedMaskInOtherPage=false;
	int		CurrentGlobalPage=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
	for(int globalpage=0;globalpage<GetLayersBase()->GetGlobalPageNumb();globalpage++){
		if(CurrentGlobalPage==globalpage){
			continue;
		}
		SlaveCommReqLibraryInMaskOfOutline	RCmd(GetLayersBase(),sRoot,sName,globalpage);
		SlaveCommAckLibraryInMaskOfOutline	ACmd(GetLayersBase(),sRoot,sName,globalpage);
		RCmd.UsedLibraries.Add(LibID);
		if(RCmd.Send(globalpage,0,ACmd)==true){
			if(ACmd.UsedLibraries.IsIncluded(LibID)==true){
				LimitedMaskInOtherPage=true;
			}
		}
	}
	return LimitedMaskInOtherPage;
}
void	OutlineInLayer::PickupTest(OutlineInspectLibrary &Lib)
{
	bool	LimitedMaskInOtherPage=UseLibraryForMaskingInOtherPage(Lib.GetLibID());
	bool	LimitedMaskInThisPage =IncludeLibInReflection(_Reflection_Mask,&Lib,NULL);
	if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
		ConstMapBuffer MaskMap;
		GetReflectionMap(_Reflection_Mask,MaskMap,&Lib);
		CreatePickupBmpBuff();
		Pickup(&Lib  ,PickupBmp,PickupBmpXByte ,PickupBmpYLen,MaskMap.GetBitMap());

		PureFlexAreaListContainer ResPack;
		WashAreas(&Lib ,PickupBmp,PickupBmpXByte ,PickupBmpYLen,ResPack);

		MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		for(PureFlexAreaList *a=ResPack.GetFirst();a!=NULL;a=a->GetNext()){
			a->MakeBitData(PickupBmp ,PickupBmpXByte*8 ,PickupBmpYLen);
		}
	}
}

BYTE	**OutlineInLayer::GetCutLineMaskBitmap(void)
{
	AlgorithmInPageRoot	*LPLI=GetParentInPage()->GetAlgorithm(/**/"Basic" ,/**/"Masking");
	if(LPLI!=NULL){
		CmdCreateCutLineBitmapPacket		CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.BmpMap=MakeMatrixBuff(CmdPacket.XByte,CmdPacket.YLen);
		MatrixBuffClear(CmdPacket.BmpMap ,0 ,CmdPacket.XByte,CmdPacket.YLen);
		LPLI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	return NULL;
}


void	OutlineInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetOutlineFromList	*CmdGetOutlineFromListVar=dynamic_cast<CmdGetOutlineFromList *>(packet);
	if(CmdGetOutlineFromListVar!=NULL){
		OutlineItem *Item=(OutlineItem *)SearchIDItem(CmdGetOutlineFromListVar->CurrentItem.GetFirst()->ID);
		CmdGetOutlineFromListVar->OutlineInfoOnMouse=Item;
		return;
	}
	CmdClearTestOutlinePacket	*CmdClearTestOutlinePacketVar=dynamic_cast<CmdClearTestOutlinePacket *>(packet);
	if(CmdClearTestOutlinePacketVar!=NULL){
		if(PickupBmp!=NULL){
			MatrixBuffClear(PickupBmp ,0,PickupBmpXByte ,PickupBmpYLen);
		}
		return;
	}		
	CmdOutlineInfoListPacket	*CmdOutlineInfoListPacketVar=dynamic_cast<CmdOutlineInfoListPacket *>(packet);
	if(CmdOutlineInfoListPacketVar!=NULL){
		for(AlgorithmItemPLI	*L=GetFirstData();L!=NULL;L=L->GetNext()){
			OutlineInfoList	*a;
			for(a=CmdOutlineInfoListPacketVar->OutlineInfos->GetFirst();a!=NULL;a=a->GetNext()){
				if(a->LibID==L->GetLibID()){
					IntClass	*d=a->OutlineCount.GetItem(GetLayer());
					if(d!=NULL){
						d->SetValue(d->GetValue()+1);
					}
					break;
				}
			}
			if(a==NULL){
				a=new OutlineInfoList();
				a->LibID=L->GetLibID();
				for(int layer=0;layer<GetLayerNumb();layer++){
					if(layer==GetLayer())
						a->OutlineCount.Add(1);
					else
						a->OutlineCount.Add(0);
				}
				CmdOutlineInfoListPacketVar->OutlineInfos->AppendList(a);
			}
		}
		return;
	}
}
void	OutlineInLayer::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	OutlineDrawAttr	*BAttr=dynamic_cast<OutlineDrawAttr *>(Attr);
	if(BAttr!=NULL){
		if(BAttr->Mode==CmdOutlineDrawModePacket::_LibTest){
			if(PickupBmp!=NULL){
				OutlineBase	*BBase=dynamic_cast<OutlineBase *>(GetParentBase());
				DrawBitImage(pnt, (const BYTE **)PickupBmp,PickupBmpXByte*8,PickupBmpXByte,PickupBmpYLen
					,(movx<0)?movx:0 ,(movy<0)?movy:0,ZoomRate
						,0,0
						,BBase->ColorPickup);
			}
		}
		else if(BAttr->Mode==CmdOutlineDrawModePacket::_CreatedBlock){
			AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
		}
	}
	else{
		AlgorithmInLayerPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}

OutlineInPage::OutlineInPage(AlgorithmBase *parent)
:AlgorithmInPagePLI(parent)
{
}



void	OutlineInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetOutlineFromList	*CmdGetOutlineFromListVar=dynamic_cast<CmdGetOutlineFromList *>(packet);
	if(CmdGetOutlineFromListVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdPickupTestOutlinePacket	*BPickLib=dynamic_cast<CmdPickupTestOutlinePacket *>(packet);
	if(BPickLib!=NULL){
		for(IntClass *L=BPickLib->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			int	Layer=L->GetValue();
			OutlineInLayer	*BL=dynamic_cast<OutlineInLayer	*>(GetLayerData(Layer));
			if(BL!=NULL){
				AlgorithmLibrary	*ALib=BPickLib->LibPoint->GetLibrary();

				BL->PickupTest(*(OutlineInspectLibrary *)ALib);
			}
		}
		return;
	}
	CmdClearTestOutlinePacket	*CmdClearTestOutlinePacketVar=dynamic_cast<CmdClearTestOutlinePacket *>(packet);
	if(CmdClearTestOutlinePacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdOutlineInfoListPacket	*CmdOutlineInfoListPacketVar=dynamic_cast<CmdOutlineInfoListPacket *>(packet);
	if(CmdOutlineInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
}
//===============================================================================================
OutlineBase::OutlineBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup		=Qt::yellow;
	BlockNormal		=Qt::darkGreen;
	BlockSelected	=Qt::green;
	BlockActive		=Qt::red;
	OmitZoneDot		=100;

	SetParam(&ColorPickup		, /**/"Color"	,/**/"ColorPickup"	,LangSolver.GetString(XOutlineInspect_LS,LID_1)/*"Color for Image to Pickup-Test "*/);
	SetParam(&BlockNormal		, /**/"Color"	,/**/"BlockNormal"	,LangSolver.GetString(XOutlineInspect_LS,LID_3)/*"Color for Block"*/);
	SetParam(&BlockSelected		, /**/"Color"	,/**/"BlockSelected",LangSolver.GetString(XOutlineInspect_LS,LID_5)/*"Color for Selected Block"*/);
	SetParam(&BlockActive		, /**/"Color"	,/**/"BlockActive"	,LangSolver.GetString(XOutlineInspect_LS,LID_7)/*"Color for Active Block"*/);
	SetParam(&OmitZoneDot		, /**/"Setting" ,/**/"OmitZoneDot"	,LangSolver.GetString(XOutlineInspect_LS,LID_9)/*"Omitting zone "*/);
}

AlgorithmDrawAttr	*OutlineBase::CreateDrawAttr(void)
{
	return new OutlineDrawAttr();
}

void	OutlineBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetOutlineLibraryListPacket	*AListPacket=dynamic_cast<CmdGetOutlineLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetOutlineLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetOutlineLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertOutlineLibraryPacket	*BInsLib=dynamic_cast<CmdInsertOutlineLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(OutlineInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateOutlineLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateOutlineLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(OutlineInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadOutlineLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadOutlineLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempOutlineLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempOutlineLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new OutlineInspectLibrary(GetLibType(),GetLayersBase());
		return;
	}
	CmdClearOutlineLibraryPacket	*CmdClearOutlineLibraryPacketVar=dynamic_cast<CmdClearOutlineLibraryPacket *>(packet);
	if(CmdClearOutlineLibraryPacketVar!=NULL){
		CmdClearOutlineLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteOutlineLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteOutlineLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdGenerateOutlinePacket	*BGenerated=dynamic_cast<CmdGenerateOutlinePacket *>(packet);
	if(BGenerated!=NULL){
		OutlineInspectLibrary	**LibDim=new OutlineInspectLibrary*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new OutlineInspectLibrary(GetLibType(),GetLayersBase());
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				if(LibDim[i]->Priority>LibDim[i+1]->Priority){
					OutlineInspectLibrary	Tmp(GetLibType(),GetLayersBase());
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}
		int	Page=BGenerated->Page;
		AlgorithmInPageRoot		*p=GetPageData(Page);
		if(p!=NULL){
			OutlineInPage	*Bp=dynamic_cast<OutlineInPage *>(p);
			if(Bp!=NULL){
				IntList LayerList;
				Bp->SelectAll(LayerList);
				Bp->DeleteSelectedItems(LayerList);
				for(int i=0;i<N;i++){
					for(int Layer=0;Layer<GetLayerNumb(Page);Layer++){
					//for(IntClass *c=BGenerated->LayerList.GetFirst();c!=NULL;c=c->GetNext()){
					//	OutlineInLayer	*BL=(OutlineInLayer	*)(Bp->GetLayerData(c->GetValue()));
						if(LibDim[i]->HasGenLayer(Layer)==true
						|| ((LibDim[i]->GetAdaptedGenLayers().IsEmpty()==true) && LayerList.IsInclude(Layer)==true)){
							OutlineInLayer	*BL=(OutlineInLayer	*)(Bp->GetLayerData(Layer));
							BL->CreateBlocks(LibDim[i]->GetLibID());
						}
					}
				}
			}
		}
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempOutlineItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempOutlineItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new OutlineItem();
		return;
	}
	CmdCreateByteArrayFromOutlineItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromOutlineItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
		return;
	}
	/*
	CmdAddByteOutlineItemPacket	*AddBItem=dynamic_cast<CmdAddByteOutlineItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePLI	*PData=dynamic_cast<AlgorithmInPagePLI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			QBuffer	MBuff(&AddBItem->Buff);
			OutlineItem	*Item=new OutlineItem();
			MBuff.open(QIODevice::ReadWrite);
			Item->Load(&MBuff,GetLayersBase());
			Item->SetArea(AddBItem->Area);
			Item->SetManualCreated(true);
			PData->AppendItem(Item);
		}
		return;
	}
	*/
	CmdLoadOutlineItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadOutlineItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
		return;
	}
	CmdModifySelectedOutlineFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedOutlineFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		OutlineInspectLibrary	LibData(GetLibType(),GetLayersBase());
		if(GetLibraryContainer()!=NULL){
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdClearTestOutlinePacket	*CmdClearTestOutlinePacketVar=dynamic_cast<CmdClearTestOutlinePacket *>(packet);
	if(CmdClearTestOutlinePacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestOutlinePacketVar);
		}
		return;
	}
	CmdOutlineInfoListPacket	*CmdOutlineInfoListPacketVar=dynamic_cast<CmdOutlineInfoListPacket *>(packet);
	if(CmdOutlineInfoListPacketVar!=NULL){
		GetPageData(CmdOutlineInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
	}
	CmdGetOutlineFromList	*CmdGetOutlineFromListVar=dynamic_cast<CmdGetOutlineFromList *>(packet);
	if(CmdGetOutlineFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetOutlineFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateOutlineItem	*CmdCreateOutlineItemVar=dynamic_cast<CmdCreateOutlineItem *>(packet);
	if(CmdCreateOutlineItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
}

bool	OutlineBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==OutlineHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==OutlineHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==OutlineReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==OutlineReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==OutlineReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==OutlineSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*OutlineBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==OutlineHistogramListSendCommand){
		OutlineHistogramListSend	*pSend=new OutlineHistogramListSend();
		if(reqData!=NULL){
			OutlineHistogramListReq	*req=(OutlineHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==OutlineHistogramListReqCommand){
		return new OutlineHistogramListReq();
	}
	else if(Command==OutlineReqThresholdReqCommand){
		return new OutlineThresholdReq();
	}
	else if(Command==OutlineReqThresholdSendCommand){
		OutlineThresholdSend	*pSend=new OutlineThresholdSend();
		if(reqData!=NULL){
			OutlineThresholdReq	*req=(OutlineThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==OutlineReqTryThresholdCommand){
		return new OutlineReqTryThreshold();
	}
	else if(Command==OutlineSendTryThresholdCommand){
		OutlineSendTryThreshold	*pSend=new OutlineSendTryThreshold();
		if(reqData!=NULL){
			OutlineReqTryThreshold	*req=(OutlineReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	OutlineBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==OutlineHistogramListSendCommand){
		OutlineHistogramListSend	*p=(OutlineHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==OutlineHistogramListReqCommand){
		OutlineHistogramListReq	*p=(OutlineHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==OutlineReqThresholdReqCommand){
		OutlineThresholdReq	*p=(OutlineThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==OutlineReqThresholdSendCommand){
		OutlineThresholdSend	*p=(OutlineThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==OutlineReqTryThresholdCommand){
		OutlineReqTryThreshold	*p=(OutlineReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==OutlineSendTryThresholdCommand){
		OutlineSendTryThreshold	*p=(OutlineSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	OutlineBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==OutlineHistogramListSendCommand){
		OutlineHistogramListSend	*p=(OutlineHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==OutlineHistogramListReqCommand){
		OutlineHistogramListReq	*p=(OutlineHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==OutlineReqThresholdReqCommand){
		OutlineThresholdReq	*p=(OutlineThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==OutlineReqThresholdSendCommand){
		OutlineThresholdSend	*p=(OutlineThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==OutlineReqTryThresholdCommand){
		OutlineReqTryThreshold	*p=(OutlineReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==OutlineSendTryThresholdCommand){
		OutlineSendTryThreshold	*p=(OutlineSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	OutlineBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==OutlineHistogramListSendCommand){
		OutlineHistogramListSend	*p=(OutlineHistogramListSend *)data;
		return true;
	}
	else if(Command==OutlineHistogramListReqCommand){
		OutlineHistogramListReq	*p=(OutlineHistogramListReq *)data;
		return true;
	}
	else if(Command==OutlineReqThresholdReqCommand){
		OutlineThresholdReq	*p=(OutlineThresholdReq *)data;
		return true;
	}
	else if(Command==OutlineReqThresholdSendCommand){
		OutlineThresholdSend	*p=(OutlineThresholdSend *)data;
		return true;
	}
	else if(Command==OutlineReqTryThresholdCommand){
		OutlineReqTryThreshold	*p=(OutlineReqTryThreshold *)data;
		return true;
	}
	else if(Command==OutlineSendTryThresholdCommand){
		OutlineSendTryThreshold	*p=(OutlineSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}


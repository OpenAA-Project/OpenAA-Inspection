/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XBlockInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "BlockFormResource.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include "XPropertyBlockPacket.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "ChangeCreateBlockForm.h"
//#include "XMasking.h"
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XDynamicMaskingPICommon.h"
#include "XUndo.h"
#include "XBlockAlgoPacket.h"
#include "swap.h"
#include "XAlignmentCommon.h"
#include "XAlgorithmDLL.h"
#include "XDisplaySimPanel.h"
#include "XPropertyBlockCommon.h"
#include "XBlockManualExecuter.h"
#include <QPen>
#include <QPainter>
#include "XLearningRegist.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


BlockShiftList::~BlockShiftList(void)
{
	CurrentNumb=0;
}

BlockHistogramListReq::BlockHistogramListReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	BlockHistogramListReq::Save(QIODevice *f)
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
bool	BlockHistogramListReq::Load(QIODevice *f)
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


BlockHistogramListSend::BlockHistogramListSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));
	CenterBright		=0;
	CenterTargetBright	=0;
	ShiftByAlignmentX	=0;
	ShiftByAlignmentY	=0;
	ShiftByCommonX		=0;
	ShiftByCommonY		=0;
	ShiftBySelfX		=0;
	ShiftBySelfY		=0;
}
void	BlockHistogramListSend::ConstructList(BlockHistogramListReq *reqPacket ,BlockBase *Base)
{
	memset(ListMaster,0,sizeof(ListMaster));
	memset(ListTarget,0,sizeof(ListTarget));

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
				BlockItem	*Item=dynamic_cast<BlockItem*>(item);
				bool	BuiltList=false;
				if(item->IsOriginParts()==true && Item->GetThresholdR(Ap->GetLayersBase())->ThreshouldBag.PointMove.ModeCenterBrightFromParts==true){
					PieceClass	*Pc=NULL;
					Pc=Base->GetLayersBase()->GetPieceStock()->SearchOnly(item->GetPartsID());
					if(Pc!=NULL){
						QString DLLRoot ,DLLName;
						Base->GetAlgorithmRootName(DLLRoot ,DLLName);
						AlgorithmItemRoot	*PItem=Pc->GetAlgorithmItem(DLLRoot,DLLName,Layer ,item->GetPartsItemID());
						if(PItem->GetDataInLayer()->GetMasterBuff().IsNull()==false)
							PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetMasterBuff(),0 ,0);
						else if(PItem->GetDataInLayer()->GetTargetBuff().IsNull()==false)
							PItem->GetArea().MakeBrightList(ListMaster ,PItem->GetDotPerLine(),PItem->GetMaxLines(),PItem->GetDataInLayer()->GetTargetBuff(),0 ,0);
						BuiltList=true;
					}
				}
				if(BuiltList==false){
					if(Item->GetMasterBuff().IsNull()==false)
						item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetMasterBuff(),0 ,0);
					else if(Item->GetTargetBuff().IsNull()==false)
						item->GetArea().MakeBrightList(ListMaster ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
				}

				Item->GetShiftByAlignemnt(ShiftByAlignmentX,ShiftByAlignmentY);
				ShiftByCommonX	=Item->ShiftX;
				ShiftByCommonY	=Item->ShiftY;
			
				ResultInspection	*DRes=item->GetParentBase()->GetLayersBase()->GetCurrentResultForDraw();
				if(DRes!=NULL){
					ResultBaseForAlgorithmRoot	*rbase=DRes->GetResultBaseForAlgorithm(item->GetParentBase());				
					ResultBasePhase	*Ph=rbase->GetPageDataPhase(item->GetPhaseCode());
					ResultInPagePLI	*Rp=dynamic_cast<ResultInPagePLI *>(Ph->GetPageData(item->GetParentInPage()->GetPage()));
					if(Rp!=NULL){
						ResultInLayerPLI	&rLayer=Rp->GetLayerData(Item->GetParent()->GetLayer());
						ResultInItemPLI		*rItem=rLayer.FindResultInItem(Item->GetID());
						if(rItem!=NULL){
							int	sx,sy;
							rItem->GetTotalShifted(sx,sy);
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),sx ,sy);
							ShiftBySelfX	=rItem->GetItemSearchedX();
							ShiftBySelfY	=rItem->GetItemSearchedY();
						}
						else{
							item->GetArea().MakeBrightList(ListTarget ,item->GetDotPerLine(),item->GetMaxLines(),Item->GetTargetBuff(),0 ,0);
						}
					}
				}
				CenterBright		=Item->CenterBright;
				CenterTargetBright	=Item->CenterTargetBright;
			}
		}
	}
}

bool	BlockHistogramListSend::Save(QIODevice *f)
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
	if(f->write((const char *)ListMaster,sizeof(ListMaster))!=sizeof(ListMaster))
		return false;
	if(f->write((const char *)ListTarget,sizeof(ListTarget))!=sizeof(ListTarget))
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;

	if(::Save(f,ShiftByAlignmentX)==false)
		return false;
	if(::Save(f,ShiftByAlignmentY)==false)
		return false;
	if(::Save(f,ShiftByCommonX)==false)
		return false;
	if(::Save(f,ShiftByCommonY)==false)
		return false;
	if(::Save(f,ShiftBySelfX)==false)
		return false;
	if(::Save(f,ShiftBySelfY)==false)
		return false;
	return true;
}
bool	BlockHistogramListSend::Load(QIODevice *f)
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
	if(f->read((char *)ListMaster,sizeof(ListMaster))!=sizeof(ListMaster))
		return false;
	if(f->read((char *)ListTarget,sizeof(ListTarget))!=sizeof(ListTarget))
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;
	if(::Load(f,ShiftByAlignmentX)==false)
		return false;
	if(::Load(f,ShiftByAlignmentY)==false)
		return false;
	if(::Load(f,ShiftByCommonX)==false)
		return false;
	if(::Load(f,ShiftByCommonY)==false)
		return false;
	if(::Load(f,ShiftBySelfX)==false)
		return false;
	if(::Load(f,ShiftBySelfY)==false)
		return false;
	return true;
}
BlockThresholdReq::BlockThresholdReq(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	BlockThresholdReq::Save(QIODevice *f)
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
bool	BlockThresholdReq::Load(QIODevice *f)
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

BlockThresholdSend::BlockThresholdSend(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;

	CenterBright		=0;
	CenterTargetBright	=0;
	NBrightWidthL		=0;
	NBrightWidthH		=0;
	BBrightWidthL		=0;
	BBrightWidthH		=0;

	AbsNBrightWidthL	=0;
	AbsNBrightWidthH	=0;
	AbsBBrightWidthL	=0;
	AbsBBrightWidthH	=0;

	NMinNGCountL		=0;
	NMinNGCountH		=0;
	BMinNGCountL		=0;
	BMinNGCountH		=0;
	NConnectLen			=0;
	BConnectLen			=0;
}

void	BlockThresholdSend::ConstructList(BlockThresholdReq *reqPacket,BlockBase *Base)
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
		AlgorithmInLayerRoot	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(BlockItemID);
			if(item!=NULL){
				int	dx=0;
				int	dy=0;
				if(item->GetCurrentResult()!=NULL){
					dx=item->GetCurrentResult()->GetTotalShiftedX();
					dy=item->GetCurrentResult()->GetTotalShiftedY();
				}
				BlockItem	*BItem=(BlockItem *)item;
				const	BlockThreshold	*RThr=BItem->GetThresholdR(Ap->GetLayersBase());
				if(BItem->CenterBright==0){
					BItem->MakeInsideEdgeArea();
					if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && BItem->GetMasterBuff().IsNull()==false){
						BItem->CenterBright=BItem->CalcCenterBright(BItem->GetMasterBuff(),0,0);
					}
					else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && BItem->GetTargetBuff().IsNull()==false){
						BItem->CenterBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),0,0);
					}
					else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false){
						BItem->CenterBright=0;
					}
					else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
						BItem->CenterBright=RThr->ThreshouldBag.RegularCenterBright;
					}
					BItem->CenterTargetBright=BItem->CenterBright;
				}
				CenterBright	=BItem->CenterBright;
				NBrightWidthL	=RThr->ThreshouldBag.NBrightWidthL;
				NBrightWidthH	=RThr->ThreshouldBag.NBrightWidthH;
				BBrightWidthL	=RThr->ThreshouldBag.BBrightWidthL;
				BBrightWidthH	=RThr->ThreshouldBag.BBrightWidthH;

				NMinNGCountL	=RThr->ThreshouldBag.NMinNGCountL;
				NMinNGCountH	=RThr->ThreshouldBag.NMinNGCountH;
				BMinNGCountL	=RThr->ThreshouldBag.BMinNGCountL;
				BMinNGCountH	=RThr->ThreshouldBag.BMinNGCountH;
				NConnectLen		=RThr->ThreshouldBag.NConnectLen;
				BConnectLen		=RThr->ThreshouldBag.BConnectLen;

				int	TmpNBrightWidthL=NBrightWidthL;
				int	TmpNBrightWidthH=NBrightWidthH;
				int	TmpBBrightWidthL=BBrightWidthL;
				int	TmpBBrightWidthH=BBrightWidthH;
				if(RThr->ThreshouldBag.PointMove.ModeAbsoluteBright==true){
					AbsNBrightWidthL=TmpNBrightWidthL;
					AbsNBrightWidthH=TmpNBrightWidthH;
					AbsBBrightWidthL=TmpBBrightWidthL;
					AbsBBrightWidthH=TmpBBrightWidthH;
				}
				else{
					AbsNBrightWidthL=CenterBright-TmpNBrightWidthL;
					AbsNBrightWidthH=CenterBright+TmpNBrightWidthH;
					AbsBBrightWidthL=CenterBright-TmpBBrightWidthL;
					AbsBBrightWidthH=CenterBright+TmpBBrightWidthH;
				}
				if(RThr->ThreshouldBag.PointMove.ModeAdjustable==true){
					int	iAbsBBrightWidthL=AbsBBrightWidthL;
					int	iAbsBBrightWidthH=AbsBBrightWidthH;
					BItem->EnAverage(dx,dy
								,iAbsBBrightWidthL,iAbsBBrightWidthH);
					AbsBBrightWidthL	=iAbsBBrightWidthL;
					AbsBBrightWidthH	=iAbsBBrightWidthH;

					int	iAbsNBrightWidthL=AbsNBrightWidthL;
					int	iAbsNBrightWidthH=AbsNBrightWidthH;
					BItem->EnAverage(dx,dy
								,iAbsNBrightWidthL,iAbsNBrightWidthH);
					AbsNBrightWidthL	=iAbsNBrightWidthL;
					AbsNBrightWidthH	=iAbsNBrightWidthH;
				}
				CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);
			}
		}
	}
}

bool	BlockThresholdSend::Save(QIODevice *f)
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
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;
	if(::Save(f,NBrightWidthL)==false)
		return false;
	if(::Save(f,NBrightWidthH)==false)
		return false;
	if(::Save(f,BBrightWidthL)==false)
		return false;
	if(::Save(f,BBrightWidthH)==false)
		return false;

	if(::Save(f,AbsNBrightWidthL)==false)
		return false;
	if(::Save(f,AbsNBrightWidthH)==false)
		return false;
	if(::Save(f,AbsBBrightWidthL)==false)
		return false;
	if(::Save(f,AbsBBrightWidthH)==false)
		return false;

	if(::Save(f,NMinNGCountL)==false)
		return false;
	if(::Save(f,NMinNGCountH)==false)
		return false;
	if(::Save(f,BMinNGCountL)==false)
		return false;
	if(::Save(f,BMinNGCountH)==false)
		return false;
	if(::Save(f,NConnectLen)==false)
		return false;
	if(::Save(f,BConnectLen)==false)
		return false;
	return true;
}
bool	BlockThresholdSend::Load(QIODevice *f)
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
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;
	if(::Load(f,NBrightWidthL)==false)
		return false;
	if(::Load(f,NBrightWidthH)==false)
		return false;
	if(::Load(f,BBrightWidthL)==false)
		return false;
	if(::Load(f,BBrightWidthH)==false)
		return false;

	if(::Load(f,AbsNBrightWidthL)==false)
		return false;
	if(::Load(f,AbsNBrightWidthH)==false)
		return false;
	if(::Load(f,AbsBBrightWidthL)==false)
		return false;
	if(::Load(f,AbsBBrightWidthH)==false)
		return false;

	if(::Load(f,NMinNGCountL)==false)
		return false;
	if(::Load(f,NMinNGCountH)==false)
		return false;
	if(::Load(f,BMinNGCountL)==false)
		return false;
	if(::Load(f,BMinNGCountH)==false)
		return false;
	if(::Load(f,NConnectLen)==false)
		return false;
	if(::Load(f,BConnectLen)==false)
		return false;
	return true;
}

BlockReqTryThreshold::BlockReqTryThreshold(void)
{
	GlobalPage=-1;
	Layer=-1;
	BlockItemID=-1;
}
bool	BlockReqTryThreshold::Save(QIODevice *f)
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
bool	BlockReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
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

BlockSendTryThreshold::BlockSendTryThreshold(void)
{
	NGDotInNDark	=0;
	NGDotInNBright	=0;
	NGDotInBDark	=0;
	NGDotInBBright	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error			=0;
	Result	=new ResultInItemPLI();
}
BlockSendTryThreshold::~BlockSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}


bool	BlockSendTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,NGDotInNDark	)==false)
		return false;
	if(::Save(f,NGDotInNBright	)==false)
		return false;
	if(::Save(f,NGDotInBDark	)==false)
		return false;
	if(::Save(f,NGDotInBBright	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,ShiftByCommonX)==false)
		return false;
	if(::Save(f,ShiftByCommonY)==false)
		return false;
	if(::Save(f,ShiftBySelfX)==false)
		return false;
	if(::Save(f,ShiftBySelfY)==false)
		return false;
	return true;
}
bool	BlockSendTryThreshold::Load(QIODevice *f)
{
	if(::Load(f,NGDotInNDark	)==false)
		return false;
	if(::Load(f,NGDotInNBright	)==false)
		return false;
	if(::Load(f,NGDotInBDark	)==false)
		return false;
	if(::Load(f,NGDotInBBright	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,ShiftByCommonX)==false)
		return false;
	if(::Load(f,ShiftByCommonY)==false)
		return false;
	if(::Load(f,ShiftBySelfX)==false)
		return false;
	if(::Load(f,ShiftBySelfY)==false)
		return false;
	return true;
}

void	BlockSendTryThreshold::ConstructList(BlockReqTryThreshold *reqPacket,BlockBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	BlockInPage		*BP=(BlockInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		BlockInLayer	*BL=(BlockInLayer *)BP->GetLayerData(reqPacket->Layer);
		if(BL!=NULL){
			BlockItem		*BI=(BlockItem *)BL->SearchIDItem(reqPacket->BlockItemID);
			if(BI!=NULL){
				Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
				reqPacket->Threshold.CenterBright						=BI->CenterBright;
				reqPacket->Threshold.CenterTargetBright					=BI->CenterTargetBright;
				reqPacket->Threshold.GetThresholdW()->ThreshouldBag.OmitVectorIndex	=BI->GetThresholdR(BP->GetLayersBase())->ThreshouldBag.OmitVectorIndex;
				reqPacket->Threshold.AVector							=BI->AVector;
				if(BI->FollowLineData==NULL){
					if(reqPacket->Threshold.FollowLineData!=NULL)
						delete	reqPacket->Threshold.FollowLineData;
					reqPacket->Threshold.FollowLineData=NULL;
				}
				else{
					if(reqPacket->Threshold.FollowLineData==NULL)
						reqPacket->Threshold.FollowLineData=new BlockItem::FollowLines(reqPacket->Threshold);
					*reqPacket->Threshold.FollowLineData=*BI->FollowLineData;
				}

				reqPacket->Threshold.ShiftX								=BI->ShiftX;
				reqPacket->Threshold.ShiftY								=BI->ShiftY;
				//reqPacket->Threshold.GetThresholdW()->ThreshouldBag.PointMove.ModeCalcBothBN=true;
				reqPacket->Threshold.SetParent(BI->GetParent());
				reqPacket->Threshold.CopyArea(*BI);
				AlgorithmItemPointerListContainerContainer	*CC=BL->FindGroup(reqPacket->BlockItemID);
				if(CC!=NULL){
					ImageBuffer &DBuff=BI->GetTargetBuff();
					int	CommonMoveDot=reqPacket->Threshold.GetThresholdR()->ThreshouldBag.CommonMoveDot;
					int	MaxDx=0;
					int	MaxDy=0;
					CC->Match(DBuff,CommonMoveDot,MaxDx,MaxDy,reqPacket->Threshold.GetThresholdW()->ThreshouldBag.PointMove.ModeUseGlobalLine);
					reqPacket->Threshold.ShiftX=MaxDx;
					reqPacket->Threshold.ShiftY=MaxDy;
				}
				
				bool	Masked=BI->RewindDynamicMask(BL);
				ExecutablePointerList	*E=BL->ExecutableContainer.FindItem(BI);
				if(E!=NULL){
					E->MakeDynamicMask();
				}
				reqPacket->Threshold.ExecuteProcessing(0,0,Result);
				if(Masked==true){
					BI->SetDynamicMask(BL);
				}

				ShiftByCommonX	=reqPacket->Threshold.ShiftX;
				ShiftByCommonY	=reqPacket->Threshold.ShiftY;
				ShiftBySelfX	=Result->GetItemSearchedX();
				ShiftBySelfY	=Result->GetItemSearchedY();
			}
		}
	}
	Result->SetAddedData(NULL,0);

	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();
}

/*
void	BlockResultPosList::DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
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
	if(0<=x2 && x1<IData.width() && 0<=y2 && y1<IData.height()){
		LibraryListWithNGType	*AType=NULL;
		if(parent!=NULL){
			AlgorithmItemRoot	*AItem=parent->GetAlgorithmItem();
			if(AItem!=NULL && AItem->AlgorithmItemRoot::GetCurrentResult()!=NULL){
				AlgorithmBase	*ABase=AItem->GetParentBase();
				if(ABase!=NULL){
					AType=ABase->GetNGTypeList(AItem->GetLibID());
				}
			}
		}
		if(AType!=NULL && AType->NGList.GetCount()>0){
			AType->Draw(PData,x1+R,y2+R,parent->GetLayersBase()->GetParamGlobal()->NGMarkRadius*2);
		}
		else{
			QPen	hPen;
			hPen.setColor(QColor(Col));
			hPen.setWidth(parent->GetLayersBase()->GetParamGlobal()->ResultNGCircleWidth);
			PData.setBrush(Qt::NoBrush);
			PData.setPen(hPen);
			if(ImportanceLevel<100){
				PData.drawEllipse(x1-4,y1-4,R2+4,R2+4);
				PData.drawEllipse(x1-2,y1-2,R2+2,R2+2);
				PData.drawEllipse(x1,y1,R2,R2);
			}
			else{
				PData.drawEllipse(x1,y1,R2,R2);
			}
		}
	}
}
*/

void	BlockResultPosList::DrawResultDetail(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
										,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)
{
	int	Level=parent->GetLayersBase()->GetParamGlobal()->DrawResultDetailLevel;
	if(Level<5){
		ResultPosList::DrawResultDetail(parent ,IData ,PData ,MovX ,MovY ,ZoomRate
										,MinimumRadius,Col,CircleWidth,DrawBlueNGMark);
	}
	else{
		DrawResult(parent ,IData ,PData ,MovX ,MovY ,ZoomRate,MinimumRadius,Col,CircleWidth,DrawBlueNGMark);
		if(NGShape.IsNull()==false){
			NGShape.DrawAlpha(parent->GetAlignedX()+Rx
							, parent->GetAlignedY()+Ry
							,&IData ,Col
							,ZoomRate ,MovX ,MovY);
		}
		if(Vector.IsNull()==false){
			QRgb	LCol;
			LCol=qRgb(qRed(Col),qGreen(Col),qBlue(Col));
			Vector.Draw(IData,PData,LCol,MovX ,MovY,ZoomRate);
		}
		if(Message.isEmpty()==false){
			int	x=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
			int y=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
			QRgb	CCol;
			CCol=qRgb(qRed(Col),qGreen(255),qBlue(Col));
			PData.setPen(CCol);
			PData.drawText(x+10,y+10,Message);
		}
		else{
			int	x=(Px+Rx+parent->GetAlignedX()+MovX)*ZoomRate;
			int y=(Py+Ry+parent->GetAlignedY()+MovY)*ZoomRate;
			QRgb	CCol;
			CCol=qRgb(qRed(Col),qGreen(255),qBlue(Col));
			PData.setPen(CCol);
			int	Dots=NGShape.GetPatternByte();
			int	WLen=NGShape.GetWidth();
			int	HLen=NGShape.GetHeight();
			ParamGlobal	*G=parent->GetLayersBase()->GetParamGlobal();
			int	page=parent->GetPage();
			int		SmallNumberFigure	=parent->GetLayersBase()->GetParamGlobal()->SmallNumberFigure;
			PData.drawText(x+10,y+10,QString(/**/"Pixels:")+QString::number(Dots)
									+QString(/**/" (")+QString::number(G->TransformPixelToUnitSquare(page,Dots),'f',SmallNumberFigure)
									+QString(/**/"mm2)"));
			PData.drawText(x+10,y+26,QString(/**/"W,H:")+QString::number(WLen)+QString(/**/",")+QString::number(HLen)
									+QString(/**/" (")
									+QString::number(G->TransformPixelToUnit(page,WLen),'f',SmallNumberFigure)
									+QString(/**/"mm,")
									+QString::number(G->TransformPixelToUnit(page,HLen),'f',SmallNumberFigure)
									+QString(/**/"mm)"));
		}				
	}
}


//=====================================================================================
void	BlockChangeShift::Reflect(BlockBase *Base)
{
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePLI	*Ap=dynamic_cast<AlgorithmInPagePLI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmInLayerPLI	*L	=Ap->GetLayerDataPLI(Layer);
		if(L!=NULL){
			AlgorithmItemRoot	*item	=L->SearchIDItem(BlockItemID);
			if(item!=NULL){
				if(item->GetCurrentResult()!=NULL){
					item->GetCurrentResult()->SetItemSearchedXY(Dx,Dy);
				}
			}
		}
	}
}

bool	BlockChangeShift::Save(QIODevice *f)
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
bool	BlockChangeShift::Load(QIODevice *f)
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
//=====================================================================================
BlockThreshold::BlockThreshold(BlockItem *parent)
:AlgorithmThreshold(parent)
{
	ThreshouldBag.NBrightWidthL		=0;
	ThreshouldBag.NBrightWidthH		=0;
	ThreshouldBag.NOKDotL			=0;
	ThreshouldBag.NOKDotH			=0;
	ThreshouldBag.NMaxNGDotL		=99999999;
	ThreshouldBag.NMaxNGDotH		=99999999;
	ThreshouldBag.NOKLengthL		=0;
	ThreshouldBag.NOKLengthH		=0;
	ThreshouldBag.BBrightWidthL		=0;
	ThreshouldBag.BBrightWidthH		=0;
	ThreshouldBag.BOKDotL			=0;
	ThreshouldBag.BOKDotH			=0;
	ThreshouldBag.BMaxNGDotL		=99999999;
	ThreshouldBag.BMaxNGDotH		=99999999;
	ThreshouldBag.BOKLengthL		=0;
	ThreshouldBag.BOKLengthH		=0;
	ThreshouldBag.DiffBrightWidthL	=255;
	ThreshouldBag.DiffBrightWidthH	=255;
	ThreshouldBag.ExpandForGenMask	=0;
	ThreshouldBag.RegularCenterBright	=0;

	ThreshouldBag.PointMove.ModeEnabled					=true;
	ThreshouldBag.PointMove.ModeAbsoluteBright			=true;
	ThreshouldBag.PointMove.ModeCommonMovable			=false;
	ThreshouldBag.PointMove.ModeNGCluster				=true;
	ThreshouldBag.PointMove.ModeDiffer					=false;
	ThreshouldBag.PointMove.ModeCenterBrightFromParts	=false;
	ThreshouldBag.PointMove.ModeOnlyMatching			=false;
	ThreshouldBag.PointMove.ModeWhiteMask				=false;
	ThreshouldBag.PointMove.ModeBlackMask				=false;
	ThreshouldBag.PointMove.ModeAdjustable				=false;
	ThreshouldBag.PointMove.ModeCalcBothBN				=false;
	ThreshouldBag.PointMove.ModeInvertLogic				=false;
	ThreshouldBag.PointMove.ModeMatchPosition			=false;
	ThreshouldBag.PointMove.ModeSearchDetail			=false;
	ThreshouldBag.PointMove.ModeDynamicMask				=false;
	ThreshouldBag.PointMove.ModeBindBWBroad				=false;
	ThreshouldBag.PointMove.ModeBindBWNarrow			=false;
	ThreshouldBag.PointMove.ModeAdoptBiggest			=false;
	ThreshouldBag.PointMove.ModeUseMasterImage			=false;
	ThreshouldBag.PointMove.ModeUseRegularBrightness	=false;
	ThreshouldBag.PointMove.ModePermitInverted			=true;
	ThreshouldBag.PointMove.ModeMatchPositionBW			=false;
	ThreshouldBag.PointMove.ModeOppositeRange			=false;
	ThreshouldBag.PointMove.ModeUseGlobalLine			=true;
	//ThreshouldBag.GeneratedOrigin	=BlockThreshold::_ThreshouldBag3::_FromUnknown;

	ThreshouldBag.CommonMoveID	=-1;
	ThreshouldBag.CommonMoveDot	=0;

	ThreshouldBag.NMinNGCountL	=0;
	ThreshouldBag.NMinNGCountH	=0;
	ThreshouldBag.BMinNGCountL	=0;
	ThreshouldBag.BMinNGCountH	=0;
	ThreshouldBag.NConnectLen		=0;
	ThreshouldBag.BConnectLen		=0;

	ThreshouldBag.SpaceToOutline	=0;
    ThreshouldBag.AdjustBlack		=20;    //?P?x?a?3?I?o?A??
    ThreshouldBag.AdjustWhite		=20;    //?P?x?a?3?I?a?A??
    ThreshouldBag.SelfSearch		=4;     //?c?E?T?o?h?b?g??
	ThreshouldBag.OmitVectorIndex=0xFFFF;//?T?o?O?~?u?u	0xFFFF?I?A?≪?A?O?~?E?μ
	
	CalculatedInfo.ModeSmallCalc	=false;
	//Set("NBrightWidthL"	,&NBrightWidthL,1,255,4);
	//Set("NBrightWidthH"	,&NBrightWidthH,1,255,4);
	//Set("BBrightWidthL"	,&BBrightWidthL,1,255,4);
	//Set("BBrightWidthH"	,&BBrightWidthH,1,255,4);
	//Set("NOKDotL"		,&NOKDotL	,1,1000,10);
	//Set("NOKDotH"		,&NOKDotH	,1,1000,10);
	//Set("BOKDotL"		,&BOKDotL	,1,1000,10);
	//Set("BOKDotH"		,&BOKDotH	,1,1000,10);
	//Set("NOKLengthL"	,&NOKLengthL,1,1000,5);
	//Set("NOKLengthH"	,&NOKLengthH,1,1000,5);
	//Set("BOKLengthL"	,&BOKLengthL,1,1000,5);
	//Set("BOKLengthH"	,&BOKLengthH,1,1000,5);
}

void	BlockThreshold::RegistHist(void)
{
	static	bool	InitialStr	=false;

	static	QString	StrCenterBrightDiference	;
	static	QString	StrBroadLightNGSize			;
	static	QString	StrBroadDarkNGSize			;
	static	QString	StrNarrowLightNGSize		;
	static	QString	StrNarrowDarkNGSize			;
	static	QString	StrXShift					;
	static	QString	StrYShift					;
	static	QString	StrBBrightnessLow			;
	static	QString	StrBBrightnessHigh			;
	static	QString	StrNBrightnessLow			;
	static	QString	StrNBrightnessHigh			;

	if(InitialStr==false){
		StrCenterBrightDiference=LangSolver.GetString(XBlockInspection_LS,LID_107)/*"Center Bright difference"*/;
		StrBroadLightNGSize		=LangSolver.GetString(XBlockInspection_LS,LID_108)/*"Broad Light NG size"*/;
		StrBroadDarkNGSize		=LangSolver.GetString(XBlockInspection_LS,LID_109)/*"Broad Dark NG size"*/;
		StrNarrowLightNGSize	=LangSolver.GetString(XBlockInspection_LS,LID_110)/*"Narrow Light NG size"*/;
		StrNarrowDarkNGSize		=LangSolver.GetString(XBlockInspection_LS,LID_111)/*"Narrow Dark NG size"*/;
		StrXShift				=LangSolver.GetString(XBlockInspection_LS,LID_112)/*"X-Shift"*/;
		StrYShift				=LangSolver.GetString(XBlockInspection_LS,LID_113)/*"Y-Shift"*/;
		StrBBrightnessLow		="Broad Brightness width Low";
		StrBBrightnessHigh		="Broad Brightness width High";
		StrNBrightnessLow		="Narrow Brightness width Low";
		StrNBrightnessHigh		="Narrow Brightness width High";

		Set(/**/"NBrightWidthL"	,&ThreshouldBag.NBrightWidthL	,0,255,1);
		Set(/**/"NBrightWidthH"	,&ThreshouldBag.NBrightWidthH	,0,255,1);
		Set(/**/"NOKDotL"		,&ThreshouldBag.NOKDotL			,0,3000,5);
		Set(/**/"NOKDotH"		,&ThreshouldBag.NOKDotH			,0,3000,5);
		Set(/**/"BBrightWidthL"	,&ThreshouldBag.NBrightWidthL	,0,255,1);
		Set(/**/"BBrightWidthH"	,&ThreshouldBag.NBrightWidthH	,0,255,1);
		Set(/**/"BOKDotL"		,&ThreshouldBag.BOKDotL			,0,3000,5);
		Set(/**/"BOKDotH"		,&ThreshouldBag.BOKDotH			,0,3000,5);

		InitialStr=true;
	}

	RegistBoundaryChar	(StrCenterBrightDiference	,Hist_BlockInspection_CenterBright,-120,120);
	RegistInt			(StrBroadLightNGSize		,Hist_BlockInspection_BLightNGSize		);
	RegistInt			(StrBroadDarkNGSize			,Hist_BlockInspection_BDarkNGSize		);
	RegistInt			(StrNarrowLightNGSize		,Hist_BlockInspection_NLightNGSize		);
	RegistInt			(StrNarrowDarkNGSize		,Hist_BlockInspection_NDarkNGSize		);
	RegistBoundaryByte	(StrXShift					,Hist_BlockInspection_X_Shift	,0,32);
	RegistBoundaryByte	(StrYShift					,Hist_BlockInspection_Y_Shift	,0,32);
	RegistInt			(StrBBrightnessLow			,Hist_BlockInspection_BBrightnessLow	);
	RegistInt			(StrBBrightnessHigh			,Hist_BlockInspection_BBrightnessHigh	);
	RegistInt			(StrNBrightnessLow			,Hist_BlockInspection_NBrightnessLow	);
	RegistInt			(StrNBrightnessHigh			,Hist_BlockInspection_NBrightnessHigh	);
}

void	BlockThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	ThreshouldBag	=((BlockThreshold *)&src)->ThreshouldBag;
	CalculatedInfo.ModeSmallCalc	=((BlockThreshold *)&src)->CalculatedInfo.ModeSmallCalc;
}
void	BlockThreshold::CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)
{
	const	BlockThreshold	*s=dynamic_cast<const BlockThreshold *>(&src);

	if(EdittedMemberID.IsInclude(ID_NBrightWidthL)==true)
		ThreshouldBag.NBrightWidthL		=s->ThreshouldBag.NBrightWidthL	;	//狭域の暗側輝度幅
	if(EdittedMemberID.IsInclude(ID_NBrightWidthH)==true)
		ThreshouldBag.NBrightWidthH		=s->ThreshouldBag.NBrightWidthH	;	//狭域の明側輝度幅
	if(EdittedMemberID.IsInclude(ID_NOKDotL)==true)
		ThreshouldBag.NOKDotL			=s->ThreshouldBag.NOKDotL			;		//狭域の暗側ＯＫドット数
	if(EdittedMemberID.IsInclude(ID_NOKDotH)==true)
		ThreshouldBag.NOKDotH			=s->ThreshouldBag.NOKDotH			;		//狭域の明側ＯＫドット数
	if(EdittedMemberID.IsInclude(ID_NMaxNGDotL)==true)
		ThreshouldBag.NMaxNGDotL		=s->ThreshouldBag.NMaxNGDotL		;		//狭域の暗側最大ＮＧドット数
	if(EdittedMemberID.IsInclude(ID_NMaxNGDotH)==true)
		ThreshouldBag.NMaxNGDotH		=s->ThreshouldBag.NMaxNGDotH		;		//狭域の明側最大ＮＧドット数
	if(EdittedMemberID.IsInclude(ID_NOKLengthL)==true)
		ThreshouldBag.NOKLengthL		=s->ThreshouldBag.NOKLengthL		;		//狭域の明側で、この長さ以下の時ＯＫ
	if(EdittedMemberID.IsInclude(ID_NOKLengthH)==true)
		ThreshouldBag.NOKLengthH		=s->ThreshouldBag.NOKLengthH		;		//狭域の明側で、この長さ以下の時ＯＫ
	if(EdittedMemberID.IsInclude(ID_BBrightWidthL)==true)
		ThreshouldBag.BBrightWidthL		=s->ThreshouldBag.BBrightWidthL	;	//広域の暗側輝度幅
	if(EdittedMemberID.IsInclude(ID_BBrightWidthH)==true)
		ThreshouldBag.BBrightWidthH		=s->ThreshouldBag.BBrightWidthH	;	//広域の明側輝度幅
	if(EdittedMemberID.IsInclude(ID_BOKDotL)==true)
		ThreshouldBag.BOKDotL			=s->ThreshouldBag.BOKDotL			;		//広域の暗側ＯＫドット数
	if(EdittedMemberID.IsInclude(ID_BOKDotH)==true)
		ThreshouldBag.BOKDotH			=s->ThreshouldBag.BOKDotH			;		//広域の明側ＯＫドット数
	if(EdittedMemberID.IsInclude(ID_BMaxNGDotL)==true)
		ThreshouldBag.BMaxNGDotL		=s->ThreshouldBag.BMaxNGDotL		;		//広域の暗側最大ＮＧドット数
	if(EdittedMemberID.IsInclude(ID_BMaxNGDotH)==true)
		ThreshouldBag.BMaxNGDotH		=s->ThreshouldBag.BMaxNGDotH		;		//広域の明側最大ＮＧドット数
	if(EdittedMemberID.IsInclude(ID_BOKLengthL)==true)
		ThreshouldBag.BOKLengthL		=s->ThreshouldBag.BOKLengthL		;		//広域の明側で、この長さ以下の時ＯＫ
	if(EdittedMemberID.IsInclude(ID_BOKLengthH)==true)
		ThreshouldBag.BOKLengthH		=s->ThreshouldBag.BOKLengthH		;		//広域の明側で、この長さ以下の時ＯＫ
	if(EdittedMemberID.IsInclude(ID_DiffBrightWidthL)==true)
		ThreshouldBag.DiffBrightWidthL	=s->ThreshouldBag.DiffBrightWidthL;
	if(EdittedMemberID.IsInclude(ID_DiffBrightWidthH)==true)
		ThreshouldBag.DiffBrightWidthH	=s->ThreshouldBag.DiffBrightWidthH;
	if(EdittedMemberID.IsInclude(ID_RegularCenterBright)==true)
		ThreshouldBag.RegularCenterBright=s->ThreshouldBag.RegularCenterBright;

	if(EdittedMemberID.IsInclude(ID_NMinNGCountL)==true)
		ThreshouldBag.NMinNGCountL		=s->ThreshouldBag.NMinNGCountL	;	//狭域の暗側でこの個数以上のＮＧ個数があればＮＧにする
	if(EdittedMemberID.IsInclude(ID_NMinNGCountH)==true)
		ThreshouldBag.NMinNGCountH		=s->ThreshouldBag.NMinNGCountH	;	//狭域の暗側でこの個数以上のＮＧ個数があればＮＧにする
	if(EdittedMemberID.IsInclude(ID_BMinNGCountL)==true)
		ThreshouldBag.BMinNGCountL		=s->ThreshouldBag.BMinNGCountL	;	//広域の暗側でこの個数以上のＮＧ個数があればＮＧにする
	if(EdittedMemberID.IsInclude(ID_BMinNGCountH)==true)
		ThreshouldBag.BMinNGCountH		=s->ThreshouldBag.BMinNGCountH	;	//広域の暗側でこの個数以上のＮＧ個数があればＮＧにする
	if(EdittedMemberID.IsInclude(ID_NConnectLen)==true)
		ThreshouldBag.NConnectLen		=s->ThreshouldBag.NConnectLen		;	//狭域のＮＧ接続距離
	if(EdittedMemberID.IsInclude(ID_BConnectLen)==true)
		ThreshouldBag.BConnectLen		=s->ThreshouldBag.BConnectLen		;	//広域のＮＧ接続距離
	if(EdittedMemberID.IsInclude(ID_ExpandForGenMask)==true)
		ThreshouldBag.ExpandForGenMask	=s->ThreshouldBag.ExpandForGenMask;	//Expansion dot for dynamic mask to generate in ExecuteIntialAfterEdit

	if(EdittedMemberID.IsInclude(ID_ModeEnabled)==true)
		ThreshouldBag.PointMove.ModeEnabled					=s->ThreshouldBag.PointMove.ModeEnabled					;
	if(EdittedMemberID.IsInclude(ID_ModeAdjustable)==true)
		ThreshouldBag.PointMove.ModeAdjustable				=s->ThreshouldBag.PointMove.ModeAdjustable				;
	if(EdittedMemberID.IsInclude(ID_ModeAbsoluteBright)==true)
		ThreshouldBag.PointMove.ModeAbsoluteBright			=s->ThreshouldBag.PointMove.ModeAbsoluteBright			;
	if(EdittedMemberID.IsInclude(ID_ModeCommonMovable)==true)
		ThreshouldBag.PointMove.ModeCommonMovable			=s->ThreshouldBag.PointMove.ModeCommonMovable			;
	if(EdittedMemberID.IsInclude(ID_ModeNGCluster)==true)
		ThreshouldBag.PointMove.ModeNGCluster				=s->ThreshouldBag.PointMove.ModeNGCluster				;
	if(EdittedMemberID.IsInclude(ID_ModeDiffer)==true)
		ThreshouldBag.PointMove.ModeDiffer					=s->ThreshouldBag.PointMove.ModeDiffer					;
	if(EdittedMemberID.IsInclude(ID_ModeCenterBrightFromParts)==true)
		ThreshouldBag.PointMove.ModeCenterBrightFromParts	=s->ThreshouldBag.PointMove.ModeCenterBrightFromParts	;
	if(EdittedMemberID.IsInclude(ID_ModeOnlyMatching)==true)
		ThreshouldBag.PointMove.ModeOnlyMatching			=s->ThreshouldBag.PointMove.ModeOnlyMatching			;
	if(EdittedMemberID.IsInclude(ID_ModeWhiteMask)==true)
		ThreshouldBag.PointMove.ModeWhiteMask				=s->ThreshouldBag.PointMove.ModeWhiteMask				;
	if(EdittedMemberID.IsInclude(ID_ModeBlackMask)==true)
		ThreshouldBag.PointMove.ModeBlackMask				=s->ThreshouldBag.PointMove.ModeBlackMask				;
	if(EdittedMemberID.IsInclude(ID_ModeCalcBothBN)==true)
		ThreshouldBag.PointMove.ModeCalcBothBN				=s->ThreshouldBag.PointMove.ModeCalcBothBN				;
	if(EdittedMemberID.IsInclude(ID_ModeInvertLogic)==true)
		ThreshouldBag.PointMove.ModeInvertLogic				=s->ThreshouldBag.PointMove.ModeInvertLogic				;
	if(EdittedMemberID.IsInclude(ID_ModeMatchPosition)==true)
		ThreshouldBag.PointMove.ModeMatchPosition			=s->ThreshouldBag.PointMove.ModeMatchPosition			;
	if(EdittedMemberID.IsInclude(ID_ModeSearchDetail)==true)
		ThreshouldBag.PointMove.ModeSearchDetail			=s->ThreshouldBag.PointMove.ModeSearchDetail			;
	if(EdittedMemberID.IsInclude(ID_ModeDynamicMask)==true)
		ThreshouldBag.PointMove.ModeDynamicMask				=s->ThreshouldBag.PointMove.ModeDynamicMask				;
	if(EdittedMemberID.IsInclude(ID_ModeBindBWBroad)==true)
		ThreshouldBag.PointMove.ModeBindBWBroad				=s->ThreshouldBag.PointMove.ModeBindBWBroad				;
	if(EdittedMemberID.IsInclude(ID_ModeBindBWNarrow)==true)
		ThreshouldBag.PointMove.ModeBindBWNarrow			=s->ThreshouldBag.PointMove.ModeBindBWNarrow			;
	if(EdittedMemberID.IsInclude(ID_ModeAdoptBiggest)==true)
		ThreshouldBag.PointMove.ModeAdoptBiggest			=s->ThreshouldBag.PointMove.ModeAdoptBiggest			;
	if(EdittedMemberID.IsInclude(ID_ModeUseMasterImage)==true)
		ThreshouldBag.PointMove.ModeUseMasterImage			=s->ThreshouldBag.PointMove.ModeUseMasterImage			;
	if(EdittedMemberID.IsInclude(ID_ModeUseRegularBrightness)==true)
		ThreshouldBag.PointMove.ModeUseRegularBrightness	=s->ThreshouldBag.PointMove.ModeUseRegularBrightness	;
	if(EdittedMemberID.IsInclude(ID_ModePermitInverted)==true)
		ThreshouldBag.PointMove.ModePermitInverted			=s->ThreshouldBag.PointMove.ModePermitInverted			;	//For outline-matching
	if(EdittedMemberID.IsInclude(ID_ModeMatchPositionBW)==true)
		ThreshouldBag.PointMove.ModeMatchPositionBW			=s->ThreshouldBag.PointMove.ModeMatchPositionBW			;	//Follow outline
	if(EdittedMemberID.IsInclude(ID_ModeOppositeRange)==true)
		ThreshouldBag.PointMove.ModeOppositeRange			=s->ThreshouldBag.PointMove.ModeOppositeRange			;
	if(EdittedMemberID.IsInclude(ID_ModeUseGlobalLine)==true)
		ThreshouldBag.PointMove.ModeUseGlobalLine			=s->ThreshouldBag.PointMove.ModeUseGlobalLine			;	//Follow outline-matching

 	if(EdittedMemberID.IsInclude(ID_CommonMoveID)==true)
		ThreshouldBag.CommonMoveID		=s->ThreshouldBag.CommonMoveID		;
	if(EdittedMemberID.IsInclude(ID_CommonMoveDot)==true)
		ThreshouldBag.CommonMoveDot		=s->ThreshouldBag.CommonMoveDot		;
	if(EdittedMemberID.IsInclude(ID_SpaceToOutline)==true)
		ThreshouldBag.SpaceToOutline	=s->ThreshouldBag.SpaceToOutline	;	//ModeMatchPosition==trueのときしか使わない
	if(EdittedMemberID.IsInclude(ID_AdjustBlack)==true)
		ThreshouldBag.AdjustBlack		=s->ThreshouldBag.AdjustBlack		;    //輝度補正の下限幅
	if(EdittedMemberID.IsInclude(ID_AdjustWhite)==true)
		ThreshouldBag.AdjustWhite		=s->ThreshouldBag.AdjustWhite		;    //輝度補正の上限幅
	if(EdittedMemberID.IsInclude(ID_SelfSearch)==true)
		ThreshouldBag.SelfSearch		=s->ThreshouldBag.SelfSearch		;     //自己探索ドット数
	if(EdittedMemberID.IsInclude(ID_OmitVectorIndex)==true)
		ThreshouldBag.OmitVectorIndex	=s->ThreshouldBag.OmitVectorIndex	;//探索禁?方向	0xFFFFのとき、禁?なし
	if(EdittedMemberID.IsInclude(ID_FollowLineLayer)==true)
		ThreshouldBag.FollowLineLayer	=s->ThreshouldBag.FollowLineLayer	;//-1:Save layer
}

bool	BlockThreshold::Save(QIODevice *file)
{
	WORD	Ver=BlockInspectionVersion;

	if(::Save(file,Ver)==false)
		return false;

	if(file->write((const char *)&ThreshouldBag,sizeof(ThreshouldBag))!=sizeof(ThreshouldBag))
		return false;

	return true;
}
bool	BlockThreshold::Load(QIODevice *file)
{
	WORD	Ver;

	if(::Load(file,Ver)==false)
		return false;
	if(Ver<=10015){
		if(Ver>=10003){
			if(::Load(file,ThreshouldBag.NBrightWidthL)==false)
				return false;
			if(::Load(file,ThreshouldBag.NBrightWidthH)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKDotH)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKLengthL)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKLengthH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BBrightWidthL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BBrightWidthH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKDotH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKLengthL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKLengthH)==false)
				return false;

			if(Ver>=10014){
				if(::Load(file,ThreshouldBag.DiffBrightWidthL)==false)
					return false;
				if(::Load(file,ThreshouldBag.DiffBrightWidthH)==false)
					return false;
			}

			if(Ver<10013){
				BlockThreshold::_ThreshouldBag3::__PointMoveOld	PointMoveOld;
				if(file->read((char *)&PointMoveOld,sizeof(PointMoveOld))!=sizeof(PointMoveOld))
					return false;
				ThreshouldBag.PointMove.ModeEnabled				=PointMoveOld.ModeEnabled;
				ThreshouldBag.PointMove.ModeAdjustable			=PointMoveOld.ModeAdjustable;
				ThreshouldBag.PointMove.ModeAbsoluteBright		=PointMoveOld.ModeAbsoluteBright;
				ThreshouldBag.PointMove.ModeCommonMovable		=PointMoveOld.ModeCommonMovable;
				ThreshouldBag.PointMove.ModeNGCluster			=PointMoveOld.ModeNGCluster;
				ThreshouldBag.PointMove.ModeDiffer				=PointMoveOld.ModeDiffer;
				ThreshouldBag.PointMove.ModeCenterBrightFromParts=PointMoveOld.ModeCenterBrightFromParts;
				ThreshouldBag.PointMove.ModeOnlyMatching		=PointMoveOld.ModeOnlyMatching;
				ThreshouldBag.PointMove.ModeWhiteMask			=PointMoveOld.ModeWhiteMask;
				ThreshouldBag.PointMove.ModeBlackMask			=PointMoveOld.ModeBlackMask;
				ThreshouldBag.PointMove.ModeCalcBothBN			=PointMoveOld.ModeCalcBothBN;
				ThreshouldBag.PointMove.ModeInvertLogic			=PointMoveOld.ModeInvertLogic;
				ThreshouldBag.PointMove.ModeMatchPosition		=PointMoveOld.ModeMatchPosition;
				ThreshouldBag.PointMove.ModeMatchPositionBW		=false;
				ThreshouldBag.PointMove.ModeSearchDetail		=PointMoveOld.ModeSearchDetail;
				ThreshouldBag.PointMove.ModeDynamicMask			=PointMoveOld.ModeDynamicMask;
				ThreshouldBag.PointMove.ModeOppositeRange		=false;
				ThreshouldBag.PointMove.ModeUseGlobalLine		=true;
			}	
			else{
				if(file->read((char *)&ThreshouldBag.PointMove,sizeof(ThreshouldBag.PointMove))!=sizeof(ThreshouldBag.PointMove))
					return false;
			}
			if(file->read((char *)&ThreshouldBag.GeneratedOriginOld,sizeof(ThreshouldBag.GeneratedOriginOld))!=sizeof(ThreshouldBag.GeneratedOriginOld))
				return false;
			if(::Load(file,ThreshouldBag.CommonMoveID)==false)
				return false;
			if(::Load(file,ThreshouldBag.CommonMoveDot)==false)
				return false;
			if(Ver>=10009){
				if(::Load(file,ThreshouldBag.SpaceToOutline)==false)
					return false;
			}
			if(::Load(file,ThreshouldBag.AdjustBlack)==false)
				return false;
			if(::Load(file,ThreshouldBag.AdjustWhite)==false)
				return false;
			if(::Load(file,ThreshouldBag.SelfSearch)==false)
				return false;
			if(::Load(file,ThreshouldBag.OmitVectorIndex)==false)
				return false;

			if(Ver>=10004){
				if(::Load(file,ThreshouldBag.NMinNGCountL)==false)
					return false;
				if(::Load(file,ThreshouldBag.NMinNGCountH)==false)
					return false;
				if(::Load(file,ThreshouldBag.BMinNGCountL)==false)
					return false;
				if(::Load(file,ThreshouldBag.BMinNGCountH)==false)
					return false;
			}
			if(Ver>=10005){
				if(::Load(file,ThreshouldBag.NConnectLen)==false)
					return false;
				if(::Load(file,ThreshouldBag.BConnectLen)==false)
					return false;
			}
		}
		else{
			ThreshouldBag.NBrightWidthL=Ver;
			//if(::Load(file,NBrightWidthL)==false)
			//	return false;
			if(::Load(file,ThreshouldBag.NBrightWidthH)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.NOKDotH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BBrightWidthL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BBrightWidthH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BOKDotH)==false)
				return false;
			if(file->read((char *)&ThreshouldBag.PointMove,sizeof(ThreshouldBag.PointMove))!=sizeof(ThreshouldBag.PointMove))
				return false;
			if(file->read((char *)&ThreshouldBag.GeneratedOriginOld,sizeof(ThreshouldBag.GeneratedOriginOld))!=sizeof(ThreshouldBag.GeneratedOriginOld))
				return false;
			if(::Load(file,ThreshouldBag.CommonMoveID)==false)
				return false;
			if(::Load(file,ThreshouldBag.CommonMoveDot)==false)
				return false;
			if(::Load(file,ThreshouldBag.AdjustBlack)==false)
				return false;
			if(::Load(file,ThreshouldBag.AdjustWhite)==false)
				return false;
			if(::Load(file,ThreshouldBag.SelfSearch)==false)
				return false;
			if(::Load(file,ThreshouldBag.OmitVectorIndex)==false)
				return false;
		}
		if(Ver<=10008){
			ThreshouldBag.PointMove.ModeInvertLogic	=false;
			ThreshouldBag.PointMove.ModeMatchPosition	=false;
			ThreshouldBag.PointMove.ModeMatchPositionBW	=false;
			ThreshouldBag.PointMove.ModeOppositeRange	=false;
			ThreshouldBag.PointMove.ModeUseGlobalLine	=true;
		}

		if(Ver>=10010){
			if(::Load(file,ThreshouldBag.NMaxNGDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.NMaxNGDotH)==false)
				return false;
			if(::Load(file,ThreshouldBag.BMaxNGDotL)==false)
				return false;
			if(::Load(file,ThreshouldBag.BMaxNGDotH)==false)
				return false;
		}
		if(Ver<10011){
			ThreshouldBag.PointMove.ModeSearchDetail	=false;
		}
		if(Ver<10012){
			ThreshouldBag.PointMove.ModeDynamicMask	=false;
		}
		if(Ver<10013){
			ThreshouldBag.PointMove.ModeBindBWBroad	=false;
			ThreshouldBag.PointMove.ModeBindBWNarrow	=false;
		}
		if(Ver<10015){
			ThreshouldBag.PointMove.ModeAdoptBiggest	=false;
		}
		if(Ver<10017){
			ThreshouldBag.PointMove.ModeUseMasterImage	=false;
		}
		if(Ver<10018){
			ThreshouldBag.PointMove.ModeUseRegularBrightness=false;
		}
		if(Ver<10021){
			ThreshouldBag.PointMove.ModePermitInverted	=true;
		}
	}
	else if(Ver<10018){

		struct	_ThreshouldBag2	ThreshouldBag2;
		if(file->read((char *)&ThreshouldBag2,sizeof(ThreshouldBag2))!=sizeof(ThreshouldBag2))
			return false;

		ThreshouldBag.NBrightWidthL	=ThreshouldBag2.NBrightWidthL;
		ThreshouldBag.NBrightWidthH	=ThreshouldBag2.NBrightWidthH;
		ThreshouldBag.NOKDotL		=ThreshouldBag2.NOKDotL;
		ThreshouldBag.NOKDotH		=ThreshouldBag2.NOKDotH;
		ThreshouldBag.NMaxNGDotL	=ThreshouldBag2.NMaxNGDotL;
		ThreshouldBag.NMaxNGDotH	=ThreshouldBag2.NMaxNGDotH;
		ThreshouldBag.NOKLengthL	=ThreshouldBag2.NOKLengthL;
		ThreshouldBag.NOKLengthH	=ThreshouldBag2.NOKLengthH;
		ThreshouldBag.BBrightWidthL	=ThreshouldBag2.BBrightWidthL;
		ThreshouldBag.BBrightWidthH	=ThreshouldBag2.BBrightWidthH;
		ThreshouldBag.BOKDotL		=ThreshouldBag2.BOKDotL;		
		ThreshouldBag.BOKDotH		=ThreshouldBag2.BOKDotH;		
		ThreshouldBag.BMaxNGDotL	=ThreshouldBag2.BMaxNGDotL;		
		ThreshouldBag.BMaxNGDotH	=ThreshouldBag2.BMaxNGDotH;		
		ThreshouldBag.BOKLengthL	=ThreshouldBag2.BOKLengthL;		
		ThreshouldBag.BOKLengthH	=ThreshouldBag2.BOKLengthH;		
		ThreshouldBag.DiffBrightWidthL	=ThreshouldBag2.DiffBrightWidthL;
		ThreshouldBag.DiffBrightWidthH	=ThreshouldBag2.DiffBrightWidthH;
		ThreshouldBag.RegularCenterBright=0;
		ThreshouldBag.ExpandForGenMask	=0;

		ThreshouldBag.NMinNGCountL	=ThreshouldBag2.NMinNGCountL;
		ThreshouldBag.NMinNGCountH	=ThreshouldBag2.NMinNGCountH;
		ThreshouldBag.BMinNGCountL	=ThreshouldBag2.BMinNGCountL;
		ThreshouldBag.BMinNGCountH	=ThreshouldBag2.BMinNGCountH;
		ThreshouldBag.NConnectLen	=ThreshouldBag2.NConnectLen;
		ThreshouldBag.BConnectLen	=ThreshouldBag2.BConnectLen;

		ThreshouldBag.PointMove.ModeEnabled			=ThreshouldBag2.PointMove.ModeEnabled;
		ThreshouldBag.PointMove.ModeAdjustable		=ThreshouldBag2.PointMove.ModeAdjustable;
		ThreshouldBag.PointMove.ModeAbsoluteBright	=ThreshouldBag2.PointMove.ModeAbsoluteBright;
		ThreshouldBag.PointMove.ModeCommonMovable	=ThreshouldBag2.PointMove.ModeCommonMovable;
		ThreshouldBag.PointMove.ModeNGCluster		=ThreshouldBag2.PointMove.ModeNGCluster;
		ThreshouldBag.PointMove.ModeDiffer			=ThreshouldBag2.PointMove.ModeDiffer;
		ThreshouldBag.PointMove.ModeCenterBrightFromParts	=ThreshouldBag2.PointMove.ModeCenterBrightFromParts;
		ThreshouldBag.PointMove.ModeOnlyMatching	=ThreshouldBag2.PointMove.ModeOnlyMatching;
		ThreshouldBag.PointMove.ModeWhiteMask		=ThreshouldBag2.PointMove.ModeWhiteMask;
		ThreshouldBag.PointMove.ModeBlackMask		=ThreshouldBag2.PointMove.ModeBlackMask;
		ThreshouldBag.PointMove.ModeCalcBothBN		=ThreshouldBag2.PointMove.ModeCalcBothBN;
		ThreshouldBag.PointMove.ModeInvertLogic		=ThreshouldBag2.PointMove.ModeInvertLogic;
		ThreshouldBag.PointMove.ModeMatchPosition	=ThreshouldBag2.PointMove.ModeMatchPosition;
		ThreshouldBag.PointMove.ModeMatchPositionBW	=false;
		ThreshouldBag.PointMove.ModeSearchDetail	=ThreshouldBag2.PointMove.ModeSearchDetail;
		ThreshouldBag.PointMove.ModeDynamicMask		=ThreshouldBag2.PointMove.ModeDynamicMask;
		ThreshouldBag.PointMove.ModeBindBWBroad		=ThreshouldBag2.PointMove.ModeBindBWBroad;
		ThreshouldBag.PointMove.ModeBindBWNarrow	=ThreshouldBag2.PointMove.ModeBindBWNarrow;
		ThreshouldBag.PointMove.ModeAdoptBiggest	=ThreshouldBag2.PointMove.ModeAdoptBiggest;
		ThreshouldBag.PointMove.ModeUseMasterImage	=ThreshouldBag2.PointMove.ModeUseMasterImage;
		ThreshouldBag.PointMove.ModeUseRegularBrightness=false;
		ThreshouldBag.PointMove.ModePermitInverted		=true;
		ThreshouldBag.PointMove.ModeOppositeRange		=false;
		ThreshouldBag.PointMove.ModeUseGlobalLine		=true;

        ThreshouldBag.CommonMoveID		=ThreshouldBag2.CommonMoveID;
        ThreshouldBag.CommonMoveDot		=ThreshouldBag2.CommonMoveDot;

		ThreshouldBag.SpaceToOutline	=ThreshouldBag2.SpaceToOutline;
        ThreshouldBag.AdjustBlack		=ThreshouldBag2.AdjustBlack;    
        ThreshouldBag.AdjustWhite		=ThreshouldBag2.AdjustWhite;    
        ThreshouldBag.SelfSearch		=ThreshouldBag2.SelfSearch;     
		ThreshouldBag.OmitVectorIndex	=ThreshouldBag2.OmitVectorIndex;
	}
	else if(Ver<10026){

		struct	_ThreshouldBag3	ThreshouldBag3;
		if(file->read((char *)&ThreshouldBag3,sizeof(ThreshouldBag3))!=sizeof(ThreshouldBag3))
			return false;

		ThreshouldBag.NBrightWidthL		=ThreshouldBag3.NBrightWidthL;
		ThreshouldBag.NBrightWidthH		=ThreshouldBag3.NBrightWidthH;
		ThreshouldBag.NOKDotL			=ThreshouldBag3.NOKDotL;
		ThreshouldBag.NOKDotH			=ThreshouldBag3.NOKDotH;
		ThreshouldBag.NMaxNGDotL		=ThreshouldBag3.NMaxNGDotL;
		ThreshouldBag.NMaxNGDotH		=ThreshouldBag3.NMaxNGDotH;
		ThreshouldBag.NOKLengthL		=ThreshouldBag3.NOKLengthL;
		ThreshouldBag.NOKLengthH		=ThreshouldBag3.NOKLengthH;
		ThreshouldBag.BBrightWidthL		=ThreshouldBag3.BBrightWidthL;
		ThreshouldBag.BBrightWidthH		=ThreshouldBag3.BBrightWidthH;
		ThreshouldBag.BOKDotL			=ThreshouldBag3.BOKDotL;		
		ThreshouldBag.BOKDotH			=ThreshouldBag3.BOKDotH;		
		ThreshouldBag.BMaxNGDotL		=ThreshouldBag3.BMaxNGDotL;		
		ThreshouldBag.BMaxNGDotH		=ThreshouldBag3.BMaxNGDotH;		
		ThreshouldBag.BOKLengthL		=ThreshouldBag3.BOKLengthL;		
		ThreshouldBag.BOKLengthH		=ThreshouldBag3.BOKLengthH;		
		ThreshouldBag.DiffBrightWidthL	=ThreshouldBag3.DiffBrightWidthL;
		ThreshouldBag.DiffBrightWidthH	=ThreshouldBag3.DiffBrightWidthH;
		ThreshouldBag.RegularCenterBright=ThreshouldBag3.RegularCenterBright;
		ThreshouldBag.ExpandForGenMask	=0;

		ThreshouldBag.NMinNGCountL	=ThreshouldBag3.NMinNGCountL;
		ThreshouldBag.NMinNGCountH	=ThreshouldBag3.NMinNGCountH;
		ThreshouldBag.BMinNGCountL	=ThreshouldBag3.BMinNGCountL;
		ThreshouldBag.BMinNGCountH	=ThreshouldBag3.BMinNGCountH;
		ThreshouldBag.NConnectLen	=ThreshouldBag3.NConnectLen;
		ThreshouldBag.BConnectLen	=ThreshouldBag3.BConnectLen;

		ThreshouldBag.PointMove.ModeEnabled			=ThreshouldBag3.PointMove.ModeEnabled;
		ThreshouldBag.PointMove.ModeAdjustable		=ThreshouldBag3.PointMove.ModeAdjustable;
		ThreshouldBag.PointMove.ModeAbsoluteBright	=ThreshouldBag3.PointMove.ModeAbsoluteBright;
		ThreshouldBag.PointMove.ModeCommonMovable	=ThreshouldBag3.PointMove.ModeCommonMovable;
		ThreshouldBag.PointMove.ModeNGCluster		=ThreshouldBag3.PointMove.ModeNGCluster;
		ThreshouldBag.PointMove.ModeDiffer			=ThreshouldBag3.PointMove.ModeDiffer;
		ThreshouldBag.PointMove.ModeCenterBrightFromParts	=ThreshouldBag3.PointMove.ModeCenterBrightFromParts;
		ThreshouldBag.PointMove.ModeOnlyMatching	=ThreshouldBag3.PointMove.ModeOnlyMatching;
		ThreshouldBag.PointMove.ModeWhiteMask		=ThreshouldBag3.PointMove.ModeWhiteMask;
		ThreshouldBag.PointMove.ModeBlackMask		=ThreshouldBag3.PointMove.ModeBlackMask;
		ThreshouldBag.PointMove.ModeCalcBothBN		=ThreshouldBag3.PointMove.ModeCalcBothBN;
		ThreshouldBag.PointMove.ModeInvertLogic		=ThreshouldBag3.PointMove.ModeInvertLogic;
		ThreshouldBag.PointMove.ModeMatchPosition	=ThreshouldBag3.PointMove.ModeMatchPosition;
		ThreshouldBag.PointMove.ModeMatchPositionBW	=ThreshouldBag3.PointMove.ModeMatchPositionBW;
		ThreshouldBag.PointMove.ModeSearchDetail	=ThreshouldBag3.PointMove.ModeSearchDetail;
		ThreshouldBag.PointMove.ModeDynamicMask		=ThreshouldBag3.PointMove.ModeDynamicMask;
		ThreshouldBag.PointMove.ModeBindBWBroad		=ThreshouldBag3.PointMove.ModeBindBWBroad;
		ThreshouldBag.PointMove.ModeBindBWNarrow	=ThreshouldBag3.PointMove.ModeBindBWNarrow;
		ThreshouldBag.PointMove.ModeAdoptBiggest	=ThreshouldBag3.PointMove.ModeAdoptBiggest;
		ThreshouldBag.PointMove.ModeUseMasterImage	=ThreshouldBag3.PointMove.ModeUseMasterImage;
		ThreshouldBag.PointMove.ModeUseRegularBrightness=ThreshouldBag3.PointMove.ModeUseRegularBrightness;
		ThreshouldBag.PointMove.ModePermitInverted		=ThreshouldBag3.PointMove.ModePermitInverted		;
		ThreshouldBag.PointMove.ModeOppositeRange		=ThreshouldBag3.PointMove.ModeOppositeRange		;
		ThreshouldBag.PointMove.ModeUseGlobalLine		=ThreshouldBag3.PointMove.ModeUseGlobalLine		;

        ThreshouldBag.CommonMoveID		=ThreshouldBag3.CommonMoveID;
        ThreshouldBag.CommonMoveDot		=ThreshouldBag3.CommonMoveDot;

		ThreshouldBag.SpaceToOutline	=ThreshouldBag3.SpaceToOutline;
        ThreshouldBag.AdjustBlack		=ThreshouldBag3.AdjustBlack;    
        ThreshouldBag.AdjustWhite		=ThreshouldBag3.AdjustWhite;    
        ThreshouldBag.SelfSearch		=ThreshouldBag3.SelfSearch;     
		ThreshouldBag.OmitVectorIndex	=ThreshouldBag3.OmitVectorIndex;
	}
	else if(Ver<10029){

		struct	_ThreshouldBag4	ThreshouldBag4;
		if(file->read((char *)&ThreshouldBag4,sizeof(ThreshouldBag4))!=sizeof(ThreshouldBag4))
			return false;

		ThreshouldBag.NBrightWidthL		=ThreshouldBag4.NBrightWidthL;
		ThreshouldBag.NBrightWidthH		=ThreshouldBag4.NBrightWidthH;
		ThreshouldBag.NOKDotL			=ThreshouldBag4.NOKDotL;
		ThreshouldBag.NOKDotH			=ThreshouldBag4.NOKDotH;
		ThreshouldBag.NMaxNGDotL		=ThreshouldBag4.NMaxNGDotL;
		ThreshouldBag.NMaxNGDotH		=ThreshouldBag4.NMaxNGDotH;
		ThreshouldBag.NOKLengthL		=ThreshouldBag4.NOKLengthL;
		ThreshouldBag.NOKLengthH		=ThreshouldBag4.NOKLengthH;
		ThreshouldBag.BBrightWidthL		=ThreshouldBag4.BBrightWidthL;
		ThreshouldBag.BBrightWidthH		=ThreshouldBag4.BBrightWidthH;
		ThreshouldBag.BOKDotL			=ThreshouldBag4.BOKDotL;		
		ThreshouldBag.BOKDotH			=ThreshouldBag4.BOKDotH;		
		ThreshouldBag.BMaxNGDotL		=ThreshouldBag4.BMaxNGDotL;		
		ThreshouldBag.BMaxNGDotH		=ThreshouldBag4.BMaxNGDotH;		
		ThreshouldBag.BOKLengthL		=ThreshouldBag4.BOKLengthL;		
		ThreshouldBag.BOKLengthH		=ThreshouldBag4.BOKLengthH;		
		ThreshouldBag.DiffBrightWidthL	=ThreshouldBag4.DiffBrightWidthL;
		ThreshouldBag.DiffBrightWidthH	=ThreshouldBag4.DiffBrightWidthH;
		ThreshouldBag.RegularCenterBright=ThreshouldBag4.RegularCenterBright;
		ThreshouldBag.ExpandForGenMask	=0;

		ThreshouldBag.NMinNGCountL	=ThreshouldBag4.NMinNGCountL;
		ThreshouldBag.NMinNGCountH	=ThreshouldBag4.NMinNGCountH;
		ThreshouldBag.BMinNGCountL	=ThreshouldBag4.BMinNGCountL;
		ThreshouldBag.BMinNGCountH	=ThreshouldBag4.BMinNGCountH;
		ThreshouldBag.NConnectLen	=ThreshouldBag4.NConnectLen;
		ThreshouldBag.BConnectLen	=ThreshouldBag4.BConnectLen;

		ThreshouldBag.PointMove.ModeEnabled			=ThreshouldBag4.PointMove.ModeEnabled;
		ThreshouldBag.PointMove.ModeAdjustable		=ThreshouldBag4.PointMove.ModeAdjustable;
		ThreshouldBag.PointMove.ModeAbsoluteBright	=ThreshouldBag4.PointMove.ModeAbsoluteBright;
		ThreshouldBag.PointMove.ModeCommonMovable	=ThreshouldBag4.PointMove.ModeCommonMovable;
		ThreshouldBag.PointMove.ModeNGCluster		=ThreshouldBag4.PointMove.ModeNGCluster;
		ThreshouldBag.PointMove.ModeDiffer			=ThreshouldBag4.PointMove.ModeDiffer;
		ThreshouldBag.PointMove.ModeCenterBrightFromParts	=ThreshouldBag4.PointMove.ModeCenterBrightFromParts;
		ThreshouldBag.PointMove.ModeOnlyMatching	=ThreshouldBag4.PointMove.ModeOnlyMatching;
		ThreshouldBag.PointMove.ModeWhiteMask		=ThreshouldBag4.PointMove.ModeWhiteMask;
		ThreshouldBag.PointMove.ModeBlackMask		=ThreshouldBag4.PointMove.ModeBlackMask;
		ThreshouldBag.PointMove.ModeCalcBothBN		=ThreshouldBag4.PointMove.ModeCalcBothBN;
		ThreshouldBag.PointMove.ModeInvertLogic		=ThreshouldBag4.PointMove.ModeInvertLogic;
		ThreshouldBag.PointMove.ModeMatchPosition	=ThreshouldBag4.PointMove.ModeMatchPosition;
		ThreshouldBag.PointMove.ModeMatchPositionBW	=ThreshouldBag4.PointMove.ModeMatchPositionBW;
		ThreshouldBag.PointMove.ModeSearchDetail	=ThreshouldBag4.PointMove.ModeSearchDetail;
		ThreshouldBag.PointMove.ModeDynamicMask		=ThreshouldBag4.PointMove.ModeDynamicMask;
		ThreshouldBag.PointMove.ModeBindBWBroad		=ThreshouldBag4.PointMove.ModeBindBWBroad;
		ThreshouldBag.PointMove.ModeBindBWNarrow	=ThreshouldBag4.PointMove.ModeBindBWNarrow;
		ThreshouldBag.PointMove.ModeAdoptBiggest	=ThreshouldBag4.PointMove.ModeAdoptBiggest;
		ThreshouldBag.PointMove.ModeUseMasterImage	=ThreshouldBag4.PointMove.ModeUseMasterImage;
		ThreshouldBag.PointMove.ModeUseRegularBrightness=ThreshouldBag4.PointMove.ModeUseRegularBrightness;
		ThreshouldBag.PointMove.ModePermitInverted		=ThreshouldBag4.PointMove.ModePermitInverted		;
		ThreshouldBag.PointMove.ModeOppositeRange		=ThreshouldBag4.PointMove.ModeOppositeRange		;
		ThreshouldBag.PointMove.ModeUseGlobalLine		=ThreshouldBag4.PointMove.ModeUseGlobalLine		;

        ThreshouldBag.CommonMoveID		=ThreshouldBag4.CommonMoveID;
        ThreshouldBag.CommonMoveDot		=ThreshouldBag4.CommonMoveDot;

		ThreshouldBag.SpaceToOutline	=ThreshouldBag4.SpaceToOutline;
        ThreshouldBag.AdjustBlack		=ThreshouldBag4.AdjustBlack;    
        ThreshouldBag.AdjustWhite		=ThreshouldBag4.AdjustWhite;    
        ThreshouldBag.SelfSearch		=ThreshouldBag4.SelfSearch;     
		ThreshouldBag.OmitVectorIndex	=ThreshouldBag4.OmitVectorIndex;
		ThreshouldBag.FollowLineLayer	=-1;
	}
	else{
		if(file->read((char *)&ThreshouldBag,sizeof(ThreshouldBag))!=sizeof(ThreshouldBag))
			return false;
	}
	if(Ver<10019){
		switch(ThreshouldBag.GeneratedOriginOld){
		case _ThreshouldBag2::_FromUnknown:	GetParentItem()->SetOriginType(_OriginType_FromUnknown);	break;
		case _ThreshouldBag2::_FromLibrary:	GetParentItem()->SetOriginType(_OriginType_FromLibrary);	break;
		case _ThreshouldBag2::_FromManual:	GetParentItem()->SetOriginType(_OriginType_FromManual);		break;
		case _ThreshouldBag2::_FromParts:	GetParentItem()->SetOriginType(_OriginType_FromParts);		break;
		case _ThreshouldBag2::_FromMPA:		GetParentItem()->SetOriginType(_OriginType_FromMPA);		break;
		case _ThreshouldBag2::_FromCAD:		GetParentItem()->SetOriginType(_OriginType_FromCAD);		break;
		}
	}
	if(Ver<10023){
		ThreshouldBag.PointMove.ModeMatchPositionBW	=false;
	}
	if(Ver<10024){
		ThreshouldBag.PointMove.ModeOppositeRange	=false;
	}
	if(Ver<10025){
		ThreshouldBag.PointMove.ModeUseGlobalLine	=true;
	}
	return true;
}

void	BlockThreshold::FromLibrary(AlgorithmLibrary *src)
{
	BlockLibrary	*LSrc=dynamic_cast<BlockLibrary *>(src);
	if(LSrc==NULL)
		return;
	ThreshouldBag.NBrightWidthL	=LSrc->NBrightWidthL;
	ThreshouldBag.NBrightWidthH	=LSrc->NBrightWidthH;
	ThreshouldBag.NOKDotL			=LSrc->NOKDotL;
	ThreshouldBag.NOKDotH			=LSrc->NOKDotH;
	ThreshouldBag.NMaxNGDotL		=LSrc->NMaxNGDotL;
	ThreshouldBag.NMaxNGDotH		=LSrc->NMaxNGDotH;
	ThreshouldBag.NOKLengthL		=LSrc->NOKLengthL;
	ThreshouldBag.NOKLengthH		=LSrc->NOKLengthH;
	ThreshouldBag.BBrightWidthL	=LSrc->BBrightWidthL;
	ThreshouldBag.BBrightWidthH	=LSrc->BBrightWidthH;
	ThreshouldBag.BOKDotL			=LSrc->BOKDotL;
	ThreshouldBag.BOKDotH			=LSrc->BOKDotH;
	ThreshouldBag.BMaxNGDotL		=LSrc->BMaxNGDotL;
	ThreshouldBag.BMaxNGDotH		=LSrc->BMaxNGDotH;
	ThreshouldBag.BOKLengthL		=LSrc->BOKLengthL;
	ThreshouldBag.BOKLengthH		=LSrc->BOKLengthH;
	ThreshouldBag.DiffBrightWidthL	=LSrc->DiffBrightWidthL;
	ThreshouldBag.DiffBrightWidthH	=LSrc->DiffBrightWidthH;
	ThreshouldBag.RegularCenterBright=LSrc->RegularBrightness;

	ThreshouldBag.PointMove.ModeEnabled					=LSrc->PointMove.ModeEnabled;
	ThreshouldBag.PointMove.ModeAdjustable				=LSrc->PointMove.ModeAdjustable;
	ThreshouldBag.PointMove.ModeAbsoluteBright			=LSrc->PointMove.ModeAbsoluteBright;
	ThreshouldBag.PointMove.ModeCommonMovable			=LSrc->PointMove.ModeCommonMovable;
	ThreshouldBag.PointMove.ModeNGCluster				=LSrc->PointMove.ModeNGCluster;
	ThreshouldBag.PointMove.ModeDiffer					=LSrc->PointMove.ModeDiffer;
	ThreshouldBag.PointMove.ModeCenterBrightFromParts	=LSrc->PointMove.ModeCenterBrightFromParts;
	ThreshouldBag.PointMove.ModeOnlyMatching			=LSrc->PointMove.ModeOnlyMatching;
	ThreshouldBag.PointMove.ModeWhiteMask				=LSrc->PointMove.ModeWhiteMask;
	ThreshouldBag.PointMove.ModeBlackMask				=LSrc->PointMove.ModeBlackMask;
	ThreshouldBag.PointMove.ModeInvertLogic				=LSrc->PointMove.ModeInvertLogic;
	ThreshouldBag.PointMove.ModeMatchPosition			=LSrc->PointMove.ModeMatchPosition;
	ThreshouldBag.PointMove.ModeMatchPositionBW			=LSrc->PointMove.ModeMatchPositionBW;
	ThreshouldBag.PointMove.ModeSearchDetail			=LSrc->PointMove.ModeSearchDetail;
	ThreshouldBag.PointMove.ModeDynamicMask				=LSrc->PointMove.ModeDynamicMask;
	ThreshouldBag.PointMove.ModeBindBWBroad				=LSrc->PointMove.ModeBindBWBroad;
	ThreshouldBag.PointMove.ModeBindBWNarrow			=LSrc->PointMove.ModeBindBWNarrow;
	ThreshouldBag.PointMove.ModeAdoptBiggest			=LSrc->PointMove.ModeAdoptBiggest;
	ThreshouldBag.PointMove.ModeUseMasterImage			=LSrc->PointMove.ModeUseMasterImage;
	ThreshouldBag.PointMove.ModeUseRegularBrightness	=(LSrc->RegularBrightness<0)?false:true;
	ThreshouldBag.PointMove.ModePermitInverted			=LSrc->PointMove.ModePermitInverted;
	ThreshouldBag.PointMove.ModeOppositeRange			=LSrc->PointMove.ModeOppositeRange;
	ThreshouldBag.PointMove.ModeUseGlobalLine			=LSrc->PointMove.ModeUseGlobalLine;

	GetParentItem()->SetOriginType(_OriginType_FromLibrary);

		//v->CommonMoveID;
	ThreshouldBag.CommonMoveDot						=LSrc->CommonMoveDot;

	ThreshouldBag.NMinNGCountL						=LSrc->NMinNGCountL;
	ThreshouldBag.NMinNGCountH						=LSrc->NMinNGCountH;
	ThreshouldBag.BMinNGCountL						=LSrc->BMinNGCountL;
	ThreshouldBag.BMinNGCountH						=LSrc->BMinNGCountH;
	ThreshouldBag.NConnectLen							=LSrc->NConnectLen;
	ThreshouldBag.BConnectLen							=LSrc->BConnectLen;
	ThreshouldBag.ExpandForGenMask						=LSrc->ExpandForGenMask;

	ThreshouldBag.SpaceToOutline						=LSrc->SpaceToOutline;
	ThreshouldBag.AdjustBlack							=LSrc->AdjustBlack;
	ThreshouldBag.AdjustWhite							=LSrc->AdjustWhite;
	ThreshouldBag.SelfSearch							=LSrc->SelfSearch;
	ThreshouldBag.FollowLineLayer						=LSrc->FollowLineLayer;
}
void	BlockThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	BlockLibrary	*LDst=dynamic_cast<BlockLibrary *>(Dest);
	if(LDst==NULL)
		return;
	LDst->NBrightWidthL		=ThreshouldBag.NBrightWidthL;
	LDst->NBrightWidthH		=ThreshouldBag.NBrightWidthH;
	LDst->NOKDotL			=ThreshouldBag.NOKDotL		;
	LDst->NOKDotH			=ThreshouldBag.NOKDotH	;
	LDst->NMaxNGDotL		=ThreshouldBag.NMaxNGDotL;
	LDst->NMaxNGDotH		=ThreshouldBag.NMaxNGDotH;
	LDst->NOKLengthL		=ThreshouldBag.NOKLengthL		;
	LDst->NOKLengthH		=ThreshouldBag.NOKLengthH	;
	LDst->BBrightWidthL		=ThreshouldBag.BBrightWidthL;
	LDst->BBrightWidthH		=ThreshouldBag.BBrightWidthH;
	LDst->BOKDotL			=ThreshouldBag.BOKDotL	;
	LDst->BOKDotH			=ThreshouldBag.BOKDotH	;
	LDst->BMaxNGDotL		=ThreshouldBag.BMaxNGDotL;
	LDst->BMaxNGDotH		=ThreshouldBag.BMaxNGDotH;
	LDst->BOKLengthL		=ThreshouldBag.BOKLengthL		;
	LDst->BOKLengthH		=ThreshouldBag.BOKLengthH	;
	LDst->DiffBrightWidthL	=ThreshouldBag.DiffBrightWidthL;
	LDst->DiffBrightWidthH	=ThreshouldBag.DiffBrightWidthH;

	LDst->PointMove.ModeEnabled				=ThreshouldBag.PointMove.ModeEnabled		;
	LDst->PointMove.ModeAdjustable			=ThreshouldBag.PointMove.ModeAdjustable	;
	LDst->PointMove.ModeAbsoluteBright		=ThreshouldBag.PointMove.ModeAbsoluteBright;
	LDst->PointMove.ModeCommonMovable		=ThreshouldBag.PointMove.ModeCommonMovable;
	LDst->PointMove.ModeNGCluster			=ThreshouldBag.PointMove.ModeNGCluster	;
	LDst->PointMove.ModeDiffer				=ThreshouldBag.PointMove.ModeDiffer		;
	LDst->PointMove.ModeCenterBrightFromParts	=ThreshouldBag.PointMove.ModeCenterBrightFromParts;
	LDst->PointMove.ModeOnlyMatching		=ThreshouldBag.PointMove.ModeOnlyMatching	;
	LDst->PointMove.ModeWhiteMask			=ThreshouldBag.PointMove.ModeWhiteMask		;
	LDst->PointMove.ModeBlackMask			=ThreshouldBag.PointMove.ModeBlackMask		;
	LDst->PointMove.ModeInvertLogic			=ThreshouldBag.PointMove.ModeInvertLogic	;
	LDst->PointMove.ModeMatchPosition		=ThreshouldBag.PointMove.ModeMatchPosition	;
	LDst->PointMove.ModeMatchPositionBW		=ThreshouldBag.PointMove.ModeMatchPositionBW;
	LDst->PointMove.ModeSearchDetail		=ThreshouldBag.PointMove.ModeSearchDetail;
	LDst->PointMove.ModeDynamicMask			=ThreshouldBag.PointMove.ModeDynamicMask;
	LDst->PointMove.ModeBindBWBroad			=ThreshouldBag.PointMove.ModeBindBWBroad;
	LDst->PointMove.ModeBindBWNarrow		=ThreshouldBag.PointMove.ModeBindBWNarrow;
	LDst->PointMove.ModeAdoptBiggest		=ThreshouldBag.PointMove.ModeAdoptBiggest;
	LDst->PointMove.ModeUseMasterImage		=ThreshouldBag.PointMove.ModeUseMasterImage;
	LDst->PointMove.ModePermitInverted		=ThreshouldBag.PointMove.ModePermitInverted;
	LDst->PointMove.ModeOppositeRange		=ThreshouldBag.PointMove.ModeOppositeRange;
	LDst->PointMove.ModeUseGlobalLine		=ThreshouldBag.PointMove.ModeUseGlobalLine;
	
	if(ThreshouldBag.PointMove.ModeUseRegularBrightness==false){
		LDst->RegularBrightness	=-1;
	}
	else{
		LDst->RegularBrightness	=ThreshouldBag.RegularCenterBright;
	}
	LDst->CommonMoveDot						=ThreshouldBag.CommonMoveDot		;

	LDst->NMinNGCountL					=ThreshouldBag.NMinNGCountL;
	LDst->NMinNGCountH					=ThreshouldBag.NMinNGCountH;
	LDst->BMinNGCountL					=ThreshouldBag.BMinNGCountL;
	LDst->BMinNGCountH					=ThreshouldBag.BMinNGCountH;
	LDst->NConnectLen					=ThreshouldBag.NConnectLen;
	LDst->BConnectLen					=ThreshouldBag.BConnectLen;
	LDst->ExpandForGenMask				=ThreshouldBag.ExpandForGenMask;

	LDst->SpaceToOutline				=ThreshouldBag.SpaceToOutline;
	LDst->AdjustBlack					=ThreshouldBag.AdjustBlack		;
	LDst->AdjustWhite					=ThreshouldBag.AdjustWhite		;
	LDst->SelfSearch					=ThreshouldBag.SelfSearch		;
	LDst->FollowLineLayer				=ThreshouldBag.FollowLineLayer	;
}

bool	BlockThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const BlockThreshold	*LSrc=dynamic_cast<const BlockThreshold *>(&src);

	if(ThreshouldBag.NBrightWidthL		!=LSrc->ThreshouldBag.NBrightWidthL			)	return false;
	if(ThreshouldBag.NBrightWidthH		!=LSrc->ThreshouldBag.NBrightWidthH			)	return false;
	if(ThreshouldBag.NOKDotL			!=LSrc->ThreshouldBag.NOKDotL				)	return false;
	if(ThreshouldBag.NOKDotH			!=LSrc->ThreshouldBag.NOKDotH				)	return false;
	if(ThreshouldBag.NMaxNGDotL			!=LSrc->ThreshouldBag.NMaxNGDotL			)	return false;
	if(ThreshouldBag.NMaxNGDotH			!=LSrc->ThreshouldBag.NMaxNGDotH			)	return false;
	if(ThreshouldBag.NOKLengthL			!=LSrc->ThreshouldBag.NOKLengthL			)	return false;
	if(ThreshouldBag.NOKLengthH			!=LSrc->ThreshouldBag.NOKLengthH			)	return false;
	if(ThreshouldBag.BBrightWidthL		!=LSrc->ThreshouldBag.BBrightWidthL			)	return false;
	if(ThreshouldBag.BBrightWidthH		!=LSrc->ThreshouldBag.BBrightWidthH			)	return false;
	if(ThreshouldBag.BOKDotL			!=LSrc->ThreshouldBag.BOKDotL				)	return false;
	if(ThreshouldBag.BOKDotH			!=LSrc->ThreshouldBag.BOKDotH				)	return false;
	if(ThreshouldBag.BMaxNGDotL			!=LSrc->ThreshouldBag.BMaxNGDotL			)	return false;
	if(ThreshouldBag.BMaxNGDotH			!=LSrc->ThreshouldBag.BMaxNGDotH			)	return false;
	if(ThreshouldBag.BOKLengthL			!=LSrc->ThreshouldBag.BOKLengthL			)	return false;
	if(ThreshouldBag.BOKLengthH			!=LSrc->ThreshouldBag.BOKLengthH			)	return false;
	if(ThreshouldBag.DiffBrightWidthL	!=LSrc->ThreshouldBag.DiffBrightWidthL		)	return false;
	if(ThreshouldBag.DiffBrightWidthH	!=LSrc->ThreshouldBag.DiffBrightWidthH		)	return false;
	if(ThreshouldBag.RegularCenterBright!=LSrc->ThreshouldBag.RegularCenterBright	)	return false;

	if(ThreshouldBag.PointMove.ModeEnabled				!=LSrc->ThreshouldBag.PointMove.ModeEnabled					)	return false;
	if(ThreshouldBag.PointMove.ModeAdjustable			!=LSrc->ThreshouldBag.PointMove.ModeAdjustable				)	return false;
	if(ThreshouldBag.PointMove.ModeAbsoluteBright		!=LSrc->ThreshouldBag.PointMove.ModeAbsoluteBright			)	return false;
	if(ThreshouldBag.PointMove.ModeCommonMovable		!=LSrc->ThreshouldBag.PointMove.ModeCommonMovable			)	return false;
	if(ThreshouldBag.PointMove.ModeNGCluster			!=LSrc->ThreshouldBag.PointMove.ModeNGCluster				)	return false;
	if(ThreshouldBag.PointMove.ModeDiffer				!=LSrc->ThreshouldBag.PointMove.ModeDiffer					)	return false;
	if(ThreshouldBag.PointMove.ModeCenterBrightFromParts!=LSrc->ThreshouldBag.PointMove.ModeCenterBrightFromParts	)	return false;
	if(ThreshouldBag.PointMove.ModeOnlyMatching			!=LSrc->ThreshouldBag.PointMove.ModeOnlyMatching			)	return false;
	if(ThreshouldBag.PointMove.ModeWhiteMask			!=LSrc->ThreshouldBag.PointMove.ModeWhiteMask				)	return false;
	if(ThreshouldBag.PointMove.ModeBlackMask			!=LSrc->ThreshouldBag.PointMove.ModeBlackMask				)	return false;
	if(ThreshouldBag.PointMove.ModeInvertLogic			!=LSrc->ThreshouldBag.PointMove.ModeInvertLogic				)	return false;
	if(ThreshouldBag.PointMove.ModeMatchPosition		!=LSrc->ThreshouldBag.PointMove.ModeMatchPosition			)	return false;
	if(ThreshouldBag.PointMove.ModeMatchPositionBW		!=LSrc->ThreshouldBag.PointMove.ModeMatchPositionBW			)	return false;
	if(ThreshouldBag.PointMove.ModeSearchDetail			!=LSrc->ThreshouldBag.PointMove.ModeSearchDetail			)	return false;
	if(ThreshouldBag.PointMove.ModeDynamicMask			!=LSrc->ThreshouldBag.PointMove.ModeDynamicMask				)	return false;
	if(ThreshouldBag.PointMove.ModeBindBWBroad			!=LSrc->ThreshouldBag.PointMove.ModeBindBWBroad				)	return false;
	if(ThreshouldBag.PointMove.ModeBindBWNarrow			!=LSrc->ThreshouldBag.PointMove.ModeBindBWNarrow			)	return false;
	if(ThreshouldBag.PointMove.ModeAdoptBiggest			!=LSrc->ThreshouldBag.PointMove.ModeAdoptBiggest			)	return false;
	if(ThreshouldBag.PointMove.ModeUseMasterImage		!=LSrc->ThreshouldBag.PointMove.ModeUseMasterImage			)	return false;
	if(ThreshouldBag.PointMove.ModeUseRegularBrightness	!=LSrc->ThreshouldBag.PointMove.ModeUseRegularBrightness	)	return false;
	if(ThreshouldBag.PointMove.ModePermitInverted		!=LSrc->ThreshouldBag.PointMove.ModePermitInverted			)	return false;
	if(ThreshouldBag.PointMove.ModeOppositeRange		!=LSrc->ThreshouldBag.PointMove.ModeOppositeRange			)	return false;
	if(ThreshouldBag.PointMove.ModeUseGlobalLine		!=LSrc->ThreshouldBag.PointMove.ModeUseGlobalLine			)	return false;


	if(ThreshouldBag.GeneratedOriginOld				!=LSrc->ThreshouldBag.GeneratedOriginOld)	return false;
	if(ThreshouldBag.CommonMoveDot					!=LSrc->ThreshouldBag.CommonMoveDot		)	return false;
													
	if(ThreshouldBag.NMinNGCountL					!=LSrc->ThreshouldBag.NMinNGCountL		)	return false;
	if(ThreshouldBag.NMinNGCountH					!=LSrc->ThreshouldBag.NMinNGCountH		)	return false;
	if(ThreshouldBag.BMinNGCountL					!=LSrc->ThreshouldBag.BMinNGCountL		)	return false;
	if(ThreshouldBag.BMinNGCountH					!=LSrc->ThreshouldBag.BMinNGCountH		)	return false;
	if(ThreshouldBag.NConnectLen					!=LSrc->ThreshouldBag.NConnectLen		)	return false;
	if(ThreshouldBag.BConnectLen					!=LSrc->ThreshouldBag.BConnectLen		)	return false;
	if(ThreshouldBag.ExpandForGenMask				!=LSrc->ThreshouldBag.ExpandForGenMask	)	return false;
													
	if(ThreshouldBag.SpaceToOutline					!=LSrc->ThreshouldBag.SpaceToOutline	)	return false;
	if(ThreshouldBag.AdjustBlack					!=LSrc->ThreshouldBag.AdjustBlack		)	return false;
	if(ThreshouldBag.AdjustWhite					!=LSrc->ThreshouldBag.AdjustWhite		)	return false;
	if(ThreshouldBag.SelfSearch						!=LSrc->ThreshouldBag.SelfSearch		)	return false;
	if(ThreshouldBag.OmitVectorIndex				!=LSrc->ThreshouldBag.OmitVectorIndex	)	return false;
	if(ThreshouldBag.FollowLineLayer				!=LSrc->ThreshouldBag.FollowLineLayer	)	return false;
	return true;
}

//===========================================================================================

void	BlockInPage::PickupTest(IntList &LayerList ,BlockLibrary &LibData)
{
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			BlockInLayer	*BI=dynamic_cast<BlockInLayer *>(AL);
			if(BI!=NULL){
				BI->PickupTest(LibData);
			}
		}
	}
}
void	BlockInPage::GenerateBlocks(IntList &LayerList, BlockLibrary *LibDim[],int LibDimNumb)
{
	for(int Layer=0;Layer<GetLayerNumb();Layer++){
		BlockLibrary *TmpLibDim[1000];
		int	LibN=0;
		for(int i=0;i<LibDimNumb;i++){
			if(LibDim[i]->HasGenLayer(Layer)==true
			|| ((LibDim[i]->GetAdaptedGenLayers().IsEmpty()==true) && LayerList.IsInclude(Layer)==true)){
				TmpLibDim[LibN]=LibDim[i];
				LibN++;
				if(LibN>=1000){
					break;
				}
			}
		}
		if(LibN!=0){
			AlgorithmInLayerRoot	*AL=GetLayerData(Layer);
			BlockInLayer	*BI=dynamic_cast<BlockInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(TmpLibDim,LibN);
			}
		}
	}
	/*
	for(IntClass *L=LayerList.GetFirst();L!=NULL;L=L->GetNext()){
		if(0<=L->GetValue() && L->GetValue()<GetLayerNumb()){
			AlgorithmInLayerRoot	*AL=GetLayerData(L->GetValue());
			BlockInLayer	*BI=dynamic_cast<BlockInLayer *>(AL);
			if(BI!=NULL){
				BI->GenerateBlocks(LibDim,LibDimNumb);
			}
		}
	}
	*/
}
void	BlockInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdModifySelectedBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(IntClass *L=ModifyItemFromBA->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}	
	CmdClearTestBlockPacket	*CmdClearTestBlockPacketVar=dynamic_cast<CmdClearTestBlockPacket *>(packet);
	if(CmdClearTestBlockPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdClearTestBlockPacketVar);
		}
		return;
	}
	CmdBlockInfoListPacket	*CmdBlockInfoListPacketVar=dynamic_cast<CmdBlockInfoListPacket *>(packet);
	if(CmdBlockInfoListPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(CmdBlockInfoListPacketVar);
		}
		return;
	}
	CmdGetBlockFromList	*CmdGetBlockFromListVar=dynamic_cast<CmdGetBlockFromList *>(packet);
	if(CmdGetBlockFromListVar!=NULL){
		if(CmdGetBlockFromListVar->CurrentItem.GetFirst()!=NULL){
			AlgorithmInLayerRoot	*p=GetLayerData(CmdGetBlockFromListVar->CurrentItem.GetFirst()->Layer);
			if(p!=NULL){
				p->TransmitDirectly(packet);
			}
		}
		return;
	}
	CmdCreateBlockItem	*CmdCreateBlockItemVar=dynamic_cast<CmdCreateBlockItem *>(packet);
	if(CmdCreateBlockItemVar!=NULL){
		AlgorithmInLayerRoot	*p=GetLayerData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdAlgoSimulate	*CmdAlgoSimulateVar=dynamic_cast<CmdAlgoSimulate *>(packet);
	if(CmdAlgoSimulateVar!=NULL){
		GetLayerData(CmdAlgoSimulateVar->Layer)->TransmitDirectly(packet);
		return;
	}
	CmdReqShrinkArea	*CmdReqShrinkAreaVar=dynamic_cast<CmdReqShrinkArea *>(packet);
	if(CmdReqShrinkAreaVar!=NULL){
		for(IntClass *L=CmdReqShrinkAreaVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetUsedLibID	*CmdGetUsedLibIDVar=dynamic_cast<CmdGetUsedLibID *>(packet);
	if(CmdGetUsedLibIDVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqShrinkHalf	*CmdReqShrinkHalfVar=dynamic_cast<CmdReqShrinkHalf *>(packet);
	if(CmdReqShrinkHalfVar!=NULL){
		for(IntClass *L=CmdReqShrinkHalfVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdReqExpandHalf	*CmdReqExpandHalfVar=dynamic_cast<CmdReqExpandHalf *>(packet);
	if(CmdReqExpandHalfVar!=NULL){
		for(IntClass *L=CmdReqExpandHalfVar->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
			AlgorithmInLayerRoot	*p=GetLayerData(L->GetValue());
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdSetNGSizeInBlock	*CmdSetNGSizeInBlockVar=dynamic_cast<CmdSetNGSizeInBlock *>(packet);
	if(CmdSetNGSizeInBlockVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdSetSearchDotInBlock	*CmdSetSearchDotInBlockVar=dynamic_cast<CmdSetSearchDotInBlock *>(packet);
	if(CmdSetSearchDotInBlockVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdUpdateBlockCommon	*CmdUpdateBlockCommonVar=dynamic_cast<CmdUpdateBlockCommon *>(packet);
	if(CmdUpdateBlockCommonVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdGenerateBlockCommon	*CmdGenerateBlockCommonVar=dynamic_cast<CmdGenerateBlockCommon *>(packet);
	if(CmdGenerateBlockCommonVar!=NULL){
		AlgorithmLibraryLevelContainer	*Lib[100];
		int	LibNumb=0;
		AlgorithmLibraryContainer	*Container=GetLibraryContainer();
		for(BlockLibraryWithThresholdList *a=CmdGenerateBlockCommonVar->Infos.GetFirst();a!=NULL;a=a->GetNext(),LibNumb++){
			Lib[LibNumb]=new AlgorithmLibraryLevelContainer(Container);
			CmdLoadBlockLibraryPacket	LPacket(GetLayersBase());
			LPacket.Point=Lib[LibNumb];
			LPacket.Point->SetLibID(a->LibID);
			GetParentBase()->TransmitDirectly(&LPacket);
		}

		GetLayersBase()->AddMaxProcessing(GetPage(),GetLayerNumb());
		
		LibNumb=0;
		for(int Layer=0;Layer<GetLayerNumb();Layer++){
			BlockLibrary *LibDim[100];
			int			LibDimNumb=0;
			for(BlockLibraryWithThresholdList *a=CmdGenerateBlockCommonVar->Infos.GetFirst();a!=NULL;a=a->GetNext(),LibNumb++){
				if(Lib[LibNumb]->GetAdaptedGenLayers().IsInclude(Layer)==true
				|| (Lib[LibNumb]->GetAdaptedGenLayers().GetCount()==0 && Layer==0)){
					LibDim[LibDimNumb]=dynamic_cast<BlockLibrary *>(Lib[LibNumb]->GetLibrary());
					LibDimNumb++;
				}
			}
			if(LibDimNumb>0){
				BlockInLayer		*p=(BlockInLayer *)GetLayerData(Layer);
				p->GenerateBlocks(LibDim,LibDimNumb);
				p->TransmitDirectly(packet);
			}
			GetLayersBase()->StepProcessing(GetPage());
		}

		for(int i=0;i<LibNumb;i++){
			delete	Lib[i];
		}
		return;
	}
	CmdRemoveAllOriginalBlockItems	*CmdRemoveAllOriginalBlockItemsVar=dynamic_cast<CmdRemoveAllOriginalBlockItems *>(packet);
	if(CmdRemoveAllOriginalBlockItemsVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	ChangeBlocksThresholdCommon	*ChangeBlocksThresholdCommonVar=dynamic_cast<ChangeBlocksThresholdCommon *>(packet);
	if(ChangeBlocksThresholdCommonVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmInLayerRoot		*p=GetLayerData(layer);
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdTryProcess	*CmdTryProcessVar=dynamic_cast<CmdTryProcess *>(packet);
	if(CmdTryProcessVar!=NULL){
		int layer=CmdTryProcessVar->BItemPoint->GetLayer();
		AlgorithmInLayerRoot		*p=GetLayerData(layer);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
}
bool	BlockInPage::PipeGeneration(GeneralPipeInfo &Info)
{
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormat){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqFormatBmpMap){
		Info.Cmd=GeneralPipeInfo::_GI_AckBmpMap;
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_InitialBmpMap){
		for(int layer=0;layer<GetLayerNumb();layer++){
			AlgorithmItemPointerListContainer Items;
			GetLayerData(layer)->EnumOriginTypeItems(Info.OperationOrigin,Items);
			for(AlgorithmItemPointerList *a=Items.GetFirst();a!=NULL;){
				AlgorithmItemPointerList *NextP=a->GetNext();
				if(a->GetItem()->GetEditLocked()==true){
					Items.RemoveList(a);
					delete	a;
				}
				a=NextP;
			}
			GetLayerData(layer)->RemoveItems(Items);
		}
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_SendBmpMap){
		//GetParentBase()->LoadAllManagedCacheLib();
		GetParentBase()->LoadManagedCacheLib(Info.LibID);
		BlockLibrary	*TmpLib=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(Info.LibID);
		if(TmpLib!=NULL){
			for(int layer=0;layer<GetLayerNumb();layer++){
				NPListPack<AlgorithmItemPLI>	TmpBlockData;
				if(TmpLib->HasGenLayer(layer)==true){
					BlockInLayer	*BL=(BlockInLayer*)GetLayerData(layer);

					BYTE	**TmpData=MakeMatrixBuff(Info.XByte ,Info.YLen);
					MatrixBuffCopy(TmpData					,Info.XByte ,Info.YLen
								, (const BYTE **)Info.BmpMap,Info.XByte ,Info.YLen);
					ConstMapBuffer MaskMap;
					BL->GetReflectionMap(_Reflection_Mask,MaskMap,TmpLib);
					bool	LimitedMaskInOtherPage=BL->UseLibraryForMaskingInOtherPage(Info.LibID);
					bool	LimitedMaskInThisPage =BL->IncludeLibInReflection(_Reflection_Mask,TmpLib,NULL);
					if(LimitedMaskInOtherPage==false || LimitedMaskInThisPage==true){
						MatrixBuffAnd	(TmpData ,MaskMap.GetBitMap() ,Info.XByte ,Info.YLen);
						
						if(Info.Something.count()>0){
							QBuffer	tBuff(&Info.Something);
							tBuff.open(QIODevice::ReadOnly);

							int32	AlgoCount;
							if(::Load(&tBuff,AlgoCount)==false)
								return false;
							QByteArray	DataArray;
							bool		Found=false;
							for(int i=0;i<AlgoCount;i++){
								QString	AlgoName;
								if(::Load(&tBuff,AlgoName)==false)
									return false;
								if(::Load(&tBuff,DataArray)==false)
									return false;
								if(AlgoName==/**/"BlockInspection"){
									Found=true;
									break;
								}
							}
							if(Found==true){
								QBuffer	Buff(&DataArray);
								Buff.open(QIODevice::ReadOnly);

								SetThresholdBlockInfo	ThresholdBlockInfoData;
								if(ThresholdBlockInfoData.Load(&Buff)==true){
									//TmpLib->SpaceToOutline	= 0;
									TmpLib->MakeBlockOnly(GetPage()
														,TmpData,MaskMap.GetBitMap(),Info.DriftMap
														,Info.XByte 
														,Info.XByte*8,Info.YLen
														,TmpBlockData
														,((BlockBase *)GetParentBase())->OmitZoneDot);
									for(AlgorithmItemPLI *aq=TmpBlockData.GetFirst();aq!=NULL;aq=aq->GetNext()){
										BlockItem	*BItem=dynamic_cast<BlockItem *>(aq);
										if(BItem!=NULL){
											BItem->SetThresholdFromCommon(&ThresholdBlockInfoData);
										}
									}
								}
							}
						}
						else{
							TmpLib->MakeBlockOnly(GetPage()
												,TmpData,MaskMap.GetBitMap(),Info.DriftMap
												,Info.XByte 
												,Info.XByte*8,Info.YLen
												,TmpBlockData
												,((BlockBase *)GetParentBase())->OmitZoneDot);
						}

						AlgorithmItemPLI	*q;
						while((q=TmpBlockData.GetFirst())!=NULL){
							TmpBlockData.RemoveList(q);
							q->SetOrigin(Info.Origin);
							q->SetOriginType(Info.OperationOrigin);
							BL->AppendItem(q);
							((BlockItem *)q)->MakeFLineBeforeShrink(*TmpLib);
							((BlockItem *)q)->MakeOmitArea(Info.OmitMap,Info.XByte ,Info.YLen);
						}
					}
					DeleteMatrixBuff(TmpData,Info.YLen);
					ManualExecuteAll(GetParentBase()->GetManualExecuter());
				}
			}
		}
		return true;
	}
	if(Info.Cmd==GeneralPipeInfo::_GI_ReqToMoveByAlignment){
		for(int layer=0;layer<GetLayerNumb();layer++){
			BlockInLayer	*L=(BlockInLayer *)GetLayerData(layer);
			L->MoveFromPipe(Info);
		}
		return true;
	}

	return false;
}

//===========================================================================================
BlockBase::BlockBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorPickup			=Qt::yellow;
	ColorBlockNormal	=Qt::darkGreen;
	ColorBlockSelected	=Qt::green;
	ColorBlockActive	=Qt::red;

	BlockColor0	=Qt::green;
	BlockColor1	=Qt::yellow;
	BlockColor2	=Qt::darkRed;
	BlockColor3	=Qt::cyan;
	BlockColor4	=Qt::magenta;
	BlockColor5	=Qt::darkGreen;
	BlockColor6	=Qt::darkYellow;
	BlockColor7	=Qt::darkCyan;
	OmitZoneDot	=100;
	RentalZone	=0;
	MoreSearchForRental	=2;
	RevivedStep	=2;
	RevivedShift=0;
	RevisedRotation=0;
	ReviveOKAgain	=false;
	VarLow		=20;
	UseTargetCenterInNoMaster	=true;
	ExtendFollowedOutline=true;
	LengthFollowedOutline=10;
	ExtendFollowedOutlineMult	=2;
	SkipSearchDot		=0;
	MaxBlockShiftCount	=3;

	SetParam(&ColorPickup		, /**/"Color" ,/**/"ColorPickup"		,LangSolver.GetString(XBlockInspection_LS,LID_30)/*"Color for Image to Pickup-Test "*/);
	SetParam(&ColorBlockNormal	, /**/"Color" ,/**/"ColorBlockNormal"	,LangSolver.GetString(XBlockInspection_LS,LID_32)/*"Color for Block"*/);
	SetParam(&ColorBlockSelected, /**/"Color" ,/**/"ColorBlockSelected"	,LangSolver.GetString(XBlockInspection_LS,LID_34)/*"Color for Selected Block"*/);
	SetParam(&ColorBlockActive	, /**/"Color" ,/**/"ColorBlockActive"	,LangSolver.GetString(XBlockInspection_LS,LID_36)/*"Color for Active Block"*/);

	SetParam(&BlockColor0	, /**/"BlockColor" ,/**/"BlockColor0"	,LangSolver.GetString(XBlockInspection_LS,LID_38)/*"Block Color 0"*/);
	SetParam(&BlockColor1	, /**/"BlockColor" ,/**/"BlockColor1"	,LangSolver.GetString(XBlockInspection_LS,LID_40)/*"Block Color 1"*/);
	SetParam(&BlockColor2	, /**/"BlockColor" ,/**/"BlockColor2"	,LangSolver.GetString(XBlockInspection_LS,LID_42)/*"Block Color 2"*/);
	SetParam(&BlockColor3	, /**/"BlockColor" ,/**/"BlockColor3"	,LangSolver.GetString(XBlockInspection_LS,LID_44)/*"Block Color 3"*/);
	SetParam(&BlockColor4	, /**/"BlockColor" ,/**/"BlockColor4"	,LangSolver.GetString(XBlockInspection_LS,LID_46)/*"Block Color 4"*/);
	SetParam(&BlockColor5	, /**/"BlockColor" ,/**/"BlockColor5"	,LangSolver.GetString(XBlockInspection_LS,LID_48)/*"Block Color 5"*/);
	SetParam(&BlockColor6	, /**/"BlockColor" ,/**/"BlockColor6"	,LangSolver.GetString(XBlockInspection_LS,LID_50)/*"Block Color 6"*/);
	SetParam(&BlockColor7	, /**/"BlockColor" ,/**/"BlockColor7"	,LangSolver.GetString(XBlockInspection_LS,LID_52)/*"Block Color 7"*/);

	SetParam(&OmitZoneDot			, /**/"Setting"		,/**/"OmitZoneDot"	,LangSolver.GetString(XBlockInspection_LS,LID_54)/*"Omit zone dot in block generation"*/);
	SetParam(&RentalZone			, /**/"Setting"		,/**/"RentalZone"	,LangSolver.GetString(XBlockInspection_LS,LID_114)/*"Rental zone dot"*/);
	SetParam(&MoreSearchForRental	, /**/"Setting"		,/**/"MoreSearchForRental"	,LangSolver.GetString(XBlockInspection_LS,LID_115)/*"More dots to search for rental block"*/);
	SetParam(&RevivedStep			, /**/"Setting"		,/**/"RevivedStep"		,LangSolver.GetString(XBlockInspection_LS,LID_116)/*"Step dot for revived re-calculation"*/);
	SetParam(&RevivedShift			, /**/"Setting"		,/**/"RevivedShift"		,LangSolver.GetString(XBlockInspection_LS,LID_117)/*"Shift dot for revived re-calculation"*/);
	SetParam(&RevisedRotation		, /**/"Setting"		,/**/"RevisedRotation"	,LangSolver.GetString(XBlockInspection_LS,LID_118)/*"Rotation dot for revived re-calculation"*/);
	SetParam(&ReviveOKAgain			, /**/"Setting"		,/**/"ReviveOKAgain"	,LangSolver.GetString(XBlockInspection_LS,LID_119)/*"Revive for re-calculation of OK items too"*/);
	SetParam(&VarLow				, /**/"Setting"		,/**/"VarLow"			,LangSolver.GetString(XBlockInspection_LS,LID_120)/*"Var limit low for outline chaser"*/);
	SetParam(&UseTargetCenterInNoMaster, /**/"Setting"	,/**/"UseTargetCenterInNoMaster"			,LangSolver.GetString(XBlockInspection_LS,LID_121)/*"Use target center brightness in no master image mode"*/);
	SetParam(&SkipSearchDot			, /**/"Setting"		,/**/"SkipSearchDot"	,LangSolver.GetString(XBlockInspection_LS,LID_9)/*"Skip dot for search"*/);

	SetParam(&ExtendFollowedOutline	, /**/"FollowOutline"	,/**/"ExtendFollowedOutline"	,LangSolver.GetString(XBlockInspection_LS,LID_4)/*"If checked , extend x2 of line length"*/);
	SetParam(&LengthFollowedOutline	, /**/"FollowOutline"	,/**/"LengthFollowedOutline"	,LangSolver.GetString(XBlockInspection_LS,LID_5)/*"Line length of follow-line"*/);
	SetParam(&MaxBlockShiftCount	, /**/"FollowOutline"	,/**/"MaxBlockShiftCount"		,"Max search count in Loop");

	GetManualExecuter().RegisteringClass(new ManualExecuterBlockBBrightL(0));
	GetManualExecuter().RegisteringClass(new ManualExecuterBlockBBrightH(0));
	GetManualExecuter().RegisteringClass(new ManualExecuterBlockNBrightL(0));
	GetManualExecuter().RegisteringClass(new ManualExecuterBlockNBrightH(0));

	if(MaxBlockShiftCount>MaxCountOfBlockShiftList)
		MaxBlockShiftCount=MaxCountOfBlockShiftList;

	//int	N0=sizeof(FlexArea);
	//int	N1=sizeof(BlockItem);
	//int	N2=sizeof(AlgorithmItemPLI);
	//int	N3=sizeof(AlgorithmItemRoot);
	//int	N4=sizeof(BlockThreshold);
}

AlgorithmDrawAttr	*BlockBase::CreateDrawAttr(void)
{
	return new BlockDrawAttr();
}

void	BlockBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetBlockLibraryListPacket	*AListPacket=dynamic_cast<CmdGetBlockLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
	CmdGetBlockLibraryListInPasteLayerPacket	*ACmdGetBlockLibraryListInPasteLayerPacketVar=dynamic_cast<CmdGetBlockLibraryListInPasteLayerPacket *>(packet);
	if(ACmdGetBlockLibraryListInPasteLayerPacketVar!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),ACmdGetBlockLibraryListInPasteLayerPacketVar->LibFolderID 
				,ACmdGetBlockLibraryListInPasteLayerPacketVar->AList);
			for(AlgorithmLibraryList *a=ACmdGetBlockLibraryListInPasteLayerPacketVar->AList.GetFirst();a!=NULL;){
				AlgorithmLibraryList *NextA=a->GetNext();
				IntList	PickupLayers;
				IntList	GeneratedLayers;
				if(GetLibraryContainer()->GetLayers(a->GetLibID(),PickupLayers,GeneratedLayers)==false
				|| (ACmdGetBlockLibraryListInPasteLayerPacketVar->Layer>=0 && GeneratedLayers.IsInclude(ACmdGetBlockLibraryListInPasteLayerPacketVar->Layer)==false)){
					ACmdGetBlockLibraryListInPasteLayerPacketVar->AList.RemoveList(a);
					delete	a;
				}
				a=NextA;
			}
		}
		return;
	}
	CmdGetBlockLibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetBlockLibraryNamePacket *>(packet);
	if(ANamePacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
		}
		return;
	}
	CmdInsertBlockLibraryPacket	*BInsLib=dynamic_cast<CmdInsertBlockLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		BInsLib->Point->SetDataVersion(BlockInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateBlockLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateBlockLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		BUpdLib->Point->SetDataVersion(BlockInspectionVersion);
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadBlockLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadBlockLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempBlockLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempBlockLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearBlockLibraryPacket	*CmdClearBlockLibraryPacketVar=dynamic_cast<CmdClearBlockLibraryPacket *>(packet);
	if(CmdClearBlockLibraryPacketVar!=NULL){
		CmdClearBlockLibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteBlockLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteBlockLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
	CmdPickupTestBlockPacket	*BPickLib=dynamic_cast<CmdPickupTestBlockPacket *>(packet);
	if(BPickLib!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(BPickLib->Page);
		if(p==NULL)
			return;
		BlockInPage	*Bp=dynamic_cast<BlockInPage *>(p);
		if(Bp==NULL)
			return;
		Bp->PickupTest(BPickLib->LayerList,*(BlockLibrary *)BPickLib->LibPoint->GetLibrary());		
		return;
	}
	CmdGenerateBlockPacket	*BGenerated=dynamic_cast<CmdGenerateBlockPacket *>(packet);
	if(BGenerated!=NULL){
		AlgorithmLibraryLevelContainer	**LibDim=new AlgorithmLibraryLevelContainer*[BGenerated->LibList.GetCount()];
		int	N=0;
		for(IntClass *L=BGenerated->LibList.GetFirst();L!=NULL;L=L->GetNext(),N++){
			LibDim[N]=new AlgorithmLibraryLevelContainer(this);
			GetLibraryContainer()->GetLibrary(L->GetValue(),*LibDim[N]);
		}
		for(;;){
			bool	Changed=false;
			for(int i=0;i<N-1;i++){
				BlockLibrary	*L1=dynamic_cast<BlockLibrary *>(LibDim[i  ]->GetLibrary());
				BlockLibrary	*L2=dynamic_cast<BlockLibrary *>(LibDim[i+1]->GetLibrary());
				if(L1->Priority>L2->Priority){
					AlgorithmLibraryLevelContainer	Tmp(this);
					Tmp=*LibDim[i];
					*LibDim[i]=*LibDim[i+1];
					*LibDim[i+1]=Tmp;
					Changed=true;
				}
			}
			if(Changed==false)
				break;
		}
		BlockLibrary	**LDim=new BlockLibrary*[N];
		for(int i=0;i<N;i++){
			LDim[i]=dynamic_cast<BlockLibrary *>(LibDim[i]->GetLibrary());
		}

		AlgorithmInPageRoot		*p=GetPageData(BGenerated->Page);
		if(p!=NULL){
			BlockInPage	*Bp=dynamic_cast<BlockInPage *>(p);
			if(Bp!=NULL){
				Bp->GenerateBlocks(BGenerated->LayerList,LDim,N);		
			}
		}
		delete	[]LDim;
		for(int i=0;i<N;i++){
			delete	LibDim[i];
		}
		delete	[]LibDim;
		//PostRebuildItems();
		return;
	}
	CmdCreateTempBlockItemPacket	*CreateBlockItem=dynamic_cast<CmdCreateTempBlockItemPacket *>(packet);
	if(CreateBlockItem!=NULL){
		CreateBlockItem->Point=new BlockItem();
		return;
	}
	CmdCreateByteArrayFromBlockItemPacket	*BAFromBlockItem=dynamic_cast<CmdCreateByteArrayFromBlockItemPacket *>(packet);
	if(BAFromBlockItem!=NULL){
		QBuffer	Buff(&BAFromBlockItem->Buff);
		Buff.open(QIODevice::ReadWrite);
		BAFromBlockItem->Point->Save(&Buff);
		return;
	}
	CmdAddByteBlockItemPacket	*AddBItem=dynamic_cast<CmdAddByteBlockItemPacket *>(packet);
	if(AddBItem!=NULL){
		AlgorithmInPagePLI		*PData=dynamic_cast<AlgorithmInPagePLI	*>(GetPageData(AddBItem->LocalPage));
		if(PData!=NULL){
			ClearManagedCacheLib();
			for(IntClass *L=AddBItem->LayerList.GetFirst();L!=NULL;L=L->GetNext()){
				BlockInLayer	*BL=dynamic_cast<BlockInLayer *>(PData->GetLayerData(L->GetValue()));
				if(BL!=NULL){
					QBuffer	MBuff(&AddBItem->Buff);
					BlockItem	*Item=new BlockItem();
					MBuff.open(QIODevice::ReadWrite);
					Item->Load(&MBuff,GetLayersBase());
					Item->SetArea(AddBItem->Area);
					Item->SetManualCreated(true);
					if(BL->AppendItem(Item)==true){
						UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(BL,&BlockInLayer::UndoAppendManualItem);
						::Save(UPointer->GetWritePointer(),Item->GetID());
						Item->Save(UPointer->GetWritePointer());
						GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
					}
					else{
						delete	Item;
					}
				}
			}
		}
		return;
	}
	CmdLoadBlockItemPacketFromByteArray	*FromBA=dynamic_cast<CmdLoadBlockItemPacketFromByteArray *>(packet);
	if(FromBA!=NULL){
		QBuffer	MBuff(&FromBA->Buff);
		MBuff.open(QIODevice::ReadWrite);
		FromBA->BItemPoint->Load(&MBuff,GetLayersBase());
		return;
	}
	CmdModifySelectedBlockFromByteArray	*ModifyItemFromBA=dynamic_cast<CmdModifySelectedBlockFromByteArray *>(packet);
	if(ModifyItemFromBA!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(ModifyItemFromBA);
		}
		return;
	}
	CmdGetLibName	*PCmdGetLibName=dynamic_cast<CmdGetLibName *>(packet);
	if(PCmdGetLibName!=NULL){
		if(GetLibraryContainer()!=NULL){
			AlgorithmLibraryLevelContainer	LibData(this);
			if(GetLibraryContainer()->GetLibrary(PCmdGetLibName->LibID,LibData)==true){
				PCmdGetLibName->LibName=LibData.GetLibName();
			}
		}
		return;
	}
	CmdClearTestBlockPacket	*CmdClearTestBlockPacketVar=dynamic_cast<CmdClearTestBlockPacket *>(packet);
	if(CmdClearTestBlockPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			AlgorithmInPageRoot		*p=GetPageData(page);
			p->TransmitDirectly(CmdClearTestBlockPacketVar);
		}
		return;
	}
	CmdBlockInfoListPacket	*CmdBlockInfoListPacketVar=dynamic_cast<CmdBlockInfoListPacket *>(packet);
	if(CmdBlockInfoListPacketVar!=NULL){
		GetPageData(CmdBlockInfoListPacketVar->LocalPage)->TransmitDirectly(packet);
		return;
	}
	CmdGetBlockFromList	*CmdGetBlockFromListVar=dynamic_cast<CmdGetBlockFromList *>(packet);
	if(CmdGetBlockFromListVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(CmdGetBlockFromListVar->LocalPage);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
	CmdCreateBlockItem	*CmdCreateBlockItemVar=dynamic_cast<CmdCreateBlockItem *>(packet);
	if(CmdCreateBlockItemVar!=NULL){
		AlgorithmInPageRoot		*p=GetPageData(0);
		if(p!=NULL){
			p->TransmitDirectly(packet);
		}
		return;
	}
}

bool	BlockBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockHistogramListReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==BlockReqChangeShiftCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*BlockBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==BlockHistogramListSendCommand){
		BlockHistogramListSend	*pSend=new BlockHistogramListSend();
		if(reqData!=NULL){
			BlockHistogramListReq	*req=(BlockHistogramListReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==BlockHistogramListReqCommand){
		return new BlockHistogramListReq();
	}
	else if(Command==BlockReqThresholdReqCommand){
		return new BlockThresholdReq();
	}
	else if(Command==BlockReqThresholdSendCommand){
		BlockThresholdSend	*pSend=new BlockThresholdSend();
		if(reqData!=NULL){
			BlockThresholdReq	*req=(BlockThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==BlockReqTryThresholdCommand){
		return new BlockReqTryThreshold();
	}
	else if(Command==BlockSendTryThresholdCommand){
		BlockSendTryThreshold	*pSend=new BlockSendTryThreshold();
		if(reqData!=NULL){
			BlockReqTryThreshold	*req=(BlockReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==BlockReqChangeShiftCommand){
		return new BlockChangeShift();
	}
	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	BlockBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		BlockHistogramListSend	*p=(BlockHistogramListSend *)data;
		return p->Load(f);
	}
	else if(Command==BlockHistogramListReqCommand){
		BlockHistogramListReq	*p=(BlockHistogramListReq *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqThresholdReqCommand){
		BlockThresholdReq	*p=(BlockThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqThresholdSendCommand){
		BlockThresholdSend	*p=(BlockThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqTryThresholdCommand){
		BlockReqTryThreshold	*p=(BlockReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==BlockSendTryThresholdCommand){
		BlockSendTryThreshold	*p=(BlockSendTryThreshold *)data;
		return p->Load(f);
	}
	else if(Command==BlockReqChangeShiftCommand){
		BlockChangeShift	*p=(BlockChangeShift *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	BlockBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		BlockHistogramListSend	*p=(BlockHistogramListSend *)data;
		return p->Save(f);
	}
	else if(Command==BlockHistogramListReqCommand){
		BlockHistogramListReq	*p=(BlockHistogramListReq *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqThresholdReqCommand){
		BlockThresholdReq	*p=(BlockThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqThresholdSendCommand){
		BlockThresholdSend	*p=(BlockThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqTryThresholdCommand){
		BlockReqTryThreshold	*p=(BlockReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==BlockSendTryThresholdCommand){
		BlockSendTryThreshold	*p=(BlockSendTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==BlockReqChangeShiftCommand){
		BlockChangeShift	*p=(BlockChangeShift *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	BlockBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==BlockHistogramListSendCommand){
		BlockHistogramListSend	*p=(BlockHistogramListSend *)data;
		return true;
	}
	else if(Command==BlockHistogramListReqCommand){
		BlockHistogramListReq	*p=(BlockHistogramListReq *)data;
		return true;
	}
	else if(Command==BlockReqThresholdReqCommand){
		BlockThresholdReq	*p=(BlockThresholdReq *)data;
		return true;
	}
	else if(Command==BlockReqThresholdSendCommand){
		BlockThresholdSend	*p=(BlockThresholdSend *)data;
		return true;
	}
	else if(Command==BlockReqTryThresholdCommand){
		BlockReqTryThreshold	*p=(BlockReqTryThreshold *)data;
		return true;
	}
	else if(Command==BlockSendTryThresholdCommand){
		BlockSendTryThreshold	*p=(BlockSendTryThreshold *)data;
		return true;
	}
	else if(Command==BlockReqChangeShiftCommand){
		BlockChangeShift	*p=(BlockChangeShift *)data;
		p->Reflect(this);
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}

bool	BlockBase::ShowPasteCreateWithShape(QByteArray &templateData,int Layer)
{
	ChangeCreateBlockForm	Q(this,Layer,GetLayersBase()->GetMainWidget());
	bool	ret=Q.exec();
	if(ret==true){
		QBuffer	Buff(&templateData);
		Buff.open(QIODevice::ReadWrite);
		if(Q.ResultBlock.Save(&Buff)==false)
			return false;
	}
	return ret;
}
int	BlockBase::GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)
{
	if(MaxDimCount>=4){
		MenuPointer[0].MenuMessage	="OK by brightness";
		MenuPointer[0].MenuID		=LearningMenu_BlockInspection_OK_ByBrightness;
		MenuPointer[0].OkMode		=true;
		MenuPointer[1].MenuMessage	="OK by size";
		MenuPointer[1].MenuID		=LearningMenu_BlockInspection_OK_BySize;
		MenuPointer[1].OkMode		=true;
		MenuPointer[2].MenuMessage	="OK by shift";
		MenuPointer[2].MenuID		=LearningMenu_BlockInspection_OK_ByShift;
		MenuPointer[2].OkMode		=true;
		MenuPointer[3].MenuMessage	="NG by brightness";
		MenuPointer[3].MenuID		=LearningMenu_BlockInspection_NG_ByBrightness;
		MenuPointer[3].OkMode		=false;
		MenuPointer[4].MenuMessage	="NG by size";
		MenuPointer[4].MenuID		=LearningMenu_BlockInspection_NG_Size;
		MenuPointer[4].OkMode		=false;
		return 5;
	}
	return 0;
}

//===========================================================================================


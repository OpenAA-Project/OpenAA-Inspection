/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XBlockItem.cpp
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

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	DbgID=46;
static	int	DbgPage=2;
static	int	DbgLayer=0;
static	int	DbgNumer=0;


BlockItem::FollowLines::FollowLines(BlockItem &Parent)
	:LftMatchLine0(&Parent)
	,LftMatchLine1(&Parent)
	,LftMatchLine2(&Parent)
	,TopMatchLine0(&Parent)
	,TopMatchLine1(&Parent)
	,TopMatchLine2(&Parent)
	,RgtMatchLine0(&Parent)
	,RgtMatchLine1(&Parent)
	,RgtMatchLine2(&Parent)
	,BtmMatchLine0(&Parent)
	,BtmMatchLine1(&Parent)
	,BtmMatchLine2(&Parent)
{
}

BlockItem::FollowLines	&BlockItem::FollowLines::operator=(BlockItem::FollowLines &src)
{
	LftMatchLine0=src.LftMatchLine0;
	LftMatchLine1=src.LftMatchLine1;
	LftMatchLine2=src.LftMatchLine2;
	TopMatchLine0=src.TopMatchLine0;
	TopMatchLine1=src.TopMatchLine1;
	TopMatchLine2=src.TopMatchLine2;
	RgtMatchLine0=src.RgtMatchLine0;
	RgtMatchLine1=src.RgtMatchLine1;
	RgtMatchLine2=src.RgtMatchLine2;
	BtmMatchLine0=src.BtmMatchLine0;
	BtmMatchLine1=src.BtmMatchLine1;
	BtmMatchLine2=src.BtmMatchLine2;

	return *this;
}

void	BlockItem::FollowLines::MoveTo(int OffsetX ,int OffsetY)
{
	LftMatchLine0.MoveTo(OffsetX,OffsetY);
	LftMatchLine1.MoveTo(OffsetX,OffsetY);
	LftMatchLine2.MoveTo(OffsetX,OffsetY);
	TopMatchLine0.MoveTo(OffsetX,OffsetY);
	TopMatchLine1.MoveTo(OffsetX,OffsetY);
	TopMatchLine2.MoveTo(OffsetX,OffsetY);

	RgtMatchLine0.MoveTo(OffsetX,OffsetY);
	RgtMatchLine1.MoveTo(OffsetX,OffsetY);
	RgtMatchLine2.MoveTo(OffsetX,OffsetY);
	BtmMatchLine0.MoveTo(OffsetX,OffsetY);
	BtmMatchLine1.MoveTo(OffsetX,OffsetY);
	BtmMatchLine2.MoveTo(OffsetX,OffsetY);
}

void	BlockItem::FollowLines::CalcMatchPosition(bool ModeUseMasterImage 
												,FlexArea &FLineBeforeShrink 
												,FlexArea &OmitMatchLineArea
												,int FollowLinelength
												,bool Gen_Left
												,bool Gen_Top
												,bool Gen_Right
												,bool Gen_Bottom
												,ExecuteInitialAfterEditInfo &EInfo)
{
	//#pragma omp parallel sections
	//{
		if(Gen_Left==true){
		//#pragma omp section
			LftMatchLine0.ExecuteInitialAfterEdit(true,0,FollowLinelength,EInfo);
		//#pragma omp section
			LftMatchLine1.ExecuteInitialAfterEdit(true,1,FollowLinelength,EInfo);
		//#pragma omp section
			LftMatchLine2.ExecuteInitialAfterEdit(true,2,FollowLinelength,EInfo);
		}
		else{
			LftMatchLine0.SetEffective(false);
			LftMatchLine1.SetEffective(false);
			LftMatchLine2.SetEffective(false);
		}

		//#pragma omp section
		if(Gen_Top==true){
			TopMatchLine0.ExecuteInitialAfterEdit(true,0,FollowLinelength,EInfo);
		//#pragma omp section
			TopMatchLine1.ExecuteInitialAfterEdit(true,1,FollowLinelength,EInfo);
		//#pragma omp section
			TopMatchLine2.ExecuteInitialAfterEdit(true,2,FollowLinelength,EInfo);
		}
		else{
			TopMatchLine0.SetEffective(false);
			TopMatchLine1.SetEffective(false);
			TopMatchLine2.SetEffective(false);
		}

		if(Gen_Right==true){
		//#pragma omp section
			RgtMatchLine0.ExecuteInitialAfterEdit(false,0,FollowLinelength,EInfo);
		//#pragma omp section
			RgtMatchLine1.ExecuteInitialAfterEdit(false,1,FollowLinelength,EInfo);
		//#pragma omp section
			RgtMatchLine2.ExecuteInitialAfterEdit(false,2,FollowLinelength,EInfo);
		}
		else{
			RgtMatchLine0.SetEffective(false);
			RgtMatchLine1.SetEffective(false);
			RgtMatchLine2.SetEffective(false);
		}

		if(Gen_Bottom==true){
		//#pragma omp section
			BtmMatchLine0.ExecuteInitialAfterEdit(false,0,FollowLinelength,EInfo);
		//#pragma omp section
			BtmMatchLine1.ExecuteInitialAfterEdit(false,1,FollowLinelength,EInfo);
		//#pragma omp section
			BtmMatchLine2.ExecuteInitialAfterEdit(false,2,FollowLinelength,EInfo);
		}
		else{
			BtmMatchLine0.SetEffective(false);
			BtmMatchLine1.SetEffective(false);
			BtmMatchLine2.SetEffective(false);
		}
	//}
	double	Var=0;
	int		N=0;
	if(LftMatchLine0.IsEffective()==true){
		Var+=LftMatchLine0.GetSelfCoef();
		N++;
	}
	if(LftMatchLine1.IsEffective()==true){
		Var+=LftMatchLine1.GetSelfCoef();
		N++;
	}
	if(LftMatchLine2.IsEffective()==true){
		Var+=LftMatchLine2.GetSelfCoef();
		N++;
	}
	if(TopMatchLine0.IsEffective()==true){
		Var+=TopMatchLine0.GetSelfCoef();
		N++;
	}
	if(TopMatchLine1.IsEffective()==true){
		Var+=TopMatchLine1.GetSelfCoef();
		N++;
	}
	if(TopMatchLine2.IsEffective()==true){
		Var+=TopMatchLine2.GetSelfCoef();
		N++;
	}
	if(RgtMatchLine0.IsEffective()==true){
		Var+=RgtMatchLine0.GetSelfCoef();
		N++;
	}
	if(RgtMatchLine1.IsEffective()==true){
		Var+=RgtMatchLine1.GetSelfCoef();
		N++;
	}
	if(RgtMatchLine2.IsEffective()==true){
		Var+=RgtMatchLine2.GetSelfCoef();
		N++;
	}
	if(BtmMatchLine0.IsEffective()==true){
		Var+=BtmMatchLine0.GetSelfCoef();
		N++;
	}
	if(BtmMatchLine1.IsEffective()==true){
		Var+=BtmMatchLine1.GetSelfCoef();
		N++;
	}
	if(BtmMatchLine2.IsEffective()==true){
		Var+=BtmMatchLine2.GetSelfCoef();
		N++;
	}
	if(N!=0){
		Var/=N;
		Var*=0.1;
		if(ModeUseMasterImage==true){
			if(LftMatchLine0.IsEffective()==true && (LftMatchLine0.GetSelfCoef()<Var || LftMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false)){
				LftMatchLine0.SetEffective(false);
			}
			if(LftMatchLine1.IsEffective()==true && (LftMatchLine1.GetSelfCoef()<Var || LftMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false)){
				LftMatchLine1.SetEffective(false);
			}
			if(LftMatchLine2.IsEffective()==true && (LftMatchLine2.GetSelfCoef()<Var || LftMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false)){
				LftMatchLine2.SetEffective(false);
			}

			if(TopMatchLine0.IsEffective()==true && (TopMatchLine0.GetSelfCoef()<Var || TopMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false)){
				TopMatchLine0.SetEffective(false);
			}
			if(TopMatchLine1.IsEffective()==true && (TopMatchLine1.GetSelfCoef()<Var || TopMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false)){
				TopMatchLine1.SetEffective(false);
			}
			if(TopMatchLine2.IsEffective()==true && (TopMatchLine2.GetSelfCoef()<Var || TopMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false)){
				TopMatchLine2.SetEffective(false);
			}

			if(RgtMatchLine0.IsEffective()==true && (RgtMatchLine0.GetSelfCoef()<Var || RgtMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false)){
				RgtMatchLine0.SetEffective(false);
			}
			if(RgtMatchLine1.IsEffective()==true && (RgtMatchLine1.GetSelfCoef()<Var || RgtMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false)){
				RgtMatchLine1.SetEffective(false);
			}
			if(RgtMatchLine2.IsEffective()==true && (RgtMatchLine2.GetSelfCoef()<Var || RgtMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false)){
				RgtMatchLine2.SetEffective(false);
			}

			if(BtmMatchLine0.IsEffective()==true && (BtmMatchLine0.GetSelfCoef()<Var || BtmMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false)){
				BtmMatchLine0.SetEffective(false);
			}
			if(BtmMatchLine1.IsEffective()==true && (BtmMatchLine1.GetSelfCoef()<Var || BtmMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false)){
				BtmMatchLine1.SetEffective(false);
			}
			if(BtmMatchLine2.IsEffective()==true && (BtmMatchLine2.GetSelfCoef()<Var || BtmMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false)){
				BtmMatchLine2.SetEffective(false);
			}
		}
		else{
			if(LftMatchLine0.IsEffective()==true && LftMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false){
				LftMatchLine0.SetEffective(false);
			}
			if(LftMatchLine1.IsEffective()==true && LftMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false){
				LftMatchLine1.SetEffective(false);
			}
			if(LftMatchLine2.IsEffective()==true && LftMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false){
				LftMatchLine2.SetEffective(false);
			}

			if(TopMatchLine0.IsEffective()==true && TopMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false){
				TopMatchLine0.SetEffective(false);
			}
			if(TopMatchLine1.IsEffective()==true && TopMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false){
				TopMatchLine1.SetEffective(false);
			}
			if(TopMatchLine2.IsEffective()==true && TopMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false){
				TopMatchLine2.SetEffective(false);
			}

			if(RgtMatchLine0.IsEffective()==true && RgtMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false){
				RgtMatchLine0.SetEffective(false);
			}
			if(RgtMatchLine1.IsEffective()==true && RgtMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false){
				RgtMatchLine1.SetEffective(false);
			}
			if(RgtMatchLine2.IsEffective()==true && RgtMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false){
				RgtMatchLine2.SetEffective(false);
			}

			if(BtmMatchLine0.IsEffective()==true && BtmMatchLine0.CheckOverlapArea(FLineBeforeShrink)==false){
				BtmMatchLine0.SetEffective(false);
			}
			if(BtmMatchLine1.IsEffective()==true && BtmMatchLine1.CheckOverlapArea(FLineBeforeShrink)==false){
				BtmMatchLine1.SetEffective(false);
			}
			if(BtmMatchLine2.IsEffective()==true && BtmMatchLine2.CheckOverlapArea(FLineBeforeShrink)==false){
				BtmMatchLine2.SetEffective(false);
			}
		}
		if(LftMatchLine0.IsEffective()==true && LftMatchLine0.CheckOverlapArea(OmitMatchLineArea)==true){
			LftMatchLine0.SetEffective(false);
		}
		if(LftMatchLine1.IsEffective()==true && LftMatchLine1.CheckOverlapArea(OmitMatchLineArea)==true){
			LftMatchLine1.SetEffective(false);
		}
		if(LftMatchLine2.IsEffective()==true && LftMatchLine2.CheckOverlapArea(OmitMatchLineArea)==true){
			LftMatchLine2.SetEffective(false);
		}

		if(TopMatchLine0.IsEffective()==true && TopMatchLine0.CheckOverlapArea(OmitMatchLineArea)==true){
			TopMatchLine0.SetEffective(false);
		}
		if(TopMatchLine1.IsEffective()==true && TopMatchLine1.CheckOverlapArea(OmitMatchLineArea)==true){
			TopMatchLine1.SetEffective(false);
		}
		if(TopMatchLine2.IsEffective()==true && TopMatchLine2.CheckOverlapArea(OmitMatchLineArea)==true){
			TopMatchLine2.SetEffective(false);
		}

		if(RgtMatchLine0.IsEffective()==true && RgtMatchLine0.CheckOverlapArea(OmitMatchLineArea)==true){
			RgtMatchLine0.SetEffective(false);
		}
		if(RgtMatchLine1.IsEffective()==true && RgtMatchLine1.CheckOverlapArea(OmitMatchLineArea)==true){
			RgtMatchLine1.SetEffective(false);
		}
		if(RgtMatchLine2.IsEffective()==true && RgtMatchLine2.CheckOverlapArea(OmitMatchLineArea)==true){
			RgtMatchLine2.SetEffective(false);
		}

		if(BtmMatchLine0.IsEffective()==true && BtmMatchLine0.CheckOverlapArea(OmitMatchLineArea)==true){
			BtmMatchLine0.SetEffective(false);
		}
		if(BtmMatchLine1.IsEffective()==true && BtmMatchLine1.CheckOverlapArea(OmitMatchLineArea)==true){
			BtmMatchLine1.SetEffective(false);
		}
		if(BtmMatchLine2.IsEffective()==true && BtmMatchLine2.CheckOverlapArea(OmitMatchLineArea)==true){
			BtmMatchLine2.SetEffective(false);
		}
	}
}
bool	BlockItem::FollowLines::IsEffective(void)
{
	if(LftMatchLine0.IsEffective()==true
	|| LftMatchLine1.IsEffective()==true
	|| LftMatchLine2.IsEffective()==true
	|| TopMatchLine0.IsEffective()==true
	|| TopMatchLine1.IsEffective()==true
	|| TopMatchLine2.IsEffective()==true
	|| RgtMatchLine0.IsEffective()==true
	|| RgtMatchLine1.IsEffective()==true
	|| RgtMatchLine2.IsEffective()==true
	|| BtmMatchLine0.IsEffective()==true
	|| BtmMatchLine1.IsEffective()==true
	|| BtmMatchLine2.IsEffective()==true){
		return true;
	}
	return false;
}

void	BlockItem::FollowLines::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &LineColor)
{
	LftMatchLine0.Draw(pnt,movx,movy,ZoomRate,LineColor);
	LftMatchLine1.Draw(pnt,movx,movy,ZoomRate,LineColor);
	LftMatchLine2.Draw(pnt,movx,movy,ZoomRate,LineColor);
	TopMatchLine0.Draw(pnt,movx,movy,ZoomRate,LineColor);
	TopMatchLine1.Draw(pnt,movx,movy,ZoomRate,LineColor);
	TopMatchLine2.Draw(pnt,movx,movy,ZoomRate,LineColor);

	RgtMatchLine0.Draw(pnt,movx,movy,ZoomRate,LineColor);
	RgtMatchLine1.Draw(pnt,movx,movy,ZoomRate,LineColor);
	RgtMatchLine2.Draw(pnt,movx,movy,ZoomRate,LineColor);
	BtmMatchLine0.Draw(pnt,movx,movy,ZoomRate,LineColor);
	BtmMatchLine1.Draw(pnt,movx,movy,ZoomRate,LineColor);
	BtmMatchLine2.Draw(pnt,movx,movy,ZoomRate,LineColor);
}

//====================================================================================================
BlockItem::BlockItem(void)
{
	InitialConstructor();
}
BlockItem::BlockItem(FlexArea &area)
:AlgorithmItemPLI(area)
{
	InitialConstructor();
}
BlockItem::BlockItem(FlexArea *area)
:AlgorithmItemPLI(area)
{
	InitialConstructor();
}

void BlockItem::InitialConstructor(void)
{
	CenterBright	=0;
	CenterTargetBright	=0;
	AVector=NULL;
	SkipSearchAreasData	=NULL;
	ShiftX	=0;
	ShiftY	=0;
	FollowLineData	=NULL;
}

BlockItem::~BlockItem(void)
{
	if(SkipSearchAreasData!=NULL){
		delete	SkipSearchAreasData;
		SkipSearchAreasData=NULL;
	}
}
void    BlockItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPLI::MoveTo(dx,dy);

	FLineBeforeShrink.MoveToNoClip(dx,dy);
    FLineEdge		.MoveToNoClip(dx,dy);
    FLineInside		.MoveToNoClip(dx,dy);

	AppeUp		.MoveToNoClip(dx,dy);
	AppeLeft	.MoveToNoClip(dx,dy);
	AppeRight	.MoveToNoClip(dx,dy);
	AppeBottom	.MoveToNoClip(dx,dy);
	DisaUp		.MoveToNoClip(dx,dy);
	DisaLeft	.MoveToNoClip(dx,dy);
	DisaRight	.MoveToNoClip(dx,dy);
	DisaBottom	.MoveToNoClip(dx,dy);

	if(SkipSearchAreasData!=NULL){
		SkipSearchAreasData->AppeUp		.MoveToNoClip(dx,dy);
		SkipSearchAreasData->AppeLeft	.MoveToNoClip(dx,dy);
		SkipSearchAreasData->AppeRight	.MoveToNoClip(dx,dy);
		SkipSearchAreasData->AppeBottom	.MoveToNoClip(dx,dy);
		SkipSearchAreasData->DisaUp		.MoveToNoClip(dx,dy);
		SkipSearchAreasData->DisaLeft	.MoveToNoClip(dx,dy);
		SkipSearchAreasData->DisaRight	.MoveToNoClip(dx,dy);
		SkipSearchAreasData->DisaBottom	.MoveToNoClip(dx,dy);
	}
}

AlgorithmItemPLI	&BlockItem::operator=(const AlgorithmItemRoot &src)
{
	const BlockItem	*s=dynamic_cast<const BlockItem *>(&src);
	if(s!=NULL)
		return AlgorithmItemPLI::operator=(src);
	return *this;
}
BlockItem &BlockItem::operator=(BlockItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);

	return *this;
}

void	BlockItem::CopyThreshold(BlockItem &src)
{
	CenterBright	=src.CenterBright;
	GetThresholdW()->CopyFrom(*((BlockThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	BlockItem::CopyThresholdOnly(BlockItem &src,IntList &EdittedMemberID)
{
	GetThresholdW()->CopyFrom(*((BlockThreshold *)src.GetThresholdR()),EdittedMemberID);
	SetInvertLogic(src.GetInvertLogic());
}

bool    BlockItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;

	WORD	XVer=0x8003;

	if(::Save(file,XVer)==false)
		return false;

	if(::Save(file,CenterBright)==false)
		return false;
	if(FLineBeforeShrink.Save(file)==false)
		return false;
	if(::Save(file,ShiftX)==false)
		return false;
	if(::Save(file,ShiftY)==false)
		return false;
	if(OmitMatchLineArea.Save(file)==false)
		return false;
	return true;
}
bool    BlockItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;
	bool	LoadedFLineBeforeShrink=false;
	if(LoadedVersion==1){
		if(::Load(file,CenterBright)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.NBrightWidthL)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.NBrightWidthH)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.NOKDotL)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.NOKDotH)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.BBrightWidthL)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.BBrightWidthH)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.BOKDotL)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.BOKDotH)==false)
			return false;
		if(file->read((char *)&GetThresholdW()->ThreshouldBag.PointMove,sizeof(GetThresholdW()->ThreshouldBag.PointMove))!=sizeof(GetThresholdW()->ThreshouldBag.PointMove))
			return false;
		if(file->read((char *)&GetThresholdW()->ThreshouldBag.GeneratedOriginOld,sizeof(GetThresholdW()->ThreshouldBag.GeneratedOriginOld))!=sizeof(GetThresholdW()->ThreshouldBag.GeneratedOriginOld))
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.CommonMoveID)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.CommonMoveDot)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.AdjustBlack)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.AdjustWhite)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.SelfSearch)==false)
			return false;
		if(::Load(file,GetThresholdW()->ThreshouldBag.OmitVectorIndex)==false)
			return false;
	}
	else{
		WORD	XVer;
		if(::Load(file,XVer)==false)
			return false;
		if(XVer<0x8000){
			CenterBright=XVer;
		}
		else{
			if(::Load(file,CenterBright)==false)
				return false;
			if(FLineBeforeShrink.Load(file)==false)
				return false;
			LoadedFLineBeforeShrink=true;
			if(XVer>=0x8002){
				if(::Load(file,ShiftX)==false)
					return false;
				if(::Load(file,ShiftY)==false)
					return false;
			}
			if(XVer>=0x8003){
				if(OmitMatchLineArea.Load(file)==false)
					return false;
			}
		}
	}
	if(LoadedFLineBeforeShrink==false){
		FLineBeforeShrink=GetArea();
	}
	if(GetArea().GetWidth()*GetArea().GetHeight()<65530)
		GetThresholdW()->CalculatedInfo.ModeSmallCalc=true;
	else
		GetThresholdW()->CalculatedInfo.ModeSmallCalc=false;
	return true;
}

void	BlockItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			BlockInLayer	*Ly=dynamic_cast<BlockInLayer *>(GetParentInLayer());
			UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(Ly,&BlockInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			BlockItem *src=(BlockItem *)Data;
			const	BlockThreshold	*RThr=GetThresholdR();
			bool	OldModeMatchPosition		=RThr->ThreshouldBag.PointMove.ModeMatchPosition;
			bool	OldModeMatchPositionBW		=RThr->ThreshouldBag.PointMove.ModeMatchPositionBW;
			CopyThresholdOnly(*src,EdittedMemberID);
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			if(IsOriginParts()==false || RThr->ThreshouldBag.PointMove.ModeCenterBrightFromParts==false){
				if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && GetMasterBuff().IsNull()==false){
					CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
				}
				else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && GetTargetBuff().IsNull()==false){
					CenterBright=CalcCenterBright(GetTargetBuff(),0,0);
				}
				else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
					CenterBright=RThr->ThreshouldBag.RegularCenterBright;
				}
				else{
					CenterBright=0;
				}
			}
			if((OldModeMatchPosition	!=RThr->ThreshouldBag.PointMove.ModeMatchPosition)
			|| (OldModeMatchPositionBW	!=RThr->ThreshouldBag.PointMove.ModeMatchPositionBW)){
				ExecuteInitialAfterEditInfo DummyEInfo;
				DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				CalcMatchPosition(DummyEInfo);
			}
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((BlockItem *)Data)->GetLibID()){
			BlockInLayer	*Ly=dynamic_cast<BlockInLayer *>(GetParentInLayer());
			UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(Ly,&BlockInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			BlockItem *src=(BlockItem *)Data;
			const	BlockThreshold	*RThr=GetThresholdR();
			bool	OldModeMatchPosition	=RThr->ThreshouldBag.PointMove.ModeMatchPosition;
			bool	OldModeMatchPositionBW	=RThr->ThreshouldBag.PointMove.ModeMatchPositionBW;
			CopyThresholdOnly(*src,EdittedMemberID);
			SetLibID(src->GetLibID());
			if(IsOriginParts()==false || RThr->ThreshouldBag.PointMove.ModeCenterBrightFromParts==false){
				if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && GetMasterBuff().IsNull()==false){
					CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
				}
				else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && GetTargetBuff().IsNull()==false){
					CenterBright=CalcCenterBright(GetTargetBuff(),0,0);
				}
				else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
					CenterBright=RThr->ThreshouldBag.RegularCenterBright;
				}
				else{
					CenterBright=0;
				}
			}
			if((OldModeMatchPosition  !=RThr->ThreshouldBag.PointMove.ModeMatchPosition)
			|| (OldModeMatchPositionBW!=RThr->ThreshouldBag.PointMove.ModeMatchPositionBW)){
				ExecuteInitialAfterEditInfo DummyEInfo;
				DummyEInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
				CalcMatchPosition(DummyEInfo);
			}
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((BlockItem *)Data)->GetLibID()){
			BlockInLayer	*Ly=dynamic_cast<BlockInLayer *>(GetParentInLayer());
			UndoElement<BlockInLayer>	*UPointer=new UndoElement<BlockInLayer>(Ly,&BlockInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			BlockItem *src=(BlockItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}
void	BlockItem::SetInvertLogic(bool b)
{
	AlgorithmItemPLI::SetInvertLogic(b);
	GetThresholdW()->ThreshouldBag.PointMove.ModeInvertLogic=b;
}
	
bool	BlockItem::GetInvertLogic(void)	
{
	return GetThresholdR()->ThreshouldBag.PointMove.ModeInvertLogic;
}

void	BlockItem::CopyArea(BlockItem &src)
{
	SetArea(src.GetArea());
	FLineBeforeShrink	=src.FLineBeforeShrink;
    FLineEdge			=src.FLineEdge;
    FLineInside			=src.FLineInside;

	AppeUp			=src.AppeUp	;
	AppeLeft		=src.AppeLeft;
	AppeRight		=src.AppeRight;
	AppeBottom		=src.AppeBottom;
	DisaUp			=src.DisaUp	;
	DisaLeft		=src.DisaLeft;
	DisaRight		=src.DisaRight;
	DisaBottom		=src.DisaBottom;

	if(src.SkipSearchAreasData!=NULL){
		if(SkipSearchAreasData==NULL){
			SkipSearchAreasData=new struct	SkipSearchAreas;
		}
		if(SkipSearchAreasData!=NULL){
			SkipSearchAreasData->AppeUp		=src.SkipSearchAreasData->AppeUp	;
			SkipSearchAreasData->AppeLeft	=src.SkipSearchAreasData->AppeLeft;
			SkipSearchAreasData->AppeRight	=src.SkipSearchAreasData->AppeRight;
			SkipSearchAreasData->AppeBottom	=src.SkipSearchAreasData->AppeBottom;
			SkipSearchAreasData->DisaUp		=src.SkipSearchAreasData->DisaUp	;
			SkipSearchAreasData->DisaLeft	=src.SkipSearchAreasData->DisaLeft;
			SkipSearchAreasData->DisaRight	=src.SkipSearchAreasData->DisaRight;
			SkipSearchAreasData->DisaBottom	=src.SkipSearchAreasData->DisaBottom;
		}
	}
	else{
		if(SkipSearchAreasData!=NULL){
			delete	SkipSearchAreasData;
			SkipSearchAreasData=NULL;
		}
	}
}


int		BlockItem::GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	return 100;
}

void	BlockItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	BlockItem	*ASrc=dynamic_cast<BlockItem *>(src);
	if(ASrc!=NULL){	
		FLineBeforeShrink.SetRefereneFrom(&ASrc->FLineBeforeShrink);
		FLineBeforeShrink.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		FLineEdge		 .SetRefereneFrom(&ASrc->FLineEdge);
		FLineEdge		 .MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		FLineInside		 .SetRefereneFrom(&ASrc->FLineInside);
		FLineInside		 .MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		int	OmitZoneDot=((BlockBase *)GetParentBase())->OmitZoneDot;
		GetArea()			.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineBeforeShrink	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineEdge			.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		FLineInside			.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		CenterBright	=ASrc->CenterBright;

		if(ASrc->FollowLineData==NULL){
			if(FollowLineData!=NULL)
				delete	FollowLineData;
			FollowLineData=NULL;
		}
		else{
			if(FollowLineData==NULL)
				FollowLineData=new BlockItem::FollowLines(*this);
			*FollowLineData=*ASrc->FollowLineData;
		}
		OmitMatchLineArea	=ASrc->OmitMatchLineArea;

		if(FollowLineData!=NULL)
			FollowLineData->MoveTo(OffsetX,OffsetY);

		AppeUp		.SetRefereneFrom(&ASrc->AppeUp		);
		AppeLeft	.SetRefereneFrom(&ASrc->AppeLeft	);
		AppeRight	.SetRefereneFrom(&ASrc->AppeRight	);
		AppeBottom	.SetRefereneFrom(&ASrc->AppeBottom	);
		DisaUp		.SetRefereneFrom(&ASrc->DisaUp		);
		DisaLeft	.SetRefereneFrom(&ASrc->DisaLeft	);
		DisaRight	.SetRefereneFrom(&ASrc->DisaRight	);
		DisaBottom	.SetRefereneFrom(&ASrc->DisaBottom	);

		AppeUp		.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		AppeLeft	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		AppeRight	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		AppeBottom	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		DisaUp		.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		DisaLeft	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		DisaRight	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
		DisaBottom	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

		AppeUp		.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		AppeLeft	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		AppeRight	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		AppeBottom	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		DisaUp		.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		DisaLeft	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		DisaRight	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		DisaBottom	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);

		if(ASrc->SkipSearchAreasData!=NULL){
			if(SkipSearchAreasData==NULL){
				SkipSearchAreasData=new struct	SkipSearchAreas;
			}
			SkipSearchAreasData->AppeUp		.SetRefereneFrom(&ASrc->SkipSearchAreasData->AppeUp		);
			SkipSearchAreasData->AppeLeft	.SetRefereneFrom(&ASrc->SkipSearchAreasData->AppeLeft	);
			SkipSearchAreasData->AppeRight	.SetRefereneFrom(&ASrc->SkipSearchAreasData->AppeRight	);
			SkipSearchAreasData->AppeBottom	.SetRefereneFrom(&ASrc->SkipSearchAreasData->AppeBottom	);
			SkipSearchAreasData->DisaUp		.SetRefereneFrom(&ASrc->SkipSearchAreasData->DisaUp		);
			SkipSearchAreasData->DisaLeft	.SetRefereneFrom(&ASrc->SkipSearchAreasData->DisaLeft	);
			SkipSearchAreasData->DisaRight	.SetRefereneFrom(&ASrc->SkipSearchAreasData->DisaRight	);
			SkipSearchAreasData->DisaBottom	.SetRefereneFrom(&ASrc->SkipSearchAreasData->DisaBottom	);

			SkipSearchAreasData->AppeUp		.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->AppeLeft	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->AppeRight	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->AppeBottom	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->DisaUp		.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->DisaLeft	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->DisaRight	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());
			SkipSearchAreasData->DisaBottom	.MoveToClip(OffsetX,OffsetY,0,0,GetDotPerLine(),GetMaxLines());

			SkipSearchAreasData->AppeUp		.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->AppeLeft	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->AppeRight	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->AppeBottom	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->DisaUp		.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->DisaLeft	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->DisaRight	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
			SkipSearchAreasData->DisaBottom	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		}
	}
	else{
		if(SkipSearchAreasData!=NULL){
			delete	SkipSearchAreasData;
			SkipSearchAreasData=NULL;
		}
	}
}

ExeResult	BlockItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	if(GetID()==DbgID && GetPage()==DbgPage && GetLayer()==DbgLayer)
		DbgNumer++;	
	int	cx,cy;
	//_CrtCheckMemory();

	int	gap=((BlockBase *)GetParentBase())->OmitZoneDot;
	if(GetLayersBase()->GetBootingLevel()>=1){
		gap=5;
	}
	if(GetFromRental()==false){
		GetArea().ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	}

	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	if(GetArea().GetWidth()*GetArea().GetHeight()<65530)
		GetThresholdW()->CalculatedInfo.ModeSmallCalc=true;
	else
		GetThresholdW()->CalculatedInfo.ModeSmallCalc=false;

	if(IsEdited()==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true){
		if(IsOriginParts()==false){
			MakeInsideEdgeArea();
		}
	}
	BlockInLayer	*P=(BlockInLayer *)GetParentInLayer();
	const	BlockThreshold	*RThr=GetThresholdR();
	if(IsOriginParts()==false || RThr->ThreshouldBag.PointMove.ModeCenterBrightFromParts==false){
		if(GetMasterBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
			if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && RThr->ThreshouldBag.PointMove.ModeDynamicMask==true)
				CenterBright=CalcCenterBright(GetMasterBuff(),0,0
											,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
			else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false){
				//if(IsEdited()==true || GetMasterBuff().IsChanged()==true){
					CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
				//}
			}
		}
		else if(GetTargetBuff().IsNull()==false && (GetParamGlobal()->NoLoadSaveMasterImage==false || GetParamGlobal()->IsLoadedMasterImageSuccessful==true)){
			if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false && RThr->ThreshouldBag.PointMove.ModeDynamicMask==true)
				CenterBright=CalcCenterBright(GetTargetBuff(),0,0
											,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
			else if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==false){
				//if(IsEdited()==true || GetTargetBuff().IsChanged()==true){
					CenterBright=CalcCenterBright(GetTargetBuff(),0,0);
				//}
			}
		}
		CenterTargetBright=CenterBright;
	}
	if(RThr->ThreshouldBag.PointMove.ModeUseRegularBrightness==true){
		CenterBright=RThr->ThreshouldBag.RegularCenterBright;
		CenterTargetBright=CenterBright;
	}

	//_CrtCheckMemory();
	//if(IsEdited()==true
	//|| GetLayersBase()->IsChanged(AlgorithmBit_TypeMasking)==true || GetLayersBase()->IsChanged(AlgorithmBit_TypeDynamicMasking)==true 
	//|| (GetMasterBuff().IsNull()==false && GetMasterBuff().IsChanged()==true)){
		CalcMatchPosition(EInfo);
	//}

	return Ret;
}

void	BlockItem::MakeFLineBeforeShrink(BlockLibrary &BLib)
{
	BYTE	BmpImageBuff [10000];
	BYTE	TmpImageBuff [10000];

	const	BlockThreshold	*RThr=GetThresholdR();
	int	ExpandForGenMask=RThr->ThreshouldBag.ExpandForGenMask;
	int	Mergin=8+ExpandForGenMask;
	FlexArea FLineBS;
	FLineBS=GetArea();
	int	mx=FLineBS.GetMinX()-Mergin;
	int	my=FLineBS.GetMinY()-Mergin;
	FLineBS.MoveToNoClip(-mx,-my);
	int	XLen=FLineBS.GetMaxX()+Mergin+Mergin;
	int	YLen=FLineBS.GetMaxY()+Mergin+Mergin;
	int	XByte=(XLen+7)/8;
	BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen,BmpImageBuff,sizeof(BmpImageBuff));
	MatrixBuffClear(BmpImage,0,XByte,YLen);
	BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen,TmpImageBuff,sizeof(TmpImageBuff));

	FLineBS.MakeBitData(BmpImage,XLen,YLen);
	if(BLib.GenerationCategory==BlockLibrary::_AutoSetting_OTHERMASK
	|| BLib.GenerationCategory==BlockLibrary::_AutoSetting_SURROUND){
		GetLayersBase()->ThinAreaN(BmpImage,TmpImage ,XByte, YLen,ExpandForGenMask);
	}
	else{
		GetLayersBase()->FatAreaN(BmpImage,TmpImage ,XByte, YLen,ExpandForGenMask);
	}
	/*
	for(int y=0;y<YLen;y++){
		if((y+my)<0 || GetMaxLines()<=(y+my))
			continue;
		BYTE	*d=BmpImage[y];
		BYTE	*s=CurrentMap[my+y];
		for(int x=0;x<XLen;x++){
			if(GetBmpBitOnY(d,x)!=0){
				if((x+mx)<0 || GetDotPerLine()<=(x+mx))
					continue;
				if(GetBmpBitOnY(s,x+mx)==0){
					SetBmpBitOnY0(d,x);
				}
			}
		}
	}
	*/
	FLineBeforeShrink.BuildFromRaster(BmpImage,XByte ,YLen,mx,my);

	if((BYTE	**)BmpImageBuff!=BmpImage){
		DeleteMatrixBuff(BmpImage,YLen);
	}
	if((BYTE	**)TmpImageBuff!=TmpImage){
		DeleteMatrixBuff(TmpImage,YLen);
	}
}

void	BlockItem::CalcMatchPosition(ExecuteInitialAfterEditInfo &EInfo)
{
	if(IsOriginParts()==true)
		return;
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeMatchPosition==true
	|| RThr->ThreshouldBag.PointMove.ModeMatchPositionBW==true){
		BlockLibrary	*LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(GetLibID());
		if(LibP==NULL){
			GetParentBase()->LoadAllManagedCacheLib();
			LibP=(BlockLibrary *)GetParentBase()->FindLibFromManagedCacheLib(GetLibID());
		}
		if(LibP!=NULL){
			if(FollowLineData==NULL)
				FollowLineData=new FollowLines(*this);
			FollowLineData->CalcMatchPosition(RThr->ThreshouldBag.PointMove.ModeUseMasterImage
											,FLineBeforeShrink
											,OmitMatchLineArea
											,LibP->FollowLineLength
											,LibP->GenFollowLine.Gen_Left
											,LibP->GenFollowLine.Gen_Top
											,LibP->GenFollowLine.Gen_Right
											,LibP->GenFollowLine.Gen_Bottom
											,EInfo);
		}
	}
	else{									
		if(FollowLineData!=NULL)
			delete	FollowLineData;
		FollowLineData=NULL;
	}
}

void	BlockItem::MakeInsideEdgeArea(void)
{
	BYTE	BmpImageBuff [10000];
	BYTE	TmpImageBuff [10000];
	BYTE	TmpImageBuff2[10000];
	try{
		FLineInside=GetArea();
		const	BlockThreshold	*RThr=GetThresholdR();
		int	SelfSearch=RThr->ThreshouldBag.SelfSearch;
		int	mx=FLineInside.GetMinX()-8-SelfSearch;
		int	my=FLineInside.GetMinY()-8-SelfSearch;
		FLineInside.MoveToNoClip(-mx,-my);
		int	XLen=FLineInside.GetMaxX()+16+SelfSearch;
		int	YLen=FLineInside.GetMaxY()+16+SelfSearch;
		int	XByte=(XLen+7)/8;
		BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen,BmpImageBuff,sizeof(BmpImageBuff));
		MatrixBuffClear(BmpImage,0,XByte,YLen,false);
		BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen,TmpImageBuff,sizeof(TmpImageBuff));
		BYTE	**TmpImage2=MakeMatrixBuff(XByte,YLen,TmpImageBuff2,sizeof(TmpImageBuff2));

		FLineInside.MakeBitData(BmpImage,XLen,YLen,false);

		FLineInside.MoveToNoClip(0,-1);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		AppeUp.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(-1,1);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		AppeLeft.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(2,0);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		AppeRight.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(-1,1);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		AppeBottom.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);


		FLineInside.MoveToNoClip(0,-2);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		DisaUp.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(-1,1);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		DisaLeft.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(2,0);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		DisaRight.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		FLineInside.MoveToNoClip(-1,1);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		FLineInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		DisaBottom.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		GetLayersBase()->ThinAreaN(BmpImage
					,TmpImage
					,XByte ,YLen
					,RThr->ThreshouldBag.SelfSearch);

		FLineInside.BuildFromRaster(BmpImage,XByte ,YLen,0,0);
		FLineInside	.MoveToNoClip(mx,my);
		FLineEdge	.Sub(GetArea(),FLineInside);
		if((BYTE	**)BmpImageBuff!=BmpImage){
			DeleteMatrixBuff(BmpImage,YLen);
		}
		if((BYTE	**)TmpImageBuff!=TmpImage){
			DeleteMatrixBuff(TmpImage,YLen);
		}
		if((BYTE	**)TmpImageBuff2!=TmpImage2){
			DeleteMatrixBuff(TmpImage2,YLen);
		}
		//int	gap=((BlockBase *)GetParentBase())->OmitZoneDot;
		//FLineInside	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
		//FLineEdge	.ClipArea(gap,gap,GetDotPerLine()-gap,GetMaxLines()-gap);
	}
	catch(...){}

	int	SkipSearchDot=((BlockBase *)GetParentBase())->SkipSearchDot;
	if(SkipSearchDot>1){
		if(SkipSearchAreasData==NULL){
			SkipSearchAreasData=new struct	SkipSearchAreas;
		}
		FlexArea	TmpInside;
		TmpInside=GetArea();
		int	mx=TmpInside.GetMinX()-8-SkipSearchDot;
		int	my=TmpInside.GetMinY()-8-SkipSearchDot;
		TmpInside.MoveToNoClip(-mx,-my);
		int	XLen=TmpInside.GetMaxX()+16+2*SkipSearchDot;
		int	YLen=TmpInside.GetMaxY()+16+2*SkipSearchDot;
		int	XByte=(XLen+7)/8;
		BYTE	**BmpImage=MakeMatrixBuff(XByte,YLen,BmpImageBuff,sizeof(BmpImageBuff));
		MatrixBuffClear(BmpImage,0,XByte,YLen,false);
		BYTE	**TmpImage=MakeMatrixBuff(XByte,YLen,TmpImageBuff,sizeof(TmpImageBuff));
		BYTE	**TmpImage2=MakeMatrixBuff(XByte,YLen,TmpImageBuff2,sizeof(TmpImageBuff2));

		TmpInside.MakeBitData(BmpImage,XLen,YLen,false);

		TmpInside.MoveToNoClip(0,-SkipSearchDot);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		SkipSearchAreasData->AppeUp.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(-SkipSearchDot,SkipSearchDot);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		SkipSearchAreasData->AppeLeft.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(2*SkipSearchDot,0);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		SkipSearchAreasData->AppeRight.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(-SkipSearchDot,SkipSearchDot);
		MatrixBuffClear(TmpImage,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage,XLen,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)BmpImage ,XByte ,YLen,false);
		SkipSearchAreasData->AppeBottom.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);


		TmpInside.MoveToNoClip(0,-2*SkipSearchDot);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		SkipSearchAreasData->DisaUp.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(-SkipSearchDot,SkipSearchDot);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		SkipSearchAreasData->DisaLeft.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(2*SkipSearchDot,0);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		SkipSearchAreasData->DisaRight.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		TmpInside.MoveToNoClip(-SkipSearchDot,SkipSearchDot);
		MatrixBuffClear(TmpImage2,0,XByte,YLen,false);
		TmpInside.MakeBitData(TmpImage2,XLen,YLen,false);
		MatrixBuffCopy	(TmpImage,XByte,YLen ,(const BYTE **)BmpImage ,XByte,YLen,false);
		MatrixBuffNotAnd(TmpImage ,(const BYTE **)TmpImage2 ,XByte ,YLen,false);
		SkipSearchAreasData->DisaBottom.BuildFromRaster(TmpImage,XByte ,YLen,mx,my);

		if((BYTE	**)BmpImageBuff!=BmpImage){
			DeleteMatrixBuff(BmpImage,YLen);
		}
		if((BYTE	**)TmpImageBuff!=TmpImage){
			DeleteMatrixBuff(TmpImage,YLen);
		}
		if((BYTE	**)TmpImageBuff2!=TmpImage2){
			DeleteMatrixBuff(TmpImage2,YLen);
		}
	}
}
ExeResult	BlockItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ShiftX=0;
	ShiftY=0;
	return _ER_true;
}

ExeResult	BlockItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	if(GetID()==DbgID && GetPage()==DbgPage && GetLayer()==DbgLayer)
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
	const	BlockThreshold	*RThr=GetThresholdR();
	ExeResult	ret=ExecuteProcessingCalc(ThreadNo,Res,mx+ShiftX ,my+ShiftY);
	if(RThr->ThreshouldBag.PointMove.ModeSearchDetail==true){
		if(Res->IsOk()==false){
			int		OrgSelfSearch=RThr->ThreshouldBag.SelfSearch;
			if((OrgSelfSearch>=4) && (RThr->ThreshouldBag.PointMove.ModeSearchDetail==true)){
				for(int s=RThr->ThreshouldBag.SelfSearch-1;s>=4;s-=3){
					GetThresholdW()->ThreshouldBag.SelfSearch=s;
					Res->InitialInspection();
					ExecuteProcessingCalc(ThreadNo,Res,mx ,my);
					if(Res->IsOk()==true)
						break;
				}
				if(Res->IsOk()==false){
					for(int s=3;s>=1;s-=2){
						GetThresholdW()->ThreshouldBag.SelfSearch=s;
						Res->InitialInspection();
						ExecuteProcessingCalc(ThreadNo,Res,mx ,my);
						if(Res->IsOk()==true)
							break;
					}
				}
				GetThresholdW()->ThreshouldBag.SelfSearch=OrgSelfSearch;
				if(Res->IsOk()==false){
					ExecuteProcessingCalc(ThreadNo,Res,mx ,my);
				}
			}
		}
	}
	int	sx ,sy;
	Res->GetTotalShifted(sx ,sy);
	int	MinBrightness,MaxBrightness;
	GetArea().GetMinMaxBrightness(GetTargetBuff(),sx ,sy ,MinBrightness,MaxBrightness);

	GetThresholdW()->AddHist(Hist_BlockInspection_BBrightnessLow	,CenterTargetBright-MinBrightness);
	GetThresholdW()->AddHist(Hist_BlockInspection_BBrightnessHigh	,MaxBrightness-CenterTargetBright);
	GetThresholdW()->AddHist(Hist_BlockInspection_NBrightnessLow	,CenterTargetBright-MinBrightness);
	GetThresholdW()->AddHist(Hist_BlockInspection_NBrightnessHigh	,MaxBrightness-CenterTargetBright);

	if(RThr->ThreshouldBag.PointMove.ModeOnlyMatching==true){
		Res->SetError(1);
	}
	return ret;
}

bool	BlockItem::RewindDynamicMask(BlockInLayer *BL)
{
	if(BL!=NULL){
		if(BL->ExecutableContainer.IsLinkedToMask(this)==true){
			int	ShiftByAlignmentX,ShiftByAlignmentY;
			GetShiftByAlignemnt(ShiftByAlignmentX,ShiftByAlignmentY);
			int	sx,sy;
			GetCurrentResult()->GetTotalShifted(sx,sy);
			FLineBeforeShrink.MakeNotBitData(BL->DynamicMaskMap,BL->DynamicMaskMapXByte*8,BL->DynamicMaskMapYLen
											,sx,sy);
			return true;
		}
	}
	return false;
}
bool	BlockItem::SetDynamicMask(BlockInLayer *BL)
{
	if(BL!=NULL){
		if(BL->ExecutableContainer.IsLinkedToMask(this)==true){
			int	ShiftByAlignmentX,ShiftByAlignmentY;
			GetShiftByAlignemnt(ShiftByAlignmentX,ShiftByAlignmentY);
			int	sx,sy;
			GetCurrentResult()->GetTotalShifted(sx,sy);
			FLineBeforeShrink.MakeBitData(BL->DynamicMaskMap,sx,sy,BL->DynamicMaskMapXByte*8,BL->DynamicMaskMapYLen);
			return true;
		}
	}
	return false;
}
bool	BlockItem::UseMatchLine(void)
{
	const	BlockThreshold	*RThr=GetThresholdR();
	if(RThr->ThreshouldBag.PointMove.ModeMatchPosition==true
	|| RThr->ThreshouldBag.PointMove.ModeMatchPositionBW==true){
		if(FollowLineData!=NULL){
			if(FollowLineData->IsEffective()==true)
				return true;
		}
	}
	return false;
}
double	BlockItem::CalcMatch(int dx,int dy)
{
	int	mx,my;
	GetShiftByAlignemnt(mx,my);

	if(UseMatchLine()==true){
		return CalcMatchLinePosition(mx+dx,my+dy);
	}
	return 1.0;
}

void	BlockItem::GetShiftByAlignemnt(int &mx,int &my)
{
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
}

int		ExecutedCounter[100];

ExeResult	BlockItem::ExecuteProcessingCalc(int ThreadNo,ResultInItemRoot *Res ,int mx ,int my)
{
	if(GetID()==DbgID && GetPage()==DbgPage && GetLayer()==DbgLayer)
		DbgNumer++;

	BlockThreshold	*Thres=(BlockThreshold *)GetThresholdR();
	WORD	OKLengthL;
	WORD	OKLengthH;
	WORD	MinNGCountL;
	WORD	MinNGCountH;
	int8	ConnectLen;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	OKLengthL	=Thres->ThreshouldBag.BOKLengthL;
	OKLengthH	=Thres->ThreshouldBag.BOKLengthH;
	MinNGCountL	=Thres->ThreshouldBag.BMinNGCountL;
	MinNGCountH	=Thres->ThreshouldBag.BMinNGCountH;
	ConnectLen	=Thres->ThreshouldBag.BConnectLen;

	BlockInLayer	*P=(BlockInLayer *)GetParentInLayer();
	bool	ModeFixPos=false;
	bool	FixXDir=false;
	bool	FixYDir=false;
	BlockShiftList	BlockShiftListData;
	if(UseMatchLine()==true){
		ModeFixPos=ExeMatchLinePosition(mx,my,BlockShiftListData,FixXDir,FixYDir);
		int	n=BlockShiftListData.CurrentNumb;
		if(n>=MaxCountOfBlockShiftList)
			n=MaxCountOfBlockShiftList-1;
		BlockShiftListData.Dim[n].ShiftX=0;
		BlockShiftListData.Dim[n].ShiftY=0;
		BlockShiftListData.CurrentNumb=n+1;
	}
	if(BlockShiftListData.CurrentNumb==0){
		BlockShiftListData.Dim[0].ShiftX=0;
		BlockShiftListData.Dim[0].ShiftY=0;
		BlockShiftListData.CurrentNumb=1;
	}

	int BResultBrightWidthL=Thres->ThreshouldBag.BBrightWidthL;
	int	BResultBrightWidthH=Thres->ThreshouldBag.BBrightWidthH;
	int NResultBrightWidthL=Thres->ThreshouldBag.NBrightWidthL;
	int	NResultBrightWidthH=Thres->ThreshouldBag.NBrightWidthH;
	for(int t=0;t<BlockShiftListData.CurrentNumb;t++){
		Res->ClearPosList();
		int	LShiftX=BlockShiftListData.Dim[t].ShiftX;
		int	LShiftY=BlockShiftListData.Dim[t].ShiftY;

		int	BrightWidthL=Thres->ThreshouldBag.BBrightWidthL;
		int	BrightWidthH=Thres->ThreshouldBag.BBrightWidthH;

		Res->InitialInspection();
		if(P->NoBrightnessInMaster==true){
			BlockBase	*BBase=dynamic_cast<BlockBase *>(GetParentBase());
			if(BBase->UseTargetCenterInNoMaster==true){
				if(ModeFixPos==true && FixXDir==true && FixYDir==false){
					int	MinIC=9999999;
					for(int dy=-Thres->ThreshouldBag.SelfSearch;dy<=Thres->ThreshouldBag.SelfSearch;dy++){
						int	C=CalcCenterBright(GetTargetBuff(),mx+LShiftX,my+dy);
						int	ic=abs(CenterBright-C);
						if(ic<MinIC){
							CenterTargetBright=C;
							MinIC=ic;
							LShiftY=dy;
						}
					}
				}
				else if(ModeFixPos==true && FixXDir==false && FixYDir==true){
					int	MinIC=9999999;
					for(int dx=-Thres->ThreshouldBag.SelfSearch;dx<=Thres->ThreshouldBag.SelfSearch;dx++){
						int	C=CalcCenterBright(GetTargetBuff(),mx+dx,my+LShiftY);
						int	ic=abs(CenterBright-C);
						if(ic<MinIC){
							CenterTargetBright=C;
							MinIC=ic;
							LShiftX=dx;
						}
					}
				}
				else{
					CenterTargetBright=CalcCenterBright(GetTargetBuff(),mx+LShiftX,my+LShiftY);
				}
			}
		}
		WORD	DiffBrightWidthL=Thres->ThreshouldBag.DiffBrightWidthL;
		WORD	DiffBrightWidthH=Thres->ThreshouldBag.DiffBrightWidthH;
		if(Thres->ThreshouldBag.PointMove.ModeDiffer==false){
			if(GetMasterBuff().IsNull()==false){
				if(Thres->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
					BrightWidthL=CenterBright-BrightWidthL;
					BrightWidthH=CenterBright+BrightWidthH;
				}
			}
			else if(GetTargetBuff().IsNull()==false){
				if(Thres->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
					BrightWidthL=CenterTargetBright-BrightWidthL;
					BrightWidthH=CenterTargetBright+BrightWidthH;
				}
			}
		}
		else{
			if(Thres->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
				DiffBrightWidthL=CenterBright-DiffBrightWidthL;
				DiffBrightWidthH=CenterBright+DiffBrightWidthH;
			}
		}

		if(Res->GetAddedDataType()==1){
			if(Res->GetAddedData()!=NULL){
				BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
				if(Q!=NULL){
					Q->Error=0;
				}
			}
		}

		short	Error=1;

		bool	NGInBroad=false;
		bool	NGInNarrow=false;

		BResultBrightWidthL=BrightWidthL;
		BResultBrightWidthH=BrightWidthH;

		if(GetTargetBuff().IsNull()==false){
		    if(SubBlock.GetFirst()!=NULL){
				if(ExecuteProcessingInner(ThreadNo,Res
									  ,mx+LShiftX ,my+LShiftY
									  ,BrightWidthL ,BrightWidthH
									  ,BResultBrightWidthL,BResultBrightWidthH
									  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
									  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
									  ,OKLengthL,OKLengthH
									  ,MinNGCountL,MinNGCountH,ConnectLen
									  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
									  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
					Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
					if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
						Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶

						if(Res->GetAddedDataType()==1){
							if(Res->GetAddedData()!=NULL){
								BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
								if(Q!=NULL){
									Q->NGDotInBDark		=Res->GetResult1();
									Q->NGDotInBBright	=Res->GetResult2();
									Q->Error			=Res->GetError();
								}
							}
						}
						NGInBroad=true;
					}
				}
			}
			else if(Thres->ThreshouldBag.PointMove.ModeDiffer==false){
				if(UseMatchLine()==false || ModeFixPos==false){
					bool	hRet=ExecuteProcessingInnerWithoutSubtract(ThreadNo,Res
										  ,mx+LShiftX ,my+LShiftY
										  ,BrightWidthL ,BrightWidthH
										  ,BResultBrightWidthL,BResultBrightWidthH
										  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
										  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
					Thres->AddHist(Hist_BlockInspection_CenterBright	,((int)CenterTargetBright)-CenterBright);
					Thres->AddHist(Hist_BlockInspection_BDarkNGSize		,(int)Res->GetResult1());
					Thres->AddHist(Hist_BlockInspection_BLightNGSize	,(int)Res->GetResult2());
					Thres->AddHist(Hist_BlockInspection_X_Shift	,Saturation256(Res->GetItemSearchedX()));
					Thres->AddHist(Hist_BlockInspection_Y_Shift	,Saturation256(Res->GetItemSearchedY()));
					if(hRet==false){
						Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶
								
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInBDark		=Res->GetResult1();
										Q->NGDotInBBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInBroad=true;
						}
					}
					else if(hRet==true && GetInvertLogic()==true){
						Error=Res->GetError();
					}
				}
				else if(FixXDir==true && FixYDir==false){
					bool	hRet=ExecuteProcessingInnerWithoutSubtractFixX(ThreadNo,Res
										  ,mx+LShiftX ,my
										  ,BrightWidthL ,BrightWidthH
										  ,BResultBrightWidthL,BResultBrightWidthH
										  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
										  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
					Thres->AddHist(Hist_BlockInspection_CenterBright	,((int)CenterTargetBright)-CenterBright);
					Thres->AddHist(Hist_BlockInspection_BDarkNGSize		,(int)Res->GetResult1());
					Thres->AddHist(Hist_BlockInspection_BLightNGSize	,(int)Res->GetResult2());
					Thres->AddHist(Hist_BlockInspection_X_Shift	,Saturation256(Res->GetItemSearchedX()));
					Thres->AddHist(Hist_BlockInspection_Y_Shift	,Saturation256(Res->GetItemSearchedY()));
					if(hRet==false){
						Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶
								
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInBDark		=Res->GetResult1();
										Q->NGDotInBBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInBroad=true;
						}
					}
					else if(hRet==true && GetInvertLogic()==true){
						Error=Res->GetError();
					}
				}
				else if(FixXDir==false && FixYDir==true){
					bool	hRet=ExecuteProcessingInnerWithoutSubtractFixY(ThreadNo,Res
										  ,mx ,my+LShiftY
										  ,BrightWidthL ,BrightWidthH
										  ,BResultBrightWidthL,BResultBrightWidthH
										  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
										  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
					Thres->AddHist(Hist_BlockInspection_CenterBright	,((int)CenterTargetBright)-CenterBright);
					Thres->AddHist(Hist_BlockInspection_BDarkNGSize	,(int)Res->GetResult1());
					Thres->AddHist(Hist_BlockInspection_BLightNGSize	,(int)Res->GetResult2());
					Thres->AddHist(Hist_BlockInspection_X_Shift	,Saturation256(Res->GetItemSearchedX()));
					Thres->AddHist(Hist_BlockInspection_Y_Shift	,Saturation256(Res->GetItemSearchedY()));
					if(hRet==false){
						Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶
								
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInBDark		=Res->GetResult1();
										Q->NGDotInBBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInBroad=true;
						}
					}
					else if(hRet==true && GetInvertLogic()==true){
						Error=Res->GetError();
					}
				}
				else{
					bool	hRet=ExecuteProcessingInnerNoMove(ThreadNo,Res
										  ,mx ,my ,LShiftX ,LShiftY
										  ,BrightWidthL ,BrightWidthH
										  ,BResultBrightWidthL,BResultBrightWidthH
										  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
										  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
					Thres->AddHist(Hist_BlockInspection_CenterBright	,((int)CenterTargetBright)-CenterBright);
					Thres->AddHist(Hist_BlockInspection_BDarkNGSize	,(int)Res->GetResult1());
					Thres->AddHist(Hist_BlockInspection_BLightNGSize	,(int)Res->GetResult2());
					Thres->AddHist(Hist_BlockInspection_X_Shift	,Saturation256(Res->GetItemSearchedX()));
					Thres->AddHist(Hist_BlockInspection_Y_Shift	,Saturation256(Res->GetItemSearchedY()));
					if(hRet==false){
						Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶
								
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInBDark		=Res->GetResult1();
										Q->NGDotInBBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInBroad=true;
						}
					}
					else if(hRet==true && GetInvertLogic()==true){
						Error=Res->GetError();
					}
				}
			}
			else if(Thres->ThreshouldBag.PointMove.ModeDiffer==true){
				bool	hRet=ExecuteProcessingInnerDiffer(ThreadNo,Res
										  ,mx ,my
										  ,BrightWidthL ,BrightWidthH
										  ,BResultBrightWidthL,BResultBrightWidthH
										  ,Thres->ThreshouldBag.BOKDotL		,Thres->ThreshouldBag.BOKDotH
										  ,Thres->ThreshouldBag.BMaxNGDotL	,Thres->ThreshouldBag.BMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdBroad	,Thres->ThreshouldBag.PointMove.ModeBindBWBroad
										  ,DiffBrightWidthL,DiffBrightWidthH
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
					Thres->AddHist(Hist_BlockInspection_CenterBright	,((int)CenterTargetBright)-CenterBright);
					Thres->AddHist(Hist_BlockInspection_BDarkNGSize	,(int)Res->GetResult1());
					Thres->AddHist(Hist_BlockInspection_BLightNGSize	,(int)Res->GetResult2());
					Thres->AddHist(Hist_BlockInspection_X_Shift	,Saturation256(Res->GetItemSearchedX()));
					Thres->AddHist(Hist_BlockInspection_Y_Shift	,Saturation256(Res->GetItemSearchedY()));
					if(hRet==false){
						Error = 0x02 | (Res->GetError()&0xF0);	//?L?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(2 | (Res->GetError()&0xF0));	//?L?a?A?m?f?-?¶
								
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInBDark		=Res->GetResult1();
										Q->NGDotInBBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInBroad=true;
						}
					}
			}
		}
		if(NGInBroad==false || Thres->ThreshouldBag.PointMove.ModeCalcBothBN==true){
			if(Res->GetAddedDataType()==1){
				if(Res->GetAddedData()!=NULL){
					BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
					if(Q!=NULL){
						Q->NGDotInBDark		=Res->GetResult1();
						Q->NGDotInBBright	=Res->GetResult2();
						Q->Error			=Error;
					}
				}
			}

			BrightWidthL=Thres->ThreshouldBag.NBrightWidthL;
			BrightWidthH=Thres->ThreshouldBag.NBrightWidthH;
			OKLengthL	=Thres->ThreshouldBag.NOKLengthL;
			OKLengthH	=Thres->ThreshouldBag.NOKLengthH;
			MinNGCountL	=Thres->ThreshouldBag.NMinNGCountL;
			MinNGCountH	=Thres->ThreshouldBag.NMinNGCountH;
			ConnectLen	=Thres->ThreshouldBag.NConnectLen;

			if(Thres->ThreshouldBag.PointMove.ModeDiffer==false){
				if(GetMasterBuff().IsNull()==false){
					if(Thres->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
						BrightWidthL=CenterBright-BrightWidthL;
						BrightWidthH=CenterBright+BrightWidthH;
					}
				}
				else if(GetTargetBuff().IsNull()==false){
					if(Thres->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
						BrightWidthL=CenterTargetBright-BrightWidthL;
						BrightWidthH=CenterTargetBright+BrightWidthH;
					}
				}
			}

			NResultBrightWidthL	=BrightWidthL;
			NResultBrightWidthH	=BrightWidthH;
			
			if(GetTargetBuff().IsNull()==false){
			    if(SubBlock.GetFirst()!=NULL){
					if(ExecuteProcessingInner(ThreadNo,Res
										  ,mx+LShiftX ,my+LShiftY
										  ,BrightWidthL ,BrightWidthH
										  ,NResultBrightWidthL,NResultBrightWidthH
										  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
										  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
						Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶

							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInNDark		=Res->GetResult1();
										Q->NGDotInNBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInNarrow=true;
						}
					}
				}
				else if(Thres->ThreshouldBag.PointMove.ModeDiffer==false){
					if(UseMatchLine()==false || ModeFixPos==false){
						if(ExecuteProcessingInnerWithoutSubtract(ThreadNo,Res
											  ,mx+LShiftX ,my+LShiftY
											  ,BrightWidthL ,BrightWidthH
											  ,NResultBrightWidthL,NResultBrightWidthH
											  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
											  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
											  ,OKLengthL,OKLengthH
											  ,MinNGCountL,MinNGCountH,ConnectLen
											  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
											  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
							Thres->AddHist(Hist_BlockInspection_NDarkNGSize	,(int)Res->GetResult1());
							Thres->AddHist(Hist_BlockInspection_NLightNGSize	,(int)Res->GetResult2());
							Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
							if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
								Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶
								
								if(Res->GetAddedDataType()==1){
									if(Res->GetAddedData()!=NULL){
										BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
										if(Q!=NULL){
											Q->NGDotInNDark		=Res->GetResult1();
											Q->NGDotInNBright	=Res->GetResult2();
											Q->Error			=Res->GetError();
										}
									}
								}
								NGInNarrow=true;
							}
						}
					}
					else if(FixXDir==true && FixYDir==false){
						if(ExecuteProcessingInnerWithoutSubtractFixX(ThreadNo,Res
											  ,mx+LShiftX ,my
											  ,BrightWidthL ,BrightWidthH
											  ,NResultBrightWidthL,NResultBrightWidthH
											  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
											  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
											  ,OKLengthL,OKLengthH
											  ,MinNGCountL,MinNGCountH,ConnectLen
											  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
											  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
							Thres->AddHist(Hist_BlockInspection_NDarkNGSize	,(int)Res->GetResult1());
							Thres->AddHist(Hist_BlockInspection_NLightNGSize	,(int)Res->GetResult2());
							Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
							if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
								Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶
								
								if(Res->GetAddedDataType()==1){
									if(Res->GetAddedData()!=NULL){
										BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
										if(Q!=NULL){
											Q->NGDotInNDark		=Res->GetResult1();
											Q->NGDotInNBright	=Res->GetResult2();
											Q->Error			=Res->GetError();
										}
									}
								}
								NGInNarrow=true;
							}
						}
					}
					else if(FixXDir==false && FixYDir==true){
						if(ExecuteProcessingInnerWithoutSubtractFixY(ThreadNo,Res
											  ,mx ,my+LShiftY
											  ,BrightWidthL ,BrightWidthH
											  ,NResultBrightWidthL,NResultBrightWidthH
											  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
											  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
											  ,OKLengthL,OKLengthH
											  ,MinNGCountL,MinNGCountH,ConnectLen
											  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
											  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
							Thres->AddHist(Hist_BlockInspection_NDarkNGSize	,(int)Res->GetResult1());
							Thres->AddHist(Hist_BlockInspection_NLightNGSize	,(int)Res->GetResult2());
							Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
							if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
								Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶
								
								if(Res->GetAddedDataType()==1){
									if(Res->GetAddedData()!=NULL){
										BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
										if(Q!=NULL){
											Q->NGDotInNDark		=Res->GetResult1();
											Q->NGDotInNBright	=Res->GetResult2();
											Q->Error			=Res->GetError();
										}
									}
								}
								NGInNarrow=true;
							}
						}
					}
					else{
						if(ExecuteProcessingInnerNoMove(ThreadNo,Res
											  ,mx ,my ,LShiftX,LShiftY
											  ,BrightWidthL ,BrightWidthH
											  ,NResultBrightWidthL,NResultBrightWidthH
											  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
											  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
											  ,OKLengthL,OKLengthH
											  ,MinNGCountL,MinNGCountH,ConnectLen
											  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
											  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
							Thres->AddHist(Hist_BlockInspection_NDarkNGSize	,(int)Res->GetResult1());
							Thres->AddHist(Hist_BlockInspection_NLightNGSize	,(int)Res->GetResult2());
							Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
							if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
								Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶
								
								if(Res->GetAddedDataType()==1){
									if(Res->GetAddedData()!=NULL){
										BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
										if(Q!=NULL){
											Q->NGDotInNDark		=Res->GetResult1();
											Q->NGDotInNBright	=Res->GetResult2();
											Q->Error			=Res->GetError();
										}
									}
								}
								NGInNarrow=true;
							}
						}
					}
				}
				else if(Thres->ThreshouldBag.PointMove.ModeDiffer==true){
					if(ExecuteProcessingInnerDiffer(ThreadNo,Res
										  ,mx+LShiftX ,my+LShiftY
										  ,BrightWidthL ,BrightWidthH
										  ,NResultBrightWidthL,NResultBrightWidthH
										  ,Thres->ThreshouldBag.NOKDotL		,Thres->ThreshouldBag.NOKDotH
										  ,Thres->ThreshouldBag.NMaxNGDotL	,Thres->ThreshouldBag.NMaxNGDotH
										  ,OKLengthL,OKLengthH
										  ,MinNGCountL,MinNGCountH,ConnectLen
										  ,_ThresholdNarrow	,Thres->ThreshouldBag.PointMove.ModeBindBWNarrow
										  ,DiffBrightWidthL,DiffBrightWidthH
										  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen)==false){
						Thres->AddHist(Hist_BlockInspection_NDarkNGSize	,(int)Res->GetResult1());
						Thres->AddHist(Hist_BlockInspection_NLightNGSize	,(int)Res->GetResult2());
						Error = 0x03 | (Res->GetError()&0xF0);	//?・?a?A?m?f?-?¶
						if(Thres->ThreshouldBag.PointMove.ModeCalcBothBN==false){
							Res->SetError(3 | (Res->GetError()&0xF0));	//?・?a?A?m?f?-?¶
							
							if(Res->GetAddedDataType()==1){
								if(Res->GetAddedData()!=NULL){
									BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
									if(Q!=NULL){
										Q->NGDotInNDark		=Res->GetResult1();
										Q->NGDotInNBright	=Res->GetResult2();
										Q->Error			=Res->GetError();
									}
								}
							}
							NGInNarrow=true;
						}
					}
				}
			}
			if(Res->GetAddedDataType()==1){
				if(Res->GetAddedData()!=NULL){
					BlockSendTryThreshold	*Q=dynamic_cast<BlockSendTryThreshold *>(Res->GetAddedData());
					if(Q!=NULL){
						Q->NGDotInNDark		=Res->GetResult1();
						Q->NGDotInNBright	=Res->GetResult2();
						Q->Error			=Error;
					}
				}
			}
		}
		else{
			NResultBrightWidthL	=BResultBrightWidthL;
			NResultBrightWidthH	=BResultBrightWidthH;
		}
		Res->SetError(Error);
		if(NGInBroad==false && NGInNarrow==false){
			break;
		}
	}
	Res->SetResultByte(0,ClipByte(BResultBrightWidthL));
	Res->SetResultByte(1,ClipByte(BResultBrightWidthH));
	Res->SetResultByte(2,ClipByte(NResultBrightWidthL));
	Res->SetResultByte(3,ClipByte(NResultBrightWidthH));
	
	FinishCalc();
	return _ER_true;
}

bool	BlockItem::ExecuteProcessingSimple(int Mx ,int My)
{
	if(GetID()==DbgID && GetParent()->GetLayer()==DbgLayer)
		DbgNumer++;

	const	BlockThreshold	*RThr=GetThresholdR();
	int	BrightWidthL=RThr->ThreshouldBag.BBrightWidthL;
	int	BrightWidthH=RThr->ThreshouldBag.BBrightWidthH;
	WORD	OKLengthL;
	WORD	OKLengthH;
	WORD	MinNGCountL;
	WORD	MinNGCountH;
	int8	ConnectLen;

	if(CanBeProcessing()==false)
		return true;

	OKLengthL	=RThr->ThreshouldBag.BOKLengthL;
	OKLengthH	=RThr->ThreshouldBag.BOKLengthH;
	MinNGCountL	=RThr->ThreshouldBag.BMinNGCountL;
	MinNGCountH	=RThr->ThreshouldBag.BMinNGCountH;
	ConnectLen	=RThr->ThreshouldBag.BConnectLen;
	if(RThr->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
		BrightWidthL=CenterTargetBright-BrightWidthL;
		BrightWidthH=CenterTargetBright+BrightWidthH;
	}
	BlockInLayer	*P=(BlockInLayer *)GetParentInLayer();

	int	BResultBrightWidthL	=BrightWidthL;
	int	BResultBrightWidthH	=BrightWidthH;

	if(GetTargetBuff().IsNull()==false){
		bool	hRet=ExecuteProcessingSimpleWithoutSubtract(Mx ,My
								  ,BrightWidthL ,BrightWidthH
								  ,BResultBrightWidthL,BResultBrightWidthH
								  ,RThr->ThreshouldBag.BOKDotL		,RThr->ThreshouldBag.BOKDotH
								  ,RThr->ThreshouldBag.BMaxNGDotL	,RThr->ThreshouldBag.BMaxNGDotH
								  ,OKLengthL,OKLengthH
								  ,MinNGCountL,MinNGCountH,ConnectLen
								  ,_ThresholdBroad	,RThr->ThreshouldBag.PointMove.ModeBindBWBroad
								  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
		if(hRet==false){
			return false;
		}
	}

	BrightWidthL=RThr->ThreshouldBag.NBrightWidthL;
	BrightWidthH=RThr->ThreshouldBag.NBrightWidthH;
	OKLengthL	=RThr->ThreshouldBag.NOKLengthL;
	OKLengthH	=RThr->ThreshouldBag.NOKLengthH;
	MinNGCountL	=RThr->ThreshouldBag.NMinNGCountL;
	MinNGCountH	=RThr->ThreshouldBag.NMinNGCountH;
	ConnectLen	=RThr->ThreshouldBag.NConnectLen;
	if(RThr->ThreshouldBag.PointMove.ModeAbsoluteBright==false){
		BrightWidthL=CenterTargetBright-BrightWidthL;
		BrightWidthH=CenterTargetBright+BrightWidthH;
	}
	int	NResultBrightWidthL	=BrightWidthL;
	int	NResultBrightWidthH	=BrightWidthH;
	if(GetTargetBuff().IsNull()==false){
		bool	hRet=ExecuteProcessingSimpleWithoutSubtract(Mx ,My
								  ,BrightWidthL ,BrightWidthH
								  ,NResultBrightWidthL,NResultBrightWidthH
								  ,RThr->ThreshouldBag.NOKDotL		,RThr->ThreshouldBag.NOKDotH
								  ,RThr->ThreshouldBag.NMaxNGDotL	,RThr->ThreshouldBag.NMaxNGDotH
								  ,OKLengthL,OKLengthH
								  ,MinNGCountL,MinNGCountH,ConnectLen
								  ,_ThresholdNarrow	,RThr->ThreshouldBag.PointMove.ModeBindBWNarrow
								  ,P->DynamicMaskMap,P->DynamicMaskMapXByte,P->DynamicMaskMapYLen);
		if(hRet==false){
			return false;
		}
	}
	return true;
}
bool	BlockItem::IsModeDir4(void)
{
	if(AppeUp.IsNull()==true)
		return false;
	if(AppeLeft.IsNull()==true)
		return false;
	if(AppeRight.IsNull()==true)
		return false;
	if(AppeBottom.IsNull()==true)
		return false;
	if(DisaUp.IsNull()==true)
		return false;
	if(DisaLeft.IsNull()==true)
		return false;
	if(DisaRight.IsNull()==true)
		return false;
	if(DisaBottom.IsNull()==true)
		return false;
	return true;
}

bool	BlockItem::IsOnDynamicMasking(BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen
									,int mx,int my,int SelfSearch)
{
	int	x1=GetArea().GetMinX()+mx-SelfSearch-1;
	int	y1=GetArea().GetMinY()+mx-SelfSearch-1;
	int	x2=GetArea().GetMaxX()+mx+SelfSearch+1;
	int	y2=GetArea().GetMaxY()+mx+SelfSearch+1;
	if(HasBitInMatrixZone(DynamicMaskMap,DynamicMaskMapXByte,DynamicMaskMapYLen
						 ,x1,y1,x2,y2)==true)
		return true;
	return false;
}

void	BlockItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	BlockDrawAttr	*BAttr=dynamic_cast<BlockDrawAttr *>(Attr);
	if(BAttr!=NULL){
		BlockDrawAttr	TmpAttr;
		TmpAttr=*BAttr;
		//QColor	BuffColor=BAttr->NormalColor;
		switch(GetLibID()&7){
			case 0:	TmpAttr.NormalColor=BAttr->BlockColor0;	break;
			case 1:	TmpAttr.NormalColor=BAttr->BlockColor1;	break;
			case 2:	TmpAttr.NormalColor=BAttr->BlockColor2;	break;
			case 3:	TmpAttr.NormalColor=BAttr->BlockColor3;	break;
			case 4:	TmpAttr.NormalColor=BAttr->BlockColor4;	break;
			case 5:	TmpAttr.NormalColor=BAttr->BlockColor5;	break;
			case 6:	TmpAttr.NormalColor=BAttr->BlockColor6;	break;
			case 7:	TmpAttr.NormalColor=BAttr->BlockColor7;	break;
		}
		if(BAttr->DType==CmdBlockDrawModePacket::_Area)
			AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdBlockDrawModePacket::_Edge)
			AlgorithmItemPLI::DrawArea(FLineEdge,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdBlockDrawModePacket::_Inside)
			AlgorithmItemPLI::DrawArea(FLineInside,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		else if(BAttr->DType==CmdBlockDrawModePacket::_BeforeShrink)
			AlgorithmItemPLI::DrawArea(FLineBeforeShrink,pnt, movx ,movy ,ZoomRate ,&TmpAttr);
		//BAttr->NormalColor	=BuffColor;
		QRgb	AppeCol=qRgba(255,128,0,200);
		QRgb	DisaCol=qRgba(0,128,255,200);
		if(BAttr->DrawDirSkip==false){
			if(BAttr->DrawDirUp==true){
				AppeUp		.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				DisaUp		.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirLeft==true){
				AppeLeft	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				DisaLeft	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirRight==true){
				AppeRight	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				DisaRight	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirBottom==true){
				AppeBottom	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				DisaBottom	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
		}
		else if(SkipSearchAreasData!=NULL){
			if(BAttr->DrawDirUp==true){
				SkipSearchAreasData->AppeUp		.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				SkipSearchAreasData->DisaUp		.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirLeft==true){
				SkipSearchAreasData->AppeLeft	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				SkipSearchAreasData->DisaLeft	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirRight==true){
				SkipSearchAreasData->AppeRight	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				SkipSearchAreasData->DisaRight	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
			if(BAttr->DrawDirBottom==true){
				SkipSearchAreasData->AppeBottom	.DrawAlpha(0,0,&pnt,AppeCol,ZoomRate,movx,movy);
				SkipSearchAreasData->DisaBottom	.DrawAlpha(0,0,&pnt,DisaCol,ZoomRate,movx,movy);
			}
		}
		if(BAttr->DrawOmitMatchLineArea==true){
			QRgb	DMCol=qRgba(128,64,255,128);
			OmitMatchLineArea	.DrawAlpha(0,0,&pnt,DMCol,ZoomRate,movx,movy);
		}
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}

	QColor	LineColor;
	if(GetActive()==true)
		LineColor=Qt::red;
	else
		LineColor=Qt::darkRed;

	if(FollowLineData!=NULL){
		FollowLineData->Draw(pnt,movx,movy,ZoomRate,LineColor);
	}
}
void	BlockItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false && ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())
											+QString(/**/",")
											+QString::number((int)Res->GetTotalShiftedY())
											+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()==2){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"N: L=")+QString::number(Res->GetResult1()) 
												+QString(/**/" H=")
												+QString::number(Res->GetResult2())
							,&rect);
					}
					else if(Res->GetError()==3){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"B: L=")+QString::number(Res->GetResult1()) 
												+QString(/**/" H=")
												+QString::number(Res->GetResult2())
							,&rect);
					}
				}
			}
		}
	}
}

void	BlockItem::SetThresholdFromCommon(SetThresholdBlockInfo *Info)
{
	if(Info->AdjustL>=0)
		GetThresholdW()->ThreshouldBag.AdjustBlack	=Info->AdjustL;
	if(Info->AdjustH>=0)
		GetThresholdW()->ThreshouldBag.AdjustWhite	=Info->AdjustH;
	if(Info->BBrightL>=0)
		GetThresholdW()->ThreshouldBag.BBrightWidthL=Info->BBrightL;
	if(Info->BBrightH>=0)
		GetThresholdW()->ThreshouldBag.BBrightWidthH=Info->BBrightH;
	if(Info->NBrightL>=0)
		GetThresholdW()->ThreshouldBag.NBrightWidthL=Info->NBrightL;
	if(Info->NBrightH>=0)
		GetThresholdW()->ThreshouldBag.NBrightWidthH=Info->NBrightH;
	if(Info->NGSize1>=0)
		GetThresholdW()->ThreshouldBag.BOKDotL		=Info->NGSize1;
	if(Info->NGSize1>=0)
		GetThresholdW()->ThreshouldBag.BOKDotH		=Info->NGSize1;
	if(Info->NGSize2>=0)
		GetThresholdW()->ThreshouldBag.NOKDotL		=Info->NGSize2;
	if(Info->NGSize2>=0)
		GetThresholdW()->ThreshouldBag.NOKDotH		=Info->NGSize2;
	if(Info->Shift>=0)
		GetThresholdW()->ThreshouldBag.SelfSearch	=Info->Shift;
	if(Info->CenterBright>=0)
		GetThresholdW()->ThreshouldBag.RegularCenterBright	=Info->CenterBright;
}

void	BlockItem::MakeOmitArea(BYTE **OmitMap,int OmitMapXByte ,int OmitMapYLen)
{
	int	OmitMapXLen = OmitMapXByte<<3;
	int	XLen=FLineBeforeShrink.GetWidth()+2+16;
	int	XByte=(XLen+7)/8;
	int	YLen=FLineBeforeShrink.GetHeight()+20;
	BYTE	**TmpBuff =MakeMatrixBuff(XByte ,YLen);
	MatrixBuffClear(TmpBuff,0,XByte,YLen);
	int	dx=-FLineBeforeShrink.GetMinX()+8;
	int	dy=-FLineBeforeShrink.GetMinY()+8;
	FLineBeforeShrink.MakeBitData(TmpBuff,dx,dy,XLen,YLen);

	for(int y=0;y<YLen;y++){
		int	Y=y-dy;
		if(0<=Y && Y<OmitMapYLen){
			BYTE	*s=OmitMap[Y];
			BYTE	*d=TmpBuff[y];
			for(int x=0;x<XLen;x++){
				int	X=x-dx;
				if(0<=X && X<OmitMapXLen){
					if(GetBmpBitOnY(s,X)==0)
						SetBmpBitOnY0(d,x);
				}
			}
		}
	}
	OmitMatchLineArea.BuildFromRaster(TmpBuff ,XByte ,YLen ,-dx,-dy);
	DeleteMatrixBuff(TmpBuff,YLen);
}

void	BlockItem::SetAutoThreshold(ParamAutoThreshold &Param)
{
	if(Param.DirectThreshold==true){
		if(Param.HistID==Hist_BlockInspection_BLightNGSize)
			GetThresholdW()->ThreshouldBag.BOKDotH=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_BDarkNGSize)
			GetThresholdW()->ThreshouldBag.BOKDotL=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_NLightNGSize)
			GetThresholdW()->ThreshouldBag.NOKDotH=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_NDarkNGSize)
			GetThresholdW()->ThreshouldBag.NOKDotL=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_NBrightnessLow)
			GetThresholdW()->ThreshouldBag.NBrightWidthL	=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_NBrightnessHigh)
			GetThresholdW()->ThreshouldBag.NBrightWidthH	=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_BBrightnessLow)
			GetThresholdW()->ThreshouldBag.BBrightWidthL	=Param.ThresholdA;
		else
		if(Param.HistID==Hist_BlockInspection_BBrightnessHigh)
			GetThresholdW()->ThreshouldBag.BBrightWidthH	=Param.ThresholdA;
	}
}
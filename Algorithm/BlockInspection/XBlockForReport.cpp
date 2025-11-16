/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XBlockForReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "BlockFormResource.h"
#include "XBlockInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XBlockLibrary.h"
#include "XDataAlgorithm.h"

void	BlockLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("PickupL"		,PickupL);
	RetContainer.Add("PickupH"		,PickupH);
	RetContainer.Add("MinBlockSize"	,MinBlockSize);
	RetContainer.Add("MaxBlockSize"	,MaxBlockSize);
	RetContainer.Add("MinBlockDots"	,MinBlockDots);
	RetContainer.Add("MaxBlockDots"	,MaxBlockDots);
	RetContainer.Add("LimitBlockSize"	,LimitBlockSize);
	RetContainer.Add("RegularBrightness",RegularBrightness);

	RetContainer.Add("Transparent"	,(bool)GenerationMode.Transparent);
	RetContainer.Add("LeftPickup"	,(bool)GenerationMode.LeftPickup);
	RetContainer.Add("OverlappedGen",(bool)GenerationMode.OverlappedGen);

	if(GenerationCategory==_AutoSetting_PAD)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_PAD");
	else if(GenerationCategory==_AutoSetting_HOLE)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_HOLE");
	else if(GenerationCategory==_AutoSetting_SILK)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_SILK");
	else if(GenerationCategory==_AutoSetting_REGIST)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_REGIST");
	else if(GenerationCategory==_AutoSetting_OTHERMASK)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_OTHERMASK");
	else if(GenerationCategory==_AutoSetting_FINEPAD)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_FINEPAD");
	else if(GenerationCategory==_AutoSetting_SURROUND)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_SURROUND");
	else if(GenerationCategory==_AutoSetting_ANY)
		RetContainer.Add("GenerationCategory",(QString)"AutoSetting_ANY");

	RetContainer.Add("NoiseSize"		,NoiseSize);
	RetContainer.Add("NoiseSizePinHole"	,NoiseSizePinHole);
	RetContainer.Add("SpaceToOutline"	,SpaceToOutline);
	RetContainer.Add("Priority"			,Priority);

	RetContainer.Add("NBrightWidthL",NBrightWidthL);
	RetContainer.Add("NBrightWidthH",NBrightWidthH);
	RetContainer.Add("NOKDotL"		,NOKDotL);
	RetContainer.Add("NOKDotH"		,NOKDotH);
	RetContainer.Add("NOKLengthL"	,NOKLengthL);
	RetContainer.Add("NOKLengthH"	,NOKLengthH);
	RetContainer.Add("BBrightWidthL",BBrightWidthL);
	RetContainer.Add("BBrightWidthH",BBrightWidthH);
	RetContainer.Add("BOKDotL"		,BOKDotL);
	RetContainer.Add("BOKDotH"		,BOKDotH);
	RetContainer.Add("BOKLengthL"	,BOKLengthL);
	RetContainer.Add("BOKLengthH"	,BOKLengthH);
	RetContainer.Add("NMinNGCountL"	,NMinNGCountL);
	RetContainer.Add("NMinNGCountH"	,NMinNGCountH);
	RetContainer.Add("BMinNGCountL"	,BMinNGCountL);
	RetContainer.Add("BMinNGCountH"	,BMinNGCountH);
	RetContainer.Add("NConnectLen"	,NConnectLen);
	RetContainer.Add("BConnectLen"	,BConnectLen);

	RetContainer.Add("ModeEnabled"		,(bool)PointMove.ModeEnabled);
	RetContainer.Add("ModeAdjustable"	,(bool)PointMove.ModeAdjustable);
	RetContainer.Add("ModeAbsoluteBright",(bool)PointMove.ModeAbsoluteBright);
	RetContainer.Add("ModeCommonMovable",(bool)PointMove.ModeCommonMovable);
	RetContainer.Add("ModeNGCluster"	,(bool)PointMove.ModeNGCluster);
	RetContainer.Add("ModeDiffer"		,(bool)PointMove.ModeDiffer);
	RetContainer.Add("ModeCenterBrightFromParts",(bool)PointMove.ModeCenterBrightFromParts);
	RetContainer.Add("ModeOnlyMatching"	,(bool)PointMove.ModeOnlyMatching);
	RetContainer.Add("ModeWhiteMask"	,(bool)PointMove.ModeWhiteMask);
	RetContainer.Add("ModeBlackMask"	,(bool)PointMove.ModeBlackMask);
	RetContainer.Add("ModeInvertLogic"	,(bool)PointMove.ModeInvertLogic);
	RetContainer.Add("ModeMatchPosition",(bool)PointMove.ModeMatchPosition);
	RetContainer.Add("ModeSearchDetail"	,(bool)PointMove.ModeSearchDetail);

	RetContainer.Add("CommonMoveDot"	,CommonMoveDot);
	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
	RetContainer.Add("SelfSearch"		,SelfSearch);
}

void	BlockThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("NBrightWidthL",ThreshouldBag.NBrightWidthL);
	RetContainer.Add("NBrightWidthH",ThreshouldBag.NBrightWidthH);
	RetContainer.Add("NOKDotL"		,ThreshouldBag.NOKDotL);
	RetContainer.Add("NOKDotH"		,ThreshouldBag.NOKDotH);
	RetContainer.Add("NOKLengthL"	,ThreshouldBag.NOKLengthL);
	RetContainer.Add("NOKLengthH"	,ThreshouldBag.NOKLengthH);
	RetContainer.Add("BBrightWidthL",ThreshouldBag.BBrightWidthL);
	RetContainer.Add("BBrightWidthH",ThreshouldBag.BBrightWidthH);
	RetContainer.Add("BOKDotL"		,ThreshouldBag.BOKDotL);
	RetContainer.Add("BOKDotH"		,ThreshouldBag.BOKDotH);
	RetContainer.Add("BOKLengthL"	,ThreshouldBag.BOKLengthL);
	RetContainer.Add("BOKLengthH"	,ThreshouldBag.BOKLengthH);
	RetContainer.Add("NMinNGCountL"	,ThreshouldBag.NMinNGCountL);
	RetContainer.Add("NMinNGCountH"	,ThreshouldBag.NMinNGCountH);
	RetContainer.Add("BMinNGCountL"	,ThreshouldBag.BMinNGCountL);
	RetContainer.Add("BMinNGCountH"	,ThreshouldBag.BMinNGCountH);
	RetContainer.Add("NConnectLen"	,ThreshouldBag.NConnectLen);
	RetContainer.Add("BConnectLen"	,ThreshouldBag.BConnectLen);
	RetContainer.Add("RegularCenterBright",ThreshouldBag.RegularCenterBright);

	RetContainer.Add("ModeEnabled"			,(bool)ThreshouldBag.PointMove.ModeEnabled);
	RetContainer.Add("ModeAdjustable"		,(bool)ThreshouldBag.PointMove.ModeAdjustable);
	RetContainer.Add("ModeAbsoluteBright"	,(bool)ThreshouldBag.PointMove.ModeAbsoluteBright);
	RetContainer.Add("ModeCommonMovable"	,(bool)ThreshouldBag.PointMove.ModeCommonMovable);
	RetContainer.Add("ModeNGCluster"		,(bool)ThreshouldBag.PointMove.ModeNGCluster);
	RetContainer.Add("ModeDiffer"			,(bool)ThreshouldBag.PointMove.ModeDiffer);
	RetContainer.Add("ModeCenterBrightFromParts",(bool)ThreshouldBag.PointMove.ModeCenterBrightFromParts);
	RetContainer.Add("ModeOnlyMatching"		,(bool)ThreshouldBag.PointMove.ModeOnlyMatching);
	RetContainer.Add("ModeWhiteMask"		,(bool)ThreshouldBag.PointMove.ModeWhiteMask);
	RetContainer.Add("ModeBlackMask"		,(bool)ThreshouldBag.PointMove.ModeBlackMask);
	RetContainer.Add("ModeCalcBothBN"		,(bool)ThreshouldBag.PointMove.ModeCalcBothBN);
	RetContainer.Add("ModeInvertLogic"		,(bool)ThreshouldBag.PointMove.ModeInvertLogic);
	RetContainer.Add("ModeMatchPosition"	,(bool)ThreshouldBag.PointMove.ModeMatchPosition);
	RetContainer.Add("ModeSearchDetail"		,(bool)ThreshouldBag.PointMove.ModeSearchDetail);
	RetContainer.Add("ModeDynamicMask"		,(bool)ThreshouldBag.PointMove.ModeDynamicMask);
	RetContainer.Add("ModeBindBWBroad"		,(bool)ThreshouldBag.PointMove.ModeBindBWBroad);
	RetContainer.Add("ModeBindBWNarrow"		,(bool)ThreshouldBag.PointMove.ModeBindBWNarrow);
	RetContainer.Add("ModeAdoptBiggest"		,(bool)ThreshouldBag.PointMove.ModeAdoptBiggest);
	RetContainer.Add("ModeUseMasterImage"	,(bool)ThreshouldBag.PointMove.ModeUseMasterImage);
	RetContainer.Add("ModeUseRegularBrightness"	,(bool)ThreshouldBag.PointMove.ModeUseRegularBrightness);

	if(GetParentItem()->GetOriginType()==_OriginType_FromUnknown)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromUnknown");
	else if(GetParentItem()->GetOriginType()==_OriginType_FromLibrary)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromLibrary");
	else if(GetParentItem()->GetOriginType()==_OriginType_FromManual)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromManual");
	else if(GetParentItem()->GetOriginType()==_OriginType_FromParts)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromParts");
	else if(GetParentItem()->GetOriginType()==_OriginType_FromMPA)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromMPA");
	else if(GetParentItem()->GetOriginType()==_OriginType_FromCAD)
		RetContainer.Add("GeneratedOrigin"	,(QString)"FromCAD");

	RetContainer.Add("CommonMoveID"		,ThreshouldBag.CommonMoveID);
	RetContainer.Add("CommonMoveDot"	,ThreshouldBag.CommonMoveDot);
	RetContainer.Add("AdjustBlack"		,ThreshouldBag.AdjustBlack);
	RetContainer.Add("AdjustWhite"		,ThreshouldBag.AdjustWhite);
	RetContainer.Add("SelfSearch"		,ThreshouldBag.SelfSearch);
	RetContainer.Add("OmitVectorIndex"	,ThreshouldBag.OmitVectorIndex);
}

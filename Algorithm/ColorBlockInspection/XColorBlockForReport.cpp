/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorBlockInspection\XColorBlockForReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ColorBlockFormResource.h"
#include "XColorBlockInspection.h"
#include "XGeneralFunc.h"
#include "XColorBlockLibrary.h"

void	ColorBlockLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("PickupRL",PickupRL);
	RetContainer.Add("PickupRH",PickupRH);
	RetContainer.Add("PickupGL",PickupGL);
	RetContainer.Add("PickupGH",PickupGH);
	RetContainer.Add("PickupBL",PickupBL);
	RetContainer.Add("PickupBH",PickupBH);
	RetContainer.Add("MinBlockSize",MinBlockSize);
	RetContainer.Add("MaxBlockSize",MaxBlockSize);
	RetContainer.Add("MinBlockDots",MinBlockDots);
	RetContainer.Add("MaxBlockDots",MaxBlockDots);
	RetContainer.Add("LimitBlockSize",LimitBlockSize);

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

	RetContainer.Add("R.NBrightWidthL"	,InsR.NBrightWidthL);
	RetContainer.Add("R.NBrightWidthH"	,InsR.NBrightWidthH);
	RetContainer.Add("R.NOKDotL"		,InsR.NOKDotL);
	RetContainer.Add("R.NOKDotH"		,InsR.NOKDotH);
	RetContainer.Add("R.NOKLengthL"		,InsR.NOKLengthL);
	RetContainer.Add("R.NOKLengthH"		,InsR.NOKLengthH);
	RetContainer.Add("R.BBrightWidthL"	,InsR.BBrightWidthL);
	RetContainer.Add("R.BBrightWidthH"	,InsR.BBrightWidthH);
	RetContainer.Add("R.BOKDotL"		,InsR.BOKDotL);
	RetContainer.Add("R.BOKDotH"		,InsR.BOKDotH);
	RetContainer.Add("R.BOKLengthL"		,InsR.BOKLengthL);
	RetContainer.Add("R.BOKLengthH"		,InsR.BOKLengthH);
	RetContainer.Add("R.NMinNGCountL"	,InsR.NMinNGCountL);
	RetContainer.Add("R.NMinNGCountH"	,InsR.NMinNGCountH);
	RetContainer.Add("R.BMinNGCountL"	,InsR.BMinNGCountL);
	RetContainer.Add("R.BMinNGCountH"	,InsR.BMinNGCountH);
	RetContainer.Add("R.AdjustBlack"	,InsR.AdjustBlack);
	RetContainer.Add("R.AdjustWhite"	,InsR.AdjustWhite);

	RetContainer.Add("G.NBrightWidthL"	,InsG.NBrightWidthL);
	RetContainer.Add("G.NBrightWidthH"	,InsG.NBrightWidthH);
	RetContainer.Add("G.NOKDotL"		,InsG.NOKDotL);
	RetContainer.Add("G.NOKDotH"		,InsG.NOKDotH);
	RetContainer.Add("G.NOKLengthL"		,InsG.NOKLengthL);
	RetContainer.Add("G.NOKLengthH"		,InsG.NOKLengthH);
	RetContainer.Add("G.BBrightWidthL"	,InsG.BBrightWidthL);
	RetContainer.Add("G.BBrightWidthH"	,InsG.BBrightWidthH);
	RetContainer.Add("G.BOKDotL"		,InsG.BOKDotL);
	RetContainer.Add("G.BOKDotH"		,InsG.BOKDotH);
	RetContainer.Add("G.BOKLengthL"		,InsG.BOKLengthL);
	RetContainer.Add("G.BOKLengthH"		,InsG.BOKLengthH);
	RetContainer.Add("G.NMinNGCountL"	,InsG.NMinNGCountL);
	RetContainer.Add("G.NMinNGCountH"	,InsG.NMinNGCountH);
	RetContainer.Add("G.BMinNGCountL"	,InsG.BMinNGCountL);
	RetContainer.Add("G.BMinNGCountH"	,InsG.BMinNGCountH);
	RetContainer.Add("G.AdjustBlack"	,InsG.AdjustBlack);
	RetContainer.Add("G.AdjustWhite"	,InsG.AdjustWhite);

	RetContainer.Add("B.NBrightWidthL"	,InsB.NBrightWidthL);
	RetContainer.Add("B.NBrightWidthH"	,InsB.NBrightWidthH);
	RetContainer.Add("B.NOKDotL"		,InsB.NOKDotL);
	RetContainer.Add("B.NOKDotH"		,InsB.NOKDotH);
	RetContainer.Add("B.NOKLengthL"		,InsB.NOKLengthL);
	RetContainer.Add("B.NOKLengthH"		,InsB.NOKLengthH);
	RetContainer.Add("B.BBrightWidthL"	,InsB.BBrightWidthL);
	RetContainer.Add("B.BBrightWidthH"	,InsB.BBrightWidthH);
	RetContainer.Add("B.BOKDotL"		,InsB.BOKDotL);
	RetContainer.Add("B.BOKDotH"		,InsB.BOKDotH);
	RetContainer.Add("B.BOKLengthL"		,InsB.BOKLengthL);
	RetContainer.Add("B.BOKLengthH"		,InsB.BOKLengthH);
	RetContainer.Add("B.NMinNGCountL"	,InsB.NMinNGCountL);
	RetContainer.Add("B.NMinNGCountH"	,InsB.NMinNGCountH);
	RetContainer.Add("B.BMinNGCountL"	,InsB.BMinNGCountL);
	RetContainer.Add("B.BMinNGCountH"	,InsB.BMinNGCountH);
	RetContainer.Add("B.AdjustBlack"	,InsB.AdjustBlack);
	RetContainer.Add("B.AdjustWhite"	,InsB.AdjustWhite);

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

	RetContainer.Add("CommonMoveDot"	,CommonMoveDot);
	RetContainer.Add("SelfSearch"		,SelfSearch);
}

void	ColorBlockThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("R.NBrightWidthL"	,InsR.NBrightWidthL);
	RetContainer.Add("R.NBrightWidthH"	,InsR.NBrightWidthH);
	RetContainer.Add("R.NOKDotL"		,InsR.NOKDotL);
	RetContainer.Add("R.NOKDotH"		,InsR.NOKDotH);
	RetContainer.Add("R.NOKLengthL"		,InsR.NOKLengthL);
	RetContainer.Add("R.NOKLengthH"		,InsR.NOKLengthH);
	RetContainer.Add("R.BBrightWidthL"	,InsR.BBrightWidthL);
	RetContainer.Add("R.BBrightWidthH"	,InsR.BBrightWidthH);
	RetContainer.Add("R.BOKDotL"		,InsR.BOKDotL);
	RetContainer.Add("R.BOKDotH"		,InsR.BOKDotH);
	RetContainer.Add("R.BOKLengthL"		,InsR.BOKLengthL);
	RetContainer.Add("R.BOKLengthH"		,InsR.BOKLengthH);
	RetContainer.Add("R.NMinNGCountL"	,InsR.NMinNGCountL);
	RetContainer.Add("R.NMinNGCountH"	,InsR.NMinNGCountH);
	RetContainer.Add("R.BMinNGCountL"	,InsR.BMinNGCountL);
	RetContainer.Add("R.BMinNGCountH"	,InsR.BMinNGCountH);
	RetContainer.Add("R.AdjustBlack"	,InsR.AdjustBlack);
	RetContainer.Add("R.AdjustWhite"	,InsR.AdjustWhite);

	RetContainer.Add("G.NBrightWidthL"	,InsG.NBrightWidthL);
	RetContainer.Add("G.NBrightWidthH"	,InsG.NBrightWidthH);
	RetContainer.Add("G.NOKDotL"		,InsG.NOKDotL);
	RetContainer.Add("G.NOKDotH"		,InsG.NOKDotH);
	RetContainer.Add("G.NOKLengthL"		,InsG.NOKLengthL);
	RetContainer.Add("G.NOKLengthH"		,InsG.NOKLengthH);
	RetContainer.Add("G.BBrightWidthL"	,InsG.BBrightWidthL);
	RetContainer.Add("G.BBrightWidthH"	,InsG.BBrightWidthH);
	RetContainer.Add("G.BOKDotL"		,InsG.BOKDotL);
	RetContainer.Add("G.BOKDotH"		,InsG.BOKDotH);
	RetContainer.Add("G.BOKLengthL"		,InsG.BOKLengthL);
	RetContainer.Add("G.BOKLengthH"		,InsG.BOKLengthH);
	RetContainer.Add("G.NMinNGCountL"	,InsG.NMinNGCountL);
	RetContainer.Add("G.NMinNGCountH"	,InsG.NMinNGCountH);
	RetContainer.Add("G.BMinNGCountL"	,InsG.BMinNGCountL);
	RetContainer.Add("G.BMinNGCountH"	,InsG.BMinNGCountH);
	RetContainer.Add("G.AdjustBlack"	,InsG.AdjustBlack);
	RetContainer.Add("G.AdjustWhite"	,InsG.AdjustWhite);

	RetContainer.Add("B.NBrightWidthL"	,InsB.NBrightWidthL);
	RetContainer.Add("B.NBrightWidthH"	,InsB.NBrightWidthH);
	RetContainer.Add("B.NOKDotL"		,InsB.NOKDotL);
	RetContainer.Add("B.NOKDotH"		,InsB.NOKDotH);
	RetContainer.Add("B.NOKLengthL"		,InsB.NOKLengthL);
	RetContainer.Add("B.NOKLengthH"		,InsB.NOKLengthH);
	RetContainer.Add("B.BBrightWidthL"	,InsB.BBrightWidthL);
	RetContainer.Add("B.BBrightWidthH"	,InsB.BBrightWidthH);
	RetContainer.Add("B.BOKDotL"		,InsB.BOKDotL);
	RetContainer.Add("B.BOKDotH"		,InsB.BOKDotH);
	RetContainer.Add("B.BOKLengthL"		,InsB.BOKLengthL);
	RetContainer.Add("B.BOKLengthH"		,InsB.BOKLengthH);
	RetContainer.Add("B.NMinNGCountL"	,InsB.NMinNGCountL);
	RetContainer.Add("B.NMinNGCountH"	,InsB.NMinNGCountH);
	RetContainer.Add("B.BMinNGCountL"	,InsB.BMinNGCountL);
	RetContainer.Add("B.BMinNGCountH"	,InsB.BMinNGCountH);
	RetContainer.Add("B.AdjustBlack"	,InsB.AdjustBlack);
	RetContainer.Add("B.AdjustWhite"	,InsB.AdjustWhite);

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
	RetContainer.Add("ModeCalcBothBN"	,(bool)PointMove.ModeCalcBothBN);

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

	RetContainer.Add("CommonMoveID"		,CommonMoveID);
	RetContainer.Add("CommonMoveDot"	,CommonMoveDot);
	RetContainer.Add("SelfSearch"		,SelfSearch);
	RetContainer.Add("OmitVectorIndex"	,OmitVectorIndex);
}

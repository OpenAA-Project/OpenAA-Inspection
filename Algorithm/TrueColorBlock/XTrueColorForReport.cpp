/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\TrueColorBlock\XTrueColorBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTrueColorBlockResource.h"
#include "XTrueColorBlock.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XTrueColorBlockLibrary.h"

void	TrueColorBlockLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
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


	RetContainer.Add("NOKDotL"		,NOKDot);
	RetContainer.Add("NOKLengthL"	,NOKLength);
	RetContainer.Add("BOKDotL"		,BOKDot);
	RetContainer.Add("BOKLengthL"	,BOKLength);
	RetContainer.Add("NMinNGCountL"	,NMinNGCount);
	RetContainer.Add("BMinNGCountL"	,BMinNGCount);

	RetContainer.Add("NMergin"		,NMergin);
	RetContainer.Add("BMergin"		,BMergin);

	RetContainer.Add("ModeEnabled"		,PointMove.ModeEnabled);
	RetContainer.Add("ModeAdjustable"	,PointMove.ModeAdjustable);
	RetContainer.Add("ModeCommonMovable",PointMove.ModeCommonMovable);
	RetContainer.Add("ModeNGCluster"	,PointMove.ModeNGCluster);
	RetContainer.Add("ModeCenterBrightFromParts",PointMove.ModeCenterBrightFromParts);
	RetContainer.Add("ModeOnlyMatching"	,PointMove.ModeOnlyMatching);

	RetContainer.Add("CommonMoveDot"	,CommonMoveDot);
	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
	RetContainer.Add("SelfSearch"		,SelfSearch);
}

void	TrueColorBlockThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("NOKDotL"		,NOKDot);
	RetContainer.Add("NOKLengthL"	,NOKLength);
	RetContainer.Add("BOKDotL"		,BOKDot);
	RetContainer.Add("BOKLengthL"	,BOKLength);
	RetContainer.Add("NMinNGCountL"	,NMinNGCount);
	RetContainer.Add("BMinNGCountL"	,BMinNGCount);

	RetContainer.Add("NMergin"	,NMergin);
	RetContainer.Add("BMergin"	,BMergin);

	RetContainer.Add("ModeEnabled"		,(bool)PointMove.ModeEnabled);
	RetContainer.Add("ModeAdjustable"	,(bool)PointMove.ModeAdjustable);
	RetContainer.Add("ModeCommonMovable",(bool)PointMove.ModeCommonMovable);
	RetContainer.Add("ModeNGCluster"	,(bool)PointMove.ModeNGCluster);
	RetContainer.Add("ModeCenterBrightFromParts",(bool)PointMove.ModeCenterBrightFromParts);
	RetContainer.Add("ModeOnlyMatching"	,(bool)PointMove.ModeOnlyMatching);
	RetContainer.Add("ModeCalcBothBN"	,(bool)PointMove.ModeCalcBothBN);
	RetContainer.Add("ModeInvertLogic"	,(bool)PointMove.ModeInvertLogic);

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
	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
	RetContainer.Add("SelfSearch"		,SelfSearch);
	RetContainer.Add("OmitVectorIndex"	,OmitVectorIndex);
}

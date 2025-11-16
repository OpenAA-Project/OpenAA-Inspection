/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\EulerRingL1L\XEulerRingL1LReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "EulerRingL1Resource.h"
#include "XEulerRingL1.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XEulerRingL1Library.h"


void	EulerRingL1Library::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("LockFirst"	,LockFirst);
	RetContainer.Add("PickupL"		,PickupL);
	RetContainer.Add("PickupH"		,PickupH);
	RetContainer.Add("MinBlockSize",MinBlockSize);
	RetContainer.Add("MaxBlockSize",MaxBlockSize);
	RetContainer.Add("MinBlockDots",MinBlockDots);
	RetContainer.Add("MaxBlockDots",MaxBlockDots);

	RetContainer.Add("NoiseSize"		,NoiseSize);
	RetContainer.Add("NoiseSizePinHole"	,NoiseSizePinHole);
	RetContainer.Add("SpaceToOutline"	,SpaceToOutline);
	RetContainer.Add("Priority"			,Priority);
	RetContainer.Add("OutlineGeneration",OutlineGeneration);
	RetContainer.Add("ExpandedDotToPad"	,ExpandedDotToPad);


	RetContainer.Add("StandardHoleDiameter"	,StandardHoleDiameter);
	RetContainer.Add("MerginForRing"		,MerginForRing);

	RetContainer.Add("ModeEnabled"			,(bool)PointMove.ModeEnabled);
	RetContainer.Add("ModeAbsoluteBright"	,(bool)PointMove.ModeAbsoluteBright);
	RetContainer.Add("ModeMakeDynamicMask"	,(bool)PointMove.ModeMakeDynamicMask);
	RetContainer.Add("ModeEnableHoleCheck"	,(bool)PointMove.ModeEnableHoleCheck);
	RetContainer.Add("ModeCenterBrightFromParts",(bool)PointMove.ModeCenterBrightFromParts);

	RetContainer.Add("DarkWidth"			,DarkWidth);
	RetContainer.Add("LightWidth"			,LightWidth);
	RetContainer.Add("MinHoleDiameter"		,MinHoleDiameter);
	RetContainer.Add("MaxHoleDiameter"		,MaxHoleDiameter);
	RetContainer.Add("MaxShiftHole"			,MaxShiftHole);
	RetContainer.Add("ConnectLen"			,ConnectLen);
	RetContainer.Add("ExpandForDynamicMask"	,ExpandForDynamicMask);

	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
}

void	EulerRingL1Threshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ModeEnabled"			,(bool)PointMove.ModeEnabled);
	RetContainer.Add("ModeAbsoluteBright"	,(bool)PointMove.ModeAbsoluteBright);
	RetContainer.Add("ModeMakeDynamicMask"	,(bool)PointMove.ModeMakeDynamicMask);
	RetContainer.Add("ModeEnableHoleCheck"	,(bool)PointMove.ModeEnableHoleCheck);
	RetContainer.Add("ModeCenterBrightFromParts",(bool)PointMove.ModeCenterBrightFromParts);

	RetContainer.Add("DarkWidth"			,DarkWidth);
	RetContainer.Add("LightWidth"			,LightWidth);
	RetContainer.Add("MinHoleDiameter"		,MinHoleDiameter);
	RetContainer.Add("MaxHoleDiameter"		,MaxHoleDiameter);
	RetContainer.Add("MaxShiftHole"			,MaxShiftHole);
	RetContainer.Add("ConnectLen"			,ConnectLen);
	RetContainer.Add("ExpandForDynamicMask"	,ExpandForDynamicMask);

	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
}

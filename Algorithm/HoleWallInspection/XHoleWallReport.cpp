/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\HoleWallInspection\XHoleWallLReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XHoleWallInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XHoleWallLibrary.h"


void	HoleWallLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("PickupL"		,PickupL);
	RetContainer.Add("PickupH"		,PickupH);
	RetContainer.Add("MinBlockSize",MinBlockSize);
	RetContainer.Add("MaxBlockSize",MaxBlockSize);
	RetContainer.Add("MinBlockDots",MinBlockDots);
	RetContainer.Add("MaxBlockDots",MaxBlockDots);

	RetContainer.Add("NoiseSize"		,NoiseSize);
	RetContainer.Add("NoiseSizePinHole"	,NoiseSizePinHole);
	RetContainer.Add("SpaceToOutline"	,SpaceToOutline);

	RetContainer.Add("NGSize"				,NGSize);
	RetContainer.Add("SearchDot"			,SearchDot);
}

void	HoleWallThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("NGSize"				,NGSize);
	RetContainer.Add("SearchDot"			,SearchDot);
}

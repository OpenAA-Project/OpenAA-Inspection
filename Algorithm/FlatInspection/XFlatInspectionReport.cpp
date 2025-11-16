//#include "FlatInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\FlatInspection\XFlatInspectionReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XFlatInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XFlatInspectionLibrary.h"
#include "XDataAlgorithm.h"

void	FlatInspectionLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("PickupRL"		,PickupRL);
	RetContainer.Add("PickupRH"		,PickupRH);
	RetContainer.Add("PickupGL"		,PickupGL);
	RetContainer.Add("PickupGH"		,PickupGH);
	RetContainer.Add("PickupBL"		,PickupBL);
	RetContainer.Add("PickupBH"		,PickupBH);
	RetContainer.Add("MinFlatInspectionSize"		,MinFlatInspectionSize);
	RetContainer.Add("MaxFlatInspectionSize"		,MaxFlatInspectionSize);
	RetContainer.Add("MinFlatInspectionDots"		,MinFlatInspectionDots);
	RetContainer.Add("MaxFlatInspectionDots"		,MaxFlatInspectionDots);
	RetContainer.Add("LimitFlatInspectionSize"		,LimitFlatInspectionSize);


	RetContainer.Add("NoiseSize"			,NoiseSize);
	RetContainer.Add("NoiseSizePinHole"		,NoiseSizePinHole);
	RetContainer.Add("SpaceToOutline"		,SpaceToOutline);
	RetContainer.Add("UseBackGround"		,UseBackGround);


	RetContainer.Add("OKDotB"			,Broad.OKDot);
	RetContainer.Add("OKLengthB"		,Broad.OKLength);
	RetContainer.Add("RThrOffsetBL"		,Broad.RThrOffsetL);
	RetContainer.Add("RThrOffsetBH"		,Broad.RThrOffsetH);
	RetContainer.Add("GThrOffsetBL"		,Broad.GThrOffsetL);
	RetContainer.Add("GThrOffsetBH"		,Broad.GThrOffsetH);
	RetContainer.Add("BThrOffsetBL"		,Broad.BThrOffsetL);
	RetContainer.Add("BThrOffsetBH"		,Broad.BThrOffsetH);

	RetContainer.Add("OKDotN"			,Narrow.OKDot);
	RetContainer.Add("OKLengthN"		,Narrow.OKLength);
	RetContainer.Add("RThrOffsetNL"		,Narrow.RThrOffsetL);
	RetContainer.Add("RThrOffsetNH"		,Narrow.RThrOffsetH);
	RetContainer.Add("GThrOffsetNL"		,Narrow.GThrOffsetL);
	RetContainer.Add("GThrOffsetNH"		,Narrow.GThrOffsetH);
	RetContainer.Add("BThrOffsetNL"		,Narrow.BThrOffsetL);
	RetContainer.Add("BThrOffsetNH"		,Narrow.BThrOffsetH);

	RetContainer.Add("MultiSpotDot"		,MultiSpotDot);
	RetContainer.Add("MultiSpotCount"	,MultiSpotCount);
	RetContainer.Add("MultiSpotDotGathered"		,MultiSpotDotGathered);
	RetContainer.Add("MultiSpotCountGathered"	,MultiSpotCountGathered);
	RetContainer.Add("MultiSpotLengthGathered"	,MultiSpotLengthGathered);
	RetContainer.Add("BackGroundOKDot"	,BackGroundOKDot);
	RetContainer.Add("BackGroundOKLength",BackGroundOKLength);
	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
	RetContainer.Add("AreaSearchX"		,AreaSearchX);
	RetContainer.Add("AreaSearchY"		,AreaSearchY);
	RetContainer.Add("SelfSearch"		,SelfSearch);

	RetContainer.Add("RedCheckMode"			,RedCheckMode);
	RetContainer.Add("RedHighRate"			,RedHighRate);
	RetContainer.Add("RedMinBrightness"		,RedMinBrightness);
	RetContainer.Add("RedGBMerginRate"		,RedGBMerginRate);
	RetContainer.Add("RedGBMerginOffset"	,RedGBMerginOffset);
	RetContainer.Add("RedShrink"			,RedShrink);
	RetContainer.Add("RedOKDot"				,RedOKDot);
}

void	FlatInspectionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("OKDotB"			,Broad.OKDot);
	RetContainer.Add("OKLengthB"		,Broad.OKLength);
	RetContainer.Add("RThrOffsetBL"		,Broad.RThrOffsetL);
	RetContainer.Add("RThrOffsetBH"		,Broad.RThrOffsetH);
	RetContainer.Add("GThrOffsetBL"		,Broad.GThrOffsetL);
	RetContainer.Add("GThrOffsetBH"		,Broad.GThrOffsetH);
	RetContainer.Add("BThrOffsetBL"		,Broad.BThrOffsetL);
	RetContainer.Add("BThrOffsetBH"		,Broad.BThrOffsetH);

	RetContainer.Add("OKDotN"			,Narrow.OKDot);
	RetContainer.Add("OKLengthN"		,Narrow.OKLength);
	RetContainer.Add("RThrOffsetNL"		,Narrow.RThrOffsetL);
	RetContainer.Add("RThrOffsetNH"		,Narrow.RThrOffsetH);
	RetContainer.Add("GThrOffsetNL"		,Narrow.GThrOffsetL);
	RetContainer.Add("GThrOffsetNH"		,Narrow.GThrOffsetH);
	RetContainer.Add("BThrOffsetNL"		,Narrow.BThrOffsetL);
	RetContainer.Add("BThrOffsetNH"		,Narrow.BThrOffsetH);

	RetContainer.Add("SpaceToOutline"	,SpaceToOutline);

	RetContainer.Add("MultiSpotDot"		,MultiSpotDot);
	RetContainer.Add("MultiSpotCount"	,MultiSpotCount);
	RetContainer.Add("MultiSpotDotGathered"		,MultiSpotDotGathered);
	RetContainer.Add("MultiSpotCountGathered"	,MultiSpotCountGathered);
	RetContainer.Add("MultiSpotLengthGathered"	,MultiSpotLengthGathered);
	RetContainer.Add("BackGroundOKDot"	,BackGroundOKDot);
	RetContainer.Add("BackGroundOKLength",BackGroundOKLength);
	RetContainer.Add("UseBackGround"	,UseBackGround);

	RetContainer.Add("AdjustBlack"		,AdjustBlack);
	RetContainer.Add("AdjustWhite"		,AdjustWhite);
	RetContainer.Add("AreaSearchX"		,AreaSearchX);
	RetContainer.Add("AreaSearchY"		,AreaSearchY);
	RetContainer.Add("SelfSearch"		,SelfSearch);

	RetContainer.Add("RedCheckMode"			,RedCheckMode);
	RetContainer.Add("RedHighRate"			,RedHighRate);
	RetContainer.Add("RedMinBrightness"		,RedMinBrightness);
	RetContainer.Add("RedGBMerginRate"		,RedGBMerginRate);
	RetContainer.Add("RedGBMerginOffset"	,RedGBMerginOffset);
	RetContainer.Add("RedShrink"			,RedShrink);
	RetContainer.Add("RedOKDot"				,RedOKDot);

}

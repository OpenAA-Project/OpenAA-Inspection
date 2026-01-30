/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//#include "FlatInspectionResource.h"

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
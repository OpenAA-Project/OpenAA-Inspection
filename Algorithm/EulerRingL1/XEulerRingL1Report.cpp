/*
 * Copyright (C) 2023
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
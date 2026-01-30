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
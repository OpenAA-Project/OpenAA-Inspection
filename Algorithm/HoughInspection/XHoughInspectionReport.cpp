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

#include "XHoughInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"


void	HoughLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ZoneWidth"			,ZoneWidth		);
	RetContainer.Add("MaxIsolation"			,MaxIsolation		);
	RetContainer.Add("MinPixels"			,MinPixels			);
	RetContainer.Add("NGLength"				,NGLength	);
	RetContainer.Add("BinarizedLength"		,BinarizedLength	);
	RetContainer.Add("PickupL"				,PickupL	);
	RetContainer.Add("PickupH"				,PickupH	);
	RetContainer.Add("RemoveDynamicMask"	,RemoveDynamicMask	);
	RetContainer.Add("ReducedSize"			,ReducedSize	);
	RetContainer.Add("MaxLineCount"			,MaxLineCount	);
	RetContainer.Add("MinNGWidth"			,MinNGWidth	);
	RetContainer.Add("MaxNGWidth"			,MaxNGWidth	);
	RetContainer.Add("MinAverageContinuous"	,MinAverageContinuous	);
	RetContainer.Add("DynamicBinarize"		,DynamicBinarize	);
}

void	HoughThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ZoneWidth"			,ZoneWidth		);
	RetContainer.Add("MaxIsolation"			,MaxIsolation		);
	RetContainer.Add("MinPixels"			,MinPixels			);
	RetContainer.Add("NGLength"				,NGLength	);
	RetContainer.Add("BinarizedLength"		,BinarizedLength	);
	RetContainer.Add("PickupL"				,PickupL	);
	RetContainer.Add("PickupH"				,PickupH	);
	RetContainer.Add("RemoveDynamicMask"	,RemoveDynamicMask	);
	RetContainer.Add("ReducedSize"			,ReducedSize	);
	RetContainer.Add("MaxLineCount"			,MaxLineCount	);
	RetContainer.Add("MinNGWidth"			,MinNGWidth	);
	RetContainer.Add("MaxNGWidth"			,MaxNGWidth	);
	RetContainer.Add("MinAverageContinuous"	,MinAverageContinuous	);
	RetContainer.Add("DynamicBinarize"		,DynamicBinarize	);
}
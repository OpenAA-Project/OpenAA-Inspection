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

#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XMeasureLineMove.h"
#include "XDataAlgorithm.h"


void	MeasureLineMoveLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"			,SearchDot);
	RetContainer.Add("ThresholdM"			,ThresholdM);
	RetContainer.Add("ThresholdP"			,ThresholdP);
	RetContainer.Add("EdgeWidth"			,EdgeWidth);
	RetContainer.Add("PrevailRight"			,PrevailRight);
	RetContainer.Add("PrevailLeft"			,PrevailLeft);
	RetContainer.Add("UsageLayer"			,UsageLayer);
	RetContainer.Add("ModeToSetInInitial"	,ModeToSetInInitial);
	RetContainer.Add("OKRangeInInitial"		,OKRangeInInitial);
	RetContainer.Add("OutputType"			,OutputType);
	RetContainer.Add("SearchType"			,SearchType);
	RetContainer.Add("ThresholdRate"		,ThresholdRate);
}

void	MeasureLineMoveThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDot"			,SearchDot);
	RetContainer.Add("ThresholdM"			,ThresholdM);
	RetContainer.Add("ThresholdP"			,ThresholdP);
	RetContainer.Add("EdgeWidth"			,EdgeWidth);
	RetContainer.Add("PrevailRight"			,PrevailRight);
	RetContainer.Add("PrevailLeft"			,PrevailLeft);
	RetContainer.Add("UsageLayer"			,UsageLayer);
	RetContainer.Add("ModeToSetInInitial"	,ModeToSetInInitial);
	RetContainer.Add("OKRangeInInitial"		,OKRangeInInitial);
	RetContainer.Add("OutputType"			,OutputType);
	RetContainer.Add("SearchType"			,SearchType);
	RetContainer.Add("ThresholdRate"		,ThresholdRate);

	RetContainer.Add("BrightnessIdealRight"	,BrightnessIdealRight);
	RetContainer.Add("BrightnessIdealLeft"	,BrightnessIdealLeft);
}

/*
 * Copyright (C) 2024
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


#include "XShiftMark.h"
#include "XShiftMarkLibrary.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDataAlgorithm.h"

void	ShiftMarkLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDotEdge"	,SearchDotEdge);
	RetContainer.Add("SearchDotMarkMin"	,SearchDotMarkMin);
	RetContainer.Add("SearchDotMarkMax"	,SearchDotMarkMax);
	RetContainer.Add("NGByLosingMark"	,NGByLosingMark);
	RetContainer.Add("ThresholdLost"	,ThresholdLost);
}

void	ShiftMarkThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchDotEdge"	,SearchDotEdge);
	RetContainer.Add("SearchDotMarkMin"	,SearchDotMarkMin);
	RetContainer.Add("SearchDotMarkMax"	,SearchDotMarkMax);
	RetContainer.Add("NGByLosingMark"	,NGByLosingMark);
	RetContainer.Add("ThresholdLost"	,ThresholdLost);
}
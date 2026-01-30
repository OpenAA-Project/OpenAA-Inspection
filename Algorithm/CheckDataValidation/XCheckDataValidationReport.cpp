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


#include "XCheckDataValidation.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDataAlgorithm.h"

void	CheckDataValidationExistItemAreaThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("LibType"	,LibType);
	RetContainer.Add("LibID"	,LibID);
	RetContainer.Add("FilledPercentageInMask"	,FilledPercentageInMask);
	RetContainer.Add("CheckExistence"			,CheckExistence);
}

void	CheckDataValidationExistItemVectorThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("LibType"	,LibType);
	RetContainer.Add("LibID"	,LibID);
}

void	CheckDataValidationCheckMinMaxThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("LibType"	,LibType);
	RetContainer.Add("LibID"	,LibID);
	RetContainer.Add("ParamID"	,ParamID);
	//RetContainer.Add("MinValue"	,MinValue);
	//RetContainer.Add("MaxValue"	,MaxValue);
}

void	CheckDataValidationProhibiteItemThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("LibType"	,LibType);
	RetContainer.Add("LibID"	,LibID);
}
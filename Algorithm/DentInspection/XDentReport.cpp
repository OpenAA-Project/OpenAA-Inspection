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



//#include "DentResource.h"
#include "XDentInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDentLibrary.h"


void	DentLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("Difference"		,Difference		);
	RetContainer.Add("BandWidth"		,BandWidth		);
	RetContainer.Add("MinNGSize"		,MinNGSize		);
	RetContainer.Add("MaxNGSize"		,MaxNGSize		);
	RetContainer.Add("MaxDiffCoef"		,MaxDiffCoef	);
	RetContainer.Add("LinesForAverage"	,LinesForAverage);
}

void	DentThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("Difference"		,Difference		);
	RetContainer.Add("BandWidth"		,BandWidth		);
	RetContainer.Add("MinNGSize"		,MinNGSize		);
	RetContainer.Add("MaxNGSize"		,MaxNGSize		);
	RetContainer.Add("MaxDiffCoef"		,MaxDiffCoef	);
	RetContainer.Add("LinesForAverage"	,LinesForAverage);
}
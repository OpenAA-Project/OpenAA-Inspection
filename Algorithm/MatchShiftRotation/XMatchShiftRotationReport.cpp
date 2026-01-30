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

#include "XMatchShiftRotation.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XMatchShiftRotationLibrary.h"

void	MatchShiftRotationBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		MatchShiftRotationInPage	*Pg=(MatchShiftRotationInPage *)GetPageData(page);

		int	N=Pg->GetMatchShiftRotationCount();
			
		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(N));
		RetContainer.AppendList(r);
	}
}


void	MatchShiftRotationLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchArea"			,SearchArea);
	RetContainer.Add("SearchAngle"			,SearchAngle);
	RetContainer.Add("SearchLittleInItem"	,SearchLittleInItem);
	RetContainer.Add("MatchingRate"			,MatchingRate);
}

void	MatchShiftRotationThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("SearchLittleInItem"	,SearchLittleInItem);
	RetContainer.Add("MatchingRate"			,MatchingRate);
}
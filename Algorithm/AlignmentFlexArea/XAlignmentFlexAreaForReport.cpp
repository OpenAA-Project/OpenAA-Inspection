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

#define	_USE_MATH_DEFINES
#include "XAlignmentFlexArea.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"
#include "XAlignmentFlexAreaLibrary.h"

void	AlignmentFlexAreaBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlignmentFlexAreaInPage	*Pg=(AlignmentFlexAreaInPage *)GetPageData(page);

		int	N=Pg->GetAlignmentFlexAreaCount();
			
		ReportedTopic	*r=new ReportedTopic(QString("P:")
											+QString::number(page)
											,QString::number(N));
		RetContainer.AppendList(r);
	}
}


void	AlignmentFlexAreaLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("ExpansionDot"		,ExpansionDot);
	RetContainer.Add("LimitSize"		,LimitSize);

	RetContainer.Add("GlobalSearchDot"	,GlobalSearchDot);
	RetContainer.Add("SearchDot"		,SearchDot);
}

void	AlignmentFlexAreaThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("GlobalSearchDot"		,GlobalSearchDot);
	RetContainer.Add("SearchDot"			,SearchDot);
}
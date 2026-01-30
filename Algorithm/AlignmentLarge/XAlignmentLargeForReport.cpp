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

#include "XAlignmentLargeResource.h"
#include "XAlignmentLarge.h"
#include "XCrossObj.h"
#include "swap.h"
#include "XDataInLayer.h"
#include "XPointer.h"
#include "XParamGlobal.h"
#include "XGeneralFunc.h"

void	AlignmentLargeBase::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	for(int page=0;page<GetPageNumb();page++){
		AlgorithmInPagePLI	*Pg=(AlgorithmInPagePLI *)GetPageData(page);
		for(int layer=0;layer<Pg->GetLayerNumb();layer++){
			AlignmentLargeInLayer	*L=(AlignmentLargeInLayer *)Pg->GetLayerData(layer);
			int	N=L->GetAlignmentLargeAreaCount();
			ReportedTopic	*r=new ReportedTopic(QString(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_35)/*"P:"*/)
												+QString::number(page)
												+QString(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_36)/*" L:"*/)
												+QString::number(layer)
												,QString::number(N));
			RetContainer.AppendList(r);
		}
	}

}

void	AlignmentLargeLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_37)/*"MoveDotX"*/			,MoveDotX);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_38)/*"MoveDotY"*/			,MoveDotY);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_39)/*"MoveDotX2"*/		,MoveDotX2);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_40)/*"MoveDotY2"*/		,MoveDotY2);

	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_41)/*"SearchAround"*/		,SearchAround);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_42)/*"UsageGlobal"*/		,UsageGlobal);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_43)/*"MaxCountHLine"*/	,MaxCountHLine);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_44)/*"MaxCountVLine"*/	,MaxCountVLine);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_45)/*"JudgeWithBrDif"*/	,JudgeWithBrDif);
}


void	AlignmentLargeThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_46)/*"MoveDotX"*/			,MoveDotX);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_47)/*"MoveDotY"*/			,MoveDotY);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_48)/*"MoveDotX2"*/		,MoveDotX2);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_49)/*"MoveDotY2"*/		,MoveDotY2);

	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_50)/*"SearchAround"*/		,SearchAround);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_51)/*"UsageGlobal"*/		,UsageGlobal);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_52)/*"MaxCountHLine"*/	,MaxCountHLine);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_53)/*"MaxCountVLine"*/	,MaxCountVLine);
	RetContainer.Add(LangSolver.GetString(XAlignmentLargeForReport_LS,LID_54)/*"JudgeWithBrDif"*/	,JudgeWithBrDif);
}
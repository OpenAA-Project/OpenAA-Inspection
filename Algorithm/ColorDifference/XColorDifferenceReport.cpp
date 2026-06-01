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


#include "XColorDifference.h"
#include "XColorDifferenceLibrary.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDataAlgorithm.h"

void	ColorDifferenceLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("AdoptedRate"	,AdoptedRate);
	RetContainer.Add("THDeltaE"		,AdoptedRate);
	if(JudgeMethod==0)
		RetContainer.Add("THDeltaE"	,/**/"0:OK/NG");
	else if(JudgeMethod==1)
		RetContainer.Add("THDeltaE"	,/**/"1:DeltaE");
	else if(JudgeMethod==2)
		RetContainer.Add("THDeltaE"	,/**/"2:FlowSample/HSV threshold");
	else if(JudgeMethod==3)
		RetContainer.Add("THDenth"	,/**/"3:Denth");
	else if(JudgeMethod==4){
		RetContainer.Add("THDeltaE"	,/**/"4:DeltaE");
		RetContainer.Add("THDenth"	,/**/"4:Denth");
	}
	RetContainer.Add("dH"		,dH);
	RetContainer.Add("dSL"		,dSL);
	RetContainer.Add("dSH"		,dSH);
	RetContainer.Add("dVL"		,dVL);
	RetContainer.Add("dVH"		,dVH);
}

void	ColorDifferenceThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("AdoptedRate"	,AdoptedRate);
	RetContainer.Add("THDeltaE"		,AdoptedRate);
	if(JudgeMethod==0)
		RetContainer.Add("THDeltaE"	,/**/"0:OK/NG");
	else if(JudgeMethod==1)
		RetContainer.Add("THDeltaE"	,/**/"1:DeltaE");
	else if(JudgeMethod==2)
		RetContainer.Add("THDeltaE"	,/**/"2:FlowSample/HSV threshold");
	else if(JudgeMethod==3)
		RetContainer.Add("THDenth"	,/**/"3:Denth");
	else if(JudgeMethod==4){
		RetContainer.Add("THDeltaE"	,/**/"4:DeltaE");
		RetContainer.Add("THDenth"	,/**/"4:Denth");
	}
	RetContainer.Add("dH"		,dH);
	RetContainer.Add("dSL"		,dSL);
	RetContainer.Add("dSH"		,dSH);
	RetContainer.Add("dVL"		,dVL);
	RetContainer.Add("dVH"		,dVH);
}
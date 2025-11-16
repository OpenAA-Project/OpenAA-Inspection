/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ColorDifference\XColorDifference.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

	RetContainer.Add("dH"		,dH);
	RetContainer.Add("dSL"		,dSL);
	RetContainer.Add("dSH"		,dSH);
	RetContainer.Add("dVL"		,dVL);
	RetContainer.Add("dVH"		,dVH);
}

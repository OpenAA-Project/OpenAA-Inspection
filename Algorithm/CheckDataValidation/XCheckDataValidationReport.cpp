/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XCheckDataValidation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

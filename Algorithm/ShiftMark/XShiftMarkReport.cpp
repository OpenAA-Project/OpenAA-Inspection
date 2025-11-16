/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ShiftMark\XShiftMark.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

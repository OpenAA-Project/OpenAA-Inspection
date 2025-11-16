/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\Process3DL\XProcess3DLReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


//#include "Process3DResource.h"
#include "XProcess3D.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XProcess3DLibrary.h"


void	Process3DLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("BaseCycleDot"		,BaseCycleDot);
	RetContainer.Add("HeightPerShift"	,HeightPerShift);
	RetContainer.Add("LargeTilt"		,LargeTilt);
	RetContainer.Add("LargeFlatness"	,LargeFlatness);
	RetContainer.Add("SmallFlatness"	,SmallFlatness);
	RetContainer.Add("SmallAreaSize"	,SmallAreaSize);
}

void	Process3DThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("BaseCycleDot"		,BaseCycleDot);
	RetContainer.Add("HeightPerShift"	,HeightPerShift);
	RetContainer.Add("LargeTilt"		,LargeTilt);
	RetContainer.Add("LargeFlatness"	,LargeFlatness);
	RetContainer.Add("SmallFlatness"	,SmallFlatness);
	RetContainer.Add("SmallAreaSize"	,SmallAreaSize);
}

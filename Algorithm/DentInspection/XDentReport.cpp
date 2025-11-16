/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\DentL\XDentLReport.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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

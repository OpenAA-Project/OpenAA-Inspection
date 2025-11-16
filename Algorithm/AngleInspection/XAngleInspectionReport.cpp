/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\BlockInspection\XAngleInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XAngleInspection.h"
#include "XGeneralFunc.h"
#include "XPointer.h"
#include "XDataAlgorithm.h"

void	AngleInspectionThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.Add("OKAngleL"	,OKAngleL);
	RetContainer.Add("OKAngleH"	,OKAngleH);
}

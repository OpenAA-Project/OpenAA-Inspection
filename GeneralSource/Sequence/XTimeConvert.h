/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XTimeConvert.h
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  äTóv
//
//  çÏê¨é“
//
/*----------------------------------------------------------------------------*/
#ifndef XTimeConvertH
#define XTimeConvertH
//---------------------------------------------------------------------------
#include <time.h>
#include <QDateTime>
#include "XTypeDef.h"

int  GetYear(::time_t k);
int  GetMonth(::time_t k);
int  GetDay(::time_t k);
int  GetHour(::time_t k);
int  GetMinute(::time_t k);
int  GetSecond(::time_t k);


::time_t  TimeDateToTime_t(QDateTime &d);
QString  Time_tToJikokuString(::time_t k);
QString  Time_tToMinSecString(::time_t k);
QString  Time_tToDayTimeString(::time_t k);


#endif

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XTimeConvert.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#include <time.h>
#include <stdio.h>
#include "XTimeConvert.h"

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

int	GetYear(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_year+1900);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int	GetMonth(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_mon+1);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int GetDay(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_mday);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int GetHour(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_hour);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int GetMinute(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_min);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int GetSecond(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_sec);
}



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
time_t  TimeDateToTime_t(QDateTime &d)
{
    unsigned short  year;
    unsigned short  month;
    unsigned short  day;
    unsigned short  hour;
    unsigned short  dmin;
    unsigned short  dsec;
    unsigned short  dmsec;

///    d.DecodeDate(&year, &month, &day);
	year=d.date().year();
	month=d.date().month();
	day=d.date().day();
///    d.DecodeTime(&hour, &min, &sec, &msec);
	hour=d.time().hour();
	dmin=d.time().minute();
	dsec=d.time().second();
	dmsec=d.time().msec();

    struct tm   tmm;
    tmm.tm_sec  =dsec;
    tmm.tm_min  =dmin;
    tmm.tm_hour =hour;
    tmm.tm_mday =day;
    tmm.tm_mon  =month-1;
    tmm.tm_year =year-1900;
    // tmm.tm_isdst=_daylight;

    return(mktime(&tmm));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString  Time_tToJikokuString(time_t k)
{
    struct tm   *ktm=localtime(&k);
    QString  rt =QString::number(ktm->tm_hour)+QString(":")
                +QString::number(ktm->tm_min )+QString("\'")
                +QString::number(ktm->tm_sec);
    return(rt);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString  Time_tToMinSecString(time_t k)
{
    struct tm   *ktm=localtime(&k);
    QString  rt =QString::number(ktm->tm_hour*60+ktm->tm_min)+QString("\'")
                +QString::number(ktm->tm_sec);
    return(rt);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    k
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString  Time_tToDayTimeString(time_t k)
{
    struct tm   *ktm=localtime(&k);

    char    buff[100];
    sprintf(buff,"%02d/%02d/%02d %02d:%02d:%02d"
                    ,(int)(ktm->tm_year%100)
                    ,(int)ktm->tm_mon+1
                    ,(int)ktm->tm_mday
                    ,(int)ktm->tm_hour
                    ,(int)ktm->tm_min
                    ,(int)ktm->tm_sec);

    QString  rt=QString(buff);
    return(rt);
}

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




#include <time.h>
#include <stdio.h>
#include "XTimeConvert.h"


int	GetYear(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_year+1900);
}

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
int	GetMonth(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_mon+1);
}

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
int GetDay(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_mday);
}

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
int GetHour(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_hour);
}

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
int GetMinute(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_min);
}

/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
//
/*----------------------------------------------------------------------------*/
int GetSecond(time_t k)
{
    struct tm   *ktm=localtime(&k);

    return(ktm->tm_sec);
}



/*----------------------------------------------------------------------------*/
//
//  1.���{�ꖼ
//
//  2.�p�����^����
//    d
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
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
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
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
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
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
//  1.���{�ꖼ
//
//  2.�p�����^����
//    k
//
//  3.�T�v
//
//  4.�@�\����
//
//  5.�߂��l
//
//  6.���l
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
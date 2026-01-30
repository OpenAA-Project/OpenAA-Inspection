/*
 * Copyright (C) 2023
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
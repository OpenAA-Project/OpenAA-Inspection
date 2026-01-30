/*
 * Copyright (C) 2024
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

#if	!defined(XCommToTrigger_h)
#define	XCommToTrigger_h

#include <QObject>
#include <QTcpSocket>
#include "XTypeDef.h"

class	CartonMenuForm;
const	int	TriggerControllerPort=25950;

struct	TriggerInfo
{
	int32	TriggerTiming1;
	int32	TriggerTiming2;
	int32	DropTiming	  ;
};

struct	ResultCounterInfo
{
    int32	TotalCount;
    int32	OKCount;
    int32	NGCount;
    int32	TMCount;	//TimeOut
};
#endif
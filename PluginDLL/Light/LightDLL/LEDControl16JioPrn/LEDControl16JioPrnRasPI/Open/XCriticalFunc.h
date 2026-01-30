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

#if	!defined(XCRITICALFUNC_H)
#define	XCRITICALFUNC_H

#include "XTypeDef.h"

extern "C"
{
DWORD	GetComputerMiliSec(void);

#ifdef _MSC_VER
int64	GetComputerMicrosec(void);
#endif

struct	InitializedMicrosecTimerStruct
{
	char	Dif1Milisec[8];
};

void	InitialMicrosecTimer(struct	InitializedMicrosecTimerStruct &IData);
void	WaitMicrosec(struct	InitializedMicrosecTimerStruct &IData,int MicroSec);
};

#endif
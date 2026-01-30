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

#include "XCriticalFunc.h"

#ifdef _MSC_VER
#include <cmath>
#include <windows.h>

DWORD	GetComputerMiliSec(void)
{
	return ::GetTickCount();
}

int64	GetComputerMicrosec(void)
{
	LARGE_INTEGER PerformanceCount;
	if(QueryPerformanceCounter(&PerformanceCount)==TRUE){   // カウンタの値
		return PerformanceCount.QuadPart;
	}
	return 0;
}

void	InitialMicrosecTimer(struct	InitializedMicrosecTimerStruct &IData)
{
	::Sleep(20);
	LONGLONG	*Dif1Milisec=(LONGLONG	*)IData.Dif1Milisec;
	*Dif1Milisec=0;

	LARGE_INTEGER LastPerformanceCount;
	if(QueryPerformanceCounter(&LastPerformanceCount)==TRUE){   // カウンタの値
		::Sleep(100);
		LARGE_INTEGER CurrentPerformanceCount;
		QueryPerformanceCounter(&CurrentPerformanceCount);   // カウンタの値

		*Dif1Milisec=(CurrentPerformanceCount.QuadPart-LastPerformanceCount.QuadPart)/100;
	}
}

void	WaitMicrosec(struct	InitializedMicrosecTimerStruct &IData,int MicroSec)
{
	LONGLONG	*Dif1Milisec=(LONGLONG	*)IData.Dif1Milisec;
	LONGLONG	LDif=(*Dif1Milisec)*MicroSec/1000;
	if(IData.Dif1Milisec!=0){
		LARGE_INTEGER LastPerformanceCount;
		if(QueryPerformanceCounter(&LastPerformanceCount)==TRUE){   // カウンタの値
			for(;;){
				LARGE_INTEGER CurrentPerformanceCount;
				QueryPerformanceCounter(&CurrentPerformanceCount);   // カウンタの値
				if(LDif<=CurrentPerformanceCount.QuadPart-LastPerformanceCount.QuadPart){
					break;
				}
			}
		}
	}		
}

#else

#include <time.h>

DWORD	GetComputerMiliSec(void)
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
    return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}


#endif
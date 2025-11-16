/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XCritialFunc.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
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

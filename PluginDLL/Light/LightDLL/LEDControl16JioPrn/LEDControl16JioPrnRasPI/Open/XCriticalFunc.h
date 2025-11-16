/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XCriticalFunc.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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

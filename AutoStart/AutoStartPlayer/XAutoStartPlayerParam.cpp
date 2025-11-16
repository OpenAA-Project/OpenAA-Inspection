/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartPlayerParam.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XAutoStartPlayerParam.h"



ParamAutoStart::ParamAutoStart(void)
{
	SettingFileName	=/**/"AutoStart.dat";
	LoopCount=20;
	Arguments="";

	SetParam(&LoopCount	, /**/"Player" ,/**/"LoopCount"		,"Loop count"	,5,1000);
	SetParam(&Arguments	, /**/"Player" ,/**/"Arguments"		,"Argument of execute"	);
}
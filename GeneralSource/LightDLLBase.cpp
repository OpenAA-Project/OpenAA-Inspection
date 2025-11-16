/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\LightDLLBase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "LightDLLBase.h"

void LightDLLBase::SetPowerRateAll(double rate)
{
	int N=GetBarCount();
	for(int i=0;i<N;i++)
		SetPowerRate(i,rate);
}

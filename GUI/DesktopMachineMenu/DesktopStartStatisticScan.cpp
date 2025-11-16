#include "DesktopMachineMenuResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DesktopMachineMenu\DesktopStartStatisticScan.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DesktopStartStatisticScan.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


DesktopStartStatisticScan::DesktopStartStatisticScan(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent),StartStatisticScanBase(Base)
{
	Counter	=0;
	TotalCount=10;
}

void	DesktopStartStatisticScan::SlotToggled(bool checked)
{
	SlotToggledInside(checked);
}

bool DesktopStartStatisticScan::OnIdle(void)
{
	GUIFormBase::OnIdle();
	StartStatisticScanBase::OnIdleFunc();
	return true;
}

void DesktopStartStatisticScan::OnIdleEnd(void)
{
	Counter++;
	if(Counter<TotalCount){
		SlotToggledInside(true);
	}
}

//==================================================================================================

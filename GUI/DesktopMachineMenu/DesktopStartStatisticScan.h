/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DesktopMachineMenu\DesktopStartStatisticScan.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(DESKTOPSTARTSTATISTICSCAN_H)
#define	DESKTOPSTARTSTATISTICSCAN_H

#include "StartStatisticScanBase.h"
#include "XGUIFormBase.h"

class	DesktopStartStatisticScan : public GUIFormBase ,public StartStatisticScanBase
{
	Q_OBJECT

public:
	int		Counter;
	int		TotalCount;
public:
	DesktopStartStatisticScan(LayersBase *Base ,QWidget *parent = 0);

	void	SlotToggled(bool);

protected:
	virtual	bool OnIdle(void)		override;
	virtual	void OnIdleEnd(void)	override;
};


#endif
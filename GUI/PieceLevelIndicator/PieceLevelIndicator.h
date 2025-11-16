/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceLevelIndicator\PieceLevelIndicator.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PIECELEVELINDICATOR_H
#define PIECELEVELINDICATOR_H

#include "piecelevelindicator_global.h"
#include <QTimer>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	PieceLevelIndicator : public GUIFormBase
{
	Q_OBJECT

	int		ColorLevel;
public:
	QColor	BackColor;
	QColor	CurrentLevelColor;
	QColor	UpperLevelColor;
	QTimer	Tm;

	PieceLevelIndicator(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

private slots:
	void	ResizeAction();
	void	SlotTimeout ();
};
#endif // PIECELEVELINDICATOR_H

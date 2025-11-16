/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralHairLine\GeneralHairLine.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALHAIRLINE_H
#define GENERALHAIRLINE_H

#include "generalhairline_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GeneralHairLine : public GUIFormBase
{
	Q_OBJECT

	QFrame	Line;

public:
	QColor	LineColor;
	QString	FrameShape;
	QString	FrameShadow;
	int32	LineWidth;

	GeneralHairLine(LayersBase *Base ,QWidget *parent);
	~GeneralHairLine(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	ResizeAction();
};

#endif // GENERALHAIRLINE_H

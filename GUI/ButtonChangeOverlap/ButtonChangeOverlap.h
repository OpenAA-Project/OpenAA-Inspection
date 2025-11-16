/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonChangeOverlap\ButtonChangeOverlap.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONCHANGEOVERLAP_H
#define BUTTONCHANGEOVERLAP_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include <QColor>
#include <QFont>

class	ButtonChangeOverlap : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonChangeOverlap(LayersBase *Base ,QWidget *parent);
	~ButtonChangeOverlap(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};

#endif // BUTTONCHANGEOVERLAP_H

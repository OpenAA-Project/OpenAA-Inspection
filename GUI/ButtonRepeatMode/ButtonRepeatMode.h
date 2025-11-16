/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonRepeatMode\ButtonRepeatMode.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONREPEATMODE_H
#define BUTTONREPEATMODE_H

#include "buttonrepeatmode_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonRepeatMode : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;

	ButtonRepeatMode(LayersBase *Base ,QWidget *parent);
	~ButtonRepeatMode(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};

#endif // BUTTONREPEATMODE_H

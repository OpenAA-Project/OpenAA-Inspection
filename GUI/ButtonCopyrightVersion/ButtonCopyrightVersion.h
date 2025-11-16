/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCopyrightVersion\ButtonCopyrightVersion.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONCOPYRIGHTVERSION_H
#define BUTTONCOPYRIGHTVERSION_H

#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonCopyrightVersion : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	CopyrightMessage;

	ButtonCopyrightVersion(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONCOPYRIGHTVERSION_H

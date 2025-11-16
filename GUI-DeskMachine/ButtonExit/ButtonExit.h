/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonExit\ButtonExit.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONEXIT_H
#define BUTTONEXIT_H

#include "buttonexit_global.h"
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtImageToolButton.h"

class	ButtonExit : public GUIFormBase
{
	Q_OBJECT

	mtImageToolButton	Button;

public:
	ButtonExit(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONEXIT_H

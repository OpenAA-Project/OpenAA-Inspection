/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonTransferPushGUI\ButtonTransferPushGUI.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONTRANSFERPUSHGUI_H
#define BUTTONTRANSFERPUSHGUI_H

#include "buttontransferpushgui_global.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGeneralWidget.h"

class	ButtonTransferPushGUI : public GUIFormBase
{
	Q_OBJECT

	QPushButtonWithRightClick	Button;

public:
	QString	Msg;
	QString	GUIRoot;
	QString	GUIName;
	QString	GUIInst;

	ButtonTransferPushGUI(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotRightClicked();
	void	SlotResetFixedHost();
	void	SlotEditHost();
};

#endif // BUTTONTRANSFERPUSHGUI_H

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
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonExit : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ConfirmAfterEdit;

	ButtonExit(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
	void	QuitProcess();
	void	SlotQuitUnconditionally();
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONEXIT_H

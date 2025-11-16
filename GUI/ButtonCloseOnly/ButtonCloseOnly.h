/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonCloseOnly\ButtonCloseOnly.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONCLOSEONLY_H
#define BUTTONCLOSEONLY_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QColor>
#include <QFont>

class	ButtonCloseOnly : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	bool	SyncMode;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ConfirmAfterEdit;

	ButtonCloseOnly(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
private slots:
	void	SlotClicked ();
	void	ResizeAction();
};

//=========================================================================

#endif // BUTTONCLOSEONLY_H

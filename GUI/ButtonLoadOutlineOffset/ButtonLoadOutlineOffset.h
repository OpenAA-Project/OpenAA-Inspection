/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadOutlineOffset\ButtonLoadOutlineOffset.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONLOADOUTLINEOFFSET_H
#define BUTTONLOADOUTLINEOFFSET_H

#include "buttonloadoutlineoffset_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class	ButtonLoadOutlineOffset : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonLoadOutlineOffset(LayersBase *Base ,QWidget *parent);
	~ButtonLoadOutlineOffset(void);

	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};


#endif // BUTTONLOADOUTLINEOFFSET_H

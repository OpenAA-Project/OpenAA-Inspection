/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSequence\ButtonSequence.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSEQUENCE_H
#define BUTTONSEQUENCE_H

#include <QPushButton>
#include <QTranslator>
#include "buttonsequence_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSequence : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSequence(LayersBase *Base ,QWidget *parent);
	~ButtonSequence(void);
	virtual void	Prepare(void)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;
	virtual void	Terminated(void)	override;
private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
signals:
	void	SignalButtonClosed();
};

#endif // BUTTONSEQUENCE_H

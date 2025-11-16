/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonReDrawAll\ButtonReDrawAll.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONREDRAWALL_H
#define BUTTONREDRAWALL_H

#include "buttonredrawall_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonReDrawAll : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	int64		LastInspectionID;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonReDrawAll(LayersBase *Base ,QWidget *parent);
	~ButtonReDrawAll(void);
	
	virtual void	Prepare(void)	override;

	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONREDRAWALL_H

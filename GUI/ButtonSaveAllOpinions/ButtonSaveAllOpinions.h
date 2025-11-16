/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveAllOpinions\ButtonSaveAllOpinions.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef BUTTONSAVEALLOPINIONS_H
#define BUTTONSAVEALLOPINIONS_H

#include "buttonsaveallopinions_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveAllOpinions : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonSaveAllOpinions(LayersBase *Base ,QWidget *parent);
	~ButtonSaveAllOpinions(void);

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONSAVEALLOPINIONS_H

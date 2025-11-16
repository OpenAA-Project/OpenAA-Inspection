/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListboxErrorMessage\ListboxErrorMessageForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef LISTBOXERRORMESSAGEFORM_H
#define LISTBOXERRORMESSAGEFORM_H

#include "XGUIFormBase.h"
#include "ui_ListboxErrorMessageForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ListboxErrorMessageForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListboxErrorMessageForm(LayersBase *Base ,QWidget *parent = 0);
	~ListboxErrorMessageForm();

	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)						override;

private:
	void	ShowStatus(void);
private:
	Ui::ListboxErrorMessageFormClass ui;

private slots:
	void on_pushButtonClear_clicked();
    void on_pushButtonUpdate_clicked();
};

#endif // LISTBOXERRORMESSAGEFORM_H

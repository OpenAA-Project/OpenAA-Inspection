/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetTactTime\ButtonSetTactTimeForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSETTACTTIMEFORM_H
#define BUTTONSETTACTTIMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonSetTactTimeForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSetTactTimeForm : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonSetTactTimeForm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonSetTactTimeForm();

	virtual void	BuildForShow(void)	override;
private:
	Ui::ButtonSetTactTimeFormClass ui;

private slots:
	void on_pushButtonSet_clicked();
};

#endif // BUTTONSETTACTTIMEFORM_H

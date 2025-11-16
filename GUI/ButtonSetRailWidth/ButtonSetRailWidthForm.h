/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSetRailWidth\ButtonSetRailWidthForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONSETRAILWIDTHFORM_H
#define BUTTONSETRAILWIDTHFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonSetRailWidthForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonSetRailWidthForm : public GUIFormBase
{
	Q_OBJECT

public:
	int32	InitialWidth;
	double	MaxSize;

	ButtonSetRailWidthForm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonSetRailWidthForm();

	virtual void	Prepare(void)		override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ButtonSetRailWidthFormClass ui;

private slots:
	void on_pushButtonSet_clicked();
};

#endif // BUTTONSETRAILWIDTHFORM_H

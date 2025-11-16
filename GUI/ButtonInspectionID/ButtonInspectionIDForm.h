/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonInspectionID\ButtonInspectionIDForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONINSPECTIONIDFORM_H
#define BUTTONINSPECTIONIDFORM_H

#include "XGUIFormBase.h"
#include "ui_ButtonInspectionIDForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ButtonInspectionIDForm : public GUIFormBase
{
	Q_OBJECT

public:
	ButtonInspectionIDForm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonInspectionIDForm();

	virtual void	BuildForShow(void)						override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
	Ui::ButtonInspectionIDFormClass ui;
	bool	ReEntrant;
private slots:
	void on_spinBoxID_valueChanged(int);
};

#endif // BUTTONINSPECTIONIDFORM_H

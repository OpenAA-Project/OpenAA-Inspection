/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveNewMaster\SaveNewMasterForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef SAVENEWMASTERFORM_H
#define SAVENEWMASTERFORM_H

#include "XGUIFormBase.h"
#include "ui_SaveNewMasterForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class SaveNewMasterForm : public GUIFormBase
{
	Q_OBJECT

public:
	SaveNewMasterForm(LayersBase *Base ,QWidget *parent = 0);
	~SaveNewMasterForm();

private:
	Ui::SaveNewMasterFormClass ui;

private slots:
	void on_pbSave_clicked();
};

#endif // SAVENEWMASTERFORM_H

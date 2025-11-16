/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageProcessor\AddProgramForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef ADDPROGRAMFORM_H
#define ADDPROGRAMFORM_H

#include <QDialog>
#include "ui_AddProgramForm.h"
#include "XServiceForLayers.h"

class AddProgramForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	AddProgramForm(LayersBase *base, QWidget *parent);
	~AddProgramForm();
	
	QString	ProgName;

private:
	Ui::AddProgramFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // ADDPROGRAMFORM_H

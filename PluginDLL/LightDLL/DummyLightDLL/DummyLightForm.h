/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\LightDLL\DummyLightDLL\DummyLightForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef DUMMYLIGHTFORM_H
#define DUMMYLIGHTFORM_H

#include <QDialog>
#include "ui_DummyLightForm.h"

class DummyLightForm : public QDialog
{
	Q_OBJECT

public:
	DummyLightForm(QWidget *parent = 0);
	~DummyLightForm();

private:
	Ui::DummyLightFormClass ui;

private slots:
	void on_pushButtonTurnOff_clicked();
	void on_pushButtonTurnOn_clicked();
};

#endif // DUMMYLIGHTFORM_H

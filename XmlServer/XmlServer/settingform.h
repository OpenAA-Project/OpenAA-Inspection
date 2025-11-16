/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\XmlServer\XmlServer\settingform.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
 #include <QDialog>
#include "ui_settingform.h"
 #include <QFile>
 #include <QTextStream>
class SettingForm : public QDialog
//	Å@SettingForm//QWidget, public SettingFormClass
{
	Q_OBJECT

public:
	SettingForm(QWidget *parent = 0);//QDialog
	//~SettingForm();
	Ui::SettingFormClass ui;

private:
	
private slots:

	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
};

#endif // SETTINGFORM_H

/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
 #include <QDialog>
#include "ui_settingform.h"
 #include <QFile>
 #include <QTextStream>
class SettingForm : public QDialog
//	�@SettingForm//QWidget, public SettingFormClass
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
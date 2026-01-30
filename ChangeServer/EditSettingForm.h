/*
 * Copyright (C) 2012
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

#ifndef EDITSETTINGFORM_H
#define EDITSETTINGFORM_H

#include <QDialog>
#include "ui_EditSettingForm.h"
#include "XChangeServer.h"

class EditSettingForm : public QDialog
{
	Q_OBJECT

public:
	EditSettingForm(int Row
					,ChangeServerContainer	&serverContainer
					,QWidget *parent = 0);
	~EditSettingForm();

	void	GetFromWindow(ChangeServerItem *d);

	int Row;
	ChangeServerContainer	&ServerContainer;
private:
	Ui::EditSettingFormClass ui;

private slots:
	void on_radioButton_2_toggled(bool);
	void on_radioButtonFromBAT_toggled(bool);
	void on_pushButtonFile_clicked();
	void on_pushButtonCancel_clicked();
	void on_pushButtonDelete_clicked();
	void on_pushButtonUpdate_clicked();
	void on_pushButtonCreateNew_clicked();
};

#endif // EDITSETTINGFORM_H
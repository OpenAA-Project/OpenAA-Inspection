/*
 * Copyright (C) 2017
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

#ifndef SETTINGSHRINKFORM_H
#define SETTINGSHRINKFORM_H

#include <QDialog>
#include "ui_SettingShrinkForm.h"
#include "XServiceForLayers.h"

class SettingShrinkForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingShrinkForm(LayersBase *base,int _ShrinkRate,int _ShrinkMethod,QWidget *parent = 0);
	~SettingShrinkForm();

	int		ShrinkRate;
	int		ShrinkMethod;
private:
	Ui::SettingShrinkFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGSHRINKFORM_H
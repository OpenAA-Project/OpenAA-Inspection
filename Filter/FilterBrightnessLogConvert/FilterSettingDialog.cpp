/*
 * Copyright (C) 2018
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

#include "FilterSettingDialog.h"
#include "ui_FilterSettingDialog.h"

FilterSettingDialog::FilterSettingDialog(int position ,double strength ,LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::FilterSettingDialog)
{
    ui->setupUi(this);
	Position	=position;
	Strength	=strength;
	ui->spinBoxPosition			->setValue(Position);
	ui->doubleSpinBoxStrength	->setValue(Strength);
}

FilterSettingDialog::~FilterSettingDialog()
{
    delete ui;
}

void FilterSettingDialog::on_pushButtonOK_clicked()
{
	Position	=ui->spinBoxPosition		->value();
	Strength	=ui->doubleSpinBoxStrength	->value();
	done(true);
}

void FilterSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
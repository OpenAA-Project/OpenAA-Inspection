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

#include "SettingBandDialog.h"
#include "ui_SettingBandDialog.h"

SettingBandDialog::SettingBandDialog(LayersBase *base,int x1 ,int x2 ,double multipleRate ,int offset ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,MultipleRate(multipleRate),Offset(offset),X1(x1),X2(x2)
    ,ui(new Ui::SettingBandDialog)
{
    ui->setupUi(this);
	ui->spinBoxX1			->setValue(x1);
	ui->spinBoxX2			->setValue(x2);
	ui->doubleSpinBoxGain	->setValue(multipleRate);
	ui->spinBoxOffset		->setValue(offset);

	InstallOperationLog(this);
}

SettingBandDialog::~SettingBandDialog()
{
    delete ui;
}

void SettingBandDialog::on_pushButtonOK_clicked()
{
	X1				=ui->spinBoxX1			->value();
	X2				=ui->spinBoxX2			->value();
	MultipleRate	=ui->doubleSpinBoxGain	->value();
	Offset			=ui->spinBoxOffset		->value();
	done(true);
}

void SettingBandDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
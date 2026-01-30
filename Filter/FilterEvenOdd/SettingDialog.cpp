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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterEvenOdd.h"

SettingDialog::SettingDialog(LayersBase *base,FilterEvenOdd *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->doubleSpinBoxLeftEven	->setValue(FParent->ALeftEven);
	ui->doubleSpinBoxLeftOdd	->setValue(FParent->ALeftOdd);
	ui->doubleSpinBoxRightEven	->setValue(FParent->ARightEven);
	ui->doubleSpinBoxRightOdd	->setValue(FParent->ARightOdd);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->ALeftEven	=ui->doubleSpinBoxLeftEven	->value();
	FParent->ALeftOdd	=ui->doubleSpinBoxLeftOdd	->value();
	FParent->ARightEven	=ui->doubleSpinBoxRightEven	->value();
	FParent->ARightOdd	=ui->doubleSpinBoxRightOdd	->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
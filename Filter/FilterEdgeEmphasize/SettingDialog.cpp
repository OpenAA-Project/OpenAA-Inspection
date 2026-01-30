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
#include "FilterEdgeEmphasize.h"

SettingDialog::SettingDialog(LayersBase *base,FilterEdgeEmphasize *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->doubleSpinBoxStrength	->setValue(FParent->Strength);
	ui->spinBoxRadius			->setValue(FParent->Radius);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->Strength	=ui->doubleSpinBoxStrength	->value();
	FParent->Radius	=ui->spinBoxRadius			->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
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

#include "SettingHResolutionDialog.h"
#include "ui_SettingHResolutionDialog.h"

SettingHResolutionDialog::SettingHResolutionDialog(LayersBase *base,double rate ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingHResolutionDialog)
{
    ui->setupUi(this);
	ui->doubleSpinBoxRate->setValue(rate);

	InstallOperationLog(this);
}

SettingHResolutionDialog::~SettingHResolutionDialog()
{
    delete ui;
}

void SettingHResolutionDialog::on_pushButtonOK_clicked()
{
	Rate=ui->doubleSpinBoxRate->value();
	done(true);
}

void SettingHResolutionDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
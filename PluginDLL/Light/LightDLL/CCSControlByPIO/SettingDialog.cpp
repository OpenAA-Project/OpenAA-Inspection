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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XCCSControlByPIO.h"

SettingDialog::SettingDialog(LightCCSControlByPIO *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBoxBrightness->setValue(p->Brightness[0]);
	ui->toolButtonOnOff->setChecked(p->OnMode[0]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_spinBoxBrightness_editingFinished()
{
	Panel->Brightness[0]=ui->spinBoxBrightness->value();
	Panel->ReflectPhysical();
}

void SettingDialog::on_toolButtonOnOff_clicked()
{
	Panel->ReflectPhysicalTurnOn(ui->toolButtonOnOff->isChecked());
}

void SettingDialog::on_pushButtonOK_clicked()
{
	done(true);
}
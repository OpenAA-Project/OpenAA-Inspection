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
#include "XCCSControlByPIO2Ch.h"

SettingDialog::SettingDialog(LightCCSControlByPIO2Ch *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBoxBrightness1	->setValue	(p->Brightness[0]);
	ui->toolButtonOnOff1	->setChecked(p->OnMode[0]);
	ui->spinBoxBrightness2	->setValue	(p->Brightness[1]);
	ui->toolButtonOnOff2	->setChecked(p->OnMode[1]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SettingDialog::on_toolButtonOnOff1_clicked()
{
	Panel->OnMode[0]=ui->toolButtonOnOff1->isChecked();
	Panel->ReflectPhysical();
}

void SettingDialog::on_toolButtonOnOff2_clicked()
{
	Panel->OnMode[1]=ui->toolButtonOnOff2->isChecked();
	Panel->ReflectPhysical();

}

void SettingDialog::on_spinBoxBrightness1_valueChanged(int arg1)
{
	Panel->Brightness[0]=ui->spinBoxBrightness1->value();
	Panel->ReflectPhysical();
}

void SettingDialog::on_spinBoxBrightness2_valueChanged(int arg1)
{
	Panel->Brightness[1]=ui->spinBoxBrightness2->value();
	Panel->ReflectPhysical();
}
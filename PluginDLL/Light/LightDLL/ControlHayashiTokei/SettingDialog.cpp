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
#include "ControlHayashiTokei.h"


SettingDialog::SettingDialog(LightControlHayashiTokei *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBox->setValue(p->Brightness[0]);
	ui->toolButtonON->setChecked(p->OnMode[0]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_spinBox_valueChanged(int arg1)
{
	int	n=ui->comboBoxLEDNumber->currentIndex();
	if(n>=0){
		Panel->Brightness[n]=ui->spinBox->value();
		Panel->Transfer(NULL);
	}
}

void SettingDialog::on_toolButtonON_clicked()
{
	int	n=ui->comboBoxLEDNumber->currentIndex();
	if(n>=0){
		Panel->SetOnOff(n,ui->toolButtonON->isChecked());
	}
}

void SettingDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SettingDialog::on_comboBoxLEDNumber_currentIndexChanged(int index)
{
	int	n=ui->comboBoxLEDNumber->currentIndex();
	if(n>=0){
		ui->spinBox->setValue(Panel->Brightness[n]);
		ui->toolButtonON->setChecked(Panel->OnMode[n]);
	}
}
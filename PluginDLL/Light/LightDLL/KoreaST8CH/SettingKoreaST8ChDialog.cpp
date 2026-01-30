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

#include "SettingKoreaST8ChDialog.h"
#include "ui_SettingKoreaST8ChDialog.h"
#include "KoreaST8CH.h"

SettingKoreaST8ChDialog::SettingKoreaST8ChDialog(KoreaST8ChPanel *panel ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingKoreaST8ChDialog)
	,Panel(panel)
{
    ui->setupUi(this);
	for(int i=0;i<MaxCountOfLED;i++){
		ui->listWidgetCH->addItem(QString("Channel ")+QString::number(i+1));
	}
	panel->GetLayersBase()->InstallOperationLog(this);
}

SettingKoreaST8ChDialog::~SettingKoreaST8ChDialog()
{
    delete ui;
}

void SettingKoreaST8ChDialog::on_pushButtonTransmit_clicked()
{
	int	Ch=ui->listWidgetCH->currentRow();
	bool	OnOff=ui->toolButtonLightON->isChecked();
	int		LightValue=ui->spinBoxLightValue->value();
	Panel->SetValue(Ch,LightValue,OnOff);
}

void SettingKoreaST8ChDialog::on_pushButtonClose_clicked()
{
	close();
}
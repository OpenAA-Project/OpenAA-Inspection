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

#include "PropertyCheckEverydayFormResource.h"
#include "CreateManualLightDialog.h"
#include "ui_CreateManualLightDialog.h"
#include "XRememberer.h"

CreateManualLightDialog::CreateManualLightDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CreateManualLightDialog)
{
    ui->setupUi(this);

	ui->lineEditItemName->setText(ControlRememberer::GetString(ui->lineEditItemName ,/**/""));	
	ui->spinBoxBrightnessLow	->setValue(ControlRememberer::GetInt(ui->spinBoxBrightnessLow ,0));
	ui->spinBoxBrightnessHigh	->setValue(ControlRememberer::GetInt(ui->spinBoxBrightnessHigh,255));
	InstallOperationLog(this);
}

CreateManualLightDialog::~CreateManualLightDialog()
{
    delete ui;
}

void	CreateManualLightDialog::Reflect(void)
{
	ui->lineEditItemName		->setText(ItemName);
	ui->spinBoxBrightnessLow	->setValue(BrightnessLow);
	ui->spinBoxBrightnessHigh	->setValue(BrightnessHigh);
}

void CreateManualLightDialog::on_pushButtonOK_clicked()
{
	ItemName		=ui->lineEditItemName->text();
	BrightnessLow	=ui->spinBoxBrightnessLow	->value();
	BrightnessHigh	=ui->spinBoxBrightnessHigh	->value();

	ControlRememberer::SetValue(ui->lineEditItemName	 ,ui->lineEditItemName->text());
	ControlRememberer::SetValue(ui->spinBoxBrightnessLow ,ui->spinBoxBrightnessLow->value());
	ControlRememberer::SetValue(ui->spinBoxBrightnessHigh,ui->spinBoxBrightnessHigh->value());

	accept();
}

void CreateManualLightDialog::on_pushButtonCancel_clicked()
{
	reject();
}
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
#include "CreateManualFocusDialog.h"
#include "ui_CreateManualFocusDialog.h"
#include "XRememberer.h"

CreateManualFocusDialog::CreateManualFocusDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CreateManualFocusDialog)
{
    ui->setupUi(this);

	ui->lineEditItemName		->setText (ControlRememberer::GetString(ui->lineEditItemName ,/**/""));	
	ui->doubleSpinBoxFocusLow	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxFocusLow ,0));
	InstallOperationLog(this);
}

CreateManualFocusDialog::~CreateManualFocusDialog()
{
    delete ui;
}

void	CreateManualFocusDialog::Reflect(void)
{
	ui->lineEditItemName		->setText(ItemName);
	ui->doubleSpinBoxFocusLow	->setValue(FocusLow);
}

void CreateManualFocusDialog::on_pushButtonOK_clicked()
{
	ItemName	=ui->lineEditItemName		->text();
	FocusLow	=ui->doubleSpinBoxFocusLow	->value();

	ControlRememberer::SetValue(ui->lineEditItemName		,ui->lineEditItemName->text());
	ControlRememberer::SetValue(ui->doubleSpinBoxFocusLow	,ui->doubleSpinBoxFocusLow->value());

	accept();
}

void CreateManualFocusDialog::on_pushButtonCancel_clicked()
{
    reject();
}
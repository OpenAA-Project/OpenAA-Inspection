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

#include "IPAddressDialog.h"
#include "ui_IPAddressDialog.h"
#include "SettingDialog.h"
#include "ImacControlByLAN.h"

IPAddressDialog::IPAddressDialog(SettingDialog *d ,LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,SettingD(d)
    ,ui(new Ui::IPAddressDialog)
{
    ui->setupUi(this);

	ui->lineEditCurrentIP			->setText	(SettingD->Data->IPAddress);
	ui->spinBoxCurrentPort			->setValue	(SettingD->Data->Port);
	ui->lineEditNewIP				->setText	(SettingD->Data->IPAddress);
	ui->spinBoxNewPort				->setValue	(SettingD->Data->Port);
	ui->lineEditNewSubnetMask		->setText	(SettingD->Data->SubnetMask);
	ui->lineEditNewDefaultGateway	->setText	(SettingD->Data->DefaultGateway);
}

IPAddressDialog::~IPAddressDialog()
{
    delete ui;
}

void IPAddressDialog::on_pushButtonSet_clicked()
{
	SettingD->Data->IPAddress			=ui->lineEditNewIP				->text	();
	SettingD->Data->Port				=ui->spinBoxNewPort				->value	();
	SettingD->Data->SubnetMask			=ui->lineEditNewSubnetMask		->text	();
	SettingD->Data->DefaultGateway		=ui->lineEditNewDefaultGateway	->text	();

	done(true);
}

void IPAddressDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
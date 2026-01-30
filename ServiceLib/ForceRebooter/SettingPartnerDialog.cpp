/*
 * Copyright (C) 2014
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

#include "SettingPartnerDialog.h"
#include "ui_SettingPartnerDialog.h"

SettingPartnerDialog::SettingPartnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingPartnerDialog)
{
    ui->setupUi(this);
}

SettingPartnerDialog::~SettingPartnerDialog()
{
    delete ui;
}

void	SettingPartnerDialog::Init(void)
{
	ui->lineEditHostIP->setText(Info.HostName);
	ui->spinBoxPortNumber->setValue(Info.PortNumber);
	ui->lineEditRemark->setText(Info.Remark);
}

void SettingPartnerDialog::on_pushButtonOK_clicked()
{
	Info.HostName	=ui->lineEditHostIP->text();
	Info.PortNumber	=ui->spinBoxPortNumber->value();
	Info.Remark		=ui->lineEditRemark->text();
	done(true);
}

void SettingPartnerDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
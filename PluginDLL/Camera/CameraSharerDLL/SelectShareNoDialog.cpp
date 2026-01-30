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

#include "SelectShareNoDialog.h"
#include "ui_SelectShareNoDialog.h"

SelectShareNoDialog::SelectShareNoDialog(int _ShareNo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectShareNoDialog)
{
    ui->setupUi(this);
	ShareNo	=_ShareNo;
	ui->spinBoxShareNo->setValue(ShareNo);
}

SelectShareNoDialog::~SelectShareNoDialog()
{
    delete ui;
}

void SelectShareNoDialog::on_pushButtonOK_clicked()
{
	ShareNo=ui->spinBoxShareNo->value();
	done(true);
}

void SelectShareNoDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
/*
 * Copyright (C) 2019
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

#include "InputCodeDialogResource.h"
#include "InputCodeDialog.h"
#include "ui_InputCodeDialog.h"

InputCodeDialog::InputCodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputCodeDialog)
{
    ui->setupUi(this);
}

InputCodeDialog::~InputCodeDialog()
{
    delete ui;
}

void InputCodeDialog::on_pushButtonOK_clicked()
{
	BarCode	=ui->lineEditBarcode->text();
	done(true);
}

void InputCodeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
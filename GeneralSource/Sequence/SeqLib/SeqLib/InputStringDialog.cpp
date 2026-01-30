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


#include "XTypeDef.h"
#include "InputStringDialog.h"
#include "ui_InputStringDialog.h"

InputStringDialog::InputStringDialog(QString d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputStringDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(d);
}

InputStringDialog::~InputStringDialog()
{
    delete ui;
}

void InputStringDialog::on_pushButtonOK_clicked()
{
    Value=ui->lineEdit->text();
    done(true);
}

void InputStringDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
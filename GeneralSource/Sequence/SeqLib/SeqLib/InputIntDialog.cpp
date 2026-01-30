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
#include "InputIntDialog.h"
#include "ui_InputIntDialog.h"

InputIntDialog::InputIntDialog(int d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputIntDialog)
{
    ui->setupUi(this);
    ui->spinBox->setValue(d);
}

InputIntDialog::~InputIntDialog()
{
    delete ui;
}

void InputIntDialog::on_pushButtonOK_clicked()
{
    Value=ui->spinBox->value();
    done(true);
}

void InputIntDialog::on_pushButtonCancel_clicked()
{
    done(false);
}
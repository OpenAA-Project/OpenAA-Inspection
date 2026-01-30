/*
 * Copyright (C) 2016
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

#include "BrightHistogramDialog.h"
#include "ui_BrightHistogramDialog.h"

BrightHistogramDialog::BrightHistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrightHistogramDialog)
{
    ui->setupUi(this);
}

BrightHistogramDialog::~BrightHistogramDialog()
{
    delete ui;
}

void BrightHistogramDialog::on_ButtonReflect_clicked()
{

}

void BrightHistogramDialog::on_EditPickupL_valueChanged(int arg1)
{

}

void BrightHistogramDialog::on_EditPickupH_valueChanged(int arg1)
{

}

void BrightHistogramDialog::on_ButtonClose_clicked()
{

}
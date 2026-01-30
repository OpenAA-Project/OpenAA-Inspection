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

#include "CameraAllocationDialog.h"
#include "ui_CameraAllocationDialog.h"

CameraAllocationDialog::CameraAllocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraAllocationDialog)
{
    ui->setupUi(this);
}

CameraAllocationDialog::~CameraAllocationDialog()
{
    delete ui;
}

void CameraAllocationDialog::on_pushButtonOK_clicked()
{

}

void CameraAllocationDialog::on_pushButtonCancel_clicked()
{

}
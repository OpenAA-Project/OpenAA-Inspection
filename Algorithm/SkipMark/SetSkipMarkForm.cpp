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

#include "SetSkipMarkForm.h"
#include "ui_SetSkipMarkForm.h"
#include "SelectAreaDialog.h"

SetSkipMarkForm::SetSkipMarkForm(LayersBase *base, QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SetSkipMarkForm)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

SetSkipMarkForm::~SetSkipMarkForm()
{
    delete ui;
}

void SetSkipMarkForm::on_pushButtonModify_clicked()
{

}

void SetSkipMarkForm::on_pushButtonCancel_clicked()
{

}

void SetSkipMarkForm::on_pushButtonSelectArea_clicked()
{

}
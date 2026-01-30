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

#include "BlockFormResource.h"
#include "SetOKDialog.h"
#include "ui_SetOKDialog.h"

SetOKDialog::SetOKDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SetOKDialog)
{
    ui->setupUi(this);

	InstallOperationLog(this);
}

SetOKDialog::~SetOKDialog()
{
    delete ui;
}

void SetOKDialog::on_pushButtonBOKBright_clicked()
{

}

void SetOKDialog::on_pushButtonBOKSize_clicked()
{

}

void SetOKDialog::on_pushButtonNOKBright_clicked()
{

}

void SetOKDialog::on_pushButtonNOKSize_clicked()
{

}

void SetOKDialog::on_pushButtonOKSearch_clicked()
{

}

void SetOKDialog::on_pushButtonClose_clicked()
{

}
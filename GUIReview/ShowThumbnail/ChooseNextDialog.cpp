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

#include "ShowThumbnailResource.h"
#include "ChooseNextDialog.h"
#include "ui_ChooseNextDialog.h"
#include "XGeneralFunc.h"

ChooseNextDialog::ChooseNextDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseNextDialog)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
}

ChooseNextDialog::~ChooseNextDialog()
{
    delete ui;
}

void ChooseNextDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void ChooseNextDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
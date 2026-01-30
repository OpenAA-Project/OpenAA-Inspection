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

#include "SettingMoveImageForm.h"
#include "ui_SettingMoveImageForm.h"

SettingMoveImageForm::SettingMoveImageForm(LayersBase *base,int dx ,int dy ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingMoveImageForm)
{
    ui->setupUi(this);
	ui->spinBoxDx->setValue(dx);
	ui->spinBoxDy->setValue(dy);
	Dx=dx;
	Dy=dy;

	InstallOperationLog(this);
}

SettingMoveImageForm::~SettingMoveImageForm()
{
    delete ui;
}

void SettingMoveImageForm::on_pushButtonOK_clicked()
{
	Dx=ui->spinBoxDx->value();
	Dy=ui->spinBoxDy->value();
	done(true);
}

void SettingMoveImageForm::on_pushButtonCancel_clicked()
{
	done(false);
}
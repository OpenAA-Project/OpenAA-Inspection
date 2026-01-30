/*
 * Copyright (C) 2022
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

#include "ShadowSettingDialog.h"
#include "ui_ShadowSettingDialog.h"
#include "ShrinkedInspection.h"

ShadowSettingDialog::ShadowSettingDialog(ShrinkedInspection *_Handle,QWidget *parent) :
    QDialog(parent),Handle(_Handle),
    ui(new Ui::ShadowSettingDialog)
{
    ui->setupUi(this);

	ui->spinBoxSkipDot			->setValue(Handle->SkipDot);
	ui->checkBoxHorizontalTile	->setChecked(Handle->HorizontalTile );
	ui->checkBoxVerticalTile	->setChecked(Handle->VerticalTile	);
}

ShadowSettingDialog::~ShadowSettingDialog()
{
    delete ui;
}

void ShadowSettingDialog::on_pushButtonOK_clicked()
{
	Handle->SetSkipDot(ui->spinBoxSkipDot->value());
	Handle->HorizontalTile	=ui->checkBoxHorizontalTile	->isChecked();
	Handle->VerticalTile	=ui->checkBoxVerticalTile	->isChecked();
	done(true);
}

void ShadowSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
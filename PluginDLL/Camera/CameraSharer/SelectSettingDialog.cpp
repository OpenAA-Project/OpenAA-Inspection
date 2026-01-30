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

#include "SelectSettingDialog.h"
#include "ui_SelectSettingDialog.h"

SelectSettingDialog::SelectSettingDialog(CameraSharer *parentMain,int number ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSettingDialog)
{
    ui->setupUi(this);

	ParentMain	=parentMain;
	Number		=number;

	ui->spinBoxCameraNo->setValue(ParentMain->GetCam(Number)->GetCamNo());
}

SelectSettingDialog::~SelectSettingDialog()
{
    delete ui;
}

void SelectSettingDialog::on_pushButtonSetting_clicked()
{

}


void SelectSettingDialog::on_pushButtonClose_clicked()
{
	ParentMain->SetCamNo(Number,ui->spinBoxCameraNo->value());
	close();
}
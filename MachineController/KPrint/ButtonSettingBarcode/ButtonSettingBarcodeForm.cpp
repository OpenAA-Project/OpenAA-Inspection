/*
 * Copyright (C) 2021
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

#include "ButtonSettingBarcodeForm.h"
#include "ui_ButtonSettingBarcodeForm.h"
#include "SettingBarcodeFormDialog.h"

extern	char *sRoot;
extern	char *sName;

ButtonSettingBarcodeForm::ButtonSettingBarcodeForm(LayersBase *Base, QWidget *parent) :
	GUIFormBase(Base, parent),
    ui(new Ui::ButtonSettingBarcodeForm)
{
    ui->setupUi(this);
	SlaveNo=0;
	Msg=/**/"Set Barcose Threshold";
	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));
}

ButtonSettingBarcodeForm::~ButtonSettingBarcodeForm()
{
    delete ui;
}
void	ButtonSettingBarcodeForm::Prepare(void)
{
	ui->PushButtonThreshold->setText(Msg);
	ui->PushButtonThreshold->setFont(CFont);
	ResizeAction();
}
void	ButtonSettingBarcodeForm::ResizeAction()
{
	ui->PushButtonThreshold->resize(width(), height());
}

void ButtonSettingBarcodeForm::on_PushButtonThreshold_clicked()
{
	SettingBarcodeFormDialog	D(GetLayersBase(), this);
	D.exec();
}
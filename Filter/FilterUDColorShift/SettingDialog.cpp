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

#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),ServiceForLayers(base)
{
    ui->setupUi(this);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}
void	SettingDialog::Initial(int	_ShiftR ,int _ShiftG ,int _ShiftB 
								,bool _CheckTime ,int _TimeRange,int _ShiftOffset)
{
	ui->spinBoxShiftR		->setValue(_ShiftR);
	ui->spinBoxShiftG		->setValue(_ShiftG);
	ui->spinBoxShiftB		->setValue(_ShiftB);
	ui->spinBoxTimeRange	->setValue(_TimeRange);
	ui->checkBoxCheckTime	->setChecked(_CheckTime);
	ui->spinBoxShiftOffset	->setValue(_ShiftOffset);
}

void SettingDialog::on_pushButtonOK_clicked()
{
	ShiftR		=ui->spinBoxShiftR		->value();
	ShiftG		=ui->spinBoxShiftG		->value();
	ShiftB		=ui->spinBoxShiftB		->value();
	TimeRange	=ui->spinBoxTimeRange	->value();
	CheckTime	=ui->checkBoxCheckTime	->isChecked();
	ShiftOffset	=ui->spinBoxShiftOffset	->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
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

#include "SettingReverseLensOneside.h"
#include "ui_SettingReverseLensOneside.h"

SettingReverseLensOneside::SettingReverseLensOneside(LayersBase *base
													,double _Strength ,double _Width
													,  bool	_LeftSide   ,bool _RightSide
													, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingReverseLensOneside)
{
    ui->setupUi(this);
	ui->doubleSpinBoxStrength->setValue(_Strength);
	ui->doubleSpinBoxWidth	->setValue(_Width);	
	ui->checkBoxLeftSide	->setChecked(_LeftSide);
	ui->checkBoxRightSide	->setChecked(_RightSide);

	InstallOperationLog(this);
}

SettingReverseLensOneside::~SettingReverseLensOneside()
{
    delete ui;
}

void SettingReverseLensOneside::on_pushButtonOK_clicked()
{
	Strength	=ui->doubleSpinBoxStrength	->value();
	Width		=ui->doubleSpinBoxWidth		->value();
	LeftSide	=ui->checkBoxLeftSide	->isChecked();
	RightSide	=ui->checkBoxRightSide	->isChecked();
	done(true);
}

void SettingReverseLensOneside::on_pushButtonCancel_clicked()
{
	done(false);
}
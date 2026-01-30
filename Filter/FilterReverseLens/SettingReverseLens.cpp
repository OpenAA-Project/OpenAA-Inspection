/*
 * Copyright (C) 2024
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

#include "SettingReverseLens.h"

SettingReverseLens::SettingReverseLens(LayersBase *base
										,double _Strength ,double _Width,int32 _StartX,int32 _EndX
										, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.doubleSpinBoxStrength->setValue(_Strength);
	ui.doubleSpinBoxWidth	->setValue(_Width);
	ui.spinBoxStartX		->setValue(_StartX);
	ui.spinBoxEndX			->setValue(_EndX);
	InstallOperationLog(this);
}

SettingReverseLens::~SettingReverseLens()
{

}


void SettingReverseLens::on_pushButtonOK_clicked()
{
	Strength	=ui.doubleSpinBoxStrength	->value();
	Width		=ui.doubleSpinBoxWidth		->value();
	StartX		=ui.spinBoxStartX			->value();
	EndX		=ui.spinBoxEndX				->value();
	done(true);
}

void SettingReverseLens::on_pushButtonCancel_clicked()
{
	done(false);
}
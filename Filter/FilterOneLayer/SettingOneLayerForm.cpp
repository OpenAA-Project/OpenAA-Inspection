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

#include "SettingOneLayerForm.h"

SettingOneLayerForm::SettingOneLayerForm(LayersBase *base
					,int _Layer ,int _LayerNumb
					,int _MethodValue
					,int _Param
					,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);

	ui.comboBoxLayer->clear();
	for(int i=0;i<_LayerNumb;i++){
		ui.comboBoxLayer->addItem(QString(/**/"Layer-")+QString::number(i));
	}
	ui.comboBoxLayer	->setCurrentIndex(_Layer);
	ui.comboBoxProcess	->setCurrentIndex(_MethodValue);
	ui.spinBoxParam	->setValue(_Param);

	InstallOperationLog(this);
}

SettingOneLayerForm::~SettingOneLayerForm()
{

}


void SettingOneLayerForm::on_pushButtonOK_clicked()
{
	Layer		=ui.comboBoxLayer	->currentIndex();
	MethodValue	=ui.comboBoxProcess	->currentIndex();
	Param		=ui.spinBoxParam	->value();
	done(true);
}

void SettingOneLayerForm::on_pushButtonCancel_clicked()
{
	done(false);
}
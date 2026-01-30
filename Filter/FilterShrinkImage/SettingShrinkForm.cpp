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

#include "SettingShrinkForm.h"

SettingShrinkForm::SettingShrinkForm(LayersBase *base,int _ShrinkRate,int _ShrinkMethod,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.spinBoxShrinkRate	->setValue(_ShrinkRate);
	ui.comboBoxShrinkMethod->setCurrentIndex(_ShrinkMethod)	;

	InstallOperationLog(this);
}

SettingShrinkForm::~SettingShrinkForm()
{

}


void SettingShrinkForm::on_pushButtonOK_clicked()
{
	ShrinkRate	=ui.spinBoxShrinkRate	->value();
	ShrinkMethod=ui.comboBoxShrinkMethod->currentIndex();
	done(true);
}

void SettingShrinkForm::on_pushButtonCancel_clicked()
{
	done(false);
}
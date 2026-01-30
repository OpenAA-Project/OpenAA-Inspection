/*
 * Copyright (C) 2014
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

#include "EditAxisIDForm.h"

EditAxisIDForm::EditAxisIDForm(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

EditAxisIDForm::~EditAxisIDForm()
{

}

void	EditAxisIDForm::SetData(int axisID ,int centerInMaster ,int okZone)
{
	ui.spinBoxAxisID->setValue(axisID);
	ui.spinBoxCenterInMaster->setValue(centerInMaster);
	ui.spinBoxOKZone		->setValue(okZone);
}


void EditAxisIDForm::on_pushButtonOK_clicked()
{
	AxisID			=ui.spinBoxAxisID		->value();
	CenterInMaster	=ui.spinBoxCenterInMaster->value();
	OKZone			=ui.spinBoxOKZone		->value();
	done(true);
}

void EditAxisIDForm::on_pushButtonCancel_clicked()
{
	done(false);
}
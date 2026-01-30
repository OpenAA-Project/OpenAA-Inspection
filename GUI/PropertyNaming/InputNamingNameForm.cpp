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

#include "PropertyNamingFormResource.h"

#include "InputNamingNameForm.h"
#include "XPropertyNamingPacket.h"

InputNamingNameForm::InputNamingNameForm(LayersBase *base, QWidget *parent)
	: QWidget(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	ui.lineEditName->setText(InputedName);
	ui.spinBoxX	->setValue(-1);
	ui.spinBoxY	->setValue(-1);
	RetOK=false;
	InstallOperationLog(this);
}

InputNamingNameForm::~InputNamingNameForm()
{

}


void	InputNamingNameForm::SetNamingItem(NamingListForPacket *item)
{
	ui.lineEditName->setText(item->AreaName);
	ui.spinBoxX	->setValue(item->Column);
	ui.spinBoxY	->setValue(item->Row);
	NamingItem	=item;
}


void InputNamingNameForm::on_pushButtonOK_clicked()
{
	InputedName=ui.lineEditName->text();
	Column	=ui.spinBoxX	->value();
	Row		=ui.spinBoxY	->value();
	RetOK=true;
	emit	SignalClose();
}
void InputNamingNameForm::on_pushButtonCancel_clicked()
{
    RetOK=false;
    emit	SignalClose();
}
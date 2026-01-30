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

#include "ChooseItemTypeFormResource.h"
#include "ChooseItemTypeForm.h"

ChooseItemTypeForm::ChooseItemTypeForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

ChooseItemTypeForm::~ChooseItemTypeForm()
{

}


void ChooseItemTypeForm::on_toolButtonPad_clicked()
{
	done((int)Type_Pad);
}

void ChooseItemTypeForm::on_toolButtonLine_clicked()
{
	done((int)Type_Line);
}

void ChooseItemTypeForm::on_toolButtonMatchingLine_clicked()
{
	done((int)Type_Matching);
}
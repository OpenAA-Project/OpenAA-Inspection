/*
 * Copyright (C) 2026
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

//#include "AddManualItemFormResource.h"
#include "AddManualItemForm.h"
#include "XRememberer.h"

AddManualItemForm::AddManualItemForm(LayersBase *Base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	Mergin			=20;

	InstallOperationLog(this);
}

AddManualItemForm::~AddManualItemForm()
{

}

void	AddManualItemForm::Initial(void)
{
}

void	AddManualItemForm::SlotColorSampleBeforeSave()
{
}

void	AddManualItemForm::SlotColorSampleSelectOne()
{
}

void AddManualItemForm::on_pushButtonAddColor_clicked()
{
}

void AddManualItemForm::on_pushButtonEliminateColor_clicked()
{
}

void AddManualItemForm::on_pushButtonSetMergin_clicked()
{
	//Mergin=ui.spinBoxMergin->value();
}

void AddManualItemForm::on_pushButtonOK_clicked()
{
	//Mergin		=ui.spinBoxMergin		->value();

	done(true);
}

void AddManualItemForm::on_pushButtonCancel_clicked()
{
	done(false);
}
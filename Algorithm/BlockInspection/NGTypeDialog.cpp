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

#include "BlockFormResource.h"
#include "NGTypeDialog.h"
#include "XBlockLibrary.h"

NGTypeDialog::NGTypeDialog(LayersBase *base, BlockLibNGTypeItem *item ,QWidget *parent)
	: QDialog(parent)
	,ServiceForLayers(base)
	,Item(item)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	ui.spinBoxMinColor	->setValue(Item->MinColor);
	ui.spinBoxMaxColor	->setValue(Item->MaxColor);
	ui.spinBoxMinSize	->setValue(Item->MinSize);
	ui.spinBoxMaxSize	->setValue(Item->MaxSize);
	ui.spinBoxMinRoundRate->setValue(Item->MinRoundRate);
	ui.spinBoxMaxRoundRate->setValue(Item->MaxRoundRate);

	InstallOperationLog(this);
}

NGTypeDialog::~NGTypeDialog()
{

}


void NGTypeDialog::on_pushButtonOK_clicked()
{
	Item->MinColor	=ui.spinBoxMinColor->value();
	Item->MaxColor	=ui.spinBoxMaxColor->value();
	Item->MinSize	=ui.spinBoxMinSize->value();
	Item->MaxSize	=ui.spinBoxMaxSize->value();
	Item->MinRoundRate	=ui.spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui.spinBoxMaxRoundRate->value();
	done(true);
}
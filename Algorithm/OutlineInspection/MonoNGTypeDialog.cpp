/*
 * Copyright (C) 2022
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

#include "MonoNGTypeDialog.h"
#include "ui_MonoNGTypeDialog.h"
#include "XOutlineLibrary.h"

MonoNGTypeDialog::MonoNGTypeDialog(LayersBase *base, OutlineInspectLibNGTypeItem *item ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
	,Item(item)
    ,ui(new Ui::MonoNGTypeDialog)
{
    ui->setupUi(this);

	int ColL,ColH;
	Item->ColorZone.GetMonoColorRange(ColL,ColH);
	ui->spinBoxMinColor		->setValue(ColL);
	ui->spinBoxMaxColor		->setValue(ColH);
	ui->spinBoxMinSize		->setValue(Item->MinSize);
	ui->spinBoxMaxSize		->setValue(Item->MaxSize);
	ui->spinBoxMinRoundRate	->setValue(Item->MinRoundRate);
	ui->spinBoxMaxRoundRate	->setValue(Item->MaxRoundRate);

	InstallOperationLog(this);
}

MonoNGTypeDialog::~MonoNGTypeDialog()
{
    delete ui;
}

void MonoNGTypeDialog::on_pushButtonOK_clicked()
{
	int	ColL			=ui->spinBoxMinColor->value();
	int	ColH			=ui->spinBoxMaxColor->value();
	Item->ColorZone.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	Item->MinSize		=ui->spinBoxMinSize->value();
	Item->MaxSize		=ui->spinBoxMaxSize->value();
	Item->MinRoundRate	=ui->spinBoxMinRoundRate->value();
	Item->MaxRoundRate	=ui->spinBoxMaxRoundRate->value();
	done(true);
}
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

#include "CreateManualItemFormResource.h"
#include "ModifyItemDialog.h"
#include "ui_ModifyItemDialog.h"

ModifyItemDialog::ModifyItemDialog(LayersBase *base, QString &itemName ,MeasureHolePosThreshold *_ThreData ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,ThreData(_ThreData)
    ,ui(new Ui::ModifyItemDialog)
{
    ui->setupUi(this);
	ItemName	=itemName;

	ui->EditName					->setText(ItemName);
	ui->doubleSpinBoxDiaPrecision	->setValue(ThreData->DiaPrecision);
	ui->doubleSpinBoxPosPrecision	->setValue(ThreData->PosPrecision);
	ui->spinBoxNoiseSize			->setValue(ThreData->NoiseSize);
	ui->spinBoxBandWidth			->setValue(ThreData->BandWidth);
	ui->EditSearchDot				->setValue(ThreData->SearchDot);
	InstallOperationLog(this);
}

ModifyItemDialog::~ModifyItemDialog()
{
    delete ui;
}

void ModifyItemDialog::on_ButtonOK_clicked()
{
	ItemName				=ui->EditName					->text();
	ThreData->DiaPrecision	=ui->doubleSpinBoxDiaPrecision	->value();
	ThreData->PosPrecision	=ui->doubleSpinBoxPosPrecision	->value();
	ThreData->NoiseSize		=ui->spinBoxNoiseSize			->value();
	ThreData->BandWidth		=ui->spinBoxBandWidth			->value();
	ThreData->SearchDot		=ui->EditSearchDot				->value();
	done(true);
}

void ModifyItemDialog::on_ButtonCancel_clicked()
{
	done(false);
}
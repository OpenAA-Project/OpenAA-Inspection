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

#include "PropertyMeasureLineMoveFormResource.h"
#include "EditLineMoveDialog.h"
#include "ui_EditLineMoveDialog.h"

EditLineMoveDialog::EditLineMoveDialog(LayersBase *base, QString &itemName ,MeasureLineMoveThreshold *_ThreData ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,ThreData(_ThreData)
    ,ui(new Ui::EditLineMoveDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->EditName				->setText(itemName);
	ui->doubleSpinBoxThresholdM	->setValue(ThreData->ThresholdM);	//micron size
	ui->doubleSpinBoxThresholdP	->setValue(ThreData->ThresholdP);	//micron size
	ui->EditEdgeWidth			->setValue(ThreData->EdgeWidth);
	ui->EditSearchDot			->setValue(ThreData->SearchDot);
	ui->checkBoxPrevailLeft		->setChecked(ThreData->PrevailLeft);
	ui->checkBoxPrevailRight	->setChecked(ThreData->PrevailRight);
	InstallOperationLog(this);
}

EditLineMoveDialog::~EditLineMoveDialog()
{
    delete ui;
}

void EditLineMoveDialog::on_ButtonOK_clicked()
{
	ItemName				=ui->EditName					->text();
	ThreData->ThresholdM	=ui->doubleSpinBoxThresholdM	->value();	//micron size
	ThreData->ThresholdP	=ui->doubleSpinBoxThresholdP	->value();	//micron size
	ThreData->EdgeWidth		=ui->EditEdgeWidth				->value();
	ThreData->SearchDot		=ui->EditSearchDot				->value();
	ThreData->PrevailLeft	=ui->checkBoxPrevailLeft		->isChecked();
	ThreData->PrevailRight	=ui->checkBoxPrevailRight		->isChecked();
	done(true);
}

void EditLineMoveDialog::on_ButtonCancel_clicked()
{
	done(false);
}
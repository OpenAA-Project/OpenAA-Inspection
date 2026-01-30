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

#include "AddAreaDialogResource.h"
#include "SelectShapeTypeDialog.h"
#include "ui_SelectShapeTypeDialog.h"
#include "XRememberer.h"

SelectShapeTypeDialog::SelectShapeTypeDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectShapeTypeDialog)
{
    ui->setupUi(this);
	ui->doubleSpinBoxThreShape	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxThreShape,0.9));
	ui->doubleSpinBoxThreColor	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxThreColor,0.9));
	ui->spinBoxSearchDot		->setValue(ControlRememberer::GetInt(ui->spinBoxSearchDot,20));

	InstallOperationLog(this);
}

SelectShapeTypeDialog::~SelectShapeTypeDialog()
{
    delete ui;
}

void SelectShapeTypeDialog::on_pushButtonSetColorArea_clicked()
{
	ThreShape	=ui->doubleSpinBoxThreShape	->value();
	ThreColor	=ui->doubleSpinBoxThreColor	->value();

	ControlRememberer::SetValue(ui->doubleSpinBoxThreShape ,ui->doubleSpinBoxThreShape->value());
	ControlRememberer::SetValue(ui->doubleSpinBoxThreColor ,ui->doubleSpinBoxThreColor->value());

	done(1);
}

void SelectShapeTypeDialog::on_pushButtonSetShapeArea_clicked()
{
	ThreShape	=ui->doubleSpinBoxThreShape	->value();
	ThreColor	=ui->doubleSpinBoxThreColor	->value();
	SearchDot	=ui->spinBoxSearchDot		->value();

	ControlRememberer::SetValue(ui->doubleSpinBoxThreShape ,ui->doubleSpinBoxThreShape->value());
	ControlRememberer::SetValue(ui->doubleSpinBoxThreColor ,ui->doubleSpinBoxThreColor->value());
	ControlRememberer::SetValue(ui->spinBoxSearchDot		,ui->spinBoxSearchDot->value());

	done(2);
}

void SelectShapeTypeDialog::on_pushButtonCancel_clicked()
{
	done(-1);
}
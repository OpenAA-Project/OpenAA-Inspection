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

#include "PropertyGerberFastFormResource.h"
#include "EditShearDialog.h"
#include "ui_EditShearDialog.h"
#include "XRememberer.h"

EditShearDialog::EditShearDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditShearDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->doubleSpinBoxShear	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxShear,0));
	ui->radioButtonXDir		->setChecked(ControlRememberer::GetBool(ui->radioButtonXDir));

	InstallOperationLog(this);
}

EditShearDialog::~EditShearDialog()
{
    delete ui;
}

void EditShearDialog::on_pushButtonOK_clicked()
{
	Shear	=ui->doubleSpinBoxShear	->value();
	XMode	=ui->radioButtonXDir	->isChecked();
	ControlRememberer::SetValue(ui->doubleSpinBoxShear	,ui->doubleSpinBoxShear->value());
	ControlRememberer::SetValue(ui->radioButtonXDir		,ui->radioButtonXDir->isChecked());
	done(true);
}

void EditShearDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
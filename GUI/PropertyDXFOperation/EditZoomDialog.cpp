/*
 * Copyright (C) 2025
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

#include "PropertyDXFOperationResource.h"
#include "EditZoomDialog.h"
#include "ui_EditZoomDialog.h"
#include "XRememberer.h"

EditZoomDialog::EditZoomDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditZoomDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->doubleSpinBoxXZoomDir	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxXZoomDir,0));
	ui->doubleSpinBoxYZoomDir	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxYZoomDir,0));

	InstallOperationLog(this);
}

EditZoomDialog::~EditZoomDialog()
{
    delete ui;
}

void EditZoomDialog::on_pushButtonOK_clicked()
{
	XZoomDir		=ui->doubleSpinBoxXZoomDir	->value();
	YZoomDir		=ui->doubleSpinBoxYZoomDir	->value();
	ControlRememberer::SetValue(ui->doubleSpinBoxXZoomDir ,ui->doubleSpinBoxXZoomDir->value());
	ControlRememberer::SetValue(ui->doubleSpinBoxYZoomDir ,ui->doubleSpinBoxYZoomDir->value());
	done(true);
}

void EditZoomDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
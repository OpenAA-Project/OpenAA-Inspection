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
#include "EditRotateDialog.h"
#include "ui_EditRotateDialog.h"
#include "XRememberer.h"

EditRotateDialog::EditRotateDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EditRotateDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	ui->doubleSpinBoxAngle	->setValue(ControlRememberer::GetDouble(ui->doubleSpinBoxAngle,0));

	InstallOperationLog(this);
}

EditRotateDialog::~EditRotateDialog()
{
    delete ui;
}

void EditRotateDialog::on_pushButtonOK_clicked()
{
	Angle	=360-ui->doubleSpinBoxAngle	->value();
	ControlRememberer::SetValue(ui->doubleSpinBoxAngle ,ui->doubleSpinBoxAngle->value());
	done(true);
}

void EditRotateDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditRotateDialog::on_pushButton90_clicked()
{
	Angle	=270;
	done(true);
}

void EditRotateDialog::on_pushButton180_clicked()
{
	Angle	=180;
	done(true);
}

void EditRotateDialog::on_pushButton270_clicked()
{
	Angle	=90;
	done(true);
}
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

#include "ArcDialog.h"
#include "ui_ArcDialog.h"

ArcDialog::ArcDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::ArcDialog)
{
    ui->setupUi(this);
	//setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

ArcDialog::~ArcDialog()
{
    delete ui;
}

void ArcDialog::on_pushButtonOK_clicked()
{
	Cx	=ui->spinBoxCx->value();
	Cy	=ui->spinBoxCy->value();
	Rx	=ui->spinBoxRx->value();
	Ry	=ui->spinBoxRy->value();
	StartS	=ui->doubleSpinBoxStartS->value();
	EndS	=ui->doubleSpinBoxEndS->value();
	done(true);
}

void ArcDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
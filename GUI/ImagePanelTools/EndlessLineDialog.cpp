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

#include "EndlessLineDialog.h"
#include "ui_EndlessLineDialog.h"

EndlessLineDialog::EndlessLineDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::EndlessLineDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	InstallOperationLog(this);
}

EndlessLineDialog::~EndlessLineDialog()
{
    delete ui;
}

void EndlessLineDialog::on_pushButtonOK_clicked()
{
	x=ui->spinBoxX->value();
	y=ui->spinBoxY->value();
	S=ui->doubleSpinBox->value();
	done(true);
}

void EndlessLineDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
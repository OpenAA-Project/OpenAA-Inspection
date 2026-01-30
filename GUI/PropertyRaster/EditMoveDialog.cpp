/*
 * Copyright (C) 2026
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

#include "PropertyRasterResource.h"
#include "EditMoveDialog.h"
#include "ui_EditMoveDialog.h"
#include "XRememberer.h"

EditMoveDialog::EditMoveDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditMoveDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	RestoreForm(this);

	InstallOperationLog(this);
}

EditMoveDialog::~EditMoveDialog()
{
    delete ui;
}

void EditMoveDialog::on_pushButtonOK_clicked()
{
	XDir		=ui->doubleSpinBoxXDir	->value();
	YDir		=ui->doubleSpinBoxYDir	->value();
	PixelMode	=ui->radioButtonPixel	->isChecked();
	SaveForm(this);
	done(true);
}

void EditMoveDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
/*
 * Copyright (C) 2017
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
#include "InputEchingFactorDialog.h"
#include "ui_InputEchingFactorDialog.h"

InputEchingFactorDialog::InputEchingFactorDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::InputEchingFactorDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	InstallOperationLog(this);
}

InputEchingFactorDialog::~InputEchingFactorDialog()
{
    delete ui;
}

void InputEchingFactorDialog::on_pushButtonOK_clicked()
{
	ConerR	=ui->doubleSpinBoxCornerR->value();
	done(true);
}

void InputEchingFactorDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
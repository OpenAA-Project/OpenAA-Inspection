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

#include "PropertySwitchPhaseResource.h"
#include "InputThresholdDialog.h"
#include "ui_InputThresholdDialog.h"

InputThresholdDialog::InputThresholdDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::InputThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
}

InputThresholdDialog::~InputThresholdDialog()
{
    delete ui;
}

void	InputThresholdDialog::Initialize(int searchdot)
{
	SearchDot=searchdot;
	ui->spinBoxSearchDot->setValue(SearchDot);
}

void InputThresholdDialog::on_pushButtonOK_clicked()
{
	SearchDot	=ui->spinBoxSearchDot->value();
	done(true);
}

void InputThresholdDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
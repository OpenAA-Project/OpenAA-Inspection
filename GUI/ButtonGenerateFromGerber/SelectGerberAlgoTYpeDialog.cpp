/*
 * Copyright (C) 2019
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

#include "SelectGerberAlgoTYpeDialog.h"
#include "ui_SelectGerberAlgoTYpeDialog.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"

SelectGerberAlgoTYpeDialog::SelectGerberAlgoTYpeDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectGerberAlgoTYpeDialog)
{
    ui->setupUi(this);

	GerberAlgoType=-1;

	InstallOperationLog(this);
}

SelectGerberAlgoTYpeDialog::~SelectGerberAlgoTYpeDialog()
{
    delete ui;
}

void SelectGerberAlgoTYpeDialog::on_pushButtonOK_clicked()
{
	if(ui->checkBoxMakeAlgoShiftable->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromShiftable;
	}
	if(ui->checkBoxMakeAlgoSeparate->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromStable;
	}
	if(ui->checkBoxMakeAlgoEnlarge->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromEnlarge;
	}
	if(ui->checkBoxMakeAlgoShrinked->isChecked()==true){
		GerberAlgoType	=AlgoGenerationalLine::_GenFromShrinked;
	}
	done(true);
}

void SelectGerberAlgoTYpeDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
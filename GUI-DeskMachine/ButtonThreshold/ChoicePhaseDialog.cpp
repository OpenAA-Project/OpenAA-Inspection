/*
 * Copyright (C) 2014
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

#include "ChoicePhaseDialog.h"
#include "ui_ChoicePhaseDialog.h"

//ChoicePhaseDialog::ChoicePhaseDialog(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::ChoicePhaseDialog)
ChoicePhaseDialog::ChoicePhaseDialog(ChosenPhase *chosenPhase,LayersBase *LBase,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoicePhaseDialog)
{
    ui->setupUi(this);
	_LBase = LBase;
	_isQuit = true;
	_chosenPhase = chosenPhase;
}

ChoicePhaseDialog::~ChoicePhaseDialog()
{
    delete ui;
}

void ChoicePhaseDialog::on_pbFront_clicked()
{
	_isQuit = false;
	_chosenPhase->setPhaseNumber(0);
	//_LBase->TF_SetCurrentScanPhaseNumber(0);
	close();
}

void ChoicePhaseDialog::on_pbBack_clicked()
{
	_isQuit = false;
	_chosenPhase->setPhaseNumber(1);
	//_LBase->TF_SetCurrentScanPhaseNumber(1);
	close();
}

void ChoicePhaseDialog::on_pbClose_clicked()
{
	close();
}
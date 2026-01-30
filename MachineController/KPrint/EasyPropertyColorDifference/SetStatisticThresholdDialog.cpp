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

#include "EasyPropertyColorDifferenceResource.h"
#include "SetStatisticThresholdDialog.h"
#include "ui_SetStatisticThresholdDialog.h"
#include "InputPanelDialog.h"

SetStatisticThresholdDialog::SetStatisticThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetStatisticThresholdDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
}

SetStatisticThresholdDialog::~SetStatisticThresholdDialog()
{
    delete ui;
}

void SetStatisticThresholdDialog::on_pushButtonSet_clicked()
{
	SigmaH	=ui->doubleSpinBoxSigmaH->value();
	SigmaS	=ui->doubleSpinBoxSigmaS->value();
	SigmaV	=ui->doubleSpinBoxSigmaV->value();
	done(true);
}

void SetStatisticThresholdDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SetStatisticThresholdDialog::on_pushButtonPanelH_clicked()
{
	InputPanelDialog	D(IPD_Number,QString::number(ui->doubleSpinBoxSigmaH->value(),'f',3));
	if(D.exec()==true){
		ui->doubleSpinBoxSigmaH->setValue(D.GetResult().toDouble());
	}
}

void SetStatisticThresholdDialog::on_pushButtonPanelS_clicked()
{
	InputPanelDialog	D(IPD_Number,QString::number(ui->doubleSpinBoxSigmaS->value(),'f',3));
	if(D.exec()==true){
		ui->doubleSpinBoxSigmaS->setValue(D.GetResult().toDouble());
	}
}

void SetStatisticThresholdDialog::on_pushButtonPanelV_clicked()
{
	InputPanelDialog	D(IPD_Number,QString::number(ui->doubleSpinBoxSigmaV->value(),'f',3));
	if(D.exec()==true){
		ui->doubleSpinBoxSigmaV->setValue(D.GetResult().toDouble());
	}
}
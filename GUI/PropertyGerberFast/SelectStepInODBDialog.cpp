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

#include "PropertyGerberFastFormResource.h"
#include "SelectStepInODBDialog.h"
#include "ui_SelectStepInODBDialog.h"

SelectStepInODBDialog::SelectStepInODBDialog(LayersBase *base, ODBStepContainer &stepdata,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectStepInODBDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	StepData=stepdata;

	ui->tableWidget	->setColumnWidth(0,ui->tableWidget->width()-24);
	ui->tableWidget	->setRowCount(StepData.GetCount());
	int	Row=0;
	for(ODBStepList *L=StepData.GetFirst();L!=NULL;L=L->GetNext()){
		::SetDataToTableCheckable(ui->tableWidget,0,Row ,L->Name,L->Usage);
		Row++;
	}

	InstallOperationLog(this);
}

SelectStepInODBDialog::~SelectStepInODBDialog()
{
    delete ui;
}

void SelectStepInODBDialog::on_pushButtonOK_clicked()
{
	int	Row=0;
	for(ODBStepList *L=StepData.GetFirst();L!=NULL;L=L->GetNext()){
		L->Usage=::GetCheckedFromTable(ui->tableWidget,0,Row);
		Row++;
	}
	done(true);
}

void SelectStepInODBDialog::on_pushButtonClose_clicked()
{
	done(false);
}
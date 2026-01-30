/*
 * Copyright (C) 2012
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

#include "ShowConnectionInfoForm.h"
#include "ui_ShowConnectionInfoForm.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"

ShowConnectionInfoForm::ShowConnectionInfoForm(GlueRunner *G ,QWidget *parent) :
    QDialog(parent),
	Glue(G),
    ui(new Ui::ShowConnectionInfoForm)
{
    ui->setupUi(this);
	if(Glue->From()!=NULL){
		RunnerObject	*P=Glue->From()->GetParent();
		QString	DLLRoot,DLLName;
		P->GetRootName(DLLRoot,DLLName);
		ui->lineEditDLLRootFrom->setText(DLLRoot);
		ui->lineEditDLLNameFrom->setText(DLLName);
		ui->lineEditUniqueNameFrom->setText(P->GetUniqueName());
		ui->lineEditConnectionFrom->setText(Glue->From()->GetName());
	}
	if(Glue->To()!=NULL){
		RunnerObject	*P=Glue->To()->GetParent();
		QString	DLLRoot,DLLName;
		P->GetRootName(DLLRoot,DLLName);
		ui->lineEditDLLRootTo->setText(DLLRoot);
		ui->lineEditDLLNameTo->setText(DLLName);
		ui->lineEditUniqueNameTo->setText(P->GetUniqueName());
		ui->lineEditConnectionTo->setText(Glue->To()->GetName());
	}
}

ShowConnectionInfoForm::~ShowConnectionInfoForm()
{
    delete ui;
}

void ShowConnectionInfoForm::on_pushButtonOK_clicked()
{
	done(true);
}

void ShowConnectionInfoForm::on_pushButtonDelete_clicked()
{
	Glue->GetRMap()->RemoveGlue(Glue);
	done(true);
}
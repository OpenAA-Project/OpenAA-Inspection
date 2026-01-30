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

#include "NewProjectForm.h"
#include "ui_NewProjectForm.h"

NewProjectForm::NewProjectForm(const QString &ProjName ,QWidget *parent) :
    QDialog(parent)
	,ProjectName(ProjName)
    ,ui(new Ui::NewProjectForm)
{
    ui->setupUi(this);
	ui->lineEditProjectName->setText(ProjectName);
	if(ProjName==/**/""){
		ui->pushButtonDelete->setVisible(false);
	}
	else{
		ui->pushButtonDelete->setVisible(true);
	}
}

NewProjectForm::~NewProjectForm()
{
    delete ui;
}

void NewProjectForm::on_pushButtonOK_clicked()
{
	ProjectName	=ui->lineEditProjectName->text();
	done(true);
}

void NewProjectForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void NewProjectForm::on_pushButtonDelete_clicked()
{
	done(1000);
}
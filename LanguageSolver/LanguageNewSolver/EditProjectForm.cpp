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

#include "EditProjectForm.h"
#include "ui_EditProjectForm.h"
#include <QFileDialog>

EditProjectForm::EditProjectForm(LSProjectItem *a,QWidget *parent) :
    QDialog(parent)
	,Project(a)
    ,ui(new Ui::EditProjectForm)
{
    ui->setupUi(this);

	ui->EditFolderReference	->setText(Project->ReferenceFolder);
	ui->EditProjectName		->setText(Project->ProjectItemName);

	if(Project->ProjectItemName==""){
		ui->pushButtonDelete->setVisible(false);
	}
	else{
		ui->pushButtonDelete->setVisible(true);
	}
}

EditProjectForm::~EditProjectForm()
{
    delete ui;
}

void EditProjectForm::on_pushButtonFolderReference_clicked()
{
	QString dir = QFileDialog::getExistingDirectory(this, tr("Directory"));
	if(dir.isEmpty()==false){
		QDir	Dir(QDir::currentPath ());
		QFileInfo	Info(dir);
		ui->EditProjectName->setText(Info.baseName());
		ui->EditFolderReference->setText(Dir.relativeFilePath(dir));
	}
}

void EditProjectForm::on_pushButtonOK_clicked()
{
	Project->ReferenceFolder=ui->EditFolderReference	->text();
	Project->ProjectItemName=ui->EditProjectName		->text();
	done(true);
}

void EditProjectForm::on_pushButtonDelete_clicked()
{
	done(1000);
}

void EditProjectForm::on_pushButtonCancel_clicked()
{
	done(false);
}
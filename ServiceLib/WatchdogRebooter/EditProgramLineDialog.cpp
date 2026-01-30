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

#include "EditProgramLineDialog.h"
#include <QFileDialog>
#include "ui_EditProgramLineDialog.h"

EditProgramLineDialog::EditProgramLineDialog(QWidget *parent) :
    QDialog(parent)
    ,Current(NULL)
    ,ui(new Ui::EditProgramLineDialog)
{
    ui->setupUi(this);
}

EditProgramLineDialog::~EditProgramLineDialog()
{
    delete ui;
}

void	EditProgramLineDialog::showEvent ( QShowEvent * event )
{
	ui->lineEditPathFileName	->setText(Current.PathFileName);
	ui->lineEditArmuments		->setText(Current.Arguments);
	ui->lineEditWorkingPath		->setText(Current.WorkingPath);
	ui->spinBoxWatchTerm		->setValue(Current.WatchTerm);
}

void EditProgramLineDialog::on_pushButtonOK_clicked()
{
	Current.PathFileName	=ui->lineEditPathFileName	->text();
	Current.Arguments		=ui->lineEditArmuments		->text();
	Current.WorkingPath		=ui->lineEditWorkingPath	->text();
	Current.WatchTerm		=ui->spinBoxWatchTerm		->value();

	accept();
}

void EditProgramLineDialog::on_pushButtonCancel_clicked()
{
	reject();
}

void EditProgramLineDialog::on_pushButtonSelectPathFile_clicked()
{
    QString FileName=QFileDialog::getOpenFileName(NULL,"Program file name");
    if(FileName.isEmpty()==false){
        ui->lineEditPathFileName	->setText(FileName);
    }
}

void EditProgramLineDialog::on_pushButtonSelectWorkingPath_clicked()
{
    QString PathName=QFileDialog::getExistingDirectory(NULL,"Working directory");
    if(PathName.isEmpty()==false){
        ui->lineEditWorkingPath	->setText(PathName);
    }
}
/*
 * Copyright (C) 2021
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

#include "SelectFileOperationDialog.h"
#include "ui_SelectFileOperationDialog.h"
#include <QFileDialog>

SelectFileOperationDialog::SelectFileOperationDialog(DiskFileInfo *data ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFileOperationDialog)
{
    ui->setupUi(this);
	Data=*data;
	ui->lineEditPCName	->setText(Data.PCName);
	ui->lineEditPath	->setText(Data.Path);
	ui->lineEditFileName->setText(Data.FileName);
}

SelectFileOperationDialog::~SelectFileOperationDialog()
{
    delete ui;
}

void SelectFileOperationDialog::on_pushButtonDelete_clicked()
{
	done(2);
}

void SelectFileOperationDialog::on_pushButtonSelectDestination_clicked()
{
	DestPath=QFileDialog::getExistingDirectory(NULL,"Destination path");
	ui->lineEditDestination	->setText(DestPath);
}

void SelectFileOperationDialog::on_pushButtonMoveStart_clicked()
{
	DestPath	=ui->lineEditDestination	->text();
	if(DestPath.isEmpty()==true)
		return;
	done(1);
}

void SelectFileOperationDialog::on_pushButtonClose_clicked()
{
	done(0);
}
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

#include "AddExcludedFileDialog.h"
#include <QFileDialog>
#include "ui_AddExcludedFileDialog.h"

AddExcludedFileDialog::AddExcludedFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddExcludedFileDialog)
{
    ui->setupUi(this);
}

AddExcludedFileDialog::~AddExcludedFileDialog()
{
    delete ui;
}

void AddExcludedFileDialog::on_pushButtonOK_clicked()
{
	FileName	=ui->lineEditFileName->text();
	done(true);
}

void AddExcludedFileDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddExcludedFileDialog::on_pushButtonDialog_clicked()
{
	QString	f=QFileDialog::getOpenFileName(NULL,"Add excluded file","File name to be excluded");
	if(f.isNull()==false){
		ui->lineEditFileName->setText(f);
	}
}
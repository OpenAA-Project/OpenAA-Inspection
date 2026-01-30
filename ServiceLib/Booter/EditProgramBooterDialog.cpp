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

#include "EditProgramBooterDialog.h"
#include "ui_EditProgramBooterDialog.h"
#include <QFileDialog>

EditProgramBooterDialog::EditProgramBooterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProgramBooterDialog)
{
    ui->setupUi(this);
}

EditProgramBooterDialog::~EditProgramBooterDialog()
{
    delete ui;
}

void	EditProgramBooterDialog::Initial(ExecuteApplicationList &src)
{
	ui->lineEditProgram		->setText(src.Program);
	ui->lineEditParameter	->setText(src.Parameter);
}

void EditProgramBooterDialog::on_pushButtonFile_clicked()
{
	QString Txt=QFileDialog::getOpenFileName ( NULL, "Program file", QString()
											, "Exe file (*.exe);;All file (*.*)");
	if(Txt.isEmpty()==false){
		ui->lineEditProgram->setText(Txt);
	}
}

void EditProgramBooterDialog::on_pushButtonAdd_clicked()
{
	Program		=ui->lineEditProgram	->text();
	Parameter	=ui->lineEditParameter	->text();
	done(1);
}

void EditProgramBooterDialog::on_pushButtonEdit_clicked()
{
	Program		=ui->lineEditProgram	->text();
	Parameter	=ui->lineEditParameter	->text();
	done(2);
}

void EditProgramBooterDialog::on_pushButtonCancel_clicked()
{
	done(-1);
}
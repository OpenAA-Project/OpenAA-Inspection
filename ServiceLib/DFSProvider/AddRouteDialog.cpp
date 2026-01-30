/*
 * Copyright (C) 2016
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

#include "AddRouteDialog.h"
#include "ui_AddRouteDialog.h"
#include <QFileDialog>

AddRouteDialog::AddRouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRouteDialog)
{
    ui->setupUi(this);
}

AddRouteDialog::~AddRouteDialog()
{
    delete ui;
}
void	AddRouteDialog::Initial(PathClass &d)
{
	Path	=d.Path;
	Priority=d.Priority;
	ui->lineEditPath		->setText(d.Path);
	ui->spinBoxPriority		->setValue(d.Priority);
	ui->lineEditNetworkPath	->setText(d.NetworkPath);
	ui->lineEditDFSFilterDLLFileName	->setText(d.DFSFilterDLLFileName);
	ui->lineEditDFSFilterParameter		->setText(d.DFSFilterParameter);
}

void AddRouteDialog::on_pushButtonAdd_clicked()
{
	Path				=ui->lineEditPath					->text();
	Priority			=ui->spinBoxPriority				->value();
	NetworkPath			=ui->lineEditNetworkPath			->text();
	DFSFilterDLLFileName=ui->lineEditDFSFilterDLLFileName	->text();
	DFSFilterParameter	=ui->lineEditDFSFilterParameter		->text();

	done(true);
}

void AddRouteDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddRouteDialog::on_pushButtonSearchDLL_clicked()
{
	QString	DLLFileName=QFileDialog::getOpenFileName ( NULL
													, QString("Search DFSFilterDLL")
													, QString()
													, QString("DLL(*.DLL);;All files(*.*)"));
	if(DLLFileName.isEmpty()==false){
		QString	RelativeFileName=QDir::current ().relativeFilePath(DLLFileName);
		ui->lineEditDFSFilterDLLFileName	->setText(RelativeFileName);
	}
}
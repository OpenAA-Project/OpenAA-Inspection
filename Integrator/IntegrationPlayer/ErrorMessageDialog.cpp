/*
 * Copyright (C) 2019
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

#include "ErrorMessageDialog.h"
#include "ui_ErrorMessageDialog.h"
#include "XGeneralFunc.h"

ErrorMessageDialog::ErrorMessageDialog(NPListPack<ErrorInfoList> &Errors ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ErrorMessageDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth ( 0, 60);
	ui->tableWidget->setColumnWidth ( 1, 300);

	int	RCount=0;
	for(ErrorInfoList *e=Errors.GetFirst();e!=NULL;e=e->GetNext()){
		RCount+=e->Messages.count();
	}
	ui->tableWidget->setRowCount(RCount);
	int	Row=0;
	for(ErrorInfoList *e=Errors.GetFirst();e!=NULL;e=e->GetNext()){
		for(int i=0;i<e->Messages.count();i++){
			::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(e->Page));
			::SetDataToTable(ui->tableWidget ,1,Row ,e->Messages[i]);
			Row++;
		}
	}
}

ErrorMessageDialog::~ErrorMessageDialog()
{
    delete ui;
}

void ErrorMessageDialog::on_pushButtonOK_clicked()
{
    close();
}
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

#include "SelectChangeableDialog.h"
#include "XGeneralFunc.h"
#include "ui_SelectChangeableDialog.h"
#include "CameraSharer.h"

SelectChangeableDialog::SelectChangeableDialog(CameraSharer *p,QWidget *parent) :
    QDialog(parent)
	,Parent(p)
    ,ui(new Ui::SelectChangeableDialog)
{
    ui->setupUi(this);

	ui->tableWidget->setColumnWidth(0,100);
	ui->tableWidget->setColumnWidth(1,40);
	ui->tableWidget->setRowCount(Parent->CountOfShare);

	for(int row=0;row<Parent->CountOfShare;row++){
		if(row<Parent->ButtonNames.count()){
			::SetDataToTable(ui->tableWidget,0,row ,Parent->ButtonNames[row] ,Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
		}
		else{
			::SetDataToTable(ui->tableWidget,0,row ,QString("Cam")+QString::number(row+1) ,Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled);
		}
		::SetDataToTableCheckable(ui->tableWidget ,1,row ,/**/"" ,Parent->VisibleButton[row]);
	}
}

SelectChangeableDialog::~SelectChangeableDialog()
{
    delete ui;
}

void SelectChangeableDialog::on_pushButtonOK_clicked()
{
	Parent->ButtonNames.clear();
	for(int row=0;row<Parent->CountOfShare;row++){
		Parent->ButtonNames.append(GetDataToTable(ui->tableWidget,0,row));
		Parent->VisibleButton.GetItem(row)->SetValue(GetCheckedFromTable(ui->tableWidget,1,row));
	}
	done(true);
}

void SelectChangeableDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
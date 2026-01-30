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

#include "CommonGUIDLLResource.h"
#include "SelectImagePathDialog.h"
#include "ui_SelectImagePathDialog.h"

SelectImagePathDialog::SelectImagePathDialog(const QStringList &_PathList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectImagePathDialog)
{
    ui->setupUi(this);
	PathList	=_PathList;
	ui->listWidgetPath->addItems(PathList);
}

SelectImagePathDialog::~SelectImagePathDialog()
{
    delete ui;
}

void SelectImagePathDialog::on_pushButtonOK_clicked()
{
	int	Row=ui->listWidgetPath->currentRow();
	if(Row<0){
		return;
	}
	SelectedPath=PathList[Row];
	done(true);
}

void SelectImagePathDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectImagePathDialog::on_listWidgetPath_doubleClicked(const QModelIndex &index)
{
	on_pushButtonOK_clicked();
}
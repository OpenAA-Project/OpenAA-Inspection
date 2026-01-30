/*
 * Copyright (C) 2017
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

#include "EditStringListDialog.h"
#include "ui_EditStringListDialog.h"

EditStringListDialog::EditStringListDialog(const QStringList &str,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditStringListDialog)
{
    ui->setupUi(this);

	Str=str;
	ui->listWidget->addItems(Str);
	for(int i=0;i<ui->listWidget->count();i++){
		ui->listWidget->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
	}
}

EditStringListDialog::~EditStringListDialog()
{
    delete ui;
}

void EditStringListDialog::on_buttonBox_accepted()
{
	Str.clear();
	for(int i=0;i<ui->listWidget->count();i++){
		Str.append(ui->listWidget->item(i)->text());
	}
	accept();
}

void EditStringListDialog::on_pushButtonAdd_clicked()
{
	ui->listWidget->addItem(/**/"--");
	int	i=ui->listWidget->count()-1;
	ui->listWidget->item(i)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
}

void EditStringListDialog::on_pushButtonSub_clicked()
{
	int	R=ui->listWidget->currentRow();
	if(R<0)
		return;
	ui->listWidget->removeItemWidget(ui->listWidget->item(R));
}
/*
 * Copyright (C) 2025
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

#include "TunableListDialog.h"
#include "ui_TunableListDialog.h"
#include "swap.h"

TunableListDialog::TunableListDialog(QStringList &mList,QWidget *parent) :
    QDialog(parent),MList(mList),
    ui(new Ui::TunableListDialog)
{
    ui->setupUi(this);
    ShowList();
}

TunableListDialog::~TunableListDialog()
{
    delete ui;
}

void TunableListDialog::ShowList(void)
{
    ui->listWidgetTunable->clear();
    for(int i=0;i<MList.count();i++){
        ui->listWidgetTunable->addItem(MList.value(i));
    }
}

void TunableListDialog::on_pushButtonUp_clicked()
{
    int	r=ui->listWidgetTunable->currentRow();
    if(r>0){
        Swap(MList,r,r-1);
        ShowList();
        ui->listWidgetTunable->setCurrentRow(r-1);
    }
}

void TunableListDialog::on_pushButtonDown_clicked()
{
    int	r=ui->listWidgetTunable->currentRow();
    if(r<MList.count()-1){
        Swap(MList,r,r+1);
        ShowList();
        ui->listWidgetTunable->setCurrentRow(r+1);
    }
}

void TunableListDialog::on_pushButtonClose_clicked()
{
    close();
}
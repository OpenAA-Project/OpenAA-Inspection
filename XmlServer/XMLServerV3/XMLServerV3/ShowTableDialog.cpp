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

#include "ShowTableDialog.h"
#include "ui_ShowTableDialog.h"
#include "XCommandServer.h"
#include "XMLServerV3.h"
#include "XMLConstruction.h"

ShowTableDialog::ShowTableDialog(XMLElementRoot *s ,XMLServerComm *ServerCommDataParent ,QWidget *parent) :
    QDialog(parent)
	,ServerCommData(ServerCommDataParent)
	,SRoot(s)
    ,ui(new Ui::ShowTableDialog)
{
    ui->setupUi(this);

	ui->lineEditTableName	->setText(SRoot->GetTableName());

	ui->listWidgetSharedClients	->clear();
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=ServerCommData->GetSClient(i);
		if(SData!=NULL){
			if(SData->IsDealingTable(s->GetTableName())==true){
				ui->listWidgetSharedClients	->addItem(SData->GetPeerIPAddress());
			}
		}
	}
}

ShowTableDialog::~ShowTableDialog()
{
    delete ui;
}

void ShowTableDialog::on_pushButtonSave_clicked()
{
	SRoot->TableReadLock();
	SRoot->SaveFile();
	SRoot->TableUnLock();
}

void ShowTableDialog::on_pushButtonRemove_clicked()
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=ServerCommData->GetSClient(i);
		if(SData!=NULL){
			if(SData->IsDealingTable(SRoot->GetTableName())==true){
				SData->RemoveClientOperation(SRoot->GetTableName());
			}
		}
	}
	ServerCommData->SaveAndRemove(SRoot->GetTableName());
}

void ShowTableDialog::on_pushButtonClose_clicked()
{
	close();
}
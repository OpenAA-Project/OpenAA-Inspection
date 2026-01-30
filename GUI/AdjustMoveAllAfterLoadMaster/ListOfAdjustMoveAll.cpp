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

#include "AdjustMoveAllAfterLoadMasterResource.h"
#include "ListOfAdjustMoveAll.h"
#include "ui_ListOfAdjustMoveAll.h"
#include "XYCross.h"
#include "XGeneralFunc.h"

ListOfAdjustMoveAll::ListOfAdjustMoveAll(AdjustMoveAllAfterLoadMaster *p ,QWidget *parent) :
    QDialog(parent)
	,LParent(p)
    ,ui(new Ui::ListOfAdjustMoveAll)
{
    ui->setupUi(this);

	MoveAllInMaster	*L=LParent->MoveXY.GetFirst();
	if(L!=NULL){
		ui->spinBoxMasterCode	->setValue(L->MasterCode);
		LastMasterCode	=L->MasterCode;
		ui->tableWidgetXY->setRowCount(L->GetCount());
		int	Row=0;
		for(XYClass	*a=L->XYClassContainer::GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidgetXY ,0 ,Row ,QString::number(a->x),Qt::ItemIsEditable);
			::SetDataToTable(ui->tableWidgetXY ,1 ,Row ,QString::number(a->y),Qt::ItemIsEditable);
			Row++;
		}
	}
	else{
		ui->spinBoxMasterCode	->setValue(-1);
		LastMasterCode	=-1;
		ui->tableWidgetXY->setRowCount(LParent->GetPageNumb());
	}
}

ListOfAdjustMoveAll::~ListOfAdjustMoveAll()
{
    delete ui;
}

void ListOfAdjustMoveAll::on_pushButtonSave_clicked()
{
	int	MasterCode=ui->spinBoxMasterCode	->value();
	MoveAllInMaster	*M=LParent->MoveXY.FindMasterData(MasterCode);
	if(M==NULL){
		M=new MoveAllInMaster();
		M->SetPageCount(LParent->GetPageNumb());
		LParent->MoveXY.AppendList(M);
		M->MasterCode=MasterCode;
	}
	LastMasterCode	=MasterCode;
	if(M!=NULL){
		for(int page=0;page<LParent->GetPageNumb();page++){
			QString	XStr=GetDataToTable(ui->tableWidgetXY ,0,page);
			QString	YStr=GetDataToTable(ui->tableWidgetXY ,1,page);
			bool	ok;
			(*M)[page]->x=XStr.toInt(&ok);
			if(ok==false)	continue;
			(*M)[page]->y=YStr.toInt(&ok);
			if(ok==false)	continue;
		}
	}
	LParent->SaveFile();
}

void ListOfAdjustMoveAll::on_pushButtonClose_clicked()
{
	close();
}

void ListOfAdjustMoveAll::on_pushButtonLoad_clicked()
{
	LParent->LoadFile();

	MoveAllInMaster	*L=LParent->MoveXY.GetFirst();
	if(L!=NULL){
		ui->spinBoxMasterCode	->setValue(L->MasterCode);
		LastMasterCode	=L->MasterCode;
		ui->tableWidgetXY->setRowCount(L->GetCount());
		int	Row=0;
		for(XYClass	*a=L->XYClassContainer::GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidgetXY ,0 ,Row ,QString::number(a->x),Qt::ItemIsEditable);
			::SetDataToTable(ui->tableWidgetXY ,1 ,Row ,QString::number(a->y),Qt::ItemIsEditable);
			Row++;
		}
	}
	else{
		ui->spinBoxMasterCode	->setValue(-1);
		LastMasterCode	=-1;
		ui->tableWidgetXY->setRowCount(LParent->GetPageNumb());
	}
}

void ListOfAdjustMoveAll::on_spinBoxMasterCode_valueChanged(int arg1)
{
	for(int page=0;page<LParent->GetPageNumb();page++){
		::SetDataToTable(ui->tableWidgetXY ,0 ,page ,QString::number(0),Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetXY ,1 ,page ,QString::number(0),Qt::ItemIsEditable);
	}
	int	MasterCode=ui->spinBoxMasterCode	->value();
	MoveAllInMaster	*M=LParent->MoveXY.FindMasterData(MasterCode);
	LastMasterCode	=MasterCode;
	if(M!=NULL){
		int	Row=0;
		for(XYClass	*a=M->XYClassContainer::GetFirst();a!=NULL;a=a->GetNext()){
			::SetDataToTable(ui->tableWidgetXY ,0 ,Row ,QString::number(a->x),Qt::ItemIsEditable);
			::SetDataToTable(ui->tableWidgetXY ,1 ,Row ,QString::number(a->y),Qt::ItemIsEditable);
			Row++;
		}
	}

}
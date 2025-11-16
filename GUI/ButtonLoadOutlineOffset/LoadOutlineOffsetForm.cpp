#include "ButtonLoadOutlineOffsetResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadOutlineOffsetForm\LoadOutlineOffsetForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XFileRegistry.h"
#include "LoadOutlineOffsetForm.h"

LoadOutlineOffsetForm::LoadOutlineOffsetForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	LBase=Base;

	//マシーンテーブル表示
	MFieldNames << tr(/**/"MACHINEID") << tr(/**/"NAME") << tr(/**/"REMARK");
	ui.twMachineList->setColumnCount(MFieldNames.count());
	ui.twMachineList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twMachineList->setHorizontalHeaderLabels(MFieldNames);
	ui.twMachineList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	//MACHINEテーブル一覧の表示
	QSqlQuery query(/**/"SELECT MACHINEID,NAME,REMARK from MACHINE order by MACHINEID" ,Base->GetDatabase());
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMachineList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMachineList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMachineList->columnCount();Col++){
			ui.twMachineList->model()->setData(ui.twMachineList->model()->index(Row,Col),query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}

	//表示設定
	if(ui.twMachineList->rowCount()==0)
		ui.pbOK->setEnabled(false);
	else
		ui.twMachineList->setCurrentIndex(ui.twMachineList->model()->index(0,0));

	Base->InstallOperationLog(this);
}

LoadOutlineOffsetForm::~LoadOutlineOffsetForm()
{

}


void LoadOutlineOffsetForm::on_pbOK_clicked()
{
	int32 MachineID=ui.twMachineList->item(ui.twMachineList->currentIndex().row(),MFieldNames.indexOf(/**/"MACHINEID"))->text().toInt();
	//MACHINEテーブル一覧の表示
	bool	Ret=false;
	LBase->SetMachineID(MachineID);
	LBase->LoadOutlineOffsetForDatabase();
	LBase->BroadcastMachineID();
	LBase->DeliverOutlineOffset();

	accept();
}

void LoadOutlineOffsetForm::on_pbCancel_clicked()
{
	reject();
}
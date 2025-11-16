/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\WorkerSelectForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "WorkerSelectForm.h"
#include "QHeaderView"
#include "QSqlQuery"
#include "QSqlRecord"
#include "RepairBase.h"

#include "PasswordEventOperator.h"

WorkerSelectForm::WorkerSelectForm(RepairBase *ParentClass,QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbOK);


	PClass=ParentClass;

	//?i?A?O?e?[?u???\?|???X?g
	WFieldNames << tr(/**/"WORKERID") << tr(/**/"SECTION") << tr(/**/"NAME") << tr(/**/"REMARK") << tr(/**/"UPDATETIME");
	ui.twWorkerList->setColumnCount(WFieldNames.count());
//	ui.twWorkerList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twWorkerList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.twWorkerList->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.twWorkerList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.twWorkerList->setHorizontalHeaderLabels(WFieldNames);
//	ui.twWorkerList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	//SELECT????
	SelectData();

	//?V?O?i???E?X???b?g
	connect(ui.pbOK,						  SIGNAL(clicked()),								 this,SLOT(pbOKClicked()));
	connect(ui.twWorkerList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(WorkerListChanged(QModelIndex)));
	connect(ui.twWorkerList,				  SIGNAL(doubleClicked(QModelIndex)),				 this,SLOT(pbOKClicked()));

	//???u?t?H?[?J?X?i?I?d?j?I?Y?e
	if(ui.twWorkerList->selectedItems().count()==0 && ui.twWorkerList->rowCount()>0){
		ui.twWorkerList->setCurrentIndex(ui.twWorkerList->model()->index(0,0));
		ui.twWorkerList->setFocus();
	}
}

WorkerSelectForm::~WorkerSelectForm()
{
}

void WorkerSelectForm::pbOKClicked()
{
	//?i?A?O???X?g?I?d????
	int Row;
	if((Row=ui.twWorkerList->currentIndex().row())==-1){
//		QString sWID="-1";
		PClass->SetWorkerID(NULL);
		PClass->SetWorkerName(NULL);
	}
	else{
		PClass->SetWorkerID(&ui.twWorkerList->item(Row,WFieldNames.indexOf(/**/"WORKERID"))->text());
		PClass->SetWorkerName(&ui.twWorkerList->item(Row,WFieldNames.indexOf(/**/"NAME"))->text());
	}
	emit SignalClose();
	accept();
}

void WorkerSelectForm::WorkerListChanged(const QModelIndex &CIndex)
{
	ui.leID			->setText(ui.twWorkerList->item(CIndex.row(),0)->text());
	ui.leSection	->setText(ui.twWorkerList->item(CIndex.row(),1)->text());
	ui.leName		->setText(ui.twWorkerList->item(CIndex.row(),2)->text());
	ui.leRemark		->setText(ui.twWorkerList->item(CIndex.row(),3)->text());
	ui.leUpdateTime	->setText(ui.twWorkerList->item(CIndex.row(),4)->text());
}

void WorkerSelectForm::SelectData()
{
	QSqlQuery query(/**/"select WORKERID,SECTION,NAME,REMARK,UPDATETIME from WORKER where ALIVE!=0 order by WORKERID");
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twWorkerList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twWorkerList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twWorkerList->columnCount();Col++){
			PClass->SetDataToTable(ui.twWorkerList,Row,Col,query.value(query.record().indexOf(WFieldNames.at(Col))));
		}
		Row++;
	}
}

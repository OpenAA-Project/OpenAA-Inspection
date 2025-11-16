/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\LotSelectForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "RepairStationResource.h"
#include "LotSelectForm.h"
#include "QHeaderView"
#include "QSqlQuery"
#include "QSqlRecord"
#include "RepairBase.h"
#include "ProcessingForm.h"
#include "XGeneralFunc.h"

#include "PasswordEventOperator.h"

LotSelectForm::LotSelectForm(RepairBase *ParentClass,QWidget *parent)
    : QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbAllSelect);
	peo->addButton(ui.pbCancel);
	peo->addButton(ui.pbSearch);
	peo->addButton(ui.pbSelect);

	PClass=ParentClass;
	IsBoth=false;

	//???b?g?e?[?u???\?|???X?g
	LFieldNames << tr(/**/"LID") << tr(/**/"LNM") << tr(/**/"LBC");
	ui.twLotList->setColumnCount(LFieldNames.count());
    ui.twLotList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.twLotList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.twLotList->setSelectionMode(QAbstractItemView::SingleSelection);
    ui.twLotList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.twLotList->setHorizontalHeaderLabels(LFieldNames);
	ui.twLotList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
	ui.twLotList->horizontalHeader()->resizeSection (0,150);

	if(PClass->GetMasterID(PClass->SType)!=/**/""){
		//?}?X?^?[ID?E?I????E?e???b?g?e???d?a????E?A?\?|
		if(PClass->XMLLotGet(&PClass->GetMasterID(PClass->SType),&RetList,PClass->SType)){
//			LotProcessing->SetUpdate(50);
			QString strLotID,strLotName;
			int RetListSize=RetList.count();
			ui.twLotList->setRowCount(RetListSize);
			for(int Row=0,Cnt=RetListSize-1;Row<RetListSize;Row++,Cnt--){
				strLotID	=PClass->GetString(&QString(RetList.at(Cnt)),/**/"",/**/":").rightJustified(8,' ');
				strLotName	=PClass->GetString(&QString(RetList.at(Cnt)),/**/":",/**/"");
				for(int Col=0;Col<ui.twLotList->columnCount();Col++){
					if(LFieldNames.at(Col)==/**/"LID")
						PClass->SetDataToTable(ui.twLotList,Row,Col,strLotID);
					else if(LFieldNames.at(Col)==/**/"LNM")
						PClass->SetDataToTable(ui.twLotList,Row,Col,strLotName);
				}
			}
			int colLID=LFieldNames.indexOf(/**/"LID");
///			ui.twLotList->sortByColumn(colLID);
			for(int Row=0;Row<ui.twLotList->rowCount();Row++){
				QString sLID=ui.twLotList->item(Row,colLID)->text().remove(QChar(' '));
				PClass->SetDataToTable(ui.twLotList,Row,colLID,sLID);
			}
		}
	}

	//?V?O?i???E?X???b?g
	connect(ui.pbSelect,	SIGNAL(clicked()),					this,SLOT(pbSelectClicked()));
	connect(ui.pbAllSelect,	SIGNAL(clicked()),					this,SLOT(pbAllSelectClicked()));
	connect(ui.pbCancel,	SIGNAL(clicked()),					this,SLOT(pbCancelClicked()));
	connect(ui.twLotList,	SIGNAL(doubleClicked(QModelIndex)),	this,SLOT(pbSelectClicked()));
	connect(ui.leSearchLotName,SIGNAL(textChanged(QString)),	this,SLOT(leSearchLotNameTextChanged(QString)));
	connect(ui.pbSearch,	SIGNAL(clicked()),					this,SLOT(pbSearchClicked()));

	//???u?t?H?[?J?X?i?I?d?j?I?Y?e
	if(ui.twLotList->selectedItems().count()==0 && ui.twLotList->rowCount()>0){
		ui.twLotList->setCurrentIndex(ui.twLotList->model()->index(0,0));
		ui.twLotList->setFocus();
	}
//	LotProcessing->close();

	switch(PClass->SType){
		case 0:	ui.lineEdit->setText(LangSolver.GetString(LotSelectForm_LS,LID_458)/*"Front"*/);	break;
		case 1:	ui.lineEdit->setText(LangSolver.GetString(LotSelectForm_LS,LID_459)/*"Back"*/);	break;
	}
}

LotSelectForm::~LotSelectForm()
{
//	delete LotProcessing;
}

bool LotSelectForm::ExecSelectLot(QString LotName,QString LotID)
{
	//ロットリストからLotName、もしくはLotIDを検索する
	int column;
	QString SearchString;
	if(LotName.isEmpty()==false){
		column=LFieldNames.indexOf(/**/"LNM");
		SearchString=LotName;
	}
	else if(LotID.isEmpty()==false){
		column=LFieldNames.indexOf(/**/"LID");
		SearchString=LotID;
	}
	else{
		return false;
	}

	int RowCnt=ui.twLotList->rowCount();
	int row;
	for(row=0;row<RowCnt;row++){
		if(ui.twLotList->item(row,column)->text()==SearchString){
			break;
		}
	}
	if(row==RowCnt){
		return false;
	}
	ui.twLotList->selectRow(row);

	//実行
	pbSelectClicked();

	return true;
}

void LotSelectForm::pbSearchClicked()
{
	//Sort
	ui.twLotList->sortItems(1);

	//Search
	QString text=ui.leSearchLotName->text();
	int tCount=text.length();
	int RowCount=ui.twLotList->rowCount();
	for(int Row=0;Row<RowCount;Row++){
		if(ui.twLotList->item(Row,1)->text().left(tCount)==text){
			ui.twLotList->selectRow(Row);
			break;
		}
	}
}

void LotSelectForm::leSearchLotNameTextChanged(QString text)
{
	//Sort
	ui.twLotList->sortItems(1);

	//Search
//	QString text=ui.leSearchLotName->text();
	int tCount=text.length();
	int RowCount=ui.twLotList->rowCount();
	for(int Row=0;Row<RowCount;Row++){
		if(ui.twLotList->item(Row,1)->text().left(tCount)==text){
			ui.twLotList->selectRow(Row);
			break;
		}
	}
}

void LotSelectForm::pbSelectClicked()
{
	//ListNoData
	if(ui.twLotList->rowCount()==0){
		Result=false;
		reject();
		emit SignalClose();
		return;
	}

	//XML?T?[?o?A?I?U??}?m?F?i?U??}???e?I?e???I?e?U?O?f??E?A?A?U??}?j
	if(!PClass->XMLConnection(/**/"./XmlConnect-r.dat",PClass->SType)){
		Result=false;
		reject();
		emit SignalClose();
		return;
	}

	//??P????ｽ???b?g?d?I?n???e???I????
//	if(ui.twLotList->item(ui.twLotList->currentIndex().row(),LFieldNames.indexOf(/**/"LID"))->text()==PClass->GetLotID(PClass->SType)){
//		//Update
///		((RepairStation *)(PClass))->UpdateExec();
//		reject();
//	}

	if(ui.twLotList->item(ui.twLotList->currentIndex().row(),LFieldNames.indexOf(/**/"LID"))==NULL){
		Result=false;
		reject();
		emit SignalClose();
		return;
	}

	//???b?g???X?g?I?d????
	PClass->SetLotID	(PClass->SType,ui.twLotList->item(ui.twLotList->currentIndex().row(),LFieldNames.indexOf(/**/"LID"))->text());
	PClass->SetLotName	(PClass->SType,ui.twLotList->item(ui.twLotList->currentIndex().row(),LFieldNames.indexOf(/**/"LNM"))->text());

	//?}?X?^?[ID?A???b?gID?AClient_MasterStart
	if(!PClass->XMLMasterStart(&PClass->GetMasterID(PClass->SType),&PClass->GetLotID(PClass->SType),PClass->SType)){
		Result=false;
		reject();
		emit SignalClose();
		return;
	}

	RetList.clear();
	QString strQueryPCE=LangSolver.GetString(LotSelectForm_LS,LID_460)/*"PCE"*/;
	if(PClass->XMLSelect(&strQueryPCE.toLocal8Bit().data(),&RetList,PClass->SType)){
		PClass->SetRetPCEDataList(PClass->SType,&RetList);
	}

#ifdef DEBUG
	QString AAA;
	for(int i=0;i<PClass->GetRetPCEDataList(PClass->SType)->count();i++){
		AAA=PClass->GetRetPCEDataList(PClass->SType)->at(i);
		AAA=AAA;
	}
#endif

	//XML?T?[?o?c?c?f?[?^?dTagSelect
	RetList.clear();
	QString strQueryXML=/**/"IST";
	if(!PClass->XMLSelect(&strQueryXML.toLocal8Bit().data(),&RetList,PClass->SType)){
		Result=false;
		reject();
		emit SignalClose();
		return;
	}

	//???\?I??
	PClass->SetRetXMLDataList(PClass->SType,&RetList);

	if(PClass->SType==1){
		if(!PClass->XMLSelect(&strQueryXML.toLocal8Bit().data(),&RetList,0)){
			reject();
		}
		PClass->SetRetXMLDataList(0,&RetList);
	}

	//裏面のロットも読むかどうかの確認
	if(IsBoth==true){
		QMessageBox::StandardButton Btn=QMessageBox::information(this	,LangSolver.GetString(LotSelectForm_LS,LID_895/*"Message"*/)
																		,LangSolver.GetString(LotSelectForm_LS,LID_889)/*"Do you read back side Lot data?"*/
																		,QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
		if(Btn==QMessageBox::No){
			IsBoth=false;
		}
	}

	Result=true;
	emit SignalClose();
	accept();
}

void LotSelectForm::pbAllSelectClicked()
{
	//???b?g???X?g?I?d????
	PClass->SetLotID(PClass->SType,/**/"*");

	//XML?T?[?o?c?c?f?[?^?dTagSelect
	RetList.clear();
	QString strMQueryXML=QString(/**/"<MNM MID=")
						+QString('\"') 
						+ PClass->GetMasterID(PClass->SType) 
						+ QString('\"')+QString(/**/">");
	if(!PClass->XMLTagSelect(&strMQueryXML,&RetList,1,PClass->SType))
		reject();

	//???\?I??
	PClass->SetRetXMLDataList(PClass->SType,&RetList);

	Result=true;
	emit SignalClose();
	accept();
}

void LotSelectForm::pbCancelClicked()
{
	//?L?????Z??
	Result=false;
	emit SignalClose();
	reject();
}

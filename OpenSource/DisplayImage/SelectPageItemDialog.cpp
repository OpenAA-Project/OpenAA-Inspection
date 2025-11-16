/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectItemForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectItemForm.h"
#include "SelectPageItemDialog.h"
#include "ui_SelectPageItemDialog.h"
#include "XParamGlobal.h"
#include "XIntClass.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "XDataAlgorithm.h"

SelectPageItemDialog::SelectPageItemDialog(AlgorithmBase *Algo ,ListPageLayerIDLibNamePack &itemIDList ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Algo->GetLayersBase())
    ,ui(new Ui::SelectPageItemDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
	LangDISolver.SetUI(this);
	InstallOperationLog(this);

	ui->tableWidgetItem	->setColumnWidth(0,72);
	ui->tableWidgetItem	->setColumnWidth(0,72);
	ui->tableWidgetItem	->setColumnWidth(1,72);
	ui->tableWidgetItem	->setColumnWidth(2,72);
	ui->tableWidgetItem	->setColumnWidth(3,200);
	ui->tableWidgetItem	->setColumnWidth(4,185);

	int	Row=0;
	ItemIDList=itemIDList;
	LibIDNameContainer	LibIDStock;
	for(ListPageLayerIDLibName *d=itemIDList.GetFirst();d!=NULL;d=d->GetNext()){
		LibIDNameList	*s=LibIDStock.IsInclude(d->LibID);
		if(s==NULL){
			s=new LibIDNameList();
			s->LibID=d->LibID;
			LibIDStock.AppendList(s);
		}
	}
	for(LibIDNameList	*s=LibIDStock.GetFirst();s!=NULL;s=s->GetNext()){
		AlgorithmLibraryContainer	*pLib=Algo->GetLibraryContainer();
		if(pLib!=NULL){
			s->LibName=pLib->GetLibraryName(s->LibID);
		}
		else{
			s->LibName=/**/"--";
		}
	}	
	ui->tableWidgetItem->setRowCount(itemIDList.GetCount());
	for(ListPageLayerIDLibName *d=itemIDList.GetFirst();d!=NULL;d=d->GetNext()){
		::SetDataToTable(ui->tableWidgetItem ,0,Row ,QString::number(d->Page));
		::SetDataToTable(ui->tableWidgetItem ,1,Row ,QString::number(d->Layer));
		::SetDataToTable(ui->tableWidgetItem ,2,Row ,QString::number(d->ID));
		::SetDataToTable(ui->tableWidgetItem ,3,Row ,QString::number(d->LibID));
		//QString	LibName=Algo->GetLibraryContainer()->GetLibraryName(d->LibID);
		LibIDNameList	*s=LibIDStock.IsInclude(d->LibID);
		if(s!=NULL)
			::SetDataToTable(ui->tableWidgetItem ,4,Row ,s->LibName);
		else
			::SetDataToTable(ui->tableWidgetItem ,4,Row ,/**/"");
		::SetDataToTable(ui->tableWidgetItem ,5,Row ,d->ItemName);
		Row++;
	}
	if(Row>0){
		IntList Rows;
		Rows.Add(0);
		::SetSelectedRows(ui->tableWidgetItem ,Rows);
	}
}

SelectPageItemDialog::~SelectPageItemDialog()
{
    delete ui;
}

void SelectPageItemDialog::on_tableWidgetItem_clicked(const QModelIndex &index)
{
	DisplayImageWithAlgorithm	*P=dynamic_cast<DisplayImageWithAlgorithm *>(parent());
	if(P!=NULL){
		P->ClearActivattionItems();
		int	Row=ui->tableWidgetItem->currentRow();
		if(Row>=0){
			ListPageLayerIDLibName	*c=ItemIDList.GetItem(Row);
			if(c!=NULL){
				P->SetActivateItem(c->Page ,c->Layer, c->ID);
				P->Repaint();
			}
		}
	}	
}

void SelectPageItemDialog::on_tableWidgetItem_doubleClicked(const QModelIndex &index)
{
	on_ButtonOK_clicked();
}

void SelectPageItemDialog::on_ButtonOK_clicked()
{
	SelectedItems.RemoveAll();
	IntList Rows;
	::GetSelectedRows(ui->tableWidgetItem,Rows);
	for(IntClass *d=Rows.GetFirst();d!=NULL;d=d->GetNext()){
		ListPageLayerIDLibName	*c=ItemIDList.GetItem(d->GetValue());
		if(c!=NULL){
			SelectedItems.AppendList(new ListPageLayerID(c->Page,c->Layer,c->ID));
		}
	}
	done(true);
}

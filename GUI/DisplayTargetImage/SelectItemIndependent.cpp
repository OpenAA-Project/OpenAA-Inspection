/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayTargetImage\SelectItemIndependent.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayTargetImageResource.h"
#include "SelectItemIndependent.h"
#include "XAlgorithmDLL.h"
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataInLayer.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmLibrary.h"
#include "SelectResultAnalizerDialog.h"
#include "XResultAnalizer.h"

ResultAnalizerButton::ResultAnalizerButton (int row, SelectItemIndependent *Parent,QWidget * parent)
	:QPushButton(parent),Row(row)
{
	connect(this,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}
void	ResultAnalizerButton::SlotClicked()
{
	emit	SignalClicked(Row);
}

SelectItemIndependent::SelectItemIndependent(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	SetWidgetCenter(this);
	SelectedList=NULL;
	connect(ui.tableWidgetAlgorithm,SIGNAL(clicked(const QModelIndex &)),this,SLOT(on_tableWidgetAlgorithm_clicked(const QModelIndex &)));
	connect(ui.pushButtonOK		,SIGNAL(clicked())	,this,SLOT(OKButtonClicked		()));
	connect(ui.pushButtonCancel	,SIGNAL(clicked())	,this,SLOT(CancelButtonClicked	()));

	ui.tableWidgetAlgorithm->setColumnWidth (0,40);
	ui.tableWidgetAlgorithm->setColumnWidth (1,100);

	ui.tableWidgetItems->setColumnWidth (0,40);
	ui.tableWidgetItems->setColumnWidth (1,40);
	ui.tableWidgetItems->setColumnWidth (2,70);
	ui.tableWidgetItems->setColumnWidth (3,220);
	ui.tableWidgetItems->setColumnWidth (4,24);
	InstallOperationLog(this);
}

SelectItemIndependent::~SelectItemIndependent()
{

}

void	SelectItemIndependent::AddItem(AlgorithmItemIndependent *p)
{
	LogicDLL	*L=GetLayersBase()->GetAlgorithmDLL(p->AlgorithmRoot,p->AlgorithmName);
	if(L->CheckAlgorithmType(AlgorithmBit_TypeProcessing)==false
	&& L->CheckAlgorithmType(AlgorithmBit_TypePreProcessing)==false
	&& L->CheckAlgorithmType(AlgorithmBit_TypePreAlignment)==false
	&& L->CheckAlgorithmType(AlgorithmBit_TypeAlignment)==false)
		return;
	for(AlgorithmIndependentList *c=List.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->DLLRoot==p->AlgorithmRoot && c->DLLName==p->AlgorithmName){
			ItemIndependentList	*q=new ItemIndependentList();
			q->ID				=p->ItemID;
			q->LibID			=p->LibID;
			q->TypeInNoLib		=p->TypeInNoLib;
			q->ItemClassType	=p->ItemClassType;
			q->Page				=p->GlobalPage;
			q->Layer			=p->Layer;
			q->Error			=p->Result;
			q->TypeInNoLib		=p->TypeInNoLib;
			q->Point			=p;
			c->ItemList.AppendList(q);
			return;
		}
	}
	AlgorithmIndependentList	*cm=new AlgorithmIndependentList();
	cm->DLLRoot=p->AlgorithmRoot;
	cm->DLLName=p->AlgorithmName;

	ItemIndependentList	*qm=new ItemIndependentList();
	qm->ID				=p->ItemID;
	qm->LibID			=p->LibID;
	qm->ItemClassType	=p->ItemClassType;
	qm->Page			=p->GlobalPage;
	qm->Layer			=p->Layer;
	qm->Error			=p->Result;
	qm->TypeInNoLib		=p->TypeInNoLib;
	qm->Point			=p;
	cm->ItemList.AppendList(qm);

	List.AppendList(cm);
}

void	SelectItemIndependent::Show(void)
{
	for(AlgorithmIndependentList *a=List.GetFirst();a!=NULL;a=a->GetNext()){
		AlgorithmBase	*ap=GetLayersBase()->GetAlgorithmBase(a->DLLRoot,a->DLLName);
		if(ap!=NULL){
			AlgorithmLibraryContainer	*aLib=ap->GetLibraryContainer();
			if(aLib!=NULL){
				for(ItemIndependentList *item=a->ItemList.GetFirst();item!=NULL;item=item->GetNext()){
					item->LibName=aLib->GetLibraryName(item->LibID);
				}
			}
		}
	}

	ui.tableWidgetAlgorithm->setRowCount(List.GetNumber());
	int	N=0;
	for(AlgorithmIndependentList *a=List.GetFirst();a!=NULL;a=a->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidgetAlgorithm->item (N, 0);
		if(w==NULL)
			ui.tableWidgetAlgorithm->setItem(N,0,(w=new QTableWidgetItem()));

		w->setText(a->DLLRoot);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

		w=ui.tableWidgetAlgorithm->item (N, 1);
		if(w==NULL)
			ui.tableWidgetAlgorithm->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(a->DLLName);
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	ui.tableWidgetAlgorithm->selectRow (0);
	const QModelIndex	Dummy;
	on_tableWidgetAlgorithm_clicked(Dummy);
}

void	SelectItemIndependent::on_tableWidgetAlgorithm_clicked(const QModelIndex &)
{
	int	RIndex=ui.tableWidgetAlgorithm->currentRow();
	if(RIndex<0)
		return;
	int	CountResultAnalizer=GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetCount();
	if(CountResultAnalizer>0){
		ui.tableWidgetItems->setColumnCount(5);
		ui.tableWidgetItems->setColumnWidth (4,24);
	}
	else{
		ui.tableWidgetItems->setColumnCount(4);
	}
	AlgorithmIndependentList *a=List.GetItem(RIndex);
	ui.tableWidgetItems->setRowCount(a->ItemList.GetNumber());
	int	N=0;
	for(ItemIndependentList *c=a->ItemList.GetFirst();c!=NULL;c=c->GetNext(),N++){
		QTableWidgetItem *w;
		w=ui.tableWidgetItems->item (N, 0);
		if(w==NULL)
			ui.tableWidgetItems->setItem(N,0,(w=new QTableWidgetItem()));

		w->setText(QString::number(c->Page));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetTableColor(ui.tableWidgetItems ,0 ,N,(c->Error>=2)?Qt::red:Qt::white);

		w=ui.tableWidgetItems->item (N, 1);
		if(w==NULL)
			ui.tableWidgetItems->setItem(N,1,(w=new QTableWidgetItem()));
		w->setText(QString::number(c->Layer));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetTableColor(ui.tableWidgetItems ,1 ,N,(c->Error>=2)?Qt::red:Qt::white);

		w=ui.tableWidgetItems->item (N, 2);
		if(w==NULL)
			ui.tableWidgetItems->setItem(N,2,(w=new QTableWidgetItem()));
		w->setText(QString::number(c->ID));
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetTableColor(ui.tableWidgetItems ,2 ,N,(c->Error>=2)?Qt::red:Qt::white);

		w=ui.tableWidgetItems->item (N, 3);
		if(w==NULL)
			ui.tableWidgetItems->setItem(N,3,(w=new QTableWidgetItem()));
		if(c->LibID>=0){
			w->setText(c->LibName);
		}
		else{
			w->setText(c->TypeInNoLib);
		}
		w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetTableColor(ui.tableWidgetItems ,3 ,N,(c->Error>=2)?Qt::red:Qt::white);

		if(CountResultAnalizer>0){
			w=ui.tableWidgetItems->item (N, 4);
			if(w==NULL){
				ResultAnalizerButton	*b=new ResultAnalizerButton(N,this);
				connect(b,SIGNAL(SignalClicked(int)),this,SLOT(SlotResultAnalizerClicked(int)));
				ui.tableWidgetItems->setCellWidget(N,4,b);
			}
		}
	}
}

void	SelectItemIndependent::OKButtonClicked()
{
	int	RIndex=ui.tableWidgetAlgorithm->currentRow();
	if(RIndex<0){
		done ((int)false);
		return;
	}
	SelectedList=List.GetItem(RIndex);
	QList<QTableWidgetItem *>	SelList=ui.tableWidgetItems->selectedItems ();
	for(int i=0;i<SelList.count();i++){
		QTableWidgetItem	*k=SelList.value(i);
		if(k->column()==0){
			ItemIndependentList	*c=SelectedList->ItemList.GetItem(k->row());
			c->Selected=true;
		}
	}

	done ((int)true);
}
void	SelectItemIndependent::CancelButtonClicked()
{
	done ((int)false);
}

void SelectItemIndependent::on_tableWidgetItems_doubleClicked(const QModelIndex &index)
{
	OKButtonClicked();
}

void	SelectItemIndependent::SlotResultAnalizerClicked(int row)
{
	int	RIndex=ui.tableWidgetAlgorithm->currentRow();
	if(RIndex<0){
		done ((int)false);
		return;
	}
	AlgorithmIndependentList *a=List.GetItem(RIndex);
	if(a==NULL)
		return;
	ItemIndependentList *c=a->ItemList.GetItem(row);
	if(c==NULL)
		return;

	if(GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetCount()==1){
		ShowResultAnalizer(a,c,GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetFirst());
	}
	else if(GetLayersBase()->GetResultAnalizerItemBaseContainer()->GetCount()>1){
		SelectResultAnalizerDialog	D(GetLayersBase());
		if(D.exec()==(int)true){
			ShowResultAnalizer(a,c,D.Selected);
		}
	}
}

void	SelectItemIndependent::ShowResultAnalizer(AlgorithmIndependentList *a,ItemIndependentList *c
												,ResultAnalizerItemBase *R)
{
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(a->DLLRoot,a->DLLName);
	if(Ab==NULL)
		return;
	R->ShowResultDialogFunc(Ab,GetLayersBase()->GetCurrentPhase(),c->Page,c->Layer,c->ID);
}

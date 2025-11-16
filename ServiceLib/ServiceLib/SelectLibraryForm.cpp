/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibraryForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectLibraryForm.h"
#include "ui_SelectLibraryForm.h"
#include "LibFolderForm.h"
#include "XDataInLayer.h"


SelectLibraryForm::SelectLibraryForm(int libType ,LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibraryForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);
    LibType         =libType;
    SelectedLibID   =-1;

    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ui->tableWidgetLibList->setColumnWidth (0, 30);
    ui->tableWidgetLibList->setColumnWidth (1, 80);

    InstallOperationLog(this);
}

SelectLibraryForm::~SelectLibraryForm()
{
    delete ui;
}

void SelectLibraryForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
    on_pushButtonSelect_clicked();
}


void SelectLibraryForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}


void	SelectLibraryForm::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}
void SelectLibraryForm::on_pushButtonSelect_clicked()
{
    int	R=ui->tableWidgetLibList->currentRow();
    if(R<0)
        return;
    AlgorithmLibraryList	*d=LibIDList.GetItem(R);
    if(d!=NULL){
        SelectedLibID	=d->GetLibID();
        SelectedLibName	=d->GetLibName();
        emit	SignalClose();
    }
}

void SelectLibraryForm::on_pushButtonCancel_clicked()
{
    SelectedLibID	=-1;
    SelectedLibName	=/**/"";
    emit	SignalClose();
}

void	SelectLibraryForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ui->tableWidgetLibList->setRowCount(0);
    AlgorithmLibraryContainerForEnum		LibList(GetLayersBase());
    LibIDList.RemoveAll();
    LibList.EnumLibrary(GetLayersBase()->GetDatabase(),LibType,LibFolderID ,LibIDList);

    int	row=0;
    ui->tableWidgetLibList->setRowCount(LibIDList.GetNumber());
    for(AlgorithmLibraryList *a=LibIDList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetLibList->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetLibList->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetLibList->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectLibrariesForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectLibrariesForm.h"
#include "ui_SelectLibrariesForm.h"
#include "XDataInLayer.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XRememberer.h"

SelectLibrariesForm::SelectLibrariesForm(int libType ,LayersBase *Base,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectLibrariesForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(Base->GetLanguagePackageData(),Base->GetLanguageCode());
    LangDISolver.SetUI(this);
    InstallOperationLog(this);

    LibType=libType;

    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));

    ::SetColumnWidthInTable(ui->tableWidgetLibList ,0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetLibList ,1, 70);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList ,0, 30);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList ,1, 70);}

SelectLibrariesForm::~SelectLibrariesForm()
{
    delete ui;
}

void	SelectLibrariesForm::SetSelected(const AlgorithmLibraryListContainer &selectedList)
{
    SelectedList=selectedList;
    ShowSelectedList();
}
void	SelectLibrariesForm::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}

void	SelectLibrariesForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
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

void SelectLibrariesForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
    QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
    if(RIndex.isValid()==true){
        int	R=RIndex.row();
        AlgorithmLibraryList	*d=LibIDList.GetItem(R);
        if(d!=NULL){
            bool	ShowOnlyMode=false;
            for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
                if(*a==*d){
                    ShowOnlyMode=true;
                    break;
                }
            }
            if(ShowOnlyMode==false){
                AlgorithmLibraryList *as=new AlgorithmLibraryList(*d);
                SelectedList.AppendList(as);
            }
            ShowSelectedList();
        }
    }
}

void SelectLibrariesForm::on_tableWidgetSelectedList_doubleClicked(const QModelIndex &index)
{
    QModelIndex	RIndex=ui->tableWidgetSelectedList->currentIndex();
    if(RIndex.isValid()==true){
        int	R=RIndex.row();
        AlgorithmLibraryList	*d=SelectedList.GetItem(R);
        if(d!=NULL){
            SelectedList.RemoveList(d);
            delete	d;
            ShowSelectedList();
        }
    }
}

void SelectLibrariesForm::ShowSelectedList(void)
{
    int	row=0;
    ui->tableWidgetSelectedList->setRowCount(SelectedList.GetNumber());
    for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext(),row++){
        QTableWidgetItem *W;
        W=ui->tableWidgetSelectedList->item ( row, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetSelectedList->setItem ( row, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(QString::number(a->GetLibID()));
        W=ui->tableWidgetSelectedList->item ( row, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetSelectedList->setItem ( row, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(a->GetLibName());
    }
}
void SelectLibrariesForm::resizeEvent(QResizeEvent *event)
{
    ui->frameLibFolder      ->resize((width()-30)/2,(height()-20-ui->label_2->height())/2);
    pLibFolderForm  ->resize(ui->frameLibFolder->width(),ui->frameLibFolder->height());
    ui->tableWidgetLibList  ->setGeometry(10,(height()-20-ui->label_2->height())/2+20
                                         ,(width()-30)/2,(height()-20-ui->label_2->height())/2);
    ui->tableWidgetSelectedList->setGeometry((width()-30)/2+20,(height()-20-ui->label_2->height())/2+20
                                            ,(width()-30)/2,(height()-20-ui->label_2->height())/2);
    ui->label->setGeometry(ui->tableWidgetSelectedList->geometry().left()
                         , ui->tableWidgetSelectedList->geometry().top()-ui->label->height()-2
                         ,ui->tableWidgetSelectedList->width(),ui->label->height());
    ui->label_2 ->move(10,ui->tableWidgetLibList->geometry().bottom());
}

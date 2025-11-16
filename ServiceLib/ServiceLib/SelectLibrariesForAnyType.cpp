/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectLibrariesForAnyType.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectLibrariesForAnyType.h"
#include "ui_SelectLibrariesForAnyType.h"
#include "LibFolderForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLibraryType.h"
#include "XRememberer.h"

SelectLibrariesForAnyType::SelectLibrariesForAnyType(LayersBase *base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectLibrariesForAnyType)
{
    ui->setupUi(this);
    LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangLibSolver.SetUI(this);

    InitialMode =true;
    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ui->tableWidgetLibList->setColumnWidth (0, 30);
    ui->tableWidgetLibList->setColumnWidth (1, 80);
    ui->tableWidgetSelectedList->setColumnWidth (0, 30);
    ui->tableWidgetSelectedList->setColumnWidth (1, 80);
    SetLibTypeInComboBox();

    InitialMode=false;

    InstallOperationLog(this);
}

SelectLibrariesForAnyType::~SelectLibrariesForAnyType()
{
    delete ui;
}
void SelectLibrariesForAnyType::showEvent(QShowEvent *e)
{
    int	CLibType=ControlRememberer::GetInt(objectName()+/**/"\\SelectLibrariesForAnyType-LibType",-1);
    if(CLibType>=0){
        int Row=0;
        for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
            if(L->GetLibType()==CLibType){
                ui->comboBLibType->setCurrentIndex(Row);
                ShowFolder(CLibType);

                int	CLibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\SelectLibrariesForAnyType-LibFolderID",-1);
                if(CLibFolderID>=0){
                    IntListContainer	ItemNumber=ControlRememberer::GetIntListContainer(pLibFolderForm->GetTreeWidget());
                    ::SetSelectedItems(pLibFolderForm->GetTreeWidget(), ItemNumber);

                    QString	CLibFolderName=GetLayersBase()->GetLibFolderName(CLibFolderID);
                    SlotSelectLibFolder(CLibFolderID ,CLibFolderName);
                }
                break;
            }
        }
    }
}

void SelectLibrariesForAnyType::resizeEvent(QResizeEvent *event)
{
    int W2=(width()-4)/2;
    ui->comboBLibType   ->resize(W2,ui->comboBLibType->height());
    ui->frameLibFolder  ->resize(W2,ui->frameLibFolder->height());

    int L=height()  -ui->comboBLibType->height()
                    -ui->frameLibFolder->height()
                    -ui->label_2->height();
    ui->tableWidgetLibList->resize(W2,L);
    QRect   R=ui->label->geometry();
    ui->label->setGeometry(W2+4,R.top(),width()-W2-8,R.height());
    QRect   Q=ui->tableWidgetSelectedList->geometry();
    ui->tableWidgetSelectedList->setGeometry(W2+4,Q.top(),width()-W2-8,L);
    ui->label_2->move(0,height()-ui->label_2->height());

    ::SetColumnWidthInTable(ui->tableWidgetLibList,0, 25);
    ::SetColumnWidthInTable(ui->tableWidgetLibList,1, 75);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList,0, 25);
    ::SetColumnWidthInTable(ui->tableWidgetSelectedList,1, 75);
}

void SelectLibrariesForAnyType::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	SelectLibrariesForAnyType::SetSelected(AlgorithmLibraryListContainer &selectedList)
{
    SelectedList=selectedList;
    ShowSelectedList();
}
void	SelectLibrariesForAnyType::SetLibTypeInComboBox(void)
{
    ui->comboBLibType->clear();
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
        ui->comboBLibType->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
    }
}

void SelectLibrariesForAnyType::on_comboBLibType_currentIndexChanged(int)
{
    if(InitialMode==false){
        int	Index=ui->comboBLibType->currentIndex();
        LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetItem(Index);
        if(L==NULL)
            return;
        LibType=L->GetLibType();
        ShowFolder(L->GetLibType());
        //SelectedList.RemoveAll();
        LibIDList.RemoveAll();
        ui->tableWidgetLibList->setRowCount(0);
        ControlRememberer::SetValue(objectName()+/**/"\\SelectLibrariesForAnyType-LibType",LibType);
    }
}

void	SelectLibrariesForAnyType::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}

void	SelectLibrariesForAnyType::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ControlRememberer::SetValue(objectName()+/**/"\\SelectLibrariesForAnyType-LibFolderID",LibFolderID);
    
    IntListContainer ItemNumber;
    ::GetSelectedItems(pLibFolderForm->GetTreeWidget(), ItemNumber);
    ControlRememberer::SetValue(pLibFolderForm->GetTreeWidget() ,ItemNumber);

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



void SelectLibrariesForAnyType::on_tableWidgetLibList_doubleClicked(const QModelIndex &)
{
    QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
    if(RIndex.isValid()==false)
        return;
    int	R=RIndex.row();
    AlgorithmLibraryList	*d=LibIDList.GetItem(R);
    if(d!=NULL){
        bool	ModeAdd=true;
        for(AlgorithmLibraryList *a=SelectedList.GetFirst();a!=NULL;a=a->GetNext()){
            if(*a==*d){
                ModeAdd=false;
                break;
            }
        }
        if(ModeAdd==true){
            AlgorithmLibraryList *as=new AlgorithmLibraryList(*d);
            SelectedList.AppendList(as);
        }
        ShowSelectedList();
    }
}
void SelectLibrariesForAnyType::ShowSelectedList(void)
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

void SelectLibrariesForAnyType::on_tableWidgetSelectedList_doubleClicked(const QModelIndex &)
{
    QModelIndex	RIndex=ui->tableWidgetSelectedList->currentIndex();
    if(RIndex.isValid()==false)
        return;
    int	R=RIndex.row();
    AlgorithmLibraryList	*d=SelectedList.GetItem(R);
    if(d!=NULL){
        SelectedList.RemoveList(d);
        delete	d;
        ShowSelectedList();
    }
}


bool	SelectLibrariesForAnyType::Save(QIODevice *f)
{
    int32	Ver=1;

    if(::Save(f,Ver)==false)
        return false;
    if(::Save(f,LibFolderID)==false)
        return false;
    if(::Save(f,LibType)==false)
        return false;
    if(LibIDList.Save(f)==false)
        return false;
    if(SelectedList.Save(f)==false)
        return false;
    return true;
}

bool	SelectLibrariesForAnyType::Load(QIODevice *f)
{
    int32	Ver;

    if(::Load(f,Ver)==false)
        return false;
    if(::Load(f,LibFolderID)==false)
        return false;
    if(::Load(f,LibType)==false)
        return false;
    if(LibIDList.Load(f)==false)
        return false;
    if(SelectedList.Load(f)==false)
        return false;

    AlgorithmLibraryListContainer	TmpList=SelectedList;
    int	N=0;
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),N++){
        if(LibType==L->GetLibType()){
            ui->comboBLibType->setCurrentIndex(N);
            ShowFolder(L->GetLibType());
            break;
        }
    }
    pLibFolderForm->SetCurrentLibFolder(LibFolderID);
    SelectedList=TmpList;
    ShowSelectedList();

    return true;
}

void	SelectLibrariesForAnyType::setFocusComboBForMaskingForm ( void )
{
    ui->comboBLibType->setFocus();
}

void	SelectLibrariesForAnyType::resizeForMaskingForm ( void )
{
    // PropertyMaskingForm?IframeLibrary?!?T?C?Y?I?X?I???s???T?C?Y
    ui->comboBLibType->setGeometry(0, 0, 189, 22);
    ui->comboBLibType->adjustSize();
    ui->frameLibFolder->setGeometry(0, 30, 189, 141);
    ui->frameLibFolder->adjustSize();
    ui->tableWidgetLibList->setGeometry(0, 180, 189, 141);
    ui->tableWidgetLibList->adjustSize();
    ui->tableWidgetSelectedList->setGeometry(209, 180, 189, 141);
    ui->tableWidgetSelectedList->adjustSize();
    ui->label->setGeometry(209, 180, 189, 21);
    ui->label->adjustSize();
}

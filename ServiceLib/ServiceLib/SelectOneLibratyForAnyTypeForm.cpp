/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\SelectOneLibratyForAnyTypeForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "SelectOneLibratyForAnyTypeForm.h"
#include "ui_SelectOneLibratyForAnyTypeForm.h"
#include "LibFolderForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XLibraryType.h"
#include "XRememberer.h"


SelectOneLibratyForAnyTypeForm::SelectOneLibratyForAnyTypeForm(LayersBase *base  ,bool UseOkCancel,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectOneLibratyForAnyTypeForm)
{
    ui->setupUi(this);
    LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangLibSolver.SetUI(this);

    InitialMode =true;
    pLibFolderForm=new LibFolderForm(-1,GetLayersBase(),ui->frameLibFolder);
    connect(pLibFolderForm,SIGNAL(SelectLibFolder(int,QString)),this,SLOT(SlotSelectLibFolder(int,QString)));
    ui->tableWidgetLibList->setColumnWidth (0, 30);
    ui->tableWidgetLibList->setColumnWidth (1, 80);
    SetLibTypeInComboBox();

    ui->pushButtonOK    ->setVisible(UseOkCancel);
    ui->pushButtonCancel->setVisible(UseOkCancel);

    InitialMode=false;

    InstallOperationLog(this);
}

SelectOneLibratyForAnyTypeForm::~SelectOneLibratyForAnyTypeForm()
{
    delete ui;
}

void SelectOneLibratyForAnyTypeForm::showEvent(QShowEvent *e)
{
    int	CLibType=ControlRememberer::GetInt(objectName()+/**/"\\SelectOneLibraryForAnyType-LibType",-1);
    if(CLibType>=0){
        int Row=0;
        for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
            if(L->GetLibType()==CLibType){
                ui->comboBLibType->setCurrentIndex(Row);
                ShowFolder(CLibType);

                int	CLibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\SelectOneLibraryForAnyType-LibFolderID",-1);
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

void SelectOneLibratyForAnyTypeForm::resizeEvent(QResizeEvent *event)
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
}

void SelectOneLibratyForAnyTypeForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	SelectOneLibratyForAnyTypeForm::SetSelected(AlgorithmLibraryList &selectedLib)
{
    SelectedLib=selectedLib;
    ShowSelectedLib();
}
void	SelectOneLibratyForAnyTypeForm::SetLibTypeInComboBox(void)
{
    ui->comboBLibType->clear();
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext()){
        AlgorithmBase   *ABase=GetLayersBase()->GetAlgorithmBase(L->GetLibType());
        ui->comboBLibType->addItem(ABase->GetNameByCurrentLanguage(),(int)L->GetLibType());
    }
}

void    SelectOneLibratyForAnyTypeForm::ShowSelectedLib(void)
{
    ui->spinBoxLibID    ->setValue(SelectedLib.GetLibID());
    ui->lineEditLibName ->setText(GetLayersBase()->GetLibraryName(LibType,SelectedLib.GetLibID()));
}

void SelectOneLibratyForAnyTypeForm::on_comboBLibType_currentIndexChanged(int index)
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
        ControlRememberer::SetValue(objectName()+/**/"\\SelectOneLibraryForAnyType-LibType",LibType);
    }
}


void	SelectOneLibratyForAnyTypeForm::ShowFolder(int LibType)
{
    pLibFolderForm->SetLibType(LibType);
}

void	SelectOneLibratyForAnyTypeForm::SlotSelectLibFolder(int libFolderID ,QString FolderName)
{
    LibFolderID=libFolderID;
    ControlRememberer::SetValue(objectName()+/**/"\\SelectOneLibraryForAnyType-LibFolderID",LibFolderID);
    
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

void SelectOneLibratyForAnyTypeForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{
    QModelIndex	RIndex=ui->tableWidgetLibList->currentIndex();
    if(RIndex.isValid()==false)
        return;
    int	R=RIndex.row();
    AlgorithmLibraryList	*d=LibIDList.GetItem(R);
    if(d!=NULL){
        bool	ModeAdd=true;
        SelectedLib =*d;
        ShowSelectedLib();
    }
}


bool	SelectOneLibratyForAnyTypeForm::Save(QIODevice *f)
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
    if(SelectedLib.Save(f)==false)
        return false;
    return true;
}

bool	SelectOneLibratyForAnyTypeForm::Load(QIODevice *f)
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
    if(SelectedLib.Load(f)==false)
        return false;

    AlgorithmLibraryList	TmpLib=SelectedLib;
    int	N=0;
    for(LibraryTypeList *L=GetLayersBase()->GetInstalledLibType()->GetFirst();L!=NULL;L=L->GetNext(),N++){
        if(LibType==L->GetLibType()){
            ui->comboBLibType->setCurrentIndex(N);
            ShowFolder(L->GetLibType());
            break;
        }
    }
    pLibFolderForm->SetCurrentLibFolder(LibFolderID);
    SelectedLib=TmpLib;

    return true;
}
void SelectOneLibratyForAnyTypeForm::on_pushButtonOK_clicked()
{
    close();
}


void SelectOneLibratyForAnyTypeForm::on_pushButtonCancel_clicked()
{
    SelectedLib.SetLibID(-1);
    close();
}


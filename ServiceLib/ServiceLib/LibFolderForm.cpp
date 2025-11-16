/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\LibFolderForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"
#include "LibFolderForm.h"
#include "LibFolderInputForm.h"
#include "XDataInLayer.h"
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include "XDatabaseLoader.h"
#include "swap.h"
#include "ui_LibFolderForm.h"
#include "XRememberer.h"
#include "XGeneralFunc.h"

LibFolderNode::LibFolderNode(const QString &_FolderName
                ,int _ParentID
                ,int _LibFolderID
                ,int _NumberInFolder)
:QTreeWidgetItem(_LibFolderID)
{
    FolderName		=_FolderName;
    ParentID		=_ParentID;
    LibFolderID		=_LibFolderID;
    NumberInFolder	=_NumberInFolder;
}

LibFolderNode	*LibFolderNode::SetCurrentLibFolder(int _LibFolderID)
{
    if(LibFolderID==_LibFolderID){
        return this;
    }
    for(int i=0;i<childCount();i++){
        LibFolderNode	*c=dynamic_cast<LibFolderNode *>(child(i));
        if(c!=NULL){
            LibFolderNode	*ret=c->SetCurrentLibFolder(_LibFolderID);
            if(ret!=NULL){
                return ret;
            }
        }
    }
    return NULL;
}


LibFolderTreeWidget::LibFolderTreeWidget(LibFolderForm *treeParent,QWidget *parent)
:QTreeWidget(parent)
{
    TreeParent=treeParent;
    setDragDropMode(QAbstractItemView::DragDrop);
    setDragDropOverwriteMode(true);
    setDropIndicatorShown(true);
    setAcceptDrops(true);
}

void LibFolderTreeWidget::mousePressEvent ( QMouseEvent * event )
{
    if(event->button()==Qt::RightButton){
        QMenu	Menu;
        QAction	*CopyAction=new QAction(this);
        CopyAction->setText("Copy");
        Menu.addAction(CopyAction);

        QAction	*PasteAction=new QAction(this);
        PasteAction->setText("Paste");
        Menu.addAction(PasteAction);
        connect(CopyAction ,SIGNAL(triggered()),TreeParent,SLOT(SlotCopyFolder()));
        connect(PasteAction,SIGNAL(triggered()),TreeParent,SLOT(SlotPasteFolder()));
        Menu.exec(mapToGlobal(event->pos()));
    }
    else{
        QTreeWidget::mousePressEvent ( event );
    }
}

LibFolderNode	*LibFolderTreeWidget::SetCurrentLibFolder(int LibFolderID)
{
    for(int i=0;i<topLevelItemCount();i++){
        LibFolderNode	*c=dynamic_cast<LibFolderNode *>(topLevelItem(i));
        if(c!=NULL){
            LibFolderNode	*ret=c->SetCurrentLibFolder(LibFolderID);
            if(ret!=NULL){
                setCurrentItem(ret);
                return ret;
            }
        }
    }
    return NULL;
}
void LibFolderTreeWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat(/**/"LibID")){
        event->setDropAction(Qt::LinkAction);
        event->accept();
    }
}
void LibFolderTreeWidget::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->hasFormat(/**/"LibID")){
        event->setDropAction(Qt::LinkAction);
        event->accept();
    }
}
void LibFolderTreeWidget::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->hasFormat(/**/"LibID")){
        QPoint	Q=event->pos();
        QTreeWidgetItem *CurrentItem =itemAt(Q.x(),Q.y());
        LibFolderNode	*NCurrentItem=dynamic_cast<LibFolderNode *>(CurrentItem);
        if (NCurrentItem != NULL) {
            QWidget* W = dynamic_cast<QWidget*>(event->source());
            if (W != NULL) {
                TreeParent->Drop(NCurrentItem->GetParentID(), NCurrentItem->GetLibFolderID(), W);
            }
        }
    }
}

LibFolderForm::LibFolderForm(int libType ,LayersBase *lbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(lbase)
    ,treeWidget(this)
    ,ui(new Ui::LibFolderForm)
{
    ui->setupUi(this);
    setObjectName(/**/"LibFolder");
    //if(lbase!=NULL){
    //    LangDISolver.SetLanguage(lbase->GetLanguagePackageData(),lbase->GetLanguageCode());
    //}
    //LangDISolver.SetUI(this);
    treeWidget.setParent(this);

    LibType=libType;
    ShowAllNodes();

    SelectedFolderName		=/**/"";
    SelectedParentID		=-1;
    SelectedLibFolderID		=-1;
    CopiedID				=-1;
    move(0,0);
    resize(parent->width(),parent->height());
    connect(&treeWidget,SIGNAL(clicked(const QModelIndex &)),this,SLOT(on_treeWidget_clicked(const QModelIndex &)));
    connect(&treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)));
    connect(&treeWidget,SIGNAL(itemSelectionChanged()),this,SLOT(SlotItemSelectionChanged()));
    connect(&treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *))
                    ,this,SLOT(SlotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));

    IntListContainer    R=ControlRememberer::GetIntListContainer(&treeWidget);
    ::SetSelectedItems(&treeWidget, R);

    InstallOperationLog(this);
}

LibFolderForm::~LibFolderForm()
{
    delete ui;
}

int		LibFolderForm::SetLibType(int libType)
{
    treeWidget.clear();
    LibType=libType;
    ShowAllNodes();
    return LibType;
}
void    LibFolderForm::showEvent(QShowEvent *event)
{
    IntListContainer    R;
    ::GetSelectedItems(&treeWidget, R);
    if(R.GetCount()>0){
        SlotItemSelectionChanged();
    }
}
void	LibFolderForm::FitToFrame(QWidget *ParentFrame)
{
    int	Width	=ParentFrame->width();
    int	Height	=ParentFrame->height();
    resize(Width,Height);
    ui->labelFolder->resize(Width,ui->labelFolder->height());
    treeWidget.resize(Width,Height - ui->labelFolder->height() - ui->SelectedFolderName->height());
    ui->SelectedFolderName->move(0,ui->labelFolder->height()+treeWidget.height());
    ui->pushButtonUpdate->move(Width-ui->pushButtonUpdate->width(),ui->labelFolder->height()+treeWidget.height());
}
void	LibFolderForm::resizeEvent ( QResizeEvent * event )
{
    QSize	Q=event->size();
    ui->labelFolder->resize(Q.width(),ui->labelFolder->height());
    treeWidget.resize(Q.width(),Q.height() - ui->labelFolder->height() - ui->SelectedFolderName->height());
    ui->SelectedFolderName->move(0,ui->labelFolder->height()+treeWidget.height());
    ui->pushButtonUpdate->move(Q.width()-ui->pushButtonUpdate->width(),ui->labelFolder->height()+treeWidget.height());
}


int	LibFolderForm::ShowAllNodes(void)
{
    if(GetLayersBase()->IsValidDatabase()==false){
        return(0);
    }
    treeWidget.clear();
    int	N=0;
    if(GetLayersBase()->GetDatabaseLoader()){
        QSqlQuery *query=GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindFirst(GetLayersBase()->GetDatabase());
        if(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true){
            do{
                int	LibFolderID;
                QString FolderName;
                int ParentID;
                int NumberInFolder;

                GetLayersBase()->GetDatabaseLoader()->S_LibFolderGetData(query ,LibFolderID ,FolderName ,ParentID ,NumberInFolder);
                LibFolderNode	*p=new LibFolderNode(FolderName,ParentID,LibFolderID,NumberInFolder);
                p->setText(0,p->GetFolderName());
                treeWidget.addTopLevelItem(p);
                ShowAllNodes(p,LibFolderID);
                N++;
            }while(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true);
        }
        GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);
        LibFolderNode	*p=new LibFolderNode("New"
                                            ,0,-1,0);
        p->setText(0,p->GetFolderName());
        treeWidget.addTopLevelItem(p);
        N++;
    }
    return N;
}

void	LibFolderForm::ShowAllNodes(LibFolderNode *parentNode ,int parentID)
{
    if(GetLayersBase()->IsValidDatabase()==false){
        return;
    }
    if(GetLayersBase()->GetDatabaseLoader()){
        QSqlQuery *query=GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindFirstByParentID(GetLayersBase()->GetDatabase(),parentID);
        if(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true){
            do{
                int	LibFolderID;
                QString FolderName;
                int ParentID;
                int NumberInFolder;

                GetLayersBase()->GetDatabaseLoader()->S_LibFolderGetData(query ,LibFolderID ,FolderName ,ParentID ,NumberInFolder);
                LibFolderNode	*p=new LibFolderNode(FolderName,ParentID,LibFolderID,NumberInFolder);
                p->setText(0,p->GetFolderName());
                parentNode->addChild(p);
                ShowAllNodes(p,LibFolderID);
            }while(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true);
        }
        GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);
        LibFolderNode	*p=new LibFolderNode("New"
                                            ,parentID,-1,0);
        p->setText(0,p->GetFolderName());
        parentNode->addChild(p);
    }
}

void LibFolderForm::on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)
{
    CreateNewFolder();
}

int	LibFolderForm::CreateNewFolder(void)
{
    QTreeWidgetItem *CurrentItem =treeWidget.currentItem();
    LibFolderNode	*NCurrentItem=dynamic_cast<LibFolderNode *>(CurrentItem);
    int		Sel_LibFolderID;
    if(NCurrentItem!=NULL){
        Sel_LibFolderID		=NCurrentItem->GetLibFolderID();
    }

    QList<QTreeWidgetItem *>	Q=treeWidget.selectedItems();
    if(Q.count()>0){
        QTreeWidgetItem *p=Q.first();
        if(p!=NULL){
            LibFolderNode	*q=dynamic_cast<LibFolderNode *>(p);
            if(q!=NULL){
                LibFolderInputForm	D(GetLayersBase(),q->GetFolderName(),this);
                if((D.exec()==(int)true) && GetLayersBase()->GetDatabaseLoader()){
                    q->SetFolderName(D.FolderName);
                    if(q->GetLibFolderID()==-1){
                        q->SetLibFolderID(GetLayersBase()->GetDatabaseLoader()->S_LibFolderCreatenew(GetLayersBase()->GetDatabase()));
                    }
                    int	libFolderID	=q->GetLibFolderID();
                    GetLayersBase()->GetDatabaseLoader()->S_LibFolderUpdate(GetLayersBase()->GetDatabase()
                                            ,q->GetParentID()
                                            ,q->GetFolderName()
                                            , q->GetLibFolderID()
                                            ,GetLayersBase()->GetMasterCode());
                    ShowAllNodes();
                    if(Sel_LibFolderID==-1){
                        Sel_LibFolderID=libFolderID;
                    }
                    treeWidget.SetCurrentLibFolder(Sel_LibFolderID);
                    return libFolderID;
                    }
            }
        }
    }
    return -1;
}

void LibFolderForm::on_treeWidget_clicked(const QModelIndex &)
{
    SlotItemSelectionChanged();
}
void    LibFolderForm::SlotCurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
     SlotItemSelectionChanged();
}
void    LibFolderForm::SlotItemSelectionChanged()
{
    QList<QTreeWidgetItem *>	Q=treeWidget.selectedItems();
    if(Q.count()>0){
        QTreeWidgetItem *p=Q.first();
        if(p!=NULL){
            LibFolderNode	*q=dynamic_cast<LibFolderNode *>(p);
            if(q!=NULL){
                ui->SelectedFolderName	->setText(QString::number(q->GetLibFolderID())+QString(/**/":")+q->GetFolderName());
                SelectedFolderName		=q->GetFolderName();
                SelectedParentID		=q->GetParentID();
                SelectedLibFolderID		=q->GetLibFolderID();

                IntListContainer    R;
                ::GetSelectedItems(&treeWidget, R);
                ControlRememberer::SetValue(&treeWidget,R);

                emit	SelectLibFolder(q->GetLibFolderID(),q->GetFolderName());

            }
        }
    }
}
void	LibFolderForm::Show(void)
{
    treeWidget.show();
    QTreeWidgetItem *Item=treeWidget.currentItem();
    if(Item!=NULL){
        LibFolderNode	*a=dynamic_cast<LibFolderNode *>(Item);
        if(a!=NULL){
            emit	SelectLibFolder(a->GetLibFolderID() ,a->GetFolderName());
        }
    }
}

void	LibFolderForm::SlotCopyFolder(void)
{
    QTreeWidgetItem *w=treeWidget.currentItem();
    if(w!=NULL){
        LibFolderNode	*q=dynamic_cast<LibFolderNode *>(w);
        if(q!=NULL){
            if(q->GetLibFolderID()==-1){
                if(AlertNewFolder()==true){
                    q->SetLibFolderID(CreateNewFolder());
                }
            }
            CopiedID=q->GetLibFolderID();
        }
    }
}
void	LibFolderForm::SlotPasteFolder(void)
{
    if(CopiedID!=-1){
        QTreeWidgetItem *w=treeWidget.currentItem();
        if(w!=NULL){
            LibFolderNode	*q=dynamic_cast<LibFolderNode *>(w);
            if(q!=NULL){
                if(q->GetLibFolderID()==-1){
                    if(AlertNewFolder()==true){
                        q->SetLibFolderID(CreateNewFolder());
                    }
                }
                if(GetLayersBase()->GetDatabaseLoader()){
                    GetLayersBase()->GetDatabaseLoader()->S_LibCopy(GetLayersBase()->GetDatabase(),CopiedID,q->GetLibFolderID(),LibType);
                }
            }
        }
    }
}

bool	LibFolderForm::AlertNewFolder(void)
{
    QMessageBox::StandardButton ret=QMessageBox::question ( NULL
                                                            , "Select"
                                                            , "Create new folder?"
                                                            , QMessageBox::Yes | QMessageBox::No);
    if(ret==QMessageBox::Yes){
        return true;
    }
    return false;
}

void	LibFolderForm::SetCurrentLibFolder(int LibFolderID)
{
    LibFolderNode	*c=treeWidget.SetCurrentLibFolder(LibFolderID);
    if(c!=NULL){
        emit	SelectLibFolder(LibFolderID ,c->GetFolderName());
    }
}
void LibFolderForm::on_pushButtonUpdate_clicked()
{
    QTreeWidgetItem *CurrentItem =treeWidget.currentItem();
    LibFolderNode	*NCurrentItem=dynamic_cast<LibFolderNode *>(CurrentItem);
    if(NCurrentItem!=NULL){
        int		Sel_LibFolderID		=NCurrentItem->GetLibFolderID();
        ShowAllNodes();
        treeWidget.SetCurrentLibFolder(Sel_LibFolderID);
    }
}

void	LibFolderForm::Drop(int FolderParentID ,int LibFolderID , QWidget *w)
{
    emit	SignalDrop(FolderParentID ,LibFolderID , w);
}

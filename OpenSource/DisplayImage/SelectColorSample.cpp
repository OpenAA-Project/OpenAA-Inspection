/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\CommonGUIDLL\SelectColorSample.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "DisplayImageResource.h"
#include "SelectColorSampleResource.h"
#include "XTypeDef.h"
#include <QMessageBox>
#include "SelectColorSample.h"
#include "ui_SelectColorSample.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "ColorFolderInputForm.h"
#include "XFileRegistry.h"


ColorFolderNode::ColorFolderNode( const QString &_FolderName
                    ,int _ParentID
                    ,int _ColorFolderID
                    ,int _NumberInFolder)
:QTreeWidgetItem(_ColorFolderID)
{
    //LangDISolver.SetLanguage(mainPanel->GetLayersBase()->GetLanguageCode());
    //LangDISolver.SetUI(this);

    FolderName		=_FolderName;
    ParentID		=_ParentID;
    ColorFolderID	=_ColorFolderID;
    NumberInFolder	=_NumberInFolder;
}


ColorFolderNode	*ColorFolderNode::SetCurrentColorFolder(int _ColorFolderID)
{
    if(ColorFolderID==_ColorFolderID){
        return this;
    }
    for(int i=0;i<childCount();i++){
        ColorFolderNode	*c=dynamic_cast<ColorFolderNode *>(child(i));
        if(c!=NULL){
            ColorFolderNode	*ret=c->SetCurrentColorFolder(_ColorFolderID);
            if(ret!=NULL){
                return ret;
            }
        }
    }
    return NULL;
}


ColorFolderTreeWidget::ColorFolderTreeWidget(SelectColorSample *treeParent,QWidget *parent)
:QTreeWidget(parent)
{
    TreeParent=treeParent;
}

void ColorFolderTreeWidget::mousePressEvent ( QMouseEvent * event )
{
    /*
    if(event->button()==Qt::RightButton){
        QMenu	Menu;
        QAction	*CopyAction=new QAction(this);
        CopyAction->setText(QString("Copy"));
        Menu.addAction(CopyAction);

        QAction	*PasteAction=new QAction(this);
        PasteAction->setText(QString("Paste"));
        Menu.addAction(PasteAction);
        connect(CopyAction ,SIGNAL(triggered()),TreeParent,SLOT(SlotCopyFolder()));
        connect(PasteAction,SIGNAL(triggered()),TreeParent,SLOT(SlotPasteFolder()));
        Menu.exec(mapToGlobal(event->pos()));
    }
    else{
    */
        QTreeWidget::mousePressEvent ( event );
    //}
}

ColorFolderNode	*ColorFolderTreeWidget::SetCurrentColorFolder(int ColorFolderID)
{
    for(int i=0;i<topLevelItemCount();i++){
        ColorFolderNode	*c=dynamic_cast<ColorFolderNode *>(topLevelItem(i));
        if(c!=NULL){
            ColorFolderNode	*ret=c->SetCurrentColorFolder(ColorFolderID);
            if(ret!=NULL){
                setCurrentItem(ret);
                return ret;
            }
        }
    }
    return NULL;
}

SelectColorSample::SelectColorSample(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,treeWidget(this)
    ,ui(new Ui::SelectColorSample)
{
    ui->setupUi(this);
    LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangCGSolver.SetUI(this);

    ui->tableWidget->setColumnWidth(0,40);
    ui->tableWidget->setColumnWidth(1,130);
    ShowList();

    treeWidget.setParent(this);
    treeWidget.setGeometry(ui->frame->geometry().left(),ui->frame->geometry().bottom()+4,ui->frame->geometry().width()
                          ,ui->tableWidget->geometry().top()-ui->frame->geometry().bottom()-8);
    ShowAllNodes();

    SelectedFolderName		=/**/"";
    SelectedParentID		=-1;
    SelectedColorFolderID	=-1;
    CopiedID				=-1;
    move(0,0);

    connect(&treeWidget,SIGNAL(clicked(const QModelIndex &)),this,SLOT(on_treeWidget_clicked(const QModelIndex &)));
    connect(&treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)));

    InstallOperationLog(this);
}

SelectColorSample::~SelectColorSample()
{
    delete ui;
}

void SelectColorSample::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

void	SelectColorSample::ShowList(void)
{
    if(GetLayersBase()->GetDatabaseLoader()){
        int	N=GetLayersBase()->GetDatabaseLoader()->G_EnumColorSample(*GetLayersBase()->GetDataBase() ,SelectedColorFolderID
                                                    ,EnumData ,sizeof(EnumData)/sizeof(EnumData[0]));
        ui->tableWidget->setRowCount(N);
        for(int row=0;row<N;row++){
            QTableWidgetItem *W;
            W=ui->tableWidget->item ( row, 0);
            if(W==NULL){
                W=new QTableWidgetItem();
                ui->tableWidget->setItem ( row, 0,W);
                W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
            W->setText(QString::number(EnumData[row].GetAutoCount()));
            W=ui->tableWidget->item ( row, 1);
            if(W==NULL){
                W=new QTableWidgetItem();
                ui->tableWidget->setItem ( row, 1,W);
                W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            }
            W->setText(EnumData[row].GetName());
        }
    }
}

void SelectColorSample::on_tableWidget_clicked(const QModelIndex &Index)
{
    int	row=Index.row();
    if(row<0)
        return;
    CData.SetAutoCount(EnumData[row].GetAutoCount());
    QBuffer		DataBuff;
    //DataBuff.open(QIODevice::ReadWrite);
    if(GetLayersBase()->GetDatabaseLoader()){
        if(GetLayersBase()->GetDatabaseLoader()->G_LoadColorSample(*GetLayersBase()->GetDataBase() ,CData,DataBuff)==false){
            QMessageBox::critical ( this, LangCGSolver.GetString(SelectColorSample_LS,LID_8)/*"Error"*/
                                        , LangCGSolver.GetString(SelectColorSample_LS,LID_9)/*"Can't load ColorSample"*/);
        }
        else{
            DataBuff.open(QIODevice::ReadOnly);
            if(CData.LoadData(&DataBuff)==false){
                return;
            }
            ui->lineEditName->setText(CData.GetName());
        }
    }
}

void SelectColorSample::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    emit	SignalSelectCData();
}

void SelectColorSample::on_pushButtonSelect_clicked()
{
    QBuffer		DataBuff;
    DataBuff.open(QIODevice::ReadWrite);
    if(GetLayersBase()->GetDatabaseLoader()){
        if(GetLayersBase()->GetDatabaseLoader()->G_LoadColorSample(*GetLayersBase()->GetDataBase() ,CData,DataBuff)==false){
            QMessageBox::critical ( this, LangCGSolver.GetString(SelectColorSample_LS,LID_6)/*"Error"*/
                                        , LangCGSolver.GetString(SelectColorSample_LS,LID_7)/*"Can't load ColorSample"*/);
        }
        else{
            DataBuff.seek(0);
            if(CData.LoadData(&DataBuff)==false){
                return;
            }
            emit	SignalSelectCData();
        }
    }
}

void SelectColorSample::on_pushButtonDelete_clicked()
{
    if(GetLayersBase()->GetDatabaseLoader()){
        if(GetLayersBase()->GetDatabaseLoader()->G_DeleteColorSample(*GetLayersBase()->GetDataBase() ,CData)==false){
            QMessageBox::critical ( this, LangCGSolver.GetString(SelectColorSample_LS,LID_4)/*"Error"*/
                                        , LangCGSolver.GetString(SelectColorSample_LS,LID_5)/*"Can't delete ColorSample"*/);
        }
        else{
            ShowList();
        }
    }
}

void SelectColorSample::on_pushButtonSaveNew_clicked()
{
    CData.SetName(ui->lineEditName->text());
    emit	SignalBeforeSave();
    CData.SetSelectedColorFolder(SelectedColorFolderID);
    if(GetLayersBase()->GetDatabaseLoader()->G_SaveNewColorSample(*GetLayersBase()->GetDataBase() ,CData)==false){
        QMessageBox::critical ( this, LangCGSolver.GetString(SelectColorSample_LS,LID_2)/*"Error"*/
                                    , LangCGSolver.GetString(SelectColorSample_LS,LID_3)/*"Can't save ColorSample"*/);
    }
    else{
        ShowList();
    }
}

void SelectColorSample::on_pushButtonUpdate_clicked()
{
    CData.SetName(ui->lineEditName->text());
    emit	SignalBeforeSave();
    CData.SetSelectedColorFolder(SelectedColorFolderID);
    if(GetLayersBase()->GetDatabaseLoader()){
        if(GetLayersBase()->GetDatabaseLoader()->G_UpdateColorSample(*GetLayersBase()->GetDataBase() ,CData)==false){
            QMessageBox::critical ( this, LangCGSolver.GetString(SelectColorSample_LS,LID_0)/*"Error"*/
                                        , LangCGSolver.GetString(SelectColorSample_LS,LID_1)/*"Can't update ColorSample"*/);
        }
        else{
            ShowList();
        }
    }
}

int	SelectColorSample::ShowAllNodes(void)
{
    if(GetLayersBase()->IsValidDatabase()==false){
        return(0);
    }
    int	N=0;
    treeWidget.clear();
    if(GetLayersBase()->GetDatabaseLoader()){
        QSqlQuery *query=GetLayersBase()->GetDatabaseLoader()->S_ColorFolderFindFirst(GetLayersBase()->GetDatabase());
        if(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true){
            do{
                int	ColorFolderID;
                QString FolderName;
                int ParentID;
                int NumberInFolder;

                GetLayersBase()->GetDatabaseLoader()->S_ColorFolderGetData(query ,ColorFolderID ,FolderName ,ParentID ,NumberInFolder);
                ColorFolderNode	*p=new ColorFolderNode(FolderName,ParentID,ColorFolderID,NumberInFolder);

                p->setText(0,p->GetFolderName());
                treeWidget.addTopLevelItem(p);
                ShowAllNodes(p,ColorFolderID);
                N++;
            }while(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true);
        }
        GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);
        ColorFolderNode	*p=new ColorFolderNode(/**/"New",0,-1,0);
        p->setText(0,p->GetFolderName());
        treeWidget.addTopLevelItem(p);
        N++;
    }
    return N;
}

void	SelectColorSample::ShowAllNodes(ColorFolderNode *parentNode ,int parentID)
{
    if(GetLayersBase()->IsValidDatabase()==false)
        return;
    if(GetLayersBase()->GetDatabaseLoader()){
        QSqlQuery *query=GetLayersBase()->GetDatabaseLoader()->S_ColorFolderFindFirstByParentID(GetLayersBase()->GetDatabase(),parentID);
        if(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true){
            do{
                int	ColorFolderID;
                QString FolderName;
                int ParentID;
                int NumberInFolder;

                GetLayersBase()->GetDatabaseLoader()->S_ColorFolderGetData(query ,ColorFolderID ,FolderName ,ParentID ,NumberInFolder);
                ColorFolderNode	*p=new ColorFolderNode(FolderName,ParentID,ColorFolderID,NumberInFolder);
                p->setText(0,p->GetFolderName());
                parentNode->addChild(p);
                ShowAllNodes(p,ColorFolderID);
            }while(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true);
        }
        GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);
        ColorFolderNode	*p=new ColorFolderNode(/**/"New",parentID,-1,0);
        p->setText(0,p->GetFolderName());
        parentNode->addChild(p);
    }
}

void SelectColorSample::on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)
{
    CreateNewFolder();
}

int	SelectColorSample::CreateNewFolder(void)
{
    QTreeWidgetItem *CurrentItem =treeWidget.currentItem();
    ColorFolderNode	*NCurrentItem=dynamic_cast<ColorFolderNode *>(CurrentItem);
    int		Sel_ColorFolderID;
    if(NCurrentItem!=NULL){
        Sel_ColorFolderID	=NCurrentItem->GetColorFolderID();
    }

    QList<QTreeWidgetItem *>	Q=treeWidget.selectedItems();
    QTreeWidgetItem *p=Q.first();
    if(p!=NULL){
        ColorFolderNode	*q=dynamic_cast<ColorFolderNode *>(p);
        if(q!=NULL){
            ColorFolderInputForm	D(GetLayersBase(),q->GetFolderName(),this);
            if((D.exec()==(int)true) && GetLayersBase()->GetDatabaseLoader()){
                q->SetFolderName(D.FolderName);
                if(q->GetColorFolderID()==-1){
                    q->SetColorFolderID (GetLayersBase()->GetDatabaseLoader()->S_ColorFolderCreatenew(GetLayersBase()->GetDatabase()));
                }
                int	colorFolderID	=q->GetColorFolderID();
                GetLayersBase()->GetDatabaseLoader()->S_ColorFolderUpdate(GetLayersBase()->GetDatabase()
                                        ,q->GetParentID()
                                        ,q->GetFolderName()
                                        , q->GetColorFolderID());
                ShowAllNodes();
                treeWidget.SetCurrentColorFolder(Sel_ColorFolderID);
                return colorFolderID;
            }
        }
    }
    return -1;
}

void SelectColorSample::on_treeWidget_clicked(const QModelIndex &)
{
    QList<QTreeWidgetItem *>	Q=treeWidget.selectedItems();
    QTreeWidgetItem *p=Q.first();
    if(p!=NULL){
        ColorFolderNode	*q=dynamic_cast<ColorFolderNode *>(p);
        if(q!=NULL){
            //ui->SelectedFolderName	->setText(q->FolderName);
            SelectedFolderName		=q->GetFolderName();
            SelectedParentID		=q->GetParentID();
            SelectedColorFolderID	=q->GetColorFolderID();
            ShowList();
            emit	SelectColorFolder(q->GetColorFolderID(),q->GetFolderName());

        }
    }

}

void	SelectColorSample::SlotCopyFolder(void)
{
}
void	SelectColorSample::SlotPasteFolder(void)
{
}


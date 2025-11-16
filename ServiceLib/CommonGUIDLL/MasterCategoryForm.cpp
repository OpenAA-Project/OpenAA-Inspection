#include "CommonGUIDLLResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\ServiceLib\MasterCategoryForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MasterCategoryForm.h"
#include "ui_MasterCategoryForm.h"
#include "MasterCategoryInputForm.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"

CategoryNode::CategoryNode(const QString &_FolderName
                ,int _ParentID
                ,int _CategoryID
                ,const QString &_Remark)
:QTreeWidgetItem(_CategoryID)
{
    FolderName	=_FolderName;
    ParentID	=_ParentID;
    CategoryID	=_CategoryID;
    Remark		=_Remark;
}

MasterCategoryForm::MasterCategoryForm(LayersBase *lbase ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(lbase)
    ,ui(new Ui::MasterCategoryForm)
    
{
    ui->setupUi(this);
    //LangLibSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    //LangLibSolver.SetUI(this);
    connect(ui->treeWidget,SIGNAL(clicked(const QModelIndex &)),this,SLOT(TreeClicked(const QModelIndex &)));
    ShowAllNodes();

    SelectedFolderName		=/**/"";
    SelectedParentID		=-1;
    SelectedCategoryID		=-1;
    SelectedRemark			=/**/"";
}

MasterCategoryForm::~MasterCategoryForm()
{
    delete ui;
}

void MasterCategoryForm::on_pushButton_clicked()
{

}

void MasterCategoryForm::closeEvent ( QCloseEvent * event )
{
    QWidget::closeEvent (event);
    deleteLater ();
}

int	MasterCategoryForm::ShowAllNodes(void)
{
    ui->treeWidget->clear();
    if(GetLayersBase()->IsDatabaseOk()==false || (!GetLayersBase()->GetDatabaseLoader())){
        return 0;
    }
    int	N = 0;
    QSqlQuery* query = GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryFindFirst(GetLayersBase()->GetDatabase());
    if (GetLayersBase()->GetDatabaseLoader()->S_FindNext(query) == true) {
        do {
            int	CategoryID;
            QString FolderName;
            int ParentID;
            QString	Remark;

            GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryGetData(query, CategoryID, FolderName, ParentID, Remark);
            CategoryNode* p = new CategoryNode(FolderName, ParentID, CategoryID, Remark);

            p->setText(0, p->GetFolderName());
            p->setText(1, p->GetRemark());
            ui->treeWidget->addTopLevelItem(p);
            ShowAllNodes(p, CategoryID);
            N++;
        } while (GetLayersBase()->GetDatabaseLoader()->S_FindNext(query) == true);
    }
    GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);

    CategoryNode	*p=new CategoryNode(LangCGSolver.GetString(MasterCategoryForm_LS,LID_5)/*"New"*/
                                        ,0,-1,/**/"");
    p->setText(0,p->GetFolderName());
    ui->treeWidget->addTopLevelItem(p);
    N++;
    return N;
}
void	MasterCategoryForm::ShowAllNodes(CategoryNode *parentNode ,int parentID)
{
    QSqlQuery *query=GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryFindFirstByParentID(GetLayersBase()->GetDatabase() ,parentID);
    if(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true){
        do{
            int	CategoryID;
            QString FolderName;
            int ParentID;
            QString	Remark;

            GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryGetData(query ,CategoryID ,FolderName ,ParentID ,Remark);
            CategoryNode	*p=new CategoryNode(FolderName,ParentID,CategoryID,Remark);

            p->setText(0,p->GetFolderName());
            p->setText(1,p->GetRemark());
            parentNode->addChild(p);
            ShowAllNodes(p,CategoryID);
        }while(GetLayersBase()->GetDatabaseLoader()->S_FindNext(query)==true);
    }
    GetLayersBase()->GetDatabaseLoader()->S_DeleteQuery(query);

    CategoryNode	*p=new CategoryNode(LangCGSolver.GetString(MasterCategoryForm_LS,LID_6)/*"New"*/
                                        ,parentID,-1,/**/"");
    p->setText(0,p->GetFolderName());
    parentNode->addChild(p);
}
void MasterCategoryForm::TreeClicked(const QModelIndex & index)
{
    QList<QTreeWidgetItem *>	Q=ui->treeWidget->selectedItems();
    QTreeWidgetItem *p=Q.first();
    if(p!=NULL){
        CategoryNode	*q=dynamic_cast<CategoryNode *>(p);
        if(q!=NULL){
            ui->SelectedFolderName	->setText(q->GetFolderName());
            ui->SelectedRemark		->setText(q->GetRemark());
            SelectedFolderName		=q->GetFolderName();
            SelectedParentID		=q->GetParentID();
            SelectedCategoryID		=q->GetCategoryID();
            SelectedRemark			=q->GetRemark();
            emit	SelectCategory(q->GetCategoryID() ,q->GetFolderName() ,q->GetRemark());

        }
    }
}


void MasterCategoryForm::on_treeWidget_itemDoubleClicked(QTreeWidgetItem*,int)
{
    CreateNewFolder();
}

int	MasterCategoryForm::CreateNewFolder(void)
{
    QList<QTreeWidgetItem *>	Q=ui->treeWidget->selectedItems();
    QTreeWidgetItem *p=Q.first();
    if(p!=NULL){
        CategoryNode	*q=dynamic_cast<CategoryNode *>(p);
        if(q!=NULL){
            MasterCategoryInputForm	D(GetLayersBase(),q->GetFolderName(),q->GetRemark(),this);
            if(D.exec()==(int)true){
                q->SetFolderName(D.FolderName);
                q->SetRemark	(D.Remark);
                if(q->GetCategoryID()==-1){
                    q->SetCategoryID (GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryCreatenew(GetLayersBase()->GetDatabase()));
                }
                int	categoryID	=q->GetCategoryID();
                GetLayersBase()->GetDatabaseLoader()->S_MasterCategoryUpdate(GetLayersBase()->GetDatabase()
                                        ,q->GetParentID()
                                        ,q->GetFolderName()
                                        ,q->GetCategoryID()
                                        ,q->GetRemark());
                ShowAllNodes();
                return categoryID;
                }
        }
    }
    return -1;
}


void MasterCategoryForm::on_pushButtonUpdateButton_clicked()
{
    ShowAllNodes();
}

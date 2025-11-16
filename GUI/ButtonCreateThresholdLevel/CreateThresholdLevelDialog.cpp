#include "ButtonCreateThresholdLevelResource.h"
#include "CreateThresholdLevelDialog.h"
#include "ui_CreateThresholdLevelDialog.h"
#include "XLevel.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

CreateThresholdLevelDialog::CreateThresholdLevelDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::CreateThresholdLevelDialog)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);

    ShowTreeGrid();
    ShowCurrentParent();

    InstallOperationLog(this);
}

CreateThresholdLevelDialog::~CreateThresholdLevelDialog()
{
    delete ui;
}

void CreateThresholdLevelDialog::resizeEvent(QResizeEvent *event)
{
    ui->frame           ->move(0,height()-ui->frame->height());
    ui->treeWidgetLevel ->resize(width(),height()-ui->frame->height());
}
void    CreateThresholdLevelDialog::ShowTreeGrid(void)
{
    ui->treeWidgetLevel->clear();
    if(GetLayersBase()->GetLevelFolderContainer()!=NULL){
        GetLayersBase()->GetLevelFolderContainer()->Sort();
        for(LevelFolder *a=GetLayersBase()->GetLevelFolderContainer()->GetFirst();a!=NULL;a=a->GetNext()){
            QTreeWidgetItem	*Item=new QTreeWidgetItem(ui->treeWidgetLevel);
            Item->setText(0,QString::number(a->LevelValue));
            Item->setText(1,a->LevelName);
            Item->setData(0,Qt::UserRole,a->LevelID);
            ui->treeWidgetLevel->addTopLevelItem(Item);
            ShowTreeGrid(Item,a);
        }
    }
}
void CreateThresholdLevelDialog::ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *tParent)
{
    for(LevelFolder *a=tParent->Children.GetFirst();a!=NULL;a=a->GetNext()){
        QTreeWidgetItem	*m=new QTreeWidgetItem(Item);
        m->setText(0,QString::number(a->LevelValue));
        m->setText(1,a->LevelName);
        m->setData(0,Qt::UserRole,a->LevelID);
        Item->addChild(m);
        ShowTreeGrid(Item,a);
    }
}

void    CreateThresholdLevelDialog::ShowLevelItem(int LevelID)
{
    LevelFolder	*c=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(LevelID);
    if(c!=NULL){
        ui->lineEditLevelName   ->setText(c->LevelName);
        ui->lineEditRemark      ->setText(c->Remark);
        ui->spinBoxLevelValue   ->setValue(c->LevelValue);
    }
}
void CreateThresholdLevelDialog::on_pushButtonTopRoot_clicked()
{
    ShowCurrentParent();
}

void    CreateThresholdLevelDialog::ShowCurrentParent(void)
{
    if(ui->pushButtonTopRoot->isChecked()==true){
         ui->lineEditParentName->setText(/**/"Root top");
    }
    else{
        QTreeWidgetItem *Item=GetCurrentItem();
        if(Item!=NULL){
            int LevelID=Item->data(0,Qt::UserRole).toInt();
            if(LevelID>=0){
                ui->lineEditParentName->setText(GetLayersBase()->GetThresholdLevelName(LevelID));
            }
            else{
                ui->lineEditParentName->setText(/**/"Root top");
            }
        }
        else{
            ui->lineEditParentName->setText(/**/"Root top");
        }
    }
}

void CreateThresholdLevelDialog::on_treeWidgetLevel_itemSelectionChanged()
{
    QTreeWidgetItem *Item=GetCurrentItem();
    if(Item!=NULL){
        int LevelID=Item->data(0,Qt::UserRole).toInt();
        ShowLevelItem(LevelID);
        ShowCurrentParent();
        ui->pushButtonUpdate->setEnabled(true);
        ui->pushButtonTopRoot->setChecked(false);
    }
}
 
static  QTreeWidgetItem *GetCurrentSelectedItemsInner(QTreeWidgetItem *W)
{
	int	N=W->childCount();
	for(int i=0;i<N;i++){
		QTreeWidgetItem *t=W->child(i);
		if(t->isSelected()==true){
			return t;
		}
		t=GetCurrentSelectedItemsInner(t);
        if(t!=NULL){
            return t;
        }
	}
    return NULL;
}

QTreeWidgetItem *CreateThresholdLevelDialog::GetCurrentItem(void)
{
	int	N=ui->treeWidgetLevel->topLevelItemCount();
	for(int i=0;i<N;i++){
		QTreeWidgetItem *t=ui->treeWidgetLevel->topLevelItem(i);
		if(t->isSelected()==true){
			return t;
		}
		t=GetCurrentSelectedItemsInner(t);
        if(t!=NULL){
            return t;
        }
	}
    return NULL;
}

void CreateThresholdLevelDialog::on_pushButtonCreateNew_clicked()
{
    int ParentID=0;
    if(ui->pushButtonTopRoot->isChecked()==false){
        QTreeWidgetItem *ParentItem=GetCurrentItem();
        if(ParentItem!=NULL){
            ParentID=ParentItem->data(0,Qt::UserRole).toInt();
        }
        if(ParentID<0){
            return;
        }
    }
    int LevelID=GetLayersBase()->GetDatabaseLoader()->S_LevelCreatenew(GetLayersBase()->GetDatabase());
    if(LevelID<0)
        return;

    IntList RetLevelIDs;
    GetLayersBase()->EnumThresholdLevelIDInFolder(RetLevelIDs ,ParentID);

    LevelFolder	*c=new LevelFolder(GetLayersBase());
    c->LevelID      =LevelID;
    c->LevelName    =ui->lineEditLevelName   ->text();
    c->Remark       =ui->lineEditRemark      ->text();
    c->LevelValue   =ui->spinBoxLevelValue   ->value();
    c->ParentID     =ParentID;
    GetLayersBase()->GetDatabaseLoader()->S_LevelUpdate(GetLayersBase()->GetDatabase()
                                                    ,LevelID 
                                                    ,c->LevelValue 
                                                    ,c->LevelName
                                                    ,c->ParentID
                                                    ,c->Remark);
    LevelFolderContainer    *ParentContainer=NULL;
    if(ParentID==0){
        ParentContainer=GetLayersBase()->GetLevelFolderContainer();
    }
    else{
        LevelFolder	*PC=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(ParentID);
        if(PC!=NULL){
            ParentContainer=&PC->Children;
        }
    }
    if(ParentContainer!=NULL){
        ParentContainer->AppendList(c);       
        for(IntClass *d=RetLevelIDs.GetFirst();d!=NULL;d=d->GetNext()){
            if(c->LevelID==d->GetValue()){
                continue;
            }
            LevelFolder	*t=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(d->GetValue());
            if(t!=NULL){
                if(t->LevelValue>=c->LevelValue){
                    t->LevelValue++;
                }
            }
        }
        ParentContainer->Sort();
        GetLayersBase()->EnumThresholdLevelIDInFolder(RetLevelIDs ,ParentID);

        int LevelValue=0;
        for(IntClass *d=RetLevelIDs.GetFirst();d!=NULL;d=d->GetNext(),LevelValue++){
            LevelFolder	*t=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(d->GetValue());
            if(t!=NULL){
                t->LevelValue=LevelValue;
                GetLayersBase()->GetDatabaseLoader()->S_LevelUpdate(GetLayersBase()->GetDatabase()
                                                        ,t->LevelID 
                                                        ,t->LevelValue 
                                                        ,t->LevelName
                                                        ,t->ParentID
                                                        ,t->Remark);
            }
        }
    }
    ShowTreeGrid();
}

void CreateThresholdLevelDialog::on_pushButtonUpdate_clicked()
{
   QTreeWidgetItem *Item=GetCurrentItem();
    if(Item!=NULL){
        int LevelID=Item->data(0,Qt::UserRole).toInt();
        LevelFolder	*c=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(LevelID);
        if(c!=NULL){
            IntList RetLevelIDs;
            GetLayersBase()->EnumThresholdLevelIDInFolder(RetLevelIDs ,c->ParentID);
            c->LevelName    =ui->lineEditLevelName   ->text();
            c->Remark       =ui->lineEditRemark      ->text();
            c->LevelValue   =ui->spinBoxLevelValue   ->value();
            GetLayersBase()->GetDatabaseLoader()->S_LevelUpdate(GetLayersBase()->GetDatabase()
                                                            ,LevelID 
                                                            ,c->LevelValue 
                                                            ,c->LevelName
                                                            ,c->ParentID
                                                            ,c->Remark);
            
            for(IntClass *d=RetLevelIDs.GetFirst();d!=NULL;d=d->GetNext()){
                if(c->LevelID==d->GetValue()){
                    continue;
                }
                LevelFolder	*t=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(d->GetValue());
                if(t!=NULL){
                    if(t->LevelValue>=c->LevelValue){
                        t->LevelValue++;
                    }
                }
            }
             LevelFolderContainer    *ParentContainer=NULL;
            if(c->ParentID!=0){
                LevelFolder	*PC=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(c->ParentID);
                if(PC!=NULL){
                    ParentContainer=&PC->Children;
                }
            }
            else{
                ParentContainer=GetLayersBase()->GetLevelFolderContainer();
            }
            if(ParentContainer!=NULL){
                ParentContainer->Sort();
            }
            
            int LevelValue=0;
            for(IntClass *d=RetLevelIDs.GetFirst();d!=NULL;d=d->GetNext(),LevelValue++){
                LevelFolder	*t=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(d->GetValue());
                if(t!=NULL){
                    t->LevelValue=LevelValue;
                    GetLayersBase()->GetDatabaseLoader()->S_LevelUpdate(GetLayersBase()->GetDatabase()
                                                            ,t->LevelID 
                                                            ,t->LevelValue 
                                                            ,t->LevelName
                                                            ,t->ParentID
                                                            ,t->Remark);
                }
            }
        }
    }
    ShowTreeGrid();
}

void CreateThresholdLevelDialog::on_pushButtonDelete_clicked()
{
    QTreeWidgetItem *Item=GetCurrentItem();
    if(Item!=NULL){
        int LevelID=Item->data(0,Qt::UserRole).toInt();
        GetLayersBase()->GetLevelFolderContainer()->RemoveByLevelID(LevelID);
        ShowTreeGrid();
    }
}

void CreateThresholdLevelDialog::on_pushButtonClose_clicked()
{
    close();
}

void CreateThresholdLevelDialog::on_treeWidgetLevel_clicked(const QModelIndex &index)
{
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    
    mimeData->setText(LangSolver.GetString(CreateThresholdLevelDialog_LS,LID_0)/*"PasswordTarget"*/);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec();
}
void    CreateThresholdLevelDialog::dropEvent(QDropEvent *event)
{
}

void CreateThresholdLevelDialog::on_pushButtonCopy_clicked()
{
    SourceLevelID=-1;
    QTreeWidgetItem *Item=GetCurrentItem();
    if(Item!=NULL){
        int LevelID=Item->data(0,Qt::UserRole).toInt();
        LevelFolder	*c=GetLayersBase()->GetLevelFolderContainer()->FindByLevelID(LevelID);
        if(c!=NULL){
            SourceLevelID=c->LevelID;
        }
    }
}

void CreateThresholdLevelDialog::on_pushButtonPaste_clicked()
{
    if(SourceLevelID>0){
        QTreeWidgetItem *Item=GetCurrentItem();
        if(Item!=NULL){
            int DestLevelID=Item->data(0,Qt::UserRole).toInt();
            GetLayersBase()->DeliverCopyThresholdLevel(SourceLevelID ,DestLevelID);
        }
    }
}

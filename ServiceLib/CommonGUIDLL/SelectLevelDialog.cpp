#include "CommonGUIDLLResource.h"
#include "SelectLevelDialog.h"
#include "ui_SelectLevelDialog.h"
#include "XLevel.h"
#include "XDataInLayer.h"


SelectLevelDialog::SelectLevelDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectLevelDialog)
{
    ui->setupUi(this);
    TreeWidgetEnabler=new TreeWidgetRightClickEnabler(ui->treeWidgetLevel);
    connect(TreeWidgetEnabler,SIGNAL(RightClicked(QTreeWidget *)),this,SLOT(SlotRightClicked(QTreeWidget *)));

    ShowTreeGrid();
}

SelectLevelDialog::~SelectLevelDialog()
{
    delete  TreeWidgetEnabler;
    TreeWidgetEnabler=NULL;

    delete ui;
}

void SelectLevelDialog::resizeEvent(QResizeEvent *event)
{
    ui->treeWidgetLevel->resize(width(),height());
}

void    SelectLevelDialog::ShowTreeGrid(void)
{
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
void SelectLevelDialog::ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent)
{
    for(LevelFolder *a=Parent->Children.GetFirst();a!=NULL;a=a->GetNext()){
        QTreeWidgetItem	*m=new QTreeWidgetItem(Item);
        m->setText(0,QString::number(a->LevelValue));
        m->setText(1,a->LevelName);
        Item->setData(0,Qt::UserRole,a->LevelID);
        Item->addChild(m);
        ShowTreeGrid(Item,a);
    }
}
void SelectLevelDialog::on_treeWidgetLevel_clicked(const QModelIndex &index)
{
    QTreeWidgetItem *Item=ui->treeWidgetLevel->currentItem();
    if(Item!=NULL){
        int LevelID=Item->data(0,Qt::UserRole).toInt();
        emit    SignaSelected(LevelID);
    }
}

void	SelectLevelDialog::SlotRightClicked(QTreeWidget *obj)
{

}


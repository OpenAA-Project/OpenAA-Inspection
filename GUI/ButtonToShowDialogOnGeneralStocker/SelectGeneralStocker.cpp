#include "SelectGeneralStocker.h"
#include "ui_SelectGeneralStocker.h"
#include "XDataInLayer.h"
#include "XGeneralStocker.h"

SelectGeneralStocker::SelectGeneralStocker(LayersBase *pbase ,NPListPack<GeneralStockerPointerList> &dim,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(pbase)
    ,ui(new Ui::SelectGeneralStocker)
{
    ui->setupUi(this);
    Dim.RemoveAll();
    for(GeneralStockerPointerList *c=dim.GetFirst();c!=NULL;c=c->GetNext()){
        Dim.AppendList(new GeneralStockerPointerList(c->Point));
    }

    ui->tableWidgetGeneralStocker->setRowCount(Dim.GetNumber());
    int	N=0;
    for(GeneralStockerPointerList *c=Dim.GetFirst();c!=NULL;c=c->GetNext()){
        QTableWidgetItem *w=ui->tableWidgetGeneralStocker->item (N, 0);
        if(w==NULL){
            ui->tableWidgetGeneralStocker->setItem(N,0,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(c->Point->GetName());

        w=ui->tableWidgetGeneralStocker->item (N, 1);
        if(w==NULL){
            ui->tableWidgetGeneralStocker->setItem(N,1,(w=new QTableWidgetItem()));
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        w->setText(c->Point->GetOrganization());
        N++;
    }
    InstallOperationLog(this);
}

SelectGeneralStocker::~SelectGeneralStocker()
{
    delete ui;
}

void SelectGeneralStocker::on_tableWidgetGeneralStocker_doubleClicked(const QModelIndex &)
{
    on_pushButtonSelect_clicked();
}

void SelectGeneralStocker::on_pushButtonSelect_clicked()
{
    int	R=ui->tableWidgetGeneralStocker->currentRow();
    if(R<0){
        return;
    }
    GeneralStockerPointerList	*c=Dim.GetItem(R);
    Selected=c->Point;
    done(true);
}

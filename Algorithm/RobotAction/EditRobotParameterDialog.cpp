#include "EditRobotParameterDialog.h"
#include "ui_EditRobotParameterDialog.h"
#include "XGeneralFunc.h"
#include "XRobotControl.h"

EditRobotParameterDialog::EditRobotParameterDialog(LayersBase *base,RobotActionBase *aBase,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base)
    ,ABase(aBase)
    ,TmpPack(base)
    ,ui(new Ui::EditRobotParameterDialog)
{
    ui->setupUi(this);

    for(RobotAccessList *a=ABase->RobotPack.GetFirst();a!=NULL;a=a->GetNext()){
        RobotAccessList *d=new RobotAccessList(GetLayersBase(),a->GetDLLPathFileName(),a->GetLoadingParameter(),a->GetUniqueCode());
        TmpPack.AppendList(d);
    }
    ShowRobotList();
}

EditRobotParameterDialog::~EditRobotParameterDialog()
{
    delete ui;
}

void EditRobotParameterDialog::ShowRobotList(void)
{
    ui->listWidgetRobotList->clear();
    for(RobotAccessList *a=TmpPack.GetFirst();a!=NULL;a=a->GetNext()){
        ui->listWidgetRobotList->addItem(a->GetUniqueCode());
    }
}

void EditRobotParameterDialog::on_listWidgetRobotList_currentRowChanged(int currentRow)
{
    int Row=ui->listWidgetRobotList->currentRow();
    if(Row<0)
        return;
    RobotAccessList *a=TmpPack.GetItem(Row);
    if(a!=NULL){
        ShowRobotAccessList(a);
    }
}

void EditRobotParameterDialog::ShowRobotAccessList(RobotAccessList *a)
{
    ui->lineEditUniqueName      ->setText(a->GetUniqueCode());
    ui->lineEditDLLFileName     ->setText(a->GetDLLPathFileName());
    ui->lineEditLoadingParameter->setText(a->GetLoadingParameter());
}


void EditRobotParameterDialog::on_pushButtonAdd_clicked()
{
    QString UniqueName          =ui->lineEditUniqueName      ->text();
    QString DLLFileName         =ui->lineEditDLLFileName     ->text();
    QString LoadingParameter    =ui->lineEditLoadingParameter->text();
    RobotAccessList *a=new RobotAccessList(GetLayersBase(),DLLFileName,LoadingParameter,UniqueName);
    TmpPack.AppendList(a);
    ShowRobotList();
}


void EditRobotParameterDialog::on_pushButtonModify_clicked()
{
    int Row=ui->listWidgetRobotList->currentRow();
    if(Row<0)
        return;
    RobotAccessList *a=TmpPack.GetItem(Row);
    QString UniqueName          =ui->lineEditUniqueName      ->text();
    QString DLLFileName         =ui->lineEditDLLFileName     ->text();
    QString LoadingParameter    =ui->lineEditLoadingParameter->text();
    if(a!=NULL){
        a->Set(DLLFileName,LoadingParameter,UniqueName);
    }
    ShowRobotList();
}


void EditRobotParameterDialog::on_pushButtonDelete_clicked()
{
    int Row=ui->listWidgetRobotList->currentRow();
    if(Row<0)
        return;
    RobotAccessList *a=TmpPack.GetItem(Row);
    if(a!=NULL){
        TmpPack.RemoveList(a);
        delete  a;
    }
    ShowRobotList();
}


void EditRobotParameterDialog::on_pushButtonOK_clicked()
{
    int Row=0;
    for(RobotAccessList *a=TmpPack.GetFirst();a!=NULL;a=a->GetNext(),Row++){
        QString UniqueName          =a->GetUniqueCode();
        QString DLLFileName         =a->GetDLLPathFileName();
        QString LoadingParameter    =a->GetLoadingParameter();

        RobotAccessList *s=ABase->RobotPack.GetItem(Row);
        if(s!=NULL){
            s->Set(DLLFileName,LoadingParameter,UniqueName);
        }
        else{
            RobotAccessList *s=new RobotAccessList(GetLayersBase(),DLLFileName,LoadingParameter,UniqueName);
            ABase->RobotPack.AppendList(s);
        }
    }

    done(true);
}


void EditRobotParameterDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


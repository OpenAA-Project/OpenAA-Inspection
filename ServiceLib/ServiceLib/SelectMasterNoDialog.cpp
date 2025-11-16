#include "SelectMasterNoDialog.h"
#include "ui_SelectMasterNoDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"

SelectMasterNoDialog::SelectMasterNoDialog(LayersBase *Base,int OriginCode,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::SelectMasterNoDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 15);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,2, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,3, 55);

    for(LogicDLL *DLL=GetLayersBase()->GetLogicDLLBase()->GetFirst();DLL!=NULL;DLL=DLL->GetNext()){
        AlgorithmBase *ABase=DLL->GetInstance();
        int LibType=ABase->GetLibType();
        if(LibType>0){
            LibTypeList.Add(LibType);
        }
    }

    ui->tableWidget->setRowCount(LibTypeList.GetCount());
    int Row=0;
    for(IntClass *c=LibTypeList.GetFirst();c!=NULL;c=c->GetNext()){
        int LibType=c->GetValue();
        AlgorithmBase *ABase=GetLayersBase()->GetAlgorithmBase(LibType);
        ::SetDataToTable(ui->tableWidget,0, Row, QString::number(LibType));
        QString DLLRoot,DLLName;
        ABase->GetDLLName(DLLRoot,DLLName);
        ::SetDataToTable(ui->tableWidget,1, Row, DLLRoot);
        ::SetDataToTable(ui->tableWidget,2, Row, DLLName);
        ::SetDataToTable(ui->tableWidget,3, Row, ABase->GetNameByCurrentLanguage());
        Row++;
    }
    if(OriginCode<=0){
        ui->groupBoxMasterNo->setChecked(true);
        ui->groupBoxAlgorithm->setChecked(false);
    }
    else{
        ui->groupBoxMasterNo->setChecked(false);
        ui->groupBoxAlgorithm->setChecked(true);

        int Row=0;
        for(IntClass *c=LibTypeList.GetFirst();c!=NULL;c=c->GetNext(),Row++){
            int LibType=c->GetValue();
            if(LibType==OriginCode){
                ::SetCurrentRow(ui->tableWidget, Row);
            }
        }
    }
    InstallOperationLog(this);
}

SelectMasterNoDialog::~SelectMasterNoDialog()
{
    delete ui;
}

void SelectMasterNoDialog::on_groupBoxMasterNo_clicked()
{
    if(ui->groupBoxMasterNo->isChecked()==true){
        ui->groupBoxAlgorithm->setChecked(false);
    }
}


void SelectMasterNoDialog::on_groupBoxAlgorithm_clicked()
{
    if(ui->groupBoxAlgorithm->isChecked()==true){
        ui->groupBoxMasterNo->setChecked(false);
    }
}


void SelectMasterNoDialog::on_pushButtonOK_clicked()
{
    if(ui->groupBoxMasterNo->isChecked()==true){
        MasterNoOriginCode=-ui->spinBoxMasterNo->value();
    }
    else{
        int row=ui->tableWidget->currentRow();
        if(row<0)
            return;
        MasterNoOriginCode=LibTypeList[row];
    }
    done(true);
}


void SelectMasterNoDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


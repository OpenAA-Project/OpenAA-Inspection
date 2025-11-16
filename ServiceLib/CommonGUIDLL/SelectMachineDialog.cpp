#include "CommonGUIDLLResource.h"
#include "SelectMachineDialog.h"
#include "ui_SelectMachineDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "XDataInLayer.h"

SelectMachineDialog::SelectMachineDialog(LayersBase *base ,const IntList &machineList
                                         ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectMachineDialog)
{
    ui->setupUi(this);

    Base=base;
    SelectedMachineID=-1;
    MachineList=machineList;
    ui->tableWidget->setRowCount(MachineList.GetCount());

    int	Row=0;
    int	CurrentRow=0;
    for(IntClass *c=MachineList.GetFirst();c!=NULL;c=c->GetNext(),Row++){
        QString MacNetID;
        QString MacName;
        QString MacVersion;
        QString MacRemark;
        Base->GetDatabaseLoader()->G_GetMachineInfo(*Base->GetDataBase() ,c->GetValue()
                                ,MacNetID
                                ,MacName
                                ,MacVersion
                                ,MacRemark);
        SetDataToTable(ui->tableWidget ,0,Row ,QString::number(c->GetValue()));
        SetDataToTable(ui->tableWidget ,1,Row ,MacName);
        if(Base->GetMachineID()==c->GetValue()){
            CurrentRow=Row;
        }
    }
    ui->tableWidget->selectRow(CurrentRow);
    Base->TmpHideProcessingForm();
    Base->InstallOperationLog(this);
}

SelectMachineDialog::~SelectMachineDialog()
{
    delete ui;
    Base->TmpRercoverProcessingForm();
}

void SelectMachineDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    on_pushButtonOK_clicked();
}

void SelectMachineDialog::on_pushButtonOK_clicked()
{
    int	Row=ui->tableWidget->currentRow();
    if(Row>=0){
        SelectedMachineID=MachineList.GetItem(Row)->GetValue();
    }
    done(true);
}

void SelectMachineDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

#include "SettingShiftVBandDialog.h"
#include "ui_SettingShiftVBandDialog.h"
#include "XGeneralFunc.h"

SettingShiftVBandDialog::SettingShiftVBandDialog(LayersBase *base
                                    ,VBandInfoContainer &List
                                    ,QWidget *parent) :
    QDialog(parent)
    ,VBands(List)
    ,ui(new Ui::SettingShiftVBandDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 50);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 50);

    ui->tableWidget->setRowCount(VBands.GetCount());
    int Row=0;
    for(VBandInfo *a=VBands.GetFirst();a!=NULL;a=a->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row, QString::number(a->XPos));
        ::SetDataToTable(ui->tableWidget, 1, Row, QString::number(a->ShiftY));
    }
}

SettingShiftVBandDialog::~SettingShiftVBandDialog()
{
    delete ui;
}

void SettingShiftVBandDialog::on_pushButtonOK_clicked()
{
    int RowCount=ui->tableWidget->rowCount();
    VBands.RemoveAll();
    for(int row=0;row<RowCount;row++){
        VBandInfo *a=new VBandInfo();
        a->XPos     =GetDataToTable(ui->tableWidget, 0, row).toInt();
        a->ShiftY   =GetDataToTable(ui->tableWidget, 1, row).toInt();
        VBands.AppendList(a);
    }
    done(true);
}


void SettingShiftVBandDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SettingShiftVBandDialog::on_pushButtonAddLine_clicked()
{
    int RowCount=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(RowCount+1);
}


void SettingShiftVBandDialog::on_pushButtonDelLine_clicked()
{
    int Row=ui->tableWidget->currentRow();
    if(Row>=0){
        ui->tableWidget->removeRow(Row);
    }
}


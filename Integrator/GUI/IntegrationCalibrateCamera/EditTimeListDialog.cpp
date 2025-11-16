#include "EditTimeListDialog.h"
#include "ui_EditTimeListDialog.h"
#include "XGeneralFunc.h"

EditTimeListDialog::EditTimeListDialog(TimeListContainer &LList,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,LContainer(LList)
    ,ui(new Ui::EditTimeListDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget,0, 45);
    ::SetColumnWidthInTable(ui->tableWidget,1, 45);

    ui->tableWidget->setRowCount(LContainer.GetCount());
    int row=0;
    for(TimeList *L=LContainer.GetFirst();L!=NULL;L=L->GetNext(),row++){
        ::SetDataToTable(ui->tableWidget, 0, row, L->Time.hour(), Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget, 1, row, L->Time.minute(), Qt::ItemIsEditable);
    }
}

EditTimeListDialog::~EditTimeListDialog()
{
    delete ui;
}

void EditTimeListDialog::on_pushButtonAddLine_clicked()
{
    int N=ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(N+1);
}


void EditTimeListDialog::on_pushButtonDelLine_clicked()
{
    int row=ui->tableWidget->currentRow();
    if(row<0)
        return;
    ui->tableWidget->removeRow(row);
}


void EditTimeListDialog::on_pushButtonOK_clicked()
{
    int N=ui->tableWidget->rowCount();
    LContainer.RemoveAll();
    for(int row=0;row<N;row++){
        bool    ok;
        int hour=::GetDataToTable(ui->tableWidget, 0, row).toInt(&ok);
        if(ok==false)
            continue;
        int minute=::GetDataToTable(ui->tableWidget, 1, row).toInt(&ok);
        if(ok==false)
            continue;
        TimeList    *t=new TimeList();
        t->Time.setHMS(hour,minute,0,0);
        LContainer.AppendList(t);
    }
    done(true);
}


void EditTimeListDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


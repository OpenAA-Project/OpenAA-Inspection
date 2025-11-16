#include "MasterPositionDialog.h"
#include "ui_MasterPositionDialog.h"
#include "XGeneralFunc.h"

MasterPositionDialog::MasterPositionDialog(MasterPositionListContainer &_MasterPositions ,QWidget *parent) :
    QDialog(parent)
    ,MasterPositions(_MasterPositions)
    ,ui(new Ui::MasterPositionDialog)
{
    ui->setupUi(this);

	SetColumnWidthInTable(ui->tableWidget ,0, 33);
    SetColumnWidthInTable(ui->tableWidget ,1, 33);
    SetColumnWidthInTable(ui->tableWidget ,2, 33);

    ShowGrid();
}

MasterPositionDialog::~MasterPositionDialog()
{
    delete ui;
}

void MasterPositionDialog::ShowGrid(void)
{
    ui->tableWidget->setRowCount(MasterPositions.GetCount());
    int N=MasterPositions.GetCount();
    for(int row=0;row<N;row++){
        MasterPositionList  *L=MasterPositions[row];
        ::SetDataToTable(ui->tableWidget, 0, row, QString::number(L->XPos),Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget, 1, row, QString::number(L->YPos),Qt::ItemIsEditable);
        ::SetDataToTable(ui->tableWidget, 2, row, QString::number(L->ZPos),Qt::ItemIsEditable);
    }
}

void MasterPositionDialog::on_pushButtonAdd_clicked()
{
    MasterPositions.AppendList(new MasterPositionList());
    ShowGrid();
}


void MasterPositionDialog::on_pushButtonSub_clicked()
{
    int Row=ui->tableWidget->currentRow();
    MasterPositionList  *L=MasterPositions[Row];
    if(L!=NULL){
        MasterPositions.RemoveList(L);
        delete  L;
    }
    ShowGrid();
}


void MasterPositionDialog::on_pushButtonOK_clicked()
{
    int N=MasterPositions.GetCount();
    for(int row=0;row<N;row++){
        MasterPositionList  *L=MasterPositions[row];
        QString Sx=::GetDataToTable(ui->tableWidget, 0, row);
        QString Sy=::GetDataToTable(ui->tableWidget, 1, row);
        QString Sz=::GetDataToTable(ui->tableWidget, 2, row);

        L->XPos=Sx.toInt();
        L->YPos=Sy.toInt();
        L->ZPos=Sz.toInt();
    }
    done(true);
}


void MasterPositionDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


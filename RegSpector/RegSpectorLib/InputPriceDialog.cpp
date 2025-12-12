#include "InputPriceDialog.h"
#include "ui_InputPriceDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QTableWidget>
#include <QScrollBar>
#include "XGeneralFunc.h"
#include <QCheckBox>
#include "XServiceRegSpector.h"
    
//===============================================================================
InputPriceDialog::InputPriceDialog(PriceContainer &prices ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputPriceDialog)
{
    ui->setupUi(this);

    Prices=prices;
    QStringListListCSV CSV;
    if(CSV.LoadFromCSVFile(CurrencyListFileName)==true){
        int RowCount=CSV.GetRowCount();
        for(int row=0;row<RowCount;row++){
            QString Code=CSV.Get(0, row).left(3);
            PriceList *t;
            for(t=Prices.GetFirst();t!=NULL;t=t->GetNext()){
                if(t->CurrencyCode==Code){
                    t->CurrencyMark =CSV.Get(1, row);
                    t->CurrencyName =CSV.Get(2, row);
                    t->Head         =(CSV.Get(4, row)=='F')?true:false;
                    break;
                }
            }
            if(t==NULL){
                t=new PriceList;
                t->CurrencyCode=Code;
                t->CurrencyMark =CSV.Get(1, row);
                t->CurrencyName =CSV.Get(2, row);
                t->Head         =(CSV.Get(4, row)=='F')?true:false;
                Prices.AppendList(t);
            }
        }
    }
    int W=width()-64;
    ui->tableWidget->setColumnWidth(0,W*0.15);
    ui->tableWidget->setColumnWidth(1,W*0.45);
    ui->tableWidget->setColumnWidth(2,W*0.4);

    int RowCount=Prices.GetCount();
    ui->tableWidget->setRowCount(RowCount);
    int row=0;
    for(PriceList *t=Prices.GetFirst();t!=NULL;t=t->GetNext(),row++){
        ::SetDataToTable(ui->tableWidget, 0, row, t->CurrencyCode);
        ::SetDataToTable(ui->tableWidget, 1, row, t->CurrencyName);
        ::SetDataToTable(ui->tableWidget, 2, row, QString::number(t->PriceValue,'f',3),Qt::ItemIsEditable);
    }

    setResult(false);
}

InputPriceDialog::~InputPriceDialog()
{
    delete ui;
}

void InputPriceDialog::on_pushButtonSet_clicked()
{
    int row=0;
    for(PriceList *t=Prices.GetFirst();t!=NULL;t=t->GetNext(),row++){
        QString s=GetDataToTable(ui->tableWidget, 2, row);
        t->PriceValue=s.toDouble();
    }
    done(true);
}

void InputPriceDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

#include "FindCountryDialog.h"
#include "ui_FindCountryDialog.h"
#include <QFile>
#include <QTableWidget>
#include <QScrollBar>
#include "XCSV.h"
#include "XGeneralFunc.h"


FindCountryDialog::FindCountryDialog(const QString &CSVFileName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindCountryDialog)
{
    ui->setupUi(this);

    QStringListListCSV  CSV;
    if(CSV.LoadFromCSVFile(CSVFileName)==true){
        int RowCount=CSV.GetRowCount();
        ui->tableWidget->setRowCount(RowCount);
        for(int row=0;row<RowCount;row++){
            QString Code=CSV.Get(0, row).left(2);
            CodeList.append(Code);
            ::SetDataToTable(ui->tableWidget, 0, row, Code);
            ::SetDataToTable(ui->tableWidget, 1, row, CSV.Get(1, row));
            ::SetDataToTable(ui->tableWidget, 2, row, CSV.Get(2, row));
        }
    }
    setResult(false);
}

FindCountryDialog::~FindCountryDialog()
{
    delete ui;
}

void FindCountryDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    int Row=ui->tableWidget->currentRow();
    if(Row>=0){
        CountryCode=CodeList[Row];
        done(true);
    }
}

void FindCountryDialog::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget->resize(width(),height());
    int W=ui->tableWidget->verticalHeader()->width() + ui->tableWidget->verticalScrollBar()->width();
    ui->tableWidget->setColumnWidth(0,(width()-W)*0.150);
    ui->tableWidget->setColumnWidth(1,(width()-W)*0.425);
    ui->tableWidget->setColumnWidth(2,(width()-W)*0.425);
}



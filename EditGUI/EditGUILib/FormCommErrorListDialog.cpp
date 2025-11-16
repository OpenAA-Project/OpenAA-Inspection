#include "FormCommErrorListDialog.h"
#include "ui_FormCommErrorListDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include <QFileDialog>
#include "XCSV.h"

FormCommErrorListDialog::FormCommErrorListDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::FormCommErrorListDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 25);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 11);
    ::SetColumnWidthInTable(ui->tableWidget ,2, 11);
    ::SetColumnWidthInTable(ui->tableWidget ,3, 50);

    ShowList();
}

FormCommErrorListDialog::~FormCommErrorListDialog()
{
    delete ui;
}

void    FormCommErrorListDialog::ShowList(void)
{
    GetLayersBase()->LockMutexCommErrorList();

    ui->tableWidget->setRowCount(GetLayersBase()->GetCommErrorListContainer().GetCount());
    int Row=0;
    for(CommErrorList *L=GetLayersBase()->GetCommErrorListContainer().GetFirst();L!=NULL;L=L->GetNext(),Row++){
        ::SetDataToTable(ui->tableWidget, 0, Row, L->TM.toString());
        ::SetDataToTable(ui->tableWidget, 1, Row, QString::number(L->SlaveNo));
        ::SetDataToTable(ui->tableWidget, 2, Row, QString::number(L->GlobalPage));
        ::SetDataToTable(ui->tableWidget, 3, Row, L->ClassNameStr);
    }
    GetLayersBase()->UnlockMutexCommErrorList();
}

void FormCommErrorListDialog::on_pushButtonOK_clicked()
{
    done(0);
}


void FormCommErrorListDialog::on_pushButtonClear_clicked()
{
    GetLayersBase()->LockMutexCommErrorList();
    GetLayersBase()->GetCommErrorListContainer().RemoveAll();
    GetLayersBase()->UnlockMutexCommErrorList();

    ShowList();
}


void FormCommErrorListDialog::on_pushButtonSave_clicked()
{
    QString FileName=QFileDialog::getSaveFileName(nullptr
                            , "Save comm error list"
                            , QString()
                            , /**/"csv(*.csv);;All file(*.*)");
    if(FileName.isEmpty()==false){
        QStringListListCSV  CSV;
        GetLayersBase()->LockMutexCommErrorList();

        int Row=0;
        for(CommErrorList *L=GetLayersBase()->GetCommErrorListContainer().GetFirst();L!=NULL;L=L->GetNext(),Row++){
            CSV.Set(0, Row ,L->TM.toString());
            CSV.Set(1, Row ,QString::number(L->SlaveNo));
            CSV.Set(2, Row ,QString::number(L->GlobalPage));
            CSV.Set(3, Row ,L->ClassNameStr);
        }
        GetLayersBase()->UnlockMutexCommErrorList();

        CSV.SaveFromCSVFile(FileName);
    }
}


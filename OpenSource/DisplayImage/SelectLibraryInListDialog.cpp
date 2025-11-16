#include "SelectLibraryInListDialog.h"
#include "ui_SelectLibraryInListDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"

SelectLibraryInListDialog::SelectLibraryInListDialog(int libType ,IntList &_LibList
                                                    ,LayersBase *Base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
    ,LibType(libType)
    ,LibList(_LibList)
    ,ui(new Ui::SelectLibraryInListDialog)
{
    ui->setupUi(this);

    ::SetColumnWidthInTable(ui->tableWidget ,0, 20);
    ::SetColumnWidthInTable(ui->tableWidget ,1, 70);

    ui->tableWidget->setRowCount(LibList.GetCount());
    int row=0;
    for(IntClass *v=LibList.GetFirst();v!=NULL;v=v->GetNext(),row++){
        int LibID=v->GetValue();
        ::SetDataToTable(ui->tableWidget,0, row, QString::number(LibID));
        ::SetDataToTable(ui->tableWidget,1, row,GetLayersBase()->GetLibraryName(LibType,LibID));
    }
    SelectedLibID=-1;
}

SelectLibraryInListDialog::~SelectLibraryInListDialog()
{
    delete ui;
}

void SelectLibraryInListDialog::on_pushButtonSelect_clicked()
{
    int Row=ui->tableWidget->currentRow();
    if(Row>0){
        int LibID=LibList[Row];
        SelectedLibID=LibID;
        done(true);
    }
}


void SelectLibraryInListDialog::on_pushButtonCancel_clicked()
{
    done(false);
}


void SelectLibraryInListDialog::on_tableWidget_doubleClicked(const QModelIndex &index)
{
    on_pushButtonSelect_clicked();
}


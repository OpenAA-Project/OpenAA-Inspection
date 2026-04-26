#include "SelectExecuteDialog.h"
#include "ui_SelectExecuteDialog.h"

SelectExecuteDialog::SelectExecuteDialog(LayersBase *Base ,QWidget *parent)
    : QDialog(parent)
    , ServiceForLayers(Base)
    , ui(new Ui::SelectExecuteDialog)
{
    ui->setupUi(this);
    ResultCode  =-1;
}

SelectExecuteDialog::~SelectExecuteDialog()
{
    delete ui;
}

void SelectExecuteDialog::on_pushButtonSaveNew_clicked()
{
    ResultCode  =1;
    done(1);
}


void SelectExecuteDialog::on_pushButtonOverWrite_clicked()
{
    ResultCode  =2;
    done(2);
}


void SelectExecuteDialog::on_pushButtonCancel_clicked()
{
    done(-1);
}


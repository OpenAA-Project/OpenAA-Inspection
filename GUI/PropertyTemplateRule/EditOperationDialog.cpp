#include "EditOperationDialog.h"
#include "ui_EditOperationDialog.h"

EditOperationDialog::EditOperationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditOperationDialog)
{
    ui->setupUi(this);
}

EditOperationDialog::~EditOperationDialog()
{
    delete ui;
}

void EditOperationDialog::on_pushButtonOK_clicked()
{

}


void EditOperationDialog::on_pushButtonCancel_clicked()
{

}


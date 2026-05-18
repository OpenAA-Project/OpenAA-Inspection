#include "EditManualInterpolateDialog.h"
#include "ui_EditManualInterpolateDialog.h"

EditManualInterpolateDialog::EditManualInterpolateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditManualInterpolateDialog)
{
    ui->setupUi(this);
}

EditManualInterpolateDialog::~EditManualInterpolateDialog()
{
    delete ui;
}

void EditManualInterpolateDialog::on_pushButtonDeleteLine_clicked()
{

}


void EditManualInterpolateDialog::on_pushButtonClose_clicked()
{

}


void EditManualInterpolateDialog::on_pushButtonAdd_clicked()
{

}


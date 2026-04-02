#include "EditDenseInterpolateDialog.h"
#include "ui_EditDenseInterpolateDialog.h"

EditDenseInterpolateDialog::EditDenseInterpolateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditDenseInterpolateDialog)
{
    ui->setupUi(this);
}

EditDenseInterpolateDialog::~EditDenseInterpolateDialog()
{
    delete ui;
}

void EditDenseInterpolateDialog::on_pushButtonAddDense_clicked()
{

}


void EditDenseInterpolateDialog::on_pushButtonDeleteLine_clicked()
{

}


void EditDenseInterpolateDialog::on_pushButtonClose_clicked()
{

}


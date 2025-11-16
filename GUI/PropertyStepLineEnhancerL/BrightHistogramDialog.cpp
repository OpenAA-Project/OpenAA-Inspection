#include "BrightHistogramDialog.h"
#include "ui_BrightHistogramDialog.h"

BrightHistogramDialog::BrightHistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrightHistogramDialog)
{
    ui->setupUi(this);
}

BrightHistogramDialog::~BrightHistogramDialog()
{
    delete ui;
}

void BrightHistogramDialog::on_ButtonReflect_clicked()
{

}

void BrightHistogramDialog::on_EditPickupL_valueChanged(int arg1)
{

}

void BrightHistogramDialog::on_EditPickupH_valueChanged(int arg1)
{

}

void BrightHistogramDialog::on_ButtonClose_clicked()
{

}

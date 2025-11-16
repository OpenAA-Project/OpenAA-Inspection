#include "CameraAllocationDialog.h"
#include "ui_CameraAllocationDialog.h"

CameraAllocationDialog::CameraAllocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraAllocationDialog)
{
    ui->setupUi(this);
}

CameraAllocationDialog::~CameraAllocationDialog()
{
    delete ui;
}

void CameraAllocationDialog::on_pushButtonOK_clicked()
{

}

void CameraAllocationDialog::on_pushButtonCancel_clicked()
{

}

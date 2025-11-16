#include "EditGUILibResource.h"
#include "ShareMasterAddDestinationDialog.h"
#include "ui_ShareMasterAddDestinationDialog.h"

ShareMasterAddDestinationDialog::ShareMasterAddDestinationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShareMasterAddDestinationDialog)
{
    ui->setupUi(this);
}

ShareMasterAddDestinationDialog::~ShareMasterAddDestinationDialog()
{
    delete ui;
}

void ShareMasterAddDestinationDialog::on_pushButtonAdd_clicked()
{

}

void ShareMasterAddDestinationDialog::on_pushButtonCancel_clicked()
{

}

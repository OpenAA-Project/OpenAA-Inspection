#include "LoadThresholdDialog.h"
#include "ui_LoadThresholdDialog.h"

LoadThresholdDialog::LoadThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadThresholdDialog)
{
    ui->setupUi(this);
}

LoadThresholdDialog::~LoadThresholdDialog()
{
    delete ui;
}

void LoadThresholdDialog::on_pushButtonSelect_clicked()
{

}


void LoadThresholdDialog::on_pushButtonClose_clicked()
{

}


void LoadThresholdDialog::on_tableWidget_itemSelectionChanged()
{

}


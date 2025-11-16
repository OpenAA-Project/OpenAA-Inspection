#include "SaveThresholdDialog.h"
#include "ui_SaveThresholdDialog.h"

SaveThresholdDialog::SaveThresholdDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveThresholdDialog)
{
    ui->setupUi(this);
}

SaveThresholdDialog::~SaveThresholdDialog()
{
    delete ui;
}

void SaveThresholdDialog::on_pushButtonCreateNew_clicked()
{

}


void SaveThresholdDialog::on_pushButtonModify_clicked()
{

}


void SaveThresholdDialog::on_pushButtonDelete_clicked()
{

}


void SaveThresholdDialog::on_pushButtonClose_clicked()
{

}


void SaveThresholdDialog::on_tableWidget_itemSelectionChanged()
{

}


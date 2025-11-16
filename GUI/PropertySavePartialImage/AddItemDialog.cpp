#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"

AddItemDialog::AddItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}

void AddItemDialog::on_pushButtonOK_clicked()
{

}

void AddItemDialog::on_pushButtonCancel_clicked()
{

}

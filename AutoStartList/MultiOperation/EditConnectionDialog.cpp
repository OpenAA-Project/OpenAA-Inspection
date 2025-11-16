#include "EditConnectionDialog.h"
#include "ui_EditConnectionDialog.h"

EditConnectionDialog::EditConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditConnectionDialog)
{
    ui->setupUi(this);
}

EditConnectionDialog::~EditConnectionDialog()
{
    delete ui;
}

void EditConnectionDialog::on_pushButtonSet_clicked()
{

}

void EditConnectionDialog::on_pushButtonClose_clicked()
{

}

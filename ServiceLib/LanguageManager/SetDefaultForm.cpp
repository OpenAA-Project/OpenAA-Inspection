#include "SetDefaultForm.h"
#include "ui_SetDefaultForm.h"

SetDefaultForm::SetDefaultForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetDefaultForm)
{
    ui->setupUi(this);
}

SetDefaultForm::~SetDefaultForm()
{
    delete ui;
}

void SetDefaultForm::on_pushButtonOK_clicked()
{

}

void SetDefaultForm::on_pushButtonCancel_clicked()
{

}

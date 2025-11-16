#include "ServiceLibResource.h"
#include "SimplePasswordForm.h"
#include "ui_SimplePasswordForm.h"

SimplePasswordForm::SimplePasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SimplePasswordForm)
{
    ui->setupUi(this);
}

SimplePasswordForm::~SimplePasswordForm()
{
    delete ui;
}

void SimplePasswordForm::on_pushButtonOK_clicked()
{
    Password	=ui->lineEditPassword->text();
    done(true);
}

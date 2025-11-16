#include "XTypeDef.h"
#include "CreatePasswordForm.h"
#include "ui_CreatePasswordForm.h"

CreatePasswordForm::CreatePasswordForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreatePasswordForm)
{
    ui->setupUi(this);
}

CreatePasswordForm::~CreatePasswordForm()
{
    delete ui;
}
void	CreatePasswordForm::Initial(const QString &Name)
{
    ui->lineEditPassword->setText(Name);
}
void	CreatePasswordForm::ShowData(void)
{
    ui->lineEditPassword->setText(Password);
}

void CreatePasswordForm::on_pushButtonOK_clicked()
{
    Password=ui->lineEditPassword->text();
    done(true);
}

void CreatePasswordForm::on_pushButtonCancel_clicked()
{
    done(false);
}

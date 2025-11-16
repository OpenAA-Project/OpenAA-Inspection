#include "XTypeDef.h"
#include "CreateClassForm.h"
#include "ui_CreateClassForm.h"

CreateClassForm::CreateClassForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateClassForm)
{
    ui->setupUi(this);
}

CreateClassForm::~CreateClassForm()
{
    delete ui;
}

void	CreateClassForm::Initial(const QString &Name)
{
    ui->lineEditName->setText(Name);
}

void	CreateClassForm::ShowData(void)
{
    ui->lineEditName->setText(ClassName);
}

void CreateClassForm::on_pushButtonOK_clicked()
{
    ClassName=ui->lineEditName->text();
    done(true);
}

void CreateClassForm::on_pushButtonCancel_clicked()
{
    done(false);
}

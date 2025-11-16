#include "ShowNGMessageForm.h"
#include "ui_ShowNGMessageForm.h"

ShowNGMessageForm::ShowNGMessageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowNGMessageForm)
{
    ui->setupUi(this);
}

ShowNGMessageForm::~ShowNGMessageForm()
{
    delete ui;
}

void    ShowNGMessageForm::SetMessage(const QString &msg)
{
    ui->label->setText(msg);
}

void ShowNGMessageForm::on_pushButtonOK_clicked()
{
    hide();
}


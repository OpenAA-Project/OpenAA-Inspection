#include "WindowMismatchForm.h"
#include "ui_WindowMismatchForm.h"
#include "XGeneralFunc.h"

WindowMismatchForm::WindowMismatchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WindowMismatchForm)
{
    ui->setupUi(this);
    ::SetWidgetCenter(this);
}

WindowMismatchForm::~WindowMismatchForm()
{
    delete ui;
}

void WindowMismatchForm::on_pushButtonOK_clicked()
{
    close();
}


#include "OperatingForm.h"
#include "ui_OperatingForm.h"

OperatingForm::OperatingForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OperatingForm)
{
    ui->setupUi(this);
}

OperatingForm::~OperatingForm()
{
    delete ui;
}

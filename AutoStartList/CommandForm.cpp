#include "CommandForm.h"
#include "ui_CommandForm.h"

CommandForm::CommandForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandForm)
{
    ui->setupUi(this);
}

CommandForm::~CommandForm()
{
    delete ui;
}

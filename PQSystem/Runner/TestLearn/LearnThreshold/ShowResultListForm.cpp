#include "ShowResultListForm.h"
#include "ui_ShowResultListForm.h"

ShowResultListForm::ShowResultListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowResultListForm)
{
    ui->setupUi(this);
}

ShowResultListForm::~ShowResultListForm()
{
    delete ui;
}

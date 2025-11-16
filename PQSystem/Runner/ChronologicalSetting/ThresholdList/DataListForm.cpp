#include "DataListForm.h"
#include "ui_DataListForm.h"

DataListForm::DataListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataListForm)
{
    ui->setupUi(this);
}

DataListForm::~DataListForm()
{
    delete ui;
}

#include "AddItemForm.h"
#include "ui_AddItemForm.h"

AddItemForm::AddItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddItemForm)
{
    ui->setupUi(this);
}

AddItemForm::~AddItemForm()
{
    delete ui;
}

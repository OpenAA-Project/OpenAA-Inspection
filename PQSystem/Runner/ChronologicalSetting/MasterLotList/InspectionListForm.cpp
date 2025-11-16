#include "InspectionListForm.h"
#include "ui_InspectionListForm.h"

InspectionListForm::InspectionListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InspectionListForm)
{
    ui->setupUi(this);
}

InspectionListForm::~InspectionListForm()
{
    delete ui;
}

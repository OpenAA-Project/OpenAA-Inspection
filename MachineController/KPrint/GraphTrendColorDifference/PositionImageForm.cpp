#include "GraphTrendColorDifferenceResource.h"
#include "PositionImageForm.h"
#include "ui_PositionImageForm.h"

PositionImageForm::PositionImageForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PositionImageForm)
{
    ui->setupUi(this);
}

PositionImageForm::~PositionImageForm()
{
    delete ui;
}

#include "RWDev3DMouseForm.h"
#include "ui_RWDev3DMouseForm.h"
#include "RWDev3DMouse.h"

RWDev3DMouseForm::RWDev3DMouseForm(RWDev3DMouse *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::RWDev3DMouseForm)
{
    ui->setupUi(this);
}

RWDev3DMouseForm::~RWDev3DMouseForm()
{
    delete ui;
}

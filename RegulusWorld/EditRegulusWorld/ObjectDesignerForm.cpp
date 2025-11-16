#include "ObjectDesignerForm.h"
#include "ui_ObjectDesignerForm.h"
#include "EditRegulusWorld.h"

ObjectDesignerForm::ObjectDesignerForm(EditRegulusWorld *p,QWidget *parent) :
    QWidget(parent)
    ,Parent(p)
    ,ui(new Ui::ObjectDesignerForm)
{
    ui->setupUi(this);
}

ObjectDesignerForm::~ObjectDesignerForm()
{
    delete ui;
}

void ObjectDesignerForm::resizeEvent(QResizeEvent *event)
{
}

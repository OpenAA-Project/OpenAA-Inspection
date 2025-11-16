#include "World3DForm.h"
#include "ui_World3DForm.h"
#include "EditRegulusWorld.h"

World3DForm::World3DForm(EditRegulusWorld *p,QWidget *parent) :
    QWidget(parent)
    ,DisplayImage3D(p->GetWorldBase(),this)
    ,Parent(p)
    ,ui(new Ui::World3DForm)
{
    ui->setupUi(this);

    DisplayImage3D.setParent(this);
    DisplayImage3D.setGeometry(0,0,width(),height());
}

World3DForm::~World3DForm()
{
    delete ui;
}

void World3DForm::resizeEvent(QResizeEvent *event)
{
    DisplayImage3D.setGeometry(0,0,width(),height());
}

#include "RWRobotRunForm.h"
#include "ui_RWRobotRunForm.h"

RWRobotRunForm::RWRobotRunForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::RWRobotRunForm)
{
    ui->setupUi(this);
}

RWRobotRunForm::~RWRobotRunForm()
{
    delete ui;
}

void RWRobotRunForm::on_toolButtonExecute_clicked()
{

}


void RWRobotRunForm::on_toolButtonOrigin_clicked()
{

}


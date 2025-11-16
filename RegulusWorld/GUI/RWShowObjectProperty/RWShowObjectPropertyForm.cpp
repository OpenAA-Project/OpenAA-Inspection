#include "RWShowObjectPropertyForm.h"
#include "ui_RWShowObjectPropertyForm.h"

RWShowObjectPropertyForm::RWShowObjectPropertyForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent)
    ,ui(new Ui::RWShowObjectPropertyForm)
{
    ui->setupUi(this);
}

RWShowObjectPropertyForm::~RWShowObjectPropertyForm()
{
    delete ui;
}

void RWShowObjectPropertyForm::resizeEvent(QResizeEvent *event)
{
    ui->treeWidgetObject->resize(width(),ui->treeWidgetObject->height());
    ui->tableWidgetProperty->resize(width(),height()-ui->tableWidgetProperty->geometry().top());
}

#include "ComponentParameterDialog.h"
#include "ui_ComponentParameterDialog.h"
#include "WEditParameterTab.h"
#include "XParamBase.h"

ComponentParameterDialog::ComponentParameterDialog(ParamBase *P,LayersBase *Base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Param(P)
    ,ui(new Ui::ComponentParameterDialog)
{
    ui->setupUi(this);

    int EnableCondition=ParamEnableInTransfer;
    WTabAlgorithm=new WEditParameterTab(Param ,EnableCondition,NULL);

    WTabAlgorithm->setParent(this);
    WTabAlgorithm->setGeometry(0,0,width(),height()-ui->frameBottom->height());
}

ComponentParameterDialog::~ComponentParameterDialog()
{
    delete ui;
}

void ComponentParameterDialog::on_ButtonOK_clicked()
{
    WTabAlgorithm->LoadFromWindow();
    done(true);
}


void ComponentParameterDialog::on_ButtonCancel_clicked()
{
    done(false);
}


#include "SetSkipMarkForm.h"
#include "ui_SetSkipMarkForm.h"
#include "SelectAreaDialog.h"

SetSkipMarkForm::SetSkipMarkForm(LayersBase *base, QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SetSkipMarkForm)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

SetSkipMarkForm::~SetSkipMarkForm()
{
    delete ui;
}

void SetSkipMarkForm::on_pushButtonModify_clicked()
{

}

void SetSkipMarkForm::on_pushButtonCancel_clicked()
{

}

void SetSkipMarkForm::on_pushButtonSelectArea_clicked()
{

}

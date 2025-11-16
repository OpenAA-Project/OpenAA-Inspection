#include "BlockFormResource.h"
#include "SetOKDialog.h"
#include "ui_SetOKDialog.h"

SetOKDialog::SetOKDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SetOKDialog)
{
    ui->setupUi(this);

	InstallOperationLog(this);
}

SetOKDialog::~SetOKDialog()
{
    delete ui;
}

void SetOKDialog::on_pushButtonBOKBright_clicked()
{

}

void SetOKDialog::on_pushButtonBOKSize_clicked()
{

}

void SetOKDialog::on_pushButtonNOKBright_clicked()
{

}

void SetOKDialog::on_pushButtonNOKSize_clicked()
{

}

void SetOKDialog::on_pushButtonOKSearch_clicked()
{

}

void SetOKDialog::on_pushButtonClose_clicked()
{

}

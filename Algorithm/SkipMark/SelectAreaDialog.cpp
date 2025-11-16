#include "SelectAreaDialog.h"
#include "ui_SelectAreaDialog.h"

SelectAreaDialog::SelectAreaDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectAreaDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

SelectAreaDialog::~SelectAreaDialog()
{
    delete ui;
}

void SelectAreaDialog::on_pushButtonSelect_clicked()
{

}

void SelectAreaDialog::on_pushButtonCancel_clicked()
{

}

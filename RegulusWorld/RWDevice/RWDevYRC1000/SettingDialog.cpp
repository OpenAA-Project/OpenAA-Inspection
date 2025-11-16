#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "ManualOperationDialog.h"

SettingDialog::SettingDialog(LayersBase *Base,RWDevYRC1000 *p,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(Base)
    ,Parent(p)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonManualMode_clicked()
{
    ManualOperationDialog   D;
    D.exec();
}


#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base,bool _UseShouldExecute ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	UseShouldExecute	=_UseShouldExecute;
	ui->checkBoxUseShouldExecute->setChecked(UseShouldExecute);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	UseShouldExecute	=ui->checkBoxUseShouldExecute->isChecked();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

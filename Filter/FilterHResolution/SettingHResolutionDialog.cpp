#include "SettingHResolutionDialog.h"
#include "ui_SettingHResolutionDialog.h"

SettingHResolutionDialog::SettingHResolutionDialog(LayersBase *base,double rate ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingHResolutionDialog)
{
    ui->setupUi(this);
	ui->doubleSpinBoxRate->setValue(rate);

	InstallOperationLog(this);
}

SettingHResolutionDialog::~SettingHResolutionDialog()
{
    delete ui;
}

void SettingHResolutionDialog::on_pushButtonOK_clicked()
{
	Rate=ui->doubleSpinBoxRate->value();
	done(true);
}

void SettingHResolutionDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

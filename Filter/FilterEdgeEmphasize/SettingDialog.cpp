#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterEdgeEmphasize.h"

SettingDialog::SettingDialog(LayersBase *base,FilterEdgeEmphasize *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->doubleSpinBoxStrength	->setValue(FParent->Strength);
	ui->spinBoxRadius			->setValue(FParent->Radius);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->Strength	=ui->doubleSpinBoxStrength	->value();
	FParent->Radius	=ui->spinBoxRadius			->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

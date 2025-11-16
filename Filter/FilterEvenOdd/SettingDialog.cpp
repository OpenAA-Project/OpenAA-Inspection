#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterEvenOdd.h"

SettingDialog::SettingDialog(LayersBase *base,FilterEvenOdd *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->doubleSpinBoxLeftEven	->setValue(FParent->ALeftEven);
	ui->doubleSpinBoxLeftOdd	->setValue(FParent->ALeftOdd);
	ui->doubleSpinBoxRightEven	->setValue(FParent->ARightEven);
	ui->doubleSpinBoxRightOdd	->setValue(FParent->ARightOdd);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->ALeftEven	=ui->doubleSpinBoxLeftEven	->value();
	FParent->ALeftOdd	=ui->doubleSpinBoxLeftOdd	->value();
	FParent->ARightEven	=ui->doubleSpinBoxRightEven	->value();
	FParent->ARightOdd	=ui->doubleSpinBoxRightOdd	->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

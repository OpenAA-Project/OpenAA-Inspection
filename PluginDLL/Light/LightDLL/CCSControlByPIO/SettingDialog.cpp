#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XCCSControlByPIO.h"

SettingDialog::SettingDialog(LightCCSControlByPIO *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBoxBrightness->setValue(p->Brightness[0]);
	ui->toolButtonOnOff->setChecked(p->OnMode[0]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_spinBoxBrightness_editingFinished()
{
	Panel->Brightness[0]=ui->spinBoxBrightness->value();
	Panel->ReflectPhysical();
}

void SettingDialog::on_toolButtonOnOff_clicked()
{
	Panel->ReflectPhysicalTurnOn(ui->toolButtonOnOff->isChecked());
}

void SettingDialog::on_pushButtonOK_clicked()
{
	done(true);
}

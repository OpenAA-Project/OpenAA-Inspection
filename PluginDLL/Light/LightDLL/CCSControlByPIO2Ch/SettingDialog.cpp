#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XCCSControlByPIO2Ch.h"

SettingDialog::SettingDialog(LightCCSControlByPIO2Ch *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBoxBrightness1	->setValue	(p->Brightness[0]);
	ui->toolButtonOnOff1	->setChecked(p->OnMode[0]);
	ui->spinBoxBrightness2	->setValue	(p->Brightness[1]);
	ui->toolButtonOnOff2	->setChecked(p->OnMode[1]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}


void SettingDialog::on_pushButtonOK_clicked()
{
	done(true);
}

void SettingDialog::on_toolButtonOnOff1_clicked()
{
	Panel->OnMode[0]=ui->toolButtonOnOff1->isChecked();
	Panel->ReflectPhysical();
}

void SettingDialog::on_toolButtonOnOff2_clicked()
{
	Panel->OnMode[1]=ui->toolButtonOnOff2->isChecked();
	Panel->ReflectPhysical();

}

void SettingDialog::on_spinBoxBrightness1_valueChanged(int arg1)
{
	Panel->Brightness[0]=ui->spinBoxBrightness1->value();
	Panel->ReflectPhysical();
}

void SettingDialog::on_spinBoxBrightness2_valueChanged(int arg1)
{
	Panel->Brightness[1]=ui->spinBoxBrightness2->value();
	Panel->ReflectPhysical();
}

#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "XCCSControl2.h"

SettingDialog::SettingDialog(LightCCSControl2 *p,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	Panel=p;
	ui->spinBoxBrightness1->setValue(p->Brightness[0]);
	ui->toolButtonOnOff1->setChecked(p->OnMode[0]);
	ui->spinBoxBrightness2->setValue(p->Brightness[1]);
	ui->toolButtonOnOff2->setChecked(p->OnMode[1]);

	p->GetLayersBase()->InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_spinBoxBrightness1_editingFinished()
{
	Panel->Brightness[0]=ui->spinBoxBrightness1->value();
	Panel->Transfer(0,NULL);
}

void SettingDialog::on_spinBoxBrightness2_editingFinished()
{
	Panel->Brightness[1]=ui->spinBoxBrightness2->value();
	Panel->Transfer(0,NULL);
}

void SettingDialog::on_toolButtonOnOff1_clicked()
{
	Panel->SetOnOff(0,ui->toolButtonOnOff1->isChecked());
}

void SettingDialog::on_toolButtonOnOff2_clicked()
{
	Panel->SetOnOff(1,ui->toolButtonOnOff2->isChecked());
}

void SettingDialog::on_pushButton_clicked()
{
	done(true);
}

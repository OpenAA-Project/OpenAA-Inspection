#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(int _CameraNo ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	ui->spinBoxCameraNo->setValue(_CameraNo);
	CameraNo=_CameraNo;
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonSetting_clicked()
{
	CameraNo=ui->spinBoxCameraNo->value();
	done(true);
}

void SettingDialog::on_pushButtonClose_clicked()
{
	done(false);
}

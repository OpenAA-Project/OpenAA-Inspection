#include "SettingCameraDialog.h"
#include "ui_SettingCameraDialog.h"

SettingCameraDialog::SettingCameraDialog(CameraHIKRobotGigE *Cam,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingCameraDialog)
{
    ui->setupUi(this);

	IPAddress				=Cam->IPAddress				;
	ExposureTime			=Cam->ExposureTime			;
	Gain					=Cam->Gain					;
	FrameRate				=Cam->FrameRate				;
    TriggerMode				=Cam->TriggerMode			;
    TriggerSource			=Cam->TriggerSource			;

	ui->lineEditIPAddress	->setText(IPAddress);

	float	CurrentValue ,MaxValue ,MinValue;
	if(Cam->GetfloatValue("ExposureTime",CurrentValue ,MaxValue ,MinValue)==true){
		ui->spinBoxExposureTime	->setMaximum(MaxValue);
	}
	if(Cam->GetfloatValue("Gain",CurrentValue ,MaxValue ,MinValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxValue);
	}

	ui->spinBoxExposureTime	->setValue(ExposureTime);
	ui->doubleSpinBoxGain			->setValue(Gain);

	ui->checkBoxTriggerMode		->setChecked		(TriggerMode);
	ui->comboBoxTriggerSource	->setCurrentIndex	(TriggerSource);
}

SettingCameraDialog::~SettingCameraDialog()
{
    delete ui;
}

void SettingCameraDialog::on_pushButtonSearchDevice_clicked()
{

}


void SettingCameraDialog::on_pushButtonOK_clicked()
{
	ExposureTime	=ui->spinBoxExposureTime	->value();
	Gain			=ui->doubleSpinBoxGain		->value();
	TriggerMode		=ui->checkBoxTriggerMode	->isChecked();
	TriggerSource	= ui->comboBoxTriggerSource	->currentIndex();
	done(true);
}


void SettingCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}


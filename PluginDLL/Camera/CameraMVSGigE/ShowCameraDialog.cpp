#include "ShowCameraDialog.h"
#include "ui_ShowCameraDialog.h"

ShowCameraDialog::ShowCameraDialog(CameraMVSGigE *Cam,QWidget *parent) :
    QDialog(parent)
    ,Parent(Cam)
    ,ui(new Ui::ShowCameraDialog)
{
    ui->setupUi(this);

	ExposureTime			=Cam->ExposureTime			;
	Gain					=Cam->Gain					;
	FrameRate				=Cam->FrameRate				;
	bSoftWareTriggerCheck	=Cam->bSoftWareTriggerCheck	;
	TriggerSource			=Cam->TriggerSource			;
    TriggerMode				=Cam->TriggerMode			;
    TriggerSource			=Cam->TriggerSource			;


	float	CurrentValue ,MaxValue ,MinValue;
	if(Cam->GetfloatValue("ExposureTime",CurrentValue ,MaxValue ,MinValue)==true){
		ui->spinBoxExposureTime	->setMaximum(MaxValue);
	}
	if(Cam->GetfloatValue("Gain",CurrentValue ,MaxValue ,MinValue)==true){
		ui->doubleSpinBoxGain	->setMaximum(MaxValue);
	}

	ui->spinBoxExposureTime	->setValue(ExposureTime);
	ui->doubleSpinBoxGain			->setValue(Gain);
}

ShowCameraDialog::~ShowCameraDialog()
{
    delete ui;
}

void ShowCameraDialog::on_pushButtonOK_clicked()
{
	ExposureTime	=ui->spinBoxExposureTime	->value();
	Gain			=ui->doubleSpinBoxGain		->value();
	done(true);
}


void ShowCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}


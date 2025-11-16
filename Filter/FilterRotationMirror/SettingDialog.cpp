#include "SettingDialog.h"
#include "ui_SettingDialog.h"

SettingDialog::SettingDialog(LayersBase *base
							,bool _UpsideDown
							,bool _LeftRight
							,int _Angle
							,QWidget *parent)
    :QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

	ui->toolButtonMirrorUpDown		->setChecked(_UpsideDown);
	ui->toolButtonMirrorLeftRight	->setChecked(_LeftRight);
	if(_Angle==0){
		ui->radioButtonRot0		->setChecked(true);
	}
	else if(_Angle==90){
		ui->radioButtonRot90	->setChecked(true);
	}
	else if(_Angle==180){
		ui->radioButtonRot180	->setChecked(true);
	}
	else if(_Angle==270){
		ui->radioButtonRot270	->setChecked(true);
	}
	else{
		ui->radioButtonRot0		->setChecked(true);
	}

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	UpsideDown	=ui->toolButtonMirrorUpDown		->isChecked();
	LeftRight	=ui->toolButtonMirrorLeftRight	->isChecked();
	if(ui->radioButtonRot0		->isChecked()==true)
		Angle=0;
	else if(ui->radioButtonRot90 ->isChecked()==true)
		Angle=90;
	else if(ui->radioButtonRot180->isChecked()==true)
		Angle=180;
	else if(ui->radioButtonRot270->isChecked()==true)
		Angle=270;

	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

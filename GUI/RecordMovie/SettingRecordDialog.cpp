#include "SettingRecordDialog.h"
#include "ui_SettingRecordDialog.h"
#include "RecordMovie.h"

SettingRecordDialog::SettingRecordDialog(RecordMovie *p,QWidget *parent) :
    QDialog(parent),ServiceForLayers(p->GetLayersBase())
    ,RecordParent(p)
    ,ui(new Ui::SettingRecordDialog)
{
    ui->setupUi(this);

    if(AVFormatStr==/**/"MotionJPEG"){
        ui->radioButtonAVI->setChecked(true);
    }
    else 
    if(AVFormatStr==/**/"MPEG1"){
        ui->radioButtonMPEG1->setChecked(true);
    }
    ui->comboBoxCamMovieSize	->setCurrentIndex(MovieSizeMode);

	float	TargetFrameRate;
	bool	DivideMovieFile;
}

SettingRecordDialog::~SettingRecordDialog()
{
    delete ui;
}

void SettingRecordDialog::on_pushButtonOK_clicked()
{

}


void SettingRecordDialog::on_pushButtonCancel_clicked()
{

}


void SettingRecordDialog::on_radioButtonAVI_clicked()
{

}


void SettingRecordDialog::on_radioButtonMPEG1_clicked()
{

}


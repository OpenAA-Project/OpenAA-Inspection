#include "SettingDialog.h"
#include "ui_SettingDialog.h"
#include "FilterRemoveNoiseLine.h"

SettingDialog::SettingDialog(LayersBase *base,FilterRemoveNoiseLine *v ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
	FParent=v;

	ui->comboBoxNoiseLineH	->setCurrentIndex((FParent->NoiseLineH==true)?0:1);
	ui->spinBoxNoiseLineWidth	->setValue(FParent->NoiseLineWidth);
	ui->spinBoxThresholdL		->setValue(FParent->ThresholdL);
	ui->spinBoxThresholdH		->setValue(FParent->ThresholdH);

	InstallOperationLog(this);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pushButtonOK_clicked()
{
	FParent->NoiseLineH		=(ui->comboBoxNoiseLineH	->currentIndex()==0)?true:false;
	FParent->NoiseLineWidth	=ui->spinBoxNoiseLineWidth	->value();
	FParent->ThresholdL		=ui->spinBoxThresholdL		->value();
	FParent->ThresholdH		=ui->spinBoxThresholdH		->value();
	done(true);
}

void SettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

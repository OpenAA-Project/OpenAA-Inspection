#include "SettingCameraDialog.h"
#include "ui_SettingCameraDialog.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "math.h"
#include "CLHS_PX8CommandCreater.h"
#include "sapClassBasic.h"
#include "featureCtrl.h"

SettingCameraDialog::SettingCameraDialog(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingCameraDialog)
{
    ui->setupUi(this);
	Setting		=s;
	Feature		=f;
	Setting->LoadFromCam(Feature);

	ui->spinBoxStartPos				->setValue(Setting->StartPos);
	ui->spinBoxRefStart				->setValue(Setting->RefStart);
	ui->spinBoxBindedPixels			->setValue(Setting->BindedPixels);

	ui->spinBoxLineRate				->setValue(Setting->LineRate);
	ui->doubleSpinBoxExposureTime	->setValue(Setting->ExposureTime);
	ui->checkBoxDirection			->setChecked(Setting->TDIDirection);
	ui->doubleSpinBoxGainRed		->setValue(Setting->GainRed);
	ui->spinBoxOffsetRed			->setValue(Setting->OffsetRed);
	ui->spinBoxHorizontalBinning	->setValue(Setting->HorizontalBinning);
	ui->spinBoxVerticalBinning		->setValue(Setting->VerticalBinning);
	ui->checkBoxLeftRight			->setChecked(Setting->LeftRight);
	ui->checkBoxExternalTrigger		->setChecked(Setting->ExternalTrigger);
}

SettingCameraDialog::~SettingCameraDialog()
{
    delete ui;
}

void SettingCameraDialog::on_pushButtonOK_clicked()
{
	Setting->StartPos		=ui->spinBoxStartPos			->value();
	Setting->RefStart		=ui->spinBoxRefStart			->value();
	Setting->BindedPixels	=ui->spinBoxBindedPixels		->value();

	Setting->LineRate		=ui->spinBoxLineRate			->value();
	Setting->ExposureTime	=ui->doubleSpinBoxExposureTime	->value();
	Setting->TDIDirection	=ui->checkBoxDirection			->isChecked();

	Setting->GainRed		=ui->doubleSpinBoxGainRed		->value();
	Setting->OffsetRed		=ui->spinBoxOffsetRed			->value();

	Setting->HorizontalBinning	=ui->spinBoxHorizontalBinning	->value();
	Setting->VerticalBinning	=ui->spinBoxVerticalBinning		->value();
	Setting->LeftRight			=ui->checkBoxLeftRight			->isChecked();
	Setting->ExternalTrigger	=ui->checkBoxExternalTrigger	->isChecked();
	Setting->StoreToCam(Feature);

	done(true);
}


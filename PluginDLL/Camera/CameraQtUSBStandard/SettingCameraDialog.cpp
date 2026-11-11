/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "SettingCameraDialog.h"
#include "ui_SettingCameraDialog.h"
#include "XGUIFormBase.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCamera>
#include "swap.h"
#include "CameraQtUSBStandard.h"
#include <QMediaDevices>

SettingCameraDialog::SettingCameraDialog(LayersBase *Base ,USBQtCamera *C ,QWidget *parent) :
    QDialog(NULL),
    ui(new Ui::SettingCameraDialog)
	,Cam(C)
	,ServiceForLayers(Base)
{
    ui->setupUi(this);
	UpdatingUI	=false;

    QCamera *camera=Cam->GetCamera();
	camera->setActive(true);

    ui->comboBoxResolution  ->clear();

	UpdatingUI = true;
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(Cam->CamNo);
	int		CurrentIndex = 0;
	int		n=0;
	for (const QCameraFormat &format : CamDevice.videoFormats()) {
		const QSize size=format.resolution();

        QString s=QString(/**/"X:"   )+QString::number(size.width())
                 +QString(/**/" - Y:")+QString::number(size.height());
        ui->comboBoxResolution  ->addItem(s);
        if(size==Cam->CurrentResolution){
            CurrentIndex=n;
			break;
        }
		n++;
    }
	ui->comboBoxResolution->setCurrentIndex(CurrentIndex);
	UpdatingUI = false;

    CurrentExposureMode =camera->exposureMode();
	ui->comboBoxExposureMode->setCurrentIndex((int)CurrentExposureMode);

	CurrentFlashMode = camera->flashMode();
	ui->comboBoxFlashMode->setCurrentIndex((int)CurrentFlashMode);

	CurrentExposureCompensation = camera->exposureCompensation();
	ui->doubleSpinBoxExposureCompensation->setValue(CurrentExposureCompensation);
	ui->horizontalSliderExposureCompensation->setValue((int)(CurrentExposureCompensation));

	CurrentISO  = camera->isoSensitivity();
	ui->spinBoxIsoSensitivity->setValue(CurrentISO);
	ui->horizontalSliderIsoSensitivity->setValue(CurrentISO);


	//QWidget	*WFocusMode=ui->tabWidget->widget(4);
	//WFocusMode->setEnabled(camera->focus()->isAvailable());
	CurrentFocusMode = camera->focusMode();
	ui->checkBoxManualFocus		->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeManual		));
	ui->checkBoxAutoFocus		->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeAuto		));
	ui->checkBoxContinuousFocus	->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeAutoNear	));
	ui->checkBoxMacroFocus		->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeAutoFar		));
	ui->checkBoxInfinityFocus	->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeInfinity	));
	ui->checkBoxHyperfocalFocus	->setEnabled(camera->isFocusModeSupported(QCamera::FocusModeHyperfocal	));

	ui->checkBoxManualFocus		->setChecked((CurrentFocusMode & QCamera::FocusModeManual	) != 0);
	ui->checkBoxAutoFocus		->setChecked((CurrentFocusMode & QCamera::FocusModeAuto		) != 0);
	ui->checkBoxContinuousFocus	->setChecked((CurrentFocusMode & QCamera::FocusModeAutoNear	) != 0);
	ui->checkBoxMacroFocus		->setChecked((CurrentFocusMode & QCamera::FocusModeAutoFar	) != 0);
	ui->checkBoxInfinityFocus	->setChecked((CurrentFocusMode & QCamera::FocusModeInfinity	) != 0);
	ui->checkBoxHyperfocalFocus	->setChecked((CurrentFocusMode & QCamera::FocusModeHyperfocal) != 0);

	CurrentFocusDistance	= camera->focusDistance();
	ui->doubleSpinBoxFocusDistance->setValue(CurrentFocusDistance);
	ui->horizontalSliderFocusDistance->setValue(CurrentFocusDistance);

	CurrentCustomFocusPoint = camera->customFocusPoint();
	ui->doubleSpinBoxCustomFocusPointX->setValue(CurrentCustomFocusPoint.x());
	ui->doubleSpinBoxCustomFocusPointY->setValue(CurrentCustomFocusPoint.y());

	CurrentWhiteBalanceMode = camera->whiteBalanceMode();
	ui->comboBoxWhiteBalanceMode->setCurrentIndex((int)CurrentWhiteBalanceMode);
	CurrentColorTemperature = camera->colorTemperature();
	ui->doubleSpinBoxManualWhiteBalance->setValue(CurrentColorTemperature);
	ui->horizontalSliderManualWhiteBalance->setValue((int)(CurrentColorTemperature));

	ui->comboBoxTorchMode->setCurrentIndex((int)CurrentTorchMode);

	ui->doubleSpinBoxManualWhiteBalance->setMinimum(MIN_COLOR_TEMP);
	ui->doubleSpinBoxManualWhiteBalance->setMaximum(MAX_COLOR_TEMP);
	ui->horizontalSliderManualWhiteBalance->setMinimum(MIN_COLOR_TEMP);
	ui->horizontalSliderManualWhiteBalance->setMaximum(MAX_COLOR_TEMP);

	on_comboBoxResolution_currentIndexChanged(0);
	on_comboBoxExposureMode_currentIndexChanged(0);
	on_comboBoxWhiteBalanceMode_currentIndexChanged(0);
}

SettingCameraDialog::~SettingCameraDialog()
{
    delete ui;
}

void SettingCameraDialog::on_horizontalSliderExposureCompensation_valueChanged(int value)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;

	ui->doubleSpinBoxExposureCompensation->setValue((double)(value));
	UpdatingUI = false;
}


void SettingCameraDialog::on_doubleSpinBoxExposureCompensation_valueChanged(double arg1)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;
	ui->horizontalSliderExposureCompensation->setValue((int)(arg1));
	UpdatingUI = false;
}


void SettingCameraDialog::on_horizontalSliderIsoSensitivity_valueChanged(int value)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;
	ui->spinBoxIsoSensitivity->setValue(value);
	UpdatingUI = false;
}


void SettingCameraDialog::on_spinBoxIsoSensitivity_valueChanged(int arg1)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;
	ui->horizontalSliderIsoSensitivity->setValue(arg1);
	UpdatingUI = false;
}


void SettingCameraDialog::on_horizontalSliderManualWhiteBalance_valueChanged(int value)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;
	ui->doubleSpinBoxManualWhiteBalance->setValue((double)(value));
	UpdatingUI = false;
}


void SettingCameraDialog::on_doubleSpinBoxManualWhiteBalance_valueChanged(double arg1)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;
	ui->horizontalSliderManualWhiteBalance->setValue((int)(arg1));
	UpdatingUI = false;
}


void SettingCameraDialog::on_pushButtonOK_clicked()
{
	QCamera *camera=Cam->GetCamera();
	int	ResolutionIndex=ui->comboBoxResolution  ->currentIndex();
	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(Cam->CamNo);
	int		CurrentIndex = 0;
	int		n=0;
	const QCameraFormat format=CamDevice.videoFormats().at(ResolutionIndex);
	CurrentResolution	=format.resolution();
	
	CurrentExposureMode	=(QCamera::ExposureMode)ui->comboBoxExposureMode->currentIndex();
	CurrentFlashMode	=(QCamera::FlashMode)ui->comboBoxFlashMode->currentIndex();
	CurrentExposureCompensation	=ui->doubleSpinBoxExposureCompensation->value();
	CurrentISO			=ui->spinBoxIsoSensitivity->value(); 
	CurrentFocusMode	=(QCamera::FocusMode)(
		((ui->checkBoxManualFocus		->isChecked()==true)?QCamera::FocusModeManual		:0)|
		((ui->checkBoxAutoFocus			->isChecked()==true)?QCamera::FocusModeAuto			:0)|
		((ui->checkBoxContinuousFocus	->isChecked()==true)?QCamera::FocusModeAutoNear		:0)|
		((ui->checkBoxMacroFocus		->isChecked()==true)?QCamera::FocusModeAutoFar		:0)|
		((ui->checkBoxInfinityFocus		->isChecked()==true)?QCamera::FocusModeInfinity		:0)|
		((ui->checkBoxHyperfocalFocus	->isChecked()==true)?QCamera::FocusModeHyperfocal	:0));
	CurrentFocusDistance=ui->doubleSpinBoxFocusDistance->value();

	double	fX=ui->doubleSpinBoxCustomFocusPointX->value();
	double	fY=ui->doubleSpinBoxCustomFocusPointY->value();
	CurrentCustomFocusPoint	=QPointF(fX,fY);
	CurrentWhiteBalanceMode	=(QCamera::WhiteBalanceMode)ui->comboBoxWhiteBalanceMode->currentIndex();
	CurrentColorTemperature	=ui->doubleSpinBoxManualWhiteBalance->value();
	CurrentTorchMode			=(QCamera::TorchMode)ui->comboBoxTorchMode->currentIndex();

	done(true);
}


void SettingCameraDialog::on_pushButtonCancel_clicked()
{
	done(false);
}


void SettingCameraDialog::on_comboBoxResolution_currentIndexChanged(int)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;

	QCamera *camera=Cam->GetCamera();
// 1. カメラが有効か確認

	const QList<QCameraDevice> availableDevices = QMediaDevices::videoInputs();
	QCameraDevice	CamDevice = availableDevices.at(Cam->CamNo);

    // 3. 現在のアクティブなフォーマットを取得
    // ※カメラを開始する前、または開始後に設定されているフォーマット
    QCameraFormat currentFormat=CamDevice.videoFormats().at(ui->comboBoxResolution->currentIndex());
    if (currentFormat.isNull()) {
        qDebug() << "No active format set.";
		UpdatingUI = false;
        return;
    }

    qreal minFps = currentFormat.minFrameRate();
    qreal maxFps = currentFormat.maxFrameRate();

    float maxExposureTime = camera->maximumExposureTime();
    if (maxExposureTime<0 && minFps > 0) {
        maxExposureTime = 1.0f / minFps;
    }
    float minExposureTime = camera->minimumExposureTime();
    if (minExposureTime<0 && maxFps > 0) {
        minExposureTime = 1.0f / maxFps;
    }
	ui->doubleSpinBoxExposureCompensation->setMinimum(minExposureTime * 1000.0); // ミリ秒単位[ms]
	ui->doubleSpinBoxExposureCompensation->setMaximum(maxExposureTime * 1000.0); // ミリ秒単位[ms]
	ui->horizontalSliderExposureCompensation->setMinimum((int)(minExposureTime * 1000.0)); // ミリ秒単位[ms]
	ui->horizontalSliderExposureCompensation->setMaximum((int)(maxExposureTime * 1000.0)); // ミリ秒単位[ms]

	float	minimumIso=camera->minimumIsoSensitivity();
	float	maximumIso=camera->maximumIsoSensitivity();
	if(minimumIso>=0){
		ui->horizontalSliderIsoSensitivity->setMinimum(minimumIso);
		ui->spinBoxIsoSensitivity->setMinimum(minimumIso);
	}
	if(maximumIso>=0){
		ui->spinBoxIsoSensitivity->setMaximum(maximumIso);
		ui->horizontalSliderIsoSensitivity->setMaximum(maximumIso);
	}
	UpdatingUI = false;
}


void SettingCameraDialog::on_comboBoxExposureMode_currentIndexChanged(int)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;

	QCamera *camera=Cam->GetCamera();
	if((QCamera::ExposureMode)ui->comboBoxExposureMode->currentIndex()==QCamera::ExposureManual
	&& camera->isExposureModeSupported(QCamera::ExposureManual)==true){
		ui->widgetExposureCompensation->setEnabled(true);
	}
	else{
		ui->widgetExposureCompensation->setEnabled(false);
	}
	UpdatingUI = false;
}


void SettingCameraDialog::on_comboBoxWhiteBalanceMode_currentIndexChanged(int)
{
	if(UpdatingUI==true)
		return;
	UpdatingUI = true;

	QCamera *camera=Cam->GetCamera();
	if((QCamera::WhiteBalanceMode)ui->comboBoxWhiteBalanceMode->currentIndex()==QCamera::WhiteBalanceManual
	&& camera->isWhiteBalanceModeSupported(QCamera::WhiteBalanceManual)==true){
		ui->widgetManualWhiteBalance->setEnabled(true);
	}
	else{
		ui->widgetManualWhiteBalance->setEnabled(false);
	}
	UpdatingUI = false;
}

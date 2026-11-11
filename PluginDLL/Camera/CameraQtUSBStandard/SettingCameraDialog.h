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

#ifndef SETTINGCAMERADIALOG_H
#define SETTINGCAMERADIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QSlider>
#include "CameraQtUSBStandard.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingCameraDialog;
}

class  USBQtCamera;
const int MIN_COLOR_TEMP = 2000;  // �g�F�i�I�����W�����j
const int MAX_COLOR_TEMP = 10000; // ���F�i�����j

class SettingCameraDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT

    USBQtCamera *Cam;
	bool   UpdatingUI;

public:
	QSize						CurrentResolution;
    QCamera::ExposureMode		CurrentExposureMode;
    QCamera::FlashMode			CurrentFlashMode;
    qreal						CurrentExposureCompensation;
	int							CurrentISO; 
    QCamera::FocusMode			CurrentFocusMode;
    qreal						CurrentFocusDistance;
	QPointF						CurrentCustomFocusPoint;
    QCamera::WhiteBalanceMode	CurrentWhiteBalanceMode;
	int							CurrentColorTemperature;
	QCamera::TorchMode			CurrentTorchMode;

public:
    explicit SettingCameraDialog(LayersBase *Base ,USBQtCamera *C,QWidget *parent = 0);
    ~SettingCameraDialog();    

private slots:


    void on_horizontalSliderExposureCompensation_valueChanged(int value);
    void on_doubleSpinBoxExposureCompensation_valueChanged(double arg1);
    void on_horizontalSliderIsoSensitivity_valueChanged(int value);
    void on_spinBoxIsoSensitivity_valueChanged(int arg1);

    void on_horizontalSliderManualWhiteBalance_valueChanged(int value);
    void on_doubleSpinBoxManualWhiteBalance_valueChanged(double arg1);

    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_comboBoxResolution_currentIndexChanged(int index);

    void on_comboBoxExposureMode_currentIndexChanged(int index);

    void on_comboBoxWhiteBalanceMode_currentIndexChanged(int index);

private:
    Ui::SettingCameraDialog *ui;


};

#endif // SETTINGCAMERADIALOG_H
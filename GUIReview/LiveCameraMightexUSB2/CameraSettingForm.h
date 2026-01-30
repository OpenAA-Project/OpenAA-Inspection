/*
 * Copyright (C) 2016
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

#pragma once

#include <QDialog>

#include "ui_CameraSettingForm.h"

class CameraSettingForm : public QDialog
{
	Q_OBJECT

public:
	CameraSettingForm(int deviceID, QWidget *parent=0, Qt::WindowFlags f=0);
	~CameraSettingForm();

	void setDeviceInfomation(const QString &moduleNo, const QString &serialNo);
	void setExposureTime(int exp);
	void setGainR(quint8 val);
	void setGainG(quint8 val);
	void setGainB(quint8 val);
	void setGamma(double val);
	void setResolution(double val);

	int exposureTime() const;
	quint8 gainR() const;
	quint8 gainG() const;
	quint8 gainB() const;
	double gamma() const;
	quint8 resolution() const;

	void setTriggerMode(bool trigger);
	bool triggerMode() const;

protected slots:
	void on_pbShowFactoryControlPanelButton_clicked();
	void on_sbExposureTime_valueChanged(int);

private:
	Ui::CameraSettingClass m_ui;
	int m_deviceID;
};

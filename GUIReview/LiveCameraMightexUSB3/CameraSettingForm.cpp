/*
 * Copyright (C) 2017
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

#include "LiveCameraMightexUSB3Resource.h"
#include "CameraSettingForm.h"

#include "SDK\Lib\x64\SSClassic_USBCamera_SDK.h"

#include <QMessageBox>

CameraSettingForm::CameraSettingForm(int deviceID, QWidget *parent, Qt::WindowFlags f)
	:QDialog(parent, f),m_deviceID(deviceID)
{
	m_ui.setupUi(this);
}

CameraSettingForm::~CameraSettingForm()
{
	SSClassicUSB_HideFactoryControlPanel();
}

void CameraSettingForm::setDeviceInfomation(const QString &moduleNo, const QString &serialNo)
{
	m_ui.leModuleNo->setText(moduleNo);
	m_ui.leSerialNo->setText(serialNo);
}

void CameraSettingForm::setExposureTime(int exp)
{
	m_ui.sbExposureTime->setValue(exp);
}

void CameraSettingForm::setGainR(quint8 val)
{
	m_ui.sbGainR->setValue(val);
}

void CameraSettingForm::setGainG(quint8 val)
{
	m_ui.sbGainG->setValue(val);
}

void CameraSettingForm::setGainB(quint8 val)
{
	m_ui.sbGainB->setValue(val);
}

void CameraSettingForm::on_pbShowFactoryControlPanelButton_clicked()
{
	int ret = SSClassicUSB_ShowFactoryControlPanel(m_deviceID, /**/"123456");
	if(ret<0){
		QMessageBox::warning(this
							, LangSolver.GetString(CameraSettingForm_LS,LID_0)/*"fault to show"*/
							, QString(/**/"Can't show the factory control panel\nErrorCode = %1").arg(ret));
	}
}

void CameraSettingForm::on_sbExposureTime_valueChanged(int value)
{
	int us = m_ui.sbExposureTime->value() * 50;

	if(us<1000){
		m_ui.lbExposureTime->setText(QString(/**/"%1 us").arg(us));
	}else{
		m_ui.lbExposureTime->setText(QString(/**/"%1 ms").arg((qreal)us/1000.0));
	}
}

int CameraSettingForm::exposureTime() const
{
	return m_ui.sbExposureTime->value();
}

quint8 CameraSettingForm::gainR() const
{
	return m_ui.sbGainR->value();
}

quint8 CameraSettingForm::gainG() const
{
	return m_ui.sbGainG->value();
}

quint8 CameraSettingForm::gainB() const
{
	return m_ui.sbGainB->value();
}

void CameraSettingForm::setTriggerMode(bool trigger)
{
	if(trigger==0){// freeRun
		m_ui.rbFreeRun->setChecked(true);
	}else{
		m_ui.rbTrigger->setChecked(true);
	}
}

bool CameraSettingForm::triggerMode() const
{
	return m_ui.rbTrigger->isChecked();
}
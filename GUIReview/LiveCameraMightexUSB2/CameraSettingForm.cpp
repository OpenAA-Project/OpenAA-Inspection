#include "LiveCameraMightexUSB2Resource.h"
#include "CameraSettingForm.h"
typedef	unsigned char	byte;
#include "BUF_USBCamera_SDK.h"
#include <QMessageBox>

CameraSettingForm::CameraSettingForm(int deviceID, QWidget *parent, Qt::WindowFlags f)
	:QDialog(parent, f),m_deviceID(deviceID)
{
	m_ui.setupUi(this);
}

CameraSettingForm::~CameraSettingForm()
{
	//SSClassicUSB_HideFactoryControlPanel();
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

void CameraSettingForm::setGamma(double val)
{
	m_ui.doubleSpinBoxGamma->setValue(val);
}

void CameraSettingForm::setResolution(double val)
{
	m_ui.comboBoxResolution->setCurrentIndex(val);
}

void CameraSettingForm::on_pbShowFactoryControlPanelButton_clicked()
{
	//int ret = SSClassicUSB_ShowFactoryControlPanel(m_deviceID, "123456");
	//if(ret<0){
	//	QMessageBox::warning(this, "fault to show", QString("Can't show the factory control panel\nErrorCode = %1").arg(ret));
	//}
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
double CameraSettingForm::gamma() const
{
	return m_ui.doubleSpinBoxGamma->value();
}

quint8 CameraSettingForm::resolution() const
{
	return m_ui.comboBoxResolution->currentIndex();
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

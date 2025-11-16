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

	int exposureTime() const;
	quint8 gainR() const;
	quint8 gainG() const;
	quint8 gainB() const;

	void setTriggerMode(bool trigger);
	bool triggerMode() const;

protected slots:
	void on_pbShowFactoryControlPanelButton_clicked();
	void on_sbExposureTime_valueChanged(int);

private:
	Ui::CameraSettingClass m_ui;
	int m_deviceID;
};


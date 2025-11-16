#pragma once

#include <QDialog>

#include "ui_VRSSettingForm.h"

#include "XReviewCommon.h"

class VRSSetting;

class VRSSettingForm : public QDialog
{
	Q_OBJECT

public:
	VRSSettingForm(QWidget *parent=NULL);
	~VRSSettingForm();
public:
	void setVRSSetting(const VRSSetting &);
	VRSSetting result() const;
	VRSSetting getVRSSetting() const;

private slots:
	void checkValidUi();

private:
	Ui::VRSSettingClass ui;
	VRSSetting *m_VRSSetting;
};

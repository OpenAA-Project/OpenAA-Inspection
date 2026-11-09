#ifndef SETTINGCAMERADIALOG_H
#define SETTINGCAMERADIALOG_H

#include <QDialog>
#include <QString>
#include "CameraHIKRobotGigE.h"

namespace Ui {
class SettingCameraDialog;
}

class SettingCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingCameraDialog(CameraHIKRobotGigE *Cam,QWidget *parent = nullptr);
    ~SettingCameraDialog();

	QString		IPAddress;
	float		ExposureTime;
	float		Gain;
	float		FrameRate;
    int			TriggerMode;                       // ch:触发模式 | en:Trigger Mode
    int			TriggerSource;                     // ch:触发源 | en:Trigger Source

private slots:
    void on_pushButtonSearchDevice_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingCameraDialog *ui;
};

#endif // SETTINGCAMERADIALOG_H

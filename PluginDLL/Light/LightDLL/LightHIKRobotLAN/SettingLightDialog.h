#ifndef SETTINGLIGHTDIALOG_H
#define SETTINGLIGHTDIALOG_H

#include <QDialog>

namespace Ui {
class SettingLightDialog;
}

class LightHIKRobotLAN;
class LightSourceValue;

class SettingLightDialog : public QDialog
{
    Q_OBJECT

public:
	int			ChannelCount;
	QStringList	ChannelNames;
	LightSourceValue	*LightDim;
    LightHIKRobotLAN    *Parent;

public:
    explicit SettingLightDialog(LightHIKRobotLAN *p,QWidget *parent = nullptr);
    ~SettingLightDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingLightDialog *ui;
};

#endif // SETTINGLIGHTDIALOG_H

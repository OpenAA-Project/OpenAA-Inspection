#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class	LightCCSControlByPIO2Ch;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	LightCCSControlByPIO2Ch *Panel;

public:
    explicit SettingDialog(LightCCSControlByPIO2Ch *p,QWidget *parent = 0);
    ~SettingDialog();
    
	void	ShowValue(void);

private slots:
    void on_pushButtonOK_clicked();
    void on_toolButtonOnOff1_clicked();
    void on_toolButtonOnOff2_clicked();
    void on_spinBoxBrightness1_valueChanged(int arg1);
    void on_spinBoxBrightness2_valueChanged(int arg1);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

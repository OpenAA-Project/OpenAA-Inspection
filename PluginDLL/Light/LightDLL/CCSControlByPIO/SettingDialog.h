#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class	LightCCSControlByPIO;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	LightCCSControlByPIO *Panel;

public:
    explicit SettingDialog(LightCCSControlByPIO *p,QWidget *parent = 0);
    ~SettingDialog();
    
	void	ShowValue(void);

private slots:
    void on_spinBoxBrightness_editingFinished();
    void on_toolButtonOnOff_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

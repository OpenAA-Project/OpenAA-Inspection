#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class	LightCCSControl;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	LightCCSControl *Panel;

public:
    explicit SettingDialog(LightCCSControl *p,QWidget *parent = 0);
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class	LightCCSControl2;

class SettingDialog : public QDialog
{
    Q_OBJECT

    LightCCSControl2 *Panel;

public:
    explicit SettingDialog(LightCCSControl2 *p,QWidget *parent = 0);
    ~SettingDialog();
    
	void	ShowValue(void);

private slots:
    void on_spinBoxBrightness1_editingFinished();
    void on_spinBoxBrightness2_editingFinished();
    void on_toolButtonOnOff1_clicked();
    void on_toolButtonOnOff2_clicked();
    void on_pushButton_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class	LightControlHayashiTokei;

class SettingDialog : public QDialog
{
    Q_OBJECT
    
	LightControlHayashiTokei	*Panel;

public:
    explicit SettingDialog(LightControlHayashiTokei *p,QWidget *parent = 0);
    ~SettingDialog();
    
	void	ShowValue(void);

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_toolButtonON_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_comboBoxLEDNumber_currentIndexChanged(int index);

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(int CameraNo ,QWidget *parent = 0);
    ~SettingDialog();

	int	CameraNo;

private slots:
    void on_pushButtonSetting_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

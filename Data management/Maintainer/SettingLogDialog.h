#ifndef SETTINGLOGDIALOG_H
#define SETTINGLOGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingLogDialog;
}
class Maintainer;

class SettingLogDialog : public QDialog
{
    Q_OBJECT
    Maintainer	*Parent;

public:
    explicit SettingLogDialog(Maintainer *p,QWidget *parent = 0);
    ~SettingLogDialog();
    
private slots:
    void on_pushButtonSelectFile_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingLogDialog *ui;
};

#endif // SETTINGLOGDIALOG_H

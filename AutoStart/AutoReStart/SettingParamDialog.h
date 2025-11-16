#ifndef SETTINGPARAMDIALOG_H
#define SETTINGPARAMDIALOG_H

#include <QDialog>

namespace Ui {
class SettingParamDialog;
}

class AutoReStart;

class SettingParamDialog : public QDialog
{
    Q_OBJECT

    AutoReStart *Parent;
public:
    explicit SettingParamDialog(AutoReStart *p ,QWidget *parent = nullptr);
    ~SettingParamDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSelectFileName_clicked();
    void on_pushButtonSelectPath_clicked();

private:
    Ui::SettingParamDialog *ui;
};

#endif // SETTINGPARAMDIALOG_H

#ifndef SETTINGCOLORSHIFTDIALOG_H
#define SETTINGCOLORSHIFTDIALOG_H

#include <QDialog>

namespace Ui {
    class SettingColorShiftDialog;
}

class SettingColorShiftDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingColorShiftDialog(QWidget *parent = 0);
    ~SettingColorShiftDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingColorShiftDialog *ui;
};

#endif // SETTINGCOLORSHIFTDIALOG_H

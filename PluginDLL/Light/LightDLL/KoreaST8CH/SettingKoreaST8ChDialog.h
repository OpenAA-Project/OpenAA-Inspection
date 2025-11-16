#ifndef SETTINGKOREAST8CHDIALOG_H
#define SETTINGKOREAST8CHDIALOG_H

#include <QDialog>

namespace Ui {
class SettingKoreaST8ChDialog;
}
class	KoreaST8ChPanel;

class SettingKoreaST8ChDialog : public QDialog
{
    Q_OBJECT

	KoreaST8ChPanel	*Panel;

public:
    explicit SettingKoreaST8ChDialog(KoreaST8ChPanel *panel ,QWidget *parent = 0);
    ~SettingKoreaST8ChDialog();

private slots:
    void on_pushButtonTransmit_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::SettingKoreaST8ChDialog *ui;
};

#endif // SETTINGKOREAST8CHDIALOG_H

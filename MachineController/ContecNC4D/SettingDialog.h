#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XContecNC4DInfo.h"

namespace Ui {
class SettingDialog;
}

class	ContecNC4D;

class SettingDialog : public QDialog
{
    Q_OBJECT
    ContecNC4DInfo	*Data;
public:
    explicit SettingDialog(ContecNC4DInfo *info ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

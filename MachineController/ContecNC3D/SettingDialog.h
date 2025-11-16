#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XContecNC3DInfo.h"

namespace Ui {
class SettingDialog;
}

class	ContecNC3D;

class SettingDialog : public QDialog
{
    Q_OBJECT
    ContecNC3DInfo	*Data;
public:
    explicit SettingDialog(ContecNC3DInfo *info ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

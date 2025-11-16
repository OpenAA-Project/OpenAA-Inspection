#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}
class	FilterEvenOdd;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    FilterEvenOdd	*FParent;
public:
    explicit SettingDialog(LayersBase *base,FilterEvenOdd *v ,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

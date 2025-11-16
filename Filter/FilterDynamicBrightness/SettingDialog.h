#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class FilterDynamicBrightness;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    FilterDynamicBrightness	*FParent;
public:
    explicit SettingDialog(LayersBase *base,FilterDynamicBrightness *v ,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

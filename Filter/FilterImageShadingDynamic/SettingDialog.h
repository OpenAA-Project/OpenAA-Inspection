#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}
class	FilterImageShadingDynamic;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    FilterImageShadingDynamic   *Parent;
public:
    explicit SettingDialog(LayersBase *base,FilterImageShadingDynamic *p ,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

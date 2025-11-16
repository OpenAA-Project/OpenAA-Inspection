#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class RWDevYRC1000;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RWDevYRC1000    *Parent;
public:
    explicit SettingDialog(LayersBase *Base,RWDevYRC1000 *p,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_pushButtonManualMode_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

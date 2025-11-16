#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class FilterMergeColor;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    FilterMergeColor    *Parent;
public:
    explicit SettingDialog(LayersBase *base,FilterMergeColor *p,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

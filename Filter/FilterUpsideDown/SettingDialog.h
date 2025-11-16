#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingDialog(LayersBase *base,bool	UseShouldExecute ,QWidget *parent = 0);
    ~SettingDialog();

	bool	UseShouldExecute;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

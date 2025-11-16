#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}
class	FilterEdgeEmphasize;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	FilterEdgeEmphasize	*FParent;
public:
    explicit SettingDialog(LayersBase *base,FilterEdgeEmphasize *v ,QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

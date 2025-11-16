#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XFromToInfo.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingDialog(LayersBase *base ,FromToClass &Data,QWidget *parent = nullptr);
    ~SettingDialog();

    FromToClass InfoData;

private slots:
    void on_radioButtonAllPagesSrc_clicked();
    void on_radioButtonFileSrc_clicked();
    void on_radioButtonPageSrc_clicked();
    void on_radioButtonShadowSrc_clicked();
    void on_radioButtonAllPagesDst_clicked();
    void on_radioButtonFileDst_clicked();
    void on_radioButtonPageDst_clicked();
    void on_radioButtonShadowDst_clicked();
    void on_pushButtonShadowTreeSrc_clicked();
    void on_pushButtonShadowTreeDst_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include "XServiceForLayers.h"
#include "FilterShiftByLayer.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

    int LastPhase   ;
    int LastPage    ;
    int LastLayer   ;
public:
    ShiftXYInfo	ShiftInfo;

    explicit SettingDialog(LayersBase *base ,ShiftXYInfo &_ShiftInfo,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_listWidgetPhase_itemSelectionChanged();
    void on_listWidgetPhase_itemClicked(QListWidgetItem *item);
    void on_listWidgetPage_itemSelectionChanged();
    void on_listWidgetPage_itemClicked(QListWidgetItem *item);
    void on_listWidgetLayer_itemSelectionChanged();
    void on_listWidgetLayer_itemClicked(QListWidgetItem *item);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

    void    GetFromWindow   (int phase ,int page ,int layer);
    void    SetToWindow     (int phase ,int page ,int layer);
};

#endif // SETTINGDIALOG_H

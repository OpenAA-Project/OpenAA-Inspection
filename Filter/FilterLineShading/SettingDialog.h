#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class FilterLineShading;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    FilterLineShading   *Parent;

    int     *BrightnessTable[3][256];  //BrightnessTable[Layer][color][x]
    int     XLen;
    int     LayerNumb;
public:
    explicit SettingDialog(LayersBase *Base,FilterLineShading *p,QWidget *parent = 0);
    ~SettingDialog();
    
private slots:
    void on_pushButtonFileName_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonSetOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

    void    Analize(QImage &Image);
};

#endif // SETTINGDIALOG_H

#ifndef SETTINGLED500DIALOG_H
#define SETTINGLED500DIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingLED500Dialog;
}
class	LED500Panel;

class SettingLED500Dialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    bool	EnabledChanged;
	LED500Panel	*LightAccessor;
public:
    explicit SettingLED500Dialog(LayersBase *base, LED500Panel	*p ,QWidget *parent = 0);
    ~SettingLED500Dialog();
    
private slots:
    void on_comboBoxLeft_currentIndexChanged(int index);

    void on_comboBoxRight_currentIndexChanged(int index);
    void on_spinBoxLBar0_valueChanged(int arg1);
    void on_spinBoxLBar1_valueChanged(int arg1);
    void on_spinBoxLBar2_valueChanged(int arg1);
    void on_spinBoxLBar3_valueChanged(int arg1);
    void on_spinBoxLBar4_valueChanged(int arg1);
    void on_spinBoxLBar5_valueChanged(int arg1);
    void on_spinBoxLBar6_valueChanged(int arg1);
    void on_spinBoxRBar0_valueChanged(int arg1);
    void on_spinBoxRBar1_valueChanged(int arg1);
    void on_spinBoxRBar2_valueChanged(int arg1);
    void on_spinBoxRBar3_valueChanged(int arg1);
    void on_spinBoxRBar4_valueChanged(int arg1);
    void on_spinBoxRBar5_valueChanged(int arg1);
    void on_spinBoxRBar6_valueChanged(int arg1);
    void on_pushButtonSetAll_clicked();
	void on_pushButtonSetLeft_clicked();
	void on_pushButtonSetRight_clicked();
    void on_pushButtonClose_clicked();
    void on_checkBoxSyncMode_clicked();
    void on_toolButtonOnOff_clicked();
    void on_spinBoxSyncForward_valueChanged(int arg1);
    void on_spinBoxSyncPulsePerBar_valueChanged(int arg1);
    void on_spinBoxSyncBackward_valueChanged(int arg1);
    void on_pushButtonTransfer_clicked();

private:
    Ui::SettingLED500Dialog *ui;
};

#endif // SETTINGLED500DIALOG_H

/*
 * Copyright (C) 2019
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
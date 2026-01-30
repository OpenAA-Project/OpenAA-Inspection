/*
 * Copyright (C) 2022
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
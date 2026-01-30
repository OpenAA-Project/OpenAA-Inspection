/*
 * Copyright (C) 2023
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
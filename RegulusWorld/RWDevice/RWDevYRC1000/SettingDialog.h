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
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class RWDevYRC1000;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    RWDevYRC1000    *Parent;
public:
    explicit SettingDialog(LayersBase *Base,RWDevYRC1000 *p,QWidget *parent = nullptr);
    ~SettingDialog();

private slots:
    void on_pushButtonManualMode_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
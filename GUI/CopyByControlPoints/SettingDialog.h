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
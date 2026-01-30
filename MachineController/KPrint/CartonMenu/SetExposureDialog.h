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

#ifndef SETEXPOSUREDIALOG_H
#define SETEXPOSUREDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class SetExposureDialog;
}

class SetExposureDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SetExposureDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SetExposureDialog();
    
private slots:
    void on_PushButtonSettingTop1_clicked();
    void on_PushButtonSettingTop2_clicked();
    void on_PushButtonSettingTop3_clicked();
    void on_PushButtonSettingBottom1_clicked();
    void on_PushButtonSettingBottom2_clicked();
    void on_PushButtonSettingBottom3_clicked();
    void on_PushButtonClose_clicked();
    void on_PushButtonSettingTopHolo_clicked();
    void on_PushButtonSettingBottomHolo_clicked();
    void on_PushButtonSettingMonoHolo_clicked();
    void on_PushButtonSettingMono1_clicked();
    void on_PushButtonSettingMono2_clicked();
    void on_PushButtonSettingMono3_clicked();

private:
    Ui::SetExposureDialog *ui;
};

#endif // SETEXPOSUREDIALOG_H
/*
 * Copyright (C) 2025
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

#ifndef CAMERASETTINGDIALOG_H
#define CAMERASETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class CameraSettingDialog;
}
class CameraXtiumCISVienex;

class CameraSettingDialog : public QDialog
{
    Q_OBJECT

    CameraXtiumCISVienex *V;
public:
    explicit CameraSettingDialog(CameraXtiumCISVienex *index ,QWidget *parent = nullptr);
    ~CameraSettingDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonLoadFromCamera_clicked();

private:
    Ui::CameraSettingDialog *ui;

    void ShowDataToWindow(void);
};

#endif // CAMERASETTINGDIALOG_H
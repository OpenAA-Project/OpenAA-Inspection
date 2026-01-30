/*
 * Copyright (C) 2017
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

#ifndef CAMERAALLOCATIONDIALOG_H
#define CAMERAALLOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CameraAllocationDialog;
}

class CameraAllocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraAllocationDialog(QWidget *parent = 0);
    ~CameraAllocationDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::CameraAllocationDialog *ui;
};

#endif // CAMERAALLOCATIONDIALOG_H
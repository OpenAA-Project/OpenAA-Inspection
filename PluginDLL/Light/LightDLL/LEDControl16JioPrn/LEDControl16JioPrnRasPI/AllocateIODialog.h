/*
 * Copyright (C) 2024
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

#ifndef ALLOCATEIODIALOG_H
#define ALLOCATEIODIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "LightDeviceStruct.h"
#include <QMutex>
#include "NListRPi.h"
#include "DeviceStruct.h"
#include "XLightControlToPC.h"

namespace Ui {
class AllocateIODialog;
}

class LEDControl16JioPrnRasPIMain;

class AllocateIODialog : public QDialog
{
    Q_OBJECT
    LEDControl16JioPrnRasPIMain   *Parent;
public:
    explicit AllocateIODialog(LEDControl16JioPrnRasPIMain *p, QWidget *parent = nullptr);
    ~AllocateIODialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AllocateIODialog *ui;
};

#endif // ALLOCATEIODIALOG_H
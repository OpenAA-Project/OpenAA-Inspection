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

#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_YasukawaMotoCom.h"

class OperationForm;
class IOForm;

class YasukawaMotoCom : public QMainWindow
{
    Q_OBJECT

public:
    short   MachineID;
private:
    QTimer  TM;
    bool    CommandMemorizeTorque;
    double  MemorizedTorque[16];
    unsigned long   MemorizedTime;
    bool    OnWorking;
    OperationForm   *Operation;
    IOForm          *IO;
public:
    YasukawaMotoCom(QWidget *parent = nullptr);
    ~YasukawaMotoCom();

    bool    StopMeasure(void);
    bool    StartMeasure(void);
    bool    WaitWhileMoving(void);
private slots:
    void on_pushButtonOpen_clicked();
    void on_toolButtonServoON_clicked();
    void on_toolButtonHoldON_clicked();
    void on_pushButtonGetStatus_clicked();
    void    SlotTimeOut();
    void on_pushButtonMovRel_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::YasukawaMotoComClass ui;

};

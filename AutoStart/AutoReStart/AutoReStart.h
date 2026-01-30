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

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AutoReStart.h"
#include <QIODevice>
#include <QTimer>

class AutoReStartParam
{
public:
    QString ExeFileName;
    QString WorkingPath;
    QString Parameter;
    int     WaitingSecond;

	AutoReStartParam();
	~AutoReStartParam();

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

class AutoReStart : public QMainWindow
{
    Q_OBJECT

    QTimer  TM;
    bool    StopMode;
public:
    AutoReStartParam    ParamData;

    AutoReStart(QWidget *parent = nullptr);
    ~AutoReStart();

private slots:
    void on_pushButtonStart_clicked();
    void on_toolButtonStop_triggered(QAction *arg1);
    void on_pushButtonParam_clicked();

    void    SlotDialTick();

private:
    Ui::AutoReStartClass ui;
};
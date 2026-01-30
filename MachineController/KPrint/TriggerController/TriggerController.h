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

#ifndef TRIGGERCONTROLLER_H
#define TRIGGERCONTROLLER_H

#include <QMainWindow>
#include "ui_TriggerController.h"

class TriggerController : public QMainWindow
{
	Q_OBJECT

public:
	TriggerController(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TriggerController();

private slots:
    void on_pushButtonReceiveEIO_clicked();

    void on_pushButtonSendFrameTrigger_clicked();

    void on_toolButtonFlapOK_clicked();

    void on_toolButtonFlapNG_clicked();

    void on_pushButtonSaveSetting_clicked();

    void on_pushButtonReset_clicked();

private:
	Ui::TriggerControllerClass ui;
};

#endif // TRIGGERCONTROLLER_H
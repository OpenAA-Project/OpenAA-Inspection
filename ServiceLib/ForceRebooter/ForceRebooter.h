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

#ifndef FORCEREBOOTER_H
#define FORCEREBOOTER_H

#include <QMainWindow>
#include "ui_ForceRebooter.h"
#include "XForceRebooter.h"

class ForceRebooter : public QMainWindow
{
	Q_OBJECT

public:
	ForceRebooter(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ForceRebooter();

	RebooterServer	Executer;

private slots:
    void on_pushButtonRebootPrograms_clicked();
    void on_pushButtonRebootPC_clicked();
    void on_pushButtonSetting_clicked();
    void on_pushButtonShutdownPC_clicked();

private:
	Ui::ForceRebooterClass ui;
};

#endif // FORCEREBOOTER_H
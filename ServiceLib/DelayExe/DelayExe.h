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

#ifndef DELAYEXE_H
#define DELAYEXE_H

#include <QMainWindow>
#include "ui_DelayExe.h"
#include <QTimer>

class DelayExe : public QMainWindow
{
	Q_OBJECT

	QTimer	TM;
	int		CurrentCounter;
	QString	ExeFileName;
	QStringList	SArg;

public:
	DelayExe(const QString &FileName , int WaitingTime , QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~DelayExe();

private:
	Ui::DelayExeClass ui;

private slots:
	void	SlotTimeOut();
};

#endif // DELAYEXE_H
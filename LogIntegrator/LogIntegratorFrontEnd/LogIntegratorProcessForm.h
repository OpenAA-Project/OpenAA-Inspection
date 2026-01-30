/*
 * Copyright (C) 2012
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

#ifndef LOGINTEGRATORPROCESSFORM_H
#define LOGINTEGRATORPROCESSFORM_H

#include <QWidget>
#include <QTimer>
#include "ui_LogIntegratorProcessForm.h"

class LogIntegratorProcessForm : public QWidget
{
	Q_OBJECT

public:
	LogIntegratorProcessForm(QWidget *parent = 0);
	~LogIntegratorProcessForm();

	void SetLotNo		(QString LotNo);
	void SetExecCount	(int Count);
	void SetExecNo		(int No);

public slots:
	void SetUpdate		(int value);

private:
	Ui::LogIntegratorProcessFormClass ui;
};

#endif // LOGINTEGRATORPROCESSFORM_H
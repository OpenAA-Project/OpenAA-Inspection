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

#ifndef PERF1_H
#define PERF1_H

#include <QWidget>
#include "ui_perf1.h"
#include "clsExecIns.h"

class perf1 : public QWidget
{
	Q_OBJECT

public:
	perf1(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~perf1();

	clsExecIns *objThr;

private slots:
	void exitWin();
	void execStart();
	void drawExecAns(double,double,double,double,double,int);

private:
	Ui::perf1Class ui;
	int nCurCnt;
};

#endif // PERF1_H
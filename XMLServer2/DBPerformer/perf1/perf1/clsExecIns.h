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

#ifndef CLSEXECINS_H
#define CLSEXECINS_H

#include <QThread>
#include <QMutex>
#include <QTime>

#include "clsDb.h"

class clsExecIns : public QThread
{
	Q_OBJECT

public:
	clsExecIns(int cnt, QObject *parent);
	~clsExecIns();

	void run();

	double dMax;
	double dMin;
	double dAvg;
	double dErr;
	double dSum;

	double dStartX;
	double dStartY;

signals:
	void drawExecAns(double,double,double,double,double,int);

private:
	clsDb *db;
	int nExecCnt;
	int nCurCnt;

	double dTime;

	bool addTag();
	QTime curTim;
	void timeStart();
	void timeEnd();
};

#endif // CLSEXECINS_H
/*
 * Copyright (C) 2012
 * Author : cony
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


#include "clsCalcTime.h"
#include <QFile>
#include <QTextStream>

clsCalcTime::clsCalcTime() {
}

clsCalcTime::~clsCalcTime() {
}

void clsCalcTime::timeStart() {
	curTim.start();
}

void clsCalcTime::timeEnd() {
	int n = curTim.elapsed();
	dResTime = (double)n/1000.0;
}


clsDbResTime::clsDbResTime() {
	obj = new clsCalcTime();
}

clsDbResTime::~clsDbResTime() {
	delete(obj);
}

void clsDbResTime::startTime(bool bflg) {
	if ( bflg == true ) {
		dRes1 = 0.0;
		dRes2 = 0.0;
		dRes3 = 0.0;
		dRes4 = 0.0;
	}
	obj->timeStart();
}

void clsDbResTime::endTime(int idx) {
	obj->timeEnd();
	switch( idx ) {
	case 1:
		dRes1 = obj->dResTime;
		break;
	case 2:
		dRes2 = obj->dResTime;
		break;
	case 3:
		dRes3 = obj->dResTime;
		break;
	case 4:
		dRes4 = obj->dResTime;
		break;
	}
}

void clsDbResTime::wrtTimeLog(int port) {
	QString fnm = "C:\\Data\\XMLServerLog\\timelog_"+QString::number(port)+".log";
	QFile file(fnm);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);

	QString mess = QString::number(dRes1,'f',3);
	mess += ","+QString::number(dRes2,'f',3);
	mess += ","+QString::number(dRes3,'f',3);
	mess += ","+QString::number(dRes4,'f',3);
	mess += ","+QString::number((dRes1+dRes2+dRes3+dRes4),'f',3);
	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+","+mess+"\n";
	ot.flush();
	file.close();
	mess.clear();
}
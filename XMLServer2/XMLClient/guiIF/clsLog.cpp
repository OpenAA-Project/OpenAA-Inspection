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


#include "clsLog.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>
#include <QDebug>

void clsLog::startLog(QString addr) {
	fnam = logDir+"/"+"simulator_"+addr+".log";
	qDebug() << "log fnam=["+fnam+"]";
}

void clsLog::log(QString mess, int /*lvl*/) {
	QFile file(fnam);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);

	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess+"\n";
	file.close();

	qDebug() << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess;
}
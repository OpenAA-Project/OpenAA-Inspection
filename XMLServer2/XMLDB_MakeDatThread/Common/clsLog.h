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


#ifndef CLSLOG_H_
#define CLSLOG_H_

#include <QObject>
#include <QtNetwork>

class clsParam : public QObject {
	Q_OBJECT
public:
	static clsParam *GetInstance() {
		static clsParam instance;
		return &instance;
	}

	int nTimeOut;
	int nPort;
	QString logDir;
	int logSts;

	void readParam();
	void saveParam();

private:
	clsParam(){
		logSts = 0;
	}
	clsParam(const clsParam &rhs);
	clsParam& operator=(const clsParam &rhs);

	QObject *par;
};

class clsLog : public QObject {
	Q_OBJECT
public:
	clsLog(){}

	void startLog(QTcpSocket *sock);
	void startLog(QString addr);
	void log(QString mess, int lvl=1);

	static const int CLSLOG_DEBUG = 4;
	static const int CLSLOG_WARNING = 3;
	static const int CLSLOG_INFO = 2;
	static const int CLSLOG_FAITAL = 1;
	static const int CLSLOG_NOLOG = 0;

private:
	QString fnam;
};

#endif /* CLSLOG_H_ */
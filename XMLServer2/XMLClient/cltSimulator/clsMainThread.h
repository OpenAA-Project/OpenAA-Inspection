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


#ifndef CLSMAINTHREAD_H_
#define CLSMAINTHREAD_H_

#include <QThread>

class clsMainThread;
#include "XMLServerHandle.h"

class clsExecThread : public QThread {
	Q_OBJECT
public:
	clsExecThread(int no, QObject *par=0);
	virtual ~clsExecThread();

	int nThrNo;
	QString svr;
	int port;
	unsigned long WaitTime;
	QString logDir;
	int nNgCnt;
	int nEid;
	int nLid;

	QString cday;

	void run();

signals:
	void setCntThr(int row, int col, double val);
	void showMess(QString mess);

private:
	clsMainThread *par;
	XMLServerHandle *handle;

	QString svPort;
};

class clsMainThread : public QThread {
	Q_OBJECT
public:
	clsMainThread(QObject *par=0);
	virtual ~clsMainThread();

	void run();

	QString svr;
	int port;
	unsigned long WaitTime;
	QString logDir;
	int nThrCnt;
	int nLotId;
	int nStartEid;
	int nExecCnt;
	int nNgCnt;

signals:
	void setTime(int col, double val);
	void showMess(QString mess);

private:
	QObject *par;

	clsExecThread **arrThr;
	int nArrCnt;
	void clearThr();
	XMLServerHandle *handle;
};

#endif /* CLSMAINTHREAD_H_ */
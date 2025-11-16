/*
 * clsMainThread.h
 *
 *  Created on: 2010/02/04
 *      Author: cony
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

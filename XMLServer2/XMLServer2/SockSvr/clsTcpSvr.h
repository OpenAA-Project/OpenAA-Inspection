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


#ifndef CLSTCPSVR_H_
#define CLSTCPSVR_H_

#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include "clsTcpSlot.h"
#include "NList.h"
#include "clsLog.h"
#include "clsXMLDB_Front.h"

class clsTcpThread;
class clsTcpSvr;

/**
 * @brief �\�P�b�g�T�[�o�X���b�h���`�N���X
 */
class clsTcpSvrPnt : public NPList<clsTcpSvrPnt> {
public:
	clsTcpSvrPnt(){
		thrSock = NULL;
		objSlot = NULL;
		tcpSock = NULL;
		tcpSvr = NULL;
		port = -1;
		bConn = true;
	}
	~clsTcpSvrPnt();

	clsTcpThread *thrSock;
	clsTcpSlot   *objSlot;
	QTcpSocket   *tcpSock;
	QTcpServer   *tcpSvr;
	int port;
	bool bConn;
	QString cltAddr;

	clsTcpSvr *par;
};

/**
 * @brief �\�P�b�g�T�[�o�X���b�h�N���X
 */
class clsTcpThread : public QThread {
	Q_OBJECT
public:
	clsTcpThread(QTcpSocket *sock, clsTcpSvrPnt *ppar, QObject *par=0);
	virtual ~clsTcpThread();

	void connectStart(QTcpSocket *sock);
	void run();

	bool execSvr();

	bool sndMess(quint64 len, unsigned char *buf);

	void done();

	bool bExec;
	bool bAbort;
	bool bEndFlg;
	bool bCloseFlg;
	int no;

	QByteArray rcvByte;

	bool waitThread();
	int nTimeOut;

	void drawMstId(const QByteArray &MstId);

signals:
	void drawMstId(int port, QByteArray MstId);

private slots:
	void endThread();

private:
	QTcpSocket *tcpSock;

	unsigned char cRcvHeadBuf[12];
	unsigned char *pRcvHead;
	int rcvLength;

	unsigned char *rcvBuf;
	QString cmd;

	bool isSockEnable();

	clsLog *log;
	clsTcpSvrPnt *par;

	unsigned char *sndBuf;
	quint64 nSndLen;
	void makeSndBuf(QByteArray byte);

	bool chkSvcName(const QByteArray &name);
	bool splitNextSql(QByteArray &sql, QByteArray &id, QByteArray &dbFile);

	clsDb *db;
};

/**
 * @brief �^�C���A�E�g�N���X
 */
class clsTimeOut : public QObject {
	Q_OBJECT
public:
	clsTimeOut(QString no,QObject *_par=0);
	virtual ~clsTimeOut();

	bool timeOutStart(int sec);
	bool chkTimeOut();

	clsLog *log;
	clsLog *logLocal;

private:
	QDateTime startTime;
	int nTimeOutSec;
};

/**
 * @brief �\�P�b�g�T�[�o�N���X
 */
class clsTcpSvr : public QObject {
	Q_OBJECT
public:
	clsTcpSvr(QObject *_par);
	virtual ~clsTcpSvr();

	QTcpServer *svrSock;
	QTcpSocket *tcpSock;

	QTimer *timer1;

	NPListPack<clsTcpSvrPnt> *lstThrPnt;

	int curThr;
	clsLog *log;

signals:
	void drawRequest(int port, QString svr, QString sts);

public slots:
	void timer1out();
	void updRow(int port, QByteArray MstId);

private:
	QObject *par;

	void cleanTcpPnt();
	int nextPort();
};

#endif /* CLSTCPSVR_H_ */
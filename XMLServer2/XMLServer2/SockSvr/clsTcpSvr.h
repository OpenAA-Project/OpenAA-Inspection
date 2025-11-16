/*
 * clsTcpSvr.h
 *
 *  Created on: 2009/10/25
 *      Author: cony
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
 * @brief ソケットサーバスレッド定義クラス
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
 * @brief ソケットサーバスレッドクラス
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
 * @brief タイムアウトクラス
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
 * @brief ソケットサーバクラス
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

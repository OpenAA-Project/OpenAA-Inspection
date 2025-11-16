/*
 * XMLServerHandlePrivate.h
 *
 *  Created on: 2009/12/14
 *      Author: cony
 */

#ifndef XMLSERVERHANDLEPRIVATE_H_
#define XMLSERVERHANDLEPRIVATE_H_

#include <QtNetwork>
#include <QTcpSocket>
#include <QString>
#include <QByteArray>
#include <QObject>

#include "NList.h"
#include "clsTcpSlot.h"
#include "clsTcpThread.h"
#include "clsLog.h"

class XMLServerHandlePrivate : public QObject {
	Q_OBJECT
public:
	XMLServerHandlePrivate(QObject *par=0);
	virtual ~XMLServerHandlePrivate();

	bool isConnected();

	bool SockConnect();
	bool SockDisConnect();
	bool SockSndBuf();
	bool SockRcvBuf();
	bool SockEndSnd();

	void setSvrParam(QString svrname, int port, int waittime);
	QString errorMess();

	QString getPort() {
		return QString::number(svrPort);
	}
protected:
	QString svrName;
	int basePort;
	int waitTime;
	int status;
	int svrPort;

	QHostAddress svrAddr;

	bool makeSndBuf(QString cmd, QString mess);
	void logWrt(QString mess);

	QByteArray rcvByte;
	QString errMess;

	clsLog *log;

private:
	QTcpSocket *tcpSock;

	clsTcpSlot *objSlot;
	clsTcpThread *objThr;
	clsTimeOut objTOut;

	quint64 nHeadLen;
	quint64 nSndLen;
	unsigned char *pSndBuf;

	void done();
	void doneSock();

	QString fixStrBnd(QString buf, int len);
};

#endif /* XMLSERVERHANDLEPRIVATE_H_ */

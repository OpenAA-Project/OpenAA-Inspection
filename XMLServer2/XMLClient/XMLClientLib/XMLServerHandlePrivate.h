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
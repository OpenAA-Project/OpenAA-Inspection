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


#ifndef CLSTCPTHREAD_H_
#define CLSTCPTHREAD_H_

#include <QThread>
#include <QtNetwork>
#include <QTimer>

#include "clsTimeOut.h"

class clsTcpThread : public QThread {
	Q_OBJECT
public:
	clsTcpThread(QTcpSocket *sock, QObject *par=0);
	virtual ~clsTcpThread();

	void run();
	bool bAbort;
	unsigned char *rcvBuf;
	QByteArray rcvByte;
	int rcvLen;

private slots:
	void endThread();

private:
	QTcpSocket *tcpSock;

	unsigned char cRcvHeadBuf[11];
	unsigned char *pRcvHead;
	int rcvLength;

	clsTimeOut objTOut;
};

#endif /* CLSTCPTHREAD_H_ */
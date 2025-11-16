/*
 * clsTcpThread.h
 *
 *  Created on: 2009/10/25
 *      Author: cony
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

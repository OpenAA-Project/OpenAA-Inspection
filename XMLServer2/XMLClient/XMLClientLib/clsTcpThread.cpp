/*
 * clsTcpThread.cpp
 *
 *  Created on: 2009/10/25
 *      Author: cony
 */

#include "clsTcpThread.h"

clsTcpThread::clsTcpThread(QTcpSocket *sock, QObject *par) :
	QThread(par) {
	tcpSock = sock;
	rcvBuf = NULL;
	rcvLength = -1;
	//start();
}

void clsTcpThread::run() {
	int nReadStep = 0;
	int nReadSize = 0;
	int nHeadByte = 0;
	int nRcvCnt = 0;
	pRcvHead = cRcvHeadBuf;
	memset(pRcvHead, 0x00, 11);

	clsTimeOut *tout = new clsTimeOut(this);
	tout->timeOutStart(30);

	char flg;

	printf("read loop start\n");
	while (bAbort == false) {
		if (tout->chkTimeOut() == true) {
			break;
		}
		while (1) {
			objTOut.timeOutStart(10);
			if (tcpSock->state() == QAbstractSocket::UnconnectedState) {
				bAbort = true;
				break;
			}

			int nBufSize = tcpSock->bytesAvailable();
			if (nBufSize < 1) {
				printf("not ready\n");
				if (tcpSock->waitForReadyRead(100) == false) {
					//TODO タイムアウト処理
					if (objTOut.chkTimeOut() == true) {
						printf("timeout\n");
						bAbort = true;
						break;
					}
				}
				printf("ready step=[%d]\n",nReadStep);
			}
			printf("byteAvailable=[%d]\n", nBufSize);

			if (nReadStep == 0) {
				nReadSize = tcpSock->read((char *) (pRcvHead + nHeadByte), 1);
				if (nReadSize < 1) {
					printf("readsize=[%d]\n", nReadSize);
					if ( nReadSize < 0 ) {
						qDebug() << "read Error:"+tcpSock->errorString();
					}
					break;
				}

				nHeadByte += nReadSize;
				if (nHeadByte >= 11) {
					printf("head read=[%s]\n", pRcvHead);
					if ( strncmp((const char *)pRcvHead,"FFFFFFFFFF",10) == 0 ) {
						printf("rcv end conn\n");
						return;
					}
					// 送信バッファバイト数取得
					flg = pRcvHead[10];
					pRcvHead[10] = 0x00;
					int n = atoi((char *) pRcvHead);
					printf("rcv buf size=[%d]\n", n);
					rcvLength = n;

					rcvBuf = new unsigned char[rcvLength + 1];
					memset(rcvBuf, 0x00, rcvLength + 1);
					nReadStep = 1;
					nRcvCnt = 0;
				}
				break;
			} else {
				int nTmpSize = rcvLength - nRcvCnt;
				nReadSize
						= tcpSock->read((char *) (rcvBuf + nRcvCnt), nTmpSize);
				if (nReadSize < 1)
					break;
				nRcvCnt += nReadSize;

				if (nRcvCnt >= rcvLength) {
					rcvByte = QByteArray((const char *)rcvBuf,nRcvCnt);
					switch(flg) {
					case '0':
						break;
					case '1':
						rcvByte = qUncompress(rcvByte);
						break;
					}
					qDebug() << "rcvByte=["+rcvByte+"]";
					rcvLen = nRcvCnt;
					bAbort = true;
				}
				break;
			}
		}
		usleep(1);
	}
	printf("read thread end\n");
}

clsTcpThread::~clsTcpThread() {
	// TODO Auto-generated destructor stub
}

void clsTcpThread::endThread() {

}

/*
 * XMLServerHandlePrivate.cpp
 *
 *  Created on: 2009/12/14
 *      Author: cony
 */

#include "XMLServerHandlePrivate.h"

#include <QDebug>

#define COMPRESSSIZE 100

XMLServerHandlePrivate::XMLServerHandlePrivate(QObject *par) : QObject(par) {
	svrName = "localhost";
	basePort = 8666;
	waitTime = 5000;
	status = -1;
	svrPort = -1;
	tcpSock = NULL;
	errMess = "";
	pSndBuf = NULL;
	rcvByte = "";
	log = NULL;
}

XMLServerHandlePrivate::~XMLServerHandlePrivate() {
	// TODO Auto-generated destructor stub
}

bool XMLServerHandlePrivate::SockConnect() {
	if ( tcpSock != NULL ) doneSock();
	tcpSock = new QTcpSocket(this);
	if ( svrPort < 0 ) {
		svrPort = basePort;
	}
	tcpSock->connectToHost(svrAddr,svrPort);

	if ( tcpSock->waitForConnected(waitTime) == false ) {
		logWrt(svrName+":"+QString::number(svrPort)+" connect error:"+tcpSock->errorString());
		doneSock();
		return false;
	}

	objThr  = new clsTcpThread(tcpSock,this);
	objSlot = new clsTcpSlot(this);
	//connect(tcpSock,SIGNAL(disconnected()),this,SLOT(endThread()));
	if ( tcpSock->open(QIODevice::ReadWrite|QIODevice::Unbuffered) == false ) {
		logWrt(svrName+" open error:"+tcpSock->errorString());
		doneSock();
		return false;
	}
	connect(tcpSock, SIGNAL(readyRead()), objSlot, SLOT(readyRead()));

	qDebug() << "Connect "+svrAddr.toString()+":"+QString::number(svrPort);
	return true;
}

bool XMLServerHandlePrivate::SockDisConnect() {
	doneSock();
	return true;
}

bool XMLServerHandlePrivate::SockSndBuf() {
	if ( pSndBuf == NULL ) return false;
	if ( tcpSock == NULL ) return false;
	objTOut.timeOutStart(waitTime);
	while( 1 ) {
		if ( tcpSock->bytesToWrite() > 0 ) {
			if ( objTOut.chkTimeOut() == true ) {
				logWrt("sndBuf:time out");
				return false;
			}
			continue;
		}
		break;
	}
	if ( tcpSock->write((const char *)pSndBuf, nSndLen+nHeadLen) == false ) {
		logWrt("sndBuf:write error:"+tcpSock->errorString());
		doneSock();
		return false;
	}
	if ( tcpSock->waitForBytesWritten(waitTime) == false ) {
		logWrt("waitForBytesWrittn time out\n");
	}
	/*
	if ( pSndBuf[0] == 'F' ) {
		tcpSock->flush();
		if (tcpSock->waitForReadyRead(waitTime) == false) {
			printf("timeout sndMess wait read\n");
		}
	}
	*/

	return true;
}

bool XMLServerHandlePrivate::SockRcvBuf() {
	if ( tcpSock == NULL ) return false;
	if ( objThr == NULL ) return false;
	rcvByte = "";
	objThr->bAbort = false;
	objThr->start();
	objTOut.timeOutStart(waitTime);
	bool flg = true;
	while( 1 ) {
		if ( objThr->wait(100) == true ) {
			break;
		}
		if ( objThr->isFinished() == false ) {
			if ( objTOut.chkTimeOut() == true ) {
				flg = false;
				objThr->bAbort = true;
				break;
			}
		}
	}
	if ( flg == false ) {
		logWrt("rcvBuf:read timeout");
		doneSock();
		return false;
	}
	rcvByte = objThr->rcvByte;
	return true;
}

bool XMLServerHandlePrivate::SockEndSnd() {
	if ( pSndBuf != NULL ) {
		delete(pSndBuf);
		pSndBuf = NULL;
	}
	pSndBuf = new unsigned char[16];
	sprintf((char *)pSndBuf,"FFFFFFFFFFF----");
	nSndLen = 15;
	nHeadLen = 0;
	if ( SockSndBuf() == false ) {
		return false;
	}
	return true;
}

void XMLServerHandlePrivate::doneSock() {
	if ( objSlot != NULL ) objSlot->bAbort = true;
	if ( objThr != NULL ) objThr->bAbort = true;
	objTOut.timeOutStart(300);
	int nEnd = 0;
	int nEndCnt = 0;
	if ( objSlot != NULL ) nEndCnt++;
	if ( objThr != NULL ) nEndCnt++;
	while( nEnd < nEndCnt ) {
		if ( objSlot != NULL ) {
			if ( objSlot->isFinished() == true ) {
				delete(objSlot);
				objSlot = NULL;
				nEnd ++;
			}
		}
		if ( objThr != NULL ) {
			if ( objThr->isFinished() == true ) {
				delete(objThr);
				objThr = NULL;
				nEnd ++;
			}
		}
		if ( objTOut.chkTimeOut() == true ) {
			break;
		}
	}
	if ( tcpSock != NULL ) {
		tcpSock->abort();
		tcpSock->close();
		delete(tcpSock);
		tcpSock = NULL;
	}
}

void XMLServerHandlePrivate::done() {
	doneSock();
}


bool XMLServerHandlePrivate::isConnected() {
	if ( status < 0 ) {
		return false;
	}
	/*
	if ( tcpSock == NULL ) {
		return false;
	}
	*/
	return true;
}

bool XMLServerHandlePrivate::makeSndBuf(QString cmd, QString mess) {
	if ( cmd == "" || cmd.length() > 6 ) return false;
	QString buf = "S";
	buf += fixStrBnd(cmd,6);
	buf += mess;
	int len = buf.length();
	int nFlg = 0;
	QByteArray byte = buf.toLocal8Bit();
	if ( len > COMPRESSSIZE ) {
		byte = qCompress(byte);
		nSndLen = byte.length();
		nFlg = 1;
	} else {
		nSndLen = len;
	}
	if ( pSndBuf != NULL ) {
		delete(pSndBuf);
		pSndBuf = NULL;
	}
	nHeadLen = 11;
	pSndBuf = new unsigned char[12+nSndLen];
	sprintf((char *)pSndBuf,"%10.10d%d",(int)nSndLen,nFlg);
	unsigned char *p = pSndBuf+11;
	memcpy(p,byte.data(),nSndLen);
	p[nSndLen] = 0x00;

	return true;
}

QString XMLServerHandlePrivate::fixStrBnd(QString buf, int len) {
	QString ret = buf;
	if ( ret.length() < len ) {
		int str = ret.length();
		for( int i=str; i<len; i++ ) {
			ret += " ";
		}
	}
	return ret;
}

void XMLServerHandlePrivate::setSvrParam(QString svr, int port, int waittime) {
	errMess = "";
	if ( svr != "" ) 	svrName = svr;
	if ( port > 0 ) basePort = port;
	if ( waittime > 0 ) waitTime = waittime;

	log = new clsLog();
	log->startLog(QString::number(port));

	QHostInfo host = QHostInfo::fromName(svrName);
	if ( host.error() != QHostInfo::NoError ) {
		logWrt(svrName+" Not LookUp");
		return;
	}
	if ( host.addresses().isEmpty() == true ) {
		logWrt(svrName+" Not Address");
		return;
	}
	qDebug() << "addr cnt=["+QString::number(host.addresses().size())+"]";
	for( int i=0; i<host.addresses().size(); i++ ) {
		qDebug() << "addr["+QString::number(i)+"]=["+host.addresses().at(i).toString()+"]";
	}
	svrAddr = host.addresses().first();
	logWrt(svrName+":"+QString::number(basePort)+":"+svrAddr.toString()+":"+QString::number(waitTime));
}

QString XMLServerHandlePrivate::errorMess() {
	return errMess;
}

void XMLServerHandlePrivate::logWrt(QString mess) {
	if ( mess == "" ) return;
	errMess = mess;

	if ( log != NULL ) {
		log->log(mess);
	}
	qDebug() << mess;
}

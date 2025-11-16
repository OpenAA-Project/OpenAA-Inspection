/*
 * clsTcpSvr.cpp
 *
 *	Created on: 2009/10/24
 *		Author: cony
 */

#include <QObject>
#include <QtNetwork>

#include "clsTcpSvr.h"
#include "xmlserver2.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define   new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s) 			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)			_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s) 		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s) 		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsTcpSvr::clsTcpSvr(QObject *_par) :
	QObject(_par) {
	lstThrPnt = new NPListPack<clsTcpSvrPnt> ();
	par = _par;

	svrSock = new QTcpServer((QObject *) this);
	timer1 = new QTimer();

	log = new clsLog();
	log->startLog("main");

	connect(timer1, SIGNAL(timeout()), this, SLOT(timer1out()));
	timer1->start(1);
}

clsTcpSvr::~clsTcpSvr() {
	disconnect(tcpSock, SIGNAL(disconnected()),0,0);
	// TODO Auto-generated destructor stub
	delete (log);
}

void clsTcpSvr::timer1out() {
	timer1->stop();

	clsParamDef *prm = clsParamDef::GetInstance();
	cleanTcpPnt();
	while (1) {
		if (svrSock->isListening() == false) {
			svrSock->setMaxPendingConnections(1);
			if (svrSock->listen(QHostAddress::Any, prm->nPort) == false) {
				log->log("timer1out:Listen error=[" + QString::number(
						prm->nPort) + "]", clsLog::CLSLOG_DEBUG);
				break;
			}
			log->log("timer1out:Listening start port=[" + QString::number(
					prm->nPort) + "]", clsLog::CLSLOG_INFO);
			break;
		}

		tcpSock = svrSock->nextPendingConnection();
		if (tcpSock == NULL) {
			break;
		}
		log->log("connecting First request addr=["
				+ tcpSock->peerAddress().toString() + "]", clsLog::CLSLOG_DEBUG);

		clsTcpSvrPnt *obj = new clsTcpSvrPnt();
		obj->tcpSock = tcpSock;
		obj->port = nextPort();
		obj->thrSock = new clsTcpThread(tcpSock, obj, this); // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		obj->objSlot = new clsTcpSlot(this);
		obj->tcpSvr = new QTcpServer(this);

		obj->par = this;

		obj->tcpSvr->setMaxPendingConnections(1);

		emit
		drawRequest(obj->port, obj->tcpSock->peerAddress().toString(),
				"CONNECT");

		connect(tcpSock, SIGNAL(disconnected()), obj->objSlot,
				SLOT(endThread()));
		connect(obj->thrSock, SIGNAL(drawMstId(int,QByteArray)),this,SLOT(updRow(int,QByteArray)),Qt::QueuedConnection);

		if (tcpSock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)
				== false) {
			log->log("timer1out:tcp open error:" + tcpSock->errorString(),
					clsLog::CLSLOG_DEBUG);
			break;
		}
		log->log("start First connectStart port=["+QString::number(obj->port)+"]",clsLog::CLSLOG_DEBUG);
		obj->thrSock->connectStart(tcpSock);
		log->log("end First connectStart port=["+QString::number(obj->port)+"]",clsLog::CLSLOG_DEBUG);
		//connect(tcpSock,SIGNAL(readyRead()),obj->objSlot,SLOT(readyRead()));
		lstThrPnt->AppendList(obj);
		if (obj->tcpSvr->listen(QHostAddress::Any, obj->port) == false) {
			log->log("timer1out:Listen error=["
					+ QString::number(obj->port) + "]",
					clsLog::CLSLOG_DEBUG);
			obj = obj->GetNext();
			continue;
		}
		log->log("child:Listening start port=[" + QString::number(obj->port)
				+ "]", clsLog::CLSLOG_INFO);

		break;
	}

	clsTcpSvrPnt *obj = lstThrPnt->GetFirst();
	while (obj != NULL) {
		if (obj->tcpSvr->isListening() == false) {
			obj->tcpSvr->setMaxPendingConnections(1);
			if (obj->tcpSvr->listen(QHostAddress::Any, obj->port) == false) {
				log->log("timer1out:Listen error=["
						+ QString::number(obj->port) + "]",
						clsLog::CLSLOG_DEBUG);
				obj = obj->GetNext();
				continue;
			} else {
				log->log("child:Listening start port=[" + QString::number(obj->port)
				+ "]", clsLog::CLSLOG_INFO);
				obj = obj->GetNext();
				continue;
			}
		}
		if ( obj->thrSock->waitThread() == false ) {
			//log->log("child:connection wait port=[" + QString::number(obj->port)
			//	+ "]", clsLog::CLSLOG_DEBUG);
			obj = obj->GetNext();
			continue;
		}

		QTcpSocket *sock = obj->tcpSvr->nextPendingConnection();
		if (sock == NULL) {
			obj = obj->GetNext();
			continue;
		}

		if ( obj->tcpSock != NULL ) {
			obj->tcpSock->abort();
			obj->tcpSock->close();
			delete(obj->tcpSock);
			obj->tcpSock = NULL;
		}
		//if ( obj->thrSock->waitThread() == true ) {
		//	obj = obj->GetNext();
		//	continue;
		//}
		log->log("child:connection request port=[" + QString::number(obj->port)
				+ "]", clsLog::CLSLOG_DEBUG);
		//connect(sock, SIGNAL(disconnected()), obj->objSlot,
		//		SLOT(endThread()));
		if (sock->open(QIODevice::ReadWrite | QIODevice::Unbuffered)
				== false) {
			log->log("timer1out:tcp open error:" + tcpSock->errorString(),
					clsLog::CLSLOG_DEBUG);
			break;
		}
		obj->cltAddr = sock->peerAddress().toString();
		obj->tcpSock = sock;
		log->log("start Child connectStart port=["+QString::number(obj->port)+"]",clsLog::CLSLOG_DEBUG);
		obj->thrSock->connectStart(sock);
		log->log("end Child connectStart port=["+QString::number(obj->port)+"]",clsLog::CLSLOG_DEBUG);
		obj = obj->GetNext();
	}
	timer1->start(1);
}

void clsTcpSvr::cleanTcpPnt() {
	clsTcpSvrPnt *lstThr = lstThrPnt->GetFirst();
	while (lstThr != NULL) {
		if (lstThr->bConn == false) {
			if (lstThr->thrSock->isFinished() == true
					|| lstThr->thrSock->isRunning() == false) {
				clsTcpSvrPnt *tmp = lstThr->GetNext();
				emit drawRequest(lstThr->port,lstThr->cltAddr, "DISCONNECT");
				if ( lstThr->tcpSock != NULL ) {
					if ( lstThr->tcpSock->state() != QAbstractSocket::UnconnectedState ) {
						lstThr->tcpSock->close();
						lstThr->tcpSock->abort();
					}
				}
				log->log("delete SvrPnt=["+QString::number(lstThr->port),clsLog::CLSLOG_DEBUG);
				lstThrPnt->RemoveList(lstThr);
				delete (lstThr);
				lstThr = tmp;
			} else {
				lstThr = lstThr->GetNext();
			}
		} else {
			lstThr = lstThr->GetNext();
		}
	}
}

int clsTcpSvr::nextPort() {
	clsParamDef *prm = clsParamDef::GetInstance();
	clsTcpSvrPnt *lstThr = lstThrPnt->GetFirst();
	int port = prm->nPort + 1;
	bool flg = false;
	while (1) {
		lstThr = lstThrPnt->GetFirst();
		flg = false;
		while (lstThr != NULL) {
			if (port == lstThr->port) {
				port = lstThr->port + 1;
				flg = true;
				break;
			}
			lstThr = lstThr->GetNext();
		}
		if (flg == false)
			break;
	}
	return port;
}

clsTcpSvrPnt::~clsTcpSvrPnt() {
	if (thrSock != NULL)
		thrSock->bEndFlg = true;
	if (objSlot != NULL)
		objSlot->bEndFlg = true;
	clsTimeOut *tout = new clsTimeOut("svrPnt");
	int nEnd = 0;
	int nEndCnt = 0;
	if (objSlot != NULL)
		nEndCnt++;
	if (thrSock != NULL)
		nEndCnt++;
	tout->timeOutStart(60);
	while (nEnd < nEndCnt) {
		if (objSlot != NULL) {
			if (objSlot->isFinished() == true) {
				par->log->log("delete start objSlot", clsLog::CLSLOG_DEBUG);
				delete (objSlot);
				objSlot = NULL;
				nEnd++;
			}
		}
		if (thrSock != NULL) {
			if (thrSock->isFinished() == true) {
				par->log->log("delete start objThr", clsLog::CLSLOG_DEBUG);
				delete (thrSock);
				thrSock = NULL;
				nEnd++;
			}
		}
		if (tout->chkTimeOut() == true) {
			break;
		}
	}
	delete (tout);
	if (tcpSock != NULL) {
		par->log->log("delete start tcpSock", clsLog::CLSLOG_DEBUG);
		if ( tcpSock->state() != QAbstractSocket::UnconnectedState ) {
			tcpSock->abort();
			tcpSock->close();
		}
		delete (tcpSock);
		tcpSock = NULL;
	}
	if ( tcpSvr != NULL ) {
		tcpSvr->close();
		delete(tcpSvr);
		tcpSvr = NULL;
	}
}

void clsTcpSvr::updRow(int port, QByteArray MstId) {
	XMLServer2 *obj = (XMLServer2 *)par;
	obj->drawRowMstId(port,MstId);
}

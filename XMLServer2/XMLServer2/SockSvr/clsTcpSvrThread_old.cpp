/*
 * clsTcpThread.cpp
 *
 *	Created on: 2009/10/25
 *		Author: cony
 */

#include "clsTcpSvr.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define   new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s) 			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)			_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s) 		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s) 		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsTcpThread::clsTcpThread(QTcpSocket *sock, clsTcpSvrPnt *ppar, QObject *_par) :
	QThread(_par) {
	par = ppar;
	tcpSock = sock;
	rcvBuf = NULL;
	sndBuf = NULL;
	rcvLength = -1;

	nTimeOut = 5000;
	log = new clsLog();
	log->startLog(QString::number(par->port));
}

void clsTcpThread::connectStart(QTcpSocket *sock) {
	tcpSock = sock;
	log->log("start thread port=["+QString::number(par->port)+"]?["+QString::number(tcpSock->localPort())+"]",clsLog::CLSLOG_DEBUG);
	bAbort = false;
	bEndFlg = false;
	start();
}

void clsTcpThread::run() {
	bExec = true;
	int nReadStep = 0;
	int nReadSize = 0;
	int nHeadByte = 0;
	int nRcvCnt = 0;
	pRcvHead = cRcvHeadBuf;
	memset(pRcvHead, 0x00, 12);
	bCloseFlg = false;

	clsParamDef *prm = clsParamDef::GetInstance();
	char flg;

	db = new clsDb();
	db->setConnDef("xmldb_"+QString::number(par->port));
	db->log = log;
	log->log("read loop start",clsLog::CLSLOG_DEBUG);
	clsTimeOut *tout = new clsTimeOut(QString::number(par->port));
	tout->log = log;
	tout->timeOutStart(prm->nTimeOut);
	rcvBuf = NULL;

	int nStartTimeStep = -1;
	while (bAbort == false) {
		if ( bEndFlg == true ) break;
		while (1) {
			if ( nStartTimeStep == -1 ) {
				log->startTime();
				nStartTimeStep = 0;
			}
			if ( isSockEnable() == false ) {
				log->log("abort connection",clsLog::CLSLOG_DEBUG);
				bAbort = true;
				break;
			}
			int nBufSize = tcpSock->bytesAvailable();
			if (nBufSize < 1) {
				if ( isSockEnable() == false ) {
					log->log("abort connection",clsLog::CLSLOG_DEBUG);
					bAbort = true;
					break;
				}
				if (tcpSock->waitForReadyRead(100) == false) {
					//TODO タイムアウト処理
					//if ( tout->chkTimeOut() == true ) {
					//	bAbort = true;
					//	break;
					//}
					//log->log("time out ["+QString::number(nBufSize)+"]",clsLog::CLSLOG_DEBUG);
					usleep(100);  // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					break;
				}
			}
			log->log("byteAvailable=["+QString::number(nBufSize)+"]<=["+QString::number(nHeadByte)+"]", clsLog::CLSLOG_DEBUG);
			if ( nBufSize > 0 && nStartTimeStep == 0 ) {
				log->endTime("start connection ["+QString::number(nBufSize)+"]");
				log->startTime();
				nStartTimeStep = 1;
			}
			if (nReadStep == 0) {
				if ( isSockEnable() == false ) {
					bAbort = true;
					break;
				}
				nReadSize = tcpSock->read((char *) (pRcvHead + nHeadByte), 1);
				if (nReadSize < 1) {
					log->log("readsize=["+QString::number(nReadSize)+"]",clsLog::CLSLOG_DEBUG);
					break;
				}

				nHeadByte += nReadSize;
				if (nHeadByte >= 11) {
					log->endTime("read Header");
					log->log("head read=["+QString::number(nHeadByte)+"]",clsLog::CLSLOG_DEBUG);

					if (strncmp((const char *) pRcvHead, "FFFFFFFFFF", 10) == 0) {
						log->log("connection end",clsLog::CLSLOG_DEBUG);
						//終了処理
						nReadStep = 0;
						nReadSize = 0;
						nHeadByte = 0;
						nRcvCnt = 0;
						memset(pRcvHead, 0x00, 12);
						tout->timeOutStart(prm->nTimeOut);
						break;
					}
					// 送信バッファバイト数取得
					log->startTime();
					flg = pRcvHead[10];
					pRcvHead[10] = 0x00;
					int n = atoi((char *) pRcvHead);
					if ( n == 0 ) {
						log->log("read error",clsLog::CLSLOG_DEBUG);
						nReadStep = 0;
						nReadSize = 0;
						nHeadByte = 0;
						nRcvCnt = 0;
						memset(pRcvHead, 0x00, 12);
						tout->timeOutStart(prm->nTimeOut);
						return;
					}
					log->log("rcv buf size=["+QString::number(n)+"]\n",clsLog::CLSLOG_DEBUG);
					rcvLength = n;

					rcvBuf = new unsigned char[rcvLength + 1];
					memset(rcvBuf, 0x00, rcvLength + 1);
					nReadStep = 1;
					nRcvCnt = 0;
					log->endTime("read ready");
					log->startTime();
					nStartTimeStep = 2;
				}
				log->log("loop break byteAvailable=["+QString::number(nBufSize)+"]<=["+QString::number(nHeadByte)+"]", clsLog::CLSLOG_DEBUG);
				break;
			} else {
				if ( isSockEnable() == false ) {
					bAbort = true;
					break;
				}
				int nTmpSize = rcvLength - nRcvCnt;
				nReadSize
						= tcpSock->read((char *) (rcvBuf + nRcvCnt), nTmpSize);
				if (nReadSize < 1)
					break;
				nRcvCnt += nReadSize;

				if (nRcvCnt >= rcvLength) {
					switch(flg) {
					case '0' : // 通常
						rcvByte = QByteArray((const char *)rcvBuf,nRcvCnt);
						break;
					case '1' : // 圧縮
						log->log("******** uncompressed *********",clsLog::CLSLOG_DEBUG);
						rcvByte = qUncompress((const uchar *)rcvBuf,nRcvCnt);
						break;
					}
					log->log("rcv Buf=["+rcvByte+"]",clsLog::CLSLOG_DEBUG);
					log->endTime("read body end");
					log->startTime();
					if (execSvr() == false) {
						log->endTime("exec svc error end");
						log->startTime();
						if (sndMess(10, (unsigned char *) "ExecFailed") == false ) {
							log->log("sndMess Error\n",clsLog::CLSLOG_DEBUG);
							delete(rcvBuf);
							return;
						}
						log->log("sndBuf=[ExecFailed]",clsLog::CLSLOG_DEBUG);
						sndBuf = NULL;
					} else {
						log->endTime("exec svc success end");
						log->startTime();
						if (sndMess(nSndLen, sndBuf) == false) {
							log->log("sndMess Error\n",clsLog::CLSLOG_DEBUG);
							delete(rcvBuf);
							return;
						}
						log->log("sndBuf=["+QString::fromAscii((const char *)sndBuf)+"]",clsLog::CLSLOG_DEBUG);
						delete(sndBuf);
						sndBuf = NULL;
					}
					log->endTime("return buf end");
					nStartTimeStep = -1;
					nReadStep = 0;
					nReadSize = 0;
					nHeadByte = 0;
					nRcvCnt = 0;
					//bAbort = true;
					tout->timeOutStart(prm->nTimeOut);
					delete(rcvBuf);
					rcvByte.clear();
				}
				if ( bCloseFlg == true ) break;
				//break;
			}
		}
		usleep(1);
		if ( bCloseFlg == true ) {
			log->log("Connect or Close Cmd",clsLog::CLSLOG_DEBUG);
			break;
		}
	}
	delete(tout);
	bExec = false;
	log->log("read thread end\n",clsLog::CLSLOG_DEBUG);
}

bool clsTcpThread::execSvr() {
	log->log("CMD=["+cmd+"]",clsLog::CLSLOG_DEBUG);
	if ( chkSvcName("CONN") == true ) { // 接続
		log->log("CONN start",clsLog::CLSLOG_DEBUG);
		QByteArray byte = "CONN  "+QByteArray::number(par->port);
		nSndLen = byte.size();
		sndBuf = new unsigned char[nSndLen+1];
		memcpy(sndBuf,byte.data(),nSndLen);
		sndBuf[nSndLen] = 0x00;
		byte.clear();
		bCloseFlg = true;
		return true;
	}

	if ( chkSvcName("STATE") == true ) { // 状態
		log->log("STATE start",clsLog::CLSLOG_DEBUG);
		QByteArray byte = "STATE TRUE";
		nSndLen = byte.size();
		sndBuf = new unsigned char[nSndLen+1];
		memcpy(sndBuf,byte.data(),nSndLen);
		sndBuf[nSndLen] = 0x00;
		byte.clear();
		bCloseFlg = false;
		return true;
	}

	if ( chkSvcName("CLOSE") == true ) { // 切断
		log->log("CLOSE start",clsLog::CLSLOG_DEBUG);
		QByteArray byte = "CLOSE ";
		nSndLen = byte.size();
		sndBuf = new unsigned char[nSndLen+1];
		memcpy(sndBuf,byte.data(),nSndLen);
		sndBuf[nSndLen] = 0x00;
		byte.clear();
		par->bConn = false;
		bCloseFlg = true;
		return true;
	}

	bCloseFlg = false;

	//---------------------------------------
	// 検索系
	//---------------------------------------
	if ( chkSvcName("SELECT") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		QByteArray byte;
		if ( front->searchAllXml(sql,byte) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		return true;
	}

	if ( chkSvcName("FIRST") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		QByteArray byte;
		if( front->searchFirstXml(sql,byte) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		return true;
	}

	if ( chkSvcName("NEXT") == true ) {
		QByteArray sql;
		QByteArray id;
		QByteArray dbFile;
		if ( splitNextSql(sql,id,dbFile) == false ) {
			log->log("NEXT RcvBuf Format Error",clsLog::CLSLOG_DEBUG);
			return false;
		}
		qDebug() << "sql=["+sql+"]";
		qDebug() << "id=["+id+"]";
		qDebug() << "dbFile=["+dbFile+"]";
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		QByteArray byte;
		if( front->readXml(sql,id,dbFile,byte) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		id.clear();
		dbFile.clear();
		return true;
	}

	//---------------------------------------
	// 更新系
	//---------------------------------------
	if ( chkSvcName("INSERT") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->db = db;
		front->setLogObj(log);
		if ( front->addXml(sql) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		QByteArray byte = "TRUE";
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		return true;
	}

	if ( chkSvcName("APPEND") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		if ( front->appendXml(sql) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		QByteArray byte = "TRUE";
		makeSndBuf(byte);
		log->log("APPEND SUCCESS",clsLog::CLSLOG_DEBUG);
		byte.clear();
		sql.clear();
		return true;
	}

	if ( chkSvcName("UPDATE") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		if ( front->updateXml(sql) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		QByteArray byte = "TRUE";
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		return true;
	}

	if ( chkSvcName("DELETE") == true ) {
		QByteArray sql = rcvByte.mid(7);
		clsXMLDB_Front *front = new clsXMLDB_Front(db,par->port,this);
		front->setLogObj(log);
		if ( front->deleteXml(sql) == false ) {
			log->log(front->errorString(),clsLog::CLSLOG_DEBUG);
			delete(front);
			return false;
		}
		delete(front);
		QByteArray byte = "TRUE";
		makeSndBuf(byte);
		byte.clear();
		sql.clear();
		return true;
	}
	return false;
}

void clsTcpThread::makeSndBuf(QByteArray byte) {
	nSndLen = byte.size();
	sndBuf = new unsigned char[nSndLen+1];
	memcpy(sndBuf,byte.data(),nSndLen);
	sndBuf[nSndLen] = 0x00;
}

bool clsTcpThread::sndMess(quint64 len, unsigned char *buf) {
	bool bCompflg = false;
	if ( len > 100 ) {
		bCompflg = true;
	}
	unsigned char *rplBuf = NULL;
	bool bSndAbort = false;
	while (bSndAbort == false) {
		if ( bEndFlg == true ) break;
		while (1) {
			if ( isSockEnable() == false ) {
				bSndAbort = true;
				break;
			}
			if (tcpSock->bytesToWrite() <= 0) {
				log->log("replay send start",clsLog::CLSLOG_DEBUG);
				if ( (int)len == -1 ) {
					len = 0;
				}
				int nLen = len;
				int nComp = 0;
				QByteArray sndBuf;
				if ( bCompflg == true ) {
					nComp = 1;
					sndBuf = qCompress((const char *)buf,len);
					nLen = sndBuf.length();
				} else {
					sndBuf = QByteArray((const char *)buf,len);
				}
				rplBuf = new unsigned char[11 + nLen + 1];
				if ( len == 0 ) {
					sprintf((char *)rplBuf,"FFFFFFFFFFFFF");
				} else {
					sprintf((char *) rplBuf, "%10.10d%d", nLen,nComp);
					unsigned char *p = rplBuf+11;
					if ( bCompflg == false ) {
						memcpy(p,buf,nLen);
					} else {
						memcpy(p,sndBuf.data(),nLen);
					}
					rplBuf[nLen + 11] = 0x00;
				}
				log->log("rpl=["+QString::fromLocal8Bit((const char *)rplBuf)+"]",clsLog::CLSLOG_DEBUG);
				if ( isSockEnable() == false ) {
					bAbort = true;
					break;
				}
				bool ret = tcpSock->write((const char *) rplBuf, nLen + 11);
				if (ret == false) {
					log->log("write Error:"+tcpSock->errorString(),clsLog::CLSLOG_DEBUG);
					return false;
				}
				tcpSock->flush();
				bSndAbort = true;
				sndBuf.clear();
				break;
			} else {
				if ( tcpSock->waitForBytesWritten(100) == false ) {
					//TODO タイムアウト処理
					usleep(10);
					break;
				}
			}
		}
		usleep(1);
	}
	log->log("replay end",clsLog::CLSLOG_DEBUG);
	if (rplBuf != NULL) {
		delete (rplBuf);
	}
	return true;
}

clsTcpThread::~clsTcpThread() {
	// TODO Auto-generated destructor stub
	delete(log);
	delete(db);
}

void clsTcpThread::endThread() {
	log->log("endThread",clsLog::CLSLOG_DEBUG);
}

bool clsTcpThread::isSockEnable() {
	if ( tcpSock == NULL ) return false;
	if ( tcpSock->state() == QAbstractSocket::UnconnectedState ) {
		return false;
	}
	return true;
}

void clsTcpThread::done() {

}

bool clsTcpThread::waitThread() {
	if ( isFinished() == true ) {
		log->log("****** Finished *****",clsLog::CLSLOG_DEBUG);
		return true;
	}
	if ( isRunning() == false ) {
		log->log("****** Not Running *****",clsLog::CLSLOG_DEBUG);
		return true;
	} else {
		//log->log("****** Runnning *****",clsLog::CLSLOG_DEBUG);
		return false;
	}
	if ( wait(nTimeOut) == false ) {
		log->log("waitThread timeout",clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsTcpThread::chkSvcName(const QByteArray &name) {
	QByteArray svcNam = rcvByte.mid(1,6).trimmed();
	if ( svcNam == name ) {
		return true;
	}
	svcNam.clear();
	return false;
}

bool clsTcpThread::splitNextSql(QByteArray &sql, QByteArray &id, QByteArray &dbFile) {
	qDebug() << "rcvByte=["+rcvByte+"]";
	int idx = rcvByte.indexOf("_@_");
	if ( idx < 0 ) {
		return false;
	}
	qDebug() << "idx=("+QString::number(idx)+")";
	sql = rcvByte.mid(7,(idx-7));
	int idx2 = rcvByte.indexOf("_@_",idx+1);
	if ( idx < 0 ) {
		return false;
	}
	qDebug() << "idx=("+QString::number(idx2)+")";
	if ( idx2 < 0 ) {
		id	= rcvByte.mid(idx+3);
		dbFile = "";
	} else {
		qDebug() << "idx=("+QString::number(idx)+","+QString::number(idx2)+")";
		id = rcvByte.mid(idx+3,idx2-idx-3);
		dbFile = rcvByte.mid(idx2+3);
	}
	return true;
}

void clsTcpThread::drawMstId(const QByteArray &MstId) {
	qDebug() << "drawMstId:"+MstId;
	emit drawMstId(par->port,MstId);
}


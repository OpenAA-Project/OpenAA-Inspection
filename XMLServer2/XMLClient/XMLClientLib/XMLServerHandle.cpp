/*
 * XMLServerHandle.cpp
 *
 *  Created on: 2009/12/14
 *      Author: cony
 */

#include "XMLServerHandle.h"
#include <QDebug>

XMLServerHandle *XML_Connect(const QString &IPAddress,int port, unsigned long  WaitingTime) {
	XMLServerHandle *handle = new XMLServerHandle();

	handle->setSvrParam((QString)IPAddress,port,(int)WaitingTime);
	if ( handle->Connect() == false ) {
		qDebug() << "Connect error:"+handle->errorMess();
		delete(handle);
		return NULL;
	}
	return handle;
}

bool XML_Select(XMLServerHandle *Handle,const QString &SelectStr,QStringList &RetStringList) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->selectXml(SelectStr,RetStringList) == false ) {
		return false;
	}
	return true;
}

bool XML_SelectFirst(XMLServerHandle *Handle,const QString &SelectStr,QString &RetString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->openXml(SelectStr,RetString) == false ) {
		return false;
	}
	return true;
}

bool XML_SelectNext(XMLServerHandle *Handle, QString &RetString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->nextXml(RetString) == false ) {
		return false;
	}
	return true;
}

bool XML_Insert(XMLServerHandle *Handle,const QString &InsertedString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->addXml(InsertedString) == false ) {
		return false;
	}
	return true;
}

bool XML_Append(XMLServerHandle *Handle,const QString &InsertedString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->appendXml(InsertedString) == false ) {
		return false;
	}
	return true;
}

bool XML_Update(XMLServerHandle *Handle,const QString &UpdatedString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->updateXml(UpdatedString) == false ) {
		return false;
	}
	return true;
}

bool XML_Delete(XMLServerHandle *Handle,const QString &DeletedString) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->deleteXml(DeletedString) == false ) {
		return false;
	}
	return true;
}

bool XML_Close(XMLServerHandle *Handle) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->DisConnect() == false ) {
		return false;
	}

	return true;
}

bool XML_GetState(XMLServerHandle *Handle,bool &RetOpened) {
	if ( Handle == NULL ) {
		return false;
	}
	if ( Handle->isConnected() == false ) {
		return false;
	}
	if ( Handle->GetStatus() == false ) {
		RetOpened = false;
		return false;
	}
	RetOpened = true;
	return true;
}

XMLServerHandle::XMLServerHandle(QObject *par) : XMLServerHandlePrivate(par){
	svsql = "";
}

XMLServerHandle::~XMLServerHandle() {
}

bool XMLServerHandle::Connect() {
	if ( SockConnect() == false ) {
		return false;
	}
	if ( SndRcv("CONN","") == false ) {
		logWrt("Connect:CONN Send Error");
		return false;
	}
	SockDisConnect();
	if ( rcvBuf == "" ) {
		errMess = "bad CONN return";
		logWrt("Connect:rcvBuf Empty");
		return false;
	}
	bool b;
	int n = rcvBuf.toInt(&b);
	if ( b == false ) {
		errMess = "bad port format:["+rcvBuf+"]";
		logWrt("Connect:"+errMess);
		return false;
	}
	if ( n > 0 ) {
		svrPort = n;
		status = 1;
	}
	if ( log != NULL ) {
		log->startLog(QString::number(svrPort));
	}

	logWrt("Connect:reconnect port=["+QString::number(svrPort)+"]");
	if ( SockConnect() == false ) {
		errMess = "Connect Error port=["+QString::number(svrPort)+"]";
		logWrt("Connect:"+errMess);
		return false;
	}
	return true;
}

bool XMLServerHandle::DisConnect() {
	if ( SndRcv("CLOSE","") == false ) {
		return false;
	}
	SockDisConnect();
	svrPort = 0;
	status = -1;
	return true;
}

bool XMLServerHandle::GetStatus() {
	if ( SndRcv("STATE","") == false ) {
		return false;
	}
	qDebug() << "Status return=["+rcvBuf+"]";
	if ( rcvBuf != "TRUE" ) {
		return false;
	}
	qDebug() << "return true";
	return true;
}

bool XMLServerHandle::selectXml(const QString &sql, QStringList &lst) {
	if ( SndRcv("SELECT",sql) == false ) {
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		return false;
	}
	QStringList lstTmp = rcvBuf.split("_@_");
	int cnt = lstTmp.at(0).toInt();
	if ( cnt <= 0 ) return true;
	for( int i=1; i<=cnt; i++ ) {
		lst << lstTmp.at(i);
	}
	return true;
}

bool XMLServerHandle::openXml(const QString &sql, QString &buf) {
	svsql = sql;
	lstHit.clear();
	nHitCnt = 0;
	nCurIdx = 0;
	if ( SndRcv("FIRST",sql) == false ) {
		buf = "";
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		buf = "";
		return false;
	}
	QStringList lstTmp = rcvBuf.split("_@_");
	nHitCnt = lstTmp.at(0).toInt();
	if ( nHitCnt <= 0 ) return true;
	lstHit = lstTmp.at(1).split(",");
	if ( lstTmp.size() > 3 ) {
		mkLstDb(lstTmp.at(2));
		buf = lstTmp.at(3);
	} else {
		buf = lstTmp.at(2);
	}
	return true;
}

bool XMLServerHandle::mkLstDb(const QString &src) {
	qDebug() << "********* dblst=["+src+"]";
	QStringList lst = src.split(",");
	QString sv;
	for( int i=0; i<lst.size(); i++ ) {
		if ( i % 2 == 0 ) {
			sv = lst.at(i);
		} else {
			int n = lst.at(i).toInt();
			for( int j=0; j<n; j++ ) {
				lstDbFile << sv;
			}
		}
	}
	return true;
}

bool XMLServerHandle::nextXml(QString &buf) {
	nCurIdx++;
	if ( nCurIdx >= nHitCnt || nCurIdx < 0 ) {
		buf = "";
		return true;
	}

	qDebug() << "**** lstDbFile Size=["+QString::number(lstDbFile.size())+"]";
	if ( lstDbFile.size() > 0 ) {
		if ( SndRcv("NEXT",svsql+"_@_"+lstHit.at(nCurIdx)+"_@_"+lstDbFile.at(nCurIdx) ) == false ) {
			buf = "";
			return false;
		}
	} else {
		if ( SndRcv("NEXT",svsql+"_@_"+lstHit.at(nCurIdx)) == false ) {
			buf = "";
			return false;
		}
	}
	if ( rcvBuf == "ExecFailed" ) {
		buf = "";
		return false;
	}
	QStringList lstTmp = rcvBuf.split("_@_");
	if ( lstTmp.at(0).toInt() <= 0 ) {
		buf = "";
		return true;
	}
	buf = lstTmp.at(1);
	return true;
}

bool XMLServerHandle::addXml(const QString &sql) {
	if ( SndRcv("INSERT",sql) == false ) {
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		return false;
	}
	return true;
}

bool XMLServerHandle::appendXml(const QString &sql) {
	if ( SndRcv("APPEND",sql) == false ) {
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		return false;
	}
	return true;
}

bool XMLServerHandle::updateXml(const QString &sql) {
	if ( SndRcv("UPDATE",sql) == false ) {
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		return false;
	}
	return true;
}

bool XMLServerHandle::deleteXml(const QString &sql) {
	if ( SndRcv("DELETE",sql) == false ) {
		return false;
	}
	if ( rcvBuf == "ExecFailed" ) {
		return false;
	}
	return true;
}

bool XMLServerHandle::SndRcv(QString cmd, QString mess) {
	rcvBuf = "";
	/*
	if ( SockConnect() == false ) {
		return false;
	}
	*/
	if ( makeSndBuf(cmd,mess) == false ) {
		return false;
	}
	if ( SockSndBuf() == false ) {
		return false;
	}
	if ( SockRcvBuf() == false ) {
		return false;
	}
	/*
	if ( SockEndSnd() == false ) {
		return false;
	}
	*/
	//SockDisConnect();

	rcvBuf = rcvBufLex(cmd);
	return true;
}

QString XMLServerHandle::rcvBufLex(QString cmd) {
	qDebug() << "rcvByte=["+rcvByte+"]";
	QString tmp(rcvByte);
	if ( tmp == "ExecFailed" ) {
		return tmp;
	}
	qDebug() << "rcvBuf=["+tmp+"]";
	QString chkCmd = tmp.mid(0,6).trimmed();
	qDebug() << "cmd=["+chkCmd+"]?["+cmd+"]";
	if ( cmd != chkCmd ) {
		return "";
	}
	return tmp.mid(6);
}

/*
 * clsLog.cpp
 *
 *  Created on: 2009/11/08
 *      Author: cony
 */

#include "clsLog.h"
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QDateTime>
#include <QSettings>
#include <QDebug>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

void clsLog::startLog(QTcpSocket *sock) {
	QHostAddress addr = sock->peerAddress();
	startLog(addr.toString());
}

void clsLog::startLog(QString addr) {
	clsParamDef *prm = clsParamDef::GetInstance();
	fnam = prm->logDir+"/"+"xmlsvr_"+addr+".log";
	//qDebug() << "log fnam=["+fnam+"]";
	timFnam = prm->logDir+"/"+"xmlsvr_time_"+addr+".log";
}

void clsLog::log(QString mess, int lvl) {
	clsParamDef *prm = clsParamDef::GetInstance();
	if ( prm->logSts < lvl ) {
		qDebug() << "not log ["+mess+"]";
		return;
	}
	QFile file(fnam);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);

	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess+"\n";
	ot.flush();
	file.close();

	//qDebug() << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess;
	mess = "";
	mess.clear();
}

void clsLog::startTime() {
	objTim.timeStart();
	/*
	QFile file(timFnam);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);
	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz") << ":start time\n";
	ot.flush();
	file.close();
	*/
}

void clsLog::endTime(const QString &mess) {
	objTim.timeEnd();
	QFile file(timFnam);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);
	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz") << ":" << mess << ":" << QString::number(objTim.dResTime,'f',3) << "\n";
	ot.flush();
	file.close();
}
void clsParamDef::readParam() {
	QSettings sets("./XmlServer.ini",QSettings::IniFormat);
	QString tmp = sets.value("TIMEOUT_DEF").toString();
	if ( tmp.isEmpty() == false ) {
		nTimeOut = tmp.toInt();
	}
	tmp = sets.value("PORT").toString();
	if ( tmp.isEmpty() == false ) {
		nPort = tmp.toInt();
	}
	tmp = sets.value("LOGLVL").toString();
	if ( tmp.isEmpty() == false ) {
		logSts = tmp.toInt();
	}
	tmp = sets.value("LOGDIR").toString();
	if ( tmp.isEmpty() == false ) {
		logDir = tmp;
	}
	tmp = sets.value("DBUSR").toString();
	if ( tmp.isEmpty() == false ) {
		dbUsr = tmp;
	}
	tmp = sets.value("DBPWD").toString();
	if ( tmp.isEmpty() == false ) {
		dbPwd = tmp;
	}
	tmp = sets.value("DBFILE").toString();
	if ( tmp.isEmpty() == false ) {
		dbFile = tmp;
	}
	tmp = sets.value("DBFOLDER").toString();
	if ( tmp.isEmpty() == false ) {
		dbFolder = tmp;
	}
	tmp = sets.value("CHANGEDBDAY").toString();
	if ( tmp.isEmpty() == false ) {
		nChgDbDay = tmp.toInt();
	}

	tmp = sets.value("TAGCNT").toString();
	if ( tmp.isEmpty() == true ) return;
	nTagCnt = tmp.toInt();
	for( int i=1; i<=nTagCnt; i++ ) {
		QString itm = "TAG"+QString::number(i);
		tmp = sets.value(itm).toString();
		qDebug() << "TAGITEM=["+itm+"]=["+tmp+"]";
		clsTagAttrRec *rec = new clsTagAttrRec(tmp);
		itm = "TAGATTR"+QString::number(i);
		tmp = sets.value(itm).toString();
		qDebug() << "TAGITEM("+itm+") ATTR=["+tmp+"]";
		QStringList lst = tmp.split("-");
		for( int j=0; j<lst.size(); j++ ) {
			rec->arrItm.append(lst.at(j));
			rec->arrTblCol.append("val"+QString::number(j));
		}
		lstTag.append(rec);
	}
}

void clsParamDef::saveParam() {
	QSettings sets("./XmlServer.ini",QSettings::IniFormat);
	sets.setValue("TIMEOUT_DEF",nTimeOut);
	sets.setValue("PORT",nPort);
	sets.setValue("LOGLVL",logSts);
	sets.setValue("LOGDIR",logDir);
	sets.setValue("DBUSR",dbUsr);
	sets.setValue("DBPWD",dbPwd);
	sets.setValue("DBFILE",dbFile);
	sets.setValue("DBFOLDER",dbFolder);
	sets.setValue("CHANGEDBDAY",nChgDbDay);
	sets.setValue("TAGCNT",nTagCnt);
	for( int i=0; i<nTagCnt; i++ ) {
		QString itm = "TAG"+QString::number(i+1);
		sets.setValue(itm,lstTag.at(i)->tag);
		QString tmp="";
		for( int j=0; j<lstTag.at(i)->arrItm.size(); j++) {
			if ( tmp != "" ) tmp += "-";
			tmp += lstTag.at(i)->arrItm.at(j);
		}
		itm = "TAGATTR"+QString::number(i+1);
		sets.setValue(itm,tmp);
		itm.clear();
		tmp.clear();
	}
}

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

void clsLog::startLog(QString addr) {
	clsParamDef *prm = clsParamDef::GetInstance();
	prm->readParam();
	logDir = prm->logDir;
	fnam = logDir+"/"+"xmlclient_"+addr+".log";
	qDebug() << "log fnam=["+fnam+"]";
}

void clsLog::log(QString mess, int /*lvl*/) {
	QFile file(fnam);
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		return;
	}
	QTextStream ot(&file);

	QDateTime cur = QDateTime::currentDateTime();
	ot << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess+"\n";
	file.close();

	qDebug() << cur.toString("yyyy-MM-dd hh:mm:ss.zzz")+":"+mess;
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
}

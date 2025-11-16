/*
 * clsLog.h
 *
 *  Created on: 2009/11/08
 *      Author: cony
 */

#ifndef CLSLOG_H_
#define CLSLOG_H_

#include <QObject>
#include <QtNetwork>
#include <QTime>
#include "clsCalcTime.h"

/**
 * @brief 固定タグ設定
 */
class clsTagAttrRec {
public:
	clsTagAttrRec(QString _tag){
		tag = _tag;
		arrItm.clear();
		arrTblCol.clear();
	}

	QString tag;
	QStringList arrItm;
	QStringList arrTblCol;

	QString mkInsSql(QString tbl, QString topid, QString nid, QStringList lstVal) {
		QString sql = "INSERT INTO "+tbl+"_d_sec_"+tag+"(";
		sql += "topid,nid";
		for( int i=0; i<arrTblCol.size(); i++ ) {
			sql += ","+arrTblCol.at(i);
		}
		sql += ") VALUES ("+topid+","+nid;
		for( int i=0; i<lstVal.size(); i++ ) {
			sql += ",'"+lstVal.at(i)+"'";
		}
		sql += ")";
		return sql;
	}
};

/**
 * @brief システムパラメータクラス
 *
 * XmlServer.iniからシステムパラメータを取得する
 */
class clsParamDef : public QObject {
	Q_OBJECT
public:
	static clsParamDef *GetInstance() {
		static clsParamDef instance;
		return &instance;
	}

	int nTimeOut;
	int nPort;
	QString logDir;
	int logSts;

	QString dbFile;
	QString dbUsr;
	QString dbPwd;
	QString dbFolder;
	int nChgDbDay;

	void readParam();
	void saveParam();

	int nTagCnt;
	QList<clsTagAttrRec *> lstTag;

private:
	clsParamDef(){
		nTagCnt = 0;
		logSts = 0;
	}
	clsParamDef(const clsParamDef &rhs);
	clsParamDef& operator=(const clsParamDef &rhs);

	QObject *par;
};

/**
 * @brief ログクラス
 */
class clsLog : public QObject {
	Q_OBJECT
public:
	clsLog(){}

	void startLog(QTcpSocket *sock);
	void startLog(QString addr);
	void log(QString mess, int lvl=1);

	static const int CLSLOG_DEBUG = 4;
	static const int CLSLOG_WARNING = 3;
	static const int CLSLOG_INFO = 2;
	static const int CLSLOG_FAITAL = 1;
	static const int CLSLOG_NOLOG = 0;

	void startTime();
	void endTime(const QString &mess);
private:
	QString fnam;
	QString timFnam;
	clsCalcTime objTim;
};

#endif /* CLSLOG_H_ */

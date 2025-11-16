/*
 * clsXmlUpd.cpp
 *
 *	Created on: 2009/11/20
 *		Author: cony
 */

#include "clsXmlUpd.h"
#include "clsCalcTime.h"

#include <QDebug>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s) 			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)			_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s) 		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s) 		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsXmlUpd::clsXmlUpd() {
	doc = NULL;
	readSql = NULL;
}

clsXmlUpd::~clsXmlUpd() {
	clearDoc();
	clearSql();
}

void clsXmlUpd::clearObj() {
	clearDoc();
	clearSql();
}

void clsXmlUpd::clearDoc() {
	if (doc != NULL) {
		delete (doc);
		doc = NULL;
	}
}

void clsXmlUpd::clearSql() {
	if (readSql != NULL) {
		delete (readSql);
		readSql = NULL;
	}
	nResCnt = 0;
	lstResult.clear();
}

bool clsXmlUpd::lexSelSql(const QByteArray &sql) {
	qDebug() << "SQL=[" + sql + "]";
	if (readSql != NULL) {
		clearSql();
	}
	readSql = new clsXmlReadSql(db, sql);
	if (readSql->err == false) {
		//TODO log
		return false;
	}
	qDebug() << "table=[" + readSql->tbl + "]";

	return true;
}

bool clsXmlUpd::lexUpdSql(const QByteArray &sql) {
	if (readSql != NULL) {
		clearSql();
	}
	readSql = new clsXmlReadSql(db, sql, true);
	if (readSql->err == false) {
		//TODO log
		return false;
	}
	qDebug() << "tbl=[" + readSql->tbl + "]";
	return true;
}
bool clsXmlUpd::parse(const QByteArray &buf) {
	QString errStr;
	int errLine;
	int errColumn;

	errMess = "";
	doc = new QDomDocument();
	if (!doc->setContent(buf, true, &errStr, &errLine, &errColumn)) {
		errMess = "errLine:" + QString::number(errLine) + ",errColumn:"
				+ QString::number(errColumn) + "," + errStr;
		qDebug() << errMess;
		delete (doc);
		doc = NULL;
		return false;
	}
	return true;
}

bool clsXmlUpd::addXml() {
	if (readSql == NULL) {
		return false;
	}
	if (parse(readSql->insXml) == false) {
		return false;
	}
	if (doc == NULL) {
		return false;
	}

	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		if ( mac == "" ) mac = "N";
		if ( day == "" ) day = bndInitDay();
	}
	qDebug() << "day=["+day+"]";
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	clsDbDef *dbDef = NULL;
	if ( readSql->tbl.indexOf("pce") > 0 || readSql->tbl.indexOf("PCE") > 0 ) {
		dbDef = dbCtrl->getPceDbDef(mstid);
		if ( dbDef == NULL ) {
			return false;
		}
	} else if ( readSql->tbl.indexOf("_") > 0 ) {
		dbDef = dbCtrl->updDb(mstid,mac,day);
		if ( dbDef == NULL ) {
			dbDef = dbCtrl->addDb(mstid, mac, day);
		}
	} else {
		dbDef = dbCtrl->addDb(mstid, mac, day);
	}
	if (dbDef == NULL) {
		return false;
	}
	dbCtrl->setDbDef(dbDef, db);
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		return false;
	}
	if (db->setTable("M" + mstid) == false) {
		errMess = "setTable:" + db->mess;
		db->DisConnect();
		return false;
	}

	db->beginTran();
	QDomElement root = doc->documentElement();
	qDebug() << "root Tag=" + root.tagName();
	if (db->addTopNode(-1, root.tagName(), topid) == false) {
		qDebug() << "addTopNode Error:" + db->mess;
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	if (addAttr(root.attributes(), 0) == false) {
		qDebug() << "addAttr Error";
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	QDomNode node = root.firstChild();
	int srt = 1;
	while (node.isNull() == false) {
		addChildNode(srt, node);
		node = node.nextSibling();
		srt++;
	}
	db->endTran(true);
	db->DisConnect();
	return true;
}

bool clsXmlUpd::appendXml() {
	clsDbResTime objResTime;
	objResTime.startTime(true);
	log->log("start appendXml", clsLog::CLSLOG_DEBUG);
	if (readSql == NULL) {
		log->log("appendXml:readSql:NULL", clsLog::CLSLOG_DEBUG);
		return false;
	}
	if (readSql->selWhr == NULL) {
		log->log("appendXml:selWhr:" + errMess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	objResTime.endTime(1);
	objResTime.startTime();

	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		if ( mac == "" ) mac = "N";
		if ( day == "" ) day = bndInitDay();
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	if (dbCtrl->setDbFile(readSql->tbl, db) == false) {
		clsDbDef *dbDef = dbCtrl->appendDb(mstid, mac, day);
		if (dbDef == NULL) {
			return false;
		}
		dbCtrl->setDbDef(dbDef, db);
	}
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		return false;
	}
	if (db->setTable("M" + mstid) == false) {
		errMess = "setTable:" + db->mess;
		log->log("appendXml:setTable:" + errMess, clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return false;
	}
	objResTime.endTime(2);
	objResTime.startTime();

	readSql->selWhr->setTable("M"+mstid);
	if ( readSql->odrWhr != NULL ) {
		readSql->odrWhr->setTable("M"+mstid);
	}
	QString sql = "";
	sql = readSql->selWhr->mkSelSql();
	if (sql == "") {
		errMess = "whr lex error";
		log->log("appendXml:readSql:" + errMess, clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return false;
	}
	log->log(sql, clsLog::CLSLOG_DEBUG);
	if (db->readRec(sql) == 1) {
		errMess = "read topid error:" + db->mess;
		log->log("appendXml:readRec:" + errMess, clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return false;
	}
	topid = db->rec.value("topid").toString();
	objResTime.endTime(3);
	objResTime.startTime();
	//qDebug() << "appendXml topid=["+topid+"]";
	log->log("appendXml:topid=[" + topid + "]", clsLog::CLSLOG_DEBUG);
	if (topid == "") {
		errMess = "not found top";
		db->DisConnect();
		return false;
	}

	db->beginTran();
	if (parse(readSql->insXml) == false) {
		errMess = "parse Error";
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	QDomElement root = doc->documentElement();
	//qDebug() << "root Tag="+root.tagName();
	QDomNode node = root.firstChild();
	int srt = db->getMaxSrt("d_secnode", topid);
	srt++;
	while (node.isNull() == false) {
		if (addChildNode(srt, node) == false) {
			errMess = "addChildNode Error";
			db->endTran(false);
			db->DisConnect();
			return false;
		}
		node = node.nextSibling();
		srt++;
	}
	db->endTran(true);
	objResTime.endTime(4);
	objResTime.wrtTimeLog(nParPort);
	db->DisConnect();
	return true;
}

bool clsXmlUpd::searchXml(int idx) {
	errMess = "";
	if (readSql == NULL) {
		return false;
	}
	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		if ( mac == "" ) mac = "N";
		if ( day == "" ) day = bndInitDay();
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	if (dbCtrl->setDbFile(readSql->tbl, db) == false) {
		// DB定義検索
		clsDbDef *dbDef = dbCtrl->appendDb(mstid, mac, day);
		if (dbDef == NULL) {
			return false;
		}
		dbCtrl->debugDbDef(dbDef);
		dbCtrl->setDbDef(dbDef, db);
	}
	qDebug() << "dbFile=["+db->dbnam+"]";
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		return false;
	}
	qDebug() << "MstID=[" + mstid + "]";
	db->setTable("M" + mstid);
	if (readSql->odrWhr != NULL) {
		readSql->odrWhr->setTable("M" + mstid);
	}
	readSql->selWhr->setTable("M" + mstid);

	QByteArray sql = "";
	if (readSql->odrWhr == NULL) {
		sql = readSql->selWhr->mkSelSql();
		qDebug() << "SEARCH SQL=[" + sql + "]";
	} else {
		QByteArray wsql = readSql->selWhr->mkSelSql(true);
		sql = readSql->odrWhr->mkOrderSql(wsql, readSql->selWhr->nSelTblCnt);
	}

	qDebug() << sql;
	QSqlQuery *query = db->mkSqlQuery(sql);
	if (query == NULL) {
		errMess = "SELECT Error:" + db->mess;
		db->DisConnect();
		return false;
	}
	nResCnt = 0;
	lstResult.clear();
	lstResultId.clear();
	if ( db->openQuery(query) == false ) {
		errMess = "SELECT Exec Error:" + db->mess;
		db->DisConnect();
		return false;
	}
	while (db->next(query) == 0) {
		qDebug() << "hitt";
		nResCnt++;
		lstResultId << db->queryValue("topid", query);
	}
	db->closeQuery(query);

	qDebug() << "HitCnt=["+QString::number(nResCnt)+"]";
	if (idx == 1) {
		if (readXml(lstResultId.at(0)) == false) {
			errMess = "readXml Error:topid=[" + lstResultId.at(0) + "]";
			db->DisConnect();
			return false;
		}
		lstResult << toString();
		db->DisConnect();
		return true;
	}

	for (int i = 0; i < lstResultId.size(); i++) {
		if (readXml(lstResultId.at(i)) == false) {
			errMess = "readXml Error:topid=[" + lstResultId.at(i) + "]";
			db->DisConnect();
			return false;
		}
		lstResult << toString();
	}

	db->DisConnect();
	return true;
}

bool clsXmlUpd::nextXml(const QString &id) {
	errMess = "";
	if (readSql == NULL) {
		return false;
	}
	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		if ( mac == "" ) mac = "N";
		if ( day == "" ) day = bndInitDay();
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	if (dbCtrl->setDbFile(mstid, db) == false) {
		//DB定義検索
		clsDbDef *dbDef = dbCtrl->appendDb(mstid, mac, day);
		if (dbDef == NULL) {
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		dbCtrl->debugDbDef(dbDef);
		dbCtrl->setDbDef(dbDef, db);
	}
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}

	db->setTable("M" + mstid);
	if (readSql->odrWhr != NULL) {
		readSql->odrWhr->setTable("M" + mstid);
	}
	readSql->selWhr->setTable("M" + mstid);

	if (readXml(id) == false) {
		db->DisConnect();
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}

	db->DisConnect();
	mstid.clear();
	mac.clear();
	day.clear();
	return true;
}

bool clsXmlUpd::allSearchXml(int idx) {
	errMess = "";
	if (readSql == NULL) {
		return false;
	}

	// 検索対象
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	QByteArray dbWhr = readSql->selWhr->mkDbMstWhr();
	qDebug() << "****** dbwhr=["+dbWhr+"]";
	NPListPack<clsDbDef> *dbLst = clsDbCtrl::mkDbLst(dbWhr, log);
	if (dbLst == NULL) {
		errMess = "dblst make Error";
		dbWhr.clear();
		return false;
	}
	dbWhr.clear();

	// 検索ループ
	clsDbDef *dbDef = dbLst->GetFirst();
	QByteArray mstid = readSql->tbl.mid(0, readSql->tbl.length() - 4);
	nResCnt = 0;
	lstResult.clear();
	lstResultId.clear();
	int nStartRow = 0;
	while (dbDef != NULL) {
		dbCtrl->setDbDef(dbDef, db);
		qDebug() << "DBFile=[" + dbDef->dbFile + "]";
		if (db->Connect(db->connDef + "_db") == false) {
			errMess = "connect db" + db->mess;
			delete (dbLst);
			mstid.clear();
			return false;
		}

		db->setTable("M" + mstid);
		if (readSql->odrWhr != NULL) {
			readSql->odrWhr->setTable("M" + mstid);
		}
		readSql->selWhr->setTable("M" + mstid);

		QByteArray sql = "";
		if (readSql->odrWhr == NULL) {
			sql = readSql->selWhr->mkSelSql();
		} else {
			QByteArray wsql = readSql->selWhr->mkSelSql(true);
			sql
					= readSql->odrWhr->mkOrderSql(wsql,
							readSql->selWhr->nSelTblCnt);
		}

		qDebug() << "sql=[" + sql + "]";
		QSqlQuery *query = db->mkSqlQuery(sql);
		if (query == NULL) {
			errMess = "select error:" + db->mess;
			delete (dbLst);
			mstid.clear();
			db->DisConnect();
			return false;
		}
		if (db->execQuery(query) == false) {
			errMess = "select error:" + db->mess;
			delete (dbLst);
			mstid.clear();
			db->DisConnect();
			return false;
		}
		int nRowCnt = 0;
		while (db->next(query) == 0) {
			nRowCnt++;
			nResCnt++;
			lstResultId << db->queryValue("topid", query);
			lstDbFile << dbDef->dbFile;
		}
		qDebug() << "HitCount=[" + QString::number(nRowCnt) + "]";
		qDebug() << "HitCount=[" + QString::number(nResCnt) + "]";
		db->closeQuery(query);
		if (idx == 1) {
			if (nStartRow == 0) { // 最初の１件
				if (readXml(lstResultId.at(0)) == false) {
					errMess = "readXml Error:topid=[" + lstResultId.at(0) + "]";
					db->DisConnect();
					mstid.clear();
					return false;
				}
				lstResult << toString();
				nStartRow = 1;
			}
			db->DisConnect();
			dbDef = dbDef->GetNext();
			continue;
		}

		for (int i = nStartRow; i < lstResultId.size(); i++) {
			if (readXml(lstResultId.at(i)) == false) {
				errMess = "readXml Error:topid=[" + lstResultId.at(i) + "]";
				db->DisConnect();
				mstid.clear();
				return false;
			}
			lstResult << toString();
		}
		nStartRow = lstResultId.size();
		qDebug() << "lstResult size=[" + QString::number(lstResult.size())
				+ "]";
		db->DisConnect();
		dbDef = dbDef->GetNext();
	}

	delete (dbLst);
	mstid.clear();
	return true;
}

bool clsXmlUpd::allNextXml(const QString &id, const QByteArray &dbFile) {
	errMess = "";
	if (readSql == NULL) {
		return false;
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	QByteArray mstid = readSql->tbl.mid(0, readSql->tbl.length() - 4);
	dbCtrl->setDbFile(dbFile, db);
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		mstid.clear();
		return false;
	}

	db->setTable("M" + mstid);
	if (readSql->odrWhr != NULL) {
		readSql->odrWhr->setTable("M" + mstid);
	}
	readSql->selWhr->setTable("M" + mstid);

	if (readXml(id) == false) {
		db->DisConnect();
		mstid.clear();
		return false;
	}

	db->DisConnect();
	mstid.clear();
	return true;
}

bool clsXmlUpd::updateXml() {
	if (readSql == NULL) {
		return false;
	}
	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		mac = "N";
		day = bndInitDay();
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	clsDbDef *dbDef = dbCtrl->updDb(mstid, mac, day);
	if (dbDef == NULL) {
		errMess = "not found or error dbmst";
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}
	dbCtrl->setDbDef(dbDef, db);
	if (db->Connect(db->connDef + "_db") == false) {
		errMess = "connect db" + db->mess;
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}
	db->setTable("M" + mstid);
	QString sql = readSql->selWhr->mkSelSql();
	qDebug() << "SEARCH SQL=[" + sql + "]";
	QSqlQueryModel *mdl = db->mkQueryModel(sql);
	if (mdl->rowCount() == 0) {
		errMess = "not found";
		db->DisConnect();
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}
	QSqlRecord rec = mdl->record(0);
	QByteArray topid = rec.value(0).toByteArray();

	db->beginTran();
	if (parse(readSql->insXml) == false) {
		errMess = "parse Error";
		db->endTran(false);
		db->DisConnect();
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}
	QDomElement root = doc->documentElement();
	QDomNode node = root.firstChild();
	while (node.isNull() == false) {
		if (updChildNode(topid, node) == false) {
			errMess = "updChildNode Error";
			db->endTran(false);
			db->DisConnect();
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		node = node.nextSibling();
	}
	db->endTran(true);
	db->DisConnect();
	mstid.clear();
	mac.clear();
	day.clear();
	return true;
}

bool clsXmlUpd::deleteXml() {
	if (readSql == NULL) {
		return false;
	}
	QByteArray mac = "";
	QByteArray day = "";
	QByteArray mstid = bindTblMstId(readSql->tbl);
	if (getDbKey(mac, day) == false) {
		mac = "N";
		day = bndInitDay();
	}
	clsDbCtrl *dbCtrl = clsDbCtrl::GetInstance();
	QByteArray dbWhr = readSql->selWhr->mkDbMstWhr();
	NPListPack<clsDbDef> *dbLst = clsDbCtrl::mkDbLst(dbWhr, log);
	if (dbLst == NULL) {
		errMess = "dblst make Error";
		dbWhr.clear();
		mstid.clear();
		mac.clear();
		day.clear();
		return false;
	}
	dbWhr.clear();

	clsDbDef *dbDef = dbLst->GetFirst();
	while (dbDef != NULL) {
		dbCtrl->setDbDef(dbDef, db);
		if (db->Connect(db->connDef + "_db") == false) {
			errMess = "connect db" + db->mess;
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		qDebug() << "dbfile=["+db->dbnam+"]";

		db->setTable("M" + mstid);
		if (readSql->odrWhr != NULL) {
			readSql->odrWhr->setTable("M" + mstid);
		}
		readSql->selWhr->setTable("M" + mstid);
		QByteArray sql = readSql->selWhr->mkSelSql();
		qDebug() << "SEARCH SQL=[" + sql + "]";
		QSqlQuery *query = db->mkSqlQuery(sql);
		if ( query == NULL ) {
			errMess = "deleteXml:SELECT SQL Error:"+db->mess;
			db->DisConnect();
			sql.clear();
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		sql.clear();

		if ( db->openQuery(query) == false ) {
			errMess = "deleteXml:SELECT SQL Error:"+db->mess;
			db->DisConnect();
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		QByteArray whr = "";
		while( db->next(query) == 0 ) {
			if ( whr != "" ) whr += ",";
			whr += db->queryValue("topid",query);
		}
		qDebug() << "del whr=["+whr+"]";
		if ( whr == "" ) {
			continue;
		}
		db->beginTran();
		if (db->delSec(whr) == false) {
			errMess = db->mess;
			db->endTran(false);
			db->DisConnect();
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		if (db->delTop(whr) == false) {
			errMess = db->mess;
			db->endTran(false);
			db->DisConnect();
			mstid.clear();
			mac.clear();
			day.clear();
			return false;
		}
		db->endTran(true);
		db->DisConnect();

		dbDef = dbDef->GetNext();
	}

	delete (dbLst);
	mstid.clear();
	mac.clear();
	day.clear();
	return true;
}

QByteArray clsXmlUpd::bindTblMstId(const QByteArray &tbl) {
	if (tbl.indexOf("_") > 0) {
		return tbl.mid(0, tbl.length() - 4);
	}
	return tbl;
}

QByteArray clsXmlUpd::bndInitDay() {
	QByteArray day = QDate::currentDate().toString("yyMMdd").toLocal8Bit().data()+"      ";
	return day;
}

bool clsXmlUpd::getDbKey(QByteArray &mac, QByteArray &day) {
	if ( readSql->selWhr != NULL ) {
		if (readSql->selWhr->getDbKey(mac, day) == true) {
			return true;
		}
	}
	if ( readSql->insXml == "" ) {
		return false;
	}
	QDomElement root = doc->documentElement();
	bool flg1 = false;
	bool flg2 = false;
	if ( root.tagName() == "IST" ) {
		QDomNamedNodeMap lst = root.attributes();
		for (int i = 0; i < lst.count(); i++) {
			QDomNode attr = lst.item(i);
			if (attr.nodeName() == "MAC") {
				mac = attr.nodeValue().toLocal8Bit().data();
				flg1 = true;
			}
			if ( attr.nodeName() == "DAY" ) {
				day = attr.nodeValue().toLocal8Bit().data();
				flg2 = true;
			}
			if ( flg1 == true && flg2 == true ) break;
		}
	}
	if ( flg1 == true && flg2 == true ) {
		return true;
	}
	return false;
}

bool clsXmlUpd::addAttr(QDomNamedNodeMap lst, int lvl) {
	int srt = 0;
	if (lvl == 0) {
		srt = db->getMaxSrt("d_topnode_attr", topid);
	} else if (lvl == 1) {
		srt = db->getMaxSrt("d_secnode_attr", chldid);
	}
	srt++;
	for (int i = 0; i < lst.count(); i++) {
		QDomNode attr = lst.item(i);
		qDebug() << "  " + attr.nodeName() + "=" + attr.nodeValue();
		if (lvl == 0) {
			if (db->addTopAttr(srt, topid, attr.nodeName(), attr.nodeValue())
					== false) {
				qDebug() << "addTopAttr Error:" + db->mess;
				return false;
			}
		} else if (lvl == 1) {
			if (db->addSecAttr(srt, topid, chldid, attr.nodeName(),
					attr.nodeValue()) == false) {
				qDebug() << "addTopAttr Error:" + db->mess;
				return false;
			}
		}
	}
	return true;
}

bool clsXmlUpd::addChildNode(int srt, QDomNode node) {
	qDebug() << " child tag=" + node.toElement().tagName() + " val="
			+ node.toElement().text();
	if (db->addSecNode(srt, topid, node.toElement().tagName(),
			node.toElement().text(), chldid) == false) {
		qDebug() << "addChildNode Error:" + db->mess;
		return false;
	}
	int idx = -1;
	clsParamDef *prm = clsParamDef::GetInstance();
	for (int i = 0; i < prm->nTagCnt; i++) {
		if (node.toElement().tagName() == prm->lstTag.at(i)->tag) {
			idx = i;
			break;
		}
	}
	if (idx < 0) {
		addAttr(node.attributes(), 1);
	} else {
		addFixAttr(idx, node.attributes(), 1);
	}
	return true;
}

bool clsXmlUpd::addFixAttr(int idx, QDomNamedNodeMap lst, int lvl) {
	if (lvl == 0) {
		addAttr(lst, lvl);
		return true;
	}
	clsParamDef *prm = clsParamDef::GetInstance();
	if (idx < 0 || prm->nTagCnt <= idx) {
		addAttr(lst, lvl);
		return true;
	}
	clsTagAttrRec *recDef = prm->lstTag.at(idx);
	if (recDef == NULL) {
		addAttr(lst, lvl);
		return true;
	}
	QList<QByteArray> lstVal;
	for (int i = 0; i < recDef->arrTblCol.size(); i++) {
		lstVal.append("");
	}
	for (int i = 0; i < lst.count(); i++) {
		QDomNode attr = lst.item(i);
		qDebug() << "  " + attr.nodeName() + "=" + attr.nodeValue();
		for (int j = 0; j < recDef->arrTblCol.size(); j++) {
			qDebug() << "    " + recDef->arrItm.at(j) + "?" + attr.nodeName();
			if (recDef->arrItm.at(j) == attr.nodeName()) {
				lstVal.replace(j, attr.nodeValue().toLocal8Bit().data());
				break;
			}
		}
	}
	if (db->addFixAttr(topid, chldid, idx, lstVal) == false) {
		return false;
	}
	lstVal.clear();
	return true;
}

bool clsXmlUpd::updChildNode(const QString &topid, const QDomNode &node) {
	qDebug() << " child tag=" + node.toElement().tagName() + " val="
			+ node.toElement().text();
	QSqlQuery *query = db->mkSqlQuery("UPDATE " + db->tblHead
			+ "_D_SECNOTE SET val=:val WHERE topid=:topid AND tag=:tag");
	if (query == NULL) {
		log->log("updChildNode::UPDATE Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return false;
	}
	query->bindValue(":val", node.toElement().text());
	query->bindValue(":topid", topid);
	query->bindValue(":tag", node.toElement().tagName());
	if (db->execQuery(query) == false) {
		log->log("updChildNode::UPDATE Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		return false;
	}
	int idx = -1;
	clsParamDef *prm = clsParamDef::GetInstance();
	for (int i = 0; i < prm->nTagCnt; i++) {
		if (node.toElement().tagName() == prm->lstTag.at(i)->tag) {
			idx = i;
			break;
		}
	}
	if (idx < 0) {
		updAttr(topid, node.attributes(), 1);
	} else {
		updFixAttr(topid, idx, node.attributes(), 1);
	}
	return true;
}

bool clsXmlUpd::updAttr(const QString &topid, QDomNamedNodeMap lst, int lvl) {
	for (int i = 0; i < lst.count(); i++) {
		QDomNode attr = lst.item(i);
		qDebug() << "  " + attr.nodeName() + "=" + attr.nodeValue();
		QByteArray sql = "";
		if (lvl == 0) {
			sql = "UPDATE " + db->tblHead.toLocal8Bit().data()
					+ "_D_TOPNODE_ATTR SET VAL='" + attr.nodeValue().toLocal8Bit().data()
					+ "' WHERE topid=" + topid.toLocal8Bit().data() + " AND tag='"
					+ attr.nodeName().toLocal8Bit().data() + "'";
		} else if (lvl == 1) {
			sql = "UPDATE " + db->tblHead.toLocal8Bit().data()
					+ "_D_SECNODE_ATTR SET VAL='" + attr.nodeValue().toLocal8Bit().data()
					+ "' WHERE topid=" + topid.toLocal8Bit().data() + " AND tag='"
					+ attr.nodeName().toLocal8Bit().data() + "'";
		}
		if (db->updExecSql(sql) == false) {
			log->log("updAttr:Update Error:" + db->mess, clsLog::CLSLOG_DEBUG);
			sql.clear();
			return false;
		}
		sql.clear();
	}
	return true;
}

bool clsXmlUpd::updFixAttr(const QString &topid, int idx, QDomNamedNodeMap lst,
		int lvl) {
	if (lvl == 0) {
		return updAttr(topid, lst, lvl);
	}
	clsParamDef *prm = clsParamDef::GetInstance();
	if (idx < 0 || prm->nTagCnt <= idx) {
		return updAttr(topid, lst, lvl);
	}
	clsTagAttrRec *recDef = prm->lstTag.at(idx);
	if (recDef == NULL) {
		return updAttr(topid, lst, lvl);
	}
	QByteArray sql = "UPDATE " + db->tblHead.toLocal8Bit().data() + "_D_SEC_"
			+ recDef->tag.toLocal8Bit().data() + " SET ";
	QByteArray itm = "";
	for (int i = 0; i < lst.count(); i++) {
		QDomNode attr = lst.item(i);
		qDebug() << "  " + attr.nodeName() + "=" + attr.nodeValue();
		for (int j = 0; j < recDef->arrTblCol.size(); j++) {
			qDebug() << "    " + recDef->arrItm.at(j) + "?" + attr.nodeName();
			if (recDef->arrItm.at(j) == attr.nodeName()) {
				if (itm != "")
					itm += ",";
				itm += recDef->arrTblCol.at(i).toLocal8Bit().data() + "='"
						+ attr.nodeValue().toLocal8Bit().data() + "'";
				break;
			}
		}
	}
	return true;
}

bool clsXmlUpd::readXml(QString topid) {
	clearDoc();
	QString tbl = bindTblMstId(readSql->tbl);
	QString sql = "SELECT * FROM M" + tbl + "_d_topnode WHERE id=" + topid;
	if (db->readRec(sql) == 1) {
		errMess = "not found top";
		return false;
	}
	doc = new QDomDocument();
	QDomElement root = doc->createElement(db->rec.value("tag").toString());
	sql = "SELECT * FROM M" + tbl + "_d_topnode_attr WHERE topid=" + topid
			+ " ORDER BY srt";
	QSqlQueryModel *mdl = db->mkQueryModel(sql);
	for (int i = 0; i < mdl->rowCount(); i++) {
		QSqlRecord rec = mdl->record(i);
		if (readSql->isOutTagAttr(db->rec.value("tag").toByteArray(),
				rec.value("itm").toByteArray()) == true) {
			qDebug() << "top attr";
			root.setAttribute(rec.value("itm").toString(),
					rec.value("val").toString());
		}
	}
	doc->appendChild(root);
	mdl->clear();

	QString outwhr = readSql->outWhr->whrSecOutTag();
	sql = "SELECT * FROM M" + tbl + "_d_secnode WHERE topid=" + topid;
	if (outwhr != "") {
		sql += " AND " + outwhr;
	}
	//TODO 固定テーブル対応
	sql += " AND (NOT tag IN ('NGP','NGI')) ";

	sql += " ORDER BY id";
	qDebug() << "*****" + sql;
	mdl = db->mkQueryModel(sql);
	for (int i = 0; i < mdl->rowCount(); i++) {
		QSqlRecord rec = mdl->record(i);
		if (readSql->isOutTag(rec.value("tag").toByteArray()) == true) {
			//qDebug() << "child tag=["+rec.value("tag").toString()+"]";
			QDomElement child = doc->createElement(rec.value("tag").toString());
			if (rec.value("val").toString() != "") {
				QDomText txt = doc->createTextNode(rec.value("val").toString());
				child.appendChild(txt);
			}
			if (rec.value("tag").toString() != "NGP"
					&& rec.value("tag").toString() != "NGI") {
				qDebug() << "child tag=[" + rec.value("tag").toString() + "]";
			}
			sql = "SELECT * FROM M" + tbl + "_d_secnode_attr WHERE nid="
					+ rec.value("id").toString();//+" ORDER BY srt";
			QSqlQueryModel *mdlc = db->mkQueryModel(sql);
			for (int j = 0; j < mdlc->rowCount(); j++) {
				QSqlRecord recc = mdlc->record(j);
				if (readSql->isOutTagAttr(rec.value("tag").toByteArray(),
						recc.value("itm").toByteArray()) == true) {
					child.setAttribute(recc.value("itm").toString(),
							recc.value("val").toString());
				}
			}
			mdlc->clear();
			root.appendChild(child);
		} else {
			qDebug() << "Out child tag=[" + rec.value("tag").toString() + "]";
		}
	}
	mdl->clear();

	//TODO 暫定
	clsParamDef *prm = clsParamDef::GetInstance();
	qDebug() << "nTagCnt=[" + QString::number(prm->nTagCnt) + "]";
	for (int i = 0; i < prm->nTagCnt; i++) {
		qDebug() << "tag(" + topid + ")=>[" + prm->lstTag.at(i)->tag + "]";
		getChildTagAttr(topid, prm->lstTag.at(i)->tag, root);
	}
	qDebug() << "xml=" + toString();
	return true;
}

bool clsXmlUpd::getChildTagAttr(QString topid, QString tag, QDomElement &root) {
	if (readSql->isOutTag(tag.toLocal8Bit().data()) == false) {
		return false;
	}

	clsTagAttrRec *tagDef = db->getTagDef(tag);
	if (tagDef == NULL) {
		return false;
	}
	QString sql = "SELECT * FROM M" + bindTblMstId(readSql->tbl) + "_d_sec_"
			+ tag.toLower();
	sql += " WHERE topid=" + topid + " ORDER BY nid";
	QSqlQueryModel *mdlc = db->mkQueryModel(sql);
	for (int i = 0; i < mdlc->rowCount(); i++) {
		QSqlRecord rec = mdlc->record(i);
		QDomElement child = doc->createElement(tag);
		int cnt = 0;
		for (int j = 0; j < tagDef->arrTblCol.size(); j++) {
			if (readSql->isOutTagAttr(tag.toLocal8Bit().data(),
					tagDef->arrItm.at(j).toLocal8Bit().data()) == true) {
				child.setAttribute(tagDef->arrItm.at(j), rec.value(
						tagDef->arrTblCol.at(j)).toString());
				cnt++;
			}
		}
		if (cnt > 0) {
			root.appendChild(child);
		}
	}
	mdlc->clear();
	return true;
}

QByteArray clsXmlUpd::toString() {
	if (doc == NULL) {
		qDebug() << "************ doc NULL **********";
		return "";
	}
	qDebug() << "*** " + doc->toString(2);
	return doc->toByteArray(2);
}

QString clsXmlUpd::mkWhere(QString whrbuf) {
	QString whr = "";

	clsXmlWhereLex lex(whrbuf.toLocal8Bit().data());
	if (lex.error() == false) {
		qDebug() << lex.errMess;
	}
	whr = lex.mkWhr();
	return whr;
}

QString clsXmlUpd::mkSelSql(QString whrbuf) {
	QString whr = "";

	clsXmlWhereLex lex(whrbuf.toLocal8Bit().data());
	whr = lex.mkSelSql();
	return whr;
}

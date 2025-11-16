/*
 * clsDbCtrl.cpp
 *
 *	Created on: 2010/03/23
 *		Author: cony
 */

#include "clsDbCtrl.h"
#include <QDate>
#include <QDir>

clsDbCtrl::clsDbCtrl() {
	db = new clsDb();
	db->setConnDef("xmldb_ctrl");
	db->setPrm();
	db->log = new clsLog();
	db->log->startLog("dbctrl");

	prm = clsParamDef::GetInstance();
	lstDbDef = new NPListPack<clsDbDef> ();
}

clsDbCtrl::~clsDbCtrl() {
	delete (db->log);
	delete (db);
	delete (lstDbDef);
}

// XML追加時DBファイル選択
clsDbDef *clsDbCtrl::addDb(const QByteArray &MstId, const QByteArray &Mac,
		const QByteArray &Day) {
	clsDbDef *dbDef = lstDbDef->GetFirst();
	QByteArray dDay = bindDay(Day);
	QByteArray dMac = bindMac(Mac);
	while (dbDef != NULL) {
		if (dbDef->MstId == MstId && dbDef->Mac == dMac) {
			if (dbDef->dDay == dDay) {
				dMac.clear();
				dDay.clear();
				return dbDef;
			}
			qDebug() << "day=["+dbDef->dDay+"]?["+dDay+"]";
			if (dbDef->dDay < dDay) {
				if (chkDbDate(dbDef,dDay) == false) {
					// DB追加
					lock();
					dbDef->Mac = dMac;
					dbDef->dbFile = mkDbFileName(MstId, dMac, dDay);
					db->log->log("addDbDef start[" + MstId + "][" + dMac+"]["+dDay+"]",
							clsLog::CLSLOG_DEBUG);
					if (addDbDef(dbDef, dDay) == false) {
						db->log->log("addDb:addDbDef Error",
								clsLog::CLSLOG_DEBUG);
						unlock();
						dMac.clear();
						dDay.clear();
						return NULL;
					}
					dbDef->dDay = dDay;
					unlock();
				}
				dMac.clear();
				dDay.clear();
				return dbDef;
			}
		}
		dbDef = dbDef->GetNext();
	}

	if (dbDef == NULL) {
		// DB追加
		lock();
		dbDef = new clsDbDef();
		dbDef->MstId = MstId;
		dbDef->Mac = dMac;
		dbDef->dDay = dDay;
		dbDef->dbFile = mkDbFileName(MstId, dMac, dDay);
		if (newDbDef(dbDef) == false) {
			db->log->log("addDb:newDbDef Error", clsLog::CLSLOG_DEBUG);
			unlock();
			dMac.clear();
			dDay.clear();
			return NULL;
		}
		lstDbDef->AppendList(dbDef);
		unlock();
	}

	dMac.clear();
	dDay.clear();
	return dbDef;
}

clsDbDef *clsDbCtrl::appendDb(const QByteArray &MstId, const QByteArray &Mac,
		const QByteArray &Day) {
	clsDbDef *dbDef = lstDbDef->GetFirst();
	QByteArray dDay = bindDay(Day);
	QByteArray dMac = bindMac(Mac);
	while (dbDef != NULL) {
		if (dbDef->MstId == MstId && dbDef->Mac == dMac) {
			if (dbDef->dDay <= dDay) {
				debugDbDef(dbDef);
				dDay.clear();
				dMac.clear();
				return dbDef;
			}
		}
		dbDef = dbDef->GetNext();
	}
	if (dbDef == NULL) {
		// マスタDB検索
		dbDef = new clsDbDef();
		dbDef->MstId = MstId;
		dbDef->Mac = dMac;
		dbDef->dDay = dDay;
		if (appendReadDb(dbDef) == false) {
			db->log->log("appendDb:getDbDef Error", clsLog::CLSLOG_DEBUG);
			dDay.clear();
			dMac.clear();
			return NULL;
		}
		lock();
		lstDbDef->AppendList(dbDef);
		unlock();
	}
	debugDbDef(dbDef);
	dDay.clear();
	dMac.clear();
	return dbDef;
}

clsDbDef *clsDbCtrl::updDb(const QByteArray &MstId, const QByteArray &Mac,
		const QByteArray &Day) {
	QByteArray dDay = bindDay(Day);
	QByteArray dMac = bindMac(Mac);
	if (db->Connect() == false) {
		db->log->log("addDbDef:Connect Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return NULL;
	}
	QSqlQuery *query = NULL;
	QByteArray sql = "";
	sql
			= "SELECT * FROM d_dbmst WHERE mstid=:mstid AND mac=:mac AND ("
				"(startymd<=:day AND endymd>=:day) OR (startymd<=:day AND endymd IS NULL)) ORDER BY startymd";
	query = db->mkSqlQuery(sql);
	if ( query == NULL ) {
		db->log->log("updDb:SELECT d_dbmst Error:"+db->mess,clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		sql.clear();
		dDay.clear();
		dMac.clear();
		return NULL;
	}
	query->bindValue(":mstid", MstId);
	query->bindValue(":mac", dMac);
	query->bindValue(":day", dDay);
	sql.clear();
	dDay.clear();
	dMac.clear();

	if (db->openQuery(query) == false) {
		db->closeQuery(query);
		db->log->log("updDb:d_dbmst SELECT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return NULL;
	}
	if (db->next(query) != 0) {
		db->closeQuery(query);
		db->log->log("updDb:d_dbmst SELECT Not Fount:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return NULL;
	}
	clsDbDef *def = new clsDbDef();
	def->MstId = db->queryValue("mstid", query);
	def->dDay = db->queryValue("startymd", query);
	def->dbFile = db->queryValue("dbfile", query);
	def->Mac = db->queryValue("mac", query);
	db->closeQuery(query);
	db->DisConnect();
	return def;
}

clsDbDef *clsDbCtrl::getPceDbDef(const QByteArray &MstId) {
	if (db->Connect() == false) {
		db->log->log("getPceDbDef:Connect Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return false;
	}
	QByteArray sql = "SELECT * FROM m_dbmst WHERE mstid=:mstid AND startymd='--------'";
	QSqlQuery *query = db->mkSqlQuery(sql);
	if ( query == NULL ) {
		db->log->log("getPceDbDef:SELECT d_dbmst Error:"+db->mess,clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return NULL;
	}
	sql.clear();

	query->bindValue(":mstid", MstId);
	if (db->openQuery(query) == false) {
		db->closeQuery(query);
		db->log->log("getPceDbDef:m_dbmst SELECT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return NULL;
	}
	if (db->next(query) == 0) {
		clsDbDef *dbDef = new clsDbDef();
		dbDef->MstId = db->queryValue("mstid",query);
		dbDef->dbFile = db->queryValue("dbfile",query);
		db->closeQuery(query);
		db->log->log("getPceDbDef:m_dbmst SELECT Not Fount:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return dbDef;
	}
	db->closeQuery(query);
	db->beginTran();

	clsDbDef *dbDef = new clsDbDef();
	dbDef->MstId = MstId;
	dbDef->Mac = "N";
	dbDef->dDay = "--------";
	dbDef->dbFile = mkDbFileName(dbDef->MstId,dbDef->Mac,dbDef->dDay);

	sql = "INSERT INTO m_dbmst(mstid,mac,startymd,endymd,dbfile) VALUES (:mstid,'N','--------',NULL,:dbfile)";
	QSqlQuery *updQuery = db->mkSqlQuery(sql);
	if ( updQuery == NULL ) {
		db->log->log("getPceDbDef:m_dbmst INSERT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return NULL;
	}
	sql.clear();

	updQuery->bindValue(":mstid",MstId);
	updQuery->bindValue(":dbfile",dbDef->dbFile);
	if ( db->execQuery(updQuery) == false ) {
		db->log->log("getPceDbDef:m_dbmst INSERT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	if ( makeDbFile(dbDef) == false ) {
		db->log->log("getPceDbDef:makeDbFile Error:",clsLog::CLSLOG_DEBUG);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	db->closeQuery(updQuery);
	db->endTran(true);
	db->DisConnect();
	return dbDef;
}

bool clsDbCtrl::addDbDef(const clsDbDef *dbDef, const QByteArray &dDay) {
	debugDbDef(dbDef);
	if (db->Connect() == false) {
		db->log->log("addDbDef:Connect Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return false;
	}
	db->beginTran();
	QByteArray sql =
			"SELECT * FROM m_dbmst WHERE mstid=:mstid AND mac=:mac AND endymd IS NULL";
	QSqlQuery *query = db->mkSqlQuery(sql);
	sql.clear();
	if (query == NULL) {
		db->log->log("addDbDef:mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	debugDbDef(dbDef);
	query->bindValue(":mstid", dbDef->MstId);
	query->bindValue(":mac", dbDef->Mac);
	if (db->openQuery() == false) {
		db->closeQuery(query);
		db->log->log("addDbDef:openQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	QSqlQuery *updQuery = NULL;
	if (db->next() == 0) {
		sql = "UPDATE m_dbmst SET endymd=:endymd WHERE mstid=:mstid AND mac=:mac AND endymd IS NULL";
		updQuery = db->mkSqlQuery(sql);
		if (updQuery == NULL) {
			db->log->log("addDbDef:UPDATE mkSqlQuery Error:" + db->mess,
					clsLog::CLSLOG_DEBUG);
			db->closeQuery(query);
			db->endTran(false);
			db->DisConnect();
			return false;
		}
		sql.clear();
		updQuery->bindValue(":mstid", dbDef->MstId);
		updQuery->bindValue(":mac", dbDef->Mac);
		updQuery->bindValue(":endymd", dDay);
		if (db->execQuery(updQuery) == false) {
			db->log->log("addDbDef:UPDATE Exec mkSqlQuery Error:" + db->mess,
					clsLog::CLSLOG_DEBUG);
			db->closeQuery(query);
			db->closeQuery(updQuery);
			db->endTran(false);
			db->DisConnect();
			return false;
		}
	}
	sql = "INSERT INTO m_dbmst(mstid,mac,startymd,dbfile,endymd) VALUES (:mstid,:mac,:startymd,:dbfile,NULL)";
	updQuery = db->mkSqlQuery(sql);
	if (updQuery == NULL) {
		db->log->log("addDbDef:INSERT mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	sql.clear();
	updQuery->bindValue(":mstid", dbDef->MstId);
	updQuery->bindValue(":mac", dbDef->Mac);
	updQuery->bindValue(":startymd", dDay);
	qDebug() << "startymd=["+dDay+"]";
	updQuery->bindValue(":dbfile",dbDef->dbFile);
	if (db->execQuery(updQuery) == false) {
		db->log->log("addDbDef:INSERT Exec mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	if ( makeDbFile(dbDef) == false ) {
		db->log->log("newDbDef:makeDbFile Error:",clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	db->closeQuery(query);
	db->closeQuery(updQuery);
	db->endTran(true);
	db->DisConnect();
	return true;
}

bool clsDbCtrl::newDbDef(clsDbDef *dbDef) {
	if (db->Connect() == false) {
		db->log->log("newDbDef:Connect Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return false;
	}

	db->beginTran();
	QByteArray sql = "SELECT * FROM m_dbmst WHERE mstid=:mstid AND mac=:mac AND ("
				"(startymd<=:day AND endymd>=:day) OR (startymd<=:day AND endymd IS NULL)) ORDER BY startymd";
	QSqlQuery *query = db->mkSqlQuery(sql);
	sql.clear();
	if (query == NULL) {
		db->log->log("newDbDef:mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	query->bindValue(":mstid", dbDef->MstId);
	query->bindValue(":mac", dbDef->Mac);
	query->bindValue(":day", dbDef->dDay);
	if (db->openQuery() == false) {
		db->closeQuery(query);
		db->log->log("newDbDef:openQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	if (db->next() == 0) {
		QByteArray dDay = dbDef->dDay;
		dbDef->dbFile = db->queryValue("dbfile",query);
		dbDef->dDay = db->queryValue("startymd",query);
		if ( chkDbDate(dbDef,dDay) == true ) {
			db->closeQuery(query);
			db->endTran(false);
			db->DisConnect();
			return true;
		}
		dbDef->dDay = dDay;
		dbDef->dbFile = mkDbFileName(dbDef->MstId,dbDef->Mac,dbDef->dDay);
	}

	QSqlQuery *updQuery = NULL;
	sql = "UPDATE m_dbmst SET endymd=:endymd WHERE mstid=:mstid AND mac=:mac AND endymd IS NULL";
	updQuery = db->mkSqlQuery(sql);
	if (updQuery == NULL) {
		db->log->log("newDbDef:UPDATE mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	sql.clear();
	updQuery->bindValue(":mstid", dbDef->MstId);
	updQuery->bindValue(":mac", dbDef->Mac);
	updQuery->bindValue(":endymd", dbDef->dDay);
	if (db->execQuery(updQuery) == false) {
		db->log->log("newDbDef:UPDATE mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	sql = "INSERT INTO m_dbmst(mstid,mac,startymd,dbfile,endymd) VALUES (:mstid,:mac,:startymd,:dbfile,NULL)";
	updQuery = db->mkSqlQuery(sql);
	if (updQuery == NULL) {
		db->log->log("newDbDef:INSERT mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	sql.clear();
	updQuery->bindValue(":mstid", dbDef->MstId);
	updQuery->bindValue(":mac", dbDef->Mac);
	updQuery->bindValue(":startymd", dbDef->dDay);
	updQuery->bindValue(":dbfile",dbDef->dbFile);
	if (db->execQuery(updQuery) == false) {
		db->log->log("addDbDef:INSERT mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	if ( makeDbFile(dbDef) == false ) {
		db->log->log("newDbDef:makeDbFile Error:",clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->closeQuery(updQuery);
		db->endTran(false);
		db->DisConnect();
		return false;
	}

	db->closeQuery(query);
	db->closeQuery(updQuery);
	db->endTran(true);
	db->DisConnect();
	return true;
}

bool clsDbCtrl::appendReadDb(clsDbDef *dbDef) {
	if (db->Connect() == false) {
		db->log->log("addDbDef:Connect Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		return false;
	}
	QByteArray sql = "SELECT * FROM m_dbmst WHERE mstid=:mstid AND mac=:mac AND ("
				"(startymd<=:day AND endymd>=:day) OR (startymd<=:day AND endymd IS NULL)) ORDER BY startymd";
	QSqlQuery *query = db->mkSqlQuery(sql);
	sql.clear();
	if (query == NULL) {
		db->log->log("newDbDef:mkSqlQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->endTran(false);
		db->DisConnect();
		return false;
	}
	query->bindValue(":mstid", dbDef->MstId);
	query->bindValue(":mac", dbDef->Mac);
	query->bindValue(":day", dbDef->dDay);
	if (db->openQuery() == false) {
		db->closeQuery(query);
		db->log->log("newDbDef:openQuery Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return false;
	}
	if (db->next() == 0) {
		dbDef->dbFile = db->queryValue("dbfile",query);
		dbDef->dDay = db->queryValue("startymd",query);
		db->closeQuery(query);
		db->DisConnect();
		return true;
	}
	db->closeQuery(query);
	db->DisConnect();
	return false;
}

void clsDbCtrl::lock() {
	mutex.lock();
}

void clsDbCtrl::unlock() {
	mutex.unlock();
}

bool clsDbCtrl::chkDbDate(const clsDbDef *dbDef, const QByteArray &dDay) {
	if (prm->nChgDbDay <= 0) {
		return true;
	}
	QDate day = QDate::fromString(dbDef->dDay, "yyyyMMdd");
	QDate cday = day.addDays(prm->nChgDbDay);
	if ( dDay != "" ) {
		day = QDate::fromString(dDay,"yyyyMMdd");
	} else {
		day = QDate::currentDate();
	}
	db->log->log("chkDbDate:" + day.toString("yyyyMMdd") + "?" + cday.toString(
			"yyyyMMdd"), clsLog::CLSLOG_DEBUG);
	if (day < cday) {
		return true;
	}
	return false;
}

bool clsDbCtrl::makeDbFile(const clsDbDef *dbDef) {
	//フォルダチェック
	QDir dir;
	if ( dbDef->dbFile.mid(0,3) == "pce" ) {
		if (dir.exists(prm->dbFolder + "/pce") == false) {
			dir.mkdir(prm->dbFolder + "/pce");
		}
	} else {
		if (dir.exists(prm->dbFolder + "/" + dbDef->dDay.mid(0, 6)) == false) {
			dir.mkdir(prm->dbFolder + "/" + dbDef->dDay.mid(0, 6));
		}
	}
	if (clsDb::createDb(prm->dbUsr, prm->dbPwd, prm->dbFolder + "/"
			+ dbDef->dbFile) == false) {
		db->log->log("makeDbFile:create dbfile error:" + prm->dbFolder + "/"
				+ dbDef->dbFile, clsLog::CLSLOG_DEBUG);
		return false;
	}

	clsDb *dbMk = new clsDb();
	dbMk->log = db->log;
	dbMk->setConnDef("dbmake");
	dbMk->setPrm("QIBASE", "localhost", prm->dbFolder + "/" + dbDef->dbFile,
			prm->dbUsr, prm->dbPwd);
	if (dbMk->Connect() == false) {
		db->log->log("makeDbFile:connect newdb error:" + dbMk->mess,
				clsLog::CLSLOG_DEBUG);
		delete (dbMk);
		return false;
	}
	if (dbMk->mkInitTbl() == false) {
		db->log->log("makeDbFile::mkInitTbl Error:" + dbMk->mess,
				clsLog::CLSLOG_DEBUG);
		dbMk->DisConnect();
		delete (dbMk);
		return false;
	}
	if (dbMk->setTable("M" + dbDef->MstId) == false) {
		db->log->log("makeDbFile:connect newdb error:" + dbMk->mess,
				clsLog::CLSLOG_DEBUG);
		dbMk->DisConnect();
		delete (dbMk);
		return false;
	}

	dbMk->DisConnect();
	delete (dbMk);
	return true;
}

void clsDbCtrl::setDbDef(const clsDbDef *dbDef, clsDb *db) {
	db->dbnam = prm->dbFolder + "/" + dbDef->dbFile;
}

bool clsDbCtrl::setDbFile(const QByteArray &MstId, clsDb *db) {
	if (MstId.indexOf("/xmldb") > 0) {
		db->dbnam = prm->dbFolder + "/" + MstId;
		return true;
	}
	return false;
}

NPListPack<clsDbDef> *clsDbCtrl::mkDbLst(const QByteArray &dbWhr, clsLog *log) {
	NPListPack<clsDbDef> *lstDb = new NPListPack<clsDbDef> ();

	clsDb *db = new clsDb();
	db->setPrm();
	db->log = log;
	db->setConnDef("mkdblst");
	if (db->Connect() == false) {
		log->log("mkDbLst:Connect Error:" + db->mess, clsLog::CLSLOG_DEBUG);
		delete (db);
		return false;
	}
	QByteArray sql = "SELECT distinct DBFile FROM m_dbmst";
	if (dbWhr != "")
		sql += " WHERE " + dbWhr;
	sql += " ORDER BY STARTYMD";

	qDebug() << "******** "+sql;
	QSqlQuery *query = db->mkSqlQuery(sql);
	sql.clear();
	if (query == NULL) {
		log->log("mkDbLst:m_dbmst SELECT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		delete (db);
		return false;
	}
	if (db->execQuery(query) == false) {
		log->log("mkDbLst:m_dbmst SELECT Error:" + db->mess,
				clsLog::CLSLOG_DEBUG);
		db->closeQuery(query);
		db->DisConnect();
		delete (db);
		return false;
	}
	while (db->next(query) == 0) {
		clsDbDef *dbDef = new clsDbDef();
		dbDef->dbFile = db->queryValue("DBFILE", query);
		lstDb->AppendList(dbDef);
	}

	db->closeQuery(query);
	db->DisConnect();
	delete (db);
	return lstDb;
}

void clsDbCtrl::debugDbDef(const clsDbDef *dbDef) {
	if (db != NULL) {
		if (db->log != NULL) {
			if (dbDef == NULL) {
				db->log->log("dbDef IS NULL", clsLog::CLSLOG_DEBUG);
			} else {
				db->log->log("MstId=[" + dbDef->MstId + "],dDay=["
						+ dbDef->dDay + "],Mac=[" + dbDef->Mac
						+ "],dbFile=[" + dbDef->dbFile + "]",
						clsLog::CLSLOG_DEBUG);
			}
		}
	}
}

QByteArray clsDbCtrl::bindDay(const QByteArray &daytime) {
	qDebug() << "day=["+daytime+"]";
	if ( daytime.length() < 12 ) {
		qDebug() << "small";
		return "200"+daytime.mid(0,5);
	}
	return "20"+daytime.mid(0,6);
}

QByteArray clsDbCtrl::mkDbFileName(const QByteArray &MstId, const QByteArray &Mac, const QByteArray &Day) {
	if ( Day == "--------" ) {
		return "pce/xmldb_"+MstId+"_pce.fdb";
	}
	return Day.mid(0,6)+"/xmldb_"+MstId+"_"+Mac+"_"+Day.mid(6,2)+".fdb";
}

QByteArray clsDbCtrl::bindMac(const QByteArray &Mac) {
	if ( Mac == "" ) return "N";
	return Mac;
}

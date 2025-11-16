#include "clsDb.h"

#include <QStringList>
#include <QMessageBox>
#include <QDateTime>
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

clsDb::clsDb(QObject *parent) :
	QObject(parent) {
	mess = "";

	prm = clsParamDef::GetInstance();
	nTagTop = -1;
	nTagSec = -1;
	connDef = "comConn";
	queryTop = NULL;
	queryTopAttr = NULL;
	querySec = NULL;
	querySecAttr = NULL;
	nFixInsCnt = 0;
	arrQueryFixIns = NULL;

	connNam = "";
}

clsDb::~clsDb() {
	if ( queryTop != NULL ) delete(queryTop);
	if ( queryTopAttr != NULL ) delete(queryTopAttr);
	if ( querySec != NULL ) delete(querySec);
	if ( querySecAttr != NULL ) delete(querySecAttr);
	if ( arrQueryFixIns != NULL ) {
		for( int i=0; i<nFixInsCnt; i++ ) {
			delete(arrQueryFixIns[i]);
		}
		delete(arrQueryFixIns);
	}
}

void clsDb::setConnDef(const QString &def) {
	connDef = def;
}

void clsDb::setPrm() {
	setPrm("QIBASE", "localhost", prm->dbFile, prm->dbUsr, prm->dbPwd);
}

void clsDb::setPrm(const QString &_dbtyp, const QString &_dbhost, const QString &_dbnam,
		const QString &_dbusr, const QString &_dbpwd) {
	dbtype = _dbtyp;
	dbhost = _dbhost;
	dbnam = _dbnam;
	dbusr = _dbusr;
	dbpwd = _dbpwd;
}

bool clsDb::getDatabase(const QString &nam) {
	QString strConnNam = "";
	if ( nam != "" ) {
		strConnNam = nam;
	}
	if ( strConnNam == "" ) {
		strConnNam = connDef;
	}
	if ( strConnNam == "" ) {
		log->log("getDatabase: error connNam is NULL",clsLog::CLSLOG_DEBUG);
		return false;
	}
	log->log("getDatabase: name=["+strConnNam+"]<=["+nam+"]",clsLog::CLSLOG_DEBUG);
	db = QSqlDatabase::database(strConnNam);
	if ( db.isValid() == false ) {
		QStringList lst = QSqlDatabase::connectionNames();
		for( int i=0; i<lst.size(); i++ ) {
			log->log("getDatabase: connNameLst["+QString::number(i)+"]=["+lst.at(i)+"]",clsLog::CLSLOG_DEBUG);
		}
		log->log("getDatabase: isValid false name=["+strConnNam+"]",clsLog::CLSLOG_DEBUG);
		return false;
	}
	connNam = strConnNam;
	return true;
}

bool clsDb::mkDatabase(const QString &nam) {
	QString strConnNam = "";
	if ( nam != "" ) {
		strConnNam = nam;
	}
	if ( strConnNam == "" ) {
		strConnNam = connDef;
	}
	if ( strConnNam == "" ) {
		return false;
	}
	log->log("getDatabase:addDatabase: name=["+strConnNam+"]<=["+nam+"]",clsLog::CLSLOG_DEBUG);
	db = QSqlDatabase::addDatabase(dbtype, strConnNam);
	if (dbnam != "") {
		db.setDatabaseName(dbnam);
	} else {
		db.setDatabaseName(":memory:");
	}
	if (dbhost != "") {
		db.setHostName(dbhost);
	}
	if (dbusr != "") {
		db.setUserName(dbusr);
	}
	if (dbpwd != "") {
		db.setPassword(dbpwd);
	}
	db.setPort(6789);
	connNam = strConnNam;
	return true;
}
bool clsDb::Connect(QString nam) {	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if ( getDatabase(nam) == false ) {
		if ( mkDatabase(nam) == false ) {
			return false;
		}
	}
	curDbNam = "";
	if ( db.databaseName() != dbnam ) {
		db.setDatabaseName(dbnam);
	}
	if (!db.open()) {
		QStringList lst = db.drivers();
		QString sDbDrv = "";
		for (int i = 0; i < lst.size(); i++) {
			sDbDrv = lst.at(i) + ",";
		}
		QSqlError err = db.lastError();
		/*
		 QMessageBox::critical(0,QString::fromLocal8Bit("接続エラー"),
		 dbnam+QString::fromLocal8Bit("接続失敗しました")+"\n"+dbtype+":"+dbnam+":"+dbhost+":"+dbusr+":"+dbpwd+"\n"+
		 err.text()+"\n"+sDbDrv
		 , QMessageBox::Cancel, QMessageBox::NoButton);
		 */
		mess = err.text() + "[" + dbtype + ":" + dbnam + ":" + dbhost + ":"
				+ dbusr + ":" + dbpwd + "]";
		log->log("connect Error:"+mess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	curDbNam = nam;
	return true;
}

bool clsDb::DisConnect() {
	if ( queryTop != NULL ) {
		queryTop->clear();
		delete(queryTop);
		queryTop = NULL;
	}
	if ( queryTopAttr != NULL ) {
		queryTopAttr->clear();
		delete(queryTopAttr);
		queryTopAttr = NULL;
	}
	if ( querySec != NULL ) {
		querySec->clear();
		delete(querySec);
		querySec = NULL;
	}
	if ( querySecAttr != NULL ) {
		querySecAttr->clear();
		delete(querySecAttr);
		querySecAttr = NULL;
	}
	if ( arrQueryFixIns != NULL ) {
		for( int i=0; i<nFixInsCnt; i++ ) {
			if ( arrQueryFixIns[i] != NULL ) {
				arrQueryFixIns[i]->clear();
				delete(arrQueryFixIns[i]);
			}
		}
		delete(arrQueryFixIns);
		arrQueryFixIns = NULL;
	}
	db.close();
	return true;
}

bool clsDb::updExecSql(const QString &sql) {
	mess = "";
	//qDebug() << "update SQL " + sql;
	QSqlQuery query(db);
	log->log(sql, clsLog::CLSLOG_DEBUG);
	if (query.exec(sql) == false) {
		QSqlError err = query.lastError();
		mess = err.text();
		query.clear();
		log->log(sql, clsLog::CLSLOG_DEBUG);
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	query.clear();
	log->log("execSQL success", clsLog::CLSLOG_DEBUG);
	return true;
}

QString clsDb::maxId(const QString &tbl) {
	mess = "";
	//TODO
	QSqlQuery query(db);
	/*
	 if (query.exec("SELECT max(id) FROM " + tbl) == false) {
	 return "";
	 }
	 */
	if (query.exec("SELECT NEXT VALUE FOR " + tbl + "_id_seq FROM RDB$DATABASE")
			== false) {
		QSqlError err = query.lastError();
		mess = err.text();
		return "";
	}
	QString ret = "0";
	int n = 0;
	while (query.next()) {
		n = query.value(0).toInt();
	}
	n++;
	ret = QString::number(n);
	return ret;
}

QSqlQueryModel *clsDb::mkQueryModel(const QString &sql) {
	mess = "";
	errflg = true;
	QSqlQueryModel *model = new QSqlQueryModel(this);
	model->setQuery(sql, db);
	//qDebug() << sql;
	if (model->lastError().isValid()) {
		errflg = false;
		mess = model->lastError().text();
	}
	return model;
}

int clsDb::readRec(const QString &sql) {
	mess = "";
	errflg = true;
	QSqlQueryModel *mdl = mkQueryModel(sql);
	if (errflg == false) {
		mdl->clear();
		return -1;
	}
	if (mdl->rowCount() <= 0) {
		mdl->clear();
		return 1;
	}
	rec = mdl->record(0);
	mdl->clear();
	return 0;
}

QSqlQuery *clsDb::mkSqlQuery(const QString &sql) {
	if ( log != NULL ) {
		log->log("mkSqlQuery:"+sql,clsLog::CLSLOG_DEBUG);
	}
	openedQuery = new QSqlQuery(db);
	if ( openedQuery->prepare(sql) == false ) {
		mess = openedQuery->lastError().text();
		return NULL;
	}
	return openedQuery;
}

bool clsDb::openQuery(QSqlQuery *query) {
	QSqlQuery *q = query;
	if ( q == NULL ) {
		q = openedQuery;
	}
	if ( q->exec() == false ) {
		mess = q->lastError().text();
		if ( q == openedQuery ) {
			closeQuery(q);
			return false;
		}
	}
	return true;
}

int clsDb::next(QSqlQuery *query) {
	QSqlQuery *q = query;
	if ( q == NULL ) {
		q = openedQuery;
	}
	if ( q->isSelect() == false ) {
		return -1;
	}
	if ( q->next() == false ) {
		return 1;
	}
	return 0;
}

void clsDb::closeQuery(QSqlQuery *query) {
	QSqlQuery *q = query;
	if ( q == NULL ) {
		q = openedQuery;
	}
	if ( q != NULL ) {
		q->clear();
		delete(q);
	}
}

QByteArray clsDb::queryValue(const QString &itm, QSqlQuery *query) {
	QSqlQuery *q = query;
	if ( q == NULL ) {
		q = openedQuery;
	}
	QSqlRecord rec = q->record();
	int idx = rec.indexOf(itm);
	if ( idx < 0 ) {
		return "";
	}
	return q->value(idx).toByteArray();
}

bool clsDb::execQuery(QSqlQuery *query) {
	QSqlQuery *q = query;
	if ( q == NULL ) {
		q = openedQuery;
	}
	if ( q->exec() == false ) {
		mess = q->lastError().text();
		return false;
	}
	return true;
}

QString clsDb::curDay(bool flgTime) {
	QDateTime cur = QDateTime::currentDateTime();
	QString ret = "";
	QString fmt = "yyyy-MM-dd";
	if (flgTime == true) {
		fmt += " HH:mm:ss";
	}
	ret = cur.toString(fmt);
	if (flgTime == false) {
		ret += " 00:00:00";
	}
	fmt.clear();
	return ret;
}

bool clsDb::beginTran() {
	if (db.transaction() == false) {
		errflg = false;
		mess = db.lastError().text();
		return false;
	}
	return true;
}

bool clsDb::endTran(bool flg) {
	bool ret;
	if (flg == false) {
		ret = db.rollback();
	} else {
		ret = db.commit();
	}
	if (ret == false) {
		errflg = false;
		mess = db.lastError().text();
		return false;
	}
	return true;
}

bool clsDb::makePrepare() {
	if ( queryTop != NULL ) delete(queryTop);
	if ( queryTopAttr != NULL ) delete(queryTopAttr);
	if ( querySec != NULL ) delete(querySec);
	if ( querySecAttr != NULL ) delete(querySecAttr);
	if ( arrQueryFixIns != NULL ) {
		for( int i=0; i<nFixInsCnt; i++ ) {
			if ( arrQueryFixIns[i] != NULL )
				delete(arrQueryFixIns[i]);
		}
		delete(arrQueryFixIns);
	}
	//if ( queryReadLidEid != NULL ) delete(queryReadLidEid);

	queryTop = new QSqlQuery(db);
	queryTopAttr = new QSqlQuery(db);
	querySec = new QSqlQuery(db);
	querySecAttr = new QSqlQuery(db);
	//queryReadLidEid = new QSqlQuery(db);

	if (queryTop->prepare("INSERT INTO " + tblHead
			+ "_d_topnode(id,tag,srt) VALUES (:id,:tag,:srt)") == false) {
		QSqlError err = queryTop->lastError();
		mess = "Top:" + err.text();
		queryTop->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	if (queryTopAttr->prepare(
			"INSERT INTO " + tblHead
					+ "_d_topnode_attr(id,topid,srt,itm,val) VALUES (:id,:topid,:srt,:itm,:val)")
			== false) {
		QSqlError err = queryTopAttr->lastError();
		mess = "Top Attr:" + err.text();
		queryTopAttr->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	if (querySec->prepare(
			"INSERT INTO " + tblHead
					+ "_d_secnode(id,topid,srt,tag,val) VALUES (:id,:topid,:srt,:tag,:val)")
			== false) {
		QSqlError err = querySec->lastError();
		mess = "Sec;" + err.text();
		querySec->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	if (querySecAttr->prepare(
			"INSERT INTO " + tblHead
					+ "_d_secnode_attr(id,topid,nid,srt,itm,val) VALUES (:id,:topid,:nid,:srt,:itm,:val)")
			== false) {
		QSqlError err = querySecAttr->lastError();
		mess = "Sec Attr:" + err.text();
		querySecAttr->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}

	nFixInsCnt = prm->nTagCnt;
	if ( nFixInsCnt > 0 ) {
		arrQueryFixIns = new QSqlQuery*[nFixInsCnt];
		QString sql = "";
		for( int j=0; j<nFixInsCnt; j++ ) {
			clsTagAttrRec *recDef = prm->lstTag.at(j);
			sql = "INSERT INTO "+tblHead+"_d_sec_"+recDef->tag+"(id,topid,nid";
			for( int i=0; i<recDef->arrTblCol.size(); i++ ) {
				sql += ","+recDef->arrTblCol.at(i);
			}
			sql += ") VALUES (:id,:topid,:nid";
			for( int i=0; i<recDef->arrTblCol.size(); i++ ) {
				sql += ",:"+recDef->arrTblCol.at(i);
			}
			sql += ")";
			arrQueryFixIns[j] = new QSqlQuery(db);
			if ( arrQueryFixIns[j]->prepare(sql) == false ) {
				mess = "Fix TagAttr:"+arrQueryFixIns[j]->lastError().text();
				arrQueryFixIns[j]->clear();
				log->log(mess, clsLog::CLSLOG_DEBUG);
				return false;
			}
		}
	}
	return true;
}

bool clsDb::addTopNode(int no, const QString &tag, QString &parid) {
	if (setTag(tag, 1) == false) {
		return false;
	}
	if (no == -1) {
		//no = getMaxSrt("d_topnode", "");
		no = 0;
	}
	parid = maxId(tblHead + "_d_topnode");
	/*
	 QString sql = "INSERT INTO " + tblHead + "_d_topnode(id,tag,srt) VALUES ("
	 + parid + ",'" + tag + "'," + QString::number(no) + ")";
	 return updExecSql(sql);
	 */
	queryTop->bindValue(":id", parid);
	queryTop->bindValue(":tag", tag);
	queryTop->bindValue(":srt", QString::number(no));
	if (queryTop->exec() == false) {
		QSqlError err = queryTop->lastError();
		mess = err.text();
		queryTop->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsDb::addTopAttr(int no, const QString &topid, const QString &tag, const QString &val) {
	if (no == -1) {
		no = getMaxSrt("d_topnode_attr", topid);
	}
	QString id = maxId(tblHead + "_d_topnode_attr");
	/*
	 QString sql = "INSERT INTO " + tblHead
	 + "_d_topnode_attr(topid,srt,itm,val) VALUES (" + topid + ","
	 + QString::number(no) + ",'" + tag + "','" + val + "')";
	 return updExecSql(sql);
	 */
	queryTopAttr->bindValue(":id", id);
	queryTopAttr->bindValue(":topid", topid);
	queryTopAttr->bindValue(":srt", QString::number(no));
	queryTopAttr->bindValue(":itm", tag);
	queryTopAttr->bindValue(":val", val);
	if (queryTopAttr->exec() == false) {
		QSqlError err = queryTopAttr->lastError();
		mess = err.text();
		queryTopAttr->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsDb::addSecNode(int no, const QString &topid, const QString &tag, const QString &val,
		QString &parid) {
	if (setTag(tag, 2) == false) {
		return false;
	}
	if (no == -1) {
		no = getMaxSrt("d_secnode", topid);
	}
	parid = maxId(tblHead + "_d_secnode");
	/*
	 QString sql = "INSERT INTO " + tblHead
	 + "_d_secnode(id,topid,tag,val,srt) VALUES (" + parid + "," + topid
	 + ",'" + tag + "','" + val + "'," + QString::number(no) + ")";
	 return updExecSql(sql);
	 */
	querySec->bindValue(":id", parid);
	querySec->bindValue(":topid", topid);
	querySec->bindValue(":srt", QString::number(no));
	querySec->bindValue(":tag", tag);
	querySec->bindValue(":val", val);
	if (querySec->exec() == false) {
		QSqlError err = querySec->lastError();
		mess = err.text();
		querySec->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsDb::addSecAttr(int no, const QString &topid, const QString &nid, const QString &tag,
		const QString &val) {
	if (no == -1) {
		no = getMaxSrt("d_secnode_attr", nid);
	}
	QString id = maxId(tblHead + "_d_secnode_attr");
	/*
	 QString sql = "INSERT INTO " + tblHead
	 + "_d_secnode_attr(topid,nid,srt,itm,val) VALUES (" + topid + ","
	 + nid + "," + QString::number(no) + ",'" + tag + "','" + val + "')";
	 return updExecSql(sql);
	 */
	querySecAttr->bindValue(":id", id);
	querySecAttr->bindValue(":topid", topid);
	querySecAttr->bindValue(":nid", nid);
	querySecAttr->bindValue(":srt", QString::number(no));
	querySecAttr->bindValue(":itm", tag);
	querySecAttr->bindValue(":val", val);
	if (querySecAttr->exec() == false) {
		QSqlError err = querySecAttr->lastError();
		mess = err.text();
		querySecAttr->clear();
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsDb::addFixAttr(const QString &topid, const QString &nid, int idx, const QList<QByteArray> &lstAttr) {
	if ( idx < 0 || prm->nTagCnt <= idx ) {
		return false;
	}
	clsTagAttrRec *recDef = prm->lstTag.at(idx);
	/*
	QString sql = recDef->mkInsSql(tblHead, topid, nid, lstAttr);
	if ( updExecSql(sql) == false ) {
		return false;
	}
	sql = "";
	*/
	QSqlQuery *query = arrQueryFixIns[idx];
	query->bindValue(":id",maxId(tblHead+"_d_sec_"+recDef->tag));
	query->bindValue(":topid",topid);
	query->bindValue(":nid,",nid);
	for( int i=0; i<recDef->arrTblCol.size(); i++ ) {
		query->bindValue(":"+recDef->arrTblCol.at(i),lstAttr.at(i));
	}
	if( query->exec() == false ) {
		mess = query->lastError().text();
		log->log(mess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsDb::delTop(const QString &whr) {
	if (whr == "") {
		return true;
	}
	QString sql = "DELETE FROM " + tblHead + "_d_topnode_attr WHERE topid IN ("
			+ whr + ")";
	if (updExecSql(sql) == false) {
		return false;
	}
	sql = "DELETE FROM " + tblHead + "_d_topnode WHERE id IN (" + whr + ")";
	if (updExecSql(sql) == false) {
		return false;
	}
	sql = "";
	return true;
}

bool clsDb::delSec(const QString &whr) {
	if (whr == "") {
		return true;
	}
	QString sql = "DELETE FROM " + tblHead + "_d_secnode_attr WHERE topid IN ("
			+ whr + ")";
	if (updExecSql(sql) == false) {
		return false;
	}
	sql = "DELETE FROM " + tblHead + "_d_secnode WHERE topid IN (" + whr + ")";
	if (updExecSql(sql) == false) {
		return false;
	}
	sql = "";
	return true;
}

int clsDb::getMaxSrt(const QString &tbl, QString topid) {
	QString sql = "SELECT MAX(srt) AS maxsrt FROM " + tblHead + "_" + tbl;
	if (tbl == "d_secnode_attr") {
		sql += " WHERE nid=" + topid;
	} else if (topid != "") {
		sql += " WHERE topid=" + topid;
	}
	QSqlQuery query(db);
	if (query.exec(sql) == false) {
		return 0;
	}
	query.next();
	int ret = query.value(0).toInt();
	query.clear();
	sql = "";
	return ret;
}

bool clsDb::mkInitTbl() {
	QString sql = "create table d_table (";
	sql += "id integer,";
	sql += "name varchar(50),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence("d_table") == false) {
		return false;
	}
	sql = "create table d_taglvl (";
	sql += "id integer,";
	sql += "tag varchar(50),";
	sql += "lvl integer,";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence("d_taglvl") == false) {
		return false;
	}

	return true;
}

bool clsDb::mkMasterTbl() {
	QString sql = "create table m_dbmst (";
	sql += "mstid varchar(10),";
	sql += "mac varchar(10),";
	sql += "startymd varchar(8),";
	sql += "dbfile varchar(100),";
	sql += "endymd varchar(8),";
	sql += "primary key(mstid,mac,startymd));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if ( createIndex("m_dbmst","mstid,mac,endymd","m_dbmst_idx1") == false ) {
		return false;
	}

	return true;
}

/*
bool clsDb::setDbFile(QString lid) {
	mkSqlQuery("SELECT * FROM m_dbfile ORDER BY id DESC");
	if ( openQuery() == false ) {
		log->log("error m_dbfile read:"+mess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	if ( next() == 1 ) {
		if (lid == "") {
			log->log("not db selected ["+lid+"]",clsLog::CLSLOG_DEBUG);
			return false;
		}
		if (addDbFile(lid) == false) {
			log->log("add db error ["+lid+"]",clsLog::CLSLOG_DEBUG);
			return false;
		}
		return true;
	} else {
		recDb.id = queryValue("id");
		recDb.dbnam = queryValue("dbname");
		recDb.startLid = queryValue("startLid");
		recDb.endLid = queryValue("lastLid");
		recDb.dbday = queryValue("dbday");
	}
	closeQuery();

	if (lid == "") {
		DisConnect();
		dbnam = recDb.dbnam;
		if (Connect(connDef+"_db") == false) {
			return false;
		}
		log->log("connected db:"+dbnam,clsLog::CLSLOG_DEBUG);
		return true;
	}
	//qDebug() << "rec=[" + recDb.endLid + "][" + recDb.dbday + "]";
	if (recDb.endLid != lid) {
		if (chkDbChg(lid) == false) {
			if (errflg == false) {
				return false;
			}
			DisConnect();
			dbnam = recDb.dbnam;
			if (Connect(connDef+"_db") == false) {
				return false;
			}
			return true;
		}
		if (addDbFile(lid) == false) {
			return false;
		}
	}

	DisConnect();
	dbnam = recDb.dbnam;
	if (Connect(connDef + "_db") == false) {
		return false;
	}
	return true;
}

bool clsDb::chkDbChg(const QString &lid) {
	if (recDb.endLid == "") {
		setLastLid(lid);
		return false;
	}
	clsParamDef *prm = clsParamDef::GetInstance();
	QDate day = QDate::fromString(recDb.dbday, "yyyy-MM-dd");
	QDate cday = day.addDays(prm->nChgDbDay);
	day = QDate::currentDate();
	qDebug() << "chk day [" + day.toString("yyyy-MM-dd") + "]?["
			+ cday.toString("yyyy-MM-dd") + "] [" + QString::number(
			prm->nChgDbDay) + "]";
	if (day <= cday) {
		setLastLid(lid);
		return false;
	}

	return true;
}

bool clsDb::setLastLid(const QString &lid) {
	errflg = true;
	QSqlQuery *query = mkSqlQuery("UPDATE m_dbfile SET lastlid=:lid WHERE id=:id");
	query->bindValue(":lid",lid);
	query->bindValue(":id",recDb.id);
	if ( query->exec() == false ) {
		errflg = false;
		mess = query->lastError().text();
		return false;
	}
	closeQuery();
	return true;
}

bool clsDb::addDbFile(const QString &lid) {
	QDate day = QDate::currentDate();
	clsParamDef *prm = clsParamDef::GetInstance();

	QString strDir = prm->dbFolder;
	QDir dir = QDir(strDir);
	if (dir.exists() == false) {
		mess = "Database Dir Not Found";
		return false;
	}
	strDir += "/" + day.toString("yyyy-MM");
	dir.setPath(strDir);
	if (dir.exists() == false) {
		dir.mkdir(strDir);
	}
	recDb.dbday = day.toString("yyyy-MM-dd").toLocal8Bit().data();
	recDb.dbnam = (strDir + "/xmldb-" + day.toString("dd") + ".fdb").toLocal8Bit().data();
	recDb.startLid = lid.toLocal8Bit().data();
	if (clsDb::createDb(dbusr, dbpwd, recDb.dbnam) == false) {
		mess = "Create DBFile Error";
		return false;
	}

	QSqlQuery *query = mkSqlQuery("INSERT INTO m_dbfile(dbname,startLid,dbday) VALUES (:dbn,:lid,:dbday)");
	query->bindValue(":dbn",recDb.dbnam);
	query->bindValue(":lid",recDb.startLid);
	query->bindValue(":dbday",recDb.dbday);
	if ( query->exec() == false ) {
		mess = "INSERT m_dbfile error:"+query->lastError().text();
		return false;
	}
	closeQuery();
	DisConnect();

	dbnam = recDb.dbnam;
	if (Connect(connDef+"_db") == false) {
		qDebug() << "Connect Error";
		return false;
	}
	if (mkInitTbl() == false) {
		qDebug() << "mkInitTbl Error";
		return false;
	}
	return true;
}
*/

bool clsDb::setTable(const QString &tbl) {
	tblHead = tbl;
	QSqlQuery *query = mkSqlQuery("SELECT * FROM d_table WHERE name=:name");
	if ( query == NULL ) {
		log->log("setTable:mkSqlQuery(SELECT d_table) Error:"+mess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	query->bindValue(":name",tblHead);
	if ( openQuery() == false ) {
		return false;
	}
	if ( next() == 0 ) {
		if (makePrepare() == false) {
			return false;
		}
		return true;
	}

	// テーブル作成
	QString sql = "create table " + tblHead + "_d_topnode ( ";
	sql += "id integer,";
	sql += "tag varchar(20),";
	sql += "srt integer,";
	sql += "val varchar(256),";
	sql += "depth integer,";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_topnode") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_topnode", "tag,val", tblHead
			+ "_topnode_idx1") == false) {
		return false;
	}
	sql = "create table " + tblHead + "_d_topnode_attr (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "srt integer,";
	sql += "itm varchar(20),";
	sql += "val varchar(256),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_topnode_attr") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_topnode_attr", "itm,val", tblHead
			+ "_topnode_attr_idx1") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_topnode_attr", "topid", tblHead
			+ "_topnode_attr_idx2") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_topnode_attr", "srt", tblHead
			+ "_topnode_attr_idx3") == false) {
		return false;
	}

	sql = "create table " + tblHead + "_d_secnode (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "srt integer,";
	sql += "tag varchar(20),";
	sql += "val varchar(256),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_secnode") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode", "tag,val", tblHead
			+ "_secnode_idx1") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode", "topid", tblHead + "_secnode_idx2")
			== false) {
		return false;
	}

	sql = "create table " + tblHead + "_d_secnode_attr (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "nid integer,";
	sql += "srt integer,";
	sql += "itm varchar(20),";
	sql += "val varchar(256),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_secnode_attr") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode_attr", "itm,val", tblHead
			+ "_secnode_attr_idx1") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode_attr", "topid", tblHead
			+ "_secnode_attr_idx2") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode_attr", "nid", tblHead
			+ "_secnode_attr_idx3") == false) {
		return false;
	}
	if (createIndex(tblHead + "_d_secnode_attr", "srt", tblHead
			+ "_secnode_attr_idx4") == false) {
		return false;
	}

	sql = "create table " + tblHead + "_d_childnode (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "srt integer,";
	sql += "tag varchar(20),";
	sql += "val varchar(256),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_childnode") == false) {
		return false;
	}

	sql = "create table " + tblHead + "_d_childnode_attr (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "nid integer,";
	sql += "srt integer,";
	sql += "itm varchar(20),";
	sql += "val varchar(256),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_childnode_attr") == false) {
		return false;
	}

	for (int i = 0; i < prm->nTagCnt; i++) {
		clsTagAttrRec *recDet = prm->lstTag.at(i);
		if (recDet == NULL)
			continue;
		QString tbl = tblHead + "_d_sec_" + recDet->tag;
		sql = "create table " + tbl + " (";
		sql += "id integer,";
		sql += "topid integer,";
		sql += "nid integer,";
		for (int j = 0; j < recDet->arrTblCol.size(); j++) {
			sql += recDet->arrTblCol.at(j) + " varchar(50),";
		}
		sql += "primary key(id));";
		if (updExecSql(sql) == false) {
			return false;
		}
		if (createSequence(tbl) == false) {
			return false;
		}
		if (createIndex(tbl, "topid", tbl + "_idx2") == false) {
			return false;
		}
		if (createIndex(tbl, "nid", tbl + "_idx3") == false) {
			return false;
		}
	}
	if ( createView(tblHead) == false ) {
		return false;
	}

	sql = "INSERT INTO d_table(name) values ('" + tblHead + "')";
	qDebug() << "******** "+sql;
	if (updExecSql(sql) == false) {
		return false;
	}
	if (makePrepare() == false) {
		return false;
	}

	return true;
}

bool clsDb::createIndex(QString tbl, QString col, QString nam) {
	QString sql = "CREATE INDEX " + nam + " ON " + tbl + " " + col;
	qDebug() << "create index " + sql;
	if (updExecSql(sql) == false) {
		return false;
	}
	return true;
}

bool clsDb::createSequence(const QString &name) {
	QString sql = "create generator " + name + "_id_seq;";
	if (updExecSql(sql) == false) {
		return false;
	}
	//sql = "SET TERM ^ ;";
	sql = "";
	sql += "CREATE TRIGGER TRG_" + name + "_ID FOR " + name + " ACTIVE ";
	sql += "BEFORE INSERT POSITION 0 as ";
	sql += "begin ";
	sql += "   if (NEW.ID IS null) then NEW.ID = next value for " + name
			+ "_id_seq;";
	sql += "END; ";
	//sql += "SET TERM ; ^";
	if (updExecSql(sql) == false) {
		return false;
	}

	return true;
}

bool clsDb::setTag(const QString &tag, int lvl) {
	if (lvl == 1 && nTagTop == -1) {
		if (mkTagTopLst() == false) {
			return false;
		}
	}
	if (lvl == 2 && nTagSec == -1) {
		if (mkTagSecLst() == false) {
			return false;
		}
	}

	QStringList *lst = NULL;
	int cnt = 0;
	switch (lvl) {
	case 1:
		lst = &lstTagTop;
		cnt = nTagTop;
		break;
	case 2:
		lst = &lstTagSec;
		cnt = nTagSec;
		break;
	}
	if (lst == NULL) {
		mess = "lvl error:" + QString::number(lvl);
		return false;
	}

	qDebug() << "taglstcnt=[" + QString::number(cnt) + "]";
	for (int i = 0; i < cnt; i++) {
		qDebug() << "tag=[" + tag + "]?[" + lst->at(i) + "]";
		if (tag == lst->at(i)) {
			return true;
		}
	}
	lst->append(tag);
	QString sql = "INSERT INTO d_taglvl(tag,lvl) VALUES ('" + tag + "',"
			+ QString::number(lvl) + ")";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (lvl == 1) {
		nTagTop = lst->size();
	} else {
		nTagSec = lst->size();
	}
	return true;
}

bool clsDb::createView(QString tbl) {
	QString sql = "CREATE VIEW v_"+tbl+"_toplideid AS ";
	sql += "SELECT top.id AS topid, sel0.val AS lid, sel1.val as eid ";
	sql += "FROM "+tbl+"_d_topnode top,";
	sql += "(SELECT topid,val FROM "+tbl+"_d_secnode_attr WHERE itm='LID' ";
	sql += "  AND nid IN (SELECT id FROM "+tbl+"_d_secnode WHERE tag='LOT')) sel0 , ";
	sql += "(SELECT topid,val FROM "+tbl+"_d_secnode_attr WHERE itm='EID' ";
	sql += "  AND nid IN (SELECT id FROM "+tbl+"_d_secnode WHERE tag='INSPECT')) sel1  ";
	sql += "WHERE top.id=sel0.topid AND top.id=sel1.topid;";
	if (updExecSql(sql) == false) {
		return false;
	}
	return true;
}

bool clsDb::mkTagTopLst() {
	QString sql = "SELECT tag FROM d_taglvl WHERE lvl=1";
	return setTagLst(sql, lstTagTop, nTagTop);
}

bool clsDb::mkTagSecLst() {
	QString sql = "SELECT tag FROM d_taglvl WHERE lvl=2";
	return setTagLst(sql, lstTagSec, nTagSec);
}

bool clsDb::setTagLst(const QString &sql, QStringList &lst, int &nTag) {
	QSqlQueryModel *mdl = mkQueryModel(sql);
	if (errflg == false) {
		return false;
	}
	nTag = 0;
	for (int i = 0; i < mdl->rowCount(); i++) {
		QSqlRecord rec = mdl->record(i);
		lst << rec.value(0).toString();
		nTag++;
	}
	qDebug() << "tagcnt=[" + QString::number(nTag) + "]";
	mdl->clear();
	delete(mdl);
	return true;
}

int clsDb::tagLvl(const QString &tag) {
	if (nTagTop < 0) {
		if (mkTagTopLst() == false) {
			qDebug() << "error mkTagTopLst";
			return -1;
		}
	}
	for (int i = 0; i < nTagTop; i++) {
		qDebug() << "tag=[" + tag + "]?[" + lstTagTop.at(i) + "]";
		if (tag == lstTagTop.at(i)) {
			return 1;
		}
	}
	if (nTagSec < 0) {
		if (mkTagSecLst() == false) {
			qDebug() << "error mkTagSecLst";
			return -1;
		}
	}
	for (int i = 0; i < nTagSec; i++) {
		qDebug() << "tag=[" + tag + "]?[" + lstTagSec.at(i) + "]";
		if (tag == lstTagSec.at(i)) {
			return 2;
		}
	}
	return 0;
}

clsTagAttrRec *clsDb::getTagDef(QString tag) {
	for (int i = 0; i < prm->nTagCnt; i++) {
		if (prm->lstTag.at(i)->tag == tag) {
			return prm->lstTag.at(i);
		}
	}
	return NULL;
}

#include "clsDb.h"

#include <QStringList>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>

clsDb::clsDb(QObject *parent) :
	QObject(parent) {
	mess = "";
	lstTagTop.clear();
	lstTagSec.clear();
	nTagTop = -1;
	nTagSec = -1;
	queryTop = NULL;
	queryTopAttr = NULL;
	querySec = NULL;
	querySecAttr = NULL;
}

clsDb::~clsDb() {

}

void clsDb::setPrm() {
	//TODO
	//setPrm("QPSQL","localhost","xmldb","cony","C_Section");
	setPrm("QIBASE", "localhost", "D:\\Data\\xmldb.fdb", "sysdba",
			"masterkey");
}

void clsDb::setPrm(QString _dbtyp, QString _dbhost, QString _dbnam,
		QString _dbusr, QString _dbpwd) {
	dbtype = _dbtyp;
	dbhost = _dbhost;
	dbnam = _dbnam;
	dbusr = _dbusr;
	dbpwd = _dbpwd;
}

void clsDb::setPrm(QString _dbnam) {
	setPrm();
	dbnam = _dbnam;
}

bool clsDb::initDb() {
	return true;
}

bool clsDb::Connect() {
	db = QSqlDatabase::addDatabase(dbtype);
	QStringList lst = db.drivers();
	QString sDbDrv = "";
	for (int i = 0; i < lst.size(); i++) {
		sDbDrv = lst.at(i) + ",";
	}
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
	if (!db.open()) {
		QSqlError err = db.lastError();
		mess = err.text() + "[" + dbtype + ":" + dbnam + ":" + dbhost + ":"
				+ dbusr + ":" + dbpwd + "]";
		return false;
	}
	return true;
}

bool clsDb::DisConnect() {
	db.close();
	return true;
}

bool clsDb::updExecSql(QString sql) {
	mess = "";
	qDebug() << "update SQL " + sql;
	QSqlQuery query(db);
	//log->log(sql, clsLog::CLSLOG_DEBUG);
	if (query.exec(sql) == false) {
		QSqlError err = query.lastError();
		mess = err.text();
		query.clear();
		log->log(sql, clsLog::CLSLOG_DEBUG);
		log->log(mess, clsLog::CLSLOG_DEBUG);
		return false;
	}
	query.clear();
	return true;
}

QString clsDb::maxId(QString tbl) {
	mess = "";
	//TODO
	QSqlQuery query(db);
	/*
	 if ( query.exec("SELECT max(id) FROM "+tbl) == false ) {
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

QSqlQueryModel *clsDb::mkQueryModel(QString sql) {
	mess = "";
	errflg = true;
	QSqlQueryModel *model = new QSqlQueryModel(this);
	model->setQuery(sql, db);
	qDebug() << sql;
	if (model->lastError().isValid()) {
		errflg = false;
		mess = model->lastError().text();
	}
	return model;
}

int clsDb::readRec(QString sql) {
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
	queryTop = new QSqlQuery(db);
	queryTopAttr = new QSqlQuery(db);
	querySec = new QSqlQuery(db);
	querySecAttr = new QSqlQuery(db);

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
	return true;
}
bool clsDb::addTopNode(int no, QString tag, QString &parid) {
	if (setTag(tag, 1) == false) {
		return false;
	}
	if (no == -1) {
		no = getMaxSrt("d_topnode", "");
	}
	parid = maxId(tblHead + "_d_topnode");
	//QString sql = "INSERT INTO "+tblHead+"_d_topnode(id,tag,srt) VALUES ("+parid+",'"+tag+"',"+QString::number(no)+")";
	//return updExecSql(sql);
	/*
	 QSqlQuery query;
	 if ( query.prepare("INSERT INTO "+tblHead+"_d_topnode(id,tag,srt) VALUES (:id,:tag,:srt)") == false ) {
	 QSqlError err = query.lastError();
	 mess = err.text();
	 query.clear();
	 log->log(mess,clsLog::CLSLOG_DEBUG);
	 return false;
	 }
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

bool clsDb::addTopAttr(int no, QString topid, QString tag, QString val) {
	if (no == -1) {
		no = getMaxSrt("d_topnode_attr", topid);
	}
	//QString sql = "INSERT INTO "+tblHead+"_d_topnode_attr(topid,srt,itm,val) VALUES ("+topid+","+QString::number(no)+",'"+tag+"','"+val+"')";
	//return updExecSql(sql);
	QString id = maxId(tblHead + "_d_topnode_attr");
	/*
	 QSqlQuery query;
	 if ( query.prepare("INSERT INTO "+tblHead+"_d_topnode_attr(id,topid,srt,itm,val) VALUES (:id,:topid,:srt,:itm,:val)") == false ) {
	 QSqlError err = query.lastError();
	 mess = err.text();
	 query.clear();
	 log->log(mess,clsLog::CLSLOG_DEBUG);
	 return false;
	 }
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

bool clsDb::addSecNode(int no, QString topid, QString tag, QString val,
		QString &parid) {
	if (setTag(tag, 2) == false) {
		return false;
	}
	if (no == -1) {
		no = getMaxSrt("d_secnode", topid);
	}
	parid = maxId(tblHead + "_d_secnode");
	//QString sql = "INSERT INTO "+tblHead+"_d_secnode(id,topid,tag,val,srt) VALUES ("+parid+","+topid+",'"+tag+"','"+val+"',"+QString::number(no)+")";
	//return updExecSql(sql);
	/*
	 QSqlQuery query;
	 if ( query.prepare("INSERT INTO "+tblHead+"_d_secnode(id,topid,srt,tag,val) VALUES (:id,:topid,:srt,:tag,:val)") == false ) {
	 QSqlError err = query.lastError();
	 mess = err.text();
	 query.clear();
	 log->log(mess,clsLog::CLSLOG_DEBUG);
	 return false;
	 }
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

bool clsDb::addSecAttr(int no, QString topid, QString nid, QString tag,
		QString val) {
	if (no == -1) {
		no = getMaxSrt("d_secnode_attr", nid);
	}
	QString id = maxId(tblHead + "_d_secnode_attr");
	//QString sql = "INSERT INTO "+tblHead+"_d_secnode_attr(topid,nid,srt,itm,val) VALUES ("+topid+","+nid+","+QString::number(no)+",'"+tag+"','"+val+"')";
	//return updExecSql(sql);
	/*
	 QSqlQuery query;
	 if ( query.prepare("INSERT INTO "+tblHead+"_d_secnode_attr(id,topid,nid,srt,itm,val) VALUES (:id,:topid,:nid,:srt,:itm,:val)") == false ) {
	 QSqlError err = query.lastError();
	 mess = err.text();
	 query.clear();
	 log->log(mess,clsLog::CLSLOG_DEBUG);
	 return false;
	 }
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

bool clsDb::addNgpAttr(QString topid, QString nid, QStringList lstAttr) {
	QString sql = "INSERT INTO "+tblHead+"_d_sec_ngp(topid,nid,X,Y,MX,MY,HX,HY,RS1,RS2,RAL,PG,LY) VALUES (";
	sql += topid+","+nid;
	for( int i=0; i<lstAttr.size(); i++ ) {
		sql += ",'"+lstAttr.at(i)+"'";
	}
	sql += ")";
	if ( updExecSql(sql) == false ) {
		return false;
	}
	return true;
}

bool clsDb::addNgiAttr(QString topid, QString nid, QStringList lstAttr) {
	QString sql = "INSERT INTO "+tblHead+"_d_sec_ngi(topid,nid,X,Y,W,H,HX,HY,IDX,IDX2) VALUES (";
	sql += topid+","+nid;
	for( int i=0; i<lstAttr.size(); i++ ) {
		sql += ",'"+lstAttr.at(i)+"'";
	}
	sql += ")";
	if ( updExecSql(sql) == false ) {
		return false;
	}
	return true;
}

bool clsDb::delTop(QString whr) {
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
	return true;
}

bool clsDb::delSec(QString whr) {
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
	return true;
}

int clsDb::getMaxSrt(QString tbl, QString topid) {
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
	return ret;
}

bool clsDb::setTable(QString tbl) {
	tblHead = tbl;
	QString sql = "SELECT * FROM d_table WHERE name='" + tbl + "'";
	int ret = readRec(sql);
	if (ret < 0) {
		return false;
	}
	if (ret == 0) {
		return true;
	}

	// テーブル作成
	sql = "create table " + tblHead + "_d_topnode ( ";
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

	sql = "create table " + tblHead + "_d_sec_ngp (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "nid integer,";
	sql += "X varchar(10),";
	sql += "Y varchar(10),";
	sql += "MX varchar(10),";
	sql += "MY varchar(10),";
	sql += "HX varchar(10),";
	sql += "HY varchar(10),";
	sql += "RS1 varchar(10),";
	sql += "RS2 varchar(10),";
	sql += "RAL varchar(100),";
	sql += "PG varchar(10),";
	sql += "LY varchar(10),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_sec_ngp") == false) {
		return false;
	}

	sql = "create table " + tblHead + "_d_sec_ngi (";
	sql += "id integer,";
	sql += "topid integer,";
	sql += "nid integer,";
	sql += "X varchar(10),";
	sql += "Y varchar(10),";
	sql += "W varchar(10),";
	sql += "H varchar(10),";
	sql += "HX varchar(10),";
	sql += "HY varchar(10),";
	sql += "IDX varchar(10),";
	sql += "IDX2 varchar(10),";
	sql += "primary key(id));";
	if (updExecSql(sql) == false) {
		return false;
	}
	if (createSequence(tblHead + "_d_sec_ngi") == false) {
		return false;
	}

	sql = "INSERT INTO d_table(name) values ('" + tblHead + "')";
	if (updExecSql(sql) == false) {
		return false;
	}

	// TODO インデックス生成

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

bool clsDb::createSequence(QString name) {
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

bool clsDb::setTag(QString tag, int lvl) {
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

bool clsDb::mkTagTopLst() {
	QString sql = "SELECT tag FROM d_taglvl WHERE lvl=1";
	return setTagLst(sql, lstTagTop, nTagTop);
}

bool clsDb::mkTagSecLst() {
	QString sql = "SELECT tag FROM d_taglvl WHERE lvl=2";
	return setTagLst(sql, lstTagSec, nTagSec);
}

bool clsDb::setTagLst(QString sql, QStringList &lst, int &nTag) {
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
	return true;
}

int clsDb::tagLvl(QString tag) {
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

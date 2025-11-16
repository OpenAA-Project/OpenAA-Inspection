/*
 * clsXmlReadSql.cpp
 *
 *  Created on: 2009/12/09
 *      Author: cony
 */

#include "clsXmlReadSql.h"

#include <QDebug>

clsXmlReadSql::clsXmlReadSql(clsDb *_db, QString sql, bool uflg) {
	db = _db;
	outWhr = NULL;
	selWhr = NULL;
	odrWhr = NULL;
	err = true;

	if ( uflg == false ) {
		lexSql(sql);
	} else {
		lexUpdSql(sql);
	}
}

clsXmlReadSql::~clsXmlReadSql() {
}

void clsXmlReadSql::lexUpdSql(QString sql) {
	sql = sql.replace(" from "," FROM ");
	sql = sql.replace(" where "," WHERE ");
	sql = sql.replace(" order by "," ORDER BY ");

	if ( sql.mid(0,4) == "FROM" ) {
		sql = " "+sql;
	} else {
		insXml = getOutWhr(sql);
		if ( insXml == "" ) {
			err = false;
			return;
		}
	}

	tbl = getTable(sql);
	if ( tbl == "" ) {
		err = false;
		return;
	}

	QString tmp = getWhere(sql);
	if ( tmp != "" ) {
		selWhr = new clsXmlWhereLex(tmp);
		selWhr->setTable(tbl);
	}
}

void clsXmlReadSql::lexSql(QString sql) {
	sql = sql.replace(" from "," FROM ");
	sql = sql.replace(" where "," WHERE ");
	sql = sql.replace(" order by "," ORDER BY ");
	QString tmp = getOutWhr(sql);
	if ( tmp == "" ) {
		err = false;
		return;
	}
	outWhr = new clsXmlOutLex(tmp);

	tbl = getTable(sql);
	if ( tbl == "" ) {
		err = false;
		return;
	}

	tmp = getWhere(sql);
	if ( tmp != "" ) {
		selWhr = new clsXmlWhereLex(tmp);
		selWhr->setTable(tbl);
	}

	tmp = getOrder(sql);
	if ( tmp != "" ) {
		odrWhr = new clsXmlOrderLex(tmp);
		odrWhr->setTable(tbl);
		odrWhr->setDb(db);
	}
	qDebug() << debugStr();
}

QString clsXmlReadSql::getOutWhr(QString sql) {
	int n = sql.indexOf(" FROM ");
	if ( n < 0 ) return "";
	QString tmp = sql.mid(0,n);
	return tmp.trimmed();
}

QString clsXmlReadSql::getTable(QString sql) {
	int ns = sql.indexOf(" FROM ");
	ns += 6;
	QString tmp = "";
	int ne = sql.indexOf(" WHERE ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		return tmp.trimmed();
	}
	ne = sql.indexOf(" ORDER ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		return tmp.trimmed();
	}
	tmp = sql.mid(ns);
	return tmp.trimmed();
}

QString clsXmlReadSql::getWhere(QString sql) {
	int ns = sql.indexOf(" WHERE ");
	if ( ns < 0 ) {
		return "";
	}
	ns += 7;
	QString tmp = "";

	int ne = sql.indexOf(" ORDER ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		return tmp.trimmed();
	}
	tmp = sql.mid(ns);
	return tmp.trimmed();
}

QString clsXmlReadSql::getOrder(QString sql) {
	int ns = sql.indexOf(" ORDER ");
	if ( ns < 0 ) {
		return "";
	}
	ns += 10;
	QString tmp = sql.mid(ns);
	return tmp.trimmed();
}

QString clsXmlReadSql::debugStr() {
	QString buf = "";
	if ( outWhr != NULL ) {
		buf += "output format\n";
		buf += outWhr->mkWhr();
	} else {
		buf += "update format\n";
		buf += insXml;
	}
	if ( buf != "" ) buf += "\n";
	buf += "table:"+tbl+"\n";
	if ( selWhr != NULL ) {
		buf += "Search format\n";
		buf += selWhr->mkWhr();
	}
	if ( buf != "" ) buf += "\n";
	if ( odrWhr != NULL ) {
		buf += "Order format\n";
		buf += odrWhr->debugPrt();
		buf += "\n"+odrWhr->mkOrderSql("ppp",1);
	}

	return buf;
}

/*
 * clsXmlReadSql.cpp
 *
 *  Created on: 2009/12/09
 *      Author: cony
 */

#include "clsXmlReadSql.h"

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

clsXmlReadSql::clsXmlReadSql(clsDb *_db, const QByteArray &sql, bool uflg) {
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
	if ( selWhr != NULL ) {
		delete(selWhr);
	}
	if ( outWhr != NULL ) {
		delete(outWhr);
	}
	if ( odrWhr != NULL ) {
		delete(odrWhr);
	}
	insXml.clear();
	tbl.clear();
}

void clsXmlReadSql::lexUpdSql(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	sql = sql.replace(" from "," FROM ");
	sql = sql.replace(" where "," WHERE ");
	sql = sql.replace(" order by "," ORDER BY ");

	if ( sql.mid(0,4) == "FROM" ) {
		sql = " "+sql;
	} else {
		insXml = getOutWhr(sql);
		if ( insXml == "" ) {
			err = false;
			sql.clear();
			return;
		}
	}

	tbl = getTable(sql);
	if ( tbl == "" ) {
		err = false;
		sql.clear();
		return;
	}

	QByteArray tmp = getWhere(sql);
	if ( tmp != "" ) {
		selWhr = new clsXmlWhereLex(tmp);
		selWhr->setTable(tbl);
	}
	sql.clear();
	tmp.clear();
}

void clsXmlReadSql::lexSql(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	sql = sql.replace(" from "," FROM ");
	sql = sql.replace(" where "," WHERE ");
	sql = sql.replace(" order by "," ORDER BY ");
	QByteArray tmp = getOutWhr(sql);
	if ( tmp == "" ) {
		err = false;
		sql.clear();
		tmp.clear();
		return;
	}
	outWhr = new clsXmlOutLex(tmp);

	tbl = getTable(sql);
	if ( tbl == "" ) {
		err = false;
		sql.clear();
		tmp.clear();
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
	tmp.clear();
	sql.clear();
}

QByteArray clsXmlReadSql::getOutWhr(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	int n = sql.indexOf(" FROM ");
	if ( n < 0 ) return "";
	QByteArray tmp = sql.mid(0,n);
	sql.clear();
	return tmp.trimmed();
}

QByteArray clsXmlReadSql::getTable(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	int ns = sql.indexOf(" FROM ");
	ns += 6;
	QByteArray tmp = "";
	int ne = sql.indexOf(" WHERE ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		sql.clear();
		return tmp.trimmed();
	}
	ne = sql.indexOf(" ORDER ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		sql.clear();
		return tmp.trimmed();
	}
	tmp = sql.mid(ns);
	sql.clear();
	return tmp.trimmed();
}

QByteArray clsXmlReadSql::getWhere(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	int ns = sql.indexOf(" WHERE ");
	if ( ns < 0 ) {
		return "";
	}
	ns += 7;
	QByteArray tmp = "";

	int ne = sql.indexOf(" ORDER ");
	if ( ne > 0 ) {
		tmp = sql.mid(ns,(ne-ns));
		sql.clear();
		return tmp.trimmed();
	}
	tmp = sql.mid(ns);
	sql.clear();
	return tmp.trimmed();
}

QByteArray clsXmlReadSql::getOrder(const QByteArray &srcsql) {
	QByteArray sql = srcsql;
	int ns = sql.indexOf(" ORDER ");
	if ( ns < 0 ) {
		sql.clear();
		return "";
	}
	ns += 10;
	QByteArray tmp = sql.mid(ns);
	sql.clear();
	return tmp.trimmed();
}

QByteArray clsXmlReadSql::debugStr() {
	QByteArray buf = "";
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

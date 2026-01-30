/*
 * Copyright (C) 2012
 * Author : cony
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


#include "clsXmlWhereLex.h"

#include <QDebug>

clsXmlOrderLex::clsXmlOrderLex(QString _buf) : clsXmlLexBase(_buf) {
	whrrec.order = NULL;
	mkXMLRec();
}

clsXmlOrderLex::~clsXmlOrderLex() {
	// TODO Auto-generated destructor stub
}

void clsXmlOrderLex::mkXMLRec() {
	if ( srcBuf == "" ) return;
	whrrec.order = new NPListPack<clsXMLOrderRec>();
	QStringList lst = srcBuf.split(",");
	for( int i=0; i<lst.size(); i++ ) {
		QString tmp = lst.at(i).trimmed();
		QStringList lst1 = tmp.split(" ");
		clsXMLOrderRec *rec = new clsXMLOrderRec();
		if ( lst1.size() > 1 ) {
			rec->odr = lst1.at(1);
		} else {
			rec->odr = "ASC";
		}
		if ( lst1.at(0).indexOf("/") > 0 ) {
			QStringList lst2 = lst1.at(0).split("/");
			rec->tag = lst2.at(0);
			rec->attr = lst2.at(1);
		} else {
			rec->tag = lst1.at(0);
		}
		whrrec.order->AppendList(rec);
	}
}

QString clsXmlOrderLex::mkOrderSql(QString wsql, int nSelTblCnt) {
	QString sql = "";
	QString odr = "";
	QString wwhr = "";
	if ( tbl == "" ) {
		errMess = "not table set";
		return "";
	}
	if ( whrrec.order == NULL ) {
		errMess = "not order defined";
		return "";
	}
	clsXMLOrderRec *rec = whrrec.order->GetFirst();
	while( rec != NULL ) {
		sql  = addTagTbl(sql,rec);
		wwhr = addWhrTbl(wwhr,rec);
		odr  = addOdrTbl(odr,rec);
		rec = rec->GetNext();
	}
	if ( sql == "" ) {
		errMess = "not order defined";
		return "";
	}
	QString retsql = "SELECT top.id AS topid FROM "+tbl+"_d_topnode top" + sql + ","+wsql;
	retsql += " WHERE "+wwhr;
	for( int i=0; i<nSelTblCnt; i++ ) {
		retsql += " AND top.id = sel"+QString::number(i)+".topid";
	}
	retsql += " ORDER BY "+odr;
	return retsql;
}

QString clsXmlOrderLex::addTagTbl(QString sql, clsXMLOrderRec *rec) {
	QString tnam = bndTblNam(rec);
	int lvl = db->tagLvl(rec->tag);
	QString tblsub = "secnode";
	if ( lvl == 1 ) {
		tblsub = "topnode";
	}
	if ( rec->attr == "" ) {
		sql += ",(SELECT tag,val,topid FROM "+tbl+"_d_"+tblsub+" WHERE tag='"+rec->tag+"') "+tnam;
	} else {
		sql += ",(SELECT itm AS tag,val,topid FROM "+tbl+"_d_"+tblsub+"_attr WHERE itm='"+rec->attr+"') "+tnam;
	}
	return sql;
}

QString clsXmlOrderLex::addWhrTbl(QString whr, clsXMLOrderRec *rec) {
	QString tnam = bndTblNam(rec);
	if ( whr != "" ) whr += " AND ";
	whr += "top.id="+tnam+".topid";
	return whr;
}

QString clsXmlOrderLex::addOdrTbl(QString odr, clsXMLOrderRec *rec) {
	QString tnam = bndTblNam(rec);
	if ( odr != "" ) odr += ",";
	odr += tnam+".val "+rec->odr;
	return odr;
}

QString clsXmlOrderLex::bndTblNam(clsXMLOrderRec *rec) {
	QString tblnam = rec->tag;
	if ( rec->attr != "" ) {
		tblnam += "_"+rec->attr;
	}
	return tblnam;
}

QString clsXmlOrderLex::debugPrt() {
	QString buf = "";
	if ( whrrec.order == NULL ) {
		buf = "order not defined";
		qDebug() << buf;
		return buf;
	}
	clsXMLOrderRec *rec = whrrec.order->GetFirst();
	while( rec != NULL ) {
		if ( buf != "" ) buf +"\n";
		buf += "tag=["+rec->tag+"]/attr=["+rec->attr+"] ["+rec->odr+"]\n";
		rec = rec->GetNext();
	}
	qDebug() << buf;
	return buf;
}
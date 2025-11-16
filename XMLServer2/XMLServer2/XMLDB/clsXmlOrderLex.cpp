/*
 * clsXmlOrderLex.cpp
 *
 *  Created on: 2009/12/10
 *      Author: cony
 */

#include "clsXmlWhereLex.h"

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

clsXmlOrderLex::clsXmlOrderLex(const QByteArray &_buf) : clsXmlLexBase(_buf) {
	whrrec.order = NULL;
	mkXMLRec();
}

clsXmlOrderLex::~clsXmlOrderLex() {
	if ( whrrec.order != NULL ) {
		delete(whrrec.order);
	}
}

void clsXmlOrderLex::mkXMLRec() {
	if ( srcBuf == "" ) return;
	whrrec.order = new NPListPack<clsXMLOrderRec>();
	QList<QByteArray> lst;
	bndSplit(",",srcBuf,lst);
	for( int i=0; i<lst.size(); i++ ) {
		QByteArray tmp = lst.at(i).trimmed();
		QList<QByteArray> lst1;
		bndSplit(" ",tmp,lst1);
		clsXMLOrderRec *rec = new clsXMLOrderRec();
		if ( lst1.size() > 1 ) {
			rec->odr = lst1.at(1);
		} else {
			rec->odr = "ASC";
		}
		if ( lst1.at(0).indexOf("/") > 0 ) {
			QList<QByteArray> lst2;
			bndSplit("/",lst1.at(0),lst2);
			rec->tag = lst2.at(0);
			rec->attr = lst2.at(1);
		} else {
			rec->tag = lst1.at(0);
		}
		whrrec.order->AppendList(rec);
	}
}

QByteArray clsXmlOrderLex::mkOrderSql(const QByteArray &wsql, int nSelTblCnt) {
	QByteArray sql = "";
	QByteArray odr = "";
	QByteArray wwhr = "";
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
	QByteArray retsql = "SELECT top.id AS topid FROM "+tbl+"_d_topnode top" + sql + ","+wsql;
	retsql += " WHERE "+wwhr;
	for( int i=0; i<nSelTblCnt; i++ ) {
		retsql += " AND top.id = sel"+QString::number(i)+".topid";
	}
	retsql += " ORDER BY "+odr;
	return retsql;
}

QByteArray clsXmlOrderLex::addTagTbl(const QByteArray &srcsql, clsXMLOrderRec *rec) {
	QByteArray sql = srcsql;
	QByteArray tnam = bndTblNam(rec);
	int lvl = db->tagLvl(rec->tag);
	QByteArray tblsub = "secnode";
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

QByteArray clsXmlOrderLex::addWhrTbl(const QByteArray &srcwhr, clsXMLOrderRec *rec) {
	QByteArray tnam = bndTblNam(rec);
	QByteArray whr = srcwhr;
	if ( whr != "" ) whr += " AND ";
	whr += "top.id="+tnam+".topid";
	return whr;
}

QByteArray clsXmlOrderLex::addOdrTbl(const QByteArray &srcodr, clsXMLOrderRec *rec) {
	QByteArray tnam = bndTblNam(rec);
	QByteArray odr = srcodr;
	if ( odr != "" ) odr += ",";
	odr += tnam+".val "+rec->odr;
	return odr;
}

QByteArray clsXmlOrderLex::bndTblNam(clsXMLOrderRec *rec) {
	QByteArray tblnam = rec->tag;
	if ( rec->attr != "" ) {
		tblnam += "_"+rec->attr;
	}
	return tblnam;
}

QByteArray clsXmlOrderLex::debugPrt() {
	QByteArray buf = "";
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

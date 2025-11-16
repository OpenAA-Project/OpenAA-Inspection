/*
 * clsXmlUpd.cpp
 *
 *  Created on: 2009/11/20
 *      Author: cony
 */

#include "clsXmlUpd.h"

#include <QDebug>

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
	if ( doc != NULL ) {
		delete(doc);
		doc = NULL;
	}
}

void clsXmlUpd::clearSql() {
	if ( readSql != NULL ) {
		delete(readSql);
		readSql = NULL;
	}
	nResCnt = 0;
	lstResult.clear();
}

bool clsXmlUpd::lexSelSql(QString sql) {
	qDebug() << "SQL=["+sql+"]";
	if ( readSql != NULL ) {
		clearSql();
	}
	readSql = new clsXmlReadSql(db,sql);
	if ( readSql->err == false ) {
		//TODO log
		return false;
	}
	qDebug() << "table=["+readSql->tbl+"]";
	return true;
}

bool clsXmlUpd::lexUpdSql(QString sql) {
	if ( readSql != NULL ) {
		clearSql();
	}
	readSql = new clsXmlReadSql(db,sql,true);
	if ( readSql->err == false ) {
		//TODO log
		return false;
	}
	qDebug() << "tbl=["+readSql->tbl+"]";
	return true;
}
bool clsXmlUpd::parse(QString buf) {
	QString errStr;
	int errLine;
	int errColumn;

	errMess = "";
	doc = new QDomDocument();
	if ( !doc->setContent(buf,true,&errStr,&errLine,&errColumn) ) {
		errMess = "errLine:"+QString::number(errLine)+",errColumn:"+QString::number(errColumn)+","+errStr;
		qDebug() << errMess;
		delete(doc);
		doc = NULL;
		return false;
	}
	return true;
}

bool clsXmlUpd::addXml() {
	if ( readSql == NULL ) {
		return false;
	}
	if ( parse(readSql->insXml) == false ) {
		return false;
	}
	if ( doc == NULL ) {
		return false;
	}

	if ( db->setTable(readSql->tbl) == false ) {
		errMess = "setTable:"+db->mess;
		return false;
	}
	QDomElement root = doc->documentElement();
	qDebug() << "root Tag="+root.tagName();
	if ( db->addTopNode(-1,root.tagName(),topid) == false ) {
		qDebug() << "addTopNode Error:"+db->mess;
		return false;
	}
	if ( addAttr(root.attributes(),0) == false ) {
		qDebug() << "addAttr Error";
		return false;
	}
	QDomNode node = root.firstChild();
	int srt = 1;
	while( node.isNull() == false ) {
		addChildNode(srt,node);
		node = node.nextSibling();
		srt ++;
	}
	return true;
}

bool clsXmlUpd::addAttr(QDomNamedNodeMap lst, int lvl) {
	int srt = 0;
	if ( lvl == 0 ) {
		srt = db->getMaxSrt("d_topnode_attr",topid);
	} else if ( lvl == 1 ) {
		srt = db->getMaxSrt("d_secnode_attr",chldid);
	}
	srt ++;
	for( int i=0; i<lst.count(); i++ ) {
		QDomNode attr = lst.item(i);
		qDebug() << "  "+attr.nodeName()+"="+attr.nodeValue();
		if ( lvl == 0 ) {
			if ( db->addTopAttr(srt,topid,attr.nodeName(),attr.nodeValue()) == false ) {
				qDebug() << "addTopAttr Error:"+db->mess;
				return false;
			}
		} else if ( lvl == 1 ){
			if ( db->addSecAttr(srt,topid,chldid,attr.nodeName(),attr.nodeValue()) == false ) {
				qDebug() << "addTopAttr Error:"+db->mess;
				return false;
			}
		}
	}
	return true;
}

bool clsXmlUpd::addChildNode(int srt,QDomNode node) {
	qDebug() << " child tag="+node.toElement().tagName()+" val="+node.toElement().text();
	if ( db->addSecNode(srt,topid,node.toElement().tagName(),node.toElement().text(),chldid) == false ) {
		qDebug() << "addChildNode Error:"+db->mess;
		return false;
	}
	addAttr(node.attributes(),1);

	return true;
}

bool clsXmlUpd::appendXml() {
	if ( readSql == NULL ) {
		return false;
	}
	if ( readSql->selWhr == NULL ) {
		return false;
	}

	if ( db->setTable(readSql->tbl) == false ) {
		errMess = "setTable:"+db->mess;
		return false;
	}

	QString sql = readSql->selWhr->mkSelSql();
	if ( sql == "" ) {
		errMess = "whr lex error";
		return false;
	}
	if ( db->readRec(sql) == 1 ) {
		errMess = "read topid error:"+db->mess;
		return false;
	}
	topid = db->rec.value("topid").toString();
	qDebug() << "appendXml topid=["+topid+"]";
	if ( topid == "" ) {
		errMess = "not found top";
		return false;
	}

	if ( parse(readSql->insXml) == false ) {
		errMess = "parse Error";
		return false;
	}
	QDomElement root = doc->documentElement();
	qDebug() << "root Tag="+root.tagName();
	QDomNode node = root.firstChild();
	int srt = db->getMaxSrt("d_secnode",topid);
	srt ++;
	while( node.isNull() == false ) {
		addChildNode(srt,node);
		node = node.nextSibling();
		srt ++;
	}
	return true;
}

bool clsXmlUpd::searchXml(int idx) {
	errMess = "";
	if ( readSql == NULL ) {
		return false;
	}
	db->setTable(readSql->tbl);

	QString sql = "";
	if ( readSql->odrWhr == NULL ) {
		sql = readSql->selWhr->mkSelSql();
		qDebug() << "SEARCH SQL=["+sql+"]";
	} else {
		QString wsql = readSql->selWhr->mkSelSql(true);
		sql = readSql->odrWhr->mkOrderSql(wsql,readSql->selWhr->nSelTblCnt);
	}

	QSqlQueryModel *mdl = db->mkQueryModel(sql);
	if ( mdl->rowCount() == 0 ) {
		errMess = "not found";
		qDebug() << "NOT FOUND SQL=["+sql+"]";
		return false;
	}
	/*
	if ( idx > 0 ) {
		if ( mdl->rowCount() >= idx ) {
			QSqlRecord rec = mdl->record(idx-1);
			if ( readXml(rec.value(0).toString()) == false ) {
				errMess = "readXml Error:topid=["+rec.value(0).toString()+"]";
				return false;
			}
			mdl->clear();
			return true;
		}
	}
	*/
	nResCnt = 0;
	lstResult.clear();
	lstResultId.clear();
	for( int i=0; i<mdl->rowCount(); i++ ) {
		QSqlRecord rec = mdl->record(i);
		lstResultId << rec.value(0).toString();
		nResCnt ++;
	}
	if ( idx == 1 ) {
		if ( readXml(lstResultId.at(0)) == false ) {
			errMess = "readXml Error:topid=["+lstResultId.at(0)+"]";
			return false;
		}
		lstResult << toString();
		return true;
	}

	for( int i=0; i<lstResultId.size(); i++ ) {
		if ( readXml(lstResultId.at(i)) == false ) {
			errMess = "readXml Error:topid=["+lstResultId.at(i)+"]";
			return false;
		}
		lstResult << toString();
	}

	return true;
}

bool clsXmlUpd::readXml(QString topid) {
	clearDoc();
	QString tbl = readSql->tbl;
	QString sql = "SELECT * FROM "+tbl+"_d_topnode WHERE id="+topid;
	if ( db->readRec(sql) == 1 ) {
		errMess = "not found top";
		return false;
	}
	doc = new QDomDocument();
	QDomElement root = doc->createElement(db->rec.value("tag").toString());
	sql = "SELECT * FROM "+tbl+"_d_topnode_attr WHERE topid="+topid+" ORDER BY srt";
	QSqlQueryModel *mdl = db->mkQueryModel(sql);
	for( int i=0; i<mdl->rowCount(); i++ ) {
		QSqlRecord rec = mdl->record(i);
		if ( readSql->isOutTagAttr(db->rec.value("tag").toString(),rec.value("itm").toString()) == true ) {
			root.setAttribute(rec.value("itm").toString(),rec.value("val").toString());
		}
	}
	doc->appendChild(root);
	mdl->clear();

	QString outwhr = readSql->outWhr->whrSecOutTag();
	sql = "SELECT * FROM "+tbl+"_d_secnode WHERE topid="+topid;
	if ( outwhr != "" ) {
		sql += " AND "+outwhr;
	}
	//TODO å≈íËÉeÅ[ÉuÉãëŒâû
	//sql += " AND (NOT tag IN ('NGP','NGI')) ";

	//sql += " ORDER BY id";
	qDebug() << "*****"+sql;
	mdl = db->mkQueryModel(sql);
	for( int i=0; i<mdl->rowCount(); i++ ) {
		QSqlRecord rec = mdl->record(i);
		if ( readSql->isOutTag(rec.value("tag").toString()) == true ) {
			//qDebug() << "child tag=["+rec.value("tag").toString()+"]";
			QDomElement child = doc->createElement(rec.value("tag").toString());
			if ( rec.value("val").toString() != "" ) {
				QDomText txt = doc->createTextNode(rec.value("val").toString());
				child.appendChild(txt);
			}
			if ( rec.value("tag").toString() != "NGP" && rec.value("tag").toString() != "NGI" ) {
				qDebug() << "child tag=["+rec.value("tag").toString()+"]";
			}
			sql = "SELECT * FROM "+tbl+"_d_secnode_attr WHERE nid="+rec.value("id").toString();//+" ORDER BY srt";
			QSqlQueryModel *mdlc = db->mkQueryModel(sql);
			for( int j=0; j<mdlc->rowCount(); j++ ) {
				QSqlRecord recc = mdlc->record(j);
				if ( readSql->isOutTagAttr(rec.value("tag").toString(),recc.value("itm").toString()) == true ) {
					child.setAttribute(recc.value("itm").toString(),recc.value("val").toString());
				}
			}
			mdlc->clear();
			root.appendChild(child);
		} else {
			qDebug() << "Out child tag=["+rec.value("tag").toString()+"]";
		}
	}
	mdl->clear();

	//TODO ébíË
	getChildTagAttr(topid,"NGP",root);
	getChildTagAttr(topid,"NGI",root);
	return true;
}

bool clsXmlUpd::getChildTagAttr(QString topid, QString tag, QDomElement &root) {
	if ( readSql->isOutTag(tag) == false ) {
		return false;
	}

	clsTagAttrRec *tagDef = db->getTagDef(tag);
	if ( tagDef == NULL ) {
		return false;
	}
	QString sql = "SELECT * FROM "+readSql->tbl+"_d_sec_"+tag.toLower();
	sql += " WHERE topid="+topid+" ORDER BY nid";
	QSqlQueryModel *mdlc = db->mkQueryModel(sql);
	for( int i=0; i<mdlc->rowCount(); i++ ) {
		QSqlRecord rec = mdlc->record(i);
		QDomElement child = doc->createElement(tag);
		int cnt = 0;
		for( int j=0; j<tagDef->arrTblCol.size(); j++ ) {
			if ( readSql->isOutTagAttr(tag,tagDef->arrItm.at(j)) == true ) {
				child.setAttribute(tagDef->arrItm.at(j),rec.value(tagDef->arrTblCol.at(j)).toString());
				cnt ++;
			}
		}
		if ( cnt > 0 ) {
			root.appendChild(child);
		}
	}
	mdlc->clear();
	return true;
}

bool clsXmlUpd::deleteXml() {
	if ( readSql == NULL ) {
		return false;
	}
	db->setTable(readSql->tbl);
	QString sql = readSql->selWhr->mkSelSql();
	qDebug() << "SEARCH SQL=["+sql+"]";
	QSqlQueryModel *mdl = db->mkQueryModel(sql);
	if ( mdl->rowCount() == 0 ) {
		errMess = "not found";
		return false;
	}
	QString whr = "";
	for( int i=0; i<mdl->rowCount(); i++ ) {
		QSqlRecord rec = mdl->record(i);
		if ( whr != "" ) whr +=",";
		whr += rec.value(0).toString();
	}
	if ( db->delSec(whr) == false ) {
		errMess = db->mess;
		return false;
	}
	if ( db->delTop(whr) == false ) {
		errMess = db->mess;
		return false;
	}
	return true;
}
QString clsXmlUpd::toString() {
	if ( doc == NULL ) {
		return "";
	}
	return doc->toString(2);
}

QString clsXmlUpd::mkWhere(QString whrbuf) {
	QString whr = "";

	clsXmlWhereLex lex(whrbuf);
	if ( lex.error() == false ) {
		qDebug() << lex.errMess;
	}
	whr = lex.mkWhr();
	return whr;
}

QString clsXmlUpd::mkSelSql(QString whrbuf) {
	QString whr = "";

	clsXmlWhereLex lex(whrbuf);
	whr = lex.mkSelSql();
	return whr;
}

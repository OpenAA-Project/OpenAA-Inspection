/*
 * clsXMLDB_Front.cpp
 *
 *	Created on: 2009/12/19
 *		Author: cony
 */

#include "clsXMLDB_Front.h"
#include "clsTcpSvr.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define   new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s) 			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)			_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s) 		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s) 		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsXMLDB_Front::clsXMLDB_Front(clsDb *_db, int port, QObject *_par) : QObject(_par) {
	connNam = "xmldb_"+QString::number(port);
	nParPort = port;
	db = _db;
	par = _par;
	makeObj();
}

clsXMLDB_Front::~clsXMLDB_Front() {
	cleanObj();
}

bool clsXMLDB_Front::searchAllXml(const QByteArray &sql, QByteArray &retByte) {
	if ( objXml->lexSelSql(sql) == false ) {
		errMess = "SELECT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}

	drawMstId(objXml->readSql->tbl);
	if ( objXml->readSql->tbl.indexOf("_all") > 0 ) {
		// DBファイル検索
		return searchAllXmlA(retByte);
	}
	if ( objXml->searchXml() == false ) {
		errMess = "searchXML Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}

	retByte = "SELECT";
	fixStrBnd(retByte,6);
	retByte += QByteArray::number(objXml->nResCnt);
	for( int i=0; i<objXml->nResCnt; i++ ) {
		if ( retByte != "" ) retByte += "_@_";
		retByte += objXml->lstResult.at(i);
	}
	return true;
}

bool clsXMLDB_Front::searchFirstXml(const QByteArray &sql, QByteArray &retByte) {
	if ( objXml->lexSelSql(sql) == false ) {
		errMess = "SELECT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	if ( objXml->readSql->tbl.indexOf("_all") > 0 ) {
		// DBファイル検索
		return searchFirstXmlA(retByte);
	}
	if ( objXml->searchXml(1) == false ) {
		errMess = "searchFirstXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}

	retByte = "FIRST";
	fixStrBnd(retByte,6);
	retByte += QByteArray::number(objXml->nResCnt)+"_@_";
	for( int i=0; i<objXml->nResCnt; i++ ) {
		if ( i > 0 ) retByte += ",";
		retByte += objXml->lstResultId.at(i);
	}
	retByte += "_@_"+objXml->lstResult.at(0);
	return true;
}

bool clsXMLDB_Front::readXml(const QByteArray &sql, const QByteArray id, const QByteArray &dbFile, QByteArray &retByte) {
	if ( objXml->lexSelSql(sql) == false ) {
		errMess = "SELECT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	if ( objXml->readSql->tbl.indexOf("_all") > 0 ) {
		// DBファイル検索
		return readXmlA(id,dbFile,retByte);
	}
	if ( objXml->nextXml(id) == false ) {
		if ( objXml->errMess == "not found top" ) { // 該当なし
			makeReturnByteArray("NEXT","0_@_",retByte);
			return true;
		}
		errMess = "readXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	retByte = "NEXT";
	fixStrBnd(retByte,6);
	retByte += "1_@_"+objXml->toString();
	return true;
}

bool clsXMLDB_Front::searchAllXmlA(QByteArray &retByte) {
	drawMstId(objXml->readSql->tbl);
	if ( objXml->allSearchXml() == false ) {
		errMess = "allSearchXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}

	retByte = "SELECT";
	fixStrBnd(retByte,6);
	retByte += QByteArray::number(objXml->nResCnt);
	for( int i=0; i<objXml->nResCnt; i++ ) {
		if ( retByte != "" ) retByte += "_@_";
		retByte += objXml->lstResult.at(i);
	}
	return true;
}

bool clsXMLDB_Front::searchFirstXmlA(QByteArray &retByte) {
	if ( objXml->allSearchXml(1) == false ) {
		errMess = "searchFirstXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}

	retByte = "FIRST";
	fixStrBnd(retByte,6);
	retByte += QByteArray::number(objXml->nResCnt)+"_@_";
	for( int i=0; i<objXml->nResCnt; i++ ) {
		if ( i > 0 ) retByte += ",";
		retByte += objXml->lstResultId.at(i);
	}
	retByte += "_@_";
	int cnt = 0;
	QByteArray curDbFile = "";
	for( int i=0; i<objXml->lstDbFile.size(); i++ ) {
		if ( curDbFile == "" ) {
			curDbFile = objXml->lstDbFile.at(i);
			cnt = 1;
			continue;
		}
		if ( curDbFile == objXml->lstDbFile.at(i) ) {
			cnt ++;
			continue;
		}
		retByte += curDbFile+","+QByteArray::number(cnt)+",";
		curDbFile = objXml->lstDbFile.at(i);
		cnt = 1;
	}

	retByte += curDbFile+","+QByteArray::number(cnt);
	retByte += "_@_"+objXml->lstResult.at(0);
	return true;
}

bool clsXMLDB_Front::readXmlA(const QByteArray &id, const QByteArray &dbFile, QByteArray &retByte) {
	if ( objXml->allNextXml(id,dbFile) == false ) {
		if ( objXml->errMess == "not found top" ) { // 該当なし
			makeReturnByteArray("NEXT","0_@_",retByte);
			return true;
		}
		errMess = "readXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	retByte = "NEXT";
	fixStrBnd(retByte,6);
	retByte += "1_@_"+objXml->toString();
	return true;
}

bool clsXMLDB_Front::addXml(const QByteArray &sql) {
	if ( objXml->lexUpdSql(sql) == false ) {
		errMess = "INSERT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	if ( objXml->addXml() == false ) {
		errMess = "addXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsXMLDB_Front::appendXml(const QByteArray &sql) {
	objXml->log->log("appendXML startpp",clsLog::CLSLOG_DEBUG);
	objXml->log->log("appendXML startpp1",clsLog::CLSLOG_DEBUG);
	objXml->log->log("appendXML startpp2",clsLog::CLSLOG_DEBUG);
	if ( objXml->lexUpdSql(sql) == false ) {
		errMess = "INSERT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	objXml->log->log("appendXML startpp3",clsLog::CLSLOG_DEBUG);
	if ( objXml->appendXml() == false ) {
		errMess = "appendXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	objXml->log->log("appendXML startpp4",clsLog::CLSLOG_DEBUG);
	return true;
}

bool clsXMLDB_Front::updateXml(const QByteArray &sql) {
	if ( objXml->lexUpdSql(sql) == false ) {
		errMess = "INSERT SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		db->DisConnect();
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	if ( objXml->deleteXml() == false ) {
		errMess = "updateXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	if ( objXml->addXml() == false ) {
		errMess = "updateXml(addXml) Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsXMLDB_Front::deleteXml(const QByteArray &sql) {
	if ( objXml->lexUpdSql(sql) == false ) {
		errMess = "DELETE SQL Format Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	drawMstId(objXml->readSql->tbl);
	if ( objXml->deleteXml() == false ) {
		errMess = "deleteXml Error:"+objXml->errMess;
		objXml->log->log(errMess,clsLog::CLSLOG_DEBUG);
		return false;
	}
	return true;
}

bool clsXMLDB_Front::makeReturnByteArray(QString cmd, QString buf, QByteArray &retByte) {
	QString tmp = fixStrBnd(cmd,6);
	retByte = tmp.toLocal8Bit()+buf.toLocal8Bit();
	return true;
}

QString clsXMLDB_Front::fixStrBnd(QString buf, int len) {
	QString ret = buf;
	if ( ret.length() < len ) {
		int str = ret.length();
		for( int i=str; i<len; i++ ) {
			ret += " ";
		}
	}
	return ret;
}

void clsXMLDB_Front::fixStrBnd(QByteArray &buf, int len) {
	if ( buf.length() < len ) {
		int str = buf.length();
		for( int i=str; i<len; i++ ) {
			buf += " ";
		}
	}
}

void clsXMLDB_Front::drawMstId(const QByteArray &MstId) {
	clsTcpThread *obj = (clsTcpThread *)par;
	if ( MstId.indexOf("_all") > 0 )
		obj->drawMstId(MstId.mid(0,MstId.length()-4));
	else
		obj->drawMstId(MstId);
}

void clsXMLDB_Front::makeObj() {
	objXml = new clsXmlUpd();
	//db = new clsDb();
	//db->connNam = connNam;

	db->setPrm();
	objXml->db = db;
	objXml->nParPort = nParPort;
}

void clsXMLDB_Front::cleanObj() {
	if ( objXml != NULL ) {
		delete(objXml);
		objXml = NULL;
	}

	//if ( db != NULL ) {
	//	delete(db);
	//	db = NULL;
	//}
}

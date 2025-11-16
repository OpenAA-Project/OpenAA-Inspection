/*
 * clsXmlWhereLex.h
 *
 *  Created on: 2009/11/26
 *      Author: cony
 */

#ifndef CLSXMLWHERELEX_H_
#define CLSXMLWHERELEX_H_

#include <QString>
#include "NList.h"
#include "clsDb.h"

class clsXMLAttrRec : public NPList<clsXMLAttrRec> {
public:
	clsXMLAttrRec(){
		itm = "";
		eq = "";
		val = "";
	}
	QString itm;
	QString eq;
	QString val;
};

class clsXMLOrderRec : public NPList<clsXMLOrderRec> {
public:
	clsXMLOrderRec() {
		tag = "";
		attr = "";
		odr = "";
		lvl = 0;
	}
	QString tag;
	QString attr;
	QString odr;
	int lvl;
};

class clsXMLRec : public NPList<clsXMLRec> {
public:
	clsXMLRec(){
		tag = "";
		childs = NULL;
		attrs = NULL;
		order = NULL;
	}
	QString tag;
	QString val;
	NPListPack<clsXMLRec> *childs;
	NPListPack<clsXMLAttrRec> *attrs;
	NPListPack<clsXMLOrderRec> *order;
};

class clsXmlLexBase {
public:
	clsXmlLexBase(QString _buf);
	virtual ~clsXmlLexBase();

	virtual QString mkWhr();

	QString errMess;
	bool error() {
		if ( errMess != "" ) {
			return false;
		}
		return true;
	}
	void setTable(QString _tbl) {
		tbl = _tbl;
	}
	void setDb(clsDb *_db) {
		db = _db;
	}

protected:
	QString srcBuf;
	QByteArray buf;
	clsXMLRec whrrec;
	QString tbl;
	clsDb *db;
	virtual void mkXMLRec(){};

	/// ëÆê´éÊìæ
	virtual bool getAttr(NPListPack<clsXMLAttrRec> *attrs);

	int nextTagName();
	int nextTagValue();
	int nextAttrName();
	int nextAttrNameOut();
	int nextAttrEq();
	int nextAttrVal();

	bool nextPt(int len);
	QString getBufMid(int nLen);

	char *p;
	int nStart;
	int nMaxLen;
	bool nextStop(char stop);
	int chkRetLen(int len);

	QString mkAttrWhr(QString itm, QString itmval);
	QString mkAttrValWhr(QString eq, QString val);
	QString mkTagWhr(QString val);
	QString mkTagValWhr(QString val);

	void debugPrt(const char *mess=0x00) {
		if ( mess != 0x00 ) {
			printf("%s : pnt=[%d]=>[%s]\n",mess,nStart,p);
		} else {
			printf("pnt=[%d]=>[%s]\n",nStart,p);
		}
	}
};

class clsXmlOutLex : public clsXmlLexBase  {
public:
	clsXmlOutLex(QString _buf);
	virtual ~clsXmlOutLex();

	bool isOutTag(QString tag);
	bool isOutTagAttr(QString tag, QString attr);

	QString whrSecOutTag();

	bool bFullFlg;

protected:
	void mkXMLRec();
	bool getAttr(NPListPack<clsXMLAttrRec> *attrs);
	bool isTagInAttr(clsXMLRec *rec, QString attr);
};

class clsXmlWhereLex : public clsXmlLexBase {
public:
	clsXmlWhereLex(QString _buf);
	virtual ~clsXmlWhereLex();

	QString mkSelSql(bool bflg=false);
	int nSelTblCnt;

	QString mkWhrTopNode();
	QString mkWhrTopAttr();
	QString mkWhrSecNode();
	QString mkWhrSecAttr();

protected:
	void mkXMLRec();

private:
	QString mkSelSubSql(QString whrtag, QString whrattr, int lvl);
	QString mkSelSubValSql(QString whrtag, QString whrval, int lvl);
};

class clsXmlOrderLex : public clsXmlLexBase {
public:
	clsXmlOrderLex(QString _buf);
	virtual ~clsXmlOrderLex();

	QString mkOrderSql(QString wsql, int nSelTblCnt);
	QString mkSecTagOrderSql(clsXMLOrderRec *rec);
	QString debugPrt();

protected:
	void mkXMLRec();
	QString addTagTbl(QString sql, clsXMLOrderRec *rec);
	QString addWhrTbl(QString whr, clsXMLOrderRec *rec);
	QString addOdrTbl(QString odr, clsXMLOrderRec *rec);
	QString bndTblNam(clsXMLOrderRec *rec);
};

#endif /* CLSXMLWHERELEX_H_ */

/*
 * clsXmlWhereLex.h
 *
 *  Created on: 2009/11/26
 *      Author: cony
 */

#ifndef CLSXMLWHERELEX_H_
#define CLSXMLWHERELEX_H_

#include <QString>
#include <QByteArray>
#include "NList.h"
#include "clsDb.h"

/**
 * @brief 属性条件クラス
 *
 * 属性条件を保存
 */
class clsXMLAttrRec : public NPList<clsXMLAttrRec> {
public:
	clsXMLAttrRec(){
		itm = "";
		eq = "";
		val = "";
	}
	~clsXMLAttrRec() {
		itm.clear();
		eq.clear();
		val.clear();
	}
	QByteArray itm;
	QByteArray eq;
	QByteArray val;
};

/**
 * @brief ソート順条件クラス
 */
class clsXMLOrderRec : public NPList<clsXMLOrderRec> {
public:
	clsXMLOrderRec() {
		tag = "";
		attr = "";
		odr = "";
		lvl = 0;
	}
	~clsXMLOrderRec() {
		tag.clear();
		attr.clear();
		odr.clear();
	}
	QByteArray tag;
	QByteArray attr;
	QByteArray odr;
	int lvl;
};

/**
 * @brief タグ条件クラス
 */
class clsXMLRec : public NPList<clsXMLRec> {
public:
	clsXMLRec(){
		tag = "";
		val = "";
		childs = NULL;
		attrs = NULL;
		order = NULL;
	}
	~clsXMLRec() {
		tag.clear();
		val.clear();
	}
	QByteArray tag;
	QByteArray val;
	NPListPack<clsXMLRec> *childs;
	NPListPack<clsXMLAttrRec> *attrs;
	NPListPack<clsXMLOrderRec> *order;
};

/**
 * @brief 条件操作基底クラス
 */
class clsXmlLexBase {
public:
	clsXmlLexBase(const QByteArray &_buf);
	virtual ~clsXmlLexBase();

	virtual QByteArray mkWhr();

	QString errMess;
	bool error() {
		if ( errMess != "" ) {
			return false;
		}
		return true;
	}
	void setTable(QByteArray _tbl) {
		tbl = _tbl;
	}
	void setDb(clsDb *_db) {
		db = _db;
	}

protected:
	QByteArray srcBuf;
	clsXMLRec whrrec;
	QByteArray tbl;
	clsDb *db;
	virtual void mkXMLRec(){};

	/// 属性取得
	virtual bool getAttr(NPListPack<clsXMLAttrRec> *attrs);

	int nextTagName();
	int nextTagValue();
	int nextAttrName();
	int nextAttrNameOut();
	int nextAttrEq();
	int nextAttrVal();

	bool nextPt(int len);
	QByteArray getBufMid(int nLen);

	char *p;
	int nStart;
	int nMaxLen;
	bool nextStop(char stop);
	int chkRetLen(int len);

	QByteArray mkAttrWhr(const QByteArray &itm, const QByteArray &itmval);
	QByteArray mkAttrValWhr(const QByteArray &eq, const QByteArray &val);
	QByteArray mkTagWhr(const QByteArray &val);
	QByteArray mkTagValWhr(const QByteArray &val);

	void debugPrt(const char *mess=0x00) {
		if ( mess != 0x00 ) {
			printf("%s : pnt=[%d]=>[%s]\n",mess,nStart,p);
		} else {
			printf("pnt=[%d]=>[%s]\n",nStart,p);
		}
	}

	bool bndSplit(const QByteArray &rep, const QByteArray &src, QList<QByteArray> &lst);
};

/**
 * @brief 出力条件操作クラス
 */
class clsXmlOutLex : public clsXmlLexBase  {
public:
	clsXmlOutLex(const QByteArray &_buf);
	virtual ~clsXmlOutLex();

	bool isOutTag(const QByteArray &tag);
	bool isOutTagAttr(const QByteArray &tag, const QByteArray &attr);

	QByteArray whrSecOutTag();

	bool bFullFlg;

protected:
	void mkXMLRec();
	bool getAttr(NPListPack<clsXMLAttrRec> *attrs);
	bool isTagInAttr(clsXMLRec *rec, const QByteArray &attr);
};

/**
 * @brief 検索条件操作クラス
 */
class clsXmlWhereLex : public clsXmlLexBase {
public:
	clsXmlWhereLex(const QByteArray &_buf);
	virtual ~clsXmlWhereLex();

	QByteArray mkSelSql(bool bflg=false);
	int nSelTblCnt;

	/**
	 * @brief トップノード条件生成
	 */
	QByteArray mkWhrTopNode();

	/**
	 * @brief トップノード属性条件生成
	 */
	QByteArray mkWhrTopAttr();

	/**
	 * @brief 子ノード条件生成
	 */
	QByteArray mkWhrSecNode();

	/**
	 * @brief 子ノード属性条件生成
	 */
	QByteArray mkWhrSecAttr();

	/*
	QByteArray getLid();
	QByteArray getEid();
	QByteArray getDay();
	 */

	/**
	 * @brief DBマスタ検索条件生成
	 */
	QByteArray mkDbMstWhr();

	/**
	 * @brief 装置番号、検査日取得
	 */
	bool getDbKey(QByteArray &mac, QByteArray &day);

protected:
	void mkXMLRec();

private:
	QByteArray mkSelSubSql(const QByteArray &whrtag, const QByteArray &whrattr, int lvl);
	QByteArray mkSelSubValSql(const QByteArray &whrtag, const QByteArray &whrval, int lvl);
	QByteArray bndDay(const QByteArray &day);
};

/**
 * @brief ソート条件操作クラス
 */
class clsXmlOrderLex : public clsXmlLexBase {
public:
	clsXmlOrderLex(const QByteArray &_buf);
	virtual ~clsXmlOrderLex();

	QByteArray mkOrderSql(const QByteArray &wsql, int nSelTblCnt);
	QByteArray mkSecTagOrderSql(clsXMLOrderRec *rec);
	QByteArray debugPrt();

protected:
	void mkXMLRec();
	QByteArray addTagTbl(const QByteArray &sql, clsXMLOrderRec *rec);
	QByteArray addWhrTbl(const QByteArray &whr, clsXMLOrderRec *rec);
	QByteArray addOdrTbl(const QByteArray &odr, clsXMLOrderRec *rec);
	QByteArray bndTblNam(clsXMLOrderRec *rec);
};

#endif /* CLSXMLWHERELEX_H_ */

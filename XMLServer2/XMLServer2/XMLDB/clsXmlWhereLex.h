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


#ifndef CLSXMLWHERELEX_H_
#define CLSXMLWHERELEX_H_

#include <QString>
#include <QByteArray>
#include "NList.h"
#include "clsDb.h"

/**
 * @brief ���������N���X
 *
 * �����������ۑ�
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
 * @brief �\�[�g�������N���X
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
 * @brief �^�O�����N���X
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
 * @brief �������������N���X
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

	/// �����擾
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
 * @brief �o�͏��������N���X
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
 * @brief �������������N���X
 */
class clsXmlWhereLex : public clsXmlLexBase {
public:
	clsXmlWhereLex(const QByteArray &_buf);
	virtual ~clsXmlWhereLex();

	QByteArray mkSelSql(bool bflg=false);
	int nSelTblCnt;

	/**
	 * @brief �g�b�v�m�[�h��������
	 */
	QByteArray mkWhrTopNode();

	/**
	 * @brief �g�b�v�m�[�h������������
	 */
	QByteArray mkWhrTopAttr();

	/**
	 * @brief �q�m�[�h��������
	 */
	QByteArray mkWhrSecNode();

	/**
	 * @brief �q�m�[�h������������
	 */
	QByteArray mkWhrSecAttr();

	/*
	QByteArray getLid();
	QByteArray getEid();
	QByteArray getDay();
	 */

	/**
	 * @brief DB�}�X�^������������
	 */
	QByteArray mkDbMstWhr();

	/**
	 * @brief ���u�ԍ��A�������擾
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
 * @brief �\�[�g���������N���X
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
/*
 * clsXmlWhereLex.cpp
 *
 *  Created on: 2009/11/26
 *      Author: cony
 */

#include "clsXmlWhereLex.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsXmlWhereLex::clsXmlWhereLex(const QByteArray &_buf) :
	clsXmlLexBase(_buf) {
	whrrec.childs = new NPListPack<clsXMLRec> ();
	whrrec.attrs = new NPListPack<clsXMLAttrRec> ();
	mkXMLRec();
}

clsXmlWhereLex::~clsXmlWhereLex() {
	if (whrrec.attrs != NULL) {
		delete (whrrec.attrs);
	}
	if (whrrec.childs != NULL) {
		clsXMLRec *rec = whrrec.childs->GetFirst();
		while (rec != NULL) {
			if (rec->attrs != NULL) {
				delete (rec->attrs);
			}
			rec = rec->GetNext();
		}
		delete (whrrec.childs);
	}
}

void clsXmlWhereLex::mkXMLRec() {
	errMess = "";
	if (*p != '<') {
		errMess = "Not Tag Format";
		return;
	}
	debugPrt("whereLex Start");

	// 親タグ取得
	if (nextPt(1) == false) {
		return;
	}
	int nTagLen = nextTagName();
	if (nTagLen <= 0 || nTagLen + 1 >= srcBuf.length()) {
		errMess = "Not Tag Format";
		return;
	}
	whrrec.tag = getBufMid(nTagLen);
	if (nextPt(nTagLen) == false) {
		return;
	}
	debugPrt("end Parent Tag");
	if ( *p == '>' ) {
		if ( nextPt(1) == false ) return;
	}
	if (*p == ' ') {
		// 親属性取得
		if (nextPt(1) == false)
			return;
		while (*p != 0x00) {
			if (*p == '>') {
				if (nextPt(1) == false)
					return;
				break;
			}
			debugPrt("start attr");
			if (getAttr(whrrec.attrs) == false)
				return;
			debugPrt("end attr");
			if (*p == '>') {
				if (nextPt(1) == false)
					return;
				break;
			}
			if (*p == '/' && *(p + 1) == '>') {
				if (nextPt(2) == false)
					return;
				break;
			}
			if (*p == ' ') {
				if (nextPt(1) == false)
					return;
				continue;
			}
			errMess = "bad format:" + srcBuf;
			return;
		}
		debugPrt("end Parent attr");
	}
	if (*p == '<' && *(p + 1) == '/') {
		return;
	}
	if (*p != '<') {
		// 親値取得
		debugPrt("start Parent TagValue");
		nTagLen = nextTagValue();
		if (nTagLen <= 0)
			return;
		whrrec.val = getBufMid(nTagLen);
		if (nextPt(nTagLen) == false)
			return;
		debugPrt("end Parent TagValue");
	}

	// 子タグ解析
	if (*p == 0x00)
		return;
	if (*p == '<' && *(p + 1) == '/')
		return;
	debugPrt("start child taglex");
	while (*p != 0x00) {
		if (*p != '<') {
			errMess = "bad format";
			return;
		}
		if (nextPt(1) == false)
			return;
		nTagLen = nextTagName();
		if (nTagLen <= 0)
			return;
		clsXMLRec *recChild = new clsXMLRec();
		recChild->tag = getBufMid(nTagLen);
		whrrec.childs->AppendList(recChild);
		if (nextPt(nTagLen) == false)
			return;
		if (*p == ' ') {
			// 子属性取得
			if (nextPt(1) == false)
				return;
			while (*p != 0x00) {
				debugPrt("start attr");
				if (recChild->attrs == NULL) {
					recChild->attrs = new NPListPack<clsXMLAttrRec> ();
				}
				if (getAttr(recChild->attrs) == false)
					return;
				if (*p == '>') {
					if (nextPt(1) == false)
						return;
					break;
				}
				if (*p == '/' && *(p + 1) == '>') {
					if (nextPt(2) == false)
						return;
					break;
				}
				if (*p == ' ') {
					if (nextPt(1) == false)
						return;
					continue;
				}
				errMess = "bad format:" + srcBuf;
				return;
			}
			debugPrt("end attr");
		}
		debugPrt("atfer child");
		if (*p != '<') {
			if (*p == '>') {
				if (nextPt(1) == false)
					return;
			}
			debugPrt("start tagvalue");
			// TODO 子タグ値
			nTagLen = nextTagValue();
			if (nTagLen <= 0)
				return;
			recChild->val = getBufMid(nTagLen);
			if (nextPt(nTagLen) == false)
				return;
			debugPrt("end tagvalue");
		}
		if (*p == '<' && *(p + 1) == '/') {
			if (nextStop('>') == false)
				return;
			debugPrt("next child continue");
			if (nextPt(1) == false)
				return;
			if (*p == '<' && *(p + 1) == '/') {
				break;
			}
			continue;
		}
		//break;
	}
}

QByteArray clsXmlWhereLex::mkSelSql(bool bflg) {
	QByteArray sql = "";
	if (whrrec.tag == "") {
		return "not where";
	}
	nSelTblCnt = 0;
	QByteArray whrtag = mkAttrWhr("tag", whrrec.tag);
	QByteArray whrattr = "";
	if (whrrec.attrs != NULL) {
		clsXMLAttrRec *recAttr = whrrec.attrs->GetFirst();
		while (recAttr != NULL) {
			whrattr = mkAttrWhr("itm", recAttr->itm) + " AND " + mkAttrValWhr(
					recAttr->eq, recAttr->val);
			QByteArray tmp = mkSelSubSql(whrtag, whrattr, 0);
			if (sql != "")
				sql += ", ";
			sql += "(" + tmp + ") sel" + QByteArray::number(nSelTblCnt) + " ";
			nSelTblCnt++;
			recAttr = recAttr->GetNext();
		}
	}
	qDebug() << "*************mkSelSql=" + sql;
	if (whrrec.val != "") {
		whrtag = mkAttrWhr("tag", whrrec.tag);
		whrattr = mkTagValWhr(whrrec.val);
		if (sql != "")
			sql += ", ";
		sql += "(" + mkSelSubValSql(whrtag, whrattr, 0) + ") sel"
				+ QByteArray::number(nSelTblCnt) + " ";
		nSelTblCnt++;
	}

	if (whrrec.childs != NULL) {
		clsXMLRec *recChild = whrrec.childs->GetFirst();
		while (recChild != NULL) {
			whrtag = mkAttrWhr("tag", recChild->tag);
			if (recChild->attrs != NULL) {
				clsXMLAttrRec *recAttr = recChild->attrs->GetFirst();
				while (recAttr != NULL) {
					whrattr = mkAttrWhr("itm", recAttr->itm) + " AND "
							+ mkAttrValWhr(recAttr->eq, recAttr->val);
					QString tmp = mkSelSubSql(whrtag, whrattr, 1);
					qDebug() << "********mkSelSql Child SQL=" + tmp;
					if (sql != "")
						sql += ", ";
					sql += "(" + tmp + ") sel" + QString::number(nSelTblCnt)
							+ " ";
					nSelTblCnt++;
					recAttr = recAttr->GetNext();
				}
			}
			if (recChild->val != "") {
				whrtag = mkAttrWhr("tag", recChild->tag);
				whrattr = mkTagValWhr(recChild->val);
				if (sql != "")
					sql += ", ";
				sql += "(" + mkSelSubValSql(whrtag, whrattr, 1) + ") sel"
						+ QString::number(nSelTblCnt) + " ";
				nSelTblCnt++;
			}
			recChild = recChild->GetNext();
		}
		qDebug() << "*************mkSelSql=" + sql;
	}

	if (bflg == false) {
		QByteArray retsql = "SELECT top.id AS topid FROM " + tbl
				+ "_d_topnode top,";
		retsql += sql + " WHERE ";
		for (int i = 0; i < nSelTblCnt; i++) {
			if (i > 0)
				retsql += " AND ";
			retsql += "top.id=sel" + QString::number(i) + ".topid";
		}
		return retsql;
	}

	return sql;
}

QByteArray clsXmlWhereLex::mkSelSubSql(const QByteArray &whrtag,
		const QByteArray &whrattr, int lvl) {
	QByteArray sql = "";
	if (lvl == 0) { // d_topnode
		sql = "SELECT topid FROM " + tbl + "_d_topnode_attr WHERE " + whrattr;
		sql += " AND topid IN (SELECT id FROM " + tbl + "_d_topnode WHERE "
				+ whrtag + ")";
	} else if (lvl == 1) { // d_secnode
		sql = "SELECT topid FROM " + tbl + "_d_secnode_attr WHERE " + whrattr;
		sql += " AND nid IN (SELECT id FROM " + tbl + "_d_secnode WHERE "
				+ whrtag + ")";
	}

	return sql;
}

QByteArray clsXmlWhereLex::mkSelSubValSql(const QByteArray &whrtag,
		const QByteArray &whrval, int lvl) {
	QByteArray sql = "";
	if (lvl == 0) {
		sql = "SELECT id AS topid FROM " + tbl + "_d_topnode WHERE " + whrval
				+ " AND " + whrtag;
	} else if (lvl == 1) {
		sql = "SELECT topid FROM " + tbl + "_d_secnode WHERE " + whrval
				+ " AND " + whrtag;
	}
	return sql;
}

/*
QByteArray clsXmlWhereLex::getLid() {
	if (whrrec.childs == NULL) {
		return "";
	}
	clsXMLRec *recChild = whrrec.childs->GetFirst();
	while (recChild != NULL) {
		if (recChild->tag == "LOT") {
			if (recChild->attrs == NULL) {
				return "";
			}
			clsXMLAttrRec *recAttr = recChild->attrs->GetFirst();
			while (recAttr != NULL) {
				if (recAttr->itm == "LID") {
					return recAttr->val;
				}
				recAttr = recAttr->GetNext();
			}
		}
		recChild = recChild->GetNext();
	}
	return "";
}

QByteArray clsXmlWhereLex::getEid() {
	if (whrrec.childs == NULL) {
		return "";
	}
	clsXMLRec *recChild = whrrec.childs->GetFirst();
	while (recChild != NULL) {
		if (recChild->tag == "INSPECT") {
			if (recChild->attrs == NULL) {
				return "";
			}
			clsXMLAttrRec *recAttr = recChild->attrs->GetFirst();
			while (recAttr != NULL) {
				if (recAttr->itm == "EID") {
					return recAttr->val;
				}
				recAttr = recAttr->GetNext();
			}
		}
		recChild = recChild->GetNext();
	}
	return "";
}

QByteArray clsXmlWhereLex::getDay() {
	clsXMLAttrRec *recTop = whrrec.attrs->GetFirst();
	while (recTop != NULL) {
		if (recTop->itm == "DAY") {
			return "20" + recTop->val.replace("/", "");
		}
		recTop = recTop->GetNext();
	}
	return "";
}
*/

QByteArray clsXmlWhereLex::mkWhrTopNode() {
	QByteArray whr = "";
	return whr;
}

QByteArray clsXmlWhereLex::mkWhrTopAttr() {
	QByteArray whr = "";
	return whr = "";
}

QByteArray clsXmlWhereLex::mkWhrSecNode() {
	QByteArray whr = "";
	return whr;
}

QByteArray clsXmlWhereLex::mkWhrSecAttr() {
	QByteArray whr = "";
	return whr = "";
}

bool clsXmlWhereLex::getDbKey(QByteArray &mac, QByteArray &day) {
	if ( whrrec.attrs == NULL ) {
		return false;
	}
	bool flg1 = false;
	bool flg2 = false;
	clsXMLAttrRec *recTop = whrrec.attrs->GetFirst();
	while (recTop != NULL) {
		if ( recTop->itm == "DAY" ) {
			day = recTop->val;
			flg1 = true;
		}
		if ( recTop->itm == "MAC" ) {
			mac = recTop->val;
			flg2 = true;
		}
		if ( flg1 == true && flg2 == true ) break;
		recTop = recTop->GetNext();
	}
	if ( flg1 == true && flg2 == true ) return true;
	return false;
}

QByteArray clsXmlWhereLex::mkDbMstWhr() {
	QByteArray whr = "";
	clsXMLAttrRec *recDayFrm = NULL;
	clsXMLAttrRec *recDayTo = NULL;
	clsXMLAttrRec *recMacFrm = NULL;
	clsXMLAttrRec *recMacTo = NULL;
	clsXMLAttrRec *recTop = whrrec.attrs->GetFirst();
	while (recTop != NULL) {
		if (recTop->itm == "DAY") {
			qDebug() << "eq=["+recTop->eq+"]";
			if (recTop->eq == "=") {
				recDayFrm = recTop;
			}
			if (recTop->eq.at(0) == '>' || recTop->eq == ">=") {
				recDayFrm = recTop;
			}
			if (recTop->eq.at(0) == '<' || recTop->eq == "<=") {
				recDayTo = recTop;
			}
		}
		if (recTop->itm == "MAC") {
			if (recTop->eq == "=") {
				recMacFrm = recTop;
			}
			if (recTop->eq.at(0) == '>') {
				recMacFrm = recTop;
			}
			if (recTop->eq.at(0) == '<') {
				recMacTo = recTop;
			}
		}
		recTop = recTop->GetNext();
	}
	if (recDayFrm != NULL) {
		if (recDayTo != NULL) {
			whr = "startymd>='"+bndDay(recDayFrm->val)+"' AND startymd<'"+bndDay(recDayTo->val)+"'";
		} else {
			whr = "startymd" + recDayFrm->eq + "'" + bndDay(recDayFrm->val) + "'";
		}
	} else {
		if (recDayTo != NULL) {
			whr = "startymd" + recDayTo->eq + "'" + bndDay(recDayTo->val) + "'";
		}
	}
	if (recMacFrm != NULL) {
		if (recMacTo != NULL) {
			if ( whr != "" ) whr += " AND ";
			whr += "mac BETWEEN '"+recMacFrm->val+"' AND '"+recMacTo->val+"'";
		} else {
			if ( whr != "" ) whr += " AND ";
			whr += "mac" + recMacFrm->eq + "'" + recMacFrm->val + "'";
		}
	} else {
		if (recMacTo != NULL) {
			if ( whr != "" ) whr += " AND ";
			whr += "mac" + recMacTo->eq + "'" + recMacTo->val + "'";
		}
	}

	return whr;
}

QByteArray clsXmlWhereLex::bndDay(const QByteArray &day) {
	if ( day.length() < 12 ) {
		return "200"+day.mid(0,5);
	}
	return "20"+day.mid(0,6);
}

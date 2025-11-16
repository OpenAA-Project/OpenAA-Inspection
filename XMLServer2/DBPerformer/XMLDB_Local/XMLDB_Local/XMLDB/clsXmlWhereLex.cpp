/*
 * clsXmlWhereLex.cpp
 *
 *  Created on: 2009/11/26
 *      Author: cony
 */

#include "clsXmlWhereLex.h"

clsXmlWhereLex::clsXmlWhereLex(QString _buf) : clsXmlLexBase(_buf) {
	whrrec.childs = new NPListPack<clsXMLRec>();
	whrrec.attrs = new NPListPack<clsXMLAttrRec>();
	mkXMLRec();
}

clsXmlWhereLex::~clsXmlWhereLex() {
	// TODO Auto-generated destructor stub
}

void clsXmlWhereLex::mkXMLRec() {
	errMess = "";
	if ( *p != '<' ) {
		errMess = "Not Tag Format";
		return;
	}
	debugPrt("whereLex Start");

	// 親タグ取得
	if ( nextPt(1) == false ) {
		return;
	}
	int nTagLen = nextTagName();
	if ( nTagLen <= 0 || nTagLen+1 >= buf.length() ) {
		errMess = "Not Tag Format";
		return;
	}
	whrrec.tag = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) {
		return;
	}
	debugPrt("end Parent Tag");
	if ( *p == ' ' ) {
		// 親属性取得
		if ( nextPt(1) == false ) return;
		while( *p != 0x00 ) {
			if ( *p == '>' ) {
				if ( nextPt(1) == false ) return;
				break;
			}
			debugPrt("start attr");
			if ( getAttr(whrrec.attrs) == false ) return;
			debugPrt("end attr");
			if ( *p == '>' ) {
				if ( nextPt(1) == false ) return;
				break;
			}
			if ( *p == '/' && *(p+1) == '>' ) {
				if ( nextPt(2) == false ) return;
				break;
			}
			if ( *p == ' ' ) {
				if ( nextPt(1) == false ) return;
				continue;
			}
			errMess = "bad format:"+buf;
			return;
		}
		debugPrt("end Parent attr");
	}
	if ( *p == '<' && *(p+1) == '/' ) {
		return;
	}
	if ( *p != '<' ) {
		// 親値取得
		debugPrt("start Parent TagValue");
		nTagLen = nextTagValue();
		if ( nTagLen <= 0 ) return;
		whrrec.val = getBufMid(nTagLen);
		if ( nextPt(nTagLen) == false ) return;
		debugPrt("end Parent TagValue");
	}

	// 子タグ解析
	if ( *p == 0x00 ) return;
	if ( *p == '<' && *(p+1) == '/' ) return;
	debugPrt("start child taglex");
	while( *p != 0x00 ) {
		if ( *p != '<' ) {
			errMess = "bad format";
			return;
		}
		if ( nextPt(1) == false ) return;
		nTagLen = nextTagName();
		if ( nTagLen <= 0 ) return;
		clsXMLRec *recChild = new clsXMLRec();
		recChild->tag = getBufMid(nTagLen);
		whrrec.childs->AppendList(recChild);
		if ( nextPt(nTagLen) == false ) return;
		if ( *p == ' ' ) {
			// 子属性取得
			if ( nextPt(1) == false ) return;
			while( *p != 0x00 ) {
				debugPrt("start attr");
				if ( recChild->attrs == NULL ) {
					recChild->attrs = new NPListPack<clsXMLAttrRec>();
				}
				if ( getAttr(recChild->attrs) == false ) return;
				if ( *p == '>' ) {
					if ( nextPt(1) == false ) return;
					break;
				}
				if ( *p == '/' && *(p+1) == '>' ) {
					if ( nextPt(2) == false ) return;
					break;
				}
				if ( *p == ' ' ) {
					if ( nextPt(1) == false ) return;
					continue;
				}
				errMess = "bad format:"+buf;
				return;
			}
			debugPrt("end attr");
		}
		debugPrt("atfer child");
		if ( *p != '<' ) {
			if ( *p == '>' ) {
				if ( nextPt(1) == false ) return;
			}
			debugPrt("start tagvalue");
			// TODO 子タグ値
			nTagLen = nextTagValue();
			if ( nTagLen <= 0 ) return;
			recChild->val = getBufMid(nTagLen);
			if ( nextPt(nTagLen) == false ) return;
			debugPrt("end tagvalue");
		}
		if ( *p == '<' && *(p+1) == '/' ) {
			if ( nextStop('>') == false ) return;
			debugPrt("next child continue");
			if ( nextPt(1) == false ) return;
			if ( *p == '<' && *(p+1) == '/' ) {
				break;
			}
			continue;
		}
		//break;
	}
}

QString clsXmlWhereLex::mkSelSql(bool bflg) {
	QString sql = "";
	if ( whrrec.tag == "" ) {
		return "not where";
	}
	nSelTblCnt = 0;
	QString whrtag = mkAttrWhr("tag",whrrec.tag);
	QString whrattr = "";
	if ( whrrec.attrs != NULL ) {
		clsXMLAttrRec *recAttr = whrrec.attrs->GetFirst();
		while( recAttr != NULL ) {
			whrattr = mkAttrWhr("itm",recAttr->itm)+" AND "+mkAttrValWhr(recAttr->eq,recAttr->val);
			QString tmp = mkSelSubSql(whrtag, whrattr,0);
			if ( sql != "" ) sql += ", ";
			sql += "("+tmp + ") sel"+QString::number(nSelTblCnt)+" ";
			nSelTblCnt++;
			recAttr = recAttr->GetNext();
		}
	}
	qDebug() << "*************mkSelSql=" +sql;
	if ( whrrec.val != "" ) {
		whrtag  = mkAttrWhr("tag",whrrec.tag);
		whrattr = mkTagValWhr(whrrec.val);
		if ( sql != "" ) sql += ", ";
		sql += "("+mkSelSubValSql(whrtag,whrattr,0)+ ") sel"+QString::number(nSelTblCnt)+" ";
		nSelTblCnt++;
	}

	if ( whrrec.childs != NULL ) {
		clsXMLRec *recChild = whrrec.childs->GetFirst();
		while( recChild != NULL ) {
			whrtag = mkAttrWhr("tag",recChild->tag);
			if ( recChild->attrs != NULL ) {
				clsXMLAttrRec *recAttr = recChild->attrs->GetFirst();
				while( recAttr != NULL ) {
					whrattr = mkAttrWhr("itm",recAttr->itm)+" AND "+mkAttrValWhr(recAttr->eq,recAttr->val);
					QString tmp = mkSelSubSql(whrtag, whrattr,1);
					qDebug() << "********mkSelSql Child SQL="+tmp;
					if ( sql != "" ) sql += ", ";
					sql += "("+ tmp+ ") sel"+QString::number(nSelTblCnt)+" ";
					nSelTblCnt++;
					recAttr = recAttr->GetNext();
				}
			}
			if ( recChild->val != "" ) {
				whrtag  = mkAttrWhr("tag",recChild->tag);
				whrattr = mkTagValWhr(recChild->val);
				if ( sql != "" ) sql += ", ";
				sql += "("+ mkSelSubValSql(whrtag,whrattr,1)+ ") sel"+QString::number(nSelTblCnt)+" ";
				nSelTblCnt++;
			}
			recChild = recChild->GetNext();
		}
		qDebug() << "*************mkSelSql=" +sql;
	}

	if ( bflg == false ) {
		QString retsql = "SELECT top.id AS topid FROM "+tbl+"_d_topnode top,";
		retsql += sql + " WHERE ";
		for( int i=0; i<nSelTblCnt; i++ ) {
			if ( i > 0 ) retsql += " AND ";
			retsql += "top.id=sel"+QString::number(i)+".topid";
		}
		return retsql;
	}

	return sql;
}

QString clsXmlWhereLex::mkSelSubSql(QString whrtag, QString whrattr, int lvl) {
	QString sql = "";
	if ( lvl == 0 ) { // d_topnode
		sql = "SELECT topid FROM "+tbl+"_d_topnode_attr WHERE "+whrattr;
		sql += " AND topid IN (SELECT id FROM "+tbl+"_d_topnode WHERE "+whrtag+")";
	} else if ( lvl == 1 ) { // d_secnode
		sql = "SELECT topid FROM "+tbl+"_d_secnode_attr WHERE "+whrattr;
		sql += " AND nid IN (SELECT id FROM "+tbl+"_d_secnode WHERE "+whrtag+")";
	}

	return sql;
}

QString clsXmlWhereLex::mkSelSubValSql(QString whrtag, QString whrval, int lvl) {
	QString sql = "";
	if ( lvl == 0 ) {
		sql = "SELECT id AS topid FROM "+tbl+"_d_topnode WHERE "+whrval+" AND "+whrtag;
	} else if ( lvl == 1 ) {
		sql = "SELECT topid FROM "+tbl+"_d_secnode WHERE "+whrval+" AND "+whrtag;
	}
	return sql;
}

QString clsXmlWhereLex::mkWhrTopNode() {
	QString whr = "";
	return whr;
}

QString clsXmlWhereLex::mkWhrTopAttr() {
	QString whr = "";
	return whr = "";
}

QString clsXmlWhereLex::mkWhrSecNode() {
	QString whr = "";
	return whr;
}

QString clsXmlWhereLex::mkWhrSecAttr() {
	QString whr = "";
	return whr = "";
}

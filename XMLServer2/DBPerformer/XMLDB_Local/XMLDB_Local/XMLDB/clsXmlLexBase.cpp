/*
 * clsXmlLexBase2.cpp
 *
 *  Created on: 2009/11/28
 *      Author: cony
 */

#include "clsXmlWhereLex.h"

clsXmlLexBase::clsXmlLexBase(QString _buf) {
	srcBuf = _buf;
	buf = _buf.toLocal8Bit();
	nMaxLen = buf.length();
	p = buf.data();
	nStart = 0;
	db = NULL;
}

clsXmlLexBase::~clsXmlLexBase() {
}


bool clsXmlLexBase::getAttr(NPListPack<clsXMLAttrRec> *attrs) {
	// 属性名取得
	debugPrt("start getAttr");
	int nTagLen = nextAttrName();
	if ( nTagLen <= 0 ) return false;
	clsXMLAttrRec *recAttr = new clsXMLAttrRec();
	recAttr->itm = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) return false;
	debugPrt("after attrname");

	// 属性演算子取得
	nTagLen = nextAttrEq();
	if ( nTagLen <= 0 ) return false;
	recAttr->eq = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) return false;
	debugPrt("after attreq");

	// 属性値取得
	if ( *p == '\'' ) {
		if ( nextPt(nTagLen) == false ) return false;
	}
	nTagLen = nextAttrVal();
	if ( nTagLen <= 0 ) return false;
	recAttr->val = getBufMid(nTagLen);
	if ( nextPt(nTagLen+1) == false ) return false;
	debugPrt("after attrval");

	attrs->AppendList(recAttr);
	return true;
}

int clsXmlLexBase::nextTagName() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == ' ' || *pp == '>' ) { // タグ名終了
			break;
		}
		if ( *pp != '<' ) len ++;
		pp++;
	}
	return len;
}

int clsXmlLexBase::nextAttrName() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == '=' || *pp == '<' || *pp == '>' || *pp == '!' ) { // 属性名終了
			break;
		}
		pp++;
		len ++;
	}
	return chkRetLen(len);
}

int clsXmlLexBase::nextAttrNameOut() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == ' ' || *pp == '/' || *pp == '>' ) { // 属性名終了
			break;
		}
		pp++;
		len ++;
	}
	return chkRetLen(len);
}

int clsXmlLexBase::nextAttrEq() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == '\'' || *pp == ' ' ) {
			break;
		}
		pp++;
		len++;
	}
	return chkRetLen(len);
}

int clsXmlLexBase::nextAttrVal() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == '\'' ) {
			break;
		}
		pp++;
		len++;
	}
	return chkRetLen(len);
}

int clsXmlLexBase::nextTagValue() {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == '<' ) {
			break;
		}
		pp++;
		len++;
	}
	return chkRetLen(len);
}

int clsXmlLexBase::chkRetLen(int len) {
	if ( len >= nMaxLen ) {
		errMess = "over flow buffer";
		len = -1;
	}
	if ( len == 0 ) {
		errMess = "not found";
	}
	return len;
}

bool clsXmlLexBase::nextPt(int len) {
	if ( nStart+len >= nMaxLen ) {
		errMess = "over flow buffer";
		return false;
	}
	p += len;
	nStart += len;
	return true;
}

bool clsXmlLexBase::nextStop(char stop) {
	int len = 0;
	char *pp = p;
	while( *pp != 0x00 ) {
		if ( *pp == stop ) {
			break;
		}
		len ++;
		pp ++;
	}
	len = chkRetLen(len);
	if ( len < 0 ) {
		errMess = "stop over flow buffer";
		return false;
	}
	p += len;
	nStart += len;
	return true;
}

QString clsXmlLexBase::getBufMid(int nLen) {
	if ( nLen+nStart >= nMaxLen ) return "";
	return srcBuf.mid(nStart,nLen);
}

QString clsXmlLexBase::mkWhr() {
	QString whr = "";

	if ( whrrec.tag == "" ) {
		return "not where";
	}
	whr = mkAttrWhr("tag",whrrec.tag);
	if ( whrrec.attrs != NULL ) {
		clsXMLAttrRec *recAttr = whrrec.attrs->GetFirst();
		while( recAttr != NULL ) {
			whr += " ("+mkAttrWhr("itm",recAttr->itm)+" AND "+mkAttrValWhr(recAttr->eq,recAttr->val)+")";
			recAttr = recAttr->GetNext();
		}
		whr += " = ["+whrrec.val+"]";
	}

	if ( whrrec.childs != NULL ) {
		clsXMLRec *recChild = whrrec.childs->GetFirst();
		while( recChild != NULL ) {
			whr += "\n";
			whr += mkAttrWhr("tag",recChild->tag);
			if ( recChild->attrs != NULL ) {
				clsXMLAttrRec *recAttr = recChild->attrs->GetFirst();
				while( recAttr != NULL ) {
					whr += " ("+mkAttrWhr("itm",recAttr->itm)+" AND "+mkAttrValWhr(recAttr->eq,recAttr->val)+")";
					recAttr = recAttr->GetNext();
				}
			}
			whr += " = ["+recChild->val+"]";
			recChild = recChild->GetNext();
		}
	}
	return whr;
}

QString clsXmlLexBase::mkAttrWhr(QString itm, QString itmval) {
	QString whr = itm;
	bool likeFlg = false;
	if ( itmval.indexOf('?') >= 0 ) {
		likeFlg = true;
	}
	if ( itmval.indexOf('*') >= 0 ) {
		likeFlg = true;
	}
	if ( likeFlg == false ) {
		return whr+"='"+itmval+"'";
	}
	itmval = itmval.replace("_","\\_");
	itmval = itmval.replace('?','_');
	itmval = itmval.replace('*','%');
	return whr+" LIKE '"+itmval+"'";
}

QString clsXmlLexBase::mkAttrValWhr(QString eq, QString val) {
	if ( eq != "!=" && eq != "==" && eq != "=" ) {
		return "val"+eq+"'"+val+"'";
	}
	bool likeFlg = false;
	if ( val.indexOf('?') >= 0 ) {
		likeFlg = true;
	}
	if ( val.indexOf('*') >= 0 ) {
		likeFlg = true;
	}
	if ( likeFlg == false ) {
		return "val"+eq+"'"+val+"'";
	}
	val = val.replace("_","\\_");
	val = val.replace('?','_');
	val = val.replace('*','%');
	if ( eq == "!=" ) {
		return "NOT val LIKE '"+val+"'";
	}
	return "val LIKE '"+val+"'";
}

QString clsXmlLexBase::mkTagValWhr(QString val) {
	bool likeFlg = false;
	if ( val.indexOf('?') >= 0 ) {
		likeFlg = true;
	}
	if ( val.indexOf('*') >= 0 ) {
		likeFlg = true;
	}
	if ( likeFlg == false ) {
		return "val='"+val+"'";
	}
	val = val.replace("_","\\_");
	val = val.replace('?','_');
	val = val.replace('*','%');
	return "val LIKE '"+val+"'";
}

QString clsXmlLexBase::mkTagWhr(QString val) {
	bool likeFlg = false;
	if ( val.indexOf('?') >= 0 ) {
		likeFlg = true;
	}
	if ( val.indexOf('*') >= 0 ) {
		likeFlg = true;
	}
	if ( likeFlg == false ) {
		return "tag='"+val+"'";
	}
	val = val.replace("_","\\_");
	val = val.replace('?','_');
	val = val.replace('*','%');
	return "tag LIKE '"+val+"'";
}

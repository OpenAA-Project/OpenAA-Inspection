/*
 * clsXmlLexBase2.cpp
 *
 *  Created on: 2009/11/28
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

clsXmlLexBase::clsXmlLexBase(const QByteArray &_buf) {
	srcBuf = _buf;
	nMaxLen = srcBuf.length();
	p = srcBuf.data();
	nStart = 0;
	db = NULL;
}

clsXmlLexBase::~clsXmlLexBase() {
	srcBuf.clear();
	tbl.clear();
}


bool clsXmlLexBase::getAttr(NPListPack<clsXMLAttrRec> *attrs) {
	// 属性名取得
	debugPrt("start getAttr");
	int nTagLen = nextAttrName();
	if ( nTagLen <= 0 ) return false;
	clsXMLAttrRec *recAttr = new clsXMLAttrRec(); //TODO memory clear
	recAttr->itm = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) return false;
	debugPrt("after attrname");

	// 属性演算子取得
	nTagLen = nextAttrEq();
	if ( nTagLen <= 0 ) return false;
	recAttr->eq = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) return false;
	if ( recAttr->eq.length() == 2 ) {
		if ( nextPt(1) == false ) return false;
	}

	// 属性値取得
	if ( *p == '\'' ) {
		if ( nextPt(nTagLen) == false ) return false;
	}
	qDebug() << "itm=["+recAttr->itm+"] eq=["+recAttr->eq+"]";

	nTagLen = nextAttrVal();
	qDebug() << "itm=["+recAttr->itm+"] eq=["+recAttr->eq+"] val=["+recAttr->val+"]";
	if ( nTagLen <= 0 ) return false;
	recAttr->val = getBufMid(nTagLen);
	qDebug() << "itm=["+recAttr->itm+"] eq=["+recAttr->eq+"] val=["+recAttr->val+"]";
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

QByteArray clsXmlLexBase::getBufMid(int nLen) {
	debugPrt("getButMid");
	if ( nLen+nStart >= nMaxLen ) return "";
	return srcBuf.mid(nStart,nLen);
}

QByteArray clsXmlLexBase::mkWhr() {
	QByteArray whr = "";

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

QByteArray clsXmlLexBase::mkAttrWhr(const QByteArray &itm, const QByteArray &itmval) {
	QByteArray whr = itm;
	QByteArray tmp;
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
	tmp = itmval;
	tmp = tmp.replace("_","\\_");
	tmp = tmp.replace('?','_');
	tmp = tmp.replace('*','%');
	return whr+" LIKE '"+tmp+"'";
}

QByteArray clsXmlLexBase::mkAttrValWhr(const QByteArray &eq, const QByteArray &val) {
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
	QByteArray tmp = val;
	tmp = tmp.replace("_","\\_");
	tmp = tmp.replace('?','_');
	tmp = tmp.replace('*','%');
	if ( eq == "!=" ) {
		return "NOT val LIKE '"+tmp+"'";
	}
	return "val LIKE '"+tmp+"'";
}

QByteArray clsXmlLexBase::mkTagValWhr(const QByteArray &val) {
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
	QByteArray tmp = val;
	tmp = tmp.replace("_","\\_");
	tmp = tmp.replace('?','_');
	tmp = tmp.replace('*','%');
	return "val LIKE '"+tmp+"'";
}

QByteArray clsXmlLexBase::mkTagWhr(const QByteArray &val) {
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
	QByteArray tmp = val;
	tmp = tmp.replace("_","\\_");
	tmp = tmp.replace('?','_');
	tmp = tmp.replace('*','%');
	return "tag LIKE '"+tmp+"'";
}

bool clsXmlLexBase::bndSplit(const QByteArray &rep, const QByteArray &src, QList<QByteArray> &lst) {
	int nStr = 0;
	lst.clear();
	while( 1 ) {
		QByteArray tmp;
		int idx = src.indexOf(rep,nStr);
		if ( idx < 0 ) break;
		tmp = src.mid(nStr,(idx-nStr));
		lst << tmp;
		nStr = idx+1;
	}
	if ( lst.size() <= 0 ) {
		return false;
	}
	return true;
}

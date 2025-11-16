/*
 * clsXmlOutLex.cpp
 *
 *  Created on: 2009/11/27
 *      Author: cony
 */
#include "clsXmlWhereLex.h"

#include <QRegularExpression>
#include <QDebug>

clsXmlOutLex::clsXmlOutLex(QString _buf) :clsXmlLexBase(_buf) {
	bFullFlg = false;
	whrrec.childs = new NPListPack<clsXMLRec>();
	whrrec.attrs = new NPListPack<clsXMLAttrRec>();
	mkXMLRec();
}

clsXmlOutLex::~clsXmlOutLex() {
	// TODO Auto-generated destructor stub
}

void clsXmlOutLex::mkXMLRec() {
	if ( srcBuf.trimmed() == "*" ) {
		bFullFlg = true;
		return;
	}
	errMess = "";
	if ( *p != '<' ) {
		errMess = "Not Tag Format";
		return;
	}

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
			printf("bat format\n");
			return;
		}
		if ( nextPt(1) == false ) return;
		nTagLen = nextTagName();
		if ( nTagLen <= 0 ) return;
		clsXMLRec *recChild = new clsXMLRec();
		recChild->tag = getBufMid(nTagLen);
		qDebug() << "get child tag=["+recChild->tag+"]";
		whrrec.childs->AppendList(recChild);
		if ( nextPt(nTagLen) == false ) return;
		if ( *p == ' ' ) {
			// 子属性取得
			if ( nextPt(1) == false ) return;
			while( *p != 0x00 ) {
				debugPrt("start child attr");
				if ( recChild->attrs == NULL ) {
					recChild->attrs = new NPListPack<clsXMLAttrRec>();
				}
				if ( getAttr(recChild->attrs) == false ) {
					return;
				}
				if ( *p == '>' ) {
					if ( nextPt(1) == false ) return;
					break;
				}
				debugPrt("start child attr1");
				if ( *p == '/' && *(p+1) == '>' ) {
					if ( nextPt(2) == false ) return;
					break;
				}
				debugPrt("start child attr2");
				if ( *p == ' ' ) {
					if ( nextPt(1) == false ) return;
					continue;
				}
				errMess = "bad format:"+buf;
				return;
			}
			debugPrt("end child attr");
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

bool clsXmlOutLex::getAttr(NPListPack<clsXMLAttrRec> *attrs) {
	// 属性名取得
	debugPrt("start getAttr");
	int nTagLen = nextAttrNameOut();
	if ( nTagLen < 0 ) return false;
	if ( nTagLen == 0 ) return true;
	clsXMLAttrRec *recAttr = new clsXMLAttrRec();
	recAttr->itm = getBufMid(nTagLen);
	if ( nextPt(nTagLen) == false ) return false;
	debugPrt("after attrname");

	recAttr->eq = "";
	recAttr->val = "";
	attrs->AppendList(recAttr);
	return true;
}

QString clsXmlOutLex::whrSecOutTag() {
	if ( bFullFlg == true ) {
		return "";
	}
	QString whr = "";
	if ( whrrec.childs == NULL ) {
		return "";
	}
	clsXMLRec *recChild = whrrec.childs->GetFirst();
	while( recChild != NULL ) {
		if ( recChild->tag != "NGP" && recChild->tag != "NGI" ) {
		if ( whr != "" ) whr += " OR ";
		whr += mkTagWhr(recChild->tag);
		}
		recChild = recChild->GetNext();
	}
	return "("+whr+")";
}

bool clsXmlOutLex::isOutTag(QString tag) {
	if ( bFullFlg == true ) {
		return true;
	}
	bool flg = false;
	if ( whrrec.tag == tag ) {
		return true;
	}
	if ( whrrec.childs != NULL ) {
		clsXMLRec *recChild = whrrec.childs->GetFirst();
		while( recChild != NULL ) {
			if ( recChild->tag.indexOf("*") >= 0 || recChild->tag.indexOf("?") >= 0 ) {
				QRegularExpression rx(recChild->tag);
				rx.setPatternSyntax(QRegularExpression::Wildcard);
				if ( rx.indexIn(tag) == 0 ) {
					flg = true;
					break;
				}
			} else {
				if ( recChild->tag == tag ) {
					flg = true;
					break;
				}
			}
			recChild = recChild->GetNext();
		}
		return flg;
	}
	return false;
}

bool clsXmlOutLex::isOutTagAttr(QString tag, QString attr) {
	if ( bFullFlg == true ) {
		return true;
	}
	bool flg = false;
	if ( whrrec.tag == tag ) {
		if ( isTagInAttr(&whrrec,attr) == false ) {
			return false;
		}
		return true;
	}
	if ( whrrec.childs != NULL ) {
		clsXMLRec *recChild = whrrec.childs->GetFirst();
		while( recChild != NULL ) {
			if ( recChild->tag.indexOf("*") >= 0 || recChild->tag.indexOf("?") >= 0 ) {
				QRegularExpression rx(recChild->tag);
				rx.setPatternSyntax(QRegularExpression::Wildcard);
				if ( rx.indexIn(tag) == 0 ) {
					if ( isTagInAttr(recChild,attr) == true ) {
						flg = true;
						break;
					}
				}
			} else {
				if ( recChild->tag == tag ) {
					if ( isTagInAttr(recChild,attr) == true ) {
						flg = true;
						break;
					}
				}
			}
			recChild = recChild->GetNext();
		}
		return flg;
	}
	return false;
}

bool clsXmlOutLex::isTagInAttr(clsXMLRec *rec, QString attr) {
	bool flg = false;
	if ( rec->attrs == NULL ) {
		return false;
	}
	clsXMLAttrRec *recAttr = rec->attrs->GetFirst();
	while( recAttr != NULL ) {
		if ( recAttr->itm.indexOf("*") >= 0 || recAttr->itm.indexOf("?") >= 0 ) {
			QRegularExpression rx(recAttr->itm);
			rx.setPatternSyntax(QRegularExpression::Wildcard);
			if ( rx.indexIn(attr) == 0 ) {
				flg = true;
				break;
			}
		} else {
			if ( recAttr->itm == attr ) {
				flg = true;
				break;
			}
		}

		recAttr = recAttr->GetNext();
	}
	return flg;
}

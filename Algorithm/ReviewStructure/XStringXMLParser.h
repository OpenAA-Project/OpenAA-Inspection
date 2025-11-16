#pragma once

#include <QtXml/QDomElement>

// QString を扱うXML文のパーサーの基底クラス
// 継承先でanalyzeを定義し、格納するデータに応じてメンバ変数を持たせる

class StringXMLParser
{
public:
	StringXMLParser():errMsg(/**/""){};
	virtual ~StringXMLParser(){};

public:
	bool isError(){ return !errMsg.isEmpty(); };
	QString getErrorMessage(){ return errMsg; };
	bool setContent(const QString &src){
		clear();

		QDomDocument doc;
		if(doc.setContent(src)==false)
			return false;

		QDomElement elem = doc.documentElement();

		analyze(elem);

		return errMsg.isEmpty();
	};

public:
	virtual void analyze(QDomElement &elem)=0;
	virtual void clear(){ errMsg.clear(); };
	static QString getCurrentTagText(const QDomElement &elem){
		return elem.firstChild().toText().data();
	};

protected:
	QString errMsg;
};

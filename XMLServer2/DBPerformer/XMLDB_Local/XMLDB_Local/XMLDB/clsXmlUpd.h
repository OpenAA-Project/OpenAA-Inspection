/*
 * clsXmlUpd.h
 *
 *  Created on: 2009/11/20
 *      Author: cony
 */

#ifndef CLSXMLUPD_H_
#define CLSXMLUPD_H_

#include <QObject>
#include <QIODevice>
#include <QDomElement>
#include <QDomDocument>
#include <QStringList>

#include "clsDb.h"
#include "clsXmlWhereLex.h"
#include "clsXmlReadSql.h"

class clsXmlUpd {
public:
	clsXmlUpd();
	virtual ~clsXmlUpd();

	clsXmlReadSql *readSql;

	bool lexSelSql(QString sql);
	bool lexUpdSql(QString sql);

	bool parse(QString buf);
	bool addXml();
	bool appendXml();
	bool deleteXml();

	bool searchXml(int idx=-1);
	QStringList lstResult;
	QStringList lstResultId;
	int nResCnt;

	bool readXml(QString topid);
	QString toString();

	QString errMess;
	clsDb *db;

	QString mkWhere(QString whrbuf);
	QString mkSelSql(QString whrbuf);

	void clearObj();

private:
	QDomDocument *doc;

	QString topid;
	QString chldid;
	bool addAttr(QDomNamedNodeMap lst, int lvl);
	bool addChildNode(int srt,QDomNode node);

	void clearDoc();
	void clearSql();

	bool getChildTagAttr(QString topid, QString tag, QDomElement &child);
};

#endif /* CLSXMLUPD_H_ */

/*
 * clsXmlReadSql.h
 *
 *  Created on: 2009/12/09
 *      Author: cony
 */

#ifndef CLSXMLREADSQL_H_
#define CLSXMLREADSQL_H_

#include <QObject>
#include <QString>
#include "clsXmlWhereLex.h"
#include "clsDb.h"

class clsXmlReadSql {
public :
	clsXmlReadSql(clsDb *_db, QString sql,bool uflg=false);
	~clsXmlReadSql();

	clsXmlOutLex *outWhr;
	clsXmlWhereLex *selWhr;
	clsXmlOrderLex *odrWhr;
	QString insXml;
	QString tbl;
	bool err;

	QString debugStr();
	bool isOutTag(QString tag) {
		return outWhr->isOutTag(tag);
	}
	bool isOutTagAttr(QString tag, QString attr) {
		return outWhr->isOutTagAttr(tag,attr);
	}

	clsDb *db;

private:
	void lexSql(QString sql);
	void lexUpdSql(QString sql);
	QString getOutWhr(QString sql);
	QString getTable(QString sql);
	QString getWhere(QString sql);
	QString getOrder(QString sql);
};

#endif /* CLSXMLREADSQL_H_ */

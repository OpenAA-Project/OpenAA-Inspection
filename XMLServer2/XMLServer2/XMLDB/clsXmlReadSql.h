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

/**
 * @brief SQL•¶ƒNƒ‰ƒX
 */
class clsXmlReadSql {
public :
	clsXmlReadSql(clsDb *_db, const QByteArray &sql,bool uflg=false);
	~clsXmlReadSql();

	clsXmlOutLex *outWhr;
	clsXmlWhereLex *selWhr;
	clsXmlOrderLex *odrWhr;
	QByteArray insXml;
	QByteArray tbl;
	bool err;

	QByteArray debugStr();
	bool isOutTag(const QByteArray &tag) {
		return outWhr->isOutTag(tag);
	}
	bool isOutTagAttr(const QByteArray &tag, const QByteArray &attr) {
		return outWhr->isOutTagAttr(tag,attr);
	}

	clsDb *db;

private:
	void lexSql(const QByteArray &sql);
	void lexUpdSql(const QByteArray &sql);
	QByteArray getOutWhr(const QByteArray &sql);
	QByteArray getTable(const QByteArray &sql);
	QByteArray getWhere(const QByteArray &sql);
	QByteArray getOrder(const QByteArray &sql);
};

#endif /* CLSXMLREADSQL_H_ */

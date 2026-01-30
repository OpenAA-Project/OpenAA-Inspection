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
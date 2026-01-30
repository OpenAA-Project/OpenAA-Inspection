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

/**
 * @brief SQL���N���X
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
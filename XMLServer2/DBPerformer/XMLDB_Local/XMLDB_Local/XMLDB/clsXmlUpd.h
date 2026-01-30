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
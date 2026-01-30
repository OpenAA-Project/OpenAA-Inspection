/*
 * Copyright (C) 2021
 * Author : Masatoshi Sasai ,MEGATRADE corporation
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

#ifndef XMLDB_LOCAL_H
#define XMLDB_LOCAL_H

#include <QWidget>
#include "ui_xmldb_local.h"

#include <QObject>
#include <QString>
#include <QStringList>
#include <QTime>

#include "clsXmlUpd.h"
#include "clsDb.h"

class XMLDB_Local : public QWidget
{
    Q_OBJECT

public:
    XMLDB_Local(QWidget *parent = 0);
    ~XMLDB_Local();

private slots:
	void exitApp();
	void selInspect();
	void selLot();

private:
    Ui::XMLDB_LocalClass ui;

	clsXmlUpd *objXml;
	clsDb *db;

    void makeObj();
    void cleanObj();

    QString mkSelectInspectSql(QString eid);

    QByteArray buf;

    void messError(QString tit, QString mess);

	double dRes;
	double dMax;
	double dMin;
	double dAvg;
	double dErr;
	double dSum;
	double dCnt;
	
	void clearTime(bool flg);
	void calcTime();
	void drawRes();
	int nRow;

	QTime curTim;
	void timeStart();
	void timeEnd();
};

#endif // XMLDB_LOCAL_H
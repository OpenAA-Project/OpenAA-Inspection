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


#ifndef CLSMAKEDAT_H_
#define CLSMAKEDAT_H_

#include <QObject>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QThread>
#include <math.h>
#include "clsDb.h"
#include "clsRand.h"

class clsMakeDat : public QThread {
	Q_OBJECT
public:
	clsMakeDat(QString _no, QObject *par=0);
	virtual ~clsMakeDat();

	void setKeyVal(QString _LotId, QString _Eid, QString _ver, QString dbNam);
	bool mkData(int nCnt, int nNgpCnt, int nNgiCnt);

	void run();

	QString thrNo;

	double dRes;
	double dMax;
	double dMin;
	double dAvg;
	double dErr;
	double dSum;
	double dCnt;

signals:
	void drawMess(QString mess,bool bWait);

private:
	bool mkIst();
	bool mkNGP();
	bool mkNGI();

	int nCnt;
	int nNgpCnt;
	int nNgiCnt;

	QString LotID;
	int nStartEID;
	int nCurEID;
	QString ver;
	QString curTopid;

	QString mess;
	void sndMess(QString _mess);

	clsDb *db;
	clsLog *log;
	QString dbFile;

	QString mkDate(int flg);
	QDateTime curTim;

	void clearTime(bool flg);
	void calcTime();

	QTime curTim1;
	void timeStart();
	void timeEnd();
};

#endif /* CLSMAKEDAT_H_ */
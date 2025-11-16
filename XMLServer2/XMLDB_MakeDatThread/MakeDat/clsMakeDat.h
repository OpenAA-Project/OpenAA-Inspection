/*
 * clsMakeDat.h
 *
 *  Created on: 2009/12/30
 *      Author: cony
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

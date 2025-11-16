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
	clsMakeDat(QObject *par=0);
	virtual ~clsMakeDat();

	void setKeyVal(QString _LotId, QString _Eid, QString _ver, QString dbNam);
	bool mkData(int nCnt, int nNgpCnt, int nNgiCnt);

	void run();

signals:
	void drawMess(QString mess);
	void updLotID(QString lid);

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
};

#endif /* CLSMAKEDAT_H_ */

#ifndef CLSEXECINS_H
#define CLSEXECINS_H

#include <QThread>
#include <QMutex>
#include <QTime>

#include "clsDb.h"

class clsExecIns : public QThread
{
	Q_OBJECT

public:
	clsExecIns(int cnt, QObject *parent);
	~clsExecIns();

	void run();

	double dMax;
	double dMin;
	double dAvg;
	double dErr;
	double dSum;

	double dStartX;
	double dStartY;

signals:
	void drawExecAns(double,double,double,double,double,int);

private:
	clsDb *db;
	int nExecCnt;
	int nCurCnt;

	double dTime;

	bool addTag();
	QTime curTim;
	void timeStart();
	void timeEnd();
};

#endif // CLSEXECINS_H

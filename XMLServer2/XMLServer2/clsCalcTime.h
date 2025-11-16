/*
 * clsCalcTime.h
 *
 *  Created on: 2010/02/07
 *      Author: cony
 */

#ifndef CLSCALCTIME_H_
#define CLSCALCTIME_H_

#include <QTime>

class clsCalcTime {
public:
	clsCalcTime();
	virtual ~clsCalcTime();

	void timeStart();
	void timeEnd();
	double dResTime;

private:
	QTime curTim;
};

class clsDbResTime {
public:
	clsDbResTime();
	virtual ~clsDbResTime();

	void startTime(bool bflg=false);
	void endTime(int idx);

	void wrtTimeLog(int port);

private:
	double dRes1;
	double dRes2;
	double dRes3;
	double dRes4;

	clsCalcTime *obj;
};
#endif /* CLSCALCTIME_H_ */

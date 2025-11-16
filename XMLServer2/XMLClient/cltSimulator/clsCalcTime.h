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

#endif /* CLSCALCTIME_H_ */

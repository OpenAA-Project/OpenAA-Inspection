/*
 * clsTimeOut.h
 *
 *  Created on: 2009/11/07
 *      Author: cony
 */

#ifndef CLSTIMEOUT_H_
#define CLSTIMEOUT_H_

#include <QObject>
#include <QDateTime>

class clsTimeOut : public QObject {
	Q_OBJECT
public:
	clsTimeOut(QObject *_par=0);
	virtual ~clsTimeOut();

	bool timeOutStart(int sec);
	bool chkTimeOut();

private:
	QDateTime startTime;
	int nTimeOutSec;
};

#endif /* CLSTIMEOUT_H_ */

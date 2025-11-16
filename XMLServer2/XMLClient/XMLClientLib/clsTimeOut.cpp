/*
 * clsTimeOut.cpp
 *
 *  Created on: 2009/11/07
 *      Author: cony
 */

#include "clsTimeOut.h"

clsTimeOut::clsTimeOut(QObject *_par) : QObject(_par) {
}

clsTimeOut::~clsTimeOut() {
}

bool clsTimeOut::timeOutStart(int sec) {
	nTimeOutSec = sec;
	startTime = QDateTime::currentDateTime();
	return true;
}

bool clsTimeOut::chkTimeOut() {
	QDateTime cur = QDateTime::currentDateTime();
	if ( startTime.secsTo(cur) > nTimeOutSec ) {
		return true;
	}
	return false;
}

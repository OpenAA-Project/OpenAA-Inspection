/*
 * clsCalcTime.cpp
 *
 *  Created on: 2010/02/07
 *      Author: cony
 */

#include "clsCalcTime.h"

clsCalcTime::clsCalcTime() {
}

clsCalcTime::~clsCalcTime() {
}

void clsCalcTime::timeStart() {
	curTim.start();
}

void clsCalcTime::timeEnd() {
	int n = curTim.elapsed();
	dResTime = (double)n/1000.0;
}

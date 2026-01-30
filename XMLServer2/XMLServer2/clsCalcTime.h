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
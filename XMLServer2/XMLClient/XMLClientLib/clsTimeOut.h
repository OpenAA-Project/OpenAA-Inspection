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
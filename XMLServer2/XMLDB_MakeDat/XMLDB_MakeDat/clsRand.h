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


#ifndef CLSRAND_H_
#define CLSRAND_H_

#include <QObject>
#include <QString>
#include <math.h>
#include <time.h>
#include <stdlib.h>

class clsRand : public QObject {
	Q_OBJECT
public:
	clsRand(QObject *par=0);
	virtual ~clsRand();

	QString mkRand(int nMax=10000);
	bool mkRandAxis(QString &x, QString &y);

	bool flg;
};

#endif /* CLSRAND_H_ */
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


#include "clsRand.h"

clsRand::clsRand(QObject *par) : QObject(par) {
	srand((unsigned)time(NULL));
	flg = false;
}

clsRand::~clsRand() {
	// TODO Auto-generated destructor stub
}

QString clsRand::mkRand(int nMax) {
	int n = rand() % nMax;
	QString rns = QString::number(n);
	return rns;
}

bool clsRand::mkRandAxis(QString &x, QString &y) {
	if ( flg == true ) {
		int xx = x.toInt();
		x = QString::number(xx+1);
		int yy = y.toInt();
		y = QString::number(yy+1);
	}
	x = mkRand();
	y = mkRand();
	flg = true;
	return true;
}
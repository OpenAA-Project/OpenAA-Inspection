/*
 * clsRand.cpp
 *
 *  Created on: 2009/12/30
 *      Author: cony
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

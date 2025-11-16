/*
 * clsRand.h
 *
 *  Created on: 2009/12/30
 *      Author: cony
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

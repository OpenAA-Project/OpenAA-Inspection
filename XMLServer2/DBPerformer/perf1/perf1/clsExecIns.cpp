/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
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

#include "clsExecIns.h"

#include <QDebug>
#include <QFile>
#include <QIODevice>

#define DRAWCNT 10

clsExecIns::clsExecIns(int cnt, QObject *parent)
	: QThread(parent)
{
	nExecCnt = cnt;
	dStartX = 1.0;
	dStartY = 1.0;
	db = new clsDb();
}

clsExecIns::~clsExecIns()
{
	if ( db != NULL ) {
		delete(db);
	}
}

void clsExecIns::run() {
	dMax = 0.0;
	dMin = 999.0;
	dAvg = 0.0;
	dErr = 0.0;
	dSum = 0.0;
	nCurCnt = 0;
	emit drawExecAns(dMax,0.0,0.0,0.0,dErr,0);

	db->setPrm();
	db->Connect();
	db->setTable("test2");

	for( int i=0; i<nExecCnt; i++ ) {
		bool bExecFlg = true;
		db->beginTran();
		bExecFlg = addTag();
		db->endTran(bExecFlg);

		if ( bExecFlg == false ) {
			dErr += 1.0;
		}
		if ( dTime > dMax ) {
			dMax = dTime;
		}
		if ( dTime < dMin ) {
			dMin = dTime;
		}
		dSum += dTime;
		qDebug() << "dSum=["+QString::number(dSum,'f',2)+"]/"+QString::number(nCurCnt)+"]";
		dAvg = dSum / nCurCnt;

		if ( i % DRAWCNT == 0 && i > 0 ) { 
			emit drawExecAns(dMax,dMin,dAvg,dSum,dErr,nCurCnt);
		}
		nCurCnt ++;
	}
	db->DisConnect();

	emit drawExecAns(dMax,dMin,dAvg,dSum,dErr,nCurCnt);
}

bool clsExecIns::addTag() {
	bool ret = true;
	QString parid = "";
	timeStart();
	ret = db->addSecNode(1,"-1","TESTNGP","",parid);
	if ( ret == false ) {
		qDebug() << "node ins error:"+db->mess;
		timeEnd();
		return false;
	}
	ret = db->addSecAttr(1,"-1",parid,"X",QString::number(dStartX,'f',2));
	if ( ret == false ) {
		qDebug() << "node attr X ins error:"+db->mess;
		timeEnd();
		return false;
	}
	ret = db->addSecAttr(1,"-1",parid,"Y",QString::number(dStartY,'f',2));
	if ( ret == false ) {
		qDebug() << "node attr Y ins error:"+db->mess;
		timeEnd();
		return false;
	}
	dStartX += 1.0;
	dStartY += 1.0;
	timeEnd();
	return true;
}

void clsExecIns::timeStart() {
	curTim.start();
}

void clsExecIns::timeEnd() {
	int n = curTim.elapsed();
	qDebug() << "time =["+QString::number(n)+"]";
	dTime = (double)n/1000.0;
	qDebug() << "dtime=["+QString::number(dTime,'f',3)+"]";

	QFile file("C:\\Data\\XMLServerLog\\time.log");
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		qDebug() << "error file";
		return;
	}
	QTextStream out(&file);
	out << QString::number(dTime,'f',3)+"\n";
	file.close();
}
/*
 * clsMakeDat.cpp
 *
 *	Created on: 2009/12/30
 *		Author: cony
 */

#include "clsMakeDat.h"

#define MESSCNT 10

clsMakeDat::clsMakeDat(QString no, QObject *par) : QThread(par) {
	mess = "";
	thrNo = no;
	db = NULL;
}

clsMakeDat::~clsMakeDat() {
	if ( db != NULL ) {
		delete(db);
	}
}

void clsMakeDat::setKeyVal(QString _LotId, QString _Eid, QString _ver, QString dbNam) {
	LotID = _LotId;
	nStartEID = _Eid.toInt();
	ver = _ver;
	dbFile = dbNam;
	/*
	db = new clsDb();
	db->setPrm();
	log = new clsLog();
	db->log = log;
	log->startLog("0");
	*/
}

bool clsMakeDat::mkData(int _nCnt, int _nNgpCnt, int _nNgiCnt) {
	qDebug() << "mkData("+thrNo+")=("+QString::number(_nCnt)+","+QString::number(_nNgpCnt)+")";
	nCnt = _nCnt;
	nNgpCnt = _nNgpCnt;
	nNgiCnt = _nNgiCnt;

	start();
	return true;
}

void clsMakeDat::run() {
	clearTime(true);
	db = new clsDb();
	db->setPrm(dbFile);
	log = new clsLog();
	db->log = log;
	log->startLog(thrNo);

	nCurEID = nStartEID;
	qDebug() << "threadNo=["+thrNo+"]";

	if ( db->Connect(thrNo) == false ) {
		sndMess("Connect:");
		return;
	}
	qDebug() << "threadNo=["+thrNo+"] Connected";
	qDebug() << "exec Cnt["+thrNo+"]=["+QString::number(nCnt)+"]";
	db->setTable("PPP1");
	//db->endTran(false);
	db->makePrepare();

	for( int i=0; i<nCnt; i++ ) {
		timeStart();
		db->beginTran();
		db->makePrepare();
		log->log("start IST",clsLog::CLSLOG_DEBUG);
		if ( mkIst() == false ) {
			sndMess("mkIst:");
			db->endTran(false);
			db->DisConnect();
			return;
		}
		log->log("start NGP",clsLog::CLSLOG_DEBUG);
		for( int j=0; j<nNgpCnt; j++ ) {
			if ( mkNGP() == false ) {
				sndMess("mkNGP:");
				db->endTran(false);
				db->DisConnect();
				return;
			}
		}
		log->log("start NGI",clsLog::CLSLOG_DEBUG);
		for( int k=0; k<nNgiCnt; k++ ) {
			if ( mkNGI() == false ) {
				sndMess("mkNGI:");
				db->endTran(false);
				db->DisConnect();
				return;
			}
		}
		log->log("end IST",clsLog::CLSLOG_DEBUG);
		db->endTran(true);
		timeEnd();
		calcTime();
		nCurEID++;

		if ( i % 10 == 0 ) {
			QString dmess = "Make Count=["+QString::number(i)+"]";
			emit drawMess(dmess,false);
		}
	}
	db->DisConnect();
	dAvg = dSum / dCnt;
	emit drawMess("Complete:"+QString::number(nCnt),true);
}

bool clsMakeDat::mkIst() {
	curTopid = "";
	if ( db->addTopNode(1,"IST",curTopid) == false ) {
		mess = "IST:TopNode:"+db->mess;
		return false;
	}
	if ( db->addTopAttr(1,curTopid,"DAY",mkDate(0)) == false ) {
		mess = "IST:DAY Attr:"+db->mess;
		return false;
	}
	if ( db->addTopAttr(2,curTopid,"NGJ","NGImage/"+mkDate(1)+"/"+mkDate(2)+"-*.jdt") == false ) {
		mess = "IST:NGJ Attr:"+db->mess;
		return false;
	}
	if ( db->addTopAttr(3,curTopid,"MAC","0") == false ) {
		mess = "IST:MAC Attr:"+db->mess;
		return false;
	}
	QString nid = "";
	if ( db->addSecNode(1,curTopid,"TIM",mkDate(3),nid) == false ) {
		mess = "IST:TIM Node:"+db->mess;
		return false;
	}
	if ( db->addSecNode(2,curTopid,"VSN",ver,nid) == false ) {
		mess = "IST:VSN Node:"+db->mess;
		return false;
	}
	if ( db->addSecNode(3,curTopid,"MNM",ver,nid) == false ) {
		mess = "IST:VSN Node:"+db->mess;
		return false;
	}
	if ( db->addSecAttr(1,curTopid,nid,"MID","80") == false ) {
		mess = "IST:MNM MID Attr:"+db->mess;
		return false;
	}
	if ( db->addSecNode(4,curTopid,"LOT",LotID,nid) == false ) {
		mess = "IST:LOT Node:"+db->mess;
		return false;
	}
	if ( db->addSecAttr(1,curTopid,nid,"LID",LotID) == false ) {
		mess = "IST:LOT LID Attr:"+db->mess;
		return false;
	}
	if ( db->addSecNode(5,curTopid,"INSPECT","",nid) == false ) {
		mess = "IST:INSPECT Node:"+db->mess;
		return false;
	}
	if ( db->addSecAttr(1,curTopid,nid,"EID",QString::number(nCurEID)) == false ) {
		mess = "IST:INSPECT EID Attr:"+db->mess;
		return false;
	}
	return true;
}

bool clsMakeDat::mkNGP() {
	QString nid = "";
	if ( db->addSecNode(1,curTopid,"NGP","",nid) == false ) {
		mess = "IST:INSPECT Node:"+db->mess;
		return false;
	}
	QString x = "";
	QString y = "";
	//int nNo = 1;

	clsRand objRand;
	objRand.mkRandAxis(x,y);
	QStringList lstAttr;

	/*
	if ( db->addSecAttr(nNo,curTopid,nid,"X",x) == false ) {
		mess = "NGP:X Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"Y",y) == false ) {
		mess = "NGP:Y Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"MX",x) == false ) {
		mess = "NGP:MX Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"MY",y) == false ) {
		mess = "NGP:MY Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"HX",x) == false ) {
		mess = "NGP:HX Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"HY",y) == false ) {
		mess = "NGP:HY Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"RS1",x) == false ) {
		mess = "NGP:RS1 Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"RS2",y) == false ) {
		mess = "NGP:RS2 Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"RAL","Basic:ColorBlockInspection") == false ) {
		mess = "NGP:RS2 Attr:"+db->mess;
		return false;
	}
	nNo ++;
	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"PG",x) == false ) {
		mess = "NGP:PG Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"LY",y) == false ) {
		mess = "NGP:LY Attr:"+db->mess;
		return false;
	}
	*/

	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	lstAttr.append("Basic:ColorBlockInspection");
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);

	if ( db->addNgpAttr(curTopid,nid,lstAttr) == false ) {
		mess = "NGP:Attr:"+db->mess;
		return false;
	}
	return true;
}

bool clsMakeDat::mkNGI() {
	QString nid = "";
	if ( db->addSecNode(1,curTopid,"NGI","",nid) == false ) {
		mess = "IST:INSPECT Node:"+db->mess;
		return false;
	}
	QString x = "";
	QString y = "";
	QStringList lstAttr;
	//int nNo = 1;

	clsRand objRand;
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	objRand.mkRandAxis(x,y);
	lstAttr.append(x);
	lstAttr.append(y);
	if ( db->addNgiAttr(curTopid,nid,lstAttr) == false ) {
		mess = "NGP:Attr:"+db->mess;
		return false;
	}
	return true;

	/*
	if ( db->addSecAttr(nNo,curTopid,nid,"X",x) == false ) {
		mess = "NGP:X Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"Y",y) == false ) {
		mess = "NGP:Y Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"W",x) == false ) {
		mess = "NGP:W Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"H",y) == false ) {
		mess = "NGP:H Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"HX",x) == false ) {
		mess = "NGP:HX Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"HY",y) == false ) {
		mess = "NGP:HY Attr:"+db->mess;
		return false;
	}
	nNo ++;

	objRand.mkRandAxis(x,y);
	if ( db->addSecAttr(nNo,curTopid,nid,"IDX",x) == false ) {
		mess = "NGP:IDX Attr:"+db->mess;
		return false;
	}
	nNo ++;
	if ( db->addSecAttr(nNo,curTopid,nid,"Index",y) == false ) {
		mess = "NGP:Index Attr:"+db->mess;
		return false;
	}
	*/
}

void clsMakeDat::sndMess(QString _mess) {
	emit drawMess(_mess+":"+mess,true);
}

QString clsMakeDat::mkDate(int flg) {
	if ( flg == 0 ) {
		curTim = QDateTime::currentDateTime();
	}
	QString tmp = "";
	switch( flg ) {
	case 0:
		tmp = curTim.toString("yyMMddhhmmss");
		break;
	case 1:
		tmp = curTim.toString("yyMMdd-hh");
		break;
	case 2:
		tmp = curTim.toString("mmss");
		break;
	case 3:
		tmp = curTim.toString("yy/MM/dd hh:mm:ss");
		break;
	}
	return tmp;
}

void clsMakeDat::timeStart() {
	curTim1.start();
}

void clsMakeDat::timeEnd() {
	int n = curTim1.elapsed();
	qDebug() << "time =["+QString::number(n)+"]";
	dRes = (double)n/1000.0;
	qDebug() << "dtime=["+QString::number(dRes,'f',3)+"]";

	clsParam *prm = clsParam::GetInstance();
	QFile file(prm->logDir+"/makedat_"+thrNo+".log");
	if ( file.open(QIODevice::Append|QIODevice::Text) == false ) {
		qDebug() << "error file";
		return;
	}
	QTextStream out(&file);
	out << QString::number(dRes,'f',3)+"\n";
	file.close();
}

void clsMakeDat::calcTime() {
	if ( dRes > dMax ) {
		dMax = dRes;
	}
	if ( dRes < dMin ) {
		dMin = dRes;
	}
	dSum += dRes;
	dCnt += 1.0;
}

void clsMakeDat::clearTime(bool flg) {
	dRes = 0.0;
	if ( flg == true ) {
		dMax = 0.0;
		dMin = 9999.0;
		dAvg = 0.0;
		dErr = 0.0;
		dSum = 0.0;
		dCnt = 0.0;
	}
}



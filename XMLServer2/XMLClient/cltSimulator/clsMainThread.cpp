/*
 * clsMainThread.cpp
 *
 *	Created on: 2010/02/04
 *		Author: cony
 */

#include "clsMainThread.h"
#include "cltSimulator.h"
#include "clsCalcTime.h"
#include "clsLog.h"
#include <QDateTime>

clsMainThread::clsMainThread(QObject *_par) : QThread(_par) {
	par = _par;
	nArrCnt = 0;
	arrThr = NULL;
}

clsMainThread::~clsMainThread() {
	// TODO Auto-generated destructor stub
}

void clsMainThread::clearThr() {
	if ( arrThr != NULL ) {
		for( int i=0; i<nArrCnt; i++ ) {
			delete(arrThr[i]);
		}
	}
	delete(arrThr);
}

void clsMainThread::run() {
	clearThr();
	if ( nThrCnt <= 0 ) return;
	arrThr = new clsExecThread*[nThrCnt];
	nArrCnt = nThrCnt;
	cltSimulator *obj = (cltSimulator *)par;
	clsLog *log = new clsLog();
	for( int i=0; i<nArrCnt; i++ ) {
		arrThr[i] = new clsExecThread(i,this);
		connect(arrThr[i],SIGNAL(setCntThr(int,int,double)),obj,SLOT(setCntThr(int,int,double)),Qt::QueuedConnection);
		arrThr[i]->svr = svr;
		arrThr[i]->port = port;
		arrThr[i]->WaitTime = WaitTime;
		arrThr[i]->nLid = nLotId;
		arrThr[i]->nNgCnt = nNgCnt/nThrCnt;
		arrThr[i]->logDir = logDir;
	}
	log->startLog("main");

	handle = XML_Connect(svr,port,WaitTime);
	if ( handle == NULL ) {
		emit showMess("Connect Error");
		return;
	}
	clsCalcTime objTime;
	log->log("curPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);

	int nEid = nStartEid;
	for( int n=0; n<nExecCnt; n++ ) {
		QDateTime curDay = QDateTime::currentDateTime();
		QString tmp;
		QString cday = curDay.toString("yyMMddhhmmss");
		double dSum = 0;
		objTime.timeStart();
		tmp = "<IST DAY=\""+cday+"\" NGJ=\"NGImage/080312-09/5642-*.jdt\" MAC=\"0\">";
		tmp += "<TIM>"+curDay.toString("yy/MM/dd hh:mm:ss")+"</TIM>";
		tmp += "<VSN>2007.3.31A</VSN>";
//		tmp += "<MNM MID=\"10\">data01-B</MNM>";
		tmp += "<MNM MID=\"100\">data01-B</MNM>";
		tmp += "<INSPECT EID=\""+QString::number(nEid)+"\"></INSPECT>";
		tmp += "<LOT LID=\""+QString::number(nLotId)+"\">"+QString::number(nLotId)+"</LOT>";

// v
		tmp += "<OKAMURA KOUTAROU=\"100\">KOUTAROU-OKAMURA</OKAMURA>";
// ^

//		tmp += "</IST> FROM PPP";
		tmp += "</IST> FROM ZZZ";
		log->log("svrPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);
		log->log(tmp,clsLog::CLSLOG_DEBUG);
		if ( XML_Insert(handle,tmp) == false ) {
			log->log("XML_Insert Error:"+handle->getErrorMess(),clsLog::CLSLOG_DEBUG);
			emit showMess("create IST Error");
			XML_Close(handle);
			return;
		}
		objTime.timeEnd();
		emit setTime(0,objTime.dResTime);
		dSum += objTime.dResTime;

		objTime.timeStart();
		for( int i=0; i<nArrCnt; i++ ) {
			arrThr[i]->nEid = nEid;
			arrThr[i]->cday = cday;
			arrThr[i]->start();
		}

		bool bFlg = false;
		while( 1 ) {
			bFlg = true;
			for( int i=0; i<nArrCnt; i++ ) {
				if ( arrThr[i]->isFinished() == false ) {
					if ( arrThr[i]->wait(100) == false ) {
						bFlg = false;
					}
				}
			}
			if ( bFlg == true ) break;
		}
		objTime.timeEnd();
		emit setTime(1,objTime.dResTime);
		dSum += objTime.dResTime;

		objTime.timeStart();
//		tmp = "* FROM PPP WHERE <IST MAC='0' DAY='"+cday+"' />";
		tmp = "* FROM ZZZ WHERE <IST MAC='0' DAY='"+cday+"' />";
		//tmp += "<LOT LID='"+QString::number(nLotId)+"'/>";
		//tmp += "<INSPECT EID='"+QString::number(nEid)+"'/></IST>";
		log->log("svrPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);
		log->log(tmp,clsLog::CLSLOG_DEBUG);
		QString xml = "";
		if ( XML_SelectFirst(handle,tmp,xml) == false ) {
			log->log("XML_SelectFirst Error:"+handle->getErrorMess(),clsLog::CLSLOG_DEBUG);
			emit showMess("read IST Error");
			XML_Close(handle);
			return;
		}
		objTime.timeEnd();
		emit setTime(2,objTime.dResTime);
		dSum += objTime.dResTime;
		log->log(xml,clsLog::CLSLOG_DEBUG);

		objTime.timeStart();
//		tmp = "<IST><RES>NG</RES></IST> FROM PPP WHERE <IST MAC='0' DAY='"+cday+"' />";
		tmp = "<IST><RES>NG</RES></IST> FROM ZZZ WHERE <IST MAC='0' DAY='"+cday+"' />";
		//tmp += "<LOT LID='"+QString::number(nLotId)+"'/>";
		//tmp += "<INSPECT EID='"+QString::number(nEid)+"'/></IST>";
		log->log("svrPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);
		log->log(tmp,clsLog::CLSLOG_DEBUG);
		if ( XML_Append(handle,tmp) == false ) {
			log->log("XML_Append Error:"+handle->getErrorMess(),clsLog::CLSLOG_DEBUG);
			emit showMess("append Res Error");
			XML_Close(handle);
			return;
		}
		objTime.timeEnd();
		emit setTime(3,objTime.dResTime);
		dSum += objTime.dResTime;

		emit setTime(4,dSum);

		nEid ++;
	}

	XML_Close(handle);
	delete(log);
}

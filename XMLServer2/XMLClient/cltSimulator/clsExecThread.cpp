/*
 * clsExecThread.cpp
 *
 *	Created on: 2010/02/04
 *		Author: cony
 */
#include "clsMainThread.h"
#include "clsCalcTime.h"
#include "clsLog.h"

clsExecThread::clsExecThread(int no, QObject *_par) : QThread(_par) {
	nThrNo = no;
	par = (clsMainThread *)_par;
	svPort = "0";
	cday = "";
}

clsExecThread::~clsExecThread() {
}

void clsExecThread::run() {
	clsCalcTime objTime;

	clsLog *log = new clsLog();
	log->startLog(QString::number(nThrNo));

	handle = XML_Connect(svr,port,WaitTime);
	if ( handle == NULL ) {
		log->log("XML_Connect Error",clsLog::CLSLOG_DEBUG);
		emit showMess("Connect Error");
		return;
	}
	QString pPort = handle->getPort();
	if ( pPort != svPort ) {
		log->log("deffrent port no=["+svPort+"]?["+pPort+"]",clsLog::CLSLOG_DEBUG);
		svPort = pPort;
	}

	log->log("curPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);
	log->log("start ngcnt=["+QString::number(nNgCnt)+"]",clsLog::CLSLOG_DEBUG);
	for( int i=0; i<nNgCnt; i++ ) {
		objTime.timeStart();
		QString tmp = "<IST>";
		tmp += "<NGP X=\"1485\" Y=\"2750\" MX=\"36\" MY=\"36\" HX=\"8\" HY=\"16\" RS1=\"533\" RS2=\"3452816845\" ";
		tmp += "RAL=\"Basic:ColorBlockInspection\" PG=\"1\" LY=\"0\"></NGP>";
		tmp += "<NGI X=\"1363\" Y=\"2494\" W=\"300\" H=\"600\" IDX=\""+QString::number(nThrNo)+QString::number(i)+"\" Index=\"0\"></NGI>";
//		tmp += "</IST> FROM PPP WHERE <IST MAC='0' DAY='"+cday+"' />";
		tmp += "</IST> FROM ZZZ WHERE <IST MAC='0' DAY='"+cday+"' />";
		//tmp += "<LOT LID='"+QString::number(nLid)+"'/>";
		//tmp += "<INSPECT EID='"+QString::number(nEid)+"'/></IST>";
		log->log("CurrentPort=["+QString::number(handle->getCurrentPort())+"]",clsLog::CLSLOG_DEBUG);
		log->log("AppendSQL:"+tmp,clsLog::CLSLOG_DEBUG);
		if ( XML_Append(handle,tmp) == false ) {
			log->log("XML_Append:Error:"+tmp,clsLog::CLSLOG_DEBUG);
			log->log("XML_Append Error:"+handle->getErrorMess(),clsLog::CLSLOG_DEBUG);
			emit showMess("append NG Error");
			XML_Close(handle);
			return;
		}
		objTime.timeEnd();
		emit setCntThr(nThrNo,0,objTime.dResTime);
	}

	XML_Close(handle);
	delete(log);
}

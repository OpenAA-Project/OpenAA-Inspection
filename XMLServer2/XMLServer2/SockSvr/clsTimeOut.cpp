/*
 * clsTimeOut.cpp
 *
 *	Created on: 2009/11/07
 *		Author: cony
 */

#include "clsTcpSvr.h"

#include <crtdbg.h>
#ifdef _DEBUG
#define   new					new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s) 			_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)			_calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s) 		_realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)	_recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s) 		_expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsTimeOut::clsTimeOut(QString no, QObject *_par) : QObject(_par) {
	logLocal = new clsLog();
	logLocal->startLog("local_"+no);
}

clsTimeOut::~clsTimeOut() {
	delete(logLocal);
}

bool clsTimeOut::timeOutStart(int sec) {
	nTimeOutSec = sec;
	startTime = QDateTime::currentDateTime();
	return true;
}

bool clsTimeOut::chkTimeOut() {
	QDateTime cur = QDateTime::currentDateTime();
	if ( startTime.secsTo(cur) > nTimeOutSec ) {
		log->log("time out",clsLog::CLSLOG_DEBUG);
		logLocal->log("time out",clsLog::CLSLOG_DEBUG);
		return true;
	}
	return false;
}

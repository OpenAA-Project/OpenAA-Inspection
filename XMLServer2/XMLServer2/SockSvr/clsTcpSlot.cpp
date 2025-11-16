/*
 * clsTcpSlot.cpp
 *
 *  Created on: 2009/10/24
 *      Author: cony
 */

#include "clsTcpSlot.h"

#include <QDebug>

#include <crtdbg.h>
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

clsTcpSlot::clsTcpSlot(QObject *par) : QThread(par) {
	bAbort = false;
	bEndFlg = false;
	start();
}

clsTcpSlot::~clsTcpSlot() {
	// TODO Auto-generated destructor stub
	printf("****************slot end**********\n");
}

void clsTcpSlot::run() {
	while( bAbort == false ) {
		usleep(1);
		if ( bEndFlg == true ) break;
	}
}

void clsTcpSlot::readyRead() {
	qDebug() << "readyRead sloting";
	return;
}

void clsTcpSlot::endThread() {
	qDebug() << "end thread";
	return;
}

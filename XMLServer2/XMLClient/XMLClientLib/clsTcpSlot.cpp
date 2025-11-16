/*
 * clsTcpSlot.cpp
 *
 *  Created on: 2009/10/24
 *      Author: cony
 */

#include "clsTcpSlot.h"

#include <QDebug>

clsTcpSlot::clsTcpSlot(QObject *par) : QThread(par) {
	bAbort = false;
	start();
}

clsTcpSlot::~clsTcpSlot() {
	// TODO Auto-generated destructor stub
	printf("delete tcpSlot\n");
}

void clsTcpSlot::run() {
	while( bAbort == false ) {
		usleep(100);
	}
	printf("exit tcpslot thread\n");
}

void clsTcpSlot::readyRead() {
	//qDebug() << "readyRead sloting";
	return;
}

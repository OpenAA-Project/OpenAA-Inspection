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
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

#include <QtCore/QCoreApplication>
#include <QTcpSocket>
#include <string.h>
#include <stdio.h>
#include "XGeneralFunc.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QString	IPAddress=/**/"localhost";
	int		PortNo=36755;

	for(int i=0;i<argc;i++){
		if(strnicmp(argv[i],"-A",2)==0
		|| strnicmp(argv[i],"/A",2)==0){
			char	*fp=argv[i]+2;
			IPAddress=QString(fp);
		}
		if(strnicmp(argv[i],"-P",2)==0
		|| strnicmp(argv[i],"/P",2)==0){
			char	*fp=argv[i]+2;
			sscanf(fp,"%d",&PortNo);
		}
	}

	QTcpSocket	Sock(NULL);
	Sock.connectToHost(IPAddress,PortNo);
	Sock.waitForConnected(3000);
	if(Sock.state()==QAbstractSocket::ConnectedState){
		if(Sock.open(QIODevice::ReadWrite | QIODevice::Unbuffered)==true){
			Sock.write("CloseOne\n",8);
			Sock.flush();

			GSleep(1000);
			Sock.disconnectFromHost();
		}
	}

	return 0;
}
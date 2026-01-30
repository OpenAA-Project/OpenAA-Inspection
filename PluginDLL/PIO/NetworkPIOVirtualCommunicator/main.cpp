/*
 * Copyright (C) 2021
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

#include "NetworkPIOVirtualCommunicator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	int		ID				=0;
	QString	ServerIPName	="localhost";
	int		ServerPort=18830;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='D' || *argv[i]=='d'){
			ID=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='I' || *argv[i]=='i'){
			ServerIPName=QString(argv[i]+1);
		}
		if(*argv[i]=='P' || *argv[i]=='p'){
			QString	PortName=QString(argv[i]+1);
			ServerPort	=PortName.toInt();
		}
	}

	NetworkPIOVirtualCommunicator w;
	w.Initial(ID,ServerIPName,ServerPort,16,16);
	w.show();
	return a.exec();
}
/*
 * Copyright (C) 2022
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

#include <QTcpSocket>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //CheckPort w;
    //w.show();
    //return a.exec();

	if(argc>=2){
		QString	s(argv[1]);
		bool	ok;
		int	Port=s.toInt(&ok);
		if(ok==false){
			return -1;
		}
		QTcpSocket	LocalSock;

		LocalSock.connectToHost(/**/"127.0.0.1",Port);
		bool	Ret=LocalSock.waitForConnected(2000);
		if(Ret==true){
			return 0;
		}
		return 1;
	}
	return -2;
}
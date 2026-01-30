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

#include "NetworkSIOServer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	int	PortNumber=28210;
	int	ComPort	=1;

	for(int i=1;i<argc;i++){
		if(strnicmp(argv[i],"COM",3)==0){
			char	*fp=argv[i]+3;
			QString	s(fp);
			bool	ok;
			ComPort	=s.toInt(&ok);
			if(ok==false){
				ComPort=1;
			}
		}
		if(strnicmp(argv[i],"P",1)==0){
			char	*fp=argv[i]+1;
			QString	s(fp);
			bool	ok;
			PortNumber	=s.toInt(&ok);
			if(ok==false){
				PortNumber=28210;
			}
		}
	}

	NetworkSIOServer w(ComPort,PortNumber);
	w.show();
	return a.exec();
}
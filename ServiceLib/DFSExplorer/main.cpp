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

#include "DFSExplorer.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString		IPAddress="localhost";
	int			Port	=DFSClientPort;
	QString		AbsPath;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='I' || *argv[i]=='i'){
			char	*fp=argv[i]+1;
			IPAddress=QString(fp);
		}
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			QString	Var(fp);
			Port=Var.toInt();
		}
	}

	QApplication a(argc, argv);

	DFSExplorer w(IPAddress ,Port);
	w.show();
	return a.exec();
}
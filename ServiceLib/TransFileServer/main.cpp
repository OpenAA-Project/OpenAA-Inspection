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

#include "TransFileServer.h"
#include <QApplication>
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	SlaveCount=4;
	int	LanguageCode=0;
	int		AccessPort=15700;
	QString	CachePath="d:\\Data";
	bool	LogMode=false;

 	for(int i=1;i<argc;i++){
		if(*argv[i]=='P' || *argv[i]=='p'){
			AccessPort=QString(argv[i]+1).toInt();
		}
		if(*argv[i]=='C' || *argv[i]=='c'){
			CachePath=QString(argv[i]+1);
		}
		if(*argv[i]=='L' || *argv[i]=='l'){
			LogMode=true;
		}
	}

	QApplication a(argc, argv);
	TransFileServer w(LogMode,AccessPort,CachePath);
	w.show();
	return a.exec();
}
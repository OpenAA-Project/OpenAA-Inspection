/*
 * Copyright (C) 2025
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

#include <QApplication>
#include "AutoStartList.h"
#include "XShowVersion.h"
#include <QDir>
#include <stdio.h>

QString		DefaultFileName	=/**/"AutoStartList.dat";

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	OperationalPort=17750;
	int	LanguageCode=0;
	QString	AbsPath;
	QString	UserPath;
	bool	EnableClose=false;

 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&OperationalPort);
		}
		if((*argv[i]=='L' || *argv[i]=='l')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&LanguageCode);
		}
		if((*argv[i]=='F' || *argv[i]=='f')){
			char	*fp=argv[i]+1;
			DefaultFileName=fp;
		}
		if((*argv[i]=='X' || *argv[i]=='x')){
			EnableClose=true;
		}
	}

	QApplication a(argc, argv);
	AutoStartList w(EnableClose);
	w.show();
	return a.exec();
}
/*
 * Copyright (C) 2023
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
#include "AutoStartPlayer.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int main(int argc, char *argv[])
{
	QString		SettingFileName=/**/"AutoStart.dat";
	QString		PlayerExe=/**/"InspectionPlayer.exe";
	QString		AbsPath;
	QString		UserPath;

	if(CheckExeVersion(argc, argv)==false)
		return 1;

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
		else if(*argv[i]=='S' || *argv[i]=='s'){
			SettingFileName=QString(argv[i]+1);
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			PlayerExe=QString(argv[i]+1);
		}
	}
	QApplication a(argc, argv);
	AutoStartPlayer w(UserPath,SettingFileName,PlayerExe);
	
		
	//BYTE	*p=NULL;
	//*p=0;

	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
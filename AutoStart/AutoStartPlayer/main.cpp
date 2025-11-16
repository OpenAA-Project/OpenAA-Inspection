/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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

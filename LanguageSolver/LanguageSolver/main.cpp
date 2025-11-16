/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\LanguageSolver\LanguageSolver\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QApplication>
#include <QDir>
#include "LanguageSolver.h"
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	int	SlaveCount=4;
	int	LanguageCode=0;
	QString	AbsPath;

 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
	}
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QDir::currentPath());

	LanguageSolver w;
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	return a.exec();
}

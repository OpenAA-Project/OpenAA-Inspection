/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "datamanagement.h"
#include "setting.h"
#include "connection.h"
#include <QtGui>
#include <QtCore>
#include <QApplication>
#include "XLanguageClass.h"
#include "XFileRegistry.h"
#include "XShowVersion.h"
#include "datamanagementResource.h"

QFile	*DBfile=NULL;
extern bool quit;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//LangSolver
	FileRegistry	*FRegistry		=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);
	//delete FRegistry;
	LanguagePackage *LangPack=new LanguagePackage();
	LangPack->LoadSolutionFromFile(/**/"Datamanagement.lng");
	LangSolver.SetLanguage(*LangPack,LanguageCode);

	bool modFilename = false;
	QString settingFilename = /**/"save.dat";
	QString addTitle;

	for(int i=0; i<argc; i++){
		QString arg = a.arguments().at(i);
		if(arg.isEmpty()==false && arg.at(0)==QChar('S')){
			modFilename = true;
			settingFilename = arg.mid(1);
		}
		if(arg.isEmpty()==false && arg.at(0)==QChar('T')){
			addTitle = arg.mid(1);
		}
	}

	DBfile = new QFile(settingFilename);

	if(modFilename==false){
		Setting s;
		s.show();
		a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
		a.exec();
	}
	if(quit==true)
		return 0;
	while(quit==false){
		quit=true;
		createConnection(settingFilename);
		Datamanagement w;
		if(addTitle.isEmpty()==false){
			w.setWindowTitle( w.windowTitle() + /**/" - " + addTitle );
		}
		w.show();
		a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
		a.exec();
		//_CrtCheckMemory();
		//delete	LangPack;
	}
	delete DBfile;
	return 0;
}

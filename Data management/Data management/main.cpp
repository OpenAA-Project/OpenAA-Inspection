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
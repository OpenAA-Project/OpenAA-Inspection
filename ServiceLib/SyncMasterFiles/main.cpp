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

#include "SyncMasterFiles.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	SlaveCount=4;
	int	LanguageCode=0;
	QString	SourcePath;
	QString	DestinationPath;
	int		SleepTimeSec=60;

 	for(int i=1;i<argc;i++){
		if(*argv[i]=='S' || *argv[i]=='s'){
			char	*fp=argv[i]+1;
			SourcePath=fp;
		}
		if(*argv[i]=='D' || *argv[i]=='d'){
			char	*fp=argv[i]+1;
			DestinationPath=fp;
		}
		if(*argv[i]=='I' || *argv[i]=='i'){
			SleepTimeSec=QString(argv[i]+1).toInt();
		}
	}

	QCoreApplication::addLibraryPath (QDir::currentPath());

	//LanguagePackage	LangPkg;
	//LangPkg.LoadSolutionFromFile("InspectionGeneral.lng");
	//LangSolver.SetLanguage(LangPkg,LanguageCode);

	QApplication a(argc, argv);
	SyncMasterFiles w(SourcePath ,DestinationPath ,SleepTimeSec);
	w.show();
	return a.exec();
}
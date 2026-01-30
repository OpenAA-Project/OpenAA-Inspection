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

#include "ChangeServerResource.h"
#include <QApplication>
#include "ChangeServer.h"
#include <QDir>
#include "XFileRegistry.h"
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	int	LanguageCode=0;
	QString	AbsPath;
	QString	UserPath;

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
	}
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QDir::currentPath());

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	LanguagePackage	LangPack;
	LangPack.LoadSolutionFromFile("ChangeServer.lng");
	LangSolver.SetLanguage(LangPack,LanguageCode);

	QApplication a(argc, argv);
	ChangeServer w;
	w.show();
	return a.exec();
}
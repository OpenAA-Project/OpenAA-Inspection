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
#include "EditStatusComment.h"

#include "XGUI.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "XOpenAA.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

LayersBase	*Layers;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	QString	AbsPath;
	QString	UserPath;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
	}

	EditStatusComment w;
	w.show();

    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}
	EntryPointBase	*e	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(e,::GetUserPath(UserPath));
	e->SetLayersBase(Layers);
	//Layers->SetCurrentPath(QDir::currentPath());
	//Layers->SetUserPath(UserPath);

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	//Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;

	Layers->SetLanguageCode();

	return a.exec();
}
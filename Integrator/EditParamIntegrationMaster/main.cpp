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

#include "EditParamIntegrationMaster.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XFileRegistry.h"
#include "XParamIntegrationMaster.h"
#include "XGUI.h"
#include "XOpenAA.h"

int	LanguageCode;

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

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
   a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}
	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal,::GetUserPath(UserPath));
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	//Layers->SetCurrentPath(QDir::currentPath());
	//Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode=0;

	FileRegistry	*FRegistry=Layers->GetFRegistry();
	LanguageCode=FRegistry->LoadRegInt("Language",0);
	Layers->SetLanguageCode(LanguageCode);

	Layers->InitialFilterBank();

	ParamIntegrationMaster Param(Layers);
    EditParamIntegrationMaster w(Layers,&Param);

    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();
    return a.exec();
}
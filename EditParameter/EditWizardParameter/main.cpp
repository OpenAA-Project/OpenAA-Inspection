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


#include "EditWizardParameter.h"
#include <QApplication>
//#include "ServiceLibResource.h"
#include "XFileRegistry.h"
#include "XShowVersion.h"
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
	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;
	
	QCoreApplication::addLibraryPath(CurrentBuff);
	QString	AddedLibPath = QString(CurrentBuff)+QString("/plugins");
	QCoreApplication::addLibraryPath(AddedLibPath);

    QApplication a(argc, argv);

	QString	AbsPath;
	QString ParamGlobalFileName;
	QString	UserPath;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if(*argv[i]=='S' || *argv[i]=='s'){
			char	*fp=argv[i]+1;
			ParamGlobalFileName	=fp;
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
	Layers->SetGUIInitializer(new GUIInitializer(Layers));

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->GetParamGlobal()->LoadDefault();
	Layers->GetParamComm()->LoadDefault();
	QString	ErrorMsg;
	DWORD	ErrorCode=0;

	FileRegistry	*FRegistry=Layers->GetFRegistry();
	LanguageCode=FRegistry->LoadRegInt("Language",0);
	Layers->SetLanguageCode(LanguageCode);

	Layers->InitialFilterBank();

	ParamComm	ParamCommData(Layers);
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();

	EditWizardParameter w(Layers
						,ParamGlobalFileName
						,&ParamCommData);
	w.show();
	return a.exec();
}
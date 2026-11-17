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
#include <QDir>
#include "FileRegistryEditor.h"
#include "XShowVersion.h"
#include "XDataInExe.h"
#include "XGUI.h"
#include "XOpenAA.h"

/*
	Arguments:
		A[path]	: Set current path to [path]
		Q[path]	: Set user path to [path] for data 
		Mn		: n- Set MachineID
		Ln		: n- Set Language Code
		C		: Close after save
		StopForDebug : Stop for debug
*/

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

int	*TestData;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;
	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	int	targc=argc;
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;
	
	QCoreApplication::addLibraryPath(CurrentBuff);
	QString	AddedLibPath = QString(CurrentBuff)+QString("/plugins");
	QCoreApplication::addLibraryPath(AddedLibPath);


	QString	AbsPath;
	QString	UserPath;
	bool	StopForDebug	=false;
	bool	CloseAfterSave	= false;
	int		ParamMachineID=-1;
	int		ParamLanguageCode=-1;

	for(int i=0;i<targc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if(*argv[i]=='C' || *argv[i]=='c'){
			CloseAfterSave = true;
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
		else if((*argv[i]=='M' || *argv[i]=='m')){
			char	*pp=argv[i]+1;
			int	n=atoi(pp);
			if(n>=0){
				ParamMachineID=n;
			}
		}
		else if((*argv[i]=='L' || *argv[i]=='l')){
			char	*pp=argv[i]+1;
			int	n=atoi(pp);
			if(n>=0){
				ParamLanguageCode=n;
			}
		}
	}

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
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());


	if(ParamLanguageCode>=0){
		Layers->SetLanguageCode(ParamLanguageCode);
		FileRegistry	*FRegistry=Layers->GetFRegistry();
		FRegistry->Save(/**/"Language",ParamLanguageCode);
	}
	if(ParamMachineID>=0){
		Layers->SetMachineID(ParamMachineID);
		FileRegistry	*FRegistry=Layers->GetFRegistry();
		FRegistry->Save(/**/"MachineID",ParamMachineID);
	}

	if(CloseAfterSave==true){
		return 0;
	}

	QApplication a(argc, argv);

	Layers->CloseInformed();

	FileRegistryEditor w(Layers);
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}
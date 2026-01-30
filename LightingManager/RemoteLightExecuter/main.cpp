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

#include "RemoteLightExecuterResource.h"
#include "RemoteLightExecuter.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QString>
#include <QDir>
#include "XFileRegistry.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


LightClassPack		*LightPack=NULL;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;
	QApplication a(argc, argv);

	QString	AbsPath;
	QString	UserPath;
	bool	DefaultGUI_DotFileNameMode=false;
	QString	DefaultGUI_DotFileName="GUI.dat";
	QString	GlobalParmaFileName;
	int		PortNumber;
	QString	DLLFileName;
	QString	InitialStr;

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
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			QString	NN(fp);
			PortNumber=NN.toInt();
		}
		else if((*argv[i]=='D' || *argv[i]=='d') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DLLFileName=fp;
		}
		else if((*argv[i]=='I' || *argv[i]=='i') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			InitialStr=fp;
		}
		else if((*argv[i]=='U' || *argv[i]=='u') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultGUI_DotFileName=fp;
			DefaultGUI_DotFileNameMode=true;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
	}

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt("Language",0);
	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;

	Layers->SetLanguageCode();
	LanguagePackage	LangPack;
	LangPack.LoadSolutionFromFile(LayersBase::GetLanguageSolutionFileName());
	LangSolver.SetLanguage(LangPack,LanguageCode);
	if(GlobalParmaFileName.isEmpty()==false){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}

	//G->Initial(Layers,ErrorCode,ErrorMsg,true);
	QString Msg;
	//if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
	//	QMessageBox Q(/**/"Error"
	//				, Msg, QMessageBox::Critical
	//				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	//	Q.exec();
	//	return(1);
	//}
	int32	xErrorCode;
	//LightPack=new LightClassPack(Layers);
	//LightPack->SearchAddDLL(xErrorCode);

	RemoteLightExecuter w(Layers,DLLFileName ,PortNumber,InitialStr);
	w.show();

	//G->GUIInitializer::InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());
	//Layers->LoadDefault();

	Layers->CloseInformed();
	Layers->ReadAllSettingFiles(true);

	bool	Ret=a.exec();
	delete	LightPack;

	return Ret;

	return a.exec();
}
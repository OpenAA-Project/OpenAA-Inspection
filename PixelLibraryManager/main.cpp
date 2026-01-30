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
#include "PixelLibraryManager.h"

#include <QDir>
#include"XParamGlobal.h"
//#include "StartupDialog.h"

#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QApplication>
#include "XGUI.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "itemlistwindow.h"
#include "propertylist.h"
#include "Regulus64System.h"

ItemListWindow	*MainItem;
PropertyList	*MainProperty;


int main(int argc, char *argv[])
{
	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	Msg;

	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
	}

	QApplication a(argc, argv);


	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());


	GUIInitialData	=new GUIInitializer();
	EntryPointToFuncGlobal->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);

	if(EntryPointToFuncGlobal->GetParamGlobal()->LoadDefault()==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}
	LayersBase	*Layers=EntryPointToFuncGlobal->GetLayersBase();
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->InitialDatabaseLoader(Msg);

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																	,EntryPointToFuncGlobal->GetParamGlobal()->LocalDatabase_FileName
																	,EntryPointToFuncGlobal->GetParamGlobal()->LocalDatabase_HostName
																	,EntryPointToFuncGlobal->GetParamGlobal()->LocalDatabase_Port);
	
	if(KDatabase->IsExistDatabase()==false){
		return(1);
	}
	if(Layers->OpenDatabase(*KDatabase)==false){
		QMessageBox Q( /**/"Error"
					, /**/"Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return(2);
	}
	RootNameListContainer	AlgorithmRootNameList;
	Layers->InitialAlgorithm(AlgorithmRootNameList,DefAlgorithmPath);
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList);
		
	int	LanguageCode=Layers->GetFRegistry()->LoadRegInt(/**/"Language",0);
	Layers->SetLanguageCode();
	Layers->InitialAlgorithmLibrary();

	Layers->SetMainForm(GUIInitialData->GetGUIInstanceRoot()->GetFirstForm());

	Layers->ReadAllSettingFiles(true);

	PixelLibraryManager w(Layers);
	w.show();
	return a.exec();
}
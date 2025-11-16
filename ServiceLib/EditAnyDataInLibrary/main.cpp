#include <QApplication>
#include "EditAnyDataInLibrary.h"

#include <QDir>
#include"XParamGlobal.h"
#include "StartupDialog.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QApplication>
#include "XGUI.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "Regulus64System.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	Msg;

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

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->InitialDatabaseLoader(Msg);

	StartupDialog	D(Layers,NULL);
	D.exec();

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																	,Layers->GetParamGlobal()->LocalDatabase_FileName
																	,Layers->GetParamGlobal()->LocalDatabase_HostName
																	,Layers->GetParamGlobal()->LocalDatabase_Port
																	,Layers->GetParamGlobal()->TransDatabaseIP
																	,Layers->GetParamGlobal()->TransDatabasePort);
	
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
	Layers->LoadLevelFolderContainerFromDB();
	
	RootNameListContainer	AlgorithmRootNameList;
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	int	LanguageCode=Layers->GetFRegistry()->LoadRegInt("Language",0);
	Layers->SetLanguageCode();
	Layers->InitialAlgorithmLibrary();
	Layers->SetMainForm(G->GetGUIInstanceRoot()->GetFirstForm());
	Layers->ReadAllSettingFiles(true);

	EditAnyDataInLibrary w(Layers);
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();

	return a.exec();
}

#include <QApplication>
#include "ManageMasterConnection.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QApplication>

#include "XGUI.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "hasplib.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int main(int argc, char *argv[])
{
	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	Msg;
	
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

	Layers->InitialDatabaseLoader(Msg);

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader()
																	,Layers->GetParamGlobal()->LocalDatabase_FileName
																	,Layers->GetParamGlobal()->LocalDatabase_HostName
																	,Layers->GetParamGlobal()->LocalDatabase_Port
																	,Layers->GetParamGlobal()->TransDatabaseIP
																	,Layers->GetParamGlobal()->TransDatabasePort);
	
	if(KDatabase->IsExistDatabase()==false){
		QString	Msg= QString(/**/"Could not open database - ")
					+QString(Layers->GetParamGlobal()->LocalDatabase_HostName)
					+QString(/**/":")
					+QString(Layers->GetParamGlobal()->LocalDatabase_FileName);
		QMessageBox Q( /**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	if(Layers->OpenDatabase(*KDatabase)==false){
		DatabaseError:;
		QMessageBox Q( /**/"Error"
					, /**/"Could not open database", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(2);
	}
	Layers->SetLanguageCode();
	Layers->SetMainForm(G->GetGUIInstanceRoot()->GetFirstForm());
	Layers->ReadAllSettingFiles(true);
	Layers->ReadLogicSettingFiles(true);

	ManageMasterConnection w(Layers);
	Layers->CloseInformed();

	w.show();
    int	ret=a.exec();

	//_CrtCheckMemory();

	return ret;

}

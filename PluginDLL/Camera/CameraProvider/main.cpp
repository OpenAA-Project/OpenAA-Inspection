#include "CameraProvider.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>
#include <QMessageBox>

#include"XParamGlobal.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QApplication>
#include "XGUI.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int	WaitingMilisecForCapture=0;
QString	CameraProviderSettingFile=/**/"CameraProviderSetting.dat";

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	CameraDLLFileName;
	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	QString	Msg;
	int		CountOfCamera;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='L' || *argv[i]=='l'){
			char	*fp=argv[i]+1;
			CameraDLLFileName=fp;
		}
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
		else if(*argv[i]=='N' || *argv[i]=='n'){
			char	*fp=argv[i]+1;
			CountOfCamera=QString(fp).toInt();
		}
		else if(*argv[i]=='W' || *argv[i]=='w'){
			char	*fp=argv[i]+1;
			WaitingMilisecForCapture=QString(fp).toInt();
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			CameraProviderSettingFile=fp;
		}
	}

	QApplication a(argc, argv);

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);

	if(Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath())==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	Layers->InitialDatabaseLoader(Msg);


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

	int	LanguageCode=Layers->GetFRegistry()->LoadRegInt("Language",0);
	Layers->SetLanguageCode();
	Layers->InitialAlgorithmLibrary();
	Layers->SetMainForm(G->GetGUIInstanceRoot()->GetFirstForm());
	Layers->ReadAllSettingFiles(true);

	CameraProvider w(CountOfCamera,CameraDLLFileName,Layers);
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();

	return a.exec();

}

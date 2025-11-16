#include "RemoteLightControllerResource.h"
#include "RemoteLightController.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QString>
#include <QDir>
#include "SingleExecute.h"
#include "XFileRegistry.h"

#include <QSqlDatabase>
#include <QApplication>
#include <stdio.h>
#include "XDatabase.h"
#include "PasswordDropper.h"
#include "XPassword.h"
#include <QInputDialog>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}


int	MachineID;
LightClassPack		*LightPack=NULL;
int		LoadLightDataOnStart=-1;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QString	AbsPath;
	QString	UserPath;
	bool	DefaultGUI_DotFileNameMode=false;
	QString	DefaultGUI_DotFileName="GUI.dat";
	QString	GlobalParmaFileName=/**/"Global.dat";
	QString	LoadedFile;//="RemoteLightDefaultSetting.dat";
	bool	StartON=false;
	int		DBTransPort=-1;
	bool	EditPasswordMode=false;
	QString	BootPassword;

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
		else if(*argv[i]=='L' || *argv[i]=='l'){
			char	*fp=argv[i]+1;
			LoadedFile	=fp;
		}
		else if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&DBTransPort);
		}
		else if((*argv[i]=='I' || *argv[i]=='i')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&LoadLightDataOnStart);
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
		else if((*argv[i]=='O' || *argv[i]=='o') && *(argv[i]+1)!=':'){
			StartON=true;
		}
		if((*argv[i]=='E' || *argv[i]=='e') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			if(*fp=='P' || *fp=='p'){
				EditPasswordMode=true;
				BootPassword=QString(fp+1);
			}
		}
	}
	QFileInfo	FInfo(argv[0]);
	if(SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt("Language",0);
	MachineID				=FRegistry.LoadRegInt("MachineID",0);

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
	QString	Msg;
	Layers->InitialDatabaseLoader(Msg);
	int	LPort;
	if(DBTransPort>0){
		LPort=DBTransPort;
	}
	else{
		LPort=Layers->GetParamGlobal()->TransDatabasePort;
	}

	LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(Layers->GetDatabaseLoader(false)
																	,Layers->GetParamGlobal()->LocalDatabase_FileName
																	,Layers->GetParamGlobal()->LocalDatabase_HostName
																	,Layers->GetParamGlobal()->LocalDatabase_Port
																	,Layers->GetParamGlobal()->TransDatabaseIP
																	,LPort);
	
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

	PasswordDropper	*PWForm=NULL;
	Layers->GetPasswordHolder()->SetDefaultFile("RemoteLightController.pwd");
	Layers->GetPasswordHolder()->LoadDefaultFile();
	if(EditPasswordMode==true){
		Layers->SetEditPasswordMode(true);
		QString Password=QInputDialog::getText ( NULL, /**/"Input Boot-Password", "Boot-Password", QLineEdit::Password);
		if(BootPassword.isEmpty()==true){
			if(Layers->GetPasswordHolder()->IsPasswordExists(Password)==false)
				return 10;
		}
		else{
			if(BootPassword!=Password){
				return 10;
			}
		}
	}

	if(EditPasswordMode==true){
		PWForm=new PasswordDropper(Layers);
		PWForm->GUIPack=G->GetGUIInstanceRoot();
		PWForm->show();
	}
	else{
		Layers->GetPasswordHolder()->SetupOnlyPassword(*G->GetGUIInstanceRoot());
	}


	int32	xErrorCode;
	LightPack=new LightClassPack(Layers);
	LightPack->SearchAddDLL(xErrorCode);

	RemoteLightController w(Layers,LoadedFile,StartON);
	w.show();

	//G->GUIInitializer::InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());
	//Layers->LoadDefault();

	Layers->CloseInformed();
	Layers->ReadAllSettingFiles(true);

	bool	Ret=a.exec();
	//delete	LightPack;

	return Ret;
}

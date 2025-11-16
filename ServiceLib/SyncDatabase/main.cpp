#include "SyncDatabase.h"
#include <QApplication>
#include "XFileRegistry.h"
#include <QSqlDatabase>

#include "XGUI.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}
int	LanguageCode;

QString		LoadedFileName;

int main(int argc, char *argv[])
{
	QString	GlobalParmaFileName=/**/"Global.dat";
	QString	AbsPath;
	bool	DupOK=true;
	QString	Msg;
	LoadedFileName="SyncDatabaseSetting.dat";

	if(CheckExeVersion(argc, argv)==false)
		return 1;
	
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
		else if((*argv[i]=='L' || *argv[i]=='l') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			LoadedFileName=fp;
		}
	}
	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	//LangLibSolver.SetLanguage(LanguageCode);

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	ParamGlobal	GlobalParam(Layers);

	QFile	F(GlobalParmaFileName);
	if(F.open(QIODevice::ReadOnly)==true){
		GlobalParam.LoadParam(&F);
		F.close();
	}

	QApplication a(argc, argv);
	SyncDatabase w(Layers,&GlobalParam);
	w.show();
	Layers->CloseInformed();

	bool	ret=a.exec();

	return ret;
}

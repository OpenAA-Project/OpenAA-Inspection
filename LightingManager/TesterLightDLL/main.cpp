#include "TesterLightDLL.h"
#include <QApplication>
#include "XGUI.h"
#include "XLightClass.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QString>
#include <QDir>
#include <QMessageBox>

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

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;

	Layers->SetLanguageCode();
	if(GlobalParmaFileName.isEmpty()==false){
		Layers->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);
	}
	Layers->GetParamGlobal()->DotPerLine=100;
	Layers->GetParamGlobal()->MaxLines	=100;
	Layers->GetParamGlobal()->PageNumb	=1;
	Layers->GetParamGlobal()->PhaseNumb	=1;

	//G->Initial(Layers,ErrorCode,ErrorMsg,true);
	QString Msg;
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	int32	xErrorCode;
	LightPack=new LightClassPack(Layers);
	LightPack->SearchAddDLL(xErrorCode);

	TesterLightDLL w(Layers);
	w.show();

	//G->GUIInitializer::InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());
	Layers->LoadAttrDefault();

	Layers->CloseInformed();
	Layers->ReadAllSettingFiles(true);

	bool	Ret=a.exec();
	delete	LightPack;

	return Ret;
}

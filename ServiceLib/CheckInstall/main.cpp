#include "CheckInstall.h"
#include <QtWidgets/QApplication>
#include "XShowVersion.h"
#include <QString>
#include <QDir>
#include "XDataInLayer.h"

ParamGlobal	*ParamGlobalInst;

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

bool    CheckFirebirdService(void)
{
}

bool    CheckFirebirdPort(void)
{
}

int main(int argc, char *argv[])
{
	QString	AbsPath;
	bool	DefaultGUI_DotFileNameMode=false;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
	}

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	ParamGlobalInst=new ParamGlobal(Layers);

	Layers->SetCurrentPath(QDir::currentPath());
	ParamGlobalInst->LoadDefault();


    QApplication a(argc, argv);
    CheckInstall w;
    w.show();
    return a.exec();
}



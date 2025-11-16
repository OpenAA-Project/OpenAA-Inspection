#include "ChangeServerResource.h"
#include <QApplication>
#include "ChangeServer.h"
#include <QDir>
#include "XFileRegistry.h"
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	int	LanguageCode=0;
	QString	AbsPath;
	QString	UserPath;

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
	}
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QDir::currentPath());

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	LanguagePackage	LangPack;
	LangPack.LoadSolutionFromFile("ChangeServer.lng");
	LangSolver.SetLanguage(LangPack,LanguageCode);

	QApplication a(argc, argv);
	ChangeServer w;
	w.show();
	return a.exec();
}

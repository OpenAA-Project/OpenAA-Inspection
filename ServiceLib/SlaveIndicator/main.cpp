#include <QApplication>
#include <QDir>
#include "SlaveIndicator.h"
#include <stdio.h>
#include "SlaveIndicatorResource.h"
#include "XShowVersion.h"
/*
const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}
*/

/*
	Commandline option

	N[SlaveCount]	Set slave count
*/

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	SlaveCount=4;
	int	LanguageCode=0;
	QString	AbsPath;

 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		if((*argv[i]=='N' || *argv[i]=='n')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&SlaveCount);
		}
		if((*argv[i]=='L' || *argv[i]=='l')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&LanguageCode);
		}
	}
	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QDir::currentPath());

	LanguagePackage	LangPkg;
	LangPkg.LoadSolutionFromFile("InspectionGeneral.lng");

	LangSolver.SetLanguage(LangPkg,LanguageCode);
	QApplication a(argc, argv);
	SlaveIndicator w(SlaveCount);
	w.show();
	return a.exec();
}

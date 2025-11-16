#include "networkdriveautoconnectResource.h"

#include <QApplication>
#include <QString>
#include <windows.h>
#include "networkdriveautoconnect.h"

#include "XFileRegistry.h"
#include "XShowVersion.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	QString iniFilename = "NetworkDriveAutoConnectInfo.ini";
	bool loop = false;
	DWORD loopTime = 600000;

	for(int i=1; i<argc; i++){
		const QString argm = argv[i];
		if(argm.at(0)==QChar('F')){
			QString file = argm.mid(1);
			if(file.isEmpty()==false){
				iniFilename = file;
			}
		}
		QChar c = argm.at(0);
		QChar l = QChar('L');
		int cc = c.cell();
		int lc = l.cell();
		if(cc==lc){
			loop = true;
			DWORD time = argm.mid(1).toInt();
			if(time!=0){
				loopTime = time;
			}
		}
	}

	FileRegistry	*FRegistry		=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);
	LangSolver.SetLanguage(LanguageCode);

	NetworkDriveAutoConnect w(NULL, iniFilename, loop, loopTime);
	w.setLoopEnable(loop);
	w.show();
	return a.exec();
}

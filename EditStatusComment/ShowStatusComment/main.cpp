#include "ShowStatusComment.h"
#include <QApplication>
#include <QFileInfo>
#include "SingleExecute.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QFileInfo	FInfo(argv[0]);
	if(SingleExecute(FInfo.fileName())==false){
		KillDupProcess(FInfo.fileName());
		//return 100;
	}

	ShowStatusComment w;
	w.show();
	return a.exec();
}

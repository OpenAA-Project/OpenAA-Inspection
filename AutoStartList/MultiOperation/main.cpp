#include "MultiOperation.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>
#include <stdio.h>
#include "XDestination.h"
#include "OperatingForm.h"

QString	SettingFile="MultiOperation.dat";

int main(int argc, char *argv[])
{
	DestinationContainer	DestContainer;

	QFile	File(SettingFile);
	if(File.open(QIODevice::ReadOnly)==true){
		DestContainer.Load(&File);
	}

	int	ret;
	if(argc>=2){
		QString	ArgVStr=QString(argv[1]).toUpper();

		if(ArgVStr=="COPY"){
			QString	Source;
			QString	Dest;
			if(argc>=3){
				Source=QString(argv[2]);
			}
			if(argc>=4){
				Dest=QString(argv[3]);
			}
			ret=FuncCopy(Source,Dest);
			return ret;
		}
		else if(ArgVStr=="DEL"){
			QString	Dest;
			if(argc>=3){
				Dest=QString(argv[2]);
			}
			ret=FuncDel(Dest);
			return ret;
		}
		else if(ArgVStr=="MKDIR"){
			QString	Dest;
			if(argc>=3){
				Dest=QString(argv[2]);
			}
			ret=FuncMkdir(Dest);
			return ret;
		}
		else if(ArgVStr=="START"){
			QString	Dest;
			if(argc>=3){
				Dest=QString(argv[2]);
			}
			ret=FuncStart(Dest);
			return ret;
		}
	}

	QApplication a(argc, argv);
	MultiOperation w;
	w.show();
	return a.exec();
}

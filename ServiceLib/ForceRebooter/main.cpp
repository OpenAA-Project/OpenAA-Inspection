#include "ForceRebooter.h"
#include <QApplication>
#include "XShowVersion.h"
#include "CommandForm.h"

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;
	bool	Minimized=false;
	int	Cmd=Cmd_None;
	int	OwnCmd=Cmd_None;

	for (int i = 1; i < argc; i++) {
		if(*argv[i]=='P'){
			Cmd = Cmd_RebootPrograms;
		}
		else if(*argv[i]=='R'){
			Cmd = Cmd_RebootPC;
		}
		else if(*argv[i]=='S'){
			Cmd = Cmd_ShutDownPC;
		}
		else if(*argv[i]=='M'){
			Minimized=true;
		}
		else if(*argv[i]=='E'){
			OwnCmd = Cmd_OwnRebootPC;
		}
		else if(*argv[i]=='W'){
			OwnCmd = Cmd_OwnShutDownPC;
		}
	}
	QApplication a(argc, argv);
	if (Cmd == Cmd_None) {
		ForceRebooter w;
		if(Minimized==true){
			w.showMinimized();
		}
		else{
			w.show();
		}
		return a.exec();
	}
	else if (Cmd == Cmd_RebootPrograms) {
		CommandForm w(Cmd,OwnCmd);
		w.show();
		return a.exec();
	}
	else if (Cmd == Cmd_RebootPC) {
		CommandForm w(Cmd,OwnCmd);
		w.show();
		return a.exec();
	}
	else if (Cmd == Cmd_ShutDownPC) {
		CommandForm w(Cmd,OwnCmd);
		w.show();
		return a.exec();
	}
}

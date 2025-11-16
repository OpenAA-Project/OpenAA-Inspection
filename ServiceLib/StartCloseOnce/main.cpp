#include "StartCloseOnce.h"
#include <QApplication>
#include <QProcess>
#include <QThread>
#include "Windows.h"

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


void	GSleep(unsigned int milisec)
{
	TmpThread::TmpGSleep(milisec);
}



bool KillProcess(DWORD dwProcessId, unsigned int uExitCode)
{
     DWORD dwDesiredAccess = PROCESS_TERMINATE;
     BOOL  bInheritHandle  = false;
     HANDLE hProcess = OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
     if (hProcess == NULL)
         return false;
 
     BOOL result = TerminateProcess(hProcess, uExitCode);
 
     CloseHandle(hProcess);
 
	 if(result==TRUE)
		 return true;
     return false;
}


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StartCloseOnce w;
	w.show();

	w.update();

	QApplication::processEvents();

	if(argc<5)
		return 1;

	int		WaitingTime1=QString(argv[1]).toInt();
	int		WaitingTime2=QString(argv[2]).toInt();
	QString	ProgFileName=argv[3];
	QString	WorkingDirectory=argv[4];
	QStringList	Arguments;
	for(int i=5;i<argc;i++){
		Arguments.append(argv[i]);
	}

	GSleep(WaitingTime1*1000);

	qint64 pid;
	QProcess::startDetached ( ProgFileName, Arguments, WorkingDirectory, &pid);

	GSleep(WaitingTime2*1000);

	KillProcess(pid, 1);

	return 0;
	//return a.exec();
}

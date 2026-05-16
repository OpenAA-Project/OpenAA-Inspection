/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "StartCloseOnce.h"
#include <QApplication>
#include <QProcess>
#include <QThread>
#include "XForWindows.h"
#include "XGeneralFunc.h"

class	TmpThread : public QThread
{
public:
	void run (){}

	static	void	TmpGSleep(unsigned int milisec){	msleep(milisec);	}
};


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
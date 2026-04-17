/*
 * Copyright (C) 2023
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


#include "XMLServerV3.h"
#include <QApplication>
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QMessageBox>
//#include <chkp.h>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
#ifdef _SDEBUG
	//LeakCheckerStart();
#endif
		
	//__chkp_report_control(__CHKP_REPORT_TRACE_LOG, 0);
	//__chkp_report_control(__CHKP_REPORT_TRACE_BPT, 0);

	if(CheckExeVersion(argc, argv)==false)
		return 1;

	char	TBuff[256];
	strcpy(TBuff,"-platformpluginpath");
	argv[argc] = TBuff;
	argc++;

	char	CurrentBuff[256];
	strcpy(CurrentBuff,(char *)QDir::currentPath().toStdString().c_str());
	argv[argc] = CurrentBuff;	
	argc++;
	QCoreApplication::addLibraryPath(CurrentBuff);

	QString	AbsPath;
	QString	UserPath;
	bool	StopForDebug=false;

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
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}
	QApplication a(argc, argv);
	XMLServerV3 w(UserPath);
	w.show();
	return a.exec();
}
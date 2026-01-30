/*
 * Copyright (C) 2022
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

#include "Booter.h"
#include <QApplication>
#include <QDir>
#include "XShowVersion.h"
#include "XGUI.h"
#include "XLightClass.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include <QString>

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int	OperationalPort=17900;
	int	LanguageCode=0;
	QString	AbsPath;
	QString	SettingFile="BooterParameter.dat";
	//EntryPointToFuncGlobal	=MakeEntryPointForGlobal();

 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		if((*argv[i]=='P' || *argv[i]=='p')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&OperationalPort);
		}
		if((*argv[i]=='L' || *argv[i]=='l')){
			char	*fp=argv[i]+1;
			sscanf(fp,/**/"%d",&LanguageCode);
		}
		if((*argv[i]=='S' || *argv[i]=='s')){
			char	*fp=argv[i]+1;
			SettingFile=QString(fp);
		}
	}

	QApplication a(argc, argv);
	Booter w(SettingFile,OperationalPort);
	
	w.show();
	return a.exec();
}
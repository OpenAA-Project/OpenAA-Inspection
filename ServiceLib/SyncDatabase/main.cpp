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

#include "SyncDatabase.h"
#include <QApplication>
#include "XFileRegistry.h"
#include <QSqlDatabase>

#include "XGUI.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XOpenAA.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}
int	LanguageCode;

QString		LoadedFileName;

int main(int argc, char *argv[])
{
	QString	GlobalParmaFileName=/**/"Global.dat";
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	Msg;
	LoadedFileName="SyncDatabaseSetting.dat";

	if(CheckExeVersion(argc, argv)==false)
		return 1;
	
 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
		else if((*argv[i]=='L' || *argv[i]=='l') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			LoadedFileName=fp;
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
	}

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal,::GetUserPath(UserPath));
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	FileRegistry	*FRegistry=Layers->GetFRegistry();
	LanguageCode=FRegistry->LoadRegInt("Language",0);

	ParamGlobal	GlobalParam(Layers);

	QFile	F(GlobalParmaFileName);
	if(F.open(QIODevice::ReadOnly)==true){
		GlobalParam.LoadParam(&F);
		F.close();
	}

	QApplication a(argc, argv);
	SyncDatabase w(Layers,&GlobalParam);
	w.show();
	Layers->CloseInformed();

	bool	ret=a.exec();

	return ret;
}
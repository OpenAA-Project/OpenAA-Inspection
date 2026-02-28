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



#include <QApplication>
#include "XGeneralFunc.h"
#include "EditParameter.h"
#include "ServiceLibResource.h"
#include "XFileRegistry.h"
#include "XShowVersion.h"
#include "XDataInExe.h"
#include "XGUI.h"
#include <QMessageBox>

//#include "itemlistwindow.h"

int	LanguageCode;

//ItemListWindow	*MainItem;
//PropertyList	*MainProperty;

/*
	Arguments:
		A[path]	: Set current path to [path]
		Q[path]	: Set user path to [path] for data 
		P[Param name]=[value] : Set parameter [name] to [value]
		V		: Save as default
		C		: Close after save
		StopForDebug : Stop for debug
*/

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

int main(int argc, char *argv[])
{
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
	QString	AddedLibPath = QString(CurrentBuff)+QString("/plugins");
	QCoreApplication::addLibraryPath(AddedLibPath);

    QApplication a(argc, argv);

	a.setStyleSheet(R"(
        QSpinBox {
            min-height: 24px;
            font-size: 10px;
        }
        QSpinBox::up-button {
            width: 20px;
        }
        QSpinBox::down-button {
            width: 20px;
        }
    )");

	QString	AbsPath;
	QString	UserPath;
	bool	StopForDebug	=false;
	bool	CloseAfterSave	= false;
	NPListPack<ParamClass>	ParamList;
	bool	SaveAsDefault = false;

	for(int i=1;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if(*argv[i]=='C' || *argv[i]=='c'){
			CloseAfterSave = true;
		}
		else if((*argv[i]=='P' || *argv[i]=='p')){
			char	*pp=argv[i]+1;
			char	*eqpos=strchr(pp,'=');
			if(eqpos!=NULL){
				*eqpos=0;
				char	*paramname=pp;
				char	*paramvalue=eqpos+1;
				ParamClass *a = new ParamClass();
				a->ParamName	= paramname;
				a->ParamValue	= paramvalue;
				ParamList.AppendList(a);
			}
		}
		else if((*argv[i]=='V' || *argv[i]=='v')){
			SaveAsDefault = true;
		}
		else if(strnicmp(argv[i],"StopForDebug",12)==0){
			StopForDebug=true;
		}
	}
	if(StopForDebug==true){
		QMessageBox::information(NULL,"Stop","Please push OK button to go",QMessageBox::Ok);
	}
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	if(AbsPath.isEmpty()==false){
		QCoreApplication::addLibraryPath (AbsPath);
	}
	else{
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());
	}
	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	EntryPointToFuncGlobal->GUISetEditMode(true);
	
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	Layers->SetGUIInitializer(new GUIInitializer(Layers));

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	Layers->SetLanguageCode(LanguageCode);

	Layers->InitialFilterBank();

	ParamComm	ParamCommData(Layers);
    EditParameter w(Layers,&ParamCommData,ParamList);

    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));


	Layers->CloseInformed();

	if(SaveAsDefault==true){
		Layers->GetParamGlobal()->SaveDefault(Layers->GetUserPath());
	}
	if(CloseAfterSave==true){
		return 0;
	}

    return a.exec();
}
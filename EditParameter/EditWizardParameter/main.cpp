/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditParameter\EditWizardParameter\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditWizardParameter.h"
#include <QApplication>
//#include "ServiceLibResource.h"
#include "XFileRegistry.h"
#include "XShowVersion.h"
#include "XGUI.h"

int	LanguageCode;


const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "EditParameter.lng";
}

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

    QApplication a(argc, argv);

	QString	AbsPath;
	QString ParamGlobalFileName;

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		if(*argv[i]=='S' || *argv[i]=='s'){
			char	*fp=argv[i]+1;
			ParamGlobalFileName	=fp;
		}
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
	Layers->SetGUIInitializer(new GUIInitializer(Layers));

	Layers->SetCurrentPath(QDir::currentPath());
	Layers->GetParamGlobal()->LoadDefault();
	Layers->GetParamComm()->LoadDefault();
	QString	ErrorMsg;
	DWORD	ErrorCode=0;

	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	LanguageCode=FRegistry.LoadRegInt("Language",0);
	Layers->SetLanguageCode(LanguageCode);

	Layers->InitialFilterBank();

	ParamComm	ParamCommData(Layers);
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	Layers->CloseInformed();

	EditWizardParameter w(Layers
						,ParamGlobalFileName
						,&ParamCommData);
	w.show();
	return a.exec();
}

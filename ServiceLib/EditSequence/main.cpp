/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\ServiceLib\EditSequence\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QApplication>
#include <QDir>
#include "EditSequence.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XGUI.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);
	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			QString	AbsPath(fp);
			QDir::setCurrent(AbsPath);
		}
	}
	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	SeqControlParam	*SeqControlParamData=new SeqControlParam(Layers);
	EditSequence w(Layers,SeqControlParamData);
	w.show();
	a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
	return a.exec();
}


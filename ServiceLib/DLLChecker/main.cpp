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
#include "DLLChecker.h"
#include "XGUI.h"
//#include "XExecuteInspect.h"
#include "XCameraClass.h"
#include "XPIOInterface.h"
#include "XPIOButton.h"
#include "XLightClass.h"
#include "XSequence.h"
#include <ThreadSequence.h>
#include "XFilterManager.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
#include "SelectDLLDialog.h"
#include <QMessageBox>
#include "Regulus64System.h"
#include "XMainGUIFormBase.h"
#include "XOpenAA.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

//ExecuteInspect	*ExecuteInspect::StaticInstance=NULL;

CameraClassPack		*CameraPack=NULL;
PIOClassPack		*PIOPack=NULL;
LightClassPack		*LightPack=NULL;
DLLVarPack			*SeqVarPack=NULL;
ThreadSequence		*Seq=NULL;

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
	QString	AbsPath;
	QString	UserPath;
	bool	DefaultGUI_DotFileNameMode=false;
	QString	DefaultGUI_DotFileName="GUI.dat";


	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if((*argv[i]=='U' || *argv[i]=='u') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultGUI_DotFileName=fp;
			DefaultGUI_DotFileNameMode=true;
		}
	}

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	EntryPointBase	*EntryPointToFuncGlobal	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal,::GetUserPath(UserPath));
	EntryPointToFuncGlobal->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);
	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	Layers->GetParamGlobal()->LoadDefault(Layers->GetUserPath());
	Layers->GetParamComm()->LoadDefault(Layers->GetUserPath());
	QString	ErrorMsg;
	DWORD	ErrorCode;
	Layers->SetLanguageCode();

	G->Initial(Layers,ErrorCode,ErrorMsg,true);
	QString Msg;
	if(G->GetGUIInstanceRoot()->InitialLayers(Msg)==false){
		QMessageBox Q(/**/"Error"
					, Msg, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return(1);
	}
	RootNameListContainer	AlgorithmRootNameList;
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	Layers->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	Layers->InitialAllocExecuterDim();
	Layers->InitialResult();
	
	if(DefaultGUI_DotFileNameMode==true){
		Layers->GetParamGUI()->SetDefaultFileName(DefaultGUI_DotFileName);
	}

	DLLChecker w(Layers);
	w.show();

	int32	xErrorCode;
	//Seq=new ThreadSequence(Layers,&w);	//�C���X�^���X����
	//Layers->SetSequenceInstance(Seq);

	SelectDLLDialog	D;

	D.exec();

	CameraPack=new CameraClassPack(Layers);
	if(D.CheckCameraDLL==true){
		CameraPack->SearchAddDLL(xErrorCode);
	}

	PIOPack=new PIOClassPack(Layers);
	if(D.CheckPIODLL==true){
		PIOPack->SearchAddDLL(xErrorCode);
	}

	LightPack=new LightClassPack(Layers);
	if(D.CheckLightDLL==true){
		LightPack->SearchAddDLL(xErrorCode);
	}

	SeqVarPack=new DLLVarPack(Layers);
	MainGUIFormBase	*MainForm=NULL;
	Seq=new ThreadSequence(Layers,MainForm);
	//Layers->SetSequenceInstance(Seq);	//Executed . then error occurs
	if(D.CheckSequenceDLL==true){
		SeqVarPack->SearchAddDLL(Seq->GetMainSeqControl(),xErrorCode);
	}

	Layers->GetFilterBank()->SearchAddDLL(xErrorCode);

	G->GUIInitializer::InitialMultiComputer(G->GetGUIInstanceRoot()->GetFirstForm());
	Layers->LoadAttrDefault();

	Layers->CloseInformed();
	Layers->ReadAllSettingFiles(true);

	bool	Ret=a.exec();

	delete	CameraPack;
	delete	PIOPack;
	delete	LightPack;
	delete	SeqVarPack;

	return Ret;
}
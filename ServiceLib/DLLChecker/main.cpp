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
	LayersBase	*Layers	=new LayersBase(EntryPointToFuncGlobal);
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
	//Seq=new ThreadSequence(Layers,&w);	//インスタンス生成
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

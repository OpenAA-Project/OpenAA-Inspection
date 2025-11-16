#include "IntegratePlayer.h"
#include <QApplication>
#include "XShowVersion.h"
#include <QDir>
#include <QMessageBox>

#include"XParamGlobal.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QApplication>
#include "XGUI.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "itemlistwindow.h"
#include "propertylist.h"
#include "XShowVersion.h"
#include "XDataInLayer.h"
//#include "XSequenceLocalExecuter.h"
#include "XExecuteIntegratePlayer.h"
#include "XSequence.h"

const	const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

ItemListWindow	*MainItem;
PropertyList	*MainProperty;
int32			xErrorCode;


int	WaitingMilisecForCapture=0;
bool	NoLoadProgram=false;
int		UnitCount=2;

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	int		Ret=0;
	QString	CameraDLLFileName;
	QString	GlobalParmaFileName="Global.dat";
	QString	AbsPath;
	QString	Msg;
	int		CountOfCamera=1;
	int		CountOfShare=2;
	bool	NoSequence=false;
	QString	CameraSettingFile=/**/"IntegratePlayerSetting.dat";
	ExecuteIntegratePlayer	*ExeIns[16];

	for(int i=1;i<argc;i++){
		if(*argv[i]=='L' || *argv[i]=='l'){
			char	*fp=argv[i]+1;
			CameraDLLFileName=fp;
		}
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
		else if(*argv[i]=='C' || *argv[i]=='c'){
			char	*fp=argv[i]+1;
			CountOfCamera=QString(fp).toInt();
		}
		else if(*argv[i]=='H' || *argv[i]=='h'){
			char	*fp=argv[i]+1;
			CountOfShare=QString(fp).toInt();
		}
		else if(*argv[i]=='W' || *argv[i]=='w'){
			char	*fp=argv[i]+1;
			WaitingMilisecForCapture=QString(fp).toInt();
		}
		else if(*argv[i]=='P' || *argv[i]=='p'){
			char	*fp=argv[i]+1;
			CameraSettingFile=fp;
		}
		else if(strcmp(argv[i],/**/"NoSequence")==0){
			NoSequence=true;
		}
		else if(strcmp(argv[i],/**/"NoLoadProgram")==0){
			NoLoadProgram=true;
		}
	}

	QApplication a(argc, argv);

	if(AbsPath.isEmpty()==false)
		QCoreApplication::addLibraryPath (AbsPath);
	else
		QCoreApplication::addLibraryPath (QCoreApplication::applicationDirPath());

	GUIInitialData	=new GUIInitializer();
	EntryPointToFuncGlobal->GetParamGlobal()->SetDefaultFileName(GlobalParmaFileName);

	if(EntryPointToFuncGlobal->GetParamGlobal()->LoadDefault()==false){
		QMessageBox Q("Load error"
					, "Load error of GlobalParam", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
	}

	EntryPointToFuncGlobal->GetLayersBase()->SetCurrentPath(QDir::currentPath());

	int	LanguageCode=EntryPointToFuncGlobal->GetLayersBase()->GetFRegistry()->LoadRegInt("Language",0);
	EntryPointToFuncGlobal->GetLayersBase()->SetLanguageCode();
	LanguagePackage	LangPack;
	LangPack.LoadSolutionFromFile(LayersBase::GetLanguageSolutionFileName());

	EntryPointToFuncGlobal->GetLayersBase()->SetMainForm(GUIInitialData->GetGUIInstanceRoot()->GetFirstForm());
	EntryPointToFuncGlobal->GetLayersBase()->LoadGUILanguage(EntryPointToFuncGlobal->GetLayersBase()->GetParamGlobal()->GUILanguageFileName);
	EntryPointToFuncGlobal->GetLayersBase()->ReadAllSettingFiles(true);

	IntegratePlayer w(EntryPointToFuncGlobal->GetLayersBase());

	for(int i=0;i<UnitCount;i++){
		ExeIns[i]=new ExecuteIntegratePlayer(&w,EntryPointToFuncGlobal,i);
		ExeIns[i]->Initial();
		ExeIns[i]->start();
	}
	/*
	SeqControlParam	*SeqControlParamData=new SeqControlParam(&w,EntryPointToFuncGlobal->GetLayersBase());
	w.SetSeqControlParam(SeqControlParamData);
	w.SetExecuteInspect(ExeIns);

	//EntryPointToFuncGlobal->GetLayersBase()->SetMainForm(MainForm);
	ThreadSequence	*Seq=NULL;
	if(NoSequence==false){
		if(EntryPointToFuncGlobal->IsMasterPC()==true){
			Seq=new ThreadSequence(EntryPointToFuncGlobal->GetLayersBase(),&w);
			EntryPointToFuncGlobal->GetLayersBase()->SetSequenceInstance(Seq);

			Seq->SetFunction(SeqControlParamData
							,_XSeqLocalInit
							,_SetDataSpecialOperand
							,_GetDataSpecialOperand
							,_SetDataSpecialBitOperand
							,_GetDataSpecialBitOperand
							,_SetDataSpecialStringOperand
							,_GetDataSpecialStringOperand
							,_SetDataSpecialFloatOperand
							,_GetDataSpecialFloatOperand
							);
			w.SetThreadSequence(Seq);
		}
	}

	if(Seq!=NULL){
		QString	ErrorLine;
		if(Seq->LoadStartSequenceFile(&w
				,EntryPointToFuncGlobal->GetParamGlobal()->Sequence_FileName
				,EntryPointToFuncGlobal->GetParamGlobal()->IODLL_FileName
				,EntryPointToFuncGlobal->GetParamGlobal()->IODefine_FileName
				,ErrorLine
				,EntryPointToFuncGlobal->GetParamGlobal()->IOSomething
				)==false){
			QString  msg=QString("Sequence Error:Line ")
						+ErrorLine;
			QMessageBox Q("Error"
						, msg, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			Ret=1;
			goto	ClosePoint;
		}
		w.setWindowTitle(Seq->GetTitle());
		Seq->start();
	}
	if(NoCamDevice==false){
		int32 ErrorCode;
		if(ExeIns->InitialCamera(ErrorCode)==false){
			QString  msg=QString("Camera Error Code=")
						+QString::number(ErrorCode,16);
			QMessageBox::warning (NULL, "Error", msg);
			Ret=2;
			goto	ClosePoint;
		}
		if(ExeIns->LoadDefault()==false){
			if(ExeIns->LoadDefaultOldVer()==false){
				QMessageBox::warning (NULL, "Alert"
										, "Loading error");
			}
		}
	}
	*/
	
	w.Initial(ExeIns);
    w.show();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

	EntryPointToFuncGlobal->GetLayersBase()->CloseInformed();

	Ret=a.exec();

	EntryPointToFuncGlobal->GetLayersBase()->CloseOne();

	ClosePoint:;

	for(int i=0;i<UnitCount;i++){
		if(ExeIns[i]!=NULL){
			ExeIns[i]->terminate();
			ExeIns[i]->wait(1000);
			delete	ExeIns[i];
		}
	}

	return Ret;
}

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RepairStation\RepairStation\main.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "RepairStationResource.h"

#include <QApplication>
#include "RepairStation.h"
#include "connection.h"
#include "XGUI.h"
#include "XDataInExe.h"
#include "XExecuteInspect.h"
#include "itemlistwindow.h"
#include "propertylist.h"
#include "XDataInLayerForRepair.h"
#include "XSequenceRepairLocal.h"

#include "SingleExecute.h"
#include <QMessageBox>
#include "XFileRegistry.h"
#include "XShowVersion.h"
#include <QFlags>
#include <QNamespace.h>
#include "PasswordManager.h"
#include "PasswordEventOperator.h"

#include <QProcess>

#define	HASP_KEY	"mk923yhd"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

ItemListWindow	*MainItem;
PropertyList	*MainProperty;
//extern	EntryPointForGlobal	EntryPointToFunc;

static	void	MesssageOutForSequence(int N)
{
	EntryPointToFuncGlobal->GetLayersBase()->GetSequenceInstance()->MessageOutExec(N);
}
/*
	Commandline option

	A[Path]			Set current path to [Path]
	S[Filename]		Load "save.dat"
	X[Filename]		Load "XmlConnect.dat"
	R[Filename]		Load "RepairSetting.dat"
	/NO_SEQUENCE	No Load "sequence.dat"
	/EP				Boot PasswordManager Mode
*/

int main(int argc, char *argv[])
{
	if(CheckExeVersion(argc, argv)==false)
		return 1;

	QApplication a(argc, argv);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

	FileRegistry	*FRegistry		=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);
	LangSolver.SetLanguage(LanguageCode);
///	LangSolver.SetLanguage(1);

	//二重起動防止
	if(SingleExecute("RepairStation.exe")==false){
		QMessageBox::critical(NULL, "Cannot start application","Application has already started.");
		return(1);
	}

#ifdef HASP_ENABLE
	//HASPのチェック
	if(RepairBase::HaspCheck(HASP_KEY)==false){
		QMessageBox::critical ( NULL, "Hasp Error", "Mismatch Hasp code", QMessageBox::Ok);
		return 0;
	}
#endif

	QString	DefaultSave_DotFileName			=/**/"save-r.dat";
	QString	DefaultXmlConnect_DotFileName	=/**/"XmlConnect-r.dat";
	QString	DefaultRepairSetting_DotFileName=/**/"RepairSetting.dat";

	for(int i=0;i<argc;i++){
		if(*argv[i]=='A' || *argv[i]=='a'){
			char	*fp=argv[i]+1;
			QString	AbsPath(fp);
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultSave_DotFileName=fp;
		}
		else if((*argv[i]=='X' || *argv[i]=='x') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultXmlConnect_DotFileName=fp;
		}
		else if((*argv[i]=='R' || *argv[i]=='r') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			DefaultRepairSetting_DotFileName=fp;
		}
	}

	//Load "save.dat"
	createConnection(DefaultSave_DotFileName);

	//メインフォームの作成
	RepairStation w(DefaultXmlConnect_DotFileName,DefaultRepairSetting_DotFileName);

	w.SetSaveFileName(DefaultSave_DotFileName);

	//RepairSetting.datのResolutionを反映
	int Resolution=0;
	//int n = w.GetRepairSettingList().count();
	if(w.GetRepairSettingList().count()>6){
		Resolution=w.GetRepairSettingList().at(6).toInt();
	}

	GUIInitialData	=new GUIInitializer();
	EntryPointToFuncGlobal->GetLayersBase()->SetCurrentPath(QDir::currentPath());
	EntryPointToFuncGlobal->GetParamGlobal()->LoadDefault();
	((LayersBaseForRepair *)EntryPointToFuncGlobal->GetLayersBase())->SetResolution(Resolution);
	QString	Msg;
	EntryPointToFuncGlobal->GetGUIInstancePack()->InitialLayers(Msg);

	ThreadSequence	*Seq=NULL;
	//Sequence.datがあれば組み込む
	bool ShowSequence=false;
	if(a.arguments().contains("/NO_SEQUENCE")==false){
		if(QFile::exists(EntryPointToFuncGlobal->GetParamGlobal()->Sequence_FileName)==true){
			SeqControlParamData=new SeqControlParam(EntryPointToFuncGlobal->GetLayersBase(),&w);
			Seq=new ThreadSequence(EntryPointToFuncGlobal->GetLayersBase(),&w);
			EntryPointToFuncGlobal->GetLayersBase()->SetSequenceInstance(Seq);
			EntryPointToFuncGlobal->GetLayersBase()->MesssageOutForSequence=::MesssageOutForSequence;
			Seq->SetFunction(_XSeqLocalInit
							,_SetDataSpecialOperand
							,_GetDataSpecialOperand
							,_SetDataSpecialBitOperand
							,_GetDataSpecialBitOperand
							,_SetDataSpecialStringOperand
							,_GetDataSpecialStringOperand);
			QString	ErrorLine;
			if(Seq->LoadStartSequenceFile(&w
					,EntryPointToFuncGlobal->GetParamGlobal()->Sequence_FileName
					,EntryPointToFuncGlobal->GetParamGlobal()->IODLL_FileName
					,EntryPointToFuncGlobal->GetParamGlobal()->IODefine_FileName
					,ErrorLine)==false){
				QString  msg=QString("Sequence Error:Line ")
							+ErrorLine;
				QMessageBox Q( "Error"
							, msg, QMessageBox::Critical
							, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
				return(1);
			}
			Seq->start();
			ShowSequence=true;
		}
	}
	w.SetParam(ShowSequence);
	w.show();

	PasswordManager *pwm = NULL;
	if(a.argc()>=2 && a.arguments().contains("/EP")){
		pwm = new PasswordManager();
		//pwm->setWindowFlags(Qt::WindowStaysOnTopHint);
		pwm->setWindowModality(Qt::WindowModal);
		PasswordEventOperator::setUnsealPassword(true);
		PasswordEventOperator *peo = new PasswordEventOperator;
		QObject::connect(pwm, SIGNAL(dataChanged()), peo, SLOT(update()));
		w.setWindowTitle(w.windowTitle() + " - No Password Mode");
		pwm->show();
	}

	#ifdef _MSC_VER
	if(_CrtCheckMemory()==false){
		return(-1);
	}
	#endif
	EntryPointToFuncGlobal->GetLayersBase()->CloseInformed();

	bool	ret=a.exec();
	if(Seq!=NULL){
		Seq->SetTerminateFlag();
		for(time_t t=time(NULL);time(NULL)-t<60;){
			if(Seq->IsAliveMode()==false){
				break;
			}
		}
		Seq->wait(5000);
		if(Seq!=NULL && Seq->isFinished()==false){
			Seq->terminate();
			Seq->wait(1000);
		}

		delete	Seq;
		Seq=NULL;
	}
	return ret;
}

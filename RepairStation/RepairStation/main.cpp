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

	//���d�N���h�~
	if(SingleExecute("RepairStation.exe")==false){
		QMessageBox::critical(NULL, "Cannot start application","Application has already started.");
		return(1);
	}

#ifdef HASP_ENABLE
	//HASP�̃`�F�b�N
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

	//���C���t�H�[���̍쐬
	RepairStation w(DefaultXmlConnect_DotFileName,DefaultRepairSetting_DotFileName);

	w.SetSaveFileName(DefaultSave_DotFileName);

	//RepairSetting.dat��Resolution�𔽉f
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
	//Sequence.dat�������Αg�ݍ���
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
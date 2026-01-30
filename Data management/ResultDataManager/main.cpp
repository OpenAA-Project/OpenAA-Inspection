/*
 * Copyright (C) 2023
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

#include "ResultDataManager.h"
#include <QApplication>
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include "XGUI.h"
#include "XDataInExe.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "hasplib.h"
#include "Regulus64Version.h"
#include "XShowVersion.h"
#include "DeleteThread.h"
#include <QProgressDialog>

#include "ResultDataManagerResource.h"

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return "InspectionGeneral.lng";
}

DeleteThread *DelThread = new DeleteThread(NULL);

void delThreadEndFunc()
{
	DelThread->pause();// ���U���~
	QTime waitTime;
	waitTime.start();
	QProgressDialog process;// �󋵂̃v���O���X�_�C�A���O
	process.setCancelButton(NULL);// �L�����Z���{�^���Ȃ�
	process.setRange(0, DelThread->remainFileCount());// �폜�����ő��l
	// ���x���X�V�̃X���b�g�ڑ�
	QObject::connect(DelThread, SIGNAL(deletedFile(const QString &)), &process, SLOT(setLabelText(const QString &)), Qt::ConnectionType::QueuedConnection);

	QTime time;// �X�V�^�C�}�[

	// �X�^�[�g
	time.start();
	DelThread->pause(false);
	while(DelThread->remainFileCount()!=0){
		if(time.elapsed()>1000){// �P�b���o�[���X�V
			process.setValue(process.maximum()-DelThread->remainFileCount());
			time.restart();
		}
		
		qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);
	}

	delete DelThread;// �X���b�h�폜
}

int main(int argc, char *argv[])
{
	QString	GlobalParmaFileName;
	QString	AbsPath;
	QString	UserPath;
	bool	DupOK=true;
	QString	Msg;

	if(CheckExeVersion(argc, argv)==false)
		return 1;
	
 	for(int i=1;i<argc;i++){
		if((*argv[i]=='A' || *argv[i]=='a') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			AbsPath	=fp;
			QDir::setCurrent(AbsPath);
		}
		else if((*argv[i]=='Q' || *argv[i]=='q') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			UserPath	=fp;
		}
		else if((*argv[i]=='S' || *argv[i]=='s') && *(argv[i]+1)!=':'){
			char	*fp=argv[i]+1;
			GlobalParmaFileName=fp;
		}
	}
	EntryPointBase	*e	=MakeEntryPointForGlobal();
	LayersBase	*Layers	=new LayersBase(e);
	e->SetLayersBase(Layers);
	Layers->SetCurrentPath(QDir::currentPath());
	Layers->SetUserPath(UserPath);

	GUIInitializer	*G=new GUIInitializer(Layers);
	Layers->SetGUIInitializer(G);

	FileRegistry	*FRegistry		=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);

	LanguagePackage	LangPkg;
	LangPkg.LoadSolutionFromFile(/**/"DataManagement.lng");

	LangSolver.SetLanguage(LangPkg,LanguageCode);

	DelThread->start();

	QApplication a(argc, argv);
	ResultDataManager w(Layers);
	w.show();
	int ret = a.exec();

	delThreadEndFunc();

	return ret;
}
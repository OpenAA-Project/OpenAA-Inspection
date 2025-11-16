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
	DelThread->pause();// 一旦停止
	QTime waitTime;
	waitTime.start();
	QProgressDialog process;// 状況のプログレスダイアログ
	process.setCancelButton(NULL);// キャンセルボタンなし
	process.setRange(0, DelThread->remainFileCount());// 削除数が最大値
	// ラベル更新のスロット接続
	QObject::connect(DelThread, SIGNAL(deletedFile(const QString &)), &process, SLOT(setLabelText(const QString &)), Qt::ConnectionType::QueuedConnection);

	QTime time;// 更新タイマー

	// スタート
	time.start();
	DelThread->pause(false);
	while(DelThread->remainFileCount()!=0){
		if(time.elapsed()>1000){// １秒ずつバーを更新
			process.setValue(process.maximum()-DelThread->remainFileCount());
			time.restart();
		}
		
		qApp->processEvents(QEventLoop::ProcessEventsFlag::ExcludeUserInputEvents);
	}

	delete DelThread;// スレッド削除
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

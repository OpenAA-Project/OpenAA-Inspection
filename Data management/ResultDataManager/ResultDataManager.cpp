#include "ResultDataManagerResource.h"
#include "ResultDataManager.h"
#include "ManageByLot.h"
#include "ManageByDayTime.h"
#include "SettingForm.h"
#include "XDatabase.h"
#include "XDataInExe.h"
#include "XGUI.h"
#include <QMessageBox>

ResultDataManager::ResultDataManager(LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	//ui.pushButtonByDayTime->setVisible(false);

	RParam.LoadDefault(GetLayersBase()->GetUserPath());
	KDatabase=NULL;
}

ResultDataManager::~ResultDataManager()
{

}

void ResultDataManager::on_pushButtonByLot_clicked()
{
	if(ConnectDatabase()==false){
		return;
	}

	ManageByLot	D(GetLayersBase(),&RParam);
	GetLayersBase()->CloseInformed();
	D.exec();
}

void ResultDataManager::on_pushButtonByDayTime_clicked()
{
	if(ConnectDatabase()==false){
		return;
	}
	ManageByDayTime	D(GetLayersBase(),&RParam);
	GetLayersBase()->CloseInformed();
	D.exec();
}

void ResultDataManager::on_pushButtonSetting_clicked()
{
	SettingForm	D(GetLayersBase(),&RParam);
	D.exec();
}

void ResultDataManager::on_pushButtonClose_clicked()
{
	close();
}


bool	ResultDataManager::ConnectDatabase(void)
{
	QString	Msg;
	if(KDatabase==NULL){
		GetLayersBase()->InitialDatabaseLoader(Msg);
	}

	if(KDatabase==NULL || KDatabase->IsExistDatabase()==false){

		KDatabase=new LocalDatabaseBasicClass(GetLayersBase()->GetDatabaseLoader()
											,RParam.DatabaseFileName
											,RParam.DatabaseHost
											,RParam.DatabasePort
											,0,0);
	
		if(KDatabase->IsExistDatabase()==false){
			return false;
		}
		if(GetLayersBase()->OpenDatabase(*KDatabase)==false){
			QMessageBox::critical(NULL
						, /**/"Database Error"
						, LangSolver.GetString(ResultDataManager_LS,LID_0)/*"データベースの接続に失敗しました"*/
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			return false;
		}
		GetLayersBase()->LoadLevelFolderContainerFromDB();
	}
	return true;
}
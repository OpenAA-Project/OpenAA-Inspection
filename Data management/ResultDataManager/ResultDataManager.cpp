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
						, LangSolver.GetString(ResultDataManager_LS,LID_0)/*"�f�[�^�x�[�X�̐ڑ��Ɏ��s���܂���"*/
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			return false;
		}
		GetLayersBase()->LoadLevelFolderContainerFromDB();
	}
	return true;
}
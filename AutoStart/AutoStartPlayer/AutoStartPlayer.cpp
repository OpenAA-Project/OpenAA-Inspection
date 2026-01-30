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



#include "AutoStartPlayer.h"
#include "AutoStartParamDialog.h"
#include "XDataInLayer.h"

AutoStartPlayer::AutoStartPlayer(const QString &_UserPath
								,const QString &SettingFileName ,const QString &_PlayerExe ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),Param()
{
	ui.setupUi(this);

	UserPath=_UserPath;
	Param.SetDefaultFileName(SettingFileName);
	Param.LoadDefault(LayersBase::GetUserPath(UserPath));

	PlayerExe=_PlayerExe;
	LThread=new ThreadAutoStart();
	connect(LThread,SIGNAL(OnLoop(int)),this,SLOT(OnLoop(int)),Qt::QueuedConnection);
	LThread->SpareSec	=Param.LoopCount;
	LThread->SArg		=Param.Arguments;
	LThread->PlayerExe	=PlayerExe;
	ui.dialLoop->setMaximum(Param.LoopCount);
	ui.labelArguments->setText(Param.Arguments);
	LThread->start();
	move(0,0);
}

AutoStartPlayer::~AutoStartPlayer()
{

}

void AutoStartPlayer::closeEvent ( QCloseEvent * event )
{
	if(LThread->GetOnExecuting()==true)
		event->ignore();
	else
		event->accept();
}

void	AutoStartPlayer::OnLoop(int n)
{
	ui.dialLoop->setValue(n);

	if(ui.toolButtonStop->isChecked()==true){
		LThread->SetStop();
		ui.pushButtonStart->setEnabled(false);
	}
}

void AutoStartPlayer::on_pushButtonStart_clicked()
{
	LThread->SetExec();
}

void AutoStartPlayer::on_pushButtonParam_clicked()
{
	LThread->SetStop();
	AutoStartParamDialog	D(&Param);
	if(D.exec()==(int)true){
		Param.SaveDefault(LayersBase::GetUserPath(UserPath));
	}
	LThread->SetRestart();
}

void AutoStartPlayer::on_toolButtonStop_clicked()
{
	if(ui.toolButtonStop->isChecked()==true){
		LThread->SetStop();
		ui.pushButtonStart->setEnabled(false);
	}
	else{
		LThread->SetRestart();
		ui.pushButtonStart->setEnabled(true);
	}
}
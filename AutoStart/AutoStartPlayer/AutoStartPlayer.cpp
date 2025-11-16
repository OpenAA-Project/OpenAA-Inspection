/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\AutoStartPlayer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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
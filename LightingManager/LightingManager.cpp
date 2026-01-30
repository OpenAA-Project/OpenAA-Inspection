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

#include "LightingManagerResource.h"
#include <QtGui>
#include <QFileDialog>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include "LightingManager.h"
#include "XFileRegistry.h"

LanguagePackage	LangPack;


LightingManager::LightingManager(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	//???e?I??
	FileRegistry	*FRegistry		=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);
	LangPack.LoadSolutionFromFile(/**/"InspectionGeneral.lng");
	LangSolver.SetLanguage(LangPack,LanguageCode);

	ui.setupUi(this);

	IsShutdown	=false;
	DoneExit	=false;

	setWindowFlags(Qt::WindowStaysOnTopHint);	//?i?E?O?E?E?\?|
//	setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);

	//?N?R???O?I?a??
	StartTime=time(NULL);

	//Timer?I?Y?e
	TimerMonitoring.setInterval(60000);
	TimerMonitoring.setSingleShot(false);
	TimerMonitoring.start();
	connect(&TimerMonitoring,SIGNAL(timeout()),this,SLOT(SlotTimerMonitoring()));

	//?w?i?F???]?p?X?^?C???V?[?g?��???n
	Index=0;
	BlinkStyleSheet[0]=LangSolver.GetString(LightingManager_LS,LID_0)/*"QGroupBox{background-color:yellow;}"*/;
	BlinkStyleSheet[1]=LangSolver.GetString(LightingManager_LS,LID_1)/*"QGroupBox{background-color:red;}"*/;

	createActions();
	createTrayIcon();

	connect(ui.pbResetTotalSumHour	,SIGNAL(clicked())			,this,SLOT(pbResetTotalSumHourClicked()));
	connect(ui.pbDetail				,SIGNAL(clicked(bool))		,this,SLOT(pbDetailClicked(bool)));
	connect(ui.sbWarmMinute			,SIGNAL(valueChanged(int))	,this,SLOT(sbWarmMinuteValueChanged(int)));
	connect(ui.sbChangeHour			,SIGNAL(valueChanged(int))	,this,SLOT(sbChangeHourValueChanged(int)));
	connect(ui.chkIsShowWidget		,SIGNAL(clicked(bool))		,this,SLOT(chkIsShowWidgetClicked(bool)));
	connect(ui.chkIsCloseWidget		,SIGNAL(clicked(bool))		,this,SLOT(chkIsCloseWidgetClicked(bool)));
	connect(ui.gbIsStartExe			,SIGNAL(clicked(bool))		,this,SLOT(gbIsStartExeClicked(bool)));
	connect(ui.tbStartExe			,SIGNAL(clicked())			,this,SLOT(tbStartExeClicked()));
	connect(ui.pbShowMessage		,SIGNAL(clicked())			,this,SLOT(pbShowMessageClicked()));
	connect(trayIcon				,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
			this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	trayIcon->show();
	resize(width(),270);

	//?Y?e?i?n?I?C??
	WarmMinute		=0;
	ChangeHour		=0;
	TotalSumHour	=0;
	IsShowWidget	=true;
	IsCloseWidget	=true;
	IsStartExe		=false;
	StartExe		=/**/"";
	QFile	mfile(/**/"./LightingManager.dat");
	if(mfile.open(QIODevice::ReadOnly)==true){
		QTextStream mystream(&mfile);
		QString myString;
		while (!mystream.atEnd()){
			for(int Cnt=0;!mystream.atEnd();Cnt++){
				switch(Cnt){
				case 0:
					SetWarmMinute(mystream.readLine().toInt());			//?g?@???O
					break;
				case 1:
					SetChangeHour(mystream.readLine().toInt());			//?A???d?�E?U?A???O
					break;
				case 2:
					SetTotalSumHour(mystream.readLine().toLongLong());	//?Y?v???O
					break;
				case 3:
					SetIsShowWidget(mystream.readLine().toInt());		//?N?R???E?a?E?d?\?|?�E?e
					break;
				case 4:
					SetIsCloseWidget(mystream.readLine().toInt());		//?g?@?I?1?a?A?a?E?d?A?��?e
					break;
				case 5:
					SetIsStartExe(mystream.readLine().toInt());			//?g?@?I?1?a?A?N?R?�E?e?\?t?g?d?w?e?�E?e
					break;
				case 6:
					SetStartExe(mystream.readLine());					//?g?@?I?1?a?A?N?R?�E?e?\?t?g
					break;
				}
			}
			mfile.close();
		}
	}

	//?a?E?I?X?V
	SettingUpdate();
	SlotTimerMonitoring();

	if(IsShowWidget==true){
		show();
	}

	//?a?E?\?|???I???e?I??
	LangSolver.SetUI(this);
}

LightingManager::~LightingManager()
{
}

void LightingManager::SlotCommitDataRequest(QSessionManager &manager)
{
	//?I?1???O?I?a??
	TerminationTime=time(NULL);

	IsShutdown=true;
	if(manager.allowsInteraction()){
		QFile	mfile(/**/"./LightingManager.dat");
		if(mfile.open(QIODevice::WriteOnly)==true){
			QTextStream mystream(&mfile);
			mystream << QString::number(WarmMinute) << Qt::endl;
			mystream << QString::number(ChangeHour) << Qt::endl;
			mystream << QString::number(TotalSumHour+TerminationTime-StartTime) << Qt::endl;
			mystream << QString::number(IsShowWidget) << Qt::endl;
			mystream << QString::number(IsCloseWidget) << Qt::endl;
			mystream << QString::number(IsStartExe) << Qt::endl;
			mystream << StartExe;
			mfile.close();
		}
	}
}

void LightingManager::closeEvent(QCloseEvent *event)
{
	if(trayIcon->isVisible()){
//		QMessageBox::information(this, "Systray","The program will keep running in the system tray."));
		hide();

		//?V???b?g?_?E?? or ?e?R?I?1?c?C???c
		if(IsShutdown==true || DoneExit==true){
			event->accept();
		}
		else{
			event->ignore();
		}
	}
}

void LightingManager::pbResetTotalSumHourClicked()
{
	int ret=QMessageBox::warning(this,LangSolver.GetString(LightingManager_LS,LID_5)/*"?m?F???b?Z?[?W"*/,
									LangSolver.GetString(LightingManager_LS,LID_6)/*"?Y?v???O?d???Z?b?g?��?U?�E?c?H"*/,
									QMessageBox::Yes | QMessageBox::Cancel,
									QMessageBox::Cancel);
	if(ret==QMessageBox::Yes){
		TotalSumHour=0;
		TimerMonitoring.setInterval(60000);
		SlotTimerMonitoring();
	}
}

void LightingManager::pbDetailClicked(bool checked)
{
	if(checked==true){
		resize(width(),480);
	}
	else{
		resize(width(),270);
	}
}

void LightingManager::tbStartExeClicked()
{
	QString ExecuteFile=QFileDialog::getOpenFileName(this, LangSolver.GetString(LightingManager_LS,LID_7)/*"Select Execute File"*/,
													LangSolver.GetString(LightingManager_LS,LID_8)/*"/home"*/,
													LangSolver.GetString(LightingManager_LS,LID_9)/*"Execute File (*.lnk)"*/);
	if(ExecuteFile.isEmpty()){
		return;
	}
	ui.leStartExe->setText(ExecuteFile);
	SetStartExe(ExecuteFile);
}

void LightingManager::pbShowMessageClicked()
{
	QSystemTrayIcon::MessageIcon icon=QSystemTrayIcon::Warning;
	trayIcon->showMessage(LangSolver.GetString(LightingManager_LS,LID_10)/*"?A???d?�E?U?A???O?E?E?e?U?��?U?��???I?I"*/,
						  LangSolver.GetString(LightingManager_LS,LID_11)/*"?Y?v???O?a?A???d?�E?U?A???O?d?z?|?U?��???B\n?A???d?d?�E?��?A?o?3?��?B"*/,
						  icon,INT_MAX);
}

void LightingManager::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) {
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		showNormal();
		break;
	case QSystemTrayIcon::MiddleClick:
		pbShowMessageClicked();
		break;
	default:
		;
	}
}

void LightingManager::SlotTimerMonitoring()
{
	//???O?I?A??
	time_t	ElapsedTime=time(NULL)-StartTime;

//	struct tm *timeObject;
//	timeObject=localtime(&ElapsedTime);
//	int ElapsedMinute=timeObject->tm_min;
	int ElapsedMinute=ElapsedTime/60;

	time_t TotalSumHourPlus=TotalSumHour+ElapsedTime;
//	timeObject=localtime(&TotalSumHourPlus);
//	int ElapsedHour=timeObject->tm_hour;
	int ElapsedHour=TotalSumHourPlus/3600;

	//?a?E?I?X?V
	int RemainingTime;
	if((RemainingTime=WarmMinute-ElapsedMinute)<0){
		RemainingTime=0;
	}
//	ui.lcdElapsedTime	->display(ElapsedMinute);
	ui.lcdElapsedTime	->display(RemainingTime);
	ui.lcdTotalSumHour	->display(ElapsedHour);
	if(WarmMinute!=0){
		ui.pgbElapsedTime	->setValue(100*ElapsedMinute/WarmMinute);
	}

	//?A???d?�E?U?A???O?E?E?A???c
	if(ChangeHour!=0 && ElapsedHour>=ChangeHour){
		ui.lbMainMessage->setText(LangSolver.GetString(LightingManager_LS,LID_12)/*"?A???d?�E?U?A???O?E?E?e?U?��?U?��???I?I"*/);
		//???b?Z?[?W
		QSystemTrayIcon::MessageIcon icon=QSystemTrayIcon::Warning;
		trayIcon->showMessage(LangSolver.GetString(LightingManager_LS,LID_13)/*"?A???d?�E?U?A???O?E?E?e?U?��?U?��???I?I"*/,
							  LangSolver.GetString(LightingManager_LS,LID_14)/*"?Y?v???O?a?A???d?�E?U?A???O?d?z?|?U?��???B\n?A???d?d?�E?��?A?o?3?��?B"*/,
							  icon,INT_MAX);
		//?w?i
		Index^=1;
		ui.gbMainFrame->setStyleSheet(BlinkStyleSheet[Index]);
		TimerMonitoring.setInterval(500);
	}
	else if(WarmMinute!=0){
		//?g?@???O?E?E?A???c
		if(ElapsedMinute>=WarmMinute){
			ui.lbMainMessage->setText(LangSolver.GetString(LightingManager_LS,LID_15)/*"?g?@?^?]?a?R?1?��?U?��??"*/);
			if(ElapsedMinute==WarmMinute){
				if(isHidden()==true){
					//???b?Z?[?W
					QSystemTrayIcon::MessageIcon icon=QSystemTrayIcon::Information;
					trayIcon->showMessage(LangSolver.GetString(LightingManager_LS,LID_16)/*"?g?@?^?]?a?R?1?��?U?��??"*/,
										  LangSolver.GetString(LightingManager_LS,LID_17)/*"?g?@?^?]?a?R?1?��?U?��???B\n???�C?d?J?n?��?A?o?3?��?B"*/,
										  icon,INT_MAX);
				}
				else if(IsCloseWidget==true){
					hide();
				}
			}
		}
		//?w?i
		char strStyleSheet[256];
		sprintf(strStyleSheet
				,/**/"QGroupBox{background-color: qlineargradient( x1: 0, y1: 0, x2:%f, x2: %f, stop: 0 #FF92BB, stop: 1 white);}"
				,0.5+(double)ElapsedMinute/WarmMinute,0.5+(double)ElapsedMinute/WarmMinute);
		ui.gbMainFrame->setStyleSheet(strStyleSheet);
	}
}

void LightingManager::SlotClose()
{
	DoneExit=true;
	close();
}

void LightingManager::createActions()
{
	restoreAction=new QAction(LangSolver.GetString(LightingManager_LS,LID_19)/*"&Restore"*/,this);
	connect(restoreAction,SIGNAL(triggered()),this,SLOT(showNormal()));
	exitAction=new QAction(LangSolver.GetString(LightingManager_LS,LID_20)/*"&Exit"*/,this);
	connect(exitAction,SIGNAL(triggered()),this,SLOT(SlotClose()));
}

void LightingManager::createTrayIcon()
{
	trayIconMenu=new QMenu(this);
	trayIconMenu->addAction(restoreAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(exitAction);

	trayIcon=new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);

	QIcon icon(/**/":Resources/LightingManager.png");
	trayIcon->setIcon(icon);
	setWindowIcon(icon);
	trayIcon->setToolTip(LangSolver.GetString(LightingManager_LS,LID_22)/*"LightingManager"*/);
}

void LightingManager::SettingUpdate()
{
	//?Y?e?�?U?I?\?|?X?V
	ui.sbWarmMinute		->setValue	(WarmMinute);
	ui.sbChangeHour		->setValue	(ChangeHour);
	ui.chkIsShowWidget	->setChecked(IsShowWidget);
	ui.chkIsCloseWidget	->setChecked(IsCloseWidget);
	ui.gbIsStartExe		->setChecked(IsStartExe);
	ui.leStartExe		->setText	(StartExe);
}
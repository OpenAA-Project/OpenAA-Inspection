/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\AutoStartPlayer.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef AUTOSTARTPLAYER_H
#define AUTOSTARTPLAYER_H

#include <QMainWindow>
#include "ui_AutoStartPlayer.h"
#include "XAutoStartPlayerParam.h"
#include "XAutoStartThread.h"

class AutoStartPlayer : public QMainWindow
{
	Q_OBJECT

	QString		PlayerExe;
	QString		UserPath;
public:
	AutoStartPlayer(const QString &UserPath
					,const QString &SettingFileName ,const QString &PlayerExe 
					,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~AutoStartPlayer();

	ParamAutoStart	Param;
	ThreadAutoStart	*LThread;
protected:
	virtual	void closeEvent ( QCloseEvent * event )	override;
private:
	Ui::AutoStartPlayerClass ui;
private slots:
	void on_toolButtonStop_clicked();
	void on_pushButtonParam_clicked();
	void on_pushButtonStart_clicked();
	void	OnLoop(int n);
};

#endif // AUTOSTARTPLAYER_H

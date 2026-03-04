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

#ifndef LIGHTINGMANAGER_H
#define LIGHTINGMANAGER_H

#include <QSystemTrayIcon>
#include <QWidget>
#include <QTimer>
#include "ui_LightingManager.h"
#include "time.h"

class LightingManager : public QWidget
{
	Q_OBJECT

public:
	LightingManager(const QString &UserPath,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LightingManager();

	void SetWarmMinute		(int Value)		{	WarmMinute		=Value;		}
	void SetChangeHour		(int Value)		{	ChangeHour		=Value;		}
	void SetTotalSumHour	(time_t Value)	{	TotalSumHour	=Value;		}
	void SetIsShowWidget	(bool Enable)	{	IsShowWidget	=Enable;	}
	void SetIsCloseWidget	(bool Enable)	{	IsCloseWidget	=Enable;	}
	void SetIsStartExe		(bool Enable)	{	IsStartExe		=Enable;	}
	void SetStartExe		(QString Str)	{	StartExe		=Str;		}

protected:
    virtual	void closeEvent(QCloseEvent *event)	override;

private slots:
	void pbResetTotalSumHourClicked	();
	void pbDetailClicked			(bool checked);
	void sbWarmMinuteValueChanged	(int value)		{	SetWarmMinute	(value);	}
	void sbChangeHourValueChanged	(int value)		{	SetChangeHour	(value);	}
	void chkIsShowWidgetClicked		(bool checked)	{	SetIsShowWidget	(checked);	}
	void chkIsCloseWidgetClicked	(bool checked)	{	SetIsCloseWidget(checked);	}
	void gbIsStartExeClicked		(bool checked)	{	SetIsStartExe	(checked);	}
	void tbStartExeClicked			();
	void pbShowMessageClicked		();
	void iconActivated				(QSystemTrayIcon::ActivationReason reason);
	void SlotTimerMonitoring		();
	void SlotClose					();

	void SlotCommitDataRequest		(QSessionManager &manager);

private:
	Ui::LightingManagerClass ui;

    QAction			*restoreAction;
    QAction			*exitAction;
    QMenu			*trayIconMenu;
    QSystemTrayIcon	*trayIcon;

	time_t	StartTime;			
	time_t	TerminationTime;	
	QTimer	TimerMonitoring;	

	int		WarmMinute;			
	int		ChangeHour;			
	time_t	TotalSumHour;		
	bool	IsShowWidget;		
	bool	IsCloseWidget;		
	bool	IsStartExe;			
	QString	StartExe;			

	bool	IsShutdown;			
	bool	DoneExit;			
	char	Index;				
	QString BlinkStyleSheet[2];	

    void createActions();
    void createTrayIcon();
	void SettingUpdate();
};

#endif // LIGHTINGMANAGER_H
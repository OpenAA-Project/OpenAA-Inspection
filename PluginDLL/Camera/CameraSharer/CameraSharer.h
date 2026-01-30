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

#ifndef CAMERASHARER_H
#define CAMERASHARER_H

#include <QMainWindow>
#include "ui_CameraSharer.h"
#include "XServiceForLayers.h"
#include "XIntClass.h"
#include "XCameraClass.h"
#include "XCameraSharerCommon.h"
#include <QThread>
#include <QToolButton>
#include "XBoolList.h"

class	CameraSharer;

class	ThreadCamProcess : public QThread
{
	CameraSharer	*Parent;
public:
	bool	Terminated;
	ThreadCamProcess(CameraSharer *parent);

	virtual void run ();
};


class CameraSharer : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

public:
	QString CameraSettingFileName;
	CameraClass	*Cam[100];
	int			CountOfCamera;
	QStringList		ButtonNames;
	BoolList		VisibleButton;

	CameraSharerHandle	*Handle[100];
	bool		CamFlag[100];
	int			CountOfShare;
	DWORD		FirstAccessTime[100];

	int		CamNoTable[100];
	QToolButton	*AssignedButton[100];

	ThreadCamProcess	ThreadCamProcessInst;
	int			ActiveShareNo;

	QSharedMemory	ContactToCameraSharer;

public:
	CameraSharer(int CountOfCamera ,int	CountOfShare 
					,const QString &CameraDLLFileName 
					,const QString &CameraSettingFileName 
					,LayersBase *base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CameraSharer();

	void	ProcessInThread(void);
	CameraClass	*GetCam(int n)	{		return Cam[n];	}
	void	ShowSetting(int n);
	bool	LoadSettingFile(void);
	bool	SaveSettingFile(void);
	void	SetCamNo(int n ,int camNo);
	int		GetCamPointNumber(int camNo);
signals:
	void	SignalShowSetting(int Number);
	void	SignalIncrease();
	void	SignalReflectActiveNo(int ActiveNo);

private slots:
    void on_pushButtonSetting_clicked();

	void	SlotShowSetting(int Number);
	void	SlotIncrease();
	void	SlotActiveShare();

	void	SlotReflectActiveNo(int ActiveNo);
    void on_pushButtonSelect_clicked();

private:
	Ui::CameraSharerClass ui;

	virtual	void	closeEvent ( QCloseEvent * event )	override;
	virtual	void	showEvent ( QShowEvent * event )	override;
	virtual	void	moveEvent ( QMoveEvent * event )	override;

	static	QString		FileNameForKeepPosition;
	static	QString		FileNameForParam;

	bool	LoadParam(QIODevice *f);
	bool	SaveParam(QIODevice *f);
};

#endif // CAMERASHARER_H
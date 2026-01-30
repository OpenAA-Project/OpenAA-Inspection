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

#pragma once

#include "integrationcalibratecamera_global.h"
#include <QToolButton>
#include <QLabel>
#include <QTimer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrateCalibrateShowForm;

class	TimeList : public NPListSaveLoad<TimeList>
{
public:
	QTime	Time;

	TimeList(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	TimeListContainer : public NPListPackSaveLoad<TimeList>
{
public:
	TimeListContainer(void){}

	virtual	TimeList	*Create(void);
};



class	IntegrationCalibrateCamera : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
	QTimer		AutoStartCal;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QByteArray	TimeListArray;
	TimeListContainer	TimeListData;
	QTime		LastTime;
	IntegrateCalibrateShowForm	*AForm;

	IntegrationCalibrateCamera(LayersBase *Base ,QWidget *parent);
	~IntegrationCalibrateCamera();

	virtual void	Prepare(void)	override;

	void	StartAutoStartCal(void);
public slots:
	void	SlotClicked ();
private slots:
	void	ResizeAction();
	void	SlotExecuteForByteArray(const QString &Category ,const QString &KeyName ,QByteArray &data);
	void	SlotAutoStartCal();
};
class	IntegrationCmdCalibrateCamera: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdCalibrateCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
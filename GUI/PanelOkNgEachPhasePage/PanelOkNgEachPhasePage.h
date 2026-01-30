/*
 * Copyright (C) 2022
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

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include <QFont>
#include <QColor>
#include <QString>
#include <QWidget>
#include <QPaintEvent>

class	SignalOperandBit;

class	PanelOkNgEachPhasePage :public GUIFormBase
{
	bool3	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;
	int		CurrentInspectionID;
	QString	SpecialMessage;
	SignalOperandBit	*iLostResult;

public:
	QFont	MessageSize;
	ResultInspection::CriticalErrorMode	CriticalError;
	QColor	ColorOK;
	QColor	ColorNG;
	QColor	ColorHalt;
	QString	MsgOK;
	QString	MsgNG;

	QString	Message1;
	QString	Message2;

	PanelOkNgEachPhasePage(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	virtual void	ShowInEdit	(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};


class	GUICmdReqOkNG : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;
	IntList	PhaseCodes;

	GUICmdReqOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOkNG : public GUICmdPacketBase
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	GUICmdSendOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class CmdSpecialOkNgMessagePacket : public GUIDirectMessage
{
public:
	QString	Message;
	QString	Message1;
	QString	Message2;

	CmdSpecialOkNgMessagePacket(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdSendOkNG : public GUIDirectMessage
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	CmdSendOkNG(LayersBase *base):GUIDirectMessage(base){}
};
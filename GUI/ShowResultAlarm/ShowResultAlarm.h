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

#ifndef SHOWRESULTALARM_H
#define SHOWRESULTALARM_H

#include "showresultalarm_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XIntClass.h"

class	SignalOperandBit;

class	ShowResultAlarm :public GUIFormBase
{
    Q_OBJECT

	int		CurrentNGCount;
	IntList	LastLotAutoCountList;
	int		ContinuousNG;
public:
	QFont		MessageSize;
	QColor		ColorNormal;
	QColor		ColorAlarm;
	QString		MsgNormal;
	QString		MsgAlarm;
	int32		AlarmNGCountInOneResult;
	int32		AlarmNGContinuous;
	int32		SystemRegisterNo;

	ShowResultAlarm(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private:
	SignalOperandBit	*ioMode;

private slots:
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	GUICmdReqResult : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResult : public GUICmdPacketBase
{
public:
	bool	ResultOk;
	int		NGCount;

	GUICmdSendResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // SHOWRESULTALARM_H
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelOkNg\PanelOkNg.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef PANELOKNG_H
#define PANELOKNG_H

#include "panelokng_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"

class	SignalOperandBit;

class	PanelOkNg :public GUIFormBase
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

	PanelOkNg(LayersBase *Base ,QWidget *parent);
	
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
#endif // PANELOKNG_H

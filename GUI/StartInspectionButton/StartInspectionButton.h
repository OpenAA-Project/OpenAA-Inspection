/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\StartInspectionButton\StartInspectionButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef STARTINSPECTIONBUTTON_H
#define STARTINSPECTIONBUTTON_H

#include "startinspectionbutton_global.h"
#include <QPushButton>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	SignalOperandBit;

class	StartInspectionButton : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;
	bool	Started;
	volatile	bool	Calculating;

	SignalOperandBit	*iFlagSet;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
	bool	IsNecessaryLot;
	int32		WaitingMilisecForSlave;
	bool	CheckExecuteInNoMaster;
	int		StartCount;
	int		ExecutedCount;
	int		IdleLoopCounter;
	bool	UseRetry;
	int32	RegNoInFlagSet;

	StartInspectionButton(LayersBase *Base ,QWidget *parent);
	~StartInspectionButton(void);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

	virtual	void keyPressEvent ( QKeyEvent * event )	override;
	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandStart(void);
protected:
	virtual	bool OnIdle(void)	override;
public slots:
	//void SlotClicked (bool checked);
	void	SlotToggled (bool checked);
private slots:
	void	ResizeAction();
};

//==============================================================
class	GUICmdStartInspect : public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		Layer;
	int32		StrategicNumber;

	GUICmdStartInspect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdStartInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyInspect : public GUICmdPacketBase
{
public:

	GUICmdReplyInspect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReplyInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdGetStateStartInspection : public GUIDirectMessage
{
public:
	bool		StartInspectionOn;

	CmdGetStateStartInspection(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStateStartInspection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGoStateStartInspection : public GUIDirectMessage
{
public:

	CmdGoStateStartInspection(LayersBase *base):GUIDirectMessage(base){}
	CmdGoStateStartInspection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // STARTINSPECTIONBUTTON_H

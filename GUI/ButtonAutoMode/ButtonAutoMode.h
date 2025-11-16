/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoMode\ButtonAutoMode.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef BUTTONAUTOMODE_H
#define BUTTONAUTOMODE_H

#include "buttonautomode_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	SignalOperandBit;

class	ButtonAutoMode : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	bool	SyncMode;
	SignalOperandBit	*iFlagSet;
	bool	CurrentState;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIconDown;
	QImage	ButtonIconUp;
	bool	DefaultPushed;
	int32	RegNoInFlagSet;

	ButtonAutoMode(LayersBase *Base ,QWidget *parent);
	~ButtonAutoMode(void);
	
	virtual void	Prepare(void)	override;
	virtual void	AfterStartSequence(void)	override;
	QTranslator Translator;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	void	CommandAutoModeON(void);
	void	CommandAutoModeOFF(void);
private:
	void	ExecuteToggled( bool checked );

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};
//--------------------------------------------------------------------------
class	CmdGetStateOnAutoMode : public GUIDirectMessage
{
public:
	bool		AutoModeOn;

	CmdGetStateOnAutoMode(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStateOnAutoMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetStateOnAutoMode : public GUIDirectMessage
{
public:
	bool		AutoModeOn;

	CmdSetStateOnAutoMode(LayersBase *base):GUIDirectMessage(base){}
	CmdSetStateOnAutoMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLockAutoMode : public GUIDirectMessage
{
public:
	bool		Enabled;

	CmdLockAutoMode(LayersBase *base):GUIDirectMessage(base){}
	CmdLockAutoMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//--------------------------------------------------------------------------

class	GUICmdSetAutoMode : public GUICmdPacketBase
{
public:
	bool	Clicked;

	GUICmdSetAutoMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // BUTTONAUTOMODE_H

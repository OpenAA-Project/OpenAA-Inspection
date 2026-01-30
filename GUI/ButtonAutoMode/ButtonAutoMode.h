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
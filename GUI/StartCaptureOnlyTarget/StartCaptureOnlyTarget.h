/*
 * Copyright (C) 2021
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

#ifndef STARTCAPTUREONLYTARGET_H
#define STARTCAPTUREONLYTARGET_H

#include "startcaptureonlytarget_global.h"
#include <QPushButton>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	StartCaptureOnlyTarget : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;
	bool	Started;
	volatile	bool	Calculating;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QColor	NormalColor;
	QColor	PushedColor;
	bool	IsNecessaryLot;
	int32		WaitingMilisecForSlave;

	StartCaptureOnlyTarget(LayersBase *Base ,QWidget *parent);
	~StartCaptureOnlyTarget(void);
	virtual void	Prepare(void)								override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

	virtual	void keyPressEvent ( QKeyEvent * event )	override;
	virtual	void	RxSync(QByteArray &f)				override;
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
class	GUICmdStartCaptureOnlyTarget: public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		Layer;
	int32		StrategicNumber;

	GUICmdStartCaptureOnlyTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdStartCaptureOnlyTarget(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReplyStartCaptureOnlyTarget : public GUICmdPacketBase
{
public:

	GUICmdReplyStartCaptureOnlyTarget(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdReplyStartCaptureOnlyTarget(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdGetStateStartCaptureOnlyTarget : public GUIDirectMessage
{
public:
	bool		StartCaptureOnlyTargetOn;

	CmdGetStateStartCaptureOnlyTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStateStartCaptureOnlyTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetStateStartCaptureOnlyTarget : public GUIDirectMessage
{
public:
	bool		StartCaptureOnlyTargetOn;

	CmdSetStateStartCaptureOnlyTarget(LayersBase *base):GUIDirectMessage(base){}
	CmdSetStateStartCaptureOnlyTarget(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // STARTCAPTUREONLYTARGET_H
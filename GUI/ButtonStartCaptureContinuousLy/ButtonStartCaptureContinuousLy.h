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

#ifndef BUTTONSTARTCAPTURECONTINUOUSLY_H
#define BUTTONSTARTCAPTURECONTINUOUSLY_H

#include "buttonstartcapturecontinuously_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonStartCaptureContinuousLy : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;

	ButtonStartCaptureContinuousLy(LayersBase *Base ,QWidget *parent);
	~ButtonStartCaptureContinuousLy(void);
	
	virtual void	Prepare(void)	override;
	QTranslator Translator;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	RxSync(QByteArray &f)	override;
	
	void	CommandStartCaptureContinuously(void);
	void	CommandStopCaptureContinuously(void);
private:
	void	ExecuteToggled( bool checked );

private slots:
	void	SlotToggled ( bool checked );
	void	ResizeAction();
};
//--------------------------------------------------------------------------
class	CmdGetStateOnStartCaptureContinuousLy : public GUIDirectMessage
{
public:
	bool		ModeOn;

	CmdGetStateOnStartCaptureContinuousLy(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStateOnStartCaptureContinuousLy(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetStateOnStartCaptureContinuousLy : public GUIDirectMessage
{
public:
	bool		ModeOn;

	CmdSetStateOnStartCaptureContinuousLy(LayersBase *base):GUIDirectMessage(base){}
	CmdSetStateOnStartCaptureContinuousLy(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLockStartCaptureContinuousLy : public GUIDirectMessage
{
public:
	bool		Enabled;

	CmdLockStartCaptureContinuousLy(LayersBase *base):GUIDirectMessage(base){}
	CmdLockStartCaptureContinuousLy(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//--------------------------------------------------------------------------

class	GUICmdSetStartCaptureContinuousLy : public GUICmdPacketBase
{
public:
	bool	Clicked;

	GUICmdSetStartCaptureContinuousLy(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONSTARTCAPTURECONTINUOUSLY_H
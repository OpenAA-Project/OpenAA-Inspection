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

#ifndef INTEGRATIONLOADMASTER_H
#define INTEGRATIONLOADMASTER_H

#include "integrationloadmaster_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationLoadMaster: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QToolButton	Button;
	QLabel		Viewnail;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	LastOpenedFileName;
	int			LastOpenedID;
	int			LastOrderMode;
	bool		LastAcsendantOrder;
	bool		EnableLoadAtFirst;
	bool		LoadedAtFirst;

	IntegrationLoadMaster(LayersBase *Base ,QWidget *parent);
	~IntegrationLoadMaster(){}

	virtual void	Prepare(void)	override;
	virtual void	ReadyParam(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	OpenDialog(void);
	bool	LoadWithoutDialog(void);
	bool	LoadOnly(int RelationCode);
private:

private slots:
	void	SlotClicked ();
	void	ResizeAction();
	void	SlotSlaveConnected();
	void	SlotSlaveDisconnected();
};

class	IntegrationCmdLoadMaster : public IntegrationCmdPacketBase
{
public:
	int		MasterCode;

	IntegrationCmdLoadMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	CmdEnableLoadAtFirst : public GUIDirectMessage
{
public:
	bool		EnableLoadAtFirst;

	CmdEnableLoadAtFirst(LayersBase *base):GUIDirectMessage(base){}
	CmdEnableLoadAtFirst(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqEnableLoadAtFirst : public GUIDirectMessage
{
public:
	bool		EnableLoadAtFirst;

	CmdReqEnableLoadAtFirst(LayersBase *base):GUIDirectMessage(base){}
	CmdReqEnableLoadAtFirst(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // INTEGRATIONLOADMASTER_H
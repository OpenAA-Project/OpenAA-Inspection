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

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include <QProgressBar>
#include <QString>
#include "XGUIPacketForDLL.h"
#include "XLightClass.h"
#include <QTcpSocket>
#include "XSocket.h"

class	XLightOpenAACam1B : public LightDLLBaseClass
{
	Q_OBJECT

	bool	Opened;
	QString Param;
	int32		LightID;
	QTcpSocket		*Socket;
	QByteArray		Received;
public:
	struct  SocketPacket	DataPacket;

	QString		IPAddress;
	QString		VersionStr;


	XLightOpenAACam1B(LayersBase *base ,const QString &LightParamStr);
	~XLightOpenAACam1B(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	ShowSettingDialog(void)				override;

	//Don't call directly
	virtual	bool	InitialPhysical(const QString &Param)	override;
	virtual	bool	ReflectPhysical(void)					override;
	virtual	bool	ReflectPhysicalTurnOn(bool LightOn)		override;

	void	GetFromDevice(void);
private slots:
	void	SlotReadyRead();
};


class	CmdReqLightOpenAACam1BPacket : public GUIDirectMessage
{
public:
	struct  SocketPacket	DataPacket;

	CmdReqLightOpenAACam1BPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLightOpenAACam1BPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetLightOpenAACam1BPacket : public GUIDirectMessage
{
public:
	struct  SocketPacket	DataPacket;

	CmdSetLightOpenAACam1BPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdSetLightOpenAACam1BPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

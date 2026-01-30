/*
 * Copyright (C) 2023
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

#ifndef XMEASUREHOLEPACKET_H
#define XMEASUREHOLEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"

class	CmdMeasureHoleDrawModePacket : public GUIDirectMessage
{
public:

	CmdMeasureHoleDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	MeasureHoleImagePanel;
class	CmdMeasureHoleDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MeasureHoleImagePanel	*ImagePanelPoint;

	CmdMeasureHoleDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdMeasureHoleGetColorMap : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MeasureHoleImagePanel	*ImagePanelPoint;

	GUICmdMeasureHoleGetColorMap(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSendAddManualMeasureHole : public GUICmdPacketBase
{
public:
	QByteArray	BItem;
	FlexArea	Area;

	GUICmdSendAddManualMeasureHole(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqMeasureHoleColorMap : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	CmdReqMeasureHoleColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdAckMeasureHoleColorMap : public GUICmdPacketBase
{
public:
	ColorLogic	Color;

	CmdAckMeasureHoleColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif
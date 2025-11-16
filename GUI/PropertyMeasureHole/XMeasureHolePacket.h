/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureHole\XMeasureHolePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
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
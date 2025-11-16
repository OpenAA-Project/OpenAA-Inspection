/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBusline\XBuslinePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XBuslinePACKET_H
#define XBuslinePACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
#include "XBuslineInspection.h"

class	BuslineDrawAttr;

class	CmdBuslineDrawEnd : public GUIDirectMessage
{
public:
	FlexArea		Area;
	IntList			LayerList;
	CmdBuslineDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSendAddManualBlock : public GUICmdPacketBase
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdSendAddManualBlock(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIReqBuslineListForPacketPack: public GUICmdPacketBase
{
public:

	GUIReqBuslineListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckBuslineListForPacketPack: public GUICmdPacketBase
{
public:
	BuslineListForPacketPack	Data;

	GUIAckBuslineListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUIReqGenerateBuslineItems: public GUICmdPacketBase
{
public:
	IntList	LibList;
	IntList	LayerList;

	GUIReqGenerateBuslineItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIReqTestMap: public GUICmdPacketBase
{
public:
	IntList	LayerList;
	GUIReqTestMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIClearMap: public GUICmdPacketBase
{
public:

	GUIClearMap(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};



#endif
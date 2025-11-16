/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyNickInspection\XNickInspectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XNickInspectionPACKET_H
#define XNickInspectionPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
#include "XNickInspection.h"

class	NickInspectionDrawAttr;

class	CmdNickInspectionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea		Area;
	IntList			LayerList;
	CmdNickInspectionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
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

class	GUIReqNickInspectionListForPacketPack: public GUICmdPacketBase
{
public:

	GUIReqNickInspectionListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIAckNickInspectionListForPacketPack: public GUICmdPacketBase
{
public:
	NickInspectionListForPacketPack	Data;

	GUIAckNickInspectionListForPacketPack(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUIReqGenerateNickInspectionItems: public GUICmdPacketBase
{
public:
	IntList	LibList;

	GUIReqGenerateNickInspectionItems(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

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
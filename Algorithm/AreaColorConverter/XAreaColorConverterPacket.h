#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaColorConverter\XAreaColorConverterPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#include <QString>
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"

class	AreaColorConverterItem;
class	GUICmdSendAddManualAreaColorConverter : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			SelectedLibID;
	IntList		LayerList;

	GUICmdSendAddManualAreaColorConverter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=================================================================================

class	AreaColorConverterListForPacket : public NPListSaveLoad<AreaColorConverterListForPacket>
{
public:
	struct{
		int		ItemID;
		int		LibID;
		int		Page;
		int		x1,y1,x2,y2;
	}Data;
	
	AreaColorConverterListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AreaColorConverterListForPacketPack : public NPListPackSaveLoad<AreaColorConverterListForPacket>
{
public:
	AreaColorConverterListForPacketPack(void){}

	virtual	AreaColorConverterListForPacket	*Create(void)	{	return new AreaColorConverterListForPacket();	}
};

//===========================================================================

class	GUICmdReqAreaColorConverterList : public GUICmdPacketBase
{
public:
	GUICmdReqAreaColorConverterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAreaColorConverterList : public GUICmdPacketBase
{
public:
	AreaColorConverterListForPacketPack	ItemListInfo;

	GUICmdSendAreaColorConverterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaColorConverterList(int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

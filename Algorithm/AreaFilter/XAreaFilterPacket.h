/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\AreaFilter\XAreaFilterPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef XAREAFILTERPACKET_H
#define XAREAFILTERPACKET_H

#include <QString>
#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "NListComp.h"

class	AreaFilterItem;
class	GUICmdSendAddManualAreaFilter : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			SelectedLibID;
	IntList		LayerList;

	GUICmdSendAddManualAreaFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//=================================================================================

class	AreaFilterListForPacket : public NPListSaveLoad<AreaFilterListForPacket>
{
public:
	struct{
		int		ItemID;
		int		LibID;
		int		Layer;
		int		Page;
		int		x1,y1,x2,y2;
	}Data;
	
	AreaFilterListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	AreaFilterListForPacketPack : public NPListPackSaveLoad<AreaFilterListForPacket>
{
public:
	AreaFilterListForPacketPack(void){}

	virtual	AreaFilterListForPacket	*Create(void)	{	return new AreaFilterListForPacket();	}
};

//===========================================================================

class	GUICmdReqAreaFilterList : public GUICmdPacketBase
{
public:
	GUICmdReqAreaFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAreaFilterList : public GUICmdPacketBase
{
public:
	AreaFilterListForPacketPack	ItemListInfo;

	GUICmdSendAreaFilterList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaFilterList(int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================
#endif
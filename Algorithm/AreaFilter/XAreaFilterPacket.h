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
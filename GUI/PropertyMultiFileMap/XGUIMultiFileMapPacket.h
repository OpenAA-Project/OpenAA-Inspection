/*
 * Copyright (C) 2015
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

#if	!defined(XGUIMultiFileMapPacket_H)
#define	XGUIMultiFileMapPacket_H

#include "XGUIPacketForDLL.h"
#include "XMultiFileMap.h"
#include "XBoolList.h"
#include "XIntClass.h"

class	GUICmdSetMultiFileMapHeader : public GUIDirectMessage
{
public:
	QString	GlobalPath;
	int32	NumbX;
	int32	NumbY;
	QString	ProductName;
	QString	PathName;

	GUICmdSetMultiFileMapHeader(LayersBase *base):GUIDirectMessage(base)			{	NumbX=NumbY=-1;	}
	GUICmdSetMultiFileMapHeader(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	NumbX=NumbY=-1;	}
};

class	GUICmdReqMultiFileMapInfo : public GUICmdPacketBase
{
public:
	int GlobalX ,GlobalY;

	GUICmdReqMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckMultiFileMapInfo : public GUICmdPacketBase
{
public:
	int	PosX,PosY;
	QString	FileName;

	GUICmdAckMultiFileMapInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif
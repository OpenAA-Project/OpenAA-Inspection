/*
 * Copyright (C) 2024
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

#if	!defined(XPropertyMakeAverageImagePacket_h)
#define	XPropertyMakeAverageImagePacket_h

#include "XGUIPacketForDLL.h"
#include "XMakeAverageImage.h"

class	CmdMakeAverageImageDrawAttr: public GUIDirectMessage
{
public:
	MakeAverageImageDrawAttr::_DrawMode	DrawMode;
	bool	ModeShowItems;
	int		VariableStrength;

	CmdMakeAverageImageDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdMakeAverageImageDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdMakeAverageImageDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdMakeAverageImageDrawEnd(LayersBase *base) :GUIDirectMessage(base) {}
	GUICmdMakeAverageImageDrawEnd(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};

class GUICmdSendAddMakeAverageImageUsageAreaItem : public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;

	GUICmdSendAddMakeAverageImageUsageAreaItem(LayersBase *Base, const QString &EmitterRoot, const QString &EmitterName, int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd, QString &EmitterRoot, QString &EmitterName);
};



class	GUICmdSetAverageToMaster: public GUICmdPacketBase
{
public:

	GUICmdSetAverageToMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqAverageCount: public GUICmdPacketBase
{
public:
	GUICmdReqAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAverageCount: public GUICmdPacketBase
{
public:
	int		AddedCount;

	GUICmdAckAverageCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdResetAverage: public GUICmdPacketBase
{
public:

	GUICmdResetAverage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	CmdReqReset: public GUIDirectMessage
{
public:
	CmdReqReset(LayersBase *base) :GUIDirectMessage(base) {}
	CmdReqReset(GUICmdPacketBase *gbase) :GUIDirectMessage(gbase) {}
};


#endif
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


#if	!defined(XPROPERTYNAMINGINGPACKET_H)
#define	XPROPERTYNAMINGINGPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XNaming.h"


class	GUICmdAddNamingArea : public GUICmdPacketBase
{
	bool			CreatedInside;
public:
	FlexArea		Area;
	QString			AreaName;
	int				Column;
	int				Row;

	GUICmdAddNamingArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdChangeNamingAttr : public GUICmdPacketBase
{
public:
	int				ItemID;
	int				GlobalPage;
	QString			AreaName;
	int			Row;
	int			Column;

	GUICmdChangeNamingAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------

class	GUICmdReqSelectedNamingItems : public GUICmdPacketBase
{
public:
	GUICmdReqSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSelectedNamingItems : public GUICmdPacketBase
{
public:
	NamingPointerStock	Stocker;

	GUICmdSendSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	void	MakeSelectedNamingList(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetSelectedNamingItems : public GUICmdPacketBase
{
public:
	NamingPointerStock	Stocker;

	GUICmdSetSelectedNamingItems(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//----------------------------------------------
class	CmdNamingDrawModePacket : public GUIDirectMessage
{
public:

	CmdNamingDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	GetCountPacket: public GUIDirectMessage
{
public:
	bool	EnabledCountMode;
	QString	Format;
	int		CountX;
	int		CountY;

	GetCountPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	ChangeToCountModePacket: public GUIDirectMessage
{
public:
	ChangeToCountModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CancelCountPacket: public GUIDirectMessage
{
public:
	CancelCountPacket(LayersBase *base):GUIDirectMessage(base){}
};

//=================================================================================

class	NamingListForPacket : public NPList<NamingListForPacket>
{
public:
	int		ItemID;
	int		Page;
	int		x1,y1,x2,y2;
	QString	AreaName;
	int		Row;
	int		Column;

	NamingListForPacket(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	NamingListForPacket	&operator=(NamingListForPacket &src);
};

class	NamingListForPacketPack : public NPListPack<NamingListForPacket>
{
public:
	NamingListForPacketPack(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	NamingListForPacketPack	&operator=(NamingListForPacketPack &src);
	NamingListForPacketPack	&operator+=(NamingListForPacketPack &src);
};

//===========================================================================

class	GUICmdReqNamingList : public GUICmdPacketBase
{
public:
	bool	IneffectiveMode;
	bool	EffectiveMode;
	GUICmdReqNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingList : public GUICmdPacketBase
{
public:
	NamingListForPacketPack	NamingInfo;

	GUICmdSendNamingList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeNamingList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqSetGroup : public GUICmdPacketBase
{
public:
	QString		GroupString;
	int			GroupID;

	GUICmdReqSetGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================
class	GUICmdReqClearGroup : public GUICmdPacketBase
{
public:
	int			GroupID;

	GUICmdReqClearGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqNamingGroupList : public GUICmdPacketBase
{
public:
	GUICmdReqNamingGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNamingGroupList : public GUICmdPacketBase
{
public:
	NamingGroupContainer	GroupData;

	GUICmdSendNamingGroupList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//----------------------------------------------

class	GUICmdReqGenerateIndex : public GUICmdPacketBase
{
public:
	GUICmdReqGenerateIndex(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif
/*
 * Copyright (C) 2012
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

#if	!defined(XShowPieceResultListPacket_h)
#define	XShowPieceResultListPacket_h

#include "XGUIPacketForDLL.h"
#include "NListComp.h"

class	ResultPieceList  : public NPListSaveLoad<ResultPieceList>
{
public:
	int		AreaNumber;
	QString	AreaName;
	enum	ResultAttr
	{
			_Ok			=1
			,_Ng		=2
			,_MaxError	=3
			,_TimeOver	=4
	}Result;

	ResultPieceList(void);

	virtual	bool	Save(QIODevice *f)	;
	virtual	bool	Load(QIODevice *f)	;
};

class	ResultPieceListContainer : public NPListPackSaveLoad<ResultPieceList>
{
public:
	ResultPieceListContainer(void){}

	virtual	ResultPieceList	*Create(void)	{	return new ResultPieceList();	}
};


class	GUICmdReqPieceList : public GUICmdPacketBase
{
public:
	int64	ShownInspectionID;

	GUICmdReqPieceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendPieceList : public GUICmdPacketBase
{
public:
	ResultPieceListContainer	ResData;

	GUICmdSendPieceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};



#endif
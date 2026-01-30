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


#if	!defined(XRESULTIMPORTANCEPACKET_H)
#define	XRESULTIMPORTANCEPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResultImportance.h"

class	GUICmdAddResultImportanceArea : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int		ImportanceLevel;

	GUICmdAddResultImportanceArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdResultImportanceDrawEnd :public GUIDirectMessage
{
public:
	FlexArea	GlobalArea;

	CmdResultImportanceDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdResultImportanceColor :public GUIDirectMessage
{
public:
	QColor	ResultImportanceColor;

	CmdResultImportanceColor(LayersBase *base):GUIDirectMessage(base){}
};

//===========================================================================
class	ResultImportanceList : public NPList<ResultImportanceList>
{
public:
	int		Page;
	int		x1,y1,x2,y2;
	int		ImportanceLevel;
	int		ItemID;

	ResultImportanceList(void){}

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	ResultImportanceListForPacketPack: public NPListPack<ResultImportanceList>
{
public:
	ResultImportanceListForPacketPack(void){}

	ResultImportanceListForPacketPack	&operator+=(ResultImportanceListForPacketPack &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	GUICmdReqResultImportanceList : public GUICmdPacketBase
{
public:
	GUICmdReqResultImportanceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendResultImportanceList : public GUICmdPacketBase
{
public:
	ResultImportanceListForPacketPack	ResultImportanceInfo;

	GUICmdSendResultImportanceList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeResultImportanceList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdChangeResultImportanceLevel : public GUICmdPacketBase
{
public:
	int		Page;
	int		ImportanceLevel;
	int		ItemID;

	GUICmdChangeResultImportanceLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	ImportanceCounter : public NPList<ImportanceCounter>
{
public:
	int		ImportanceLevel;
	int		Counter;

	ImportanceCounter(void)	{	ImportanceLevel=0;	Counter=0;	}
};

//===========================================================================

class	GUICmdSelectResultImportance : public GUICmdPacketBase
{
public:
	IntList	ImportanceLevels;

	GUICmdSelectResultImportance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
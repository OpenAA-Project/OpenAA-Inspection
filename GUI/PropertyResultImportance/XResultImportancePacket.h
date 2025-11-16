/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyResultImportance\ResultImportancePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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

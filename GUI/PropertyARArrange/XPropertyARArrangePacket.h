/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\GUI\PropertyARArrange\XARArrangePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XARArrangePacket_H)
#define	XARArrangePacket_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XLearningRegist.h"
#include "XARArrange.h"
#include "XDateTime.h"

//===========================================================================

class	ARItemList : public NPList<ARItemList>
{
public:
	int64						ItemID;
	XDateTime					CreatedTime;
	ARArrangeItem::ARResult		Result;
	DualIntClass				Position;

	ARItemList(void){}
	ARItemList(ARArrangeItem *p);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	
	ARItemList	&operator=(ARItemList &src);
};

class	ARItemListContainer : public NPListPack<ARItemList>
{
public:
	ARItemListContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ARItemListContainer	&operator+=(ARItemListContainer &src);
};

//===========================================================================

class	GUICmdReqARLearningList : public GUICmdPacketBase
{
public:
	GUICmdReqARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendARLearningList : public GUICmdPacketBase
{
public:
	LearningImagePointerContainer	LearningPointerContainer;

	GUICmdSendARLearningList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
class	GUICmdReqARArrangeList : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;

	GUICmdReqARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendARArrangeList : public GUICmdPacketBase
{
public:
	ARItemListContainer		ItemContainer;

	GUICmdSendARArrangeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==================================================================================

class	GUICmdARArrangeDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	GUICmdARArrangeDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

//==================================================================================
class	GUICmdReqAddARArrange : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	XDateTime	CreatedTime;

	GUICmdReqAddARArrange(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqLearningThumnail : public GUICmdPacketBase
{
public:
	XDateTime	CreatedTime;
	int			ImageWidth;
	int			ImageHeight;

	GUICmdReqLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendLearningThumnail : public GUICmdPacketBase
{
public:
	QImage	*Img;

	GUICmdSendLearningThumnail(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendLearningThumnail(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


//==================================================================================
#endif
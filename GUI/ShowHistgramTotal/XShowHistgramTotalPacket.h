/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\GUI\ShowHistgramTotal\XShowHistgramTotalPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XShowHistgramTotalPacket_H)
#define	XShowHistgramTotalPacket_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XHistgramByParam.h"

//===========================================================================

class	HistgramTypeList : public NPList<HistgramTypeList>
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	int			HistID;
	QString		HistName;

	HistgramTypeList(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	HistgramTypeList	&operator=(HistgramTypeList &src);
	bool				operator==(HistgramTypeList &src);
};

class	HistgramTypeListContainer : public NPListPack<HistgramTypeList>
{
public:
	HistgramTypeListContainer(void){}

	HistgramTypeListContainer	&operator=(HistgramTypeListContainer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===========================================================================

class	GUICmdReqHistgramTypeList : public GUICmdPacketBase
{
public:
	GUICmdReqHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramTypeList : public GUICmdPacketBase
{
public:
	HistgramTypeListContainer	HContainer;

	GUICmdSendHistgramTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramList(int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
class	LibraryItemList : public NPList<LibraryItemList>
{
public:
	int	LibID;
	int	ItemCount;

	LibraryItemList(void){	LibID=-1;	ItemCount=0;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	LibraryItemList	&operator=(LibraryItemList &src);
};

class	LibraryItemListContainer : public NPListPack<LibraryItemList>
{
public:
	LibraryItemListContainer(void){}

	LibraryItemList	*GetLibraryItemList(int LibID);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	GUICmdReqHistgramLibrary : public GUICmdPacketBase
{
public:
	HistgramTypeList	PointData;

	GUICmdReqHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramLibrary : public GUICmdPacketBase
{
public:
	LibraryItemListContainer	LibData;

	GUICmdSendHistgramLibrary(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramData(HistgramTypeList &Point,int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================
class	GUICmdReqHistgramTotalData : public GUICmdPacketBase
{
public:
	HistgramTypeList	PointData;
	LibraryItemList		LibData;

	GUICmdReqHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendHistgramTotalData : public GUICmdPacketBase
{
public:
	HistStepClass	Data;

	GUICmdSendHistgramTotalData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeHistgramData(HistgramTypeList &PointH,LibraryItemList &PointL,int localPage);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================
#endif
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentProjection\PropertyAlignmentProjectionPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYAlignmentProjectionPACKET_H)
#define	PROPERTYAlignmentProjectionPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignmentProjection.h"
#include "XAlignmentProjection.h"


class	GUICmdAlignmentProjectionDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	GUICmdAlignmentProjectionDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};


class	GUICmdReqAlignmentProjectionDrawMode : public GUIDirectMessage
{
public:

	GUICmdReqAlignmentProjectionDrawMode(LayersBase *base):GUIDirectMessage(base){}
};

//===========================================================================

class	AlignmentProjectionPointList : public NPList<AlignmentProjectionPointList>
{
public:
	int		ItemID;
	int		Phase;
	int		Page;
	int		Cx,Cy;
	int		XSize;
	int		YSize;
	int		PeakCount;
	
	AlignmentProjectionPointList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentProjectionPointList	&operator=(AlignmentProjectionPointList &src);
};

class	AlignmentProjectionPointListPack : public NPListPack<AlignmentProjectionPointList>
{
public:
	AlignmentProjectionPointListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentProjectionPointListPack	&operator=(AlignmentProjectionPointListPack &src);
	AlignmentProjectionPointListPack	&operator+=(AlignmentProjectionPointListPack &src);
};

//===========================================================================

class	GUICmdReqAlignmentProjectionPoint : public GUICmdPacketBase
{
public:
	int	Phase;
	int	ItemID;

	GUICmdReqAlignmentProjectionPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentProjectionPoint : public GUICmdPacketBase
{
public:
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			PeakIsolation;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	GUICmdSendAlignmentProjectionPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================

class	GUICmdReqAlignmentProjectionPointListPack : public GUICmdPacketBase
{
public:
	int	Phase;

	GUICmdReqAlignmentProjectionPointListPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentProjectionPointListPack : public GUICmdPacketBase
{
public:
	AlignmentProjectionPointListPack	List;

	GUICmdSendAlignmentProjectionPointListPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//===========================================================================

class	GUICmdReqAlignmentProjectionPutPoint : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	GUICmdReqAlignmentProjectionPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentProjectionModifyPoint : public GUICmdPacketBase
{
public:
	int			ItemID;
	QString		ItemName;
	int			PeakCount;
	double		Angle;
	int			UsageLayer;
	double		AbandonRateL;
	double		AbandonRateH;

	GUICmdReqAlignmentProjectionModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif

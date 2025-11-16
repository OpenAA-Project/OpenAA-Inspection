/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\PropertyAlignmentPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYALIGNMENTPACKET_H)
#define	PROPERTYALIGNMENTPACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignment.h"
#include "XAlignment.h"

class	AlignmentAreaList : public NPList<AlignmentAreaList>
{
public:
	int		Number;
	int		AreaID;
	QString	AreaName;
	int		Layer;
	int		GlobalPage;
	int		XSize;
	int		YSize;
	
	AlignmentAreaList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentAreaList	&operator=(AlignmentAreaList &src);
};

class	AlignmentAreaListPack : public NPListPack<AlignmentAreaList>
{
public:
	AlignmentAreaListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentAreaListPack	&operator=(AlignmentAreaListPack &src);
	AlignmentAreaListPack	&operator+=(AlignmentAreaListPack &src);
};

//===========================================================================

class	AlignmentPointList : public NPList<AlignmentPointList>
{
public:
	int		ID;
	int		GroupNumber;
	int		Layer;
	int		AreaID;
	int		ItemID;
	int		Page;
	int		Cx,Cy;
	int		XSize;
	int		YSize;
	bool	AlignmentOnOutline;
	int		SearchDot;
	int		Threshold;
	
	AlignmentPointList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentPointList	&operator=(AlignmentPointList &src);
};

class	AlignmentPointListPack : public NPListPack<AlignmentPointList>
{
public:
	AlignmentPointListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentPointListPack	&operator=(AlignmentPointListPack &src);
	AlignmentPointListPack	&operator+=(AlignmentPointListPack &src);
};

//===========================================================================

class	GUICmdReqAlignmentAreaList : public GUICmdPacketBase
{
public:
	GUICmdReqAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentAreaList : public GUICmdPacketBase
{
public:
	AlignmentAreaListPack	Area;

	GUICmdSendAlignmentAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqAlignmentPointList : public GUICmdPacketBase
{
public:
	int	GlobalPage;
	int	Layer;
	int	Number;

	GUICmdReqAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentPointList : public GUICmdPacketBase
{
public:
	AlignmentPointListPack	Points;

	GUICmdSendAlignmentPointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakePointList(LayersBase *PBase ,int Layer ,int Number);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqAlignmentPutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqAlignmentPutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentPutPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	FlexArea	PointArea;
	WORD		MoveDot;		
    WORD		Threshold;
	bool		AlignmentOnOutline;	//ó÷äsÇ≈à íuçáÇÌÇπÇ∑ÇÈÇ∆Ç´true

	GUICmdReqAlignmentPutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentModifyPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			ItemID;
	WORD		MoveDot;		
    WORD		Threshold;
	bool		AlignmentOnOutline;	//ó÷äsÇ≈à íuçáÇÌÇπÇ∑ÇÈÇ∆Ç´true

	GUICmdReqAlignmentModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentPutGroup : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	int			AreaID;
	int			GroupNumber;
	FlexArea	GroupArea;

	GUICmdReqAlignmentPutGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyAlignmentAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	bool		DeleteMode;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqModifyAlignmentAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqAlignmentAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqAlignmentAreaListPack	ActiveAreas;

	CmdSetActiveAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdSetActiveAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddArea: public GUIDirectMessage
{
public:
	CmdAddArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
//===========================================================================

class	GUICmdClickAreaButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickAreaButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickPointButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickPointButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdClickGroupButton : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdClickGroupButton(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
#endif

/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\PropertyAlignmentLargePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(PROPERTYAlignmentLargePACKET_H)
#define	PROPERTYAlignmentLargePACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XPacketAlignmentLarge.h"
#include "XAlignmentLarge.h"
#include "NListComp.h"

class	AlignmentLargeAreaList : public NPList<AlignmentLargeAreaList>
{
public:
	int		Number;
	int		AreaID;
	QString	AreaName;
	int		GlobalPage;
	int		XSize;
	int		YSize;
	AlgorithmLibraryListContainer		LimitedLib;
	XAlignmentLargeArea::_EnumPriority	Priority;
	
	AlignmentLargeAreaList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargeAreaList	&operator=(AlignmentLargeAreaList &src);
};

class	AlignmentLargeAreaListPack : public NPListPack<AlignmentLargeAreaList>
{
public:
	AlignmentLargeAreaListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargeAreaListPack	&operator=(AlignmentLargeAreaListPack &src);
	AlignmentLargeAreaListPack	&operator+=(AlignmentLargeAreaListPack &src);
};

//===========================================================================

class	AlignmentLargePointList : public NPList<AlignmentLargePointList>
{
public:
	int		ID;
	int		GroupID;
	int		AreaID;
	int		ItemID;
	int		Page;
	int		Cx,Cy;
	int		XSize;
	int		YSize;
	bool	AlignmentLargeOnOutline;
	int		MoveDotX;
	int		MoveDotY;
	int		MoveDotX2;
	int		MoveDotY2;
	bool	UsageGlobal;
	int		Threshold;
	
	AlignmentLargePointList(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargePointList	&operator=(AlignmentLargePointList &src);
};

class	AlignmentLargePointListPack : public NPListPack<AlignmentLargePointList>
{
public:
	AlignmentLargePointListPack(void){}

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	AlignmentLargePointListPack	&operator=(AlignmentLargePointListPack &src);
	AlignmentLargePointListPack	&operator+=(AlignmentLargePointListPack &src);
};

//===========================================================================

class	GUICmdReqAlignmentLargeAreaList : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentLargeAreaList : public GUICmdPacketBase
{
public:
	AlignmentLargeAreaListPack	Area;

	GUICmdSendAlignmentLargeAreaList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeAreaList(int localPage,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqAlignmentLargePointList : public GUICmdPacketBase
{
public:
	int	GlobalPage;
	int	Number;

	GUICmdReqAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignmentLargePointList : public GUICmdPacketBase
{
public:
	AlignmentLargePointListPack	Points;

	GUICmdSendAlignmentLargePointList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakePointList(LayersBase *PBase ,int Number);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================
class	GUICmdReqAlignmentLargePutArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqAlignmentLargePutArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargePutPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			AreaID;
	FlexArea	PointArea;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	bool		UsageGlobal;
	WORD		GroupID;
	bool		UseBitBuff;

	GUICmdReqAlignmentLargePutPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeModifyPoint : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			AreaID;
	int			ItemID;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	bool		UsageGlobal;
	WORD		GroupID;

	GUICmdReqAlignmentLargeModifyPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeMakeGroup : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentLargeMakeGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeRemoveGroup : public GUICmdPacketBase
{
public:

	GUICmdReqAlignmentLargeRemoveGroup(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			Layer;
	int			AreaID;

	GUICmdReqAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSendAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdSendAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Make(int localPage,int layer,int areaID,LayersBase *Base);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdReqModifyAlignmentLargeAreaInfo : public GUICmdPacketBase
{
public:
	int			AreaID;
	FlexArea	Area;
	QString		AreaName;
	bool		DeleteMode;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	GUICmdReqModifyAlignmentLargeAreaInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdSetActiveAreas : public GUICmdPacketBase
{
public:
	ReqAlignmentLargeAreaListPack	ActiveAreas;
	QString						InstForm;

	GUICmdSetActiveAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	CmdSetActiveAreas : public GUIDirectMessage
{
public:
	ReqAlignmentLargeAreaListPack	ActiveAreas;

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

class	CmdClickAreaButton : public GUIDirectMessage
{
public:
	CmdClickAreaButton(LayersBase *base):GUIDirectMessage(base){}
	CmdClickAreaButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}	
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

class	CmdClickPointButton : public GUIDirectMessage
{
public:
	CmdClickPointButton(LayersBase *base):GUIDirectMessage(base){}
	CmdClickPointButton(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}	
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

//===========================================================================

class	GUICmdClearAllAreas : public GUICmdPacketBase
{
public:

	GUICmdClearAllAreas(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdClearAllPoints : public GUICmdPacketBase
{
public:

	GUICmdClearAllPoints(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCreateAreaInMask : public GUICmdPacketBase
{
public:
	int		Priority;
	int		Erosion;
	GUICmdCreateAreaInMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAutoCreatePoint : public GUICmdPacketBase
{
public:
	int		AlignmntPointSize		;
	int		AlignmntSearchAreaDot	;
	int		AlignmntSearchAreaDot2	;

	GUICmdAutoCreatePoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqAlignmentLargeAngleList : public GUICmdPacketBase
{
public:
	int	ItemID;
	GUICmdReqAlignmentLargeAngleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckAlignmentLargeAngleList : public GUICmdPacketBase
{
public:
	DoubleList	AngleList;

	GUICmdAckAlignmentLargeAngleList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
#endif

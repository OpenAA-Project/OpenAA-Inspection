#pragma once

#include "XGUIPacketForDLL.h"
#include "XEdgeMatching.h"
#include "XEdgeMatchingLibrary.h"

//==================================================================================

class	EdgeMatchingDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	DrawModeArea	 ;
	bool	DrawModeEdge	 ;
	bool	DrawModeDirection;

	EdgeMatchingDrawAttr(void):ServiceForLayers(NULL){}
	EdgeMatchingDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	EdgeMatchingDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel);

	void	Initial(void);

	EdgeMatchingDrawAttr	&operator=(EdgeMatchingDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	EdgeMatchingDrawAttr::EdgeMatchingDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol,scol ,acol),ServiceForLayers(Base)
{
}


inline	EdgeMatchingDrawAttr	&EdgeMatchingDrawAttr::operator=(EdgeMatchingDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	DrawModeArea			=src.DrawModeArea		;
	DrawModeEdge			=src.DrawModeEdge		;
	DrawModeDirection		=src.DrawModeDirection	;

	return *this;
}
inline	bool	EdgeMatchingDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,DrawModeArea)==false)
		return false;
	if(::Save(f,DrawModeEdge)==false)
		return false;
	if(::Save(f,DrawModeDirection)==false)
		return false;

	return true;
}
inline	bool	EdgeMatchingDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,DrawModeArea)==false)
		return false;
	if(::Load(f,DrawModeEdge)==false)
		return false;
	if(::Load(f,DrawModeDirection)==false)
		return false;

	return true;
}

//----------------------------------------------------------------------

class	GUICmdEdgeMatchingReflectChangeItems : public GUIDirectMessage
{
public:
	GUICmdEdgeMatchingReflectChangeItems(LayersBase *base):GUIDirectMessage(base){}
	GUICmdEdgeMatchingReflectChangeItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddEdgeMatchingPointPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			LibID;
	int			RetItemID;

	AddEdgeMatchingPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddEdgeMatchingPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEdgeMatchingLibraryListInPastePacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetEdgeMatchingLibraryListInPastePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEdgeMatchingLibraryListInPastePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertEdgeMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertEdgeMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateEdgeMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateEdgeMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEdgeMatchingLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetEdgeMatchingLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetEdgeMatchingLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempEdgeMatchingLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempEdgeMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetEdgeMatchingLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetEdgeMatchingLibraryListPacket(LayersBase *base):GUIDirectMessage(base)			{}
	CmdGetEdgeMatchingLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdLoadEdgeMatchingLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadEdgeMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearEdgeMatchingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearEdgeMatchingLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteEdgeMatchingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteEdgeMatchingLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteEdgeMatchingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempEdgeMatchingItemPacket : public GUIDirectMessage
{
public:
	EdgeMatchingItem	*Point;
	CmdCreateTempEdgeMatchingItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempEdgeMatchingItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqTestByLibID : public GUIDirectMessage
{
public:
	IntList	LibList;
	CmdReqTestByLibID(LayersBase *base):GUIDirectMessage(base){}
	CmdReqTestByLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGenerateByLibID : public GUIDirectMessage
{
public:
	IntList	LibList;
	CmdReqGenerateByLibID(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGenerateByLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqClearTestMap : public GUIDirectMessage
{
public:
	CmdReqClearTestMap(LayersBase *base):GUIDirectMessage(base){}
	CmdReqClearTestMap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGenerateAreaWithItemLibFromMask : public GUIDirectMessage
{
public:
	int		Priority;
	int		ItemLibID;

	CmdReqGenerateAreaWithItemLibFromMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGenerateAreaWithItemLibFromMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqEdgeMatchingItem : public GUIDirectMessage
{
public:
	int	localX ,localY;
	int	RetItemID;
	int	RetLibID;
	int	RetSearchDot;
	bool	RetKeepBW;

	CmdReqEdgeMatchingItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqEdgeMatchingItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetEdgeMatchingItem : public GUIDirectMessage
{
public:
	int		ItemID;
	int		LibID;
	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;
	bool	ModeSetAll;

	CmdSetEdgeMatchingItem(LayersBase *base):GUIDirectMessage(base){}
	CmdSetEdgeMatchingItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================
class	EdgeMatchingItemList : public NPListSaveLoad<EdgeMatchingItemList>
{
public:
	struct{
		int		Page;
		int		Phase;
		int		ItemID;
		int		LibID;
		int		CenterX,CenterY;
		int		x1,y1,x2,y2;
	}Data;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	EdgeMatchingItemList::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
inline	bool	EdgeMatchingItemList::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
class	EdgeMatchingItemListPack : public NPListPackSaveLoad<EdgeMatchingItemList>
{
public:
	EdgeMatchingItemListPack(void){}

	virtual	EdgeMatchingItemList	*Create(void)	{	return new EdgeMatchingItemList();	}
};

class	CmdReqEdgeMatchingItemtPack : public GUIDirectMessage
{
public:
	EdgeMatchingItemListPack	*Items;

	CmdReqEdgeMatchingItemtPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReqEdgeMatchingItemtPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqEdgeMatchingItemAngleList : public GUIDirectMessage
{
public:
	int			ItemID;
	DoubleList	AngleList;

	CmdReqEdgeMatchingItemAngleList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqEdgeMatchingItemAngleList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	MatchAngleList : public NPListSaveLoad<MatchAngleList>
{
public:
	int		SImageNo;
	double	Angle;
	double	MatchingRate;

	MatchAngleList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	MatchAngleListContainer : public NPListPackSaveLoad<MatchAngleList>
{
public:
	virtual	MatchAngleList	*Create(void)	{	return new MatchAngleList();	}
};

inline	bool	MatchAngleList::Save(QIODevice *f)
{
	if(::Save(f,SImageNo)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}
inline	bool	MatchAngleList::Load(QIODevice *f)
{
	if(::Load(f,SImageNo)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	return true;
}

class	CmdReqBaseMatchList : public GUIDirectMessage
{
public:
	MatchAngleListContainer	*ListPoint;

	CmdReqBaseMatchList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBaseMatchList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateBaseMatch : public GUIDirectMessage
{
public:
	CmdGenerateBaseMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateBaseMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecBaseMatch : public GUIDirectMessage
{
public:
	CmdExecBaseMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdExecBaseMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//===========================================================================
class	AlignmentPointList : public NPListSaveLoad<AlignmentPointList>
{
public:
	int		LibID;
	int		ItemID;
	int		PosX1,PosY1;
	int		PosX2,PosY2;
	int		SearchDot;

	AlignmentPointList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
	
inline	bool	AlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	if(::Save(f,PosX1)==false)		return false;
	if(::Save(f,PosY1)==false)		return false;
	if(::Save(f,PosX2)==false)		return false;
	if(::Save(f,PosY2)==false)		return false;
	if(::Save(f,SearchDot)==false)	return false;
	return true;
}

inline	bool	AlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	if(::Load(f,PosX1)==false)		return false;
	if(::Load(f,PosY1)==false)		return false;
	if(::Load(f,PosX2)==false)		return false;
	if(::Load(f,PosY2)==false)		return false;
	if(::Load(f,SearchDot)==false)	return false;
	return true;
}

class	AlignmentPointListContainer : public NPListPackSaveLoad<AlignmentPointList>
{
public:
	virtual	AlignmentPointList	*Create(void)	{	return new AlignmentPointList();	}
};

class	CmdReqAlignmentPointList : public GUIDirectMessage
{
public:
	AlignmentPointListContainer	*PointList;

	CmdReqAlignmentPointList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentPointList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#pragma once

#include "XGUIPacketForDLL.h"
#include "XAlignmentShiftRotation.h"
#include "XAlignmentShiftRotationCommon.h"
#include "XAlignmentShiftRotationLibrary.h"

//==================================================================================

class	AlignmentShiftRotationDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	DrawModeArea;
	bool	DrawModeHVLines;	
	int		HVLinesPage			;
	int		HVLinesPhase		;
	int		HVLinesItemID		;
	int		HVLinesAngleIndex	;

	AlignmentShiftRotationDrawAttr(void):ServiceForLayers(NULL){}
	AlignmentShiftRotationDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	AlignmentShiftRotationDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel
				, QColor pickupcol ,int ptranparentLevel);

	void	Initial(void);

	AlignmentShiftRotationDrawAttr	&operator=(AlignmentShiftRotationDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	AlignmentShiftRotationDrawAttr	&AlignmentShiftRotationDrawAttr::operator=(AlignmentShiftRotationDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	DrawModeArea			=src.DrawModeArea		;
	DrawModeHVLines			=src.DrawModeHVLines	;
	HVLinesPage				=src.HVLinesPage		;	
	HVLinesPhase			=src.HVLinesPhase		;
	HVLinesItemID			=src.HVLinesItemID		;
	HVLinesAngleIndex		=src.HVLinesAngleIndex	;

	return *this;
}
inline	bool	AlignmentShiftRotationDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,DrawModeArea)==false)
		return false;
	if(::Save(f,DrawModeHVLines)==false)
		return false;
	if(::Save(f,HVLinesPage)==false)
		return false;
	if(::Save(f,HVLinesPhase)==false)
		return false;
	if(::Save(f,HVLinesItemID)==false)
		return false;
	if(::Save(f,HVLinesAngleIndex)==false)
		return false;

	return true;
}
inline	bool	AlignmentShiftRotationDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,DrawModeArea)==false)
		return false;
	if(::Load(f,DrawModeHVLines)==false)
		return false;
	if(::Load(f,HVLinesPage)==false)
		return false;
	if(::Load(f,HVLinesPhase)==false)
		return false;
	if(::Load(f,HVLinesItemID)==false)
		return false;
	if(::Load(f,HVLinesAngleIndex)==false)
		return false;

	return true;
}

//----------------------------------------------------------------------

class	GUICmdAlignmentShiftRotationReflectChangeItems : public GUIDirectMessage
{
public:
	GUICmdAlignmentShiftRotationReflectChangeItems(LayersBase *base):GUIDirectMessage(base){}
	GUICmdAlignmentShiftRotationReflectChangeItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentShiftRotationPointPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	int			LibID;
	int			RetItemID;

	AddAlignmentShiftRotationPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentShiftRotationPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentShiftRotationLibraryListInPastePacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAlignmentShiftRotationLibraryListInPastePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentShiftRotationLibraryListInPastePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAlignmentShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAlignmentShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAlignmentShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAlignmentShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentShiftRotationLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAlignmentShiftRotationLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentShiftRotationLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempAlignmentShiftRotationLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempAlignmentShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentShiftRotationLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetAlignmentShiftRotationLibraryListPacket(LayersBase *base):GUIDirectMessage(base)			{}
	CmdGetAlignmentShiftRotationLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdLoadAlignmentShiftRotationLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadAlignmentShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAlignmentShiftRotationLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAlignmentShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAlignmentShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAlignmentShiftRotationLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAlignmentShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempAlignmentShiftRotationItemPacket : public GUIDirectMessage
{
public:
	AlignmentShiftRotationItem	*Point;
	CmdCreateTempAlignmentShiftRotationItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentShiftRotationItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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

class	CmdReqAlignmentShiftRotationItem : public GUIDirectMessage
{
public:
	int	localX ,localY;
	int	RetItemID;
	int	RetLibID;
	int	RetSearchDot;
	bool	RetKeepBW;

	CmdReqAlignmentShiftRotationItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentShiftRotationItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAlignmentShiftRotationItem : public GUIDirectMessage
{
public:
	int		ItemID;
	int		LibID;
	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;
	bool	ModeSetAll;

	CmdSetAlignmentShiftRotationItem(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAlignmentShiftRotationItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================
class	AlignmentShiftRotationItemList : public NPListSaveLoad<AlignmentShiftRotationItemList>
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

inline	bool	AlignmentShiftRotationItemList::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
inline	bool	AlignmentShiftRotationItemList::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
class	AlignmentShiftRotationItemListPack : public NPListPackSaveLoad<AlignmentShiftRotationItemList>
{
public:
	AlignmentShiftRotationItemListPack(void){}

	virtual	AlignmentShiftRotationItemList	*Create(void)	{	return new AlignmentShiftRotationItemList();	}
};

class	CmdReqAlignmentShiftRotationItemtPack : public GUIDirectMessage
{
public:
	AlignmentShiftRotationItemListPack	*Items;

	CmdReqAlignmentShiftRotationItemtPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentShiftRotationItemtPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentShiftRotationItemAngleList : public GUIDirectMessage
{
public:
	int			ItemID;
	DoubleList	AngleList;

	CmdReqAlignmentShiftRotationItemAngleList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentShiftRotationItemAngleList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
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


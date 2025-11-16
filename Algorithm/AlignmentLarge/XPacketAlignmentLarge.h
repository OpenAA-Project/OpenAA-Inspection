/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPacketAlignmentLarge.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPACKETAlignmentLarge_H)
#define	XPACKETAlignmentLarge_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XYCross.h"
#include "XAlignmentLarge.h"


class TransformBase;

//--------------------------------------------------------------------------------------------------------

class ListAreaIDInfo : public NPListSaveLoad<ListAreaIDInfo>
{
public:
	int32	GlobalPage;
	int32	Layer;
	int32	AreaID;
	XAlignmentLargeArea::_EnumPriority	Priority;

	ListAreaIDInfo(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	ListAreaIDInfo	&operator=(const ListAreaIDInfo &src);
};

inline	ListAreaIDInfo::ListAreaIDInfo(void)
{
	GlobalPage	=0;
	Layer		=0;
	AreaID		=0;
	Priority	=XAlignmentLargeArea::_PriorityMiddle;
}

inline	bool	ListAreaIDInfo::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,AreaID)==false)
		return false;
	BYTE	d=(BYTE)Priority;
	if(::Save(f,d)==false)
		return false;
	return true;
}
inline	bool	ListAreaIDInfo::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,AreaID)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	Priority	=(XAlignmentLargeArea::_EnumPriority)d;
	return true;
}

inline	ListAreaIDInfo	&ListAreaIDInfo::operator=(const ListAreaIDInfo &src)
{
	GlobalPage	=src.GlobalPage;
	Layer		=src.Layer;
	AreaID		=src.AreaID;
	Priority	=src.Priority;
	return *this;
}

class ListAreaIDInfoContainer : public NPListPackSaveLoad<ListAreaIDInfo>
{
public:
	ListAreaIDInfoContainer(void){}

	virtual	ListAreaIDInfo	*Create(void)	override	{	return new ListAreaIDInfo();	}
};

//--------------------------------------------------------------------------------------------------------
class	ReqAlignmentLargeAreaList : public NPList<ReqAlignmentLargeAreaList>
{
public:
	int		AreaID;
	int		GlobalPage;
	int		Layer;

	ReqAlignmentLargeAreaList(void){}

	ReqAlignmentLargeAreaList	&operator=(ReqAlignmentLargeAreaList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ReqAlignmentLargeAreaListPack : public NPListPack<ReqAlignmentLargeAreaList>
{
public:
	ReqAlignmentLargeAreaListPack(void){}

	ReqAlignmentLargeAreaListPack &operator=(ReqAlignmentLargeAreaListPack &src);
	ReqAlignmentLargeAreaListPack &operator+=(ReqAlignmentLargeAreaListPack &src);
	bool	LayerExists(int page ,int layer);
	bool	ExistsAreaID(int areaID);
	bool	Exists(int page ,int layer,int areaID);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//==================================================================================

class	AlignmentLargeDrawAttr : public AlgorithmDrawAttr
{
public:
	enum	DrawModeAttr{
			_AreaMode		=1
			,_InsideMode	=2
			,_ShiftMode		=3
			,_OutsideMode	=4
	};
	enum	__DrawKind{
		_Area
		,_Group
		,_Point
	}DrawKind;
	DrawModeAttr	DrawMode;
	ReqAlignmentLargeAreaListPack	AList;
	IntList			Priority;

	AlignmentLargeDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100)
	{	DrawMode=_AreaMode;	DrawKind=_Point;	Priority.Add(-1);	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

//==================================================================================

class	GetAlignmentLargeConclusion : public GUIDirectMessage
{
public:
	double	m[6];
	//	TargetX=m[0]*MasterX + m[1]*MasterY + m[2]
	//	TargetY=m[3]*MasterX + m[4]*MasterY + m[5]
	GetAlignmentLargeConclusion(LayersBase *base):GUIDirectMessage(base){}
	GetAlignmentLargeConclusion(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAlignmentLargeIsModeItemEditingPacket : public GUIDirectMessage
{
public:
	enum{
		_ItemMode	=0
		,_AreaMode	=1
		,_GroupMode	=2
	}ItemMode;

	CmdAlignmentLargeIsModeItemEditingPacket(LayersBase *base):GUIDirectMessage(base)
			{	ItemMode=_ItemMode;	}
	CmdAlignmentLargeIsModeItemEditingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ItemMode=_ItemMode;	}
};


//他のページのアラインメントポイントを取得
class	SlaveCommReqAlignmentLargePoint : public DirectCommPacketBase
{
public:
	int		AreaID;
	QString	AreaName;
	int		Layer;

	SlaveCommReqAlignmentLargePoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentLargePoint : public DirectCommPacketBase
{
public:

	AlignmentLargeShiftContainer	AlignmentLargePointData;

	SlaveCommAckAlignmentLargePoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentLargePointPacket : public GUIDirectMessage
{
public:
	int				AreaID;
	QString			AreaName;
	AlignmentLargeShiftContainer	AlignmentLargePointData;

	CmdReqAlignmentLargePointPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargePointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SlaveCommReqAlignmentLargeShift : public DirectCommPacketBase
{
public:
	int		Layer;
	IntList	ItemID;

	SlaveCommReqAlignmentLargeShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentLargeShift : public DirectCommPacketBase
{
public:
	AlignmentLargeShiftContainer	ShiftData;

	SlaveCommAckAlignmentLargeShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentLargeShiftPacket : public GUIDirectMessage
{
public:		
	IntList					*ItemIDPoint;
	AlignmentLargeShiftContainer	*ShiftDataPoint;

	CmdReqAlignmentLargeShiftPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeShiftPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectItemsAlignmentLargeByPoint: public GUIDirectMessage
{
public:
	int						LocalX,LocalY;
	ListAreaIDInfoContainer	AreaList;

	CmdSelectItemsAlignmentLargeByPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectItemsAlignmentLargeByPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentLargeAreaListWithMark: public GUIDirectMessage
{
public:
	ListAreaIDInfoContainer	AreaList;

	CmdReqAlignmentLargeAreaListWithMark(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeAreaListWithMark(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentLargeArea: public GUIDirectMessage
{
public:
	int		AreaID;
	int		Priority;
	int		x1,y1,x2,y2;
	QString AreaName;
	CmdReqAlignmentLargeArea(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteAreaExceptGlobal: public GUIDirectMessage
{
public:
	CmdDeleteAreaExceptGlobal(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAreaExceptGlobal(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteItemsExceptGlobal: public GUIDirectMessage
{
public:
	CmdDeleteItemsExceptGlobal(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteItemsExceptGlobal(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentLargeSavePointByPriority : public GUIDirectMessage
{
public:
	IntList	AreaPriority;
	QBuffer	SavedBuff;

	CmdReqAlignmentLargeSavePointByPriority(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeSavePointByPriority(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqAlignmentLargeLoadPointByPriority : public GUIDirectMessage
{
public:
	QByteArray	Buff;
	TransformBase	*Param;
	bool	ClearBeforeCopy;

	CmdReqAlignmentLargeLoadPointByPriority(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeLoadPointByPriority(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqMakeAreaFromMask : public GUIDirectMessage
{
public:
	IntList	AreaPriority;

	CmdReqMakeAreaFromMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReqMakeAreaFromMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdReqMakeAreaFromCAD : public GUIDirectMessage
{
public:
	IntList	AreaPriority;

	CmdReqMakeAreaFromCAD(LayersBase *base):GUIDirectMessage(base){}
	CmdReqMakeAreaFromCAD(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
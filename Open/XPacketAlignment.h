/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XPacketAlignment.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XPACKETALIGNMENT_H)
#define	XPACKETALIGNMENT_H

#include <QIODevice>
#include "NList.h"
#include "XDataInLayer.h"
#include "XDisplayImage.h"
#include "XDirectComm.h"
#include "NListComp.h"
#include "XYCross.h"


class	AlignmentShiftList: public NPListSaveLoad<AlignmentShiftList>
{
public:
	int		GlobalPage;
	int		ItemID;
	bool	CalcDone;
	double	ShiftX,ShiftY;
    double	MasterX,MasterY;

	AlignmentShiftList(void){	CalcDone=false;	ShiftX=0;	ShiftY=0;	MasterX=0;	MasterY=0;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	AlignmentShiftContainer : public NPListPackSaveLoad<AlignmentShiftList>
{
public:
	AlignmentShiftContainer(void)	{}
	virtual	AlignmentShiftList	*Create(void){	return new AlignmentShiftList();	}
};
//--------------------------------------------------------------------------------------------------------
class	ReqAlignmentAreaList : public NPList<ReqAlignmentAreaList>
{
public:
	int		AreaID;
	int		GlobalPage;
	int		Layer;

	ReqAlignmentAreaList(void){}

	ReqAlignmentAreaList	&operator=(ReqAlignmentAreaList &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ReqAlignmentAreaListPack : public NPListPack<ReqAlignmentAreaList>
{
public:
	ReqAlignmentAreaListPack(void){}

	ReqAlignmentAreaListPack &operator=(ReqAlignmentAreaListPack &src);
	ReqAlignmentAreaListPack &operator+=(ReqAlignmentAreaListPack &src);
	bool	LayerExists(int page ,int layer);
	bool	ExistsAreaID(int areaID);
	bool	Exists(int page ,int layer,int areaID);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AlignmentDrawAttr : public AlgorithmDrawAttr
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
	ReqAlignmentAreaListPack	AList;

	AlignmentDrawAttr(void)
		: AlgorithmDrawAttr(Qt::green,100,Qt::yellow,100,Qt::red,100)
	{	DrawMode=_AreaMode;	DrawKind=_Point;	}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	GetAlignmentConclusion : public GUIDirectMessage
{
public:
	double	m[6];
	//	TargetX=m[0]*MasterX + m[1]*MasterY + m[2]
	//	TargetY=m[3]*MasterX + m[4]*MasterY + m[5]
	GetAlignmentConclusion(LayersBase *base):GUIDirectMessage(base){}
	GetAlignmentConclusion(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdIsModeItemEditingPacket : public GUIDirectMessage
{
public:
	enum{
		_ItemMode	=0
		,_AreaMode	=1
		,_GroupMode	=2
	}ItemMode;

	CmdIsModeItemEditingPacket(LayersBase *base):GUIDirectMessage(base)
			{	ItemMode=_ItemMode;	}
	CmdIsModeItemEditingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ItemMode=_ItemMode;	}
};


//他のページのアラインメントポイントを取得
class	SlaveCommReqAlignmentPoint : public DirectCommPacketBase
{
public:
	int		AreaID;
	QString	AreaName;
	int		Layer;

	SlaveCommReqAlignmentPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentPoint : public DirectCommPacketBase
{
public:

	AlignmentShiftContainer	AlignmentPointData;

	SlaveCommAckAlignmentPoint(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentPointPacket : public GUIDirectMessage
{
public:
	int				AreaID;
	QString			AreaName;
	AlignmentShiftContainer	AlignmentPointData;

	CmdReqAlignmentPointPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	SlaveCommReqAlignmentShift : public DirectCommPacketBase
{
public:
	int		Layer;
	IntList	ItemID;

	SlaveCommReqAlignmentShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckAlignmentShift : public DirectCommPacketBase
{
public:
	AlignmentShiftContainer	ShiftData;

	SlaveCommAckAlignmentShift(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	CmdReqAlignmentShiftPacket : public GUIDirectMessage
{
public:		
	IntList					*ItemIDPoint;
	AlignmentShiftContainer	*ShiftDataPoint;

	CmdReqAlignmentShiftPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentShiftPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
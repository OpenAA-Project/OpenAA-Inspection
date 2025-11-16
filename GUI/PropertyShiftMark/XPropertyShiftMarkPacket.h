#pragma once
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyShiftMark\XShiftMarkPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XShiftMark.h"
#include "XShiftMarkAlgoPacket.h"

class AddLinePacket: public GUIDirectMessage
{
public:
	VectorLineBase	*Vector;

	AddLinePacket(LayersBase *base):GUIDirectMessage(base){}
	AddLinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class ReqItemAddMode: public GUIDirectMessage
{
public:
	bool	ModeAddLine;
	bool	ModeAddEdge;
	bool	ModeAddMark;

	ReqItemAddMode(LayersBase *base):GUIDirectMessage(base)			{	ModeAddLine=false;	ModeAddEdge=false;	ModeAddMark=false;	}
	ReqItemAddMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	ModeAddLine=false;	ModeAddEdge=false;	ModeAddMark=false;	}
};

class	ShiftMarkImagePanel;
class	CmdShiftMarkDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	ShiftMarkImagePanel	*ImagePanelPoint;

	CmdShiftMarkDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	ShiftMarkDrawAttr;

class	CmdShiftMarkDrawModePacket : public GUIDirectMessage
{
public:
	ShiftMarkDrawAttr	*DrawAttr;
	CmdShiftMarkDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdSendAddManualShiftMark : public GUICmdPacketBase
{
public:
	QByteArray			BItem;
	VectorLineBase		*Vector;
	int			LocalPage;
	int			SelectedLibID;
	QString		ItemName;

	GUICmdSendAddManualShiftMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAddManualShiftMark(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAddEdgeMark : public GUICmdPacketBase
{
public:
	int			ItemID;
	FlexArea	Area;
	bool		ModeAddEdge;
	bool		ModeAddMark;

	GUICmdSendAddEdgeMark(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//===========================================================================

class	GUICmdReqItemList : public GUICmdPacketBase
{
public:
	GUICmdReqItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemList : public GUICmdPacketBase
{
public:
	ShiftMarkListForPacketPack	ListInfo;

	GUICmdSendItemList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//===========================================================================

class	GUICmdReqItemThreshold : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemThreshold : public GUICmdPacketBase
{
public:
	QString	ItemName;
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//消失判定しきい値（0-100)

	GUICmdAckItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemThreshold : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;
	QString	ItemName;
	int		SearchDotEdge;
	int		SearchDotMarkMin;
	int		SearchDotMarkMax;
	bool	NGByLosingMark;
	int		ThresholdLost;		//消失判定しきい値（0-100)

	GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	MakeList(int localPage ,LayersBase *PBase);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdChangeDirection : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdChangeDirection(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
//===========================================================================

class	GUICmdReqRotationPoint : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdReqRotationPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRotationPoint : public GUICmdPacketBase
{
public:
	FlexAreaColorRotatedImageContainer	EdgeArea;
	FlexAreaColorRotatedImageContainer	MarkArea;

	GUICmdAckRotationPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

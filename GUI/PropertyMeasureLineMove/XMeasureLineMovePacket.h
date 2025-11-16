/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMeasureLineMove\XMeasureLineMovePacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XMEASURELineMovePACKET_H
#define XMEASURELineMovePACKET_H

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "XMeasureLineMove.h"

class	CmdMeasureLineMoveDrawModePacket : public GUIDirectMessage
{
public:
	MeasureLineMoveDrawAttr	*DrawAttr;
	CmdMeasureLineMoveDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
};

class	MeasureLineMoveImagePanel;
class	CmdMeasureLineMoveDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MeasureLineMoveImagePanel	*ImagePanelPoint;

	CmdMeasureLineMoveDrawEnd(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdMeasureLineMoveGetColorMap : public GUIDirectMessage
{
public:
	FlexArea	Area;
	MeasureLineMoveImagePanel	*ImagePanelPoint;

	GUICmdMeasureLineMoveGetColorMap(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdMeasureLineMoveLDown: public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;

	CmdMeasureLineMoveLDown(LayersBase *base):GUIDirectMessage(base){}
};

class AddLinePacket: public GUIDirectMessage
{
public:
	VectorLineBase	*Vector;

	AddLinePacket(LayersBase *base):GUIDirectMessage(base){}
	AddLinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	GUICmdSendAddManualMeasureLineMove : public GUICmdPacketBase
{
public:
	QByteArray			BItem;
	VectorLineBase		*Vector;
	int			LocalPage;
	int			ItemClass;
	int			SelectedLibID;
	QString		ItemName;
	FlexArea	Area;		//For MarkArea

	//These are for Distance between scans
	bool		NoCalc;
	int			GlobalPage1;
	int			ClosedItemID1;
	int			GlobalPage2;
	int			ClosedItemID2;

	GUICmdSendAddManualMeasureLineMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAddManualMeasureLineMove(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAddCSVMeasureLineMove : public GUICmdPacketBase
{
public:
	QByteArray			BItem;
	VectorLineBase		*Vector;

	GUICmdSendAddCSVMeasureLineMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendAddCSVMeasureLineMove(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdReqMeasureLineMoveColorMap : public GUICmdPacketBase
{
public:
	FlexArea	Area;

	CmdReqMeasureLineMoveColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdAckMeasureLineMoveColorMap : public GUICmdPacketBase
{
public:
	ColorLogic	Color;

	CmdAckMeasureLineMoveColorMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqMeasureLineMoveID : public GUICmdPacketBase
{
public:
	int		GlobalX;
	int		GlobalY;

	GUICmdReqMeasureLineMoveID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMeasureLineMoveID : public GUICmdPacketBase
{
public:
	int		ItemID;

	GUICmdAckMeasureLineMoveID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
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
	LineMoveListForPacketPack	ListInfo;

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
	int		ItemID;

	GUICmdReqItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendItemThreshold : public GUICmdPacketBase
{
public:
	QString						ItemName;
	MeasureLineMoveThreshold	*Thre;

	GUICmdSendItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendItemThreshold(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemThreshold : public GUICmdPacketBase
{
public:
	int							ItemID;
	QString						ItemName;
	MeasureLineMoveThreshold	*Thre;

	GUICmdSetItemThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSetItemThreshold(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//===========================================================================

class	GUICmdGenerateMeasure : public GUICmdPacketBase
{
public:
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	BladeLeft ;
	int32	BladeRight;
	int32	LineLib;
	int32	RxLineLib;
	int32	DistanceLib;
	int32	MaskLib;
	int32	BladeHoleMinArea;
	int32	BladeHoleErosionDot;
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;
	bool	OnlyGenerateFilmLen;

	GUICmdGenerateMeasure(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdReqCorrentValues : public GUICmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	bool			Mastered;

	GUICmdReqCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckCorrentValues : public GUICmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;

	GUICmdAckCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}	
};

class	GUICmdSetCorrentValues : public GUICmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	int32	LineLib;
	int32	DistanceLib;

	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	MaskLib;

	GUICmdSetCorrentValues(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetOnlyBladeThreshold : public GUICmdPacketBase
{
public:
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;

	GUICmdSetOnlyBladeThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdSetMeasureEndPoint : public GUICmdPacketBase
{
public:
	int		EndNo;
	int		MeasureNo;
	int		LocalX;
	int		LocalY;

	GUICmdSetMeasureEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


//====================================================================================================

class	GUICmdReqListData: public GUICmdPacketBase
{
public:
	GUICmdReqListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);

private:

};

class	GUICmdAckListData : public GUICmdPacketBase
{
public:
	MeasureDistanceItemInfoContainer	ListData;

	GUICmdAckListData(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetCorrectValue : public GUICmdPacketBase
{
public:
	int		Phase;
	int		Page;
	int		ItemID;
	double	OKLengthLUnit;
	double	OKLengthHUnit;	

	GUICmdSetCorrectValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	

};

class	GUICmdAddDistance : public GUICmdPacketBase
{
public:
	int		LocalX1;
	int		LocalY1;
	int		LocalX2;
	int		LocalY2;
	int		LineLength;
	int		LineLibID1;
	int		LineLibID2;
	int		DistanceLibID;

	GUICmdAddDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	

};

class	GUICmdDeleteMeasureDistance : public GUICmdPacketBase
{
public:
	int		Phase;
	int		MeasureNo;

	GUICmdDeleteMeasureDistance(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	

};

//====================================================================================================

class	GUICmdReqMeasureLineInfo: public GUICmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;

	GUICmdReqMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	GUICmdAckMeasureLineInfo : public GUICmdPacketBase
{
public:
	int		SearchDot;

	GUICmdAckMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	GUICmdSetMeasureLineInfo : public GUICmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	GUICmdSetMeasureLineInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);

private:

};

class	GUICmdSetMeasureLineInfoAll : public GUICmdPacketBase
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	GUICmdSetMeasureLineInfoAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int cmd ,QString &EmitterRoot,QString &EmitterName);

private:

};

//====================================================================================================

class	GUICmdReqMeasureLineMovePosition : public GUICmdPacketBase
{
public:
	int		Phase;
	int		ItemID;

	GUICmdReqMeasureLineMovePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckMeasureLineMovePosition : public GUICmdPacketBase
{
public:
	int		Point1X,Point1Y;
	int		Point2X,Point2Y;

	GUICmdAckMeasureLineMovePosition(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//====================================================================================================

class	GUICmdReqChangeMeasureLineMoveEndPoint : public GUICmdPacketBase
{
public:
	bool	Point1;
	bool	Point2;
	int		ItemID;
	int		LocalX,LocalY;

	GUICmdReqChangeMeasureLineMoveEndPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif
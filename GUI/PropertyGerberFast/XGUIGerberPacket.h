/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyGerber\XGerberPacket.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XGUIGERBERPACKET_H)
#define	XGUIGERBERPACKET_H


#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGerberFast.h"
#include "XBoolList.h"
#include "XIntClass.h"
#include "XGerberFastPacket.h"

class	GUICmdReqApertureList: public GUICmdPacketBase
{
public:
	int	Layer;

	GUICmdReqApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdSendApertureList : public GUICmdPacketBase
{
public:
	struct	ApertureInfo	*ApertureDim;
	int						Count;
	int						Layer;

	GUICmdSendApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendApertureList(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqSetApertureList : public GUICmdPacketBase
{
public:
	//AXGR_APERTURELISTPM **apertureList;
	struct	ApertureInfo	*ApertureDim;
	int						Count;
	int						Layer;

	GUICmdReqSetApertureList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	void	Set(struct	ApertureInfo *ApertureList ,int ACount);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

/*
class	GUICmdSendGerberBuffer : public GUICmdPacketBase
{
public:
	LoadGerberFromLayerList	LoadedData;
	QByteArray				Buff[MaxGerberLayer];

	GUICmdSendGerberBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	SetupLoading(void);
	bool	CreateTmpFiles(QStringList &FileNames);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
*/
class	CmdGerberDrawModePacket : public GUIDirectMessage
{
public:
	enum{
		_Default	=0
		,_Move		=1
		,_Zoom		=2
		,_Rotate	=3
		,_3Point	=4
		,_AddP		=5
		,_Paint		=6
		,_Draw		=7
		,_SlopeX	=8
		,_SlopeY	=9
	}Mode;

	CmdGerberDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberTabModePacket : public GUIDirectMessage
{
public:
	enum{
		_Loading			=0
		,_Operation			=1
		,_Imaging			=2
		,_AutoMatching		=3
		,_GenerateBlocks	=4
	}Mode;

	CmdGerberTabModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberTabModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberRemoveAutoMatchingPoint : public GUIDirectMessage
{
public:
	int		GlobalX,GlobalY;

	CmdGerberRemoveAutoMatchingPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberRemoveAutoMatchingPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

/*
class	GUICmdMsgGerberCopy: public GUICmdPacketBase
{
public:
	GUICmdMsgGerberCopy(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	GUICmdMsgGerberCut: public GUICmdPacketBase
{
public:
	GUICmdMsgGerberCut(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
*/
class	GUICmdGerberExec3PointAlignment: public GUICmdPacketBase
{
public:
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];	

	GUICmdGerberExec3PointAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	GUICmdGerberExecAddAlignmentPoint: public GUICmdPacketBase
{
public:
	DoublePoint	ImagePoint[MaxGerberPointNumb];
	DoublePoint	CadPoint[MaxGerberPointNumb];	

	GUICmdGerberExecAddAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqGerberCenterize: public GUICmdPacketBase
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;
	int			Layer;

	GUICmdReqGerberCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendGerberCenterize: public GUICmdPacketBase
{
public:
	double		x;
	double		y;
	bool		Ret;

	GUICmdSendGerberCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

/*
typedef struct {
	int no;													//!< レイヤ番号
	int kind;												//!< データ種別
	double x;												//!< X座標
	double y;												//!< Y座標
} GUI_AXGR_PICKDATA;

class	GUICmdReqGerberGetPickInfo: public GUICmdPacketBase
{
public:
	double	GlobalX,GlobalY;

	GUICmdReqGerberGetPickInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendGerberGetPickInfo: public GUICmdPacketBase
{
public:
	GUI_AXGR_PICKDATA	*PData;
	int				PDataNumb;

	GUICmdSendGerberGetPickInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	~GUICmdSendGerberGetPickInfo(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
*/
class	GUICmdSendImagePointXY: public GUICmdPacketBase
{
public:
	int		Turn;
	double	GPx,GPy;
	GUICmdSendImagePointXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendAMImagePointXY: public GUICmdPacketBase
{
public:
	int		Turn;
	double	GPx,GPy;
	GUICmdSendAMImagePointXY(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendLayerTypeList: public GUICmdPacketBase
{
public:
	QStringList	LayerTypeList;

	GUICmdSendLayerTypeList(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendAddLayer: public GUICmdPacketBase
{
public:
	QString	LayerName;

	GUICmdSendAddLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdGerberSendShowingLayerInfo: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;
	IntList		LayerTypes;
	BoolList	ButtonsToShowComposite;
	IntList		OperateCompositeIDList;
	IntList		CompositeIDList;
	QColor		LayerColor[MaxGerberLayer];
	QColor		CompositeLayerColor[MaxGerberLayer];
	GerberCompositeLayerContainer	CompositeLayer;

	GUICmdGerberSendShowingLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

//=====================================================================================================


enum	OperationMode
{
	OM_None					=0
	,OM_Move				=1
	,OM_Extend				=2
	,OM_Rotate				=3
	,OM_SlopeX				=4
	,OM_SlopeY				=5
	,OM_3PointAlignment		=6
	,OM_AddAlignmentPoint	=7
	,OM_Paint				=8
	,OM_Draw				=9
	,OM_MatchingPoint1		=10
	,OM_MatchingPoint2		=11
	,OM_MatchingPoint3		=12

	,OM_CreateLine			=61
	,OM_CreateArc			=62
	,OM_CreatePolygon		=63
};

class	CmdGerberGetOperationModePacket : public GUIDirectMessage
{
public:
	OperationMode	Mode;

	CmdGerberGetOperationModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberGetOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberGetShowingState : public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	CmdGerberGetShowingState(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberGetShowingState(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberChangeOperationModePacket : public GUIDirectMessage
{
public:
	OperationMode	Mode;
	CmdGerberChangeOperationModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberChangeOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GerberFastImagePanel;
class	CmdGerberLMouseDownIn3PAPacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	FlexArea	Area;
	GerberFastImagePanel	*Source;

	CmdGerberLMouseDownIn3PAPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberLMouseDownIn3PAPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGerberLMouseDownAddAlignPacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	GerberFastImagePanel	*Source;

	CmdGerberLMouseDownAddAlignPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberLMouseDownAddAlignPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberLMouseDownIn3PAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;
	GerberFastImagePanel	*Source;
	IntList				LayerList;

	CmdGerberLMouseDownIn3PAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberLMouseDownIn3PAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddMatchingAlignmentPoint: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList				LayerList;

	CmdAddMatchingAlignmentPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdAddMatchingAlignmentPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberSet3PointAlignmentModePacket : public GUIDirectMessage
{
public:
	CmdGerberSet3PointAlignmentModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberSet3PointAlignmentModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGerberSetAutoMatchingModePacket : public GUIDirectMessage
{
public:
	CmdGerberSetAutoMatchingModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberSetAutoMatchingModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberCancelRotMoveZoom : public GUIDirectMessage
{
public:
	CmdGerberCancelRotMoveZoom(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberCancelRotMoveZoom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberDrawWithPoints : public GUIDirectMessage
{
public:
	DotListContainer	Dots;

	CmdGerberDrawWithPoints(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberDrawWithPoints(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberAddLayer : public GUIDirectMessage
{
public:
	QString	LayerName;
	int LayerNo;

	CmdGerberAddLayer(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberAddLayer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddGerberLine : public GUIDirectMessage
{
public:
	double	X1,Y1,X2,Y2;

	CmdAddGerberLine(LayersBase *base):GUIDirectMessage(base){}
	CmdAddGerberLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdGerberReqPointFromArea : public GUICmdPacketBase
{
public:
	int			GlobalPage;
	int			Layer;
	FlexArea	Area;

	GUICmdGerberReqPointFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdGerberSendPointFromArea: public GUICmdPacketBase
{
public:
	double		LocalX,LocalY;
	double		DifBrightness;

	GUICmdGerberSendPointFromArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};



/*
class	GUICmdGerberTransform: public GUICmdPacketBase
{
public:
	TransformGerber	TransParam;

	GUICmdGerberTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};
*/

class	GUICmdMakeImage: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	//BoolList	ButtonsToOperateComposite;
	IntList		OperateCompositeIDList;
	QColor		LayerColor[MaxGerberLayer];
	QColor		CompositeLayerColor[MaxGerberLayer];
	enum	MakeImageMode{
		_MIM_ToMaster
		,_MIM_Standard
		,_MIM_Enlarge	=1
		,_MIM_Shrinked	=2
		,_MIM_Shiftable	=3
		,_MIM_Unstable	=4
		,_MIM_Stable	=5
		,_MIM_Clear		=6
	}MIMode;

	GUICmdMakeImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdMakeBitImage: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	//BoolList	ButtonsToOperateComposite;
	IntList		OperateCompositeIDList;
	QColor		LayerColor[MaxGerberLayer];
	QColor		CompositeLayerColor[MaxGerberLayer];

	GUICmdMakeBitImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdMakeAlgo: public GUICmdPacketBase
{
public:
	AlgoGenerationalContainer		MakeAlgoAllList;
	int								ExecutedLine;

	GUICmdMakeAlgo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdReqSaveConstruct: public GUICmdPacketBase
{
public:
	GUICmdReqSaveConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdAckSaveConstruct: public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdAckSaveConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName ){}
};

class	GUICmdReqLoadConstruct: public GUICmdPacketBase
{
public:
	QByteArray	Data;
	bool		ChangeImportant;

	GUICmdReqLoadConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


class	GUICmdReqGerberInfo : public GUICmdPacketBase
{
public:
	int GlobalX ,GlobalY;
	BoolList	DrawingLayers;

	GUICmdReqGerberInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckGerberInfo : public GUICmdPacketBase
{
public:
	GerberInfoContainer	GInfo;

	GUICmdAckGerberInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};



#endif

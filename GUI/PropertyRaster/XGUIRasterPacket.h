#pragma once

#include <QByteArray>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XRaster.h"
#include "XBoolList.h"
#include "XIntClass.h"
#include "XDisplayImage.h"
#include <QStringList>
#include "XRasterPacket.h"
#include "NListComp.h"
#include "XGeneralFunc.h"

class PageElementIDClass : public NPListSaveLoad<PageElementIDClass>
{
public:
	int	Page;
	int	ElementID;

	PageElementIDClass(void){}
	PageElementIDClass(int page ,int elementID):Page(page),ElementID(elementID){}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class PageElementIDClassContainer : public NPListPackSaveLoad<PageElementIDClass>
{
public:
	PageElementIDClassContainer(void){}

	virtual	PageElementIDClass	*Create(void){	return new PageElementIDClass();	}
};

inline	bool	PageElementIDClass::Save(QIODevice *f)
{
	if(::Save(f,Page)==false)
		return false;
	if(::Save(f,ElementID)==false)
		return false;
	return true;
}
inline	bool	PageElementIDClass::Load(QIODevice *f)
{
	if(::Load(f,Page)==false)
		return false;
	if(::Load(f,ElementID)==false)
		return false;
	return true;
}

//====================================================================================================

class	CmdRasterDrawModePacket : public GUIDirectMessage
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

	CmdRasterDrawModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDrawModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterTabModePacket : public GUIDirectMessage
{
public:
	enum{
		_Loading			=0
		,_Operation			=1
		,_Imaging			=2
		,_GenerateBlocks	=4
	}Mode;

	CmdRasterTabModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterTabModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterRemoveAutoMatchingPoint : public GUIDirectMessage
{
public:
	int		GlobalX,GlobalY;

	CmdRasterRemoveAutoMatchingPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterRemoveAutoMatchingPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdRasterExec3PointAlignment: public GUICmdPacketBase
{
public:
	int	FileLayerID;
	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];	

	GUICmdRasterExec3PointAlignment(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterExecAddAlignmentPoint: public GUICmdPacketBase
{
public:
	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];	

	GUICmdRasterExecAddAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqRasterCenterize: public GUICmdPacketBase
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;

	GUICmdReqRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSendRasterCenterize: public GUICmdPacketBase
{
public:
	double		x;
	double		y;
	bool		Ret;

	GUICmdSendRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

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

class	GUICmdRasterSendShowingLayerInfo: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	QColor		LayerColor[MaxRasterLayer];

	GUICmdRasterSendShowingLayerInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

//=====================================================================================================


enum	RasterOperationMode
{
	 OMRaster_None					=0
	,OMRaster_Move					=1
	,OMRaster_Extend				=2
	,OMRaster_Rotate				=3
	,OMRaster_SlopeX				=4
	,OMRaster_SlopeY				=5
	,OMRaster_3PointAlignment		=6
	,OMRaster_AddAlignmentPoint		=7
	,OMRaster_Paint					=8
	,OMRaster_Draw					=9
	,OMRaster_PickColor				=13
	,OMRaster_MatchingPoint1		=10
	,OMRaster_MatchingPoint2		=11
	,OMRaster_MatchingPoint3		=12
	,OMRaster_MoveElement			=14
	,OMRaster_Partial				=15
	,OMRaster_Mask					=16

	,OMRaster_PickupByColor			=61
	,OMRaster_PickupByEdge			=62
	,OMRaster_PickupByColorReference=63
	,OMRaster_PickupByEdgeReference	=64
	,OMRaster_PickupProfileColor	=65
};

class	CmdRasterGetOperationModePacket : public GUIDirectMessage
{
public:
	RasterOperationMode	Mode;

	CmdRasterGetOperationModePacket(LayersBase *base):GUIDirectMessage(base)		{	Mode=OMRaster_None;	}
	CmdRasterGetOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Mode=OMRaster_None;	}
};

class	CmdRasterGetShowingState : public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	CmdRasterGetShowingState(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterGetShowingState(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterChangeOperationModePacket : public GUIDirectMessage
{
public:
	RasterOperationMode	Mode;
	CmdRasterChangeOperationModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterChangeOperationModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RasterImagePanel;
class	CmdRasterLMouseDownIn3PAPacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownIn3PAPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownIn3PAPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownAddAlignPacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownAddAlignPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownAddAlignPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownPickColor : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownPickColor(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownPickColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterDrawEndPickupByColorPacket : public GUIDirectMessage
{
public:
	CmdRasterDrawEndPickupByColorPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDrawEndPickupByColorPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownPickupByColorPacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownPickupByColorPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownPickupByColorPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownPickupByColorAreaPacket : public GUIDirectMessage
{
public:
	FlexArea		ColorArea;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownPickupByColorAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownPickupByColorAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownAddPickupByEdgePacket : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownAddPickupByEdgePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownAddPickupByEdgePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownPickupByEdge : public GUIDirectMessage
{
public:
	int	GlobalX,GlobalY;
	RasterImagePanel	*Source;

	CmdRasterLMouseDownPickupByEdge(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownPickupByEdge(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRasterLMouseDownIn3PAreaPacket : public GUIDirectMessage
{
public:
	FlexArea	Area;
	XYClassCluster XYArea;
	RasterImagePanel	*Source;
	IntList				LayerList;

	CmdRasterLMouseDownIn3PAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterLMouseDownIn3PAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddMatchingAlignmentPoint: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList				LayerList;

	CmdAddMatchingAlignmentPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdAddMatchingAlignmentPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterSet3PointAlignmentModePacket : public GUIDirectMessage
{
public:
	CmdRasterSet3PointAlignmentModePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterSet3PointAlignmentModePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterCancelRotMoveZoom : public GUIDirectMessage
{
public:
	CmdRasterCancelRotMoveZoom(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterCancelRotMoveZoom(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterAddLayer : public GUIDirectMessage
{
public:
	QString	LayerName;
	int LayerNo;

	CmdRasterAddLayer(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterAddLayer(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRasterLine : public GUIDirectMessage
{
public:
	double	X1,Y1,X2,Y2;

	CmdAddRasterLine(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRasterLine(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdRasterSetAlignmentPoint : public GUICmdPacketBase
{
public:
	int			LocalX,LocalY;
	int			FileLayerID;
	int			LineNo;
	bool		IsImage;

	GUICmdRasterSetAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	CmdRasterRefreshLines : public GUIDirectMessage
{
public:
	CmdRasterRefreshLines(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterRefreshLines(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

/*
class	GUICmdRasterTransform: public GUICmdPacketBase
{
public:
	TransformRaster	TransParam;

	GUICmdRasterTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};
*/

class	GUICmdMakeImage: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	QColor		LayerColor[MaxRasterLayer];
	enum	MakeImageMode{
		_MIM_ToMaster
		,_MIM_ToDispatchMaster
		,_MIM_Standard
		,_MIM_Enlarge	=1
		,_MIM_Shrinked	=2
		,_MIM_Shiftable	=3
		,_MIM_Clear		=6
	}MIMode;

	GUICmdMakeImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdMakeImageInMask: public GUICmdPacketBase
{
public:
	PureFlexAreaListContainer	ChangeableAreas;

	GUICmdMakeImageInMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdMakeBitImage: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	QColor		LayerColor[MaxRasterLayer];

	GUICmdMakeBitImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdAlgoPipeOut: public GUICmdPacketBase
{
public:

	GUICmdAlgoPipeOut(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};

class	GUICmdReqSaveConstruct: public GUICmdPacketBase
{
public:
	int	Phase;
	GUICmdReqSaveConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

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
	int	Phase;
	QByteArray	Data;
	bool		ChangeImportant;

	GUICmdReqLoadConstruct(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


class	GUICmdReqRasterInfo : public GUICmdPacketBase
{
public:
	int GlobalX ,GlobalY;
	BoolList	DrawingLayers;

	GUICmdReqRasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckRasterInfo : public GUICmdPacketBase
{
public:
	RasterInfoContainer	GInfo;

	GUICmdAckRasterInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdLoadRaster : public GUICmdPacketBase
{
public:
	int			FileLayerID;
	QString		FileName;
	QByteArray	Data;

	GUICmdLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdDeliverRasterToOtherPhases : public GUICmdPacketBase
{
public:

	GUICmdDeliverRasterToOtherPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLoadRaster : public GUICmdPacketBase
{
public:
	bool	Ret;

	GUICmdAckLoadRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================
class	GUICmdReqRasterArea : public GUICmdPacketBase
{
public:

	GUICmdReqRasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRasterArea : public GUICmdPacketBase
{
public:
	double	MinX,MinY,MaxX,MaxY;

	GUICmdAckRasterArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================

class	CmdRasterGetDrawAttr : public GUIDirectMessage
{
public:
	IntListFast		ShownFileID;
	IntListFast		OperationalFileID;
	IntListFast		MaskIDList;
	QColor			LayerColor[MaxRasterLayer];
	bool			ShowPDF;
	bool			SimpleMode;
	bool			DrawAutoMatchingArea;
	bool			DrawAutoMatchingImage;
	int				FileLayerIDTable[MaxRasterLayer];
	int				CurrentElementGlobalPage;
	int				CurrentElementID;
	bool			MoveMode;
	bool			MoveElementMode;
	bool			RotateMode;
	bool			ExtendMode;
	bool			SlopeXMode;
	bool			SlopeYMode;
	bool			AlignmentMode;
	bool			DrawPickUpArea;
	bool			ShowReferenceItems;
	int				ReferenceID;

	CmdRasterGetDrawAttr(LayersBase *base);
	CmdRasterGetDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

inline	CmdRasterGetDrawAttr::CmdRasterGetDrawAttr(LayersBase *base)
	:GUIDirectMessage(base)
{
	ShowPDF					=true;
	SimpleMode				=false;
	DrawAutoMatchingArea	=false;
	DrawAutoMatchingImage	=false;
	CurrentElementGlobalPage=-1;
	CurrentElementID		=-1;
	MoveMode				=false;
	MoveElementMode			=false;
	RotateMode				=false;
	ExtendMode				=false;
	SlopeXMode				=false;
	SlopeYMode				=false;
	AlignmentMode			=false;
	DrawPickUpArea			=false;
	ShowReferenceItems		=false;
	ReferenceID				=-1;
}

class	GUICmdClearRaster : public GUICmdPacketBase
{
public:
	bool	ModeToClearAllPhases;

	GUICmdClearRaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdTransferInfo : public GUICmdPacketBase
{
public:
	QByteArray	Array;

	GUICmdTransferInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================

class	GUICmdRasterMove : public GUICmdPacketBase
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;
	bool	OnlyOnePhase;

	GUICmdRasterMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterRotate : public GUICmdPacketBase
{
public:
	double	Angle;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRasterRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterZoom : public GUICmdPacketBase
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRasterZoom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterShear : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRasterShear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterMirror : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRasterMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterCenterize: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	double	ZoomRate;
	bool	OnlyOnePhase;

	GUICmdRasterCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterCenterizeOnly: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRasterCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//========================================================================================

class	CmdRasterDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdRasterDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterBackPage : public GUIDirectMessage
{
public:
	int		BackPage;

	CmdRasterBackPage(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterBackPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterReflectData : public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;

	CmdRasterReflectData(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterReflectData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==============================================================================================

class	GUICmdSetDrawAttr : public GUICmdPacketBase
{
public:
	IntListFast		ShownFileID;
	IntListFast		OperationalFileID;
	QColor			LayerColor[MaxRasterLayer];
	int				FileLayerIDTable[MaxRasterLayer];

	GUICmdSetDrawAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================================

class	GUICmdDrawAllSelected: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;

	GUICmdDrawAllSelected(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//==============================================================
class	GUICmdSelectLine: public GUICmdPacketBase
{
public:
	int		FileLayerID;

	GUICmdSelectLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};//==============================================================
class	GUICmdRemoveLine: public GUICmdPacketBase
{
public:
	int		LineNo;

	GUICmdRemoveLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//==============================================================
class	GUICmdSwapNext: public GUICmdPacketBase
{
public:
	int		LineNo;

	GUICmdSwapNext(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//==============================================================
class	GUICmdDuplicateLine: public GUICmdPacketBase
{
public:
	int		LineNo;

	GUICmdDuplicateLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckDuplicateLine: public GUICmdPacketBase
{
public:
	int		FileLayerID;

	GUICmdAckDuplicateLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================

class	GUICmdChangeCurrentPhase : public GUICmdPacketBase
{
public:
	int	NewPhase;

	GUICmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================

class	CmdRasterSelectLayerNo : public GUIDirectMessage
{
public:
	int32	GenRasterLayerNo;
	int32	GenRasterLib;

	CmdRasterSelectLayerNo(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterSelectLayerNo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSetGenerateAlgo : public GUIDirectMessage
{
public:
	int32	GenLibType;
	int32	GenLibID;
	int32	GenRasterLayerNo;
	int32	RasterAlgoType;
	int32	GenRasterLib;

	GUICmdSetGenerateAlgo(LayersBase *base):GUIDirectMessage(base){}
	GUICmdSetGenerateAlgo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	GUICmdGenerateAlgo : public GUIDirectMessage
{
public:
	GUICmdGenerateAlgo(LayersBase *base):GUIDirectMessage(base){}
	GUICmdGenerateAlgo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	GUICmdRasterDrawMode : public GUICmdPacketBase
{
public:
	bool	MoveMode;
	bool	MoveElementMode;
	bool	RotateMode;
	bool	SlopeXMode;
	bool	SlopeYMode;
	bool	ExtendMode;
	DisplayImage::__DrawingMode	Mode;
	int		LastPosX,LastPosY;
	int		MoveStartPosX,MoveStartPosY;
	int		LastElementPosX,LastElementPosY;
	int		MoveStartElementPosX,MoveStartElementPosY;
	int		RotateCenterXOnData	,RotateCenterYOnData;
	int		RotateFirstX		,RotateFirstY;
	double	RotateAngle;
	int		ExtendCenterXOnData	,ExtendCenterYOnData;
	int		ExtendFirstX		,ExtendFirstY;
	int		SlopeXCenterXOnData	,SlopeXCenterYOnData;
	int		SlopeXFirstX		,SlopeXFirstY;
	double	SlopeXAngle;
	int		SlopeYCenterXOnData	,SlopeYCenterYOnData;
	int		SlopeYFirstX		,SlopeYFirstY;
	double	SlopeYAngle;
	bool	AlignmentMode;
	bool	DrawPickUpArea;
	DoublePoint	ImagePoint[MaxRasterPointNumb];
	DoublePoint	CadPoint[MaxRasterPointNumb];

	GUICmdRasterDrawMode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgRasterSelectAll: public GUICmdPacketBase
{
public:
	GUICmdMsgRasterSelectAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterDraw: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToOperateLayer;

	int		GlobalX;
	int		GlobalY;

	GUICmdRasterDraw(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgRasterExtendWithCenter : public GUICmdPacketBase
{
public:
	double	RateX,RateY;
	double	Cx,Cy;

	GUICmdMsgRasterExtendWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgRasterRotateWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgRasterRotateWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgRasterSlopeXWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgRasterSlopeXWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMsgRasterSlopeYWithCenter : public GUICmdPacketBase
{
public:
	double	Radian;
	double	Cx,Cy;

	GUICmdMsgRasterSlopeYWithCenter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdMsgRasterPaste : public GUICmdPacketBase
{
public:
	int index;	//íçà” PasteRasterFormÇ≈ÇÃcurrentRow();
	int	x,y;

	GUICmdMsgRasterPaste(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRasterDrawArea: public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	QColor		Color;
	int			FileLayerID;

	GUICmdRasterDrawArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMakeRasterReferenceItem: public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;

	GUICmdMakeRasterReferenceItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSelectItemsRaster: public GUICmdPacketBase
{
public:
	FlexArea	Area;
	bool		MultiSelect;
	BoolList	ButtonsToOperateLayer;

	GUICmdSelectItemsRaster(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================================================
class	GUICmdRasterPickupByColor: public GUICmdPacketBase
{
public:
	int			FileLayerID;
	int			LocalX,LocalY;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	GUICmdRasterPickupByColor(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdRasterPickupByColorArea: public GUICmdPacketBase
{
public:
	int			FileLayerID;
	FlexArea	LocalColorArea;
	int			ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;

	GUICmdRasterPickupByColorArea(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================================================

class	GUICmdReqRasterElements: public GUICmdPacketBase
{
public:
	int			FileLayerID;

	GUICmdReqRasterElements(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRasterElements: public GUICmdPacketBase
{
public:
	RasterElementListContainer	Elements;

	GUICmdAckRasterElements(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUICmdReqRasterElementData: public GUICmdPacketBase
{
public:
	int	ItemID;
	int	ElementID;

	GUICmdReqRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRasterElementData: public GUICmdPacketBase
{
public:
	int		ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;
	bool	Found;

	GUICmdAckRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdSetRasterElementData: public GUICmdPacketBase
{
public:
	int	ItemID;
	int	ElementID;
	int		ShrinkDot;
	int			InsideEdgeWidth;
	int			OutsideEdgeWidth;
	AlgorithmLibraryListContainer	AllocatedStaticLib;
	AlgorithmLibraryListContainer	AllocatedInsideEdgeLib;
	AlgorithmLibraryListContainer	AllocatedOutsideEdgeLib;
	bool	DeleteMode;

	GUICmdSetRasterElementData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


//==============================================================================================

class	GUICmdReqRefreshLines: public GUICmdPacketBase
{
public:
	GUICmdReqRefreshLines(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRefreshLines: public GUICmdPacketBase
{
public:
	RasterFileLayerListContainer	FileLayerListContainer;

	GUICmdAckRefreshLines(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================================================

class	GUIRasterCmdDelMaskByCAD: public GUICmdPacketBase
{
public:

	GUIRasterCmdDelMaskByCAD(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

//==============================================================================================

class	CmdAddRegArea : public GUIDirectMessage
{
public:
	FlexArea	AddedArea;

	CmdAddRegArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRegArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddRegColorArea : public GUIDirectMessage
{
public:
	FlexArea	PickupArea;
	int			LibID;

	CmdAddRegColorArea(LayersBase *base):GUIDirectMessage(base){}
	CmdAddRegColorArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==============================================================================================

class	GUICmdReqPickRasterColor: public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;
	int	FileLayerID;

	GUICmdReqPickRasterColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckPickRasterColor: public GUICmdPacketBase
{
public:
	QColor	Color;

	GUICmdAckPickRasterColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetPickupArea: public GUICmdPacketBase
{
public:
	FlexArea	LocalPickupArea;

	GUICmdSetPickupArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================================================

class	CmdReqElementInfo : public GUIDirectMessage
{
public:
	RasterElementListContainer		Elements;
	PageElementIDClassContainer		ElementIDList;

	CmdReqElementInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdReqElementInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetCurrentElementID : public GUIDirectMessage
{
public:
	int	CurrentElementID;

	CmdSetCurrentElementID(LayersBase *base):GUIDirectMessage(base){}
	CmdSetCurrentElementID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGeneraeRasterAlgorithm : public GUIDirectMessage
{
public:
	CmdGeneraeRasterAlgorithm(LayersBase *base):GUIDirectMessage(base){}
	CmdGeneraeRasterAlgorithm(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteRegColor : public GUIDirectMessage
{
public:
	int	Page		;
	int	ElementID	;

	CmdDeleteRegColor(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteRegColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdRasterCancelMove : public GUIDirectMessage
{
public:

	CmdRasterCancelMove(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterCancelMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//=============================================================
class	GUICmdMoveElement: public GUICmdPacketBase
{
public:
	int	MovX,MovY;
	int	ElementID;

	GUICmdMoveElement(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


//==============================================================================================

class	GUICmdReqPickRasterColorProfile: public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqPickRasterColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqRasterColorProfiles: public GUICmdPacketBase
{
public:
	GUICmdReqRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckRasterColorProfiles: public GUICmdPacketBase
{
public:
	ColorProfileContainerWithTable		ColorProfiles;

	GUICmdAckRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetRasterColorProfiles: public GUICmdPacketBase
{
public:
	ColorProfileContainerWithTable		ColorProfiles;

	GUICmdSetRasterColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdConvertColorProfiles: public GUICmdPacketBase
{
public:
	GUICmdConvertColorProfiles(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqRasterProfileValue: public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdReqRasterProfileValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckRasterProfileValue: public GUICmdPacketBase
{
public:
	QColor	ConvertedImageColor;
	QColor	PDFColor;

	GUICmdAckRasterProfileValue(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//====================================================================================================================

class	CmdRasterSetPartial : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdRasterSetPartial(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterSetPartial(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSetPartialArea: public GUICmdPacketBase
{
public:
	FlexArea	LocalArea;
	GUICmdSetPartialArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//====================================================================================================================

class	CmdRasterMaskAreaPacket: public GUIDirectMessage
{
public:
	FlexArea	MaskArea;
	int			FileLayerID;
	CmdRasterMaskAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdRasterMaskAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdAddMaskArea: public GUICmdPacketBase
{
public:
	FlexArea	MaskArea;
	int			FileLayerID;
	GUICmdAddMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdDelMaskArea: public GUICmdPacketBase
{
public:
	int			FileLayerID;
	int			MaskID;
	GUICmdDelMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqEnumMaskArea: public GUICmdPacketBase
{
public:
	int			FileLayerID;

	GUICmdReqEnumMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckEnumMaskArea: public GUICmdPacketBase
{
public:
	int		FileLayerID;
	IntList	MaskIDList;

	GUICmdAckEnumMaskArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================

class	GUICmdSetPDFWithSelfTransform: public GUICmdPacketBase
{
public:
	QByteArray	PDFData;

	GUICmdSetPDFWithSelfTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================
class	GUICmdReqRasterTransformInfo: public GUICmdPacketBase
{
public:
	GUICmdReqRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckRasterTransformInfo: public GUICmdPacketBase
{
public:
	QByteArray	TransformData;

	GUICmdAckRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetRasterTransformInfo: public GUICmdPacketBase
{
public:
	QByteArray	TransformData;

	GUICmdSetRasterTransformInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================

class	GUICmdReqMakeProfileByImage: public GUICmdPacketBase
{
public:
	bool	Mastered;
	GUICmdReqMakeProfileByImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


//==============================================================
class	GUICmdReqRasterReference: public GUICmdPacketBase
{
public:
	GUICmdReqRasterReference(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckRasterReference: public GUICmdPacketBase
{
public:
	ColorProfileContainer	ColorProfiler;

	GUICmdAckRasterReference(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdMakeAutoRasterReference: public GUICmdPacketBase
{
public:
	int ColorMergin;
	int MinItemArea;
	int	ShrinkSize;

	GUICmdMakeAutoRasterReference(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSetColorProfile: public GUICmdPacketBase
{
public:
	QByteArray	ColorProfileData;

	GUICmdSetColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSaveDefaultColorProfile: public GUICmdPacketBase
{
public:
	ColorProfileContainer   ColorProfiler;

	GUICmdSaveDefaultColorProfile(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


//=============================================================
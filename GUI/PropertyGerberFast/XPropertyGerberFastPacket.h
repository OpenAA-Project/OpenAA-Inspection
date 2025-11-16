#if	!defined(XPropertyGerberFastPacket_h)
#define	XPropertyGerberFastPacket_h

#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGerberAperture.h"
#include "XGerberFast.h"
#include "XFlexAreaImageBuffer.h"
#include "NListComp.h"
#include "XBoolList.h"
#include "XDisplayImage.h"
#include "XGerberFastPacket.h"
#include "XPropertyGerberFastCommon.h"

class	GUICmdLoadGerber : public GUICmdPacketBase
{
public:
	int			FileLayerID;
	QString		FileName;
	QByteArray	Data;

	GUICmdLoadGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdDeliverGerberToOtherPhases : public GUICmdPacketBase
{
public:

	GUICmdDeliverGerberToOtherPhases(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f){		return true;	}
	virtual	bool	Save(QIODevice *f){		return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckLoadGerber : public GUICmdPacketBase
{
public:
	bool	Ret;

	GUICmdAckLoadGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================
class	GUICmdReqGerberArea : public GUICmdPacketBase
{
public:

	GUICmdReqGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckGerberArea : public GUICmdPacketBase
{
public:
	double	MinX,MinY,MaxX,MaxY;

	GUICmdAckGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//==============================================================

class	CmdGetDrawAttr : public GUIDirectMessage
{
public:
	IntListFast		ShownFileID;
	IntListFast		OperationalFileID;
	bool			SimpleMode;
	IntListFast		ShownCompositeID;
	IntListFast		OperationalCompositeID;
	bool			DrawAutoMatchingArea;
	bool			DrawAutoMatchingImage;
	QColor			LayerColor[MaxGerberLayer];
	int				FileLayerIDTable[MaxGerberLayer];
	QColor			CompColor[MaxGerberLayer];

	CmdGetDrawAttr(LayersBase *base):GUIDirectMessage(base){}
	CmdGetDrawAttr(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdRegulateGerberArea : public GUICmdPacketBase
{
public:
	double	MinX,MinY,MaxX,MaxY;

	GUICmdRegulateGerberArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdClearGerber : public GUICmdPacketBase
{
public:
	bool	ModeToClearAllPhases;

	GUICmdClearGerber(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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

class	GUICmdMove : public GUICmdPacketBase
{
public:
	double	XDir;
	double	YDir;
	bool	PixelMode;
	bool	OnlyOnePhase;

	GUICmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdRotate : public GUICmdPacketBase
{
public:
	double	Angle;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdRotate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdZoom : public GUICmdPacketBase
{
public:
	double	XZoomDir;
	double	YZoomDir;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdZoom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdShear : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	Shear;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdShear(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMirror : public GUICmdPacketBase
{
public:
	bool	XMode;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdMirror(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdCenterize: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	double	ZoomRate;
	bool	OnlyOnePhase;

	GUICmdCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdCenterizeOnly: public GUICmdPacketBase
{
public:
	double	MovX,MovY;
	double	CenterX,CenterY;
	bool	OnlyOnePhase;

	GUICmdCenterizeOnly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMatchingRoughly: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	IntList		OperateCompositeIDList;	
	int			Dx,Dy;
	double	ZoomX,ZoomY;
	int		ZoomStartX,ZoomStartY;

	GUICmdMatchingRoughly(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMatchingRoughlyReqShrinked: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;
	double		ShrinkedRate;

	GUICmdMatchingRoughlyReqShrinked(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdMatchingRoughlyAckShrinked: public GUICmdPacketBase
{
public:
	QByteArray	ImageData;
	QByteArray	GerberData;

	GUICmdMatchingRoughlyAckShrinked(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

//========================================================================================



class	CmdGerberDrawEnd : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdGerberDrawEnd(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberDrawEnd(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberBackPage : public GUIDirectMessage
{
public:
	int		BackPage;

	CmdGerberBackPage(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberBackPage(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGerberReflectData : public GUIDirectMessage
{
public:
	BoolList	ButtonsToShowLayer;
	BoolList	ButtonsToShowComposite;
	BoolList	ButtonsToOperateLayer;
	BoolList	ButtonsToOperateComposite;

	CmdGerberReflectData(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberReflectData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSendGerberCompositeDefPack: public GUICmdPacketBase
{
public:
	GerberCompositeDefPack	CompData;

	GUICmdSendGerberCompositeDefPack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName );	
};


//==============================================================================================

class	GUICmdMakeAutoMatch: public GUICmdPacketBase
{
public:
	bool	UsageLayer;
	int		UsageLayerID;
	bool	RemoveShiftable;
	BoolList	ButtonsToOperateLayer;
	IntList		ShiftableCompositeIDList;
	BoolList	ShiftableLayer;
	BoolList	ShiftableComposite;
	int32	MinDotsForAutoMatching;
	int32	ShrinkDotForAutoMatchingArea;

	GUICmdMakeAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdClearAutoMatch: public GUICmdPacketBase
{
public:

	GUICmdClearAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdExecAutoMatch: public GUICmdPacketBase
{
public:
	bool	UsageLayer;
	int		UsageLayerID;
	bool	RemoveShiftable;
	BoolList	ShiftableLayer;
	BoolList	ShiftableComposite;
	bool	BrighterInPattern;

	GUICmdExecAutoMatch(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


class	GUICmdReqOutsideOtherAlgorithm: public GUICmdPacketBase
{
public:

	GUICmdReqOutsideOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckOutsideOtherAlgorithm: public GUICmdPacketBase
{
public:
	ItemDataOutsideContaner		Items;

	GUICmdAckOutsideOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	SlaveCommReqItemsOutside : public DirectCommPacketBase
{
public:
	int		DestGlobalPage;
	QString	AlgoRoot;
	QString	AlgoName;

	SlaveCommReqItemsOutside(LayersBase  *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	SlaveCommAckItemsOutside : public DirectCommPacketBase
{
public:
	QByteArray	ItemsData;

	SlaveCommAckItemsOutside(LayersBase *base 
					,  const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdReflectOtherAlgorithm: public GUICmdPacketBase
{
public:
	ItemDataOutsideContaner		AddedItems;

	GUICmdReflectOtherAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdSetAutoMatchButtons: public GUICmdPacketBase
{
public:
	bool	DrawAutoMatchingArea;
	bool	DrawAutoMatchingImage;

	GUICmdSetAutoMatchButtons(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================================================
class	GUICmdRemoveAutoMatchingPoint : public GUICmdPacketBase
{
public:
	int	LocalX,LocalY;

	GUICmdRemoveAutoMatchingPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================================================
class	GUICmdAllocateAutoMatching : public GUICmdPacketBase
{
public:
	GUICmdAllocateAutoMatching(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================================================
class	GUICmdReqAlgoGenMap: public GUICmdPacketBase
{
public:
	GUICmdReqAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
class	GUICmdAckAlgoGenMap: public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdAckAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetAlgoGenMap: public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSetAlgoGenMap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================================

class	GUICmdReqApertureInfo: public GUICmdPacketBase
{
public:
	int	GerberLayer;

	GUICmdReqApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckApertureInfo: public GUICmdPacketBase
{
public:
	GerberApertureInfoContainer	InfoList;

	GUICmdAckApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdChangeApertureInfo: public GUICmdPacketBase
{
public:
	int	GerberLayer;
	GerberApertureInfoContainer	InfoList;
	BoolList	SelectedList;

	GUICmdChangeApertureInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdReqFlushMatrix: public GUICmdPacketBase
{
public:
	BoolList	ButtonsToShowLayer;
	IntList		OperateCompositeIDList;	

	GUICmdReqFlushMatrix(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckFlushMatrix: public GUICmdPacketBase
{
public:
	PasteListMatrixContainer	MatrixData;

	GUICmdAckFlushMatrix(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetDrawAttr : public GUICmdPacketBase
{
public:
	IntListFast		ShownFileID;
	IntListFast		ShownCompositeID;
	IntListFast		OperationalFileID;
	IntListFast		OperationalCompositeID;
	QColor			LayerColor[MaxGerberLayer];
	int				FileLayerIDTable[MaxGerberLayer];
	QColor			CompColor[MaxGerberLayer];

	GUICmdSetDrawAttr(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//=============================================================================================

class	GUICmdReqMatchAutoLikeManual: public GUICmdPacketBase
{
public:

	GUICmdReqMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f)	{	return true;	}
	bool	Load(QIODevice *f)	{	return true;	}

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckMatchAutoLikeManual: public GUICmdPacketBase
{
public:
	QByteArray	MatchAutoLikeManualData;

	GUICmdAckMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	GUICmdSendMatchAutoLikeManual: public GUICmdPacketBase
{
public:
	QByteArray	MatchAutoLikeManualData;

	GUICmdSendMatchAutoLikeManual(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAddMatchAutoLikeManualPoint: public GUICmdPacketBase
{
public:
	int		PointType;

	GUICmdAddMatchAutoLikeManualPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAddMatchingAlignmentPoint: public GUICmdPacketBase
{
public:
	int			PointType;
	FlexArea	Area;
	IntList		LayerList;

	GUICmdAddMatchingAlignmentPoint(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//==============================================================

class	GUICmdGenerateOutline : public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	BoolList	ButtonsToOperateComposite;

	GUICmdGenerateOutline(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdCreateEchingFactor : public GUICmdPacketBase
{
public:
	double	CornerR;

	GUICmdCreateEchingFactor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdClearOutline : public GUICmdPacketBase
{
public:

	GUICmdClearOutline(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================
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
	int		LineNo;

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
class	GUICmdAddEmptyLayer: public GUICmdPacketBase
{
public:
	int		LineNo;

	GUICmdAddEmptyLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

class	GUICmdAckAddEmptyLayer: public GUICmdPacketBase
{
public:
	int		FileLayerID;

	GUICmdAckAddEmptyLayer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};
//==============================================================
class	GUICmdAddGerberLine: public GUICmdPacketBase
{
public:
	int		FileLayerNo;
	int		DCode;
	double	X1,Y1,X2,Y2;

	GUICmdAddGerberLine(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};
//==============================================================

class	GUICmdGenerateCenterize : public GUICmdPacketBase
{
public:
	double MaxWidth;

	GUICmdGenerateCenterize(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================

class	GUICmdGenerateBlockFrom : public GUICmdPacketBase
{
public:
	int	LayerOrComposite;	//0:Layer ,1:Composite;
	int	LayerCompositeID;
	int	GeneratedLibType;
	int	GeneratedLibID;
	int	OmitLayerOrComposite;	//0:Layer ,1:Composite;
	int	OmitLayerCompositeID;

	GerberGenerationFileContainer	GFileContainer;

	QByteArray	ThresholdData;

	GUICmdGenerateBlockFrom(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

//==============================================================

class	GUICmdMakeClusterItem : public GUICmdPacketBase
{
public:
	BoolList	ButtonsToOperateLayer;
	IntList		OperateCompositeIDList;

	GUICmdMakeClusterItem(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
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

class	CmdGerberSelectLayerNo : public GUIDirectMessage
{
public:
	int32	GenGerberLayerNo;
	int32	GenGerberLib;

	CmdGerberSelectLayerNo(LayersBase *base):GUIDirectMessage(base){}
	CmdGerberSelectLayerNo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdSetGenerateAlgo : public GUIDirectMessage
{
public:
	int32	GenLibType;
	int32	GenLibID;
	int32	GenGerberLayerNo;
	int32	GerberAlgoType;
	int32	GenGerberLib;

	GUICmdSetGenerateAlgo(LayersBase *base):GUIDirectMessage(base){}
	GUICmdSetGenerateAlgo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	GUICmdGenerateAlgo : public GUIDirectMessage
{
public:
	GUICmdGenerateAlgo(LayersBase *base):GUIDirectMessage(base){}
	GUICmdGenerateAlgo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
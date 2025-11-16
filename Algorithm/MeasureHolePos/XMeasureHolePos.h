/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureHolePos\XMeasureHolePos.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XMEASUREPOS_H)
#define	XMEASUREPOS_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XColorSpace.h"
#include "XMeasureCommon.h"
#include "XFlexAreaImage.h"


#define	MeasureHolePosVersion	1
#define	MeasureHolePosItem_ItemClass_Area	1
#define	MeasureHolePosItem_ItemClass_Vector	2
#define	DefLibTypeMeasureHolePos	19

class	MeasureHolePosItem;
class	MeasureHolePosItemBase;

class	MeasureHolePosLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	ColorLogic	HoleColor;
	double		DiaPrecision;	//micron size
	double		PosPrecision;	//micron size
	int			NoiseSize;
	int			BandWidth;
	int			SearchDot;
	int			CalcMode;		//0;Normal 1:Precise

public:
	MeasureHolePosLibrary(int LibType,LayersBase *Base);
	virtual	~MeasureHolePosLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	MeasureHolePosLibrary	&operator=(const AlgorithmLibrary &src)	override;
};

class	MeasureHolePosLibraryContainer : public AlgorithmLibraryContainer
{
public:
	MeasureHolePosLibraryContainer(LayersBase *base);
	virtual	~MeasureHolePosLibraryContainer(void);

	virtual	int	GetLibType(void)				override{	return DefLibTypeMeasureHolePos;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "MeasureHolePos Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new MeasureHolePosLibrary(GetLibType(),GetLayersBase());	}
};

class	MeasureHolePosThreshold : public AlgorithmThreshold
{
public:
	ColorLogic	HoleColor;
	double		DiaPrecision;	//micron size
	double		PosPrecision;	//micron size
	int			NoiseSize;
	int			BandWidth;
	int			SearchDot;
	int			CalcMode;		//0;Normal 1:Precise

	MeasureHolePosThreshold(MeasureHolePosItemBase *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)		override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)		override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MeasureHolePosItemBase : public AlgorithmItemPI
{
protected:
	FlexAreaImageListCoeff	AreaEdgeTop;
	FlexAreaImageListCoeff	AreaEdgeLeft;
	FlexAreaImageListCoeff	AreaEdgeRight;
	FlexAreaImageListCoeff	AreaEdgeBottom;

	FlexArea	AreaTopI;
	FlexArea	AreaTopO;
	double		AvrTopI;
	double		AvrTopO;

	FlexArea	AreaLeftI;
	FlexArea	AreaLeftO;
	double		AvrLeftI;
	double		AvrLeftO;

	FlexArea	AreaRightI;
	FlexArea	AreaRightO;
	double		AvrRightI;
	double		AvrRightO;

	FlexArea	AreaBottomI;
	FlexArea	AreaBottomO;
	double		AvrBottomI;
	double		AvrBottomO;

	int			AMx,AMy;

public:
	AlignmentPacket2D	*AVector;
	double	MasterDiameterX,MasterDiameterY;
	double	MasterPosX;
	double	MasterPosY;

	double	ResultHeightDiff;
	double	ResultWidthDiff;
	double	ResultPosXDiff;
	double	ResultPosYDiff;
	double	RxTop ,RyTop;
	double	RxLeft ,RyLeft;
	double	RxRight ,RyRight;
	double	RxBottom ,RyBottom;

	double	PreciseMasterCx,PreciseMasterCy;
	double	PreciseMasterRx,PreciseMasterRy;
	double	PreciseTargetCx,PreciseTargetCy;
	double	PreciseTargetRx,PreciseTargetRy;


	MeasureHolePosItemBase (void);

	const	MeasureHolePosThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MeasureHolePosThreshold *)GetThresholdBaseReadable(base);	}
	MeasureHolePosThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MeasureHolePosThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MeasureHolePosThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	void	CopyThresholdOnly(MeasureHolePosItemBase &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
	ExeResult	ExecuteProcessingPrecise(ResultInItemRoot *Res,ImageBuffer *ImageList[],int ImageNumb);

protected:
	/*
	void	CalcCoefOne(FlexArea &EArea, int mx ,int my ,double &Rx ,double &Ry
											,ImageBuffer *ImageListMaster[10]
											,ImageBuffer *ImageListTarget[10]);
											*/
	void	CalcCoefOne(FlexAreaImageListCoeff &EArea, int mx ,int my ,double &Rx ,double &Ry
											,ImageBuffer *ImageListTarget[]
											,FlexArea &AreaInside ,double MasterColorI
											,FlexArea &AreaOutside ,double MasterColorO);

	double	ExpFunc(double c ,double MasterC);
	double	GetSemiCoeff(FlexArea &EArea 
						,ImageBuffer &Src 
						,double dx ,double dy 
						,ImageBuffer &Dst);	//‘ŠŒÝ‘ŠŠÖ‚ÌŒvŽZ
	void	MakeIdeal(FlexAreaImageListCoeff &Area);
	double	PreciseCalc(double Cx,double Cy ,double Rx, double Ry
						, int BandWidth
						, ImageBuffer *ImageList[],int ImageNumb);
};

class	MeasureHolePosItem : public MeasureHolePosItemBase, public MeasureCommon
{
	FlexArea	AreaHole;

public:

	MeasureHolePosItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureHolePosItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return MeasureHolePosItem_ItemClass_Area;		}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	int		GetItemID(void)						override{	return GetID();	}
	virtual	double	GetIsolation(double x ,double y)	override;
	virtual	double	GetDrawParam(double x ,double y)	override;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	override;
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)		override;
	virtual	void	GetShiftVector(double &sx, double &sy)					override;
	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)							override{	return this;	}
	virtual	void	GetCenterPoint(double &cx, double &cy)					override;
	virtual	void	Move(double dx ,double dy)								override;
	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	override{}
};


class	MeasureHolePosVectorItem : public MeasureHolePosItemBase, public MeasureCommon
{
public:
	MeasureHolePosVectorItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureHolePosVectorItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return MeasureHolePosItem_ItemClass_Vector;		}

	const	MeasureHolePosThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MeasureHolePosThreshold *)GetThresholdBaseReadable(base);	}
	MeasureHolePosThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MeasureHolePosThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MeasureHolePosThreshold(this);	}

	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	override{	return (GetVector()!=NULL)?GetVector()->GetXY(x1,y1,x2,y2):false;	}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	int		GetItemID(void)						override	{	return GetID();	}
	virtual	double	GetIsolation(double x ,double y)	override;
	virtual	double	GetDrawParam(double x ,double y)	override;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	override;
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)		override;
	virtual	void	GetShiftVector(double &sx, double &sy)					override;
	virtual	void	GetCenterPoint(double &cx, double &cy)					override;
	virtual	void	Move(double dx ,double dy)								override;

	virtual	VectorLineBase	*CreateVectorBase(void)		override{	return new VectorLineArc();	}
	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)		override{	return this;	}

	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	override{}
private:
	void	ExecuteInitialAfterEditInner(ExecuteInitialAfterEditInfo &EInfo);
};
class   MeasureHolePosInPage : public AlgorithmInPagePI
{
public:
	BYTE	**MaskingMap;
	int		XByte;

	MeasureHolePosInPage(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
};

class	MeasureHolePosBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	int		ResultLineWidth;

	double	Offset;
	double	Gain;

	MeasureHolePosBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MeasureHolePosInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MeasureHolePos");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMeasureHolePos.dat");		}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	AvailableShrinkItem(void)		const	override	{	return false;	}
	virtual	bool	AvailableChangeLibrary(void)	const	override	{	return false;	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	ReqTryThresholdCommand					7
#define	SendTryThresholdCommand					8

class	HolePosReqTryThreshold
{
public:
	int32	GlobalPage;
	int		ItemID;	
	MeasureHolePosVectorItem	Threshold;

	HolePosReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};


class	HolePosSendTryThreshold : public AddedDataClass
{
public:
	double	HoleV;
	double	HoleH;
	double	PosDiffX;
	double	PosDiffY;
	int		Error;

	HolePosSendTryThreshold(void);

	void	ConstructList(HolePosReqTryThreshold *reqPacket,MeasureHolePosBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===================================================================================

class	AddMeasureHolePosAreaPacket : public GUIDirectMessage
{
public:
	ColorLogic	HoleColor;
	FlexArea	MaskArea;

	AddMeasureHolePosAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMeasureHolePosAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MeasureHolePosDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	enum	__DMode{
		__Mode_Area
		,__Mode_Hole
		,__Mode_Edge
	}DMode;

	MeasureHolePosDrawAttr(void){}
	MeasureHolePosDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	MeasureHolePosDrawAttr( 
					 QColor ncol ,int ntranparentLevel
					,QColor scol ,int stranparentLevel
					,QColor acol ,int atranparentLevel
					,QColor nncol
					,QColor nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
};

class	CmdMeasureHolePosDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMeasureHolePosDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
	CmdMeasureHolePosDrawPacket(GUICmdPacketBase *gbase,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(gbase)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdCreateTempMeasureHolePosItemPacket :public GUIDirectMessage
{
public:
	MeasureHolePosItem	*Point;

	CmdCreateTempMeasureHolePosItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMeasureHolePosItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempMeasureHolePosLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempMeasureHolePosLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMeasureHolePosLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetMeasureHolePosLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMeasureHolePosLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMeasureHolePosLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadMeasureHolePosLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearMeasureHolePosLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearMeasureHolePosLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteMeasureHolePosLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteMeasureHolePosLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateByteArrayFromMeasureHolePosItemPacket : public GUIDirectMessage
{
public:
	MeasureHolePosItem	*Point;
	QByteArray	Buff;
	CmdCreateByteArrayFromMeasureHolePosItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateByteArrayFromMeasureHolePosItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdAddByteMeasureHolePosItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	FlexArea	Area;
	int			LocalPage;
	VectorLineBase		*Vector;

	CmdAddByteMeasureHolePosItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteMeasureHolePosItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertMeasureHolePosLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMeasureHolePosLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateMeasureHolePosLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMeasureHolePosLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateMeasureHolePosLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateThresholdPacket : public GUIDirectMessage
{
public:
	MeasureHolePosThreshold	*Thre;

	CmdCreateThresholdPacket(LayersBase *base):GUIDirectMessage(base){	Thre=NULL;	}
	CmdCreateThresholdPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Thre=NULL;	}
};

//=================================================================================

class	HolePosListForPacket : public NPListSaveLoad<HolePosListForPacket>
{
public:
	int		ItemID;
	QString	ItemName;
	int		Page;
	int		x1,y1,x2,y2;
	int		SearchDot;
	
	HolePosListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	HolePosListForPacket	&operator=(HolePosListForPacket &src);
};

class	HolePosListForPacketPack : public NPListPackSaveLoad<HolePosListForPacket>
{
public:
	HolePosListForPacketPack(void){}

	virtual	HolePosListForPacket	*Create(void);
};

class	MakeListPacket : public GUIDirectMessage
{
public:
	HolePosListForPacketPack	*ListInfo;

	MakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif
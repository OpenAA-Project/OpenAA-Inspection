/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\LineEnhancer\XLineEnhancer.h
** Author : YYYYYYYYYY
*******************************************************************************/


#ifndef XLineEnhancer_H
#define XLineEnhancer_H

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"

#define	LineEnhancerVersion		2
#define	DefLibTypeLineEnhancer	20

class	LineEnhancerItem;

class LineEnhancerLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	MaxDot;
	int32	MinDot;
	int32	MaxSize;
	int32	MinSize;
	int32	ShrinkDot;
	int32	LimitDot;
	ColorLogic	PickupColor;
	int32	SearchBlockWidth;
	double	EmphasizeRate;
	int32	Priority;
	int32	MaxLineWidth;
	int32	StepDot;	
	int32	SelfSearch;

	LineEnhancerLibrary(int LibType,LayersBase *Base);
	virtual	~LineEnhancerLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	LineEnhancerLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImagePointerContainer &MasterImages
						 ,const BYTE **MaskBitmap
						 ,BYTE **BmpPoint 
						 ,BYTE **OcupyMap
						 ,int XByte ,int XLen ,int YLen
						 ,int OmitZoneDot
						 ,int ModeOneLayer);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPI> &BlockList);
};

class	LineEnhancerLibraryContainer : public AlgorithmLibraryContainer
{
public:
	LineEnhancerLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~LineEnhancerLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeLineEnhancer;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "LineEnhancer Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new LineEnhancerLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------
class	LineEnhancerThreshold : public AlgorithmThreshold
{
public:
	double	EmphasizeRate;
	int		MaxLineWidth;
	int		StepDot;
	int32	SelfSearch;

	LineEnhancerThreshold(LineEnhancerItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};


class	LineEnhancerItem : public AlgorithmItemPI
{
	class	AngleDimBase
	{
	public:
		double	*AddedList;
		int32	*PixelCount;
		double	*PixelCDivider;
		int		ListNumb;
		double	CosS,SinS;
		int		Cx,Cy;
		int		PointerIndexCount;
		WORD	*PointerIndex;
		double	AllAvr;

		AngleDimBase(void);
		~AngleDimBase(void);

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
		void	ExecuteStartByInspection(void);
		void	ExecutePreProcessing(int index ,BYTE c){	AddedList[PointerIndex[index]]+=c;	}
		double	MakeAverageAndPeaks(int MaxLineWidth);
		void	Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate);
	};
	class	AngleDim : public AngleDimBase
	{
	public:
		AngleDim(void){}
		~AngleDim(void){}

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
		void	Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate);
	};
	class	AngleDimDown : public AngleDimBase
	{
	public:
		AngleDimDown(void){}
		~AngleDimDown(void){}

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
	};
public:
	FlexArea		CalcArea;
	FlexArea		MatchingArea;
	AngleDim		*AngleList;
	AngleDimDown	*AngleDownList;
	int				AngleListCount;
	AlignmentPacket2D	*AVector;
	IntList			MasterBrightness;

	LineEnhancerItem(void);
	~LineEnhancerItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new LineEnhancerItem();	}
	const	LineEnhancerThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const LineEnhancerThreshold *)GetThresholdBaseReadable(base);	}
	LineEnhancerThreshold			*GetThresholdW(LayersBase *base=NULL){	return (LineEnhancerThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new LineEnhancerThreshold(this);	}
	virtual	int32		GetItemClassType(void)		override		{		return 1;		}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	CopyThreshold(LineEnhancerItem &src);
	void	CopyThresholdOnly(LineEnhancerItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
private:
	void	ExecutePreProcessingByLayer(int mx,int my,ImageBuffer &IBuff
										,int &ResMx ,int &ResMy
										,int Layer);
	double	CalcV(int mx,int my,ImageBuffer &IBuff);
};

//--------------------------------------------------------------------------------------------------------


class   LineEnhancerInPage : public AlgorithmInPagePI
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;
public:
	LineEnhancerInPage(AlgorithmBase *parent);
	~LineEnhancerInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)	override
		{	
			LineEnhancerItem	*a= new LineEnhancerItem();	
			a->SetParent(this);
			return a;
		}

	void	CreateItems(AlgorithmLibraryListContainer &LibList);
	void	PickupTest(LineEnhancerLibrary &LibData);

	virtual	void	Draw(QImage &pnt, IntList &,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
	void	CreatePickupBmpBuff(void);
	void	GenerateBlocks(LineEnhancerLibrary *LibDim[],int LibDimNumb);

};

class	LineEnhancerBase : public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		AreaColor;
	QColor		NegAreaColor;
	QColor		NegAreaColorSelected;
	int32		TransparentLevel;
	int32		OmitZoneDot;
	int			ModeOneLayer;

	LineEnhancerBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new LineEnhancerInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("LineEnhancer");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigLineEnhancer.dat");	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData)	override;

	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
#define	LineEnhancerReqThresholdReqCommand		1
#define	LineEnhancerReqThresholdSendCommand		2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4

class	LineEnhancerThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	LineEnhancerThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LineEnhancerThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int32	Dx,Dy;
	double	EmphasizeRate;
	int		MaxLineWidth;
	int		StepDot;
	int32	SelfSearch;

	LineEnhancerThresholdSend(void);

	void	ConstructList(LineEnhancerThresholdReq *reqPacket,LineEnhancerBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//===================================================================================

class	LineEnhancerDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	AreaColor;
	QColor	NegAreaColor;
	QColor	NegAreaColorSelected;
	enum	_DrawingArea
	{
		_Pickup		=0
		,_Block		=1
		,_Calc		=2
		,_Matching	=3
	}DrawingArea;

	LineEnhancerDrawAttr(void){}
	LineEnhancerDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	LineEnhancerDrawAttr(QColor ncol ,int ntranparentLevel
						,QColor scol ,int stranparentLevel
						,QColor acol ,int atranparentLevel)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		AreaColor			=ncol;	
		NegAreaColor		=acol;	
		NegAreaColorSelected=scol;	
		AreaColor			.setAlpha(ntranparentLevel);
		NegAreaColor		.setAlpha(atranparentLevel);
		NegAreaColorSelected.setAlpha(stranparentLevel);
	}
};

//===================================================================================
//==================================================================================
class	CmdCreateTempLineEnhancerLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempLineEnhancerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLineEnhancerLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetLineEnhancerLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLineEnhancerLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadLineEnhancerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadLineEnhancerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearLineEnhancerLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearLineEnhancerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteLineEnhancerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteLineEnhancerLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertLineEnhancerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertLineEnhancerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateLineEnhancerLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateLineEnhancerLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateLineEnhancerLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLineEnhancerLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetLineEnhancerLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLineEnhancerLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateLineEnhancerPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;
	CmdCreateLineEnhancerPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateLineEnhancerPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestLineEnhancerPacket : public GUIDirectMessage
{
public:
	//LineEnhancerLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;
	
	CmdPickupTestLineEnhancerPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestLineEnhancerPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestLineEnhancePacket : public GUIDirectMessage
{
public:
	CmdClearTestLineEnhancePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestLineEnhancePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqLineEnhancerDrawMode : public GUIDirectMessage
{
public:
	LineEnhancerDrawAttr::_DrawingArea	DrawingArea;

	GUICmdReqLineEnhancerDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=LineEnhancerDrawAttr::_Pickup;	}
	GUICmdReqLineEnhancerDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=LineEnhancerDrawAttr::_Pickup;	}
};

class	GUICmdSetLineEnhancerDrawMode : public GUIDirectMessage
{
public:
	LineEnhancerDrawAttr::_DrawingArea	DrawingArea;

	GUICmdSetLineEnhancerDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=LineEnhancerDrawAttr::_Pickup;	}
	GUICmdSetLineEnhancerDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=LineEnhancerDrawAttr::_Pickup;	}
};
#endif
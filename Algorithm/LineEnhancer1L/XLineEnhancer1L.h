/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\LineEnhancer1L\XLineEnhancer1L.h
** Author : YYYYYYYYYY
*******************************************************************************/


#ifndef XLineEnhancer1L_H
#define XLineEnhancer1L_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XStandardCommand.h"

#define	LineEnhancer1LVersion		6
#define	DefLibTypeLineEnhancer1L	21

class	LineEnhancer1LItem;

class LineEnhancer1LLibrary : public AlgorithmLibrary , public ServiceForLayers
{
public:
	int32	MaxDot;
	int32	MinDot;
	int32	MaxSize;
	int32	MinSize;
	int16	ShrinkDot;
	int32	LimitDot;
	int16	PickupColorL,PickupColorH;
	bool	GenerateOverlap;

	int32	SearchBlockWidth;
	double	EmphasizeRate;
	int16	Priority;
	int32	MaxLineWidth;
	int16	StepDot;	
	int16	SelfSearch;
	int16	StartAngle,EndAngle;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	bool	ExcludeDynamicMask;
	bool	FixedAngle;
	int32	SourceLayer;

	LineEnhancer1LLibrary(int LibType,LayersBase *Base);
	virtual	~LineEnhancer1LLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	LineEnhancer1LLibrary	&operator=(const AlgorithmLibrary &src)	override;

	void	MakePickupTest(ImageBuffer *MasterImage
						 ,const BYTE **MaskBitmap
						 ,BYTE **BmpPoint 
						 ,BYTE **OcupyMap
						 ,int XByte ,int XLen ,int YLen
						 ,int OmitZoneDot);
	void	MakeBlock(
			 BYTE **CurrentMap,BYTE **OcupyMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList);
	void	MakeBlockOnly(
			 BYTE **CurrentMap,const BYTE **MaskMap
			,int XByte ,int XLen,int YLen
			,NPListPack<AlgorithmItemPLI> &BlockList);

	LineEnhancer1LItem	*CreateOneItem(int Page,FlexArea &Area);
};

class	LineEnhancer1LLibraryContainer : public AlgorithmLibraryContainer
{
public:
	LineEnhancer1LLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~LineEnhancer1LLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeLineEnhancer1L;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "LineEnhancer1L Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new LineEnhancer1LLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------
class	LineEnhancer1LThreshold : public AlgorithmThreshold
{
public:
	double		EmphasizeRate;
	int16		MaxLineWidth;
	int16		StepDot;
	int16		SelfSearch;
	int16		StartAngle,EndAngle;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	bool		ExcludeDynamicMask;
	bool		FixedAngle;
	int32		SourceLayer;

	LineEnhancer1LThreshold(LineEnhancer1LItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};


class	LineEnhancer1LItem : public AlgorithmItemPLI
{
	class	AngleDimBase
	{
	public:
		double	*AddedList;
		int32	*PixelCount;
		int32	*PixelCountForDynamicMasking;
		double	*PixelCDivider;
		int		ListNumb;
		double	CosS,SinS;
		int		Cx,Cy;
		int		PointerIndexCount;
		WORD	*PointerIndex;
		double	AllAvr;
		double	*CoefPixles;
		int		CoefCount;

		AngleDimBase(void);
		~AngleDimBase(void);

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
		void	ExecuteStartByInspection(int MaxLineWidth);
		void	ExecutePreProcessing(int index ,BYTE c){	AddedList[PointerIndex[index]]+=c;	}
		void	ExecutePreProcessingReduceDynamicMasking(int index);
		double	MakeAverageAndPeaks(int MaxLineWidth ,bool ModeDynamicMask);
		void	Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate
						,bool ExcludeDynamicMask
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	};
	class	AngleDim : public AngleDimBase
	{
	public:
		AngleDim(void){}
		~AngleDim(void){}

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
		void	Reflect(int mx,int my,FlexArea &area,ImageBuffer &IBuff ,double EmphasizeRate
						,bool ExcludeDynamicMask
						,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	};
	class	AngleDimDown : public AngleDimBase
	{
	public:
		AngleDimDown(void){}
		~AngleDimDown(void){}

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo);
	};
	double	MinAngle;
public:
	FlexArea		CalcArea;
	FlexArea		MatchingArea;
	AngleDim		*AngleList;
	AngleDimDown	*AngleDownList;
	int				AngleListCount;
	int				*AnglePointList;
	AlignmentPacket2D	*AVector;
	int				MasterBrightness;

	LineEnhancer1LItem(void);
	~LineEnhancer1LItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new LineEnhancer1LItem();	}
	const	LineEnhancer1LThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const LineEnhancer1LThreshold *)GetThresholdBaseReadable(base);	}
	LineEnhancer1LThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (LineEnhancer1LThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new LineEnhancer1LThreshold(this);	}
	virtual	int32		GetItemClassType(void)	override	{		return 1;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	CopyThreshold(LineEnhancer1LItem &src);
	void	CopyThresholdOnly(LineEnhancer1LItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
private:
	void	ExecutePreProcessingByLayer(int mx,int my,ImageBuffer &IBuff
										,int &ResMx ,int &ResMy
										,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	double	CalcV(int mx,int my,ImageBuffer &IBuff
				, BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
	double	GetAverage(FlexArea &area ,ImageBuffer &Data,int dx ,int dy
										,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen);
};


//--------------------------------------------------------------------------------------------------------

class   LineEnhancer1LInLayer : public AlgorithmInLayerPLI
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

	class	ItemPointerList : public NPList<ItemPointerList>
	{
	public:
		AlgorithmItemRoot	*Pointer;
		int					Index;
		ItemPointerList(int index ,AlgorithmItemRoot *item):Pointer(item),Index(index){}
	};

	class	ItemPointerListContainer : public NPListPack<ItemPointerList>
	{
	public:
		ItemPointerListContainer(void){}
		~ItemPointerListContainer(void){}

		void	Add(int index ,AlgorithmItemRoot *item);
	};

	class	ItemByLibContainerList : public NPList<ItemByLibContainerList>,public ItemPointerListContainer
	{
	public:
		int						LibID;
		LineEnhancer1LInLayer	*Parent;

		ItemByLibContainerList(int libID,LineEnhancer1LInLayer *parent):LibID(libID),Parent(parent){}
	};
	NPListPack<ItemByLibContainerList>	ExecutingList;

public:
	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;

public:
	LineEnhancer1LInLayer(AlgorithmInPageRoot *parent);
	~LineEnhancer1LInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)	override
		{	
			LineEnhancer1LItem	*a=new LineEnhancer1LItem();	
			a->SetParent(this);
			return a;
		}
	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item)			override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override;

	void	CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList);
	bool	UseLibraryForMaskingInOtherPage(int LibID);
	void	PickupTest(LineEnhancer1LLibrary &LibData);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	GenerateBlocks(LineEnhancer1LLibrary *LibDim[],int LibDimNumb);
	bool	CreateOneItem(FlexArea &Area,int LibID);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInLayerRoot *R)	override;

	void	MoveFromPipe(GeneralPipeInfo &Info);

private:
	void	CreatePickupBmpBuff(void);

};

class   LineEnhancer1LInPage : public AlgorithmInPagePLI
{
public:
	LineEnhancer1LInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	virtual	LineEnhancer1LInLayer	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new LineEnhancer1LInLayer(parent));	}
	void	PickupTest(IntList &LayerList ,LineEnhancer1LLibrary &LibData);
	void	GenerateBlocks(IntList &LayerList, LineEnhancer1LLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;
};

class	LineEnhancer1LBase : public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		AreaColor;
	QColor		NegAreaColor;
	QColor		NegAreaColorSelected;
	int32		TransparentLevel;
	int32		OmitZoneDot;

	LineEnhancer1LBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new LineEnhancer1LInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("LineEnhancer1L");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigLineEnhancer1L.dat");		}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
#define	LineEnhancer1LReqThresholdReqCommand		1
#define	LineEnhancer1LReqThresholdSendCommand		2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4

class	LineEnhancer1LThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	LineEnhancer1LThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LineEnhancer1LThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	int32	Dx,Dy;
	double	EmphasizeRate;
	int		MaxLineWidth;
	int		StepDot;
	int32	SelfSearch;
	int16	StartAngle,EndAngle;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	bool		ExcludeDynamicMask;
	bool		FixedAngle;

	LineEnhancer1LThresholdSend(void);

	void	ConstructList(LineEnhancer1LThresholdReq *reqPacket,LineEnhancer1LBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//===================================================================================

class	LineEnhancer1LDrawAttr : public AlgorithmDrawAttr
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

	LineEnhancer1LDrawAttr(void){}
	LineEnhancer1LDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	LineEnhancer1LDrawAttr(QColor ncol ,int ntranparentLevel
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
class	CmdCreateTempLineEnhancer1LLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempLineEnhancer1LLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLineEnhancer1LLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetLineEnhancer1LLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLineEnhancer1LLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadLineEnhancer1LLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadLineEnhancer1LLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearLineEnhancer1LLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearLineEnhancer1LLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteLineEnhancer1LLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteLineEnhancer1LLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertLineEnhancer1LLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertLineEnhancer1LLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateLineEnhancer1LLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateLineEnhancer1LLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateLineEnhancer1LLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetLineEnhancer1LLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetLineEnhancer1LLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetLineEnhancer1LLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateLineEnhancer1LPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;
	IntList					LayerList;

	CmdCreateLineEnhancer1LPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateLineEnhancer1LPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestLineEnhancer1LPacket : public GUIDirectMessage
{
public:
	IntList					LayerList;
	//LineEnhancer1LLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;

	CmdPickupTestLineEnhancer1LPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestLineEnhancer1LPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestLineEnhancePacket : public GUIDirectMessage
{
public:
	CmdClearTestLineEnhancePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestLineEnhancePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqLineEnhancer1LDrawMode : public GUIDirectMessage
{
public:
	LineEnhancer1LDrawAttr::_DrawingArea	DrawingArea;

	GUICmdReqLineEnhancer1LDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=LineEnhancer1LDrawAttr::_Pickup;	}
	GUICmdReqLineEnhancer1LDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=LineEnhancer1LDrawAttr::_Pickup;	}
};

class	GUICmdSetLineEnhancer1LDrawMode : public GUIDirectMessage
{
public:
	LineEnhancer1LDrawAttr::_DrawingArea	DrawingArea;

	GUICmdSetLineEnhancer1LDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=LineEnhancer1LDrawAttr::_Pickup;	}
	GUICmdSetLineEnhancer1LDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=LineEnhancer1LDrawAttr::_Pickup;	}
};

class	CmdAddByteLineEnhancer1LItemPacket : public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteLineEnhancer1LItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteLineEnhancer1LItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempLineEnhancer1LItemPacket : public GUIDirectMessage
{
public:
	LineEnhancer1LItem	*Point;
	CmdCreateTempLineEnhancer1LItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempLineEnhancer1LItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif
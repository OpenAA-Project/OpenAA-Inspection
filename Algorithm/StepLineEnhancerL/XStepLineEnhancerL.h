/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\StepLineEnhancerL\XStepLineEnhancerL.h
** Author : YYYYYYYYYY
*******************************************************************************/


#ifndef XStepLineEnhancerL_H
#define XStepLineEnhancerL_H

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlexAreaImage.h"
#include "XStandardCommand.h"

#define	StepLineEnhancerLVersion		4
#define	DefLibTypeStepLineEnhancerL	21

class	StepLineEnhancerLItem;

class StepLineEnhancerLLibrary : public AlgorithmLibrary , public ServiceForLayers
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

	StepLineEnhancerLLibrary(int LibType,LayersBase *Base);
	virtual	~StepLineEnhancerLLibrary(void);

	virtual	bool	SaveBlob(QIODevice *f)	override;
	virtual	bool	LoadBlob(QIODevice *f)	override;

	virtual	StepLineEnhancerLLibrary	&operator=(const AlgorithmLibrary &src)	override;

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
	StepLineEnhancerLItem	*CreateOneItem(FlexArea &Area);
};

class	StepLineEnhancerLLibraryContainer : public AlgorithmLibraryContainer
{
public:
	StepLineEnhancerLLibraryContainer(LayersBase *base):AlgorithmLibraryContainer(base){}
	virtual	~StepLineEnhancerLLibraryContainer(void){}

	virtual	int	GetLibType(void)				override{	return DefLibTypeStepLineEnhancerL;	}
	virtual	const char	*GetLibTypeName(void)	override{	return "StepLineEnhancerL Library";	}
	virtual	AlgorithmLibrary	*CreateNew(void)override{	return new StepLineEnhancerLLibrary(GetLibType(),GetLayersBase());	}
};

//--------------------------------------------------------------------------------------------------------
class	StepLineEnhancerLThreshold : public AlgorithmThreshold
{
public:
	double		EmphasizeRate;
	int16		MaxLineWidth;
	int16		StepDot;
	int16		SelfSearch;
	int16		StartAngle,EndAngle;	//ÇOÅ`ÇRÇUÇOÇ≈ÅAîΩéûåvâÒÇËÇÃäpìx
	bool		ExcludeDynamicMask;

	StepLineEnhancerLThreshold(StepLineEnhancerLItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	override;
	virtual	bool	Save(QIODevice *f)				override;
    virtual	bool	Load(QIODevice *f)				override;
    virtual	int		GetSize(void)					override	{	return sizeof(this);	}

	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
};


class	StepLineEnhancerLItem : public AlgorithmItemPLI
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

		AngleDimBase(void);
		~AngleDimBase(void);

		void	Initial(double Radian, FlexArea &area);
		void	ExecuteInitialAfterEdit(FlexArea &area,ExecuteInitialAfterEditInfo &EInfo)	;
		void	ExecuteStartByInspection(void);
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

	StepLineEnhancerLItem(void);
	~StepLineEnhancerLItem(void);

	const	StepLineEnhancerLThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const StepLineEnhancerLThreshold *)GetThresholdBaseReadable(base);	}
	StepLineEnhancerLThreshold			*GetThresholdW(LayersBase *base=NULL){	return (StepLineEnhancerLThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new StepLineEnhancerLThreshold(this);	}
	virtual	int32		GetItemClassType(void)		override{		return 1;		}

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	void	CopyThreshold(StepLineEnhancerLItem &src);
	void	CopyThresholdOnly(StepLineEnhancerLItem &src);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer
								   ,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

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

class   StepLineEnhancerLInLayer : public AlgorithmInLayerPLI
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

	class	ItemPointerList : public NPList<ItemPointerList>
	{
	public:
		AlgorithmItemRoot	*Pointer;
		int					Index;
		ItemPointerList(int index ,AlgorithmItemRoot *item)
			:Pointer(item),Index(index){}
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
		StepLineEnhancerLInLayer	*Parent;

		ItemByLibContainerList(int libID,StepLineEnhancerLInLayer *parent):LibID(libID),Parent(parent){}
	};
	NPListPack<ItemByLibContainerList>	ExecutingList;

public:
	BYTE	**DynamicMaskMap;
	int		DynamicMaskMapXByte;
	int		DynamicMaskMapYLen;

public:
	StepLineEnhancerLInLayer(AlgorithmInPageRoot *parent);
	~StepLineEnhancerLInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType=0)	override
		{	
			StepLineEnhancerLItem	*a=new StepLineEnhancerLItem();	
			a->SetParent(this);
			return a;
		}

	void	CreateItems(IntList &LayerList ,AlgorithmLibraryListContainer &LibList);
	void	PickupTest(StepLineEnhancerLLibrary &LibData);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	GenerateBlocks(StepLineEnhancerLLibrary *LibDim[],int LibDimNumb);
	bool	CreateOneItem(FlexArea &Area,int LibID);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreProcessing	(int ExeID ,ResultInLayerRoot *Res)	override;

private:
	void	CreatePickupBmpBuff(void);

};

class   StepLineEnhancerLInPage : public AlgorithmInPagePLI
{
public:
	StepLineEnhancerLInPage(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}
	
	virtual	StepLineEnhancerLInLayer	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new StepLineEnhancerLInLayer(parent));	}
	void	PickupTest(IntList &LayerList ,StepLineEnhancerLLibrary &LibData);
	void	GenerateBlocks(IntList &LayerList, StepLineEnhancerLLibrary *LibDim[],int LibDimNumb);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
};

class	StepLineEnhancerLBase : public AlgorithmBase
{
public:
	QColor		ColorPickup;
	QColor		AreaColor;
	QColor		NegAreaColor;
	QColor		NegAreaColorSelected;
	int32		TransparentLevel;
	int32		OmitZoneDot;

	StepLineEnhancerLBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new StepLineEnhancerLInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("StepLineEnhancerL");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigStepLineEnhancerL.dat");		}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};
//==================================================================================
#define	StepLineEnhancerLReqThresholdReqCommand		1
#define	StepLineEnhancerLReqThresholdSendCommand		2
#define	SetIndependentItemDataCommand_OnlyOne	3
#define	SetIndependentItemDataCommand_All		4

class	StepLineEnhancerLThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	int		Layer;
	bool	Mastered;
	int32	Dx,Dy;

	StepLineEnhancerLThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	StepLineEnhancerLThresholdSend
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

	StepLineEnhancerLThresholdSend(void);

	void	ConstructList(StepLineEnhancerLThresholdReq *reqPacket,StepLineEnhancerLBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


//===================================================================================

class	StepLineEnhancerLDrawAttr : public AlgorithmDrawAttr
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

	StepLineEnhancerLDrawAttr(void){}
	StepLineEnhancerLDrawAttr(QColor ncol ,QColor scol ,QColor acol):AlgorithmDrawAttr(ncol,scol,acol){}
	StepLineEnhancerLDrawAttr(QColor ncol ,int ntranparentLevel
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
class	CmdCreateTempStepLineEnhancerLLibraryPacket: public GUIDirectMessage
{
public:
	StepLineEnhancerLLibrary	*Point;
	CmdCreateTempStepLineEnhancerLLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetStepLineEnhancerLLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetStepLineEnhancerLLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStepLineEnhancerLLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdLoadStepLineEnhancerLLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	bool				Success;
	CmdLoadStepLineEnhancerLLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearStepLineEnhancerLLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdClearStepLineEnhancerLLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteStepLineEnhancerLLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdDeleteStepLineEnhancerLLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertStepLineEnhancerLLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdInsertStepLineEnhancerLLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdUpdateStepLineEnhancerLLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdUpdateStepLineEnhancerLLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateStepLineEnhancerLLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetStepLineEnhancerLLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetStepLineEnhancerLLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetStepLineEnhancerLLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateStepLineEnhancerLPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	int								LocalPage;
	IntList					LayerList;

	CmdCreateStepLineEnhancerLPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateStepLineEnhancerLPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupTestStepLineEnhancerLPacket : public GUIDirectMessage
{
public:
	IntList					LayerList;
	//StepLineEnhancerLLibrary	*LibPoint;
	AlgorithmLibraryLevelContainer	*LibPoint;

	CmdPickupTestStepLineEnhancerLPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupTestStepLineEnhancerLPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdClearTestLineEnhancePacket : public GUIDirectMessage
{
public:
	CmdClearTestLineEnhancePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearTestLineEnhancePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdReqStepLineEnhancerLDrawMode : public GUIDirectMessage
{
public:
	StepLineEnhancerLDrawAttr::_DrawingArea	DrawingArea;

	GUICmdReqStepLineEnhancerLDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=StepLineEnhancerLDrawAttr::_Pickup;	}
	GUICmdReqStepLineEnhancerLDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=StepLineEnhancerLDrawAttr::_Pickup;	}
};

class	GUICmdSetStepLineEnhancerLDrawMode : public GUIDirectMessage
{
public:
	StepLineEnhancerLDrawAttr::_DrawingArea	DrawingArea;

	GUICmdSetStepLineEnhancerLDrawMode(LayersBase *base):GUIDirectMessage(base){	DrawingArea=StepLineEnhancerLDrawAttr::_Pickup;	}
	GUICmdSetStepLineEnhancerLDrawMode(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	DrawingArea=StepLineEnhancerLDrawAttr::_Pickup;	}
};

class	CmdAddByteStepLineEnhancerLItemPacket : public GUIDirectMessage
{
public:
	int			LibID;
	FlexArea	Area;
	IntList		LayerList;
	int			LocalPage;
	CmdAddByteStepLineEnhancerLItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdAddByteStepLineEnhancerLItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempStepLineEnhancerLItemPacket : public GUIDirectMessage
{
public:
	StepLineEnhancerLItem	*Point;
	CmdCreateTempStepLineEnhancerLItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempStepLineEnhancerLItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XMasking.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef XMasking
#define XMasking

#include "XDataInLayer.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XDirectComm.h"
#include "XIntClass.h"
#include "XGeneralFunc.h"
#include "NListComp.h"
//#include "XMaskingLibrary.h"

class	MaskingItem;
class	MaskingCutLineItem;
class	MaskingInLayer;
class	MaskingInPage;
class	MaskingBase;

#define	MaskingVersion	3

class	MaskingLibrary;


class	MaskingThreshold : public AlgorithmThreshold
{
public:
    bool							Effective;		// true=有効エリア
    AlgorithmLibraryListContainer	SelAreaID;		// 限定マスク

	MaskingThreshold(MaskingItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	bool	IsLimited(void){	return (SelAreaID.GetFirst()!=NULL)?true:false;	}
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

class	MaskingItem : public AlgorithmItemPLITemplate<MaskingInLayer,MaskingInPage,MaskingBase>
{
public:
	MaskingItem(void);
	~MaskingItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MaskingItem();	}
	const	MaskingThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MaskingThreshold *)GetThresholdBaseReadable(base);	}
	MaskingThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MaskingThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MaskingThreshold(this);	}

	virtual	QString	GetComment(Type_ItemComment t)	override;
	virtual	int32		GetItemClassType(void)		override	{		return 0;		}
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)					override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)override;
	virtual	bool	IsEffective(void)	const	override;
	virtual	void	SetEffective(bool effective)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	bool	IsValid(void)		override;
	virtual	void	MoveForAlignment(void)	override;
};

//--------------------------------------------------------
class	MaskingCutLineThreshold : public AlgorithmThreshold
{
public:
	MaskingCutLineThreshold(MaskingCutLineItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override{	return true;	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
};

class	MaskingCutLineItem : public AlgorithmItemPLITemplate<MaskingInLayer,MaskingInPage,MaskingBase>
{
public:
	MaskingCutLineItem(void){}
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MaskingCutLineItem();	}
	const	MaskingCutLineThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MaskingCutLineThreshold *)GetThresholdBaseReadable(base);	}
	MaskingCutLineThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MaskingCutLineThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold		*CreateThresholdInstance(void)	override{	return new MaskingCutLineThreshold(this);	}

	virtual	int32		GetItemClassType(void)			override	{		return 1;		}
	virtual	VectorLineBase	*CreateVectorBase(void)		override;
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	MakeCutLineMap(BYTE **MaskBitmap ,int XByte ,int YLen);
	virtual	void	MoveForAlignment(void)	override;
};

class   MaskingInLayer : public AlgorithmInLayerPLITemplate<MaskingItem,MaskingInPage,MaskingBase>
{
public:
	ImageBuffer		BackGroundImage;

	MaskingInLayer(AlgorithmInPageRoot *parent);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;
	//void	AddMask(MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool    Save(QIODevice *f)	override;
    virtual	bool    Load(QIODevice *f)	override;

	void	GenerateMaskInSameColor(int PickupL ,int PickupH ,bool Effective);
	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen
						,bool GenerateOnlyLimitMask=false);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen); 

	void	AddMaskItems(PureFlexAreaListContainer &Areas
						,bool Effective ,AlgorithmLibraryListContainer &LimitedLib
						,AlgorithmItemPointerListContainer &Appended);
	void	MakeCutLineMap(BYTE **MaskBitmap ,int XByte ,int YLen);

	void	UndoAppendManualItem(QIODevice *f);
	void	UndoGenerateMaskOnSelectedItemsEdge(QIODevice *f);
	void	UndoMakePatternEdge(QIODevice *f);

	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)	override;
	void	MakeBackGround(bool MasterMode);
	void	ClearBackGround(void);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,void *Anything=NULL)	override;
	virtual	bool	IncludeLibInReflectionForGenerator(ReflectionMode Mode,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret)			override;

	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);

	void	MoveFromPipe(GeneralPipeInfo &Info);
	int		ReqItemsToMoveByAlignmentOutside(GeneralPipeInfo &Info
										,int RelativeDestAreaX1,int RelativeDestAreaY1,int RelativeDestAreaX2,int RelativeDestAreaY2
										,int dx,int dy
										,QByteArray &Array);
	void	CopyMoveByAlignmentFromOutside(GeneralPipeInfo &Info,int N ,QByteArray &Array);
};

class   MaskingInPage : public AlgorithmInPagePLITemplate<MaskingItem,MaskingInLayer,MaskingBase>
{
	BYTE	**PickupBmp;
	int		PickupBmpXByte;
	int		PickupBmpYLen;

public:
	MaskingInPage(AlgorithmBase *parent);
	~MaskingInPage(void);

	virtual	AlgorithmInLayerPLI	*NewChild(AlgorithmInPageRoot *parent)	override{	return new MaskingInLayer(parent);	}
	//void	AddMask(IntList &LayerList , MaskArea &mask);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MaskVector ,int layer ,void *Anything=NULL)	override;
	virtual	bool	IncludeLibInReflectionForGenerator(ReflectionMode Mode,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibraryListContainer &Ret)			override;

	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int localX1, int localY1, int localX2 ,int localY2);
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;

	void	MakeBackGround(bool MasterMode);
	void	ClearBackGround(void);

private:
	void	CreatePickupBmp(void);
	void	MaskHole(FlexArea &PickupArea
					,int BladeHoleMinArea
					,int BladeHoleErosionDot
					,PureFlexAreaListContainer &HolePack);
	void	MakePatternEdge(bool Effective
						,AlgorithmLibraryListContainer &LimitedLib
						,int BoundaryDiff
						,int WidthDot);
	void	GenerateMaskFromBackGround(int DiffBrightness
									  ,int MinObjectDotCount
									  ,int BoundaryWidth
									  ,PureFlexAreaListContainer &Areas
									  ,int SearchDot);
};

class	MaskingBase : public AlgorithmBase
{
public:
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	int32	SelectedTransparentLevel;
	int32	ActiveTransparentLevel	;
	QColor	NegColorMask;
	QColor	NegColorSelected;

	QColor	ColorEffective;
	QColor	ColorEffectiveLimited;
	QColor	ColorIneffective;
	QColor	ColorIneffectiveLimited;
	QColor	TestColor;
	int32	OmitWidthForAutoPour;
	bool	UseLibColor;
	int32	AlphaBackGround;
	int32	NoisePinhole ;
	int32	NoiseSmallDot;
	int32	EdgeAverageXLen;
	int32	EdgeAverageYLen;
	int32	EdgeAverageMinArea;

	MaskingBase(LayersBase *Base);

	virtual	AlgorithmInPagePLI	*NewChild(AlgorithmBase *parent)	override{	return new MaskingInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("Masking");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMasking.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	virtual	bool	HasReflection(ReflectionMode mode)	override	{	return (mode==_Reflection_Mask || mode==_Reflection_MaskOnlyInLimitMask)?true:false;	}

	virtual	bool	PipeOutAutoGenerationForLearning(QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;
	virtual	bool	PipeInAutoGenerationForLearning (QIODevice *f ,int LocalPage ,int localX1, int localY1, int localX2 ,int localY2)	override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)					override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================
//===================================================================================
class	CmdGetMaskingLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetMaskingLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMaskingLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AddMaskingAreaPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	FlexArea	Area;
	bool		Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	AddMaskingAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMaskingAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	DelMaskingPacket : public GUIDirectMessage
{
public:
	IntList		LayerList;
	bool		Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	DelMaskingPacket(LayersBase *base):GUIDirectMessage(base){}
	DelMaskingPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class AddMaskingLinePacket: public GUIDirectMessage
{
public:
	IntList		LayerList;
	VectorLineBase	*Vector;

	AddMaskingLinePacket(LayersBase *base):GUIDirectMessage(base){}
	AddMaskingLinePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	MaskingDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask			;
	QColor	NegColorSelected		;
	bool	EffectiveMode			;
	bool	IneffectiveMode			;
	bool	EffectiveLimitedMode	;
	bool	IneffectiveLimitedMode	;
	bool	ShowBackGround			;
	QColor	ColorEffective			;
	QColor	ColorEffectiveLimited	;
	QColor	ColorIneffective		;
	QColor	ColorIneffectiveLimited	;
	int		SelectedLibID			;
	bool	ShowOnlyLibID;
	int32	TransparentLevel		;
	int32	SelectedTransparentLevel;
	int32	ActiveTransparentLevel	;

	MaskingDrawAttr(void){	SelectedLibID=-1;	ShowOnlyLibID=false;	}
	MaskingDrawAttr(QColor ncol ,QColor scol ,QColor acol)
		:AlgorithmDrawAttr(ncol,scol,acol)
		,SelectedLibID(-1)
		,ShowOnlyLibID(false){}
	MaskingDrawAttr(			 int ntranparentLevel
					,const QColor &scol ,int stranparentLevel
					,const QColor &acol ,int atranparentLevel
					,const QColor &nncol
					,const QColor &nscol)
		:AlgorithmDrawAttr(scol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
		ShowBackGround		=false;
		SelectedLibID		=-1;
		ShowOnlyLibID		=false;
		TransparentLevel		=128;
		SelectedTransparentLevel=128;
		ActiveTransparentLevel	=128;
	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

inline	bool	MaskingDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,NegColorMask)==false)
		return false;
	if(::Save(f,NegColorSelected)==false)
		return false;
	if(::Save(f,EffectiveMode)==false)
		return false;
	if(::Save(f,IneffectiveMode)==false)
		return false;
	if(::Save(f,EffectiveLimitedMode)==false)
		return false;
	if(::Save(f,IneffectiveLimitedMode)==false)
		return false;
	if(::Save(f,ShowBackGround)==false)
		return false;
	if(::Save(f,ColorEffective)==false)
		return false;
	if(::Save(f,ColorEffectiveLimited)==false)
		return false;
	if(::Save(f,ColorIneffective)==false)
		return false;
	if(::Save(f,ColorIneffectiveLimited)==false)
		return false;
	if(::Save(f,SelectedLibID)==false)
		return false;
	if(::Save(f,ShowOnlyLibID)==false)
		return false;
	if(::Save(f,TransparentLevel)==false)
		return false;
	if(::Save(f,SelectedTransparentLevel)==false)
		return false;
	if(::Save(f,ActiveTransparentLevel)==false)
		return false;
	return true;
}
inline	bool	MaskingDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,NegColorMask)==false)
		return false;
	if(::Load(f,NegColorSelected)==false)
		return false;
	if(::Load(f,EffectiveMode)==false)
		return false;
	if(::Load(f,IneffectiveMode)==false)
		return false;
	if(::Load(f,EffectiveLimitedMode)==false)
		return false;
	if(::Load(f,IneffectiveLimitedMode)==false)
		return false;
	if(::Load(f,ShowBackGround)==false)
		return false;
	if(::Load(f,ColorEffective)==false)
		return false;
	if(::Load(f,ColorEffectiveLimited)==false)
		return false;
	if(::Load(f,ColorIneffective)==false)
		return false;
	if(::Load(f,ColorIneffectiveLimited)==false)
		return false;
	if(::Load(f,SelectedLibID)==false)
		return false;
	if(::Load(f,ShowOnlyLibID)==false)
		return false;
	if(::Load(f,TransparentLevel)==false)
		return false;
	if(::Load(f,SelectedTransparentLevel)==false)
		return false;
	if(::Load(f,ActiveTransparentLevel)==false)
		return false;
	return true;
}

class	CmdMaskingDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMaskingDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};


class	CmdMaskingDeleteItemPacket : public GUIDirectMessage
{
public:

	CmdMaskingDeleteItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdMaskingDeleteItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateMaskInSameColor : public GUIDirectMessage
{
public:
	int32	PickupL;
	int32	PickupH;
	AlgorithmLibraryListContainer	LimitedLib;
	bool	Effective;
	ColorLogic	PickupColor;
	int		MinPickupSize;
	int		MaxPickupSize;
	int		MinPickupDots;
	int		MaxPickupDots;
	int		Erosion;
	IntList	LayerList;
	bool	TestMode;

	CmdGenerateMaskInSameColor(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateMaskInSameColor(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMaskingDrawOnOffPacket : public GUIDirectMessage
{
public:
	bool	Effective			;
	bool	Ineffective			;
	bool	EffectiveLimited	;
	bool	IneffectiveLimited	;
	bool	CutLine				;
	bool	ShowBackGround		;
	bool	ShowOnlyLibID		;

	CmdMaskingDrawOnOffPacket(LayersBase *base)
		:GUIDirectMessage(base)		{	Effective=false;	Ineffective=false;	ShowOnlyLibID=false;	}
	CmdMaskingDrawOnOffPacket(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase)	{	Effective=false;	Ineffective=false;	ShowOnlyLibID=false;	}

	bool	OnlyEffective(void)		{	return (Effective==true  && Ineffective==false && EffectiveLimited==false && IneffectiveLimited==false && CutLine==false)?true:false;	}
	bool	OnlyIneffective(void)	{	return (Effective==false && Ineffective==true  && EffectiveLimited==false && IneffectiveLimited==false && CutLine==false)?true:false;	}
};

class	CmdMaskingDrawInfo: public GUIDirectMessage
{
public:
	bool	Effective;
	bool	Ineffective;
	bool	EffectiveLimited;
	bool	IneffectiveLimited;
	bool	CutLine;
	AlgorithmLibraryListContainer	LimitedLib;
	int		SelectedLibID;
	bool	ShowOnlyLibID;
	int32	TransparentLevel;
	IntList	Phases;

	CmdMaskingDrawInfo(LayersBase *base)
		:GUIDirectMessage(base)		{	Effective=false;	Ineffective=false;	ShowOnlyLibID=false;	}
	CmdMaskingDrawInfo(GUICmdPacketBase *gbase)
		:GUIDirectMessage(gbase)	{	Effective=false;	Ineffective=false;	ShowOnlyLibID=false;	}

	bool	OnlyEffective(void)		{	return (Effective==true  && Ineffective==false && EffectiveLimited==false && IneffectiveLimited==false && CutLine==false)?true:false;	}
	bool	OnlyIneffective(void)	{	return (Effective==false && Ineffective==true  && EffectiveLimited==false && IneffectiveLimited==false && CutLine==false)?true:false;	}
};

class	CmdPourAreaPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
	int		PickupRL,PickupRH;
	int		PickupGL,PickupGH;
	int		PickupBL,PickupBH;
	int		ExpandedDot;
	int		LocalX,LocalY;
	bool	Effective;
	bool	Exclusive;
	int		MinSize;
	int64	MinDot;
	int		OmitX1,OmitY1,OmitX2,OmitY2;
	int		NoisePinhole ;
	int		NoiseSmallDot;
	AlgorithmLibraryListContainer	LimitedLib;

	CmdPourAreaPacket(LayersBase *base):GUIDirectMessage(base){	MinDot-0;	MinSize=0;	}
	CmdPourAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupAreaPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
	int		PickupRL,PickupRH;
	int		PickupGL,PickupGH;
	int		PickupBL,PickupBH;
	int		ExpandedDot;
	bool	Effective;
	int		MinSize;
	AlgorithmLibraryListContainer	LimitedLib;
	int32	HoleMinArea		;
	int32	HoleErosionDot	;
	int		AreaX1,AreaY1,AreaX2,AreaY2;

	CmdPickupAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdPickupMaxAreaInAreaPacket : public GUIDirectMessage
{
public:
	IntList	LayerList;
	FlexArea	FieldArea;
	int		PickupRL,PickupRH;
	int		PickupGL,PickupGH;
	int		PickupBL,PickupBH;
	int		ExpandedDot;
	int		MinSize;
	int		MaskLibID;

	CmdPickupMaxAreaInAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdPickupMaxAreaInAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectMaskLimited : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	SelectedList;
	bool							AllMode;
	IntList							Layers;
	bool							IneffectiveMode;
	bool							EffectiveMode;
	bool							IneffectiveLimitedMode;
	bool							EffectiveLimitedMode;


	CmdSelectMaskLimited(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectMaskLimited(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempMaskingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempMaskingLibraryPacket(LayersBase *base):GUIDirectMessage(base){	Point=NULL;	}
	CmdCreateTempMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};

class	CmdLoadMaskingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool			Success;

	CmdLoadMaskingLibraryPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;		}
	CmdLoadMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};
class	CmdClearMaskingLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearMaskingLibraryPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;		}
	CmdClearMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};
class	CmdDeleteMaskingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteMaskingLibraryPacket (LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;		}
	CmdDeleteMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};
class	CmdInsertMaskingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMaskingLibraryPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;		}
	CmdInsertMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};
class	CmdUpdateMaskingLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMaskingLibraryPacket(LayersBase *base):GUIDirectMessage(base)			{	Point=NULL;		}
	CmdUpdateMaskingLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Point=NULL;		}
};

class	CmdGetMaskingLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetMaskingLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMaskingLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExpandMask : public GUIDirectMessage
{
public:
	int32	PixelCount;
	CmdExpandMask(LayersBase *base):GUIDirectMessage(base){}
	CmdExpandMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReplaceInclusiveMask: public GUIDirectMessage
{
public:
	CmdReplaceInclusiveMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReplaceInclusiveMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqLimitedLibMask : public GUIDirectMessage
{
public:
	IntList	LimitedLib;

	CmdReqLimitedLibMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLimitedLibMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqLimitedLibMaskInItem : public GUIDirectMessage
{
public:
	int		ItemID;
	AlgorithmLibraryListContainer	*SelAreaID;

	CmdReqLimitedLibMaskInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqLimitedLibMaskInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetLimitedLibMaskInItem : public GUIDirectMessage
{
public:
	int		ItemID;
	AlgorithmLibraryListContainer	*SelAreaID;

	CmdSetLimitedLibMaskInItem(LayersBase *base):GUIDirectMessage(base){}
	CmdSetLimitedLibMaskInItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqMaskCount : public GUIDirectMessage
{
public:
	int32	CountEffective;
	int32	CountNoEffective;
	CmdReqMaskCount(LayersBase *base):GUIDirectMessage(base)		{	CountEffective=CountNoEffective=0;	}
	CmdReqMaskCount(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	CountEffective=CountNoEffective=0;	}
};


class	CmdDrawOnlyItems : public GUIDirectMessage
{
public:
	IntList	LimitedLib;
	MaskingDrawAttr	*DrawAttr;
	QImage			*Image;
	int				movx;
	int				movy;
	double			ZoomRate;
	IntList			LibID;

	CmdDrawOnlyItems(LayersBase *base):GUIDirectMessage(base){}
	CmdDrawOnlyItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMaskingAreaInLibraryPacket : public GUIDirectMessage
{
public:
	int					LibID;
	PureFlexAreaListContainer	Areas;

	CmdGetMaskingAreaInLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMaskingAreaInLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMaskingMakeBackGround : public GUIDirectMessage
{
public:
	bool	MasterMode;

	CmdMaskingMakeBackGround(LayersBase *base):GUIDirectMessage(base){}
	CmdMaskingMakeBackGround(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdMaskingClearBackGround : public GUIDirectMessage
{
public:

	CmdMaskingClearBackGround(LayersBase *base):GUIDirectMessage(base){}
	CmdMaskingClearBackGround(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class UsedLimitedMask : public NPListSaveLoad<UsedLimitedMask>
{
public:
	int								Layer;
    bool							Effective;		// true=有効エリア
    AlgorithmLibraryListContainer	SelAreaID;		// 限定マスク	
	int								Count;
	bool							IncludedMode;

	UsedLimitedMask(void){	Effective=true;	Count=0;	IncludedMode=true;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	UsedLimitedMask	&operator=(const UsedLimitedMask &src);
};

class UsedLimitedMaskContainer : public NPListPackSaveLoad<UsedLimitedMask>
{
public:
	UsedLimitedMaskContainer(void){}

	virtual	UsedLimitedMask	*Create(void)	{	return new UsedLimitedMask();	}

	UsedLimitedMaskContainer	&operator+=(const UsedLimitedMaskContainer &src);
	UsedLimitedMaskContainer	&operator=(const UsedLimitedMaskContainer &src);
};

inline	UsedLimitedMask	&UsedLimitedMask::operator=(const UsedLimitedMask &src)
{
	Layer		=src.Layer		;
	Effective	=src.Effective	;	
	SelAreaID	=src.SelAreaID	;	
	Count		=src.Count		;
	IncludedMode=src.IncludedMode;
	return *this;
}

inline	bool	UsedLimitedMask::Save(QIODevice *f)
{
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,Effective)==false)
		return false;
	if(SelAreaID.Save(f)==false)
		return false;
	if(::Save(f,Count)==false)
		return false;
	if(::Save(f,IncludedMode)==false)
		return false;
	return true;
}

inline	bool	UsedLimitedMask::Load(QIODevice *f)
{
	if(::Load(f,Layer)==false)
		return false;
	if(::Load(f,Effective)==false)
		return false;
	if(SelAreaID.Load(f)==false)
		return false;
	if(::Load(f,Count)==false)
		return false;
	if(::Load(f,IncludedMode)==false)
		return false;
	return true;
}

inline	UsedLimitedMaskContainer	&UsedLimitedMaskContainer::operator+=(const UsedLimitedMaskContainer &src)
{
	for(UsedLimitedMask *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		UsedLimitedMask	*b=new UsedLimitedMask();
		*b=*a;
		AppendList(b);
	}
	return *this;
}

inline	UsedLimitedMaskContainer	&UsedLimitedMaskContainer::operator=(const UsedLimitedMaskContainer &src)
{
	RemoveAll();
	return operator+=(src);
}

class	CmdReqUsedLimitedMaskCount : public GUIDirectMessage
{
public:
	UsedLimitedMaskContainer	MaskContainer;

	CmdReqUsedLimitedMaskCount(LayersBase *base):GUIDirectMessage(base){}
	CmdReqUsedLimitedMaskCount(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdRemoveMaskItem : public GUIDirectMessage
{
public:
	int	ItemID;

	CmdRemoveMaskItem(LayersBase *base):GUIDirectMessage(base){}
	CmdRemoveMaskItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateMaskOnSelectedItemsEdge : public GUIDirectMessage
{
public:
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int								Expansion ;
    int								InsideDot ;
    int								OutsideDot;

	CmdGenerateMaskOnSelectedItemsEdge(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateMaskOnSelectedItemsEdge(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGeneratePatternEdgeOnSelected: public GUIDirectMessage
{
public:
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int								BoundaryDiff ;
    int								WidthDot ;

	CmdGeneratePatternEdgeOnSelected(LayersBase *base):GUIDirectMessage(base){}
	CmdGeneratePatternEdgeOnSelected(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetItemSelection: public GUIDirectMessage
{
public:
	bool	Effective;
	AlgorithmLibraryListContainer	LimitedLib;

	CmdSetItemSelection(LayersBase *base):GUIDirectMessage(base){}
	CmdSetItemSelection(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdGenerateMaskFromBackGround: public GUIDirectMessage
{
public:
	int		DiffBrightness;
	int		MinObjectDotCount;
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int								BoundaryWidth ;
	int								SearchDot;
	bool	CombineArea;

	CmdGenerateMaskFromBackGround(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateMaskFromBackGround(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif
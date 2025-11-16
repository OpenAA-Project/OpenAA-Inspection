#pragma once


#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>
#include <QIODevice>
#include "XDoubleClass.h"
#include "XFlexAreaImage.h"

#define	CounterVersion	1

class	CounterItem;
class	CounterRegulation;
class	CounterInPage;
class	CounterBase;
class	CounterLibrary;

class	CounterItem;
class	CounterInPage;
class	MatchingResultList;

//==========================================================================================

class	CounterDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ShowExecuteMap;
	bool	ShowItems;

	CounterDrawAttr(LayersBase *Base):ServiceForLayers(Base){	ShowItems=true;	}
	CounterDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	CounterDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	CounterDrawAttr	&operator=(CounterDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	CounterDrawAttr::CounterDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
	ShowItems=true;
}

inline	CounterDrawAttr	&CounterDrawAttr::operator=(CounterDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));

	ShowExecuteMap	=src.ShowExecuteMap;
	ShowItems		=src.ShowItems;
	return *this;
}

inline	bool	CounterDrawAttr::Save(QIODevice *f)
{
	if(AlgorithmDrawAttr::Save(f)==false)
		return false;
	if(::Save(f,ShowExecuteMap)==false)
		return false;
	if(::Save(f,ShowItems)==false)
		return false;
	return true;
}
inline	bool	CounterDrawAttr::Load(QIODevice *f)
{
	if(AlgorithmDrawAttr::Load(f)==false)
		return false;
	if(::Load(f,ShowExecuteMap)==false)
		return false;
	if(::Load(f,ShowItems)==false)
		return false;
	return true;
}

//========================================================================================
class	CounterThreshold : public AlgorithmThreshold
{
public:
	int			NoiseLevel;
	double		AdoptedRate;
	int			LineLength;
	int			RoughStep;
	double		FilterRate;
	int			OutMergin;	//ó÷äsåÎç∑ÉhÉbÉg
	int			OutlineSearchDot;

	CounterThreshold(CounterItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

};

class MatchingLineBase : public NPList<MatchingLineBase>
{
protected:
	WORD	PosX,PosY;
	WORD	LineLen;
	BYTE	*Data;
	BYTE	Layer;

	int32	A;
	int32	AA;
	double	AvrS;
	double	AASS;
	double	RLineLen;
public:
	MatchingLineBase(void);
	virtual	~MatchingLineBase(void);

	virtual	int	GetLineClass(void)	=0;

	virtual	double	Match(ImageBuffer *TBuff[],int dx,int dy)=0;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)=0;
	virtual	double	GetVar(ImageBuffer &Buff)	=0;
	int		GetLayer(void)	{	return Layer;	}
protected:
	void	Initial(void);

};

class MatchingLineV : public MatchingLineBase
{
public:
	MatchingLineV(void){}
	~MatchingLineV(void){}

	virtual	int	GetLineClass(void)	override	{	return 1;	}
	bool	Set(double cx, double cy ,double Len 
				,ImageBufferListContainer &SourcePattern);

	virtual	double	Match(ImageBuffer *TBuff[],int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(ImageBuffer &Buff)	override;
};

class MatchingLineH : public MatchingLineBase
{
public:
	MatchingLineH(void){}
	~MatchingLineH(void){}

	virtual	int	GetLineClass(void)	override	{	return 2;	}
	bool	Set(double cx, double cy ,double Len 
				,ImageBufferListContainer &SourcePattern);

	virtual	double	Match(ImageBuffer *TBuff[],int dx,int dy)	override;
	virtual	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy)override;
	virtual	double	GetVar(ImageBuffer &Buff)	override;
};

class MatchingSomePoints
{
public:
	int		PointCount;
	BYTE	*Data;
	QPoint	*PointDim;
	int		PointInsideCount;
	QPoint	*PointInsideDim;
	int		PointInsideCountD;
	QPoint	*PointInsideDimD;
	int		PointOutsideCountD;
	QPoint	*PointOutsideDimD;
	int		Layer;
	int32	A;
	int32	AA;
	double	AvrS;
	double	AASS;
	int		MinX,MinY,MaxX,MaxY;
	double	RPointCount;
public:
	MatchingSomePoints(void);
	virtual	~MatchingSomePoints(void);

	void	Allocate(ImageBufferListContainer &SourcePattern
					,FlexArea &PickedAreaInPattern
					,int FocusLevel			//0 - 9
					,int OutMergin=5);

	double	Match(ImageBuffer *TBuff[],int dx,int dy);
	void	Draw(QPainter &Pnt,double ZoomRate,int movx,int movy);
	double	GetVar(ImageBuffer &Buff);
	int		GetLayer(void)	{	return Layer;	}
	void	CalcFocusLevel(ImageBufferListContainer &SourcePattern
						   ,FlexArea &PickedAreaInPattern,int FocusLevel);
};

#pragma	pack(push)
#pragma	pack(1)
struct ShiftXY
{
	short	X,Y;
	short	Dx,Dy;
	float	D;
};
#pragma	pack(pop)
const int	MaxShiftXYDimCount=1000000;

enum MatchingMethod
{
	_AveragePower	=0
	,_MinRate		=1
};

class RotatedMatchingPattern : public NPList<RotatedMatchingPattern>
{
public:
	CounterItem						*Parent;
	int		WNumb,HNumb;
	NPListPack<MatchingLineBase>	MatachingLines[3][3];
	ImageBufferListContainer		SourcePattern;
	FlexArea						PickedAreaInPattern;
	int								PickedAreaInPatternXLen;
	int								PickedAreaInPatternYLen;
	FlexArea						PickedAreaInPatternShrinked;
	FlexArea						PickedAreaInPatternFat;
	FlexArea						PickedAreaInPatternFatMask;
	FlexAreaImageListCoeff			EdgeArea;
	int								EdgeLayer;
	MatchingSomePoints				RoughPoints;
	double							Angle;
	int								ExeOffsetX,ExeOffsetY;
	struct ShiftXY					*ShiftXYDim;
	int								ShiftXYDimCount;
	int								SingleNumb;
	int								DualNumb;
	bool							EnabledMatching;
	MatchingLineBase				*SinglePointer;
	MatchingLineBase				*SecondPointer;

	RotatedMatchingPattern(CounterItem *p);
	~RotatedMatchingPattern(void);

	void	MakeInitial(CounterItem *Item
						,FlexArea &OriginalPart
						,FlexArea &OriginalPickedAreaInPattern
						,ImageBufferListContainer &OriginalImage);

	void	MakeShiftDim(int XLen,int YLen
						,ImagePointerContainer &ImageList
						,FlexArea &PickedArea);

	void	GetSearchMax(ImagePointerContainer &ImageList
						,FlexArea &PickedArea
						,struct ShiftXY	*tShiftXYDim
						,int tShiftXYDimCount);
	double	GetSearchMaxDetail(ImagePointerContainer &ImageList
						,FlexArea &PickedArea
						,int LocalResultCount
						,MatchingResultList	LocalResult[100]
						,int PosX ,int PosY
						,int &Dx ,int &Dy);
	void	Draw(QImage &IData
				,int MovX ,int MovY ,double ZoomRate
				,int PosX,int PosY
				,const QColor &Col);
	void	MakeImage(int width ,int height ,double ZoomRate
					  ,QImage &ItemImage);

	void	MatchSingle(int XLen,int YLen
						,ImageBuffer *TBuff[],int LayerNumb
						,FlexArea &PickedArea);
	void	MatchDual(int XLen,int YLen
						,ImageBuffer *TBuff[],int LayerNumb
						,FlexArea &PickedArea);

	double	Match(RotatedMatchingPattern *src);

	double	Match			(ImageBuffer *TBuff[] ,int dx,int dy
							 ,int SearchDot ,MatchingMethod Method);
	double	MatchByEdge		(ImageBuffer *TBuff[] ,int &dx,int &dy
							 ,int SearchDot);
	int64	GetCrossCount(FlexArea &F,int dx,int dy);
	bool	GetCrossRoughPoints(int dx,int dy ,BYTE **ExecuteMap ,int XLen ,int YLen);
	bool	GetCrossDetailPoints(int dx,int dy ,BYTE **ExecuteMap ,int XLen ,int YLen);
	void	CalcFocusLevel(void);
private:
	double	MatchRough		(ImageBuffer *TBuff[] ,int dx,int dy ,int Sep);
	double	MatchRoughSuper	(ImageBuffer *TBuff[] ,int dx,int dy ,int Sep);
};

inline	bool	RotatedMatchingPattern::GetCrossRoughPoints(int dx,int dy ,BYTE **ExecuteMap ,int XLen ,int YLen)
{
	for(int i=0;i<RoughPoints.PointInsideCount;i++){
		int	hx=RoughPoints.PointInsideDim[i].x()+dx;
		int	hy=RoughPoints.PointInsideDim[i].y()+dy;
		if(0<=hx && hx<XLen && 0<=hy && hy<YLen){
			if(GetBmpBit(ExecuteMap,hx,hy)==0){
				return false;
			}
		}
		else{
			return false;
		}
	}
	return true;
}


class MatchingResultList
{
public:
	struct ShiftXY	*XY;
	int			ResultPosX,ResultPosY;
	int			RotatedIndex;
	double		MatchingResult;
	int			CCount;
	int			IndependentPixels;
	RotatedMatchingPattern	*Pointer;

	MatchingResultList(void){}
	virtual	~MatchingResultList(void){}
};

class	CounterItem : public AlgorithmItemPITemplate<CounterInPage,CounterBase>
{
public:
	ImageBufferListContainer			SourcePattern;
	ImageBufferListContainer			BackGroundPattern;
	FlexArea							PickedAreaInPattern;

	NPListPack<RotatedMatchingPattern>	RotatedContainer;

	MatchingResultList	*MatchingResultDim;
	int		ResultCount;
	int		MaxMatchingResultCount;

	RotatedMatchingPattern	**RoughRotatedContainerTable;
	MatchingResultList		*RoughResult;
	int						RoughCount;
	bool					TimeOut;
	QMutex					HaltProcess;

public:
	CounterItem(void);
	virtual	~CounterItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new CounterItem();	}
	virtual	bool		Save(QIODevice *f)					override;
	virtual	bool		Load(QIODevice *f,LayersBase *LBase)override;
	const	CounterThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const CounterThreshold *)GetThresholdBaseReadable(base);	}
	CounterThreshold			*GetThresholdW(LayersBase *base=NULL){	return (CounterThreshold *)GetThresholdBaseWritable(base);			}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new CounterThreshold(this);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	double	MakeImage(int width ,int height 
					  ,QImage &ItemImage
					  ,QImage &ItemImageWithMask
					  ,QImage &ItemBackGround);

	void	MakeInitial(void);
	double	GetRotatedZoomRate(int width ,int height);
	void	CalcFocusLevel(void);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
};

class   CounterInPage : public AlgorithmInPagePITemplate<CounterItem,CounterBase>
{
	ConstMapBufferListContainer MaskMapInPage;
public:
	BYTE	**ExecuteMap;
	BYTE	**TempMap;
	int		XLen;
	int		YLen;
	AlgorithmInPageRoot	*MaskPage;
	int		MostPixelsInBrightness[3];
	bool	FilterON;
	DWORD	NowMilisec1;
	DWORD	NowMilisec2;
	QMutex	MutexExecutedPickedFPack;
	bool	ChangedMask;
public:
	PureFlexAreaListContainer ExecutedPickedFPack;
public:
	bool	RegistInFlowMode;

	CounterInPage(AlgorithmBase *parent);
	~CounterInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	void	UndoAppendManualItem(QIODevice *f);
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

private:
	void	SetBackGround(void);
	void	ReleaseBackGround(void);

	void	MakeActiveBinarize(int x1,int y1,int x2,int y2
								,BYTE **ExecuteMap);
};

class	CounterBase : public AlgorithmBase
{
public:
	QColor	ColorArea;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorArea;
	QColor	NegColorSelected;
	QColor	TextColor;
	int32	MaxMatchingResultCount;
	int32	MinAreaPiece;
	int32	MaxAreaPiece;
	double	AdoptPixelsRate;
	double	MaxPickedPixelsRate;
	double	AngleStep;
	double	CrossRateInPickedArea;
	double	RotationalSame;
	int32	SkipFlat;
	int32	CountIndexLine;
	int32	FocusLevel;
	double	AdoptedRate;
	bool	OutsideCalc;
	double	NonOverlappedRate;
	bool	ShowDebugMode;
	int32	SearchSep;
	bool	ShowMatchingRate;

	QColor	ItemColor0;
	QColor	ItemColor1;
	QColor	ItemColor2;
	QColor	ItemColor3;
	QColor	ItemColor4;
	QColor	ItemColor5;
	QColor	ItemColor6;
	QColor	ItemColor7;

	CounterBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new CounterInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)			override{	return QString("Counter");					}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigCounter.dat");		}

	const QColor	GetItemColor(int n);
};

//==================================================================================

class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemImage : public GUIDirectMessage
{
public:
	int		Width,Height;
	QImage	ItemImage;
	QImage	ItemBackGround;
	QImage	ItemImageWithMask;
	DoubleList	Angles;
	QList<QImage>	RotatedImages;

	CmdReqItemImage(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqResultCount : public GUIDirectMessage
{
public:
	int		Count;
	bool	TimeOut;
	CmdReqResultCount(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqAdoptedRate : public GUIDirectMessage
{
public:
	double	AdoptedRate;

	CmdReqAdoptedRate(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetAdoptedRate : public GUIDirectMessage
{
public:
	double	AdoptedRate;

	CmdSetAdoptedRate(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetBackGround : public GUIDirectMessage
{
public:
	bool	SetBackGround;
	CmdSetBackGround(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdReqItemArea: public GUIDirectMessage
{
public:
	PureFlexAreaListContainer	*Areas;

	CmdReqItemArea(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetFilterMode: public GUIDirectMessage
{
public:
	bool	FilterON;

	CmdSetFilterMode(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetFocusLevel: public GUIDirectMessage
{
public:
	CmdSetFocusLevel(LayersBase *Base):GUIDirectMessage(Base){}
};




//=======================================================

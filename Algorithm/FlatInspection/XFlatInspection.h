#pragma once

#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XFlatInspectionLibrary.h"
#include <QColor>
#include <QPainter>
#include <QByteArray>

#define	FlatInspectionVersion	2

class	FlatInspectionItem;
class	FlatInspectionRegulation;
class	FlatInspectionInPage;
class	FlatInspectionBase;
class	FlatInspectionLibrary;

class	FlatInspectionItem;
class	FlatInspectionInPage;



//========================================================================================
class	FlatInspectionThreshold : public AlgorithmThreshold
{
public:
	struct MThreshold
	{
		DWORD	OrgOKDot;			//ＯＫドット数
		DWORD	OrgOKLength;		//ＯＫ距離

		DWORD	OKDot;			//ＯＫドット数
		DWORD	OKLength;		//ＯＫ距離

		short	RThrOffsetL;	//しきい値への直接加算値	(-100～100)
		short	RThrOffsetH;
		short	GThrOffsetL;
		short	GThrOffsetH;
		short	BThrOffsetL;
		short	BThrOffsetH;

		MThreshold(void);

		void	CopyFrom(const FlatInspectionThreshold::MThreshold &src);
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);

		void	FromLibrary(FlatInspectionLibrary::MLibThreshold *src)	;
		void	ToLibrary  (FlatInspectionLibrary::MLibThreshold *Dest);

		void	SetToOrigin(void);

	}Broad,Narrow;

	short	SpaceToOutline;

	DWORD	OrgMultiSpotDot;
	DWORD	OrgMultiSpotCount;
	DWORD	OrgBackGroundOKDot;			//ＯＫドット数
	DWORD	OrgBackGroundOKLength;		//ＯＫ距離
	bool	OrgUseBackGround;	

	DWORD	MultiSpotDot;	//単多点
	DWORD	MultiSpotCount;
	DWORD	MultiSpotDotGathered;	//密集多点
	DWORD	MultiSpotCountGathered;
	DWORD	MultiSpotLengthGathered;
	DWORD	BackGroundOKDot;	
	DWORD	BackGroundOKLength;
	bool	UseBackGround;

	WORD	AdjustBlack;		//輝度補正の下限幅
    WORD	AdjustWhite;		//輝度補正の上限幅
	WORD	AreaSearchX;		//Ｘ方向領域探索ドット数
	WORD	AreaSearchY;		//Ｙ方向領域探索ドット数
	WORD	SelfSearch;			//自己探索ドット数
	bool	EnableInspection;
	WORD	MaxAreaSearch;	//最大領域探索ドット数
    WORD	MaxSelfSearch;	//最大自己探索ドット数


	bool	RedCheckMode;
	WORD	RedHighRate;	//G,Bに比べてRの輝度値の増値割合(%)
	BYTE	RedMinBrightness;
	BYTE	RedGBMerginRate;
	BYTE	RedGBMerginOffset;
	BYTE	RedShrink;
	DWORD	RedOKDot;

	bool	VariationMode;
	float	VariationRL,VariationRH;	//R-OKバラツキ偏差値
	float	VariationGL,VariationGH;	//G-OKバラツキ偏差値
	float	VariationBL,VariationBH;	//B-OKバラツキ偏差値
	DWORD	VariationAdaptMinSize;		//最小適用領域サイズ
	float	VariationMultiplyMaster;	//マスター画像、バラツキ画像からの偏差しきい値計算時の係数
	bool	VariationDifMaster;			//マスター画像の差分をバラつき偏差で処理
	bool	VariationAndLogic;			//他の検査してNGになった部分だけをバラつき判定する
	float	VariationSubMasterVari;		//マスター画像のバラつき係数を引き算する係数

	bool	LineMode;
	WORD	LineOKMinLength;
	WORD	LineMaxWidth;
	WORD	LineMinDensityPercent;
	WORD	LineMinCluster;		//線の最小塊面積

	FlatInspectionThreshold(FlatInspectionItem *parent);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	CopyFrom(const AlgorithmThreshold &src,IntList &EdittedMemberID)	override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
			void	SetToOrigin(void);

	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;

	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

enum ThresholdMember
{
	 ID_BroadOKDot			=7	//ＯＫドット数
	,ID_BroadOKLength		=8	//ＯＫ距離
	,ID_BroadRThrOffsetL	=9	//しきい値への直接加算値	(-100～100)
	,ID_BroadRThrOffsetH	=10
	,ID_BroadGThrOffsetL	=11
	,ID_BroadGThrOffsetH	=12
	,ID_BroadBThrOffsetL	=13
	,ID_BroadBThrOffsetH	=14


	,ID_NarrowOKDot			=27	//ＯＫドット数
	,ID_NarrowOKLength		=28	//ＯＫ距離
	,ID_NarrowRThrOffsetL	=29	//しきい値への直接加算値	(-100～100)
	,ID_NarrowRThrOffsetH	=30
	,ID_NarrowGThrOffsetL	=31
	,ID_NarrowGThrOffsetH	=32
	,ID_NarrowBThrOffsetL	=33
	,ID_NarrowBThrOffsetH	=34

	,ID_SpaceToOutline		=40

	,ID_MultiSpotDot			=51
	,ID_MultiSpotCount			=52
	,ID_MultiSpotDotGathered	=53
	,ID_MultiSpotCountGathered	=54
	,ID_MultiSpotLengthGathered	=55
	,ID_BackGroundOKDot			=56	//ＯＫドット数
	,ID_BackGroundOKLength		=57	//ＯＫ距離
	,ID_UseBackGround			=58

	,ID_AdjustBlack			=61	//輝度補正の下限幅
	,ID_AdjustWhite			=62	//輝度補正の上限幅
	,ID_AreaSearchX			=64
	,ID_AreaSearchY			=65
	,ID_SelfSearch			=66	//自己探索ドット数
	,ID_MaxAreaSearch		=69
	,ID_MaxSelfSearch		=70

	,ID_AddedBrightness			=91	//-10 ～ +10
	,ID_AddedOffset				=92	//-10 ～ +10
	,ID_AddedShift				=93	//-10 ～ +10

	,ID_RedCheckMode		=101
	,ID_RedHighRate			=102	//G,Bに比べてRの輝度値の増値割合(%)
	,ID_RedMinBrightness	=103
	,ID_RedGBMerginRate		=104
	,ID_RedGBMerginOffset	=105
	,ID_RedOKDot			=106
	,ID_RedShrink			=107


	,ID_VariationMode			=161
	,ID_VariationRL				=162
	,ID_VariationRH				=163
	,ID_VariationGL				=164
	,ID_VariationGH				=165
	,ID_VariationBL				=166
	,ID_VariationBH				=167
	,ID_VariationAdaptMinSize	=168
	,ID_VariationMultiplyMaster	=169
	,ID_VariationDifMaster		=170
	,ID_VariationAndLogic		=171
	,ID_VariationSubMasterVari	=172

	,ID_LineMode				=191
	,ID_LineOKMinLength			=192
	,ID_LineMaxWidth			=193
	,ID_LineMinDensityPercent	=194
	,ID_LineMinCluster			=195
};


class	FlatInspectionResultPosList : public ResultPosList
{
public:
	bool	NGLine;
	int32	X1,Y1,X2,Y2;		

	FlatInspectionResultPosList(void):NGLine(false){}
	FlatInspectionResultPosList(ResultPosList &src) : ResultPosList(src),NGLine(false){}
	FlatInspectionResultPosList(int px ,int py) : ResultPosList(px,py),NGLine(false){}
	FlatInspectionResultPosList(int px ,int py ,int rx ,int ry):ResultPosList(px ,py ,rx ,ry),NGLine(false){}

	virtual	void	DrawResult(ResultInItemRoot *parent ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate 
							,int MinimumRadius,QRgb Col,int CircleWidth,bool DrawBlueNGMark)	override;

	virtual	bool    Load(QIODevice *f)	override;
    virtual	bool    Save(QIODevice *f)	override;
};

class	FlatInspectionResultInItemPI : public ResultInItemPI
{
public:
	FlatInspectionResultInItemPI(void){}

	virtual	ResultPosList	*CreateResultPosList(void)	{	return new FlatInspectionResultPosList();	}
};


struct SearchParam
{
	int		Dx,Dy;
	double	E;
	double	Coef;
	int64	D;
};


class	FlatInspectionItem : public AlgorithmItemPITemplate<FlatInspectionInPage,FlatInspectionBase>
{
	//BYTE	**Map;
	//BYTE	**TmpMap;
	//int		MapByte;
	//int		MapXLen;
	//int		MapYLen;
public:
	enum FlatInspectionType
	{
		_FIType_InspectionArea
		,_FIType_MasterArea
		,_FIType_Window
		,_FIType_SpecialShape
	}FIT_Type;

	FlexArea	MasterArea;		//FIT_Type==_FIType_MasterArea or _FIType_Window
	FlexArea	InsideArea;
	FlexArea	OutsideArea;

	FlexArea	MasterAreaLeftTop;			//FIT_Type==_FIType_MasterArea or _FIType_Window
	FlexArea	InsideAreaLeftTop;
	FlexArea	OutsideAreaLeftTop;
	FlexArea	MasterAreaRightTop;			//FIT_Type==_FIType_MasterArea or _FIType_Window
	FlexArea	InsideAreaRightTop;
	FlexArea	OutsideAreaRightTop;
	FlexArea	MasterAreaLeftBottom;		//FIT_Type==_FIType_MasterArea or _FIType_Window
	FlexArea	InsideAreaLeftBottom;
	FlexArea	OutsideAreaLeftBottom;
	FlexArea	MasterAreaRightBottom;		//FIT_Type==_FIType_MasterArea or _FIType_Window
	FlexArea	InsideAreaRightBottom;
	FlexArea	OutsideAreaRightBottom;

	FlexArea	SpecialArea;
	XYClassContainer	DarkerDots ;
	XYClassContainer	LighterDots;
	XYClassContainer	RoughDarkerDots ;
	XYClassContainer	RoughLighterDots;

	int		ResultDx			,ResultDy				;	//For _FIType_MasterArea
	int		ResultDxLeftTop		,ResultDyLeftTop		;	//For _FIType_MasterArea
	int		ResultDxRightTop	,ResultDyRightTop		;	//For _FIType_MasterArea
	int		ResultDxLeftBottom	,ResultDyLeftBottom		;	//For _FIType_MasterArea
	int		ResultDxRightBottom	,ResultDyRightBottom	;	//For _FIType_MasterArea

	struct SearchParam	*Dim;
	int		DimCount;

	double	ResultExpansion;
	IntList		AverageMaster;
	IntList		AverageTarget;

	int	MasterY1;
	int	MasterY2;
	int	MasterMinX;
	int	MasterMaxX;
	int	ResultY1;
	int	ResultY2;
	int	ResultMinX;
	int	ResultMaxX;

	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;
	WORD	CenterTargetBrightR;
	WORD	CenterTargetBrightG;
	WORD	CenterTargetBrightB;

	BYTE	**NGMapB;	
	BYTE	**NGMapN;
	BYTE	**NGMapRed;
	int		NGMapXByte	;
	int		NGMapXLen	;
	int		NGMapYLen	;
	int		NGMapOffsetX;
	int		NGMapOffsetY;

	IntList		BinarizedThresholdList;

	FlatInspectionItem(void);
	~FlatInspectionItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new FlatInspectionItem();	}
	virtual	int32		GetItemClassType(void)	override	{		return 0;		}

	bool    Save(QIODevice *file)					override;
    bool    Load(QIODevice *file,LayersBase *LBase)	override;

	const	FlatInspectionThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const FlatInspectionThreshold *)GetThresholdBaseReadable(base);	}
	FlatInspectionThreshold			*GetThresholdW(LayersBase *base=NULL){	return (FlatInspectionThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new FlatInspectionThreshold(this);	}
	
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	MakeMaskArea(void);
	void	SearchMax(int mx ,int my ,int &Dx ,int &Dy);
	void	MakeWindow(int mx ,int my);
	void	AddDarkLightDot(FlexArea &ZoneArea);
	void	SearchByDot(int mx ,int my ,int &Dx ,int &Dy,double &Expansion);
	void	CopyFrom(FlatInspectionItem *src);

	WORD	CalcCenterBright(ImageBuffer &IBuff ,int mx ,int my ,float &LVar ,float &HVar);
	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData);

private:
	int64	CalcSum(ImageBuffer *Image,int dx,int dy,FlexArea &InsideArea);
	double	CalcCoef(ImageBuffer *Image ,int SelfSearch,int mx ,int my ,double E);
	double	CalcCoefRough(ImageBuffer *Image ,int SelfSearch,int mx ,int my ,double E);
	double	CalcAverage(ImageBuffer *Image ,int mx ,int my ,double E);
	void	MakeRoughDots(void);

	ExeResult	ExecuteProcessingMasterArea		(int ExeID ,int ThreadNo,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingSpecialShape	(int ExeID ,int ThreadNo,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingInspectionArea(int ExeID ,int ThreadNo,ResultInItemRoot *Res);

	void	CopyThresholdOnly(FlatInspectionItem &src,IntList &EdittedMemberID);

	void	HandleNGMapToResult(ResultInItemRoot *Res
								,int OffsetX ,int OffsetY);
	void	HandleMultiSpotNGMapToResult(const	FlatInspectionThreshold	*RThr
								,ResultPosListContainer	&NowList
								,PureFlexAreaListContainer &FPack
								,int OffsetX ,int OffsetY);
	void	GetDetectRedRange(BYTE r,BYTE g,BYTE b
							,short &RedRL,short &RedRH
							,short &RedGL,short &RedGH
							,short &RedBL,short &RedBH);
	int		ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, FlexArea &MapArea
								, int OffsetX ,int OffsetY);
	int		ExecuteProcessingRed(ResultInItemRoot* Res
								, ImageBuffer *ImageTargetList[]
								, int OffsetX ,int OffsetY);
	int		ExecuteProcessingPickLine(ResultInItemRoot *Res
													,BYTE **Map
													,int mx,int my);
};

class   FlatInspectionInPage : public AlgorithmInPagePITemplate<FlatInspectionItem,FlatInspectionBase>
{
public:
	BYTE	**MaskMap;
	int		MaskMapXByte;
	int		MaskMapYLen;
	int	MasterY1,TargetY1;
	int	MasterY2,TargetY2;
	int	MasterX1,TargetX1;
	int	MasterX2,TargetX2;

	FlatInspectionInPage(AlgorithmBase *parent);
	~FlatInspectionInPage(void);

	//virtual	FlatInspectionItem	*tCreateItem(int ItemClassType=0);
	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	
	void	UndoSetIndependentItemDataCommand(QIODevice *f);

	virtual	ResultInItemRoot	*CreateResult(void)	override	{	return new FlatInspectionResultInItemPI();	}
private:

};

class	FlatInspectionBase : public AlgorithmBase
{
public:
	QColor	ColorArea		;
	QColor	ColorSelected	;
	QColor	ColorActive		;
	int32	TransparentLevel;
	QColor	NegColorArea	;
	QColor	NegColorSelected;
	double	SearchDot4SpecialArea;
	double	ExpansionRange;
	int32	MaxNGCountForMultiSpot;
	double	DeviationParam1;
	double	DeviationParam2;

	FlatInspectionBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new FlatInspectionInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;	
	virtual	QString	GetDataText(void)	override{	return QString("FlatInspection");					}
	QString	GetDefaultFileName(void)	override{	return QString("ConfigFlatInspection.dat");		}

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command ,void *reqData)		override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	QString	GetNameByCurrentLanguage(void)	override;
};
//==================================================================================
//==========================================================================================

class	FlatInspectionDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	FlatInspectionItem::FlatInspectionType	FIT_Type;
	bool	ShowMaskMap;


	FlatInspectionDrawAttr(LayersBase *Base):ServiceForLayers(Base){}
	FlatInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol);
	FlatInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel);

	void	Initial(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	FlatInspectionDrawAttr::FlatInspectionDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol)
:AlgorithmDrawAttr(ncol ,196
				 , scol ,196
				 , acol ,196),ServiceForLayers(Base)
{
}

inline	FlatInspectionDrawAttr::FlatInspectionDrawAttr(LayersBase *Base
				, QColor ncol ,int ntranparentLevel
				, QColor scol ,int stranparentLevel
				, QColor acol ,int atranparentLevel)
:AlgorithmDrawAttr(ncol ,ntranparentLevel
				, scol ,stranparentLevel
				, acol ,atranparentLevel),ServiceForLayers(Base)
{
}

inline	bool	FlatInspectionDrawAttr::Save(QIODevice *f)
{
	int	d=(int)FIT_Type;
	if(::Save(f,d			)==false)	return false;
	if(::Save(f,ShowMaskMap	)==false)	return false;
	return true;
}

inline	bool	FlatInspectionDrawAttr::Load(QIODevice *f)
{
	int	d;
	if(::Load(f,d)==false)	return false;
	FIT_Type	=(FlatInspectionItem::FlatInspectionType)d;
	if(::Load(f,ShowMaskMap	)==false)	return false;
	return true;
}

//==========================================================================================


class	CmdAddAreaManual : public GUIDirectMessage
{
public:
	FlexArea	Area;

	CmdAddAreaManual(LayersBase *Base):GUIDirectMessage(Base){}
};

class	CmdSetFlatInspection : public GUIDirectMessage
{
public:
	double		OKAngleL;
	double		OKAngleH;

	CmdSetFlatInspection(LayersBase *Base):GUIDirectMessage(Base){}
};

//===================================================================================

class	FlatInspectionHistogramListReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		FlatInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	FlatInspectionHistogramListReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FlatInspectionHistogramListSend
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		FlatInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;
	int		ListMasterR[256];
	int		ListMasterG[256];
	int		ListMasterB[256];
	int		ListTargetR[256];
	int		ListTargetG[256];
	int		ListTargetB[256];
	WORD	CenterBrightR;
	WORD	CenterBrightG;
	WORD	CenterBrightB;
	WORD	CenterTargetBrightR;
	WORD	CenterTargetBrightG;
	WORD	CenterTargetBrightB;

	FlatInspectionHistogramListSend(void);

	void	ConstructList(FlatInspectionHistogramListReq *reqPacket,FlatInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FlatInspectionThresholdReq
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		FlatInspectionItemID;
	bool	Mastered;
	int32	Dx,Dy;

	FlatInspectionThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FlatInspectionThresholdSend
{
public:
	struct ThresholdStruct
	{
		int32	GlobalPage;
		int32	Layer;
		int		FlatInspectionItemID;
		bool	Mastered;
		int32	Dx,Dy;
		WORD	CenterBrightR;
		WORD	CenterTargetBrightR;

		WORD	CenterBrightG;
		WORD	CenterTargetBrightG;

		WORD	CenterBrightB;
		WORD	CenterTargetBrightB;

		float	TargetSDRL,TargetSDRH;
		float	TargetSDGL,TargetSDGH;
		float	TargetSDBL,TargetSDBH;

		int		OrgOKDotB;
		int		OrgOKDotN;

	}ThresholdValues;

	FlatInspectionThresholdSend(void);

	void	ConstructList(FlatInspectionThresholdReq *reqPacket,FlatInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	FlatInspectionReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		FlatInspectionItemID;	
	FlatInspectionItem	Threshold;

	FlatInspectionReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	FlatInspectionSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	int		NGDot;
	double	NGLength;
	int		ResultMoveDx;
	int		ResultMoveDy;
	int		CurrentRotationPatternNo;
	int		Error;


	float	DeviationResultR;
	float	DeviationResultG;
	float	DeviationResultB;

	FlatInspectionSendTryThreshold(void);
	FlatInspectionSendTryThreshold(const FlatInspectionSendTryThreshold &src);
	~FlatInspectionSendTryThreshold(void);

	FlatInspectionSendTryThreshold &operator=(const FlatInspectionSendTryThreshold &src);
	void	ConstructList(FlatInspectionReqTryThreshold *reqPacket,FlatInspectionBase *Base);
	void	Calc(FlatInspectionItem *Target,FlatInspectionItem *Src,FlatInspectionBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===================================================================================

#define	SetIndependentItemDataCommand_OnlyOne			1
#define	SetIndependentItemDataCommand_All				2
#define	FlatInspectionHistogramListReqCommand			3
#define	FlatInspectionHistogramListSendCommand			4
#define	FlatInspectionReqThresholdReqCommand			5
#define	FlatInspectionReqThresholdSendCommand			6
#define	FlatInspectionReqTryThresholdCommand			7
#define	FlatInspectionSendTryThresholdCommand			8

//===================================================================================

class	CmdGetFlatInspectionLibraryListPacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetFlatInspectionLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetFlatInspectionLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetFlatInspectionLibraryNamePacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryListContainer	AList;
	CmdGetFlatInspectionLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetFlatInspectionLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateTempFlatInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdCreateTempFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearFlatInspectionLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdInsertFlatInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateFlatInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadFlatInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;
	CmdLoadFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteFlatInspectionLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibrary	*Point;
	CmdDeleteFlatInspectionLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteFlatInspectionLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetFlatInspectionLibName : public GUIDirectMessage
{
public:
	int		LibID;
	QString	LibName;
	CmdGetFlatInspectionLibName(LayersBase *base):GUIDirectMessage(base){}
	CmdGetFlatInspectionLibName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
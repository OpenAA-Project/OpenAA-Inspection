/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\MeasureLineMove\XMeasureLineMove.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XMEASULELINEMOVE_H)
#define	XMEASULELINEMOVE_H

#include <QTcpServer>
#include <QTcpSocket>
#include "XDataInLayer.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralFunc.h"
#include "XColorSpace.h"
#include "XVector.h"
#include "XFlexAreaImage.h"
#include "XMeasureCommon.h"
#include "XMeasureLineMoveLibrary.h"

#define	MeasureLineMoveVersion				1

#define	Hist_MeasureLineMove_LineShift		1
#define	Hist_MeasureLineMove_Distance		2

#define	ResultMeasureLineMoveOnItemType		102
#define	MeasureLineMove_ItemClass_Line		1
#define	MeasureLineMove_ItemClass_RxLine	5
#define	MeasureLineMove_ItemClass_CornerR	2
#define	MeasureLineMove_ItemClass_Mark		4
#define	MeasureLineMove_ItemClass_Distance	3

class	MeasureLineMoveItem;
class	MeasureLineMoveInPage;
class	MeasureLineMoveThreshold;
class	LineMoveReqTryThreshold ;
class	LineMoveSendTryThreshold;

class	LineMoveResultPosList : public ResultPosList
{
	AlgorithmItemRoot	*AItem;
public:
	LineMoveResultPosList(AlgorithmItemRoot	*item)
		:ResultPosList(),AItem(item){}
	LineMoveResultPosList(AlgorithmItemRoot	*item,int px ,int py) 
		: ResultPosList(px,py),AItem(item){}
	LineMoveResultPosList(AlgorithmItemRoot	*item,int px ,int py ,int rx ,int ry)
		:ResultPosList(px ,py ,rx ,ry),AItem(item){}

	virtual	void	GetExtraData(QByteArray &EData)	override;
};

#pragma	pack(push,1)
struct ResultDistanceForExtraData
{
	int32	Cx1,Cy1;			//１側端線の中心座標
	int32	Sx1,Sy1;
	int32	Cx2,Cy2;			//２側端線の中心座標
	int32	Sx2,Sy2;
	int32	DistanceX1,DistanceY1;
	int32	DistanceX2,DistanceY2;
	int32	TargetImageX1,TargetImageY1;
	double	TargetImageZoomRate;
	int32	TargetImageSide1X1,TargetImageSide1Y1;
	double	TargetImageSide1ZoomRate;
	int32	TargetImageSide2X1,TargetImageSide2Y1;
	double	TargetImageSide2ZoomRate;
	double	DistanceThresholdM;
	double	DistanceThresholdP;
	double	DistanceThresholdMMM;
	double	DistanceThresholdPMM;
	double	ResultDistance;
	double	ResultDistanceMM;
};
#pragma	pack(pop)

class	ResultLineMoveInPagePI : public ResultInPagePI
{
public:
	ResultLineMoveInPagePI(ResultBasePhase *pPhaseParent,DataInPage *pPage):ResultInPagePI(pPhaseParent,pPage){}

	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount) override;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f,int &WrittenNGCount)override;
};

class	ResultLineMoveBaseForAlgorithmPI : public ResultBaseForAlgorithmPI
{
public:
	ResultLineMoveBaseForAlgorithmPI(LogicDLL *parent):ResultBaseForAlgorithmPI(parent){}

	ResultInPageRoot	*CreatePage(int phase ,int page) override
	{	
		if(GetLayersBase()->GetPageDataPhase(phase)!=NULL){
			return new ResultLineMoveInPagePI(GetPageDataPhase(phase),GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page));	
		}
	return NULL;
	}
};


//========================================================================================================


class	MeasureLineMoveThreshold : public AlgorithmThreshold
{
public:
	int			SearchDot;
	double		ThresholdM;
	double		ThresholdP;
	int			EdgeWidth;
	bool		PrevailRight;
	bool		PrevailLeft;
	int			UsageLayer;
	bool		ModeToSetInInitial;
	double		OKRangeInInitial;
	int			OutputType;		//0:real distance	,1:Difference from Threshold center
	int			SearchType;		//0:Separated ideal area	1:Simple left/right area
	double		ThresholdRate;

	BYTE		*BrightnessMasterRight;
	BYTE		*BrightnessMasterLeft;
	double		BrightnessIdealRight;
	double		BrightnessIdealLeft	;
	double		BrightnessIdealRightRange;
	double		BrightnessIdealLeftRange;


	MeasureLineMoveThreshold(AlgorithmItemPI *parent);
	virtual	~MeasureLineMoveThreshold(void);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	int		GetSize(void)	const override	{	return sizeof(this);	}
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


class	MeasureLineMoveItemBase : public AlgorithmItemPI
{
public:
	AlignmentPacket2D	*AVector;
	int			AMx,AMy;
public:
	QImage	TResultImage;		//検査の部分画像
	QImage	LResultImage;		//検査の線画像

	int32	TransferInfo;		//-1: No transfer, 0-:TxID

	MeasureLineMoveItemBase(void){	AVector=NULL;	AMx=0;	AMy=0;	TransferInfo=-1;	}

	const	MeasureLineMoveThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MeasureLineMoveThreshold *)GetThresholdBaseReadable(base);	}
	MeasureLineMoveThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MeasureLineMoveThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new MeasureLineMoveThreshold(this);	}

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;

	void	ExecuteInitialAfterEdit_InFunc	(ExecuteInitialAfterEditInfo &EInfo);
	virtual	MeasureCommon	*GetMeasureCommon(void)		=0;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)=0;
	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	=0;
	virtual	void	InitialInCreation(void){}
	virtual	bool	IsEnableMakeImage(void)	{	return true;	}

	virtual bool	MakeDataToTransfer(QIODevice *f)	{	return true;	}

	double	ExpFunc(double c ,double MasterC);

	void	CreateImage(int Width ,int Height);
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)		=0;
};

class	MeasureLineMoveLineItem : public MeasureLineMoveItemBase , public MeasureCommon
{
	//FlexAreaImageListCoeff	AreaWithIdeal;
	FlexAreaImageListCoeffContainer	AreaWithIdealContainer;
	PureFlexAreaListContainer		AreaRightContainer;
	PureFlexAreaListContainer		AreaLeftContainer;

	FlexArea	AreaSideA;
	FlexArea	AreaSideB;
	double		AvrSideA;
	double		AvrSideB;

public:
	double	X1OnMaster;
	double	Y1OnMaster;
	double	X2OnMaster;
	double	Y2OnMaster;
	double	Vx,Vy;		//単位法線ベクトル
	double	ResultShift;
	double	OffsetForDark;
	double	MatchStartPos;
	double	MatchEndPos;

	MeasureLineMoveLineItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureLineMoveLineItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return MeasureLineMove_ItemClass_Line;		}

	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)const	override	{	return (GetVector()!=NULL)?GetVector()->GetXY(x1,y1,x2,y2):false;	}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	MeasureCommon	*GetMeasureCommon(void)		override	{	return this;	}
	virtual	VectorLineBase	*CreateVectorBase(void)								override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)				override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	int		GetItemID(void)						override{	return GetID();	}
	virtual	double	GetIsolation(double x ,double y)	override;
	virtual	double	GetDrawParam(double x ,double y)	override;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	override;
			double	GetDistance(double Px ,double Py);
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)		override;
	virtual	void	GetShiftVector(double &sx, double &sy)					override;
	virtual	void	GetCenterPoint(double &cx, double &cy)					override;
	virtual	void	Move(double dx ,double dy)								override;
	virtual	void	MoveForAlignment(void)	override;

	virtual bool	MakeDataToTransfer(QIODevice *f)	override	{	return true;	}

	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	override;

	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)		override	{	return this;	}
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	bool	IsInclude(int x ,int y)	const			override;
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)	override;
private:
	void	ExecuteInitialAfterEditMakeC(ExecuteInitialAfterEditInfo &EInfo);
	void	ExecuteInitialAfterEditMakeSmall(double t1 ,double t2,ExecuteInitialAfterEditInfo &EInfo);
	double	CalcCoeff(int dx ,int dy ,ImageBuffer &IBuff,bool BrightnessMatch=false);
	double	CalcCoeffOnlySameColor(int dx ,int dy ,ImageBuffer &IBuff,bool BrightnessMatch=false);
	double	CalcDeviationDiff(double dx ,double dy ,ImageBuffer &TargetImage);
	double	CalcDeviationDiff(double dx ,double dy ,ImageBuffer &TargetImage
													,int Col1,int ColRange1
													,int Col2,int ColRange2);

	double	GetResultShift(int mx ,int my ,ImageBuffer *TargetImage);
	double	GetAvrageBrightness(int mx ,int my ,PureFlexAreaListContainer &LRArea ,ImageBuffer &TargetImage);
	double	GetMatchingForType2(int mx ,int my,ImageBuffer &TargetImage);
	double	GetMatchingForType3(int mx ,int my,ImageBuffer &TargetImage);
	double	GetMatchingForType4(int mx ,int my,ImageBuffer &TargetImage);
	double	GetLineAverage(double dx ,double dy ,ImageBuffer &TargetImage);
};

class	MeasureLineMoveRxLineItem : public MeasureLineMoveItemBase , public MeasureCommon
{
	MeasureCommon	*HookedItem;
public:
	int		HookedItemID;
	int		RxID;
	bool	Received;

	double	X1OnMaster;
	double	Y1OnMaster;
	double	X2OnMaster;
	double	Y2OnMaster;
	double	Hx,Hy;
	double	Vx,Vy;		//単位法線ベクトル
	double	ResultShift;

	MeasureLineMoveRxLineItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureLineMoveRxLineItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return MeasureLineMove_ItemClass_RxLine;		}

	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)const	override	{	return (GetVector()!=NULL)?GetVector()->GetXY(x1,y1,x2,y2):false;	}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	MeasureCommon	*GetMeasureCommon(void)		override	{	return this;	}
	virtual	VectorLineBase	*CreateVectorBase(void)								override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)				override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	int		GetItemID(void)						override{	return GetID();	}
	virtual	double	GetIsolation(double x ,double y)	override;
	virtual	double	GetDrawParam(double x ,double y)	override;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	override;
			double	GetDistance(double Px ,double Py);
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)		override;
	virtual	void	GetShiftVector(double &sx, double &sy)					override;
	virtual	void	GetCenterPoint(double &cx, double &cy)					override;
	virtual	void	Move(double dx ,double dy)								override;
	virtual	void	MoveForAlignment(void)	override;
	virtual	bool	IsEnableMakeImage(void)	override	{	return true;	}

	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	override;


	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)		override	{	return this;	}
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	bool	IsInclude(int x ,int y)	const			override;
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)	override;
private:
	double	TrasnformUnitFromPixel(double Pixel);
	double	TransformPixelFromUnit(double Unit);
};

class	MeasureLineMoveCornerRItem : public MeasureLineMoveItemBase
{
	FlexAreaImageListCoeff	AreaWithIdeal1;
	FlexAreaImageListCoeff	AreaWithIdeal2;
	FlexAreaImageListCoeff	AreaWithIdeal3;
	double	Vx1,Vy1;		//単位法線ベクトル
	double	Vx2,Vy2;		//単位法線ベクトル
	double	Vx3,Vy3;		//単位法線ベクトル
	double	Cx1,Cy1;
	double	Cx2,Cy2;
	double	Cx3,Cy3;

	FlexArea	Area1I;
	FlexArea	Area1O;
	double		Avr1I;
	double		Avr1O;
	FlexArea	Area2I;
	FlexArea	Area2O;
	double		Avr2I;
	double		Avr2O;
	FlexArea	Area3I;
	FlexArea	Area3O;
	double		Avr3I;
	double		Avr3O;

public:
	double	CxOnMaster;
	double	CyOnMaster;
	double	RxOnMaster;
	double	RyOnMaster;
	double	AngleS1;
	double	AngleS2;
	double	ResultDifR;
	double	ResultCx,ResultCy;

	MeasureLineMoveCornerRItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureLineMoveCornerRItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return MeasureLineMove_ItemClass_CornerR;		}

	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	override{	return (GetVector()!=NULL)?GetVector()->GetXY(x1,y1,x2,y2):false;	}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;
	virtual	bool	Transform(TransformBase &Param)		override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)		override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	MeasureCommon	*GetMeasureCommon(void)		override	{	return NULL;	}
	virtual	VectorLineBase	*CreateVectorBase(void)	override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)				override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	override;
	virtual	bool	IsInclude(int x ,int y)	const override;
	virtual	void	MoveForAlignment(void)	override;
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)	override;
private:
	void	MakeArcArea(double StartS ,double EndS ,FlexAreaImageListCoeff &Area
												,FlexArea &AreaI
												,FlexArea &AreaO);
	void	MakeIdeal(FlexAreaImageListCoeff &Area);
	void	ExecuteInitialAfterEditMakeC	(ExecuteInitialAfterEditInfo &EInfo);
	double	ExecuteProcessingInner ( int mx,int my
									,ImageBuffer *ImageList[]
									,FlexAreaImageListCoeff &AreaWithIdeal
									,FlexArea &AreaI ,double AvrI
									,FlexArea &AreaO ,double AvrO
									,double vx ,double vy);

};

class	MeasureLineMoveMarkItem : public MeasureLineMoveItemBase , public MeasureCommon
{
	FlexAreaImageListCoeff		TransArea;
	FlexArea					iTransArea;
	FlexArea					oTransArea;

	int		VLineX,VLineY1,VLineY2;
	int		HLineX1,HLineX2,HLineY;
	BYTE	*VDot;
	BYTE	*HDot;
	int		AddedS;
	int		AddedSS;

public:
	double	XOnMaster;
	double	YOnMaster;

	double	ResultMatch;
	double	ResultDx;
	double	ResultDy;


	MeasureLineMoveMarkItem(void);
	~MeasureLineMoveMarkItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureLineMoveMarkItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return MeasureLineMove_ItemClass_Mark;		}

	virtual	void	InitialInCreation(void)		override;
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	override{	return GetArea().GetXY(x1,y1,x2,y2);	}
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)						override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	DrawNumber(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate
							   ,int Number)	override{}

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	MeasureCommon	*GetMeasureCommon(void)		override	{	return this;	}
	virtual	VectorLineBase	*CreateVectorBase(void)	override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;

	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	override;
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;

	bool    MakeArea(ImageBuffer &Buff ,ImageBuffer *specialData=NULL);
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;

	virtual	int		GetItemID(void)		override	{	return GetID();	}
	virtual	double	GetIsolation(double x ,double y)						override;
	virtual	double	GetDrawParam(double x ,double y)						override;
	virtual	double	GetTParam(double x1 ,double y1 ,double x2 ,double y2)	override;
	virtual	void	GetDrawPoint(double Param ,double &x ,double &y)		override;
	virtual	void	GetShiftVector(double &sx, double &sy)					override;
	virtual	void	GetCenterPoint(double &cx, double &cy)					override;
	virtual	void	Move(double dx ,double dy)								override;
	virtual	void	MoveForAlignment(void)	override;

	virtual	AlgorithmItemPI	*GetAlgorithmItem(void)	override	{	return this;	}
	virtual	bool	IsInclude(int x ,int y)	const	override;
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)	override;

private:
	void	ExecuteInitialAfterEditMakeC(DWORD ExecuteInitialAfterEdit_Changed);
	void	ExecuteInitialAfterEditMakeSmall(double t1 ,double t2,ExecuteInitialAfterEditInfo &EInfo);

	void	MakeHVDot(ImageBuffer &Buff);
	double	GetThreshLevel(ImageBuffer &data ,int dx=0 ,int dy=0);
	double  MatchBrightCenter(double &mx ,double &my ,ImageBuffer &Target ,int offsetX,int offsetY);
	double	MatchCross(ImageBuffer &Target ,int dx,int dy);
};

class	MeasureLineMoveDistanceItem : public MeasureLineMoveItemBase
{
public:
	int		MeasurePointNo;		//Special
	int32	LineType1;
	int32	LineType2;
	bool	NoCalc;		//This is for multi-scan mode and for drawing
	int32	Line1InGlobalPage;
	int32	LineID1;
	int32	Line2InGlobalPage;
	int32	LineID2;
	double	DrawPoint1;
	double	DrawPoint2;
	double	DifLen;
	double	ResultLen;
	double	RealLen;
	struct MeasureHVInfo	GenData;

	QByteArray	ResultExtraData;

	MeasureLineMoveDistanceItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MeasureLineMoveDistanceItem();	}
	virtual	int32		GetItemClassType(void)		override	{		return MeasureLineMove_ItemClass_Distance;		}

	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	override;
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
	virtual	bool    Save(QIODevice *f)									override;
    virtual	bool    Load(QIODevice *f,LayersBase *LBase)				override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	virtual	MeasureCommon	*GetMeasureCommon(void)		override	{	return NULL;	}
	virtual	VectorLineBase	*CreateVectorBase(void)					override;
	virtual	bool	SetLocalData(MeasureLineMoveInPage *ParentPage)	override;

	double	GetDistanceInMaster(double &X1,double &Y1,double &X2,double	&Y2);
	double	GetResultDistance(void);
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	SetConstructList(LineMoveReqTryThreshold *reqPacket,LineMoveSendTryThreshold *Packet)	override;
	virtual	bool	IsInclude(int x ,int y)	const override;
	void	SetEndPoint(int EndNo ,int X ,int Y);

	void	ExecuteProcessingLocal	(MeasureCommon *TargetLine1,MeasureCommon *TargetLine2,ResultInItemRoot *Result);
	virtual bool	MakeDataToTransfer(QIODevice *f)	override;

	double	TrasnformUnitFromPixel(double Pixel);
	double	TransformPixelFromUnit(double Unit);

	MeasureCommon	*GetFirstPointOnMaster(void)	const;
	MeasureCommon	*GetSecondPointOnMaster(void)	const;
	virtual	void	MakeResultImage(int &ImageX1,int &ImageY1,double &ImageZoomRate
									,bool EnableMakeImage ,bool EnableDrawLine)	override;
	virtual	void	UpdateThreshold(int LearningMenuID ,LearningResource &LRes)			override;
private:
	double	CalcDiv(double x1,double y1,double x2,double y2 ,double Sep,ImageBuffer *ImageList[]);
};


class SocketApp: public QObject
{
	Q_OBJECT
public:
	QTcpSocket				*sv;
	MeasureLineMoveInPage	*Parent;

	SocketApp(QTcpSocket *p,MeasureLineMoveInPage *parent);

private slots:
	void	SlotReadyRead();
};

class TransferItem : public NPList<TransferItem>
{
public:
	int32		ID;
	QByteArray	Data;
	TransferItem(void){}
};

class TransferPacket : public NPList<TransferPacket>
{
public:
	int64	InspectionID;
	NPListPack<TransferItem>	TransferItems;

	TransferPacket(void){}
};


class   MeasureLineMoveInPage : public QObject ,public AlgorithmInPagePI
{
	Q_OBJECT

	AlgorithmItemPointerListContainer	Items1;		//Line ,Arc ,Mark
	AlgorithmItemPointerListContainer	Items2;		//RxLine
	AlgorithmItemPointerListContainer	Items3;		//Distance

	QTcpServer	Server;
	SocketApp	*ServerSock;
	QTcpSocket	SockSender;
	QTimer		TimerForConnection;
	NPListPack<TransferPacket>	TransferPacks;
public:
	FlexArea	PickupArea;
	BYTE		**PickupBmp;
	int			PickupBmpXByte;
	int			PickupBmpYLen;
	FlexArea	MaskArea;

	MeasureLineMoveInPage(AlgorithmBase *parent);
	virtual	~MeasureLineMoveInPage(void);

	virtual	void	InitialAfterParamLoaded(void)	override;

	virtual	AlgorithmItemRoot		*CreateItem(int ItemClassType=0)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)			override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res) override;

	void	CreatePickupBmpBuff(void);
	void	ReleasePickupBmpBuff(void);

	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)	override;
	void	GetItemBitmap(int LibType,int LibID,BYTE **Dst ,int XLen ,int YLen);
	void	SetLimitedMask(int LibType,int LibID,BYTE **MaskBitmap ,int XByte ,int YLen);

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	void	UndoSetIndependentItemDataCommand(QIODevice *f);


	void	TransferTx(QByteArray &TData);
	void	ReceiveFromTransfer(QByteArray &RData);

	TransferItem	*FindTransferItem(int64 InspectionID,int ID);
private:
	void	PickupBlade( int BladePickupRL,int BladePickupRH
						,int BladePickupGL,int BladePickupGH
						,int BladePickupBL,int BladePickupBH
						,int X1, int X2
						,FlexArea &BladeArea
						,FlexArea &MaskArea);
	bool	AddMeasureItems(FlexArea &BladeArea,FlexArea &MaskArea
							,struct MeasureHVInfo	&GenData
							,int LineLib,int DistanceLib
							,int BaseItemID
							,int MeasurePointNo);
	bool	AddFilmMeasureItems(FlexArea &BladeArea,FlexArea &MaskArea
							,struct MeasureHVInfo	&GenData
							,int LineLib,int RxLineLib,int DistanceLib
							,int BaseItemID
							,int MeasurePointNo);
	bool	RemoveFilmMeasure(int MeasurePointNo);
	bool	AddMonoFilmMeasureItems(void);

	void	MakeBMap(BYTE **CurrentMap ,int XByte,int XLen ,int YLen
						,int BladePickupRL
						,int BladePickupRH
						,int BladePickupGL
						,int BladePickupGH
						,int BladePickupBL
						,int BladePickupBH
						,int X1, int X2);
	bool	FindY(FlexArea &Area,int XPos,int &MinY,int &MaxY);

	MeasureLineMoveDistanceItem	*SearchDistanceItem(int MeasurePointNo);
	void	MaskHole(FlexArea &PickupArea
					,int BladeHoleMinArea
					,int BladeHoleErosionDot);

	int		SearchLeftEdge(ImageBuffer &Buff,int X,int Y,int SearchDot);

private slots:
	void	SlotNewConnection();
	void	SlotTimer();
	void	SlotDisconnected();
};

#define	LearningMenu_MeasureLineMove_OK_ByDistance	1
#define	LearningMenu_MeasureLineMove_OK_BySide1		2
#define	LearningMenu_MeasureLineMove_OK_BySide2		3

class	MeasureLineMoveBase : public AlgorithmBase
{
public:
	QColor	ColorMask;
	QColor	ColorSelected;
	QColor	ColorActive;
	int32	TransparentLevel;
	QColor	NegColorMask;
	QColor	NegColorSelected;
	QColor	ResultColor;
	bool	ResultArrowEnableMakeImage		;
	bool	ResultArrowEnableDrawLine		;
	bool	ResultDistanceEnableMakeImage	;
	bool	ResultDistanceEnableDrawLine	;
	bool	SaveItemImage;

	bool	Receiver		;
	int		TransferPortNo	;
	QString	TransferIP		;

	bool	EnableFilm				;
	int		FilmLineLen				;
	int		FilmLineLibID			;
	int		FilmLineDistanceLibID	;
	int		FilmLineSearchDot		;
	int		FilmTopPaperLineOffsetX	;
	int		FilmTopFilmPaperX		;
	int		FilmTopFilmEdgeOffsetX	;
	int		FilmTopFilmEdgeOffsetY	;
	int		FilmTopRangeYLen		;
	int		FilmTopBrightness1		;
	int		FilmTopBrightness2		;
	int		FilmTopBrightness1Range	;
	int		FilmTopBrightness2Range	;

	int		FilmBotPaperLineOffsetX	;
	int		FilmBotFilmPaperX		;
	int		FilmBotFilmEdgeOffsetX	;
	int		FilmBotFilmEdgeOffsetY	;
	int		FilmBotRangeYLen		;
	int		FilmBotBrightness1		;
	int		FilmBotBrightness2		;
	int		FilmBotBrightness1Range	;
	int		FilmBotBrightness2Range	;


	MeasureLineMoveBase(LayersBase *Base);

	virtual	AlgorithmInPagePI	*NewChild(AlgorithmBase *parent)	override{	return new MeasureLineMoveInPage(parent);		}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override{	return QString("MeasureLineMove");				}
	virtual	QString	GetDefaultFileName(void)	override{	return QString("ConfigMeasureLineMove.dat");	}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	int	GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)	override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;
	virtual	bool	AvailableShrinkItem(void)		const	override	{	return false;	}
	virtual	bool	AvailableChangeLibrary(void)	const	override	{	return false;	}
	//virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
};
//==================================================================================
#define	SetIndependentItemDataCommand_OnlyOne	1
#define	SetIndependentItemDataCommand_All		2
#define	ReqTryThresholdCommand					7
#define	SendTryThresholdCommand					8
#define	ReqThresholdReqCommand					9
#define	ReqThresholdSendCommand					10


class	LineMoveThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	LineMoveThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	LineMoveThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	int			SearchDot;
	double		ThresholdM;
	double		ThresholdP;
	int			EdgeWidth;

	LineMoveThresholdSend(void);

	void	ConstructList(LineMoveThresholdReq *reqPacket,MeasureLineMoveBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};


class	LineMoveReqTryThreshold
{
public:
	int32	GlobalPage;
	int		ItemID;	
	MeasureLineMoveLineItem		ItemLine;
	MeasureLineMoveRxLineItem	ItemRxLine;
	MeasureLineMoveCornerRItem	ItemArc;
	MeasureLineMoveDistanceItem	ItemDistance;

	LineMoveReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};


class	LineMoveSendTryThreshold : public AddedDataClass
{
public:
	double	PosDiffX;
	double	PosDiffY;
	int		Error;

	double	DiffR;
	double	Radius;

	double	Distance;
	double	RealDistance;
	double	DiffDistance;
	ResultInItemRoot	*Result;

	LineMoveSendTryThreshold(void);
	~LineMoveSendTryThreshold(void);

	void	ConstructList(LineMoveReqTryThreshold *reqPacket,MeasureLineMoveBase *Base);

	void	Calc(MeasureLineMoveDistanceItem *TargetDistance ,MeasureLineMoveItemBase *TargetLine1,MeasureLineMoveItemBase *TargetLine2
				,MeasureLineMoveDistanceItem *SrcDistance ,MeasureLineMoveItemBase *SrcLine1,MeasureLineMoveItemBase *SrcLine2
				,MeasureLineMoveBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//===================================================================================

class	AddMeasureLineMoveAreaPacket : public GUIDirectMessage
{
public:
	ColorLogic	CupperColor;
	bool		ModeLine;
	bool		ModeCornerR;
	bool		ModeDistance;
	FlexArea	MaskArea;

	AddMeasureLineMoveAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMeasureLineMoveAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MeasureLineMoveDrawAttr : public AlgorithmDrawAttr
{
public:
	QColor	NegColorMask;
	QColor	NegColorSelected;
	int		ShowingItemID;

	MeasureLineMoveDrawAttr(void){	ShowingItemID=-1;	}
	MeasureLineMoveDrawAttr(const QColor &ncol ,const QColor &scol ,const QColor &acol):AlgorithmDrawAttr(ncol,scol,acol),ShowingItemID(-1){}
	MeasureLineMoveDrawAttr( 
					 const QColor &ncol ,int ntranparentLevel
					,const QColor &scol ,int stranparentLevel
					,const QColor &acol ,int atranparentLevel
					,const QColor &nncol
					,const QColor &nscol)
		:AlgorithmDrawAttr(ncol,ntranparentLevel
						,  scol,stranparentLevel
						,  acol,atranparentLevel)
		,ShowingItemID(-1)
	{	
		NegColorMask	=nncol;	
		NegColorSelected=nscol;	
		NegColorMask.setAlpha(ntranparentLevel);
		NegColorSelected.setAlpha(stranparentLevel);
	}
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

inline	bool	MeasureLineMoveDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,NegColorMask)==false)		return false;
	if(::Save(f,NegColorSelected)==false)	return false;
	if(::Save(f,ShowingItemID)==false)		return false;
	return true;
}
inline	bool	MeasureLineMoveDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,NegColorMask)==false)		return false;
	if(::Load(f,NegColorSelected)==false)	return false;
	if(::Load(f,ShowingItemID)==false)		return false;
	return true;
}

class	CmdMeasureLineMoveDrawPacket : public GUIDirectMessage
{
public:
	int		movx;
	int		movy;
	double	ZoomRate;
	QImage	*Canvas;
	IntList	LayerList;
//	CmdBlockDrawModePacket::DrawMode	Mode;

	CmdMeasureLineMoveDrawPacket(LayersBase *base,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(base)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
	CmdMeasureLineMoveDrawPacket(GUICmdPacketBase *gbase,int _movx ,int _movy ,double zoomrate
		,QImage *canvas ,IntList &layerList)
		:GUIDirectMessage(gbase)
		,movx(_movx),movy(_movy),ZoomRate(zoomrate),Canvas(canvas),LayerList(layerList){}
};

class	CmdCreateTempMeasureLineMoveLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempMeasureLineMoveLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMeasureLineMoveLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetMeasureLineMoveLibraryListPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMeasureLineMoveLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdLoadMeasureLineMoveLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadMeasureLineMoveLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearMeasureLineMoveLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearMeasureLineMoveLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteMeasureLineMoveLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteMeasureLineMoveLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdExecuteAlignMeasureLineMove :public GUIDirectMessage
{
public:
	VectorItemDouble	ImagePoint[3];
	VectorItemDouble	ItemPoint[3];

	CmdExecuteAlignMeasureLineMove(LayersBase *base):GUIDirectMessage(base){}
	CmdExecuteAlignMeasureLineMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddByteMeasureLineMoveItemPacket :public GUIDirectMessage
{
public:
	QByteArray	Buff;
	VectorLineBase	*Vector;
	int			LocalPage;
	int			ItemClass;
	int			SelectedLibID;
	QString		ItemName;
	FlexArea	Area;		//For MarkArea

	//These are for Distance between scans
	bool		NoCalc;
	int			GlobalPage1;
	int			ClosedItemID1;
	int			GlobalPage2;
	int			ClosedItemID2;

	CmdAddByteMeasureLineMoveItemPacket(LayersBase *base):GUIDirectMessage(base)		{	Vector=NULL;	}
	CmdAddByteMeasureLineMoveItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Vector=NULL;	}

	~CmdAddByteMeasureLineMoveItemPacket(void)	{	if(Vector!=NULL){	delete	Vector; Vector=NULL;	}	}	
};

class	CmdInsertMeasureLineMoveLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMeasureLineMoveLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateMeasureLineMoveLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMeasureLineMoveLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateMeasureLineMoveLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateThresholdPacket : public GUIDirectMessage
{
public:
	MeasureLineMoveThreshold	*Thre;

	CmdCreateThresholdPacket(LayersBase *base):GUIDirectMessage(base){	Thre=NULL;	}
	CmdCreateThresholdPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	Thre=NULL;	}
};

class	CmdReqMeasureLineMoveIDPacket: public GUIDirectMessage
{
public:
	int		LocalX;
	int		LocalY;
	int		ItemID;

	CmdReqMeasureLineMoveIDPacket(LayersBase *base):GUIDirectMessage(base){	ItemID=-1;	}
	CmdReqMeasureLineMoveIDPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){	ItemID=-1;	}
};

//=================================================================================

class	LineMoveListForPacket : public NPListSaveLoad<LineMoveListForPacket>
{
public:
	int		ItemID;
	int		LibID;
	QString	ItemName;
	int		Page;
	int		x1,y1,x2,y2;
	int		SearchDot;
	
	LineMoveListForPacket(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	LineMoveListForPacket	&operator=(LineMoveListForPacket &src);
};

class	LineMoveListForPacketPack : public NPListPackSaveLoad<LineMoveListForPacket>
{
public:
	LineMoveListForPacketPack(void){}

	virtual	LineMoveListForPacket	*Create(void);
};

class	MakeListPacket : public GUIDirectMessage
{
public:
	LineMoveListForPacketPack	*ListInfo;

	MakeListPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdCreateThresholdMeasureLineMove : public GUIDirectMessage
{
public:
	MeasureLineMoveDistanceItem	*Item;		
	MeasureLineMoveThreshold	*ThresholdD;	
	MeasureLineMoveThreshold	*ThresholdL1;	
	MeasureLineMoveThreshold	*ThresholdL2;	

	CmdCreateThresholdMeasureLineMove(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	ThresholdD=NULL;	ThresholdL1=NULL;	ThresholdL2=NULL;}
	CmdCreateThresholdMeasureLineMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdCreateThresholdMeasureLineMove(void){	delete	Item;	delete	ThresholdD;	delete	ThresholdL1;	delete	ThresholdL2;	}
};
class	CmdMeasureLineMoveSendTryThreshold : public GUIDirectMessage
{
public:
	LineMoveSendTryThreshold	*PTry;
	MeasureLineMoveDistanceItem	*SrcD;
	MeasureLineMoveItemBase		*SrcL1;
	MeasureLineMoveItemBase		*SrcL2;
	MeasureLineMoveDistanceItem	*TargetD;
	MeasureLineMoveItemBase		*TargetL1;
	MeasureLineMoveItemBase		*TargetL2;
	QByteArray					ThresholdDataForTargetD;
	QByteArray					ThresholdDataForTargetL1;
	QByteArray					ThresholdDataForTargetL2;

	CmdMeasureLineMoveSendTryThreshold(LayersBase *base):GUIDirectMessage(base)
	{	PTry=NULL;	SrcD=NULL;	SrcL1=NULL;	SrcL2=NULL;	TargetD=NULL;	TargetL1=NULL;	TargetL2=NULL;	}
	CmdMeasureLineMoveSendTryThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdMeasureLineMoveSendTryThreshold(void)
		{	
			delete	PTry;
			delete	TargetD;
			delete	TargetL1;
			delete	TargetL2;
		}
};
class	CmdReqThresholdHLMeasureLineMove : public GUIDirectMessage
{
public:
	MeasureLineMoveDistanceItem	*Item;		
	double		ThresholdM;
	double		ThresholdP;
	double		ThresholdMUnit;
	double		ThresholdPUnit;

	CmdReqThresholdHLMeasureLineMove(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	}
	CmdReqThresholdHLMeasureLineMove(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdReqThresholdHLMeasureLineMove(void){}
};
//=================================================================================
class	CmdGenerateMeasure : public GUIDirectMessage
{
public:
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;
	int32	BladeLeft ;
	int32	BladeRight;
	int32	LineLib;
	int32	RxLineLib;
	int32	DistanceLib;
	int32	MaskLib;
	int32	BladeHoleMinArea;
	int32	BladeHoleErosionDot;
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;
	bool	OnlyGenerateFilmLen;

	CmdGenerateMeasure(LayersBase *base):GUIDirectMessage(base){	OnlyGenerateFilmLen=false;	}
};
class	CmdReqCorrentValues : public GUIDirectMessage
{
public:
	BladeMeasure	BladeMeasureData;
	bool			Mastered;

	CmdReqCorrentValues(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetCorrectValues : public GUIDirectMessage
{
public:
	BladeMeasure	BladeMeasureData;
	int32	LineLib;
	int32	RxLineLib;
	int32	DistanceLib;
	int32	MaskLib;
	int32	BladePickupRL;
	int32	BladePickupRH;
	int32	BladePickupGL;
	int32	BladePickupGH;
	int32	BladePickupBL;
	int32	BladePickupBH;

	CmdSetCorrectValues(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetOnlyBladeThreshold : public GUIDirectMessage
{
public:
	BladeMeasure	BladeMeasureData;
	BladeMeasure	FilmMeasureData;

	CmdSetOnlyBladeThreshold(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdSetMeasureEndPoint : public GUIDirectMessage
{
public:
	int		EndNo;
	int		MeasureNo;
	int		X;
	int		Y;


	CmdSetMeasureEndPoint(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdReqMeasureLineInfo : public GUIDirectMessage
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	CmdReqMeasureLineInfo(LayersBase *base):GUIDirectMessage(base){	SearchDot=0;	}
};
class	CmdSetMeasureLineInfo : public GUIDirectMessage
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	CmdSetMeasureLineInfo(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdSetMeasureLineInfoAll : public GUIDirectMessage
{
public:
	int	Phase;
	int	Page;
	int	DistanceItemID;
	int	EndNo;
	int	MeasureNo;
	int	SearchDot;

	CmdSetMeasureLineInfoAll(LayersBase *base):GUIDirectMessage(base){}
};
class	CmdReqMeasureLinePosition : public GUIDirectMessage
{
public:
	int	Page;
	int	Phase;
	int	DistanceItemID;
	int	RetPos1X;
	int	RetPos1Y;
	int	RetPos2X;
	int	RetPos2Y;

	CmdReqMeasureLinePosition(LayersBase *base):GUIDirectMessage(base){}
};
//=================================================================================================

class CmdReqDistancePacket: public GUIDirectMessage
{
public:
	MeasureDistanceItemInfoContainer	DataList;

	CmdReqDistancePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdReqDistancePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetDistanceCorrectValue : public GUIDirectMessage
{
public:
	int		Phase;
	int		Page;
	int		ItemID;
	double	OKLengthLUnit;
	double	OKLengthHUnit;	

	CmdSetDistanceCorrectValue(LayersBase *base):GUIDirectMessage(base){}
	CmdSetDistanceCorrectValue(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAddDistance : public GUIDirectMessage
{
public:
	int		X1;
	int		Y1;
	int		X2;
	int		Y2;
	int		LineLength;
	int		LineLibID1;
	int		LineLibID2;
	int		DistanceLibID;

	CmdAddDistance(LayersBase *base):GUIDirectMessage(base){}
	CmdAddDistance(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdDeleteMeasureDistance: public GUIDirectMessage
{
public:
	int		Phase;
	int		Page;
	int		MeasureNo;

	CmdDeleteMeasureDistance(LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteMeasureDistance(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqChangeMeasureLineMoveEndPoint: public GUIDirectMessage
{
public:
	bool	Point1;
	bool	Point2;
	int		ItemID;
	int		LocalX,LocalY;

	CmdReqChangeMeasureLineMoveEndPoint(LayersBase *base):GUIDirectMessage(base){}
	CmdReqChangeMeasureLineMoveEndPoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


#endif
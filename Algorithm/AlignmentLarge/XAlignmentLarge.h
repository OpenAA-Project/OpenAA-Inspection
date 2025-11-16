/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentLarge\XAlignmentLarge.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XAlignemntLargeH
#define XAlignemntLargeH

#include <QIODevice>
#include <QPoint>
#include <QString>
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
//#include "XPacketAlignmentLarge.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageLayerItem.h"
#include "XAlgorithmLibrary.h"
#include "XAlignmentLargeLibrary.h"
#include "XStandardCommand.h"
#include "XFlexAreaImage.h"
#include "XLineMatching.h"

#define	AlignmentLargeVersion	3

class	XAlignmentLarge;
class   AlignmentLargeInLayer;
class	XAlignmentLargeArea;
class	AlignmentLargeDrawAtt;
class	AlignmentLargeBase;


class	AlignmentLargeThreshold : public AlgorithmThreshold
{
public:
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;	//For priority 1 and 2
	WORD		MoveDotY2;

	WORD		OrgMoveDotX;
	WORD		OrgMoveDotY;
	WORD		OrgMoveDotX2;	//For priority 1 and 2
	WORD		OrgMoveDotY2;

	WORD		SearchAround;
	int			UsageGlobal;
	int			MaxCountHLine;
	int			MaxCountVLine;
	bool		JudgeWithBrDif;
	int			SkipDotForRoughSearch;
	int			SkipOnMatchingLine;
	int			UseLayer;		//-1:Automatic select layer
	int			ThresholdColor;	//-1:Automatic colc threshold brightness

	bool		CharacterMode;

	AlignmentLargeThreshold(XAlignmentLarge *parent);
	~AlignmentLargeThreshold(void);

	void	RegistHist(void)							override	;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override	;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override	;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override	;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override	;
	virtual	bool	Save(QIODevice *f)					override	;
    virtual	bool	Load(QIODevice *f)					override	;
    virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

	bool	IsChangeToOrg(void);
};


struct	AlignmentLargeShiftListStruct
{
	int		Dx,Dy;
	double	Match;
};

struct	AlignmentLargeShiftItemListStruct
{
	int		Dx,Dy;
	double	Match;
	XAlignmentLarge	*Item;
	bool	Adopted;

	AlignmentLargeShiftItemListStruct(void){	Item=NULL;	}
};


#define	Hist_AlignmentLargeShiftX	1
#define	Hist_AlignmentLargeShiftY	2
#define	SetIndependentAlignmentLargeItemDataCommand_OnlyOne	10
#define	SetIndependentAlignmentLargeItemDataCommand_All		12

//=================================================================================================

class	AlignmentLargeShiftList: public NPListSaveLoad<AlignmentLargeShiftList>
{
public:
	int		GlobalPage;
	int		ItemID;
	bool	CalcDone;
	double	ShiftX,ShiftY;
    double	MasterX,MasterY;

	AlignmentLargeShiftList(void){	CalcDone=false;	ShiftX=0;	ShiftY=0;	MasterX=0;	MasterY=0;	}
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
class	AlignmentLargeShiftContainer : public NPListPackSaveLoad<AlignmentLargeShiftList>
{
public:
	AlignmentLargeShiftContainer(void)	{}
	virtual	AlignmentLargeShiftList	*Create(void){	return new AlignmentLargeShiftList();	}
};

//=================================================================================================

class   XAlignmentLargePointer :public NPList<XAlignmentLargePointer>
{
public:
	XAlignmentLarge		*Point;
	//XAlignmentLargeArea	*Parent;

	XAlignmentLargePointer(void);
	XAlignmentLargePointer(XAlignmentLarge	*P):Point(P){}
    XAlignmentLargePointer &operator=(XAlignmentLargePointer &src);
	virtual	DataInLayer	*GetDataInLayer(void);

	bool    Save(QIODevice *file);
	bool    Load(QIODevice *file ,XAlignmentLargeArea *parent);
};

class	XAlignmentLargePointerContainer : public NPListPack<XAlignmentLargePointer>
{
public:
	XAlignmentLargePointerContainer(void){}

	XAlignmentLargePointerContainer	&operator=(const XAlignmentLargePointerContainer &src);
	int	GetMachingPoint(struct	AlignmentLargeShiftItemListStruct BestMatch[3]);

	void	GetCenter(double &Cx, double &Cy);
	void	SetAdopted(struct AlignmentLargeShiftItemListStruct &s);
};

class   XAlignmentLarge : public AlgorithmItemPLI
{
public:

	class	AlignmentVLine
	{
		int		Skip;
	public:
		int		AddedS;		//ForSkip
		int		AddedSS;	//ForSkip
		int		DetailAddedS;
		int		DetailAddedSS;
		int		VLineX,VLineY1,VLineY2;
		BYTE	*VDot;
		BYTE	*DetailVDot;
		double	AvrS;
		double	MS;
	
		AlignmentVLine(void);
		~AlignmentVLine(void);
	
		AlignmentVLine	&operator=(AlignmentVLine &src);
		bool	Allocate(void);
		void	Release(void);
		bool	MakeDot(ImageBuffer &Buff,XAlignmentLarge *Item ,int Skip);
		void	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		bool	IsEffevtive(void)	{	return (VDot!=NULL)?true:false;	}
		double	Calc(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery);
		double	CalcDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
		void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo,int MaxXRange,int MaxYRange);
		bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
		void	Move(int Dx ,int Dy);
		bool    Save(QIODevice *file);
	    bool    Load(QIODevice *file);
		bool	GetXY(int &x1, int &y1, int &x2 ,int &y2);
	
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
	};
	
	class	AlignmentHLine
	{
		int		Skip;
	public:
		int		AddedS;		//ForSkip
		int		AddedSS;	//ForSkip
		int		AddedD ;
		int		AddedDD;
		int		LeftD ;
		int		LeftDD;
		int		DetailAddedS;
		int		DetailAddedSS;
		int		HLineX1,HLineX2,HLineY;
		BYTE	*HDot;
		BYTE	*DetailHDot;
		double	AvrS;
		double	MS;
	
		AlignmentHLine(void);
		~AlignmentHLine(void);
	
		AlignmentHLine	&operator=(AlignmentHLine &src);
		bool	Allocate(void);
		void	Release(void);
		void	Move(int Dx ,int Dy);
		bool	MakeDot(ImageBuffer &Buff,XAlignmentLarge *Item,int Skip);
		void	MatchCross(ImageBuffer &Target ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	MatchCrossStart(ImageBuffer &Target ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	MatchCrossNext(ImageBuffer &Target ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	MatchCrossDetail(ImageBuffer &Target ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		bool	IsEffevtive(void)	{	return (HDot!=NULL)?true:false;	}
		double	Calc	 (ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery);
		double	CalcStart(ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery);
		double	CalcNext (ImageBuffer &Target ,int dx,int dy,bool JudgeWithBrDif,double BrightnessVariery);
		double	CalcDetail(ImageBuffer &Target ,int dx,int dy);
		void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo,int MaxXRange,int MaxYRange);
		bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
		bool    Save(QIODevice *file);
	    bool    Load(QIODevice *file);
	
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
		bool	GetXY(int &x1, int &y1, int &x2 ,int &y2);
	};

	FlexAreaImageListCoeff		TransArea;
	FlexArea					iTransArea;
	FlexArea					oTransArea;
	XAlignmentLarge				*LinkThroughPhase;
	XAlignmentLargeArea			*LinkArea;

	AlignmentVLine	VLine1;
	AlignmentVLine	VLine2;
	AlignmentVLine	VLine3;
	AlignmentHLine	HLine1;
	AlignmentHLine	HLine2;
	AlignmentHLine	HLine3;

	XYData		*MatchingPointH;
	XYData		*MatchingPointL;
	int		CountOfMatchingPointH;
	int		CountOfMatchingPointL;
	double	MA;
	double	MAA;
	double	SkipMA;
	double	SkipMAA;
	int		CountOfMatchingPointSkipH;
	int		CountOfMatchingPointSkipL;
	BYTE	*MatchingPointTableH;
	BYTE	*MatchingPointTableL;
	double	ItemVar;

	int	RoughStepX;
	int	RoughStepY;
	LineMatchingX	RoughLine;
	struct	AlignmentLargeShiftListStruct	**RoughLineDim;
	int		RoughLineDimXNumb;
	int		RoughLineDimYNumb;

	int	MinDx,MinDy,MaxDx,MaxDy;

	int		AreaDx1,AreaDy1,AreaDx2,AreaDy2;

	struct	AlignmentLargeShiftListStruct	*ShiftList;
	int		ShiftListNumb;
	struct	AlignmentLargeShiftListStruct	*ShiftListSub;
	struct	AlignmentLargeShiftListStruct	*ShiftListFull;
	int		ShiftListFullNumb;

	struct	AlignmentLargeShiftListStruct	*SortedList;
	int		SortedListNumb;
	int		AllocSortedListNumb;

	double	TranAddedS;
	double	TranAddedSS;
	double	RootAddedS;
	double	RootAddedSS;
	double	SkipAddedS;
	double	SkipAddedSS;

	XYData	*LoopXYDim;
	int		LoopXYCount;
	int		SelectedLayer;	//-1: current layer
	int		ThresholdColor;
  public:
	struct	AlignmentLargeShiftItemListStruct	BestMatch[3];
	int		CountOfBestMatch;
	int		Priority;	//0,1,2

  public:
	WORD		GroupNumber;
	bool		Combination;
	double		MasterX,MasterY;
    double      CurrentResultDx	,CurrentResultDy;	//Calculated position
	double      LastResultDx	,LastResultDy;	//Calculated position
	WORD		AreaID;
	bool		UseBitBuff;

	XAlignmentLarge(void);
	~XAlignmentLarge(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new XAlignmentLarge();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;
    virtual	void    MoveTo(int dx ,int dy)	override;

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;

    double	MatchBrightCenter(double &mx ,double &my ,ImageBuffer &Target ,ImageBuffer &TRTarget ,int offsetX=0,int offsetY=0);
	double	MatchMosrDetail	(double &mx ,double &my ,ImageBuffer &Target ,int offsetX=0,int offsetY=0);
	
	const	AlignmentLargeThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const AlignmentLargeThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentLargeThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (AlignmentLargeThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AlignmentLargeThreshold(this);	}
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	XAlignmentLargeArea	*GetAlignmentArea(void);
	virtual	int		GetMasterNo(void)	override;
    void    Clear(void);
    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	bool	IsEffective(void)	const	override;
	ImageBuffer	&GetMasterBuffForMakeArea(void);
	bool    MakeArea(ImageBuffer &Buff ,ImageBuffer *specialData=NULL);
	void	GetHVCount(int &HLineCount ,int &VLineCount);

	double	GetDifferenceTransArea(ImageBuffer &Target ,int offsetX,int offsetY);

	void	Calc(ImageBuffer &TargetData ,ImageBuffer &TRTargetData ,int dx=0 ,int dy=0);
	//int		GetMx(void){	return(ResultDx);	}
	//int		GetMy(void){	return(ResultDy);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)		override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	void	MoveForAlignment(void)	override;

	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;
	void	CopyThresholdOnly(XAlignmentLarge *src);
	void	GetGlobalShift(int &mx,int &my);
	double	CalcTransAreaCalcCoeff(int dx,int dy,ImageBuffer &TargetData);
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)										override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;

	struct	AlignmentLargeShiftItemListStruct	*GetFinalResult(void);
	void	ChooseSelectedLayer(void);
public:
	double	GetThreshLevel(ImageBuffer &data ,int dx=0 ,int dy=0);
	void	ExecuteInitialAfterEditInner(bool HasChangedOnlyImage=false);

	double	MatchCross		(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
	double	MatchCrossDetail(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
	double	MatchCrossStartX(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
	double	MatchCrossNextX	(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
	void	MakeHVDot(void);
	double	MatchItem			(ImageBuffer &Master	,ImageBuffer &Target ,int dx,int dy);
	double	MatchItemTransArea	(ImageBuffer &Master	,ImageBuffer &Target ,int dx,int dy);
	double	MatchBitTransArea	(ImageBuffer &BitBuff	,ImageBuffer &Target ,int dx,int dy);
	double	MatchItemSkip		(ImageBuffer &Master	,ImageBuffer &Target ,int dx,int dy);
	double	MatchItemBit		(ImageBuffer &BitBuff	,ImageBuffer &Target ,int dx,int dy);
	double	MatchItemSkipBit	(ImageBuffer &BitBuff	,ImageBuffer &Target ,int dx,int dy);

	void	CalcShift(int MasterX1,int MasterY1,int Dx1,int Dy1
					 ,int MasterX2,int MasterY2,int Dx2,int Dy2
					 ,int &Mx,int &My
					 ,double K);
	void	MakeLineBuffer(ExecuteInitialAfterEditInfo &EInfo);

	bool	MakeMatchingPoints(ImageBuffer &Master);
	double	MatchByPoints(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);
	double	MatchByPointsSkipped(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy);

	bool	CheckCharactered(ImageBuffer &Master);
};

class	TriangleArea : public NPList<TriangleArea>
{
public:
	bool	Effective;

	XAlignmentLargePointerContainer		*Pa;
	XAlignmentLargePointerContainer		*Pb;
	XAlignmentLargePointerContainer		*Pc;

	double	Cax,Cay;	//Center of Pa
	double	Cbx,Cby;	//Center of Pb
	double	Ccx,Ccy;	//Center of Pc

	int					Dax,Day;
	int					Dbx,Dby;
	int					Dcx,Dcy;
	double				m[6];
	double				TotalCx,TotalCy;

	TriangleArea(void);
	void	GetCenter(double &Cx, double &Cy);
	double	GetRotation(void);
};

const	int		MaxGPackNumb=10000;

class   XAlignmentLargeArea : public NPList<XAlignmentLargeArea>
{
	bool	GroupMode;
	int		MaxSearchAreaFromItem;
  public:
	int				LibID	;

    int32           AreaID;
    FlexArea        Area;
	QString			AreaName;
	int32			MasterNo;
	TriangleArea	**NearestTriangleTableDim;
	int				NearestTriangleTableXRes;
	int				NearestTriangleTableYRes;
	int				NearestTriangleTableXNumb;
	int				NearestTriangleTableYNumb;

	XAlignmentLargePointerContainer		GPack;
    XAlignmentLargePointerContainer		*GPackClass;
	int									GPackClassNumb;
	AlignmentLargeShiftContainer		OtherPack;
	NPListPack<TriangleArea>			TriangleContainer;

	enum	AlignmentLargePointCount
	{
		_Aligned0
		,_Aligned1
		,_Aligned2
		,_Aligned3
		,_Aligned4
	}ResultPointCounts;
	AlgorithmLibraryListContainer	LimitedLib;
    int32			PartsID;			//ïîïiî‘çÜ		ñ≥ê›íËéû -1
    int32			PartsAllocID;       //ïîïiîzíuÇhÇc
	int32			PartsAreaID;
	bool			Locked;
	bool			Selected;
	bool			Active;
	bool			Visible;
	bool			ManualCreated;
	bool			MultiSelection;
	AlgorithmBase	*Origin;
	enum _EnumPriority{
		_PriorityNone		=-1
		,_PriorityHigh		=1
		,_PriorityMiddle	=2
		,_PriorityLow		=3
		,_PriorityGlobal	=4
	}Priority;
 
	int		ALResultNumb;
	int		ALResultAllocatedNumb;
	class	AlignmentLargeResultClass
	{
	public:
		double			AlignmentLargeResult[6];
		int				Cx,Cy;

		AlignmentLargeResultClass(void){	Cx=0;	Cy=0;	}
		AlignmentLargeResultClass	&operator=(AlignmentLargeResultClass &src);
	}*ALResult;
	double	ALRotation;

	AlignmentLargeInLayer	*ParentInLayer;
	XAlignmentLargeArea		*DependingGlobal;	//Index for Global area, This may be another layer's area

	RectClassContainer	GenerationAreas;

    XAlignmentLargeArea(void);
	XAlignmentLargeArea(AlignmentLargeInLayer	*parentInLayer);
	~XAlignmentLargeArea(void);

	int	GetPage(void);
	int	GetLayer(void);
	int	GetID(void)							{	return AreaID;	}
	void	SetOrigin(AlgorithmBase *ABase)	{	Origin=ABase;	}
	const	FlexArea	&GetArea(void)	const	{	return Area;	}
	AlignmentLargeBase	*GetParentBase(void);

    XAlignmentLargeArea  &operator=(const XAlignmentLargeArea &src);
    XAlignmentLargeArea  &CopyWithoutItems(const XAlignmentLargeArea &src,bool ReferedMode);
    void    MoveTo(int dx ,int dy);
    void    Initial(ImageBuffer &IData);
	bool	IsInclude(int x ,int y)	{	return(Area.IsInclude(x,y));	}
	bool	IsCrossed(FlexArea *b)	{	return(Area.CheckOverlap(b));	}
	bool	IsEffective(void)		{	return (GPack.GetFirst()!=NULL)?true:false;	}
	bool    GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	{	return Area.GetXY(x1,y1,x2,y2);	}
	void	SetGroup(FlexArea &area ,int groupNumber);
	AlignmentLargePointCount	GetResultInPoint(int localX ,int localY);
	double	GetClosedResultInPoint(int localX ,int localY);
	bool	GetAlignment(AlignmentPacket2D &AData);
	bool	GetAlignmentByHandle(AlignmentPacket2D &AData ,void *Handle);
	virtual	void		RemoveItem(AlgorithmItemPLI *item);
	int		GetItemCount(void);

	virtual	void	SetMultiSelection(bool b){	MultiSelection=b;	}
	virtual	bool	GetMultiSelection(void)	{	return MultiSelection;	}
	virtual	void	GetMultiSelectOrign(int &cx ,int &cy);

    void    GetCenter(int &cx, int &cy);
	void	Calc(ImageBuffer &TargetData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	void	CalcAllocateOnly(ImageBuffer &TargetData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	int		GetCalcedItemCount(void);
	bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteStartByInspection(void);
	bool	ReqOtherAlignmentLarge(void);
	void	MoveForAlignment(void);

	XAlignmentLarge	*GetItemInPriority(int priority);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file ,AlignmentLargeInLayer *parent);
    bool    SaveUnique(QIODevice *file);
    bool    LoadUnique(QIODevice *file);
	bool    Transform(TransformBase &Param);

	DataInPage	*GetDataInPage(void);
	virtual	void	Draw	 (QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove (int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);

	int		GetGPackClassNumber(XAlignmentLargePointerContainer *p);
	void	MatchCombination(ImageBuffer &TargetData ,ImageBuffer &TRTargetData);
	void	AutoCreatePointInEdge(int AlignmntPointSize
							,int AlignmntSearchAreaDotX	,int AlignmntSearchAreaDotY
							,int AlignmntSearchAreaDot2X,int AlignmntSearchAreaDot2Y
							,int LimitedLibType ,int LimitedLibID
							,bool AlignmntJudgeWithBrDif);
	void	AutoCreatePointInInside(int AlignmntPointSize
							,int AlignmntSearchAreaDotX	,int AlignmntSearchAreaDotY
							,int AlignmntSearchAreaDot2X,int AlignmntSearchAreaDot2Y
							,int LimitedLibType ,int LimitedLibID
							,bool AlignmntJudgeWithBrDif);
private:
	bool	Calc0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	Calc1(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	Index=0);
	bool	Calc2(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	IndexA=0	,int	IndexB=1);
	bool	Calc3(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	CalcAllocateOnly0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	CalcAllocateOnly1(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	Index=0);
	bool	CalcAllocateOnly2(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes
				,int	IndexA=0	,int	IndexB=1);
	bool	CalcAllocateOnly3(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	int	SelectAlignmentPoint(struct AlignmentLargeShiftItemListStruct BestMatch[10]);
	int	SelectAlignmentPoint2(struct AlignmentLargeShiftItemListStruct RetBestMatch[10]
							 , int NA ,struct AlignmentLargeShiftItemListStruct BestMatchA[3]
							 , int NB ,struct AlignmentLargeShiftItemListStruct BestMatchB[3]);
	int	SelectAlignmentPoint3(struct AlignmentLargeShiftItemListStruct RetBestMatch[10]
							, int NA ,struct AlignmentLargeShiftItemListStruct BestMatchA[3]
							, int NB ,struct AlignmentLargeShiftItemListStruct BestMatchB[3]
							, int NC ,struct AlignmentLargeShiftItemListStruct BestMatchC[3]);

	TriangleArea	*GetNearestTriangle(int x ,int y);
	TriangleArea	*GetNearestTriangleInTable(int x ,int y);
	void	MatchCombination(XAlignmentLargePointerContainer &Combinations,ImageBuffer &TargetData,ImageBuffer &TRTargetData);

	bool	FindClosedPoint(BYTE **BmpMap ,int Xlen ,int YLen
											,int Cx, int Cy
											,int &RetX ,int &RetY);
	bool	SearchAroundCorner(int AlignmntPointSize ,int AlignmntSearchAreaDot
							,int X,int Y
							,bool t1 ,bool t2 ,bool t3 ,bool t4
							,int &RetX ,int &RetY);
	bool	CheckCorner(int AlignmntPointSize
						,int X,int Y 
						,bool t1 ,bool t2 ,bool t3 ,bool t4);
public:
	bool	GenerateAuto(void);
	bool	GenerateAuto(FlexArea &GArea,int &RetLayer ,FlexArea &RetArea,FlexArea &AllMaskArea);
	bool	GenerateAutoAddItem(int &tLayer ,FlexArea &tArea);
};

class   AlignmentLargeInLayer : public AlgorithmInLayerPLI
{
  public:
    NPListPack<XAlignmentLargeArea>  Areas;				//Area statement
    NPListPack<XAlignmentLargeArea>  DispatchAreas;       //Area statement

    QPoint      *MVector;
    int         MVectorXNumb;
    int         MVectorYNumb;
    int         MVectorXRes;
    int         MVectorYRes;

	double ResultShiftX,ResultShiftY;	//ïΩçsà⁄ìÆó 
	double ResultAngle;					//Radian
	double ResultExtend;				//ägëÂó¶

  public:
    double  GCalcA[6];
    double  GCalcAr[6];

  public:
    AlignmentLargeInLayer(AlgorithmInPageRoot *parent);
    ~AlignmentLargeInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)		override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item)	override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override{	return AlgorithmInLayerPLI::AppendItem(item ,itemID);	}
	virtual	void				AppendItemWithoutMakeArea(AlgorithmItemRoot *item ,int AreaID);
	virtual	bool				AppendItemFromLoad(AlgorithmItemRoot *item)	override;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;

	virtual	void	Draw	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawItem(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	RemoveItem(AlgorithmItemRoot *item)	override;
	void	RemoveArea(XAlignmentLargeArea *a);
	XAlignmentLargeArea	*GetAlignmentLargeArea(int AreaID);
	XAlignmentLargeArea	*FindAlignmentLargeAreaByPriority(XAlignmentLargeArea::_EnumPriority Priority);

	void	UndoAppendManualArea(QIODevice *f);
	void	UndoAddPutManualArea(QIODevice *f);
	void	UndoAppendManualPoint(QIODevice *f);
	void	UndoExecuteMoveArea	(QIODevice *f);
	void	UndoExecuteCutArea	(QIODevice *f);
	void	UndoCutArea			(QIODevice *f);
	void	UndoCutPoint		(QIODevice *f);

	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override;
	virtual	void	InitializeFromParts(void)					override;
	virtual	void	CopyItemsFormDispatcherForParts(void)		override;
	virtual	void	RemoveItemFormDispatcher(void)				override;
	virtual	void	RemoveAllDatas(void)						override;

	virtual	void	Release(void)	override;
	void	MakeArea(PureFlexAreaListContainer &FPack
					, AlignmentLargeLibrary *Lib
					,AlgorithmBase *Origin);

    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file)	override;
	virtual	bool    LoadByTransform(QIODevice *f ,TransformBase &Param)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	QPoint	*GetPoint(int rx ,int ry);
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	override;

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreAlignment0	(int ExeID ,ResultInLayerRoot *Res);
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	void	MoveForAlignment(void)	override;

	void    CleanupItems(void);
    bool    ClearAll(void);
	void    InitializeFromImage(ImageBuffer &IBuff);

	XAlignmentLarge	*GetAlignmentLarge(int index);
	bool	GetAlignment(AlignmentPacket2D &AData);
    void    GetResultVectorXY(int rx ,int ry ,int &kx ,int &ky);
	int     GetAlignmentLargeNumb(void);

	int		GetAlignmentLargeAreaCount(void){	return Areas.GetCount();	}

	bool	BuildGlobalIndex(void);
	virtual	void	CopyFrom(AlgorithmInPageRoot *DestParent
							,AlgorithmInLayerRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)	override;

	bool	IsModeItemEditing(void);
	bool	IsModeAreaEditing(void);

	virtual	int		GetSelectedItemCount(void)										override;
	virtual	void	ReleaseAllSelectedItem(void)									override;
	virtual	void	SelectAll(void)													override;
	virtual	void	SelectLocked(void)												override;
	virtual	void	SelectLibs(AlgorithmLibraryListContainer &SelectedList)			override;
	virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect)				override;
	virtual	void	SelectPoint(int localX, int localY)								override;
	virtual	void	CutArea(FlexArea &localArea ,bool MultiSelect,const QByteArray &Something=QByteArray())	override;
			void	CutArea(FlexArea &localArea ,const IntList &AreaIDList,bool MultiSelect);
	virtual	void	RegistArea(FlexArea &localArea)									override;
	virtual	void	DeleteSelectedItems(void)										override;
	virtual	void	LockSelectedItems(void)											override;
	virtual	void	BindSelectedItems(void)											override;
	virtual	void	Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)	override;
	virtual	void	Activate(int ItemID)											override;
	virtual	void	Inactivate(void)												override;

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack)							override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)		override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,IntList &Items ,bool AllItems=false)	override;

	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)		override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase)				override;
	virtual	void	VisibleAll(void)												override;
	virtual	void	InvisibleAll(void)												override;
	virtual	void	InvisibleSelected(void)											override;
	virtual	void	SelectManualCreature(void)										override;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)					override{}
	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f)		;
	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList)	override;

	bool	ExistArea(int localX,int localY);
	int		GetMaxAreaID(void);
	void	MoveFromPipe(GeneralPipeInfo &Info);

	void	MatchCombination(void);

	void	CreateAreaInMask(int Priority,int Erosion);
};


class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
{
public:
	XAlignmentLargeArea	*Area;
	AlignmentPacket2DList(void){	Area=NULL;	}
};

class   AlignmentLargeInPage : public AlgorithmInPagePLI
{
public:
	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;
	int		OffsetX,OffsetY;
	int		StartHeadX	,StartHeadY;
	int		CurrentHeadX,CurrentHeadY;
	int		HeadLayerNumb;
	short	**HeadXDim;
	short	**HeadYDim;
	enum _ShowingMode
	{
		 ShowingMode_AlignmentArea	=1
		,ShowingMode_AlignmentItem	=2
	}ShowingMode;

	AlignmentLargeInPage(AlgorithmBase *parent);
	~AlignmentLargeInPage(void);

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override	{	return(new AlignmentLargeInLayer(parent));	}
	AlignmentPacket2D	*AppendAlignmentLargePacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	void	GetAlignmentLarge(AlignmentPacket2D &AData);
	void	GetAlignmentLargeByHandle(AlignmentPacket2D &AData ,void *Handle);
	void	GetAlignmentLargeParam(double m[6]);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
										,FlexArea &area ,AlgorithmBase *OriginBase
										,int ItemClass) override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	bool	DrawResultItem(ResultInPageRoot *Res,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info)	override;

	void	TransformImage(ImagePointerContainer &Images);
private:
	bool	ExistArea(int localX,int localY);
	int		ExecuteHeadAlignmentX(ImagePointerContainer &Images);
	int		ExecuteHeadAlignmentY(ImagePointerContainer &Images);
};

class	AlignmentLargeBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points

	int16		DefaultThreshold;
	WORD		DefaultMoveDot;
	bool		DefaultAlignmentLargeOnOutline;
	int16		DefaultLayer;

	WORD		DefaultOutlineDivCount;
	WORD		DefaultOutlineWidth;

	bool		UseOtherPage;
	int			PointsToUseOtherPage;
	double		AdoptedMinD;
	int32		MaxSearchAreaFromItem;
	int			MinDiffBrightness;
	bool		MakeAreaInInitialAfterEdit;
	bool		UseBitBuff;
	int			TransparentLevelInBitBuff;
	int			SkipDotForRoughSearch;
	QColor		ColorPriorityHigh;
	QColor		ColorPriorityMiddle;
	QColor		ColorPriorityLow;
	QColor		ColorPriorityGlobal;
	bool		EnableMatchingByOutlineDetail;
	double		AdoptLineDiff;
	bool		Use3Lines;
	int			SkipOnMatchingLine;
	double		BrightnessVariery;
	bool		UseLinkThroughPhase;
	double		AlertThreshold;
	bool		UseAllLayers;
	bool		UseHeadAlignment	 ;
	int			MaxHeadAlignmentX	 ;
	int			MaxHeadAlignmentY	 ;
	int			SkipHeadAlignmentX	 ;
	int			SkipHeadAlignmentY	 ;
	int			HeadAlignmentDifColor;
	int			HeadAlignmentMinSize ;
	bool		DefaultUseHeadAlignment;
	int			DefaultMaxHeadAlignmentX;
	int			DefaultMaxHeadAlignmentY;
	int			DefaultSkipHeadAlignmentX;
	int			DefaultSkipHeadAlignmentY;
	int			DefaultHeadAlignmentDifColor;
	int			DefaultHeadAlignmentMinSize ;
	int			HeadAlignmentStep;
	int			MaxCountOfMatchingPoint;
	double		JudgeCharacterModeParam;
	int			SearchPointDot;

	int			AutoGenAreaSize;
	int			AutoGenItemSize;
	int			AutoGenSelfSearchArea;
	int			AutoGenMoveDotX ;
	int			AutoGenMoveDotY ;
	int			AutoGenMoveDotX2;
	int			AutoGenMoveDotY2;
	double		AutoGenMinVar;
	double		AutoGenNeighborMatch;
	int			AutoGenMinDistance;	//Between each items

	bool		NotExpandX;
	bool		NotExpandY;

	AlignmentLargeBase(LayersBase *Base);

	virtual	void	InitialAfterParamLoaded(void)	override;
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new AlignmentLargeInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)	override	{	return QString("AlignmentLarge");			}
	QString	GetDefaultFileName(void)	override	{	return QString("ConfigAlignmentLarge.dat");	}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
	virtual	QString	GetNameByCurrentLanguage(void)	override;

	virtual	bool	SaveOnlyBase(QIODevice *f)						override;
	virtual	bool	LoadOnlyBase(QIODevice *f,QString &ErrorMsg)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;
};

//=======================================================================================
#define	AlignmentLargeThresholdReqCommand	1
#define	AlignmentLargeThresholdSendCommand	2

//=======================================================================================

class	AlignmentLargeThresholdReq
{
public:
	struct{
		int32	GlobalPage;
		int32	Layer;
		int		AlignmentLargeItemID;
		int32	Dx,Dy;
	}Data;

	AlignmentLargeThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AlignmentLargeThresholdSend
{
public:
	struct ThresholdStruct
	{
		int16			SelectedLayer	;	//-1:Automatic select layer
		int16			ThresholdColor	;	//-1:Automatic colc threshold brightness		
	}ThresholdValues;

	AlignmentLargeThresholdSend(void);

	void	ConstructList(AlignmentLargeThresholdReq *reqPacket,AlignmentLargeBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//=======================================================================================
class	AddAlignmentLargeAreaPacket : public GUIDirectMessage
{
public:
	FlexArea		Area;
	int32			Page;
	int32			Layer;
	int32			MasterNo;
	QString			AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;
	int				GeneratedAreaID;

	AddAlignmentLargeAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentLargeAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddPutAlignmentLargeAreaPacket : public GUIDirectMessage
{
public:
	FlexArea		Area;
	int32			Page;
	int32			Layer;
	int32			MasterNo;
	QString			AreaName;
	XAlignmentLargeArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	AddPutAlignmentLargeAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddPutAlignmentLargeAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdAlignmentLargeReflectChangeItems : public GUIDirectMessage
{
public:
	GUICmdAlignmentLargeReflectChangeItems(LayersBase *base):GUIDirectMessage(base){}
	GUICmdAlignmentLargeReflectChangeItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentLargePointPacket : public GUIDirectMessage
{
public:
	IntList		AreaID;
	FlexArea	Area;
	WORD		Threshold;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		SearchAround;
	WORD		GroupNumber;
	bool		UsageGlobal;
	bool		AlignmentLargeOnOutline;
	bool		MultiSelect;
	bool		UseBitBuff;
	bool		JudgeWithBrDif;
	bool		AlignmentUseCharacterMode;
	bool		CharacterMode ;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness

	AddAlignmentLargePointPacket(LayersBase *base):GUIDirectMessage(base)			{	JudgeWithBrDif=true;	AlignmentUseCharacterMode=false;	}
	AddAlignmentLargePointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	JudgeWithBrDif=true;	AlignmentUseCharacterMode=false;	}
};
class	ModifyAlignmentLargePointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	int			ItemID;
	WORD		Threshold;
	WORD		MoveDotX;
	WORD		MoveDotY;
	WORD		MoveDotX2;
	WORD		MoveDotY2;
	WORD		SearchAround;
	bool		UsageGlobal;
	WORD		GroupNumber;
	bool		AlignmentLargeOnOutline;
	bool		JudgeWithBrDif;
	bool		CharacterMode ;
	int			UseLayer		;	//-1:Automatic select layer
	int			ThresholdColor	;	//-1:Automatic colc threshold brightness

	ModifyAlignmentLargePointPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyAlignmentLargePointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RemoveAlignmentLargePointPacket: public GUIDirectMessage
{
public:
	int			AreaID;
	int			ItemID;

	RemoveAlignmentLargePointPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveAlignmentLargePointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MakeAlignmentLargeGroupPacket : public GUIDirectMessage
{
public:
	int	Cmd;

	MakeAlignmentLargeGroupPacket(LayersBase *base):GUIDirectMessage(base){}
	MakeAlignmentLargeGroupPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	RemoveAlignmentLargeGroupPacket : public GUIDirectMessage
{
public:

	RemoveAlignmentLargeGroupPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveAlignmentLargeGroupPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RemoveAlignmentLargeAreaPacket : public GUIDirectMessage
{
public:
	int			AreaID;

	RemoveAlignmentLargeAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveAlignmentLargeAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RemoveSelectedAlignmentLargeAreaPacket : public GUIDirectMessage
{
public:
	RemoveSelectedAlignmentLargeAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveSelectedAlignmentLargeAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GetSelectedAlignmentLargeAreaPacket : public GUIDirectMessage
{
public:
	QByteArray	BuffData;

	GetSelectedAlignmentLargeAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	GetSelectedAlignmentLargeAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentLargeTransform : public GUIDirectMessage
{
public:
	bool	MasterImage;

	CmdReqAlignmentLargeTransform(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeTransform(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

	
class	CmdClearAllAreas : public GUIDirectMessage
{
public:
	CmdClearAllAreas(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAllAreas(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
	
class	CmdClearAllPoints : public GUIDirectMessage
{
public:
	int	Priority;

	CmdClearAllPoints(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAllPoints(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCreateAreaInMask : public GUIDirectMessage
{
public:
	int	Priority;
	int	Erosion;
	CmdCreateAreaInMask(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateAreaInMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqCutAreaWithPriority : public GUIDirectMessage
{
public:
	XAlignmentLargeArea::_EnumPriority	AreaPriority;
	FlexArea	AreaToCut;

	CmdReqCutAreaWithPriority(LayersBase *base):GUIDirectMessage(base){}
	CmdReqCutAreaWithPriority(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqCutPointWithPriority : public GUIDirectMessage
{
public:
	XAlignmentLargeArea::_EnumPriority	AreaPriority;
	FlexArea	AreaToCut;

	CmdReqCutPointWithPriority(LayersBase *base):GUIDirectMessage(base){}
	CmdReqCutPointWithPriority(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAreaPriority : public GUIDirectMessage
{
public:
	int32	ItemID;
	XAlignmentLargeArea::_EnumPriority	AreaPriority;

	CmdReqAreaPriority(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAreaPriority(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdAutoCreatePoint : public GUIDirectMessage
{
public:
	bool	GeneratePartialAlignment;
	int		AlignmntPointSize		;
	int		AlignmntSearchAreaDotX	;
	int		AlignmntSearchAreaDotY	;
	int		AlignmntSearchAreaDot2X	;
	int		AlignmntSearchAreaDot2Y	;
	int		Layer;
	int		AreaPriority;
	int		LimitedLibType;
	int		LimitedLibID;
	bool	AlignmntJudgeWithBrDif;

	CmdAutoCreatePoint(LayersBase *base):GUIDirectMessage(base){}
	CmdAutoCreatePoint(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	AddAlignmentMarkPacket :  public GUIDirectMessage
{
public:
	FlexArea	Area;
	int		Priority;
	int		MoveDotX;
	int		MoveDotY;
	int		MoveDotX2;
	int		MoveDotY2;
	int		SearchAround;
	int		GroupNumber;
	bool	UsageGlobal;
	bool	JudgeWithBrDif;
	bool	AlignmentUseCharacterMode;
	bool	CharacterMode;
	int		UseLayer		;	//-1:Automatic select layer
	int		ThresholdColor	;	//-1:Automatic colc threshold brightness
	ListPhasePageLayerItemPack		AreaIDList;

	AddAlignmentMarkPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentMarkPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};	
	
class	SelectAlignmentPoints : public GUIDirectMessage
{
public:
	FlexArea	Area;

	SelectAlignmentPoints(LayersBase *base):GUIDirectMessage(base){}
	SelectAlignmentPoints(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentLargeLibraryListInPastePacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAlignmentLargeLibraryListInPastePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentLargeLibraryListInPastePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAlignmentLargeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAlignmentLargeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAlignmentLargeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAlignmentLargeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentLargeLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAlignmentLargeLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentLargeLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempAlignmentLargeLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempAlignmentLargeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentLargeLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	int			AreaPriority;
	AlgorithmLibraryListContainer	AList;

	CmdGetAlignmentLargeLibraryListPacket(LayersBase *base):GUIDirectMessage(base)			{	AreaPriority=-1;	}
	CmdGetAlignmentLargeLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	AreaPriority=-1;	}
};

class	CmdLoadAlignmentLargeLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadAlignmentLargeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAlignmentLargeLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAlignmentLargeLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAlignmentLargeLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAlignmentLargeLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAlignmentLargeLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectItemsAlignmentLarge: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		AreaIDList;

	CmdSelectItemsAlignmentLarge(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectItemsAlignmentLarge(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdCutItemsAlignmentLarge: public GUIDirectMessage
{
public:
	FlexArea	Area;
	IntList		AreaIDList;

	CmdCutItemsAlignmentLarge(LayersBase *base):GUIDirectMessage(base){}
	CmdCutItemsAlignmentLarge(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdSelectAlignmentAreaByID: public GUIDirectMessage
{
public:
	int	AreaID;

	CmdSelectAlignmentAreaByID(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectAlignmentAreaByID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSelectAreaByArea: public GUIDirectMessage
{
public:
	FlexArea	Area;
	bool		MultiSelect;

	CmdSelectAreaByArea(LayersBase *base):GUIDirectMessage(base){}
	CmdSelectAreaByArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdCreateAlignmentLargeThreshold : public GUIDirectMessage
{
public:
	XAlignmentLarge			*Item;		//Should be deleted
	AlignmentLargeThreshold	*Threshold;	//Should be deleted

	CmdCreateAlignmentLargeThreshold(LayersBase *base):GUIDirectMessage(base){	Item=NULL;	Threshold=NULL;	}
	CmdCreateAlignmentLargeThreshold(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
	~CmdCreateAlignmentLargeThreshold(void){	delete	Item;	delete	Threshold;	}
};

class	CmdReqAlignmentLargeFinalResult : public GUIDirectMessage
{
public:
	XAlignmentLarge			*Item;
	struct	AlignmentLargeShiftItemListStruct	*FinalResult;

	CmdReqAlignmentLargeFinalResult(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentLargeFinalResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdFindAlignmentLargeArea : public GUIDirectMessage
{
public:
	int	AreaID;
	XAlignmentLargeArea	*Area;
	CmdFindAlignmentLargeArea(LayersBase *base):GUIDirectMessage(base){}
	CmdFindAlignmentLargeArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetFirstAlignmentArea: public GUIDirectMessage
{
public:
	int	AreaID;
	FlexArea	Area;

	CmdGetFirstAlignmentArea(LayersBase *base):GUIDirectMessage(base){}
	CmdGetFirstAlignmentArea(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAlignmentData : public GUIDirectMessage
{
public:
	QByteArray	AlignData;

	CmdSetAlignmentData(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAlignmentData(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqDelAlignmentAreaByName : public GUIDirectMessage
{
public:
    QString			AreaName;

	CmdReqDelAlignmentAreaByName(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqDelAlignmentAreaByName(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdGenerateAuto: public GUIDirectMessage
{
public:
	int	AreaID;
	int	Layer;

	CmdGenerateAuto(LayersBase *base):GUIDirectMessage(base)			{}
	CmdGenerateAuto(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdAutoGenerateMark: public GUIDirectMessage
{
public:
	ListPhasePageLayerItemPack		AreaIDList;

	CmdAutoGenerateMark(LayersBase *base):GUIDirectMessage(base)			{}
	CmdAutoGenerateMark(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

#endif

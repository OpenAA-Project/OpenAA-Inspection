/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AlignmentFlexArea\XAlignmentFlexArea.h
** Author : YYYYYYYYYY
****************************************************************************-**/



#ifndef XAlignmentFlexAreaH
#define XAlignmentFlexAreaH

#include <QIODevice>
#include <QPoint>
#include <QString>
#include "XFlexAreaImage.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
//#include "XPacketAlignmentFlexArea.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XAlignmentFlexAreaLibrary.h"
#include "XStandardCommand.h"

#define	AlignmentFlexAreaVersion	2

class	AlignmentFlexAreaItem;
class	AlignmentGroup;
class	XAlignmentFlexAreaArea;
class	AlignmentFlexAreaInPage;
class	AlignmentFlexAreaBase;
class	SetThresholdAlignmentFlexAreaInfo;
class	ExecuteInitialAfterEditInfo;

class	AlignmentFlexAreaThreshold : public AlgorithmThreshold
{
public:
	WORD		TargetLayer;
	WORD		GlobalSearchDot	;
	WORD		SearchDot		;
	double		CloserRate;		//0-0.2
	int32		SmallSearch;
	bool		KeepBW;			//Keep black/white side in target image

	AlignmentFlexAreaThreshold(AlignmentFlexAreaItem *parent);
	~AlignmentFlexAreaThreshold(void);

	virtual	void	RegistHist(void)	override;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};


struct	AlignmentFlexAreaShiftListStruct
{
	int		Dx,Dy;
	double	Match;
};

struct	AlignmentFlexAreaShiftListIndexStruct
{
	int		Dx,Dy;
	int		Index;
	double	Match;
};

struct	AlignmentFlexAreaShiftItemListStruct
{
	int		Dx,Dy;
	double	Match;
	bool	Adopted;
	AlignmentGroup	*Item;

	AlignmentFlexAreaShiftItemListStruct(void){	Item=NULL;	}
};

#define	Hist_AlighmentLargeShiftX	1
#define	Hist_AlighmentLargeShiftY	2
#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12


class	AlignmentTransArea : public FlexAreaImageListCoeff
{
public:
	int	ConnectionID;
	enum LocationInfo{
		_LI_LeftTop
		,_LI_RightTop
		,_LI_LeftBottom
		,_LI_RightBottom
	};
	LocationInfo	LocInfo;

	AlignmentTransArea(void);
	AlignmentTransArea(AlignmentTransArea &src){	ConnectionID=src.ConnectionID;	LocInfo=src.LocInfo;	}

	AlignmentTransArea	&operator=(PureFlexAreaList &src);
	AlignmentTransArea	&operator=(const AlignmentTransArea &src);
};

struct	AlignmentMatchList
{
	double	MatchRate;
	int		Index;
	int		Number;
};

#define	AlignmentFlexAreaNormalLine	1

class   AlignmentFlexAreaItem : public AlgorithmItemPI
{
public:

	class	AlignmentVLine
	{
	public:
		bool	BitCalc;
		bool	Effective;
		int		AddedS;
		int		AddedSS;
		int		VLineX,VLineY1,VLineY2;
		BYTE	*VDot;
	
		AlignmentVLine(void);
		~AlignmentVLine(void);
	
		AlignmentVLine	&operator=(const AlignmentVLine &src);
		bool	Allocate(void);
		void	Release(void);
		bool	MakeDot(FlexArea &Area ,ImageBuffer &MasterBuff ,ImageBuffer &Buff ,int Expand);
		void	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
		bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
		void	Move(int Dx ,int Dy);
		bool    Save(QIODevice *file);
	    bool    Load(QIODevice *file);
	
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
	};
	
	class	AlignmentHLine
	{
	public:
		bool	BitCalc;
		bool	Effective;
		int		AddedS;
		int		AddedSS;
		int		HLineX1,HLineX2,HLineY;
		BYTE	*HDot;
	
		AlignmentHLine(void);
		~AlignmentHLine(void);
	
		AlignmentHLine	&operator=(const AlignmentHLine &src);
		bool	Allocate(void);
		void	Release(void);
		void	Move(int Dx ,int Dy);
		bool	MakeDot(FlexArea &Area ,ImageBuffer &MasterBuff ,ImageBuffer &Buff ,int Expand);
		void	MatchCross(ImageBuffer &Target ,int dx,int dy
							,int &AddedD 
							,int &AddedDD
							,int &AddedSD
							,int &SDCount);
		void	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
		bool	InArea(int dx,int dy,int x1,int y1 ,int x2 ,int y2);
		bool    Save(QIODevice *file);
	    bool    Load(QIODevice *file);
	
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);
	};

	FlexAreaImageListCoeffContainer	TransArea;
	class	VHLine
	{
	public:
		AlignmentVLine	VLine;
		AlignmentHLine	HLine;
	};
	VHLine	VHDim[3];	// 0:smaller	1:normal	2:bigger
	bool	Alive;
	bool	BitCalc;
public:
	bool		GeneratedFromBitMap;
	double		MasterX,MasterY;
	int			ShiftByGlobalX,ShiftByGlobalY;
	double      ResultDx,ResultDy;	//Calculated position
	WORD		AreaID;
	int32		GroupID;

	AlignmentMatchList	*MatchList;
	int					MatchListNumb;

	XAlignmentFlexAreaArea	*ParentArea;
	AlignmentGroup			*ParentGroup;

	AlignmentFlexAreaItem(void);
	~AlignmentFlexAreaItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AlignmentFlexAreaItem();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY) override;

    void    MoveTo(int dx ,int dy) override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	 override;
    AlignmentFlexAreaItem &operator=(const AlignmentFlexAreaItem &src);

	const	AlignmentFlexAreaThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const AlignmentFlexAreaThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentFlexAreaThreshold			*GetThresholdW(LayersBase *base=NULL){	return (AlignmentFlexAreaThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	 override	{	return new AlignmentFlexAreaThreshold(this);	}
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	 override;

    void    Clear(void);
    bool    Save(QIODevice *file) override;
    bool    Load(QIODevice *file,LayersBase *LBase) override;

	bool	IsAreaEffective(void);
	bool    MakeArea(bool ReCalcBitMask=true,ImageBuffer *specialData=NULL);

	int		GetMx(void){	return(ResultDx);	}
	int		GetMy(void){	return(ResultDy);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

	void	CopyThresholdOnly(AlignmentFlexAreaItem *src);
	void	GetGlobalShift(int &mx,int &my);
	double	TransAreaCalcCoeff(int dx ,int dy, ImageBuffer &Target);

	virtual	bool	GetVisible(void)	override;
	virtual	void	CutArea(FlexArea &localArea,bool &_Changed)	override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	 override;
	void	CalcResultWithoutGroupID(void);
	void	SetThresholdFromCommon(SetThresholdAlignmentFlexAreaInfo *Info);

	double	AdjustByLength(double d ,int dx ,int dy);
	void	ExecuteSmallSearch(ImagePointerContainer &Images,ImagePointerContainer &TRImages);
public:
	//bool	MakeAreaByManual(void);
	double	GetThreshLevel(ImagePointerContainer &Images ,int dx=0 ,int dy=0);
	double	MatchCross(ImageBuffer &Target ,ImageBuffer &TRTarget
						,int dx,int dy,int N
						,int DotPerLine,int MaxLines);
	bool	IsImageChanged(void);
};

const	int		AlignmentFlexArea_MaxGPackNumb=100;

class	AlignmentGroup : public NPList<AlignmentGroup>
{
	AlignmentFlexAreaInPage		*ParentInPage;
	XAlignmentFlexAreaArea		*ParentArea;

	struct	AlignmentFlexAreaShiftListIndexStruct	*ShiftList;
	int		ShiftListNumb;

	struct	AlignmentFlexAreaShiftListIndexStruct	*SortedList;
	int		SortedListNumb;
	int		AllocSortedListNumb;

	struct	AlignmentMatchList	*MatchList;
	double	*DList;
	int		*IList;
public:
	int	GroupID;
	AlgorithmItemPointerListContainer	ItemPack;
	int		MinX,MinY,MaxX,MaxY;

	struct	AlignmentFlexAreaShiftItemListStruct	BestMatch[3];
	int		CountOfBestMatch;
	int		AdoptedIndex;

	int		CenterX,CenterY;
	int		ResultDx,ResultDy;
	int		GlobalShiftX,GlobalShiftY;

	AlignmentGroup(XAlignmentFlexAreaArea *p);
	~AlignmentGroup(void);

	AlignmentGroup	&operator=(const AlignmentGroup &src);
	void	MakeShiftList(void);

	bool	AddItem(AlgorithmItemRoot *Item ,int GroupAreaSize);
	bool	AppendItem(AlgorithmItemRoot *Item);
	void	CalcCenter(void);
	void	GetCenter(int &Cx ,int &Cy);
	bool	IsInclude(int x ,int y);
	bool	HasItem(void);

	void	ExecuteStartByInspection(void);
	void	CalcAlignment(ImagePointerContainer &Images ,ImagePointerContainer &TRImages,int offsetX,int offsetY);
	double	GetMaxMatchByMaster(ImagePointerContainer &Images ,ImagePointerContainer &TRImages ,int dx,int dy);
	double	GetMinMatchByMaster(ImagePointerContainer &Images ,ImagePointerContainer &TRImages ,int dx,int dy);

	void	SetShiftByGlobal(void);
	void	SetShiftByGlobal(int dx ,int dy);
	void	SetAdoptedIndex(int index);
	void	DeleteSelectedItems(void);
	void	ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems);
	void	Draw(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
private:
	double	TransAreaCalcCoeff(int dx,int dy,ImagePointerContainer &Images );
};

class	IndexForGroup
{
public:
	int				ID;
	int				AreaID;
	AlignmentGroup	*Index[3];
	double	m[6];

	IndexForGroup(int id,int AreaID);

	double	GetDistance(int cx,int cy);
	void	MinimizeTransformation(double CutRate);
	bool	CheckEqual(AlignmentGroup *g1,AlignmentGroup *g2,AlignmentGroup *g3);
	void	CalcParameter(void);
	void	CalcPosition(int x, int y, int &ResX ,int &ResY);
	void	CalcShift(int x, int y, int &ShiftX ,int &ShiftY);
	double	GetRotation(void);
};

class	AlignmentGroupList : public NPList<AlignmentGroupList>
{
public:
	AlignmentGroup	*Point;
	bool			Effective;

	AlignmentGroupList(AlignmentGroup *group){	Point=group;	Effective=true;	}
};

class	IndexForGroupList : public NPList<IndexForGroupList>,public IndexForGroup
{
public:
	IndexForGroupList(int id,int _AreaID):IndexForGroup(id,_AreaID){}
};

class   XAlignmentFlexAreaArea : public NPList<XAlignmentFlexAreaArea>
{
	friend	class   AlignmentFlexAreaInPage;

	BYTE	**TestMap;
	int		MapXByte;
	int		MapXLen;
	int		MapYLen;

	NPListPack<IndexForGroupList>	MVectorList;
    IndexForGroup	**MVector;
    int         MVectorXNumb;
    int         MVectorYNumb;
    int         MVectorXRes;
    int         MVectorYRes;

	NPListPack<IndexForGroupList>	IndexForGroupListContainer;	//For selecting BestMatch combination

  public:
	int		MaxSearchAreaFromItem;
	NPListPack<AlignmentGroup>			GroupPack;		//This is generated in ExecuteInitialAfterEdit

	int32				AreaID;
    FlexArea			Area;
	QString				AreaName;

	AlgorithmLibraryListContainer	LimitedLib;
	AlgorithmLibraryListContainer	LibToCreateItems;

    int32				PartsID;			//ïîïiî‘çÜ		ñ≥ê›íËéû -1
    int32				PartsAllocID;       //ïîïiîzíuÇhÇc
	int32				PartsAreaID;
	bool				Locked;
	bool				Selected;
	bool				Active;
	bool				Visible;
	bool				ManualCreated;
	AlgorithmBase		*Origin;
	enum _EnumPriority{
		_PriorityHigh		=1
		,_PriorityMiddle	=2
		,_PriorityLow		=3
		,_PriorityGlobal	=4
	}Priority;

	AlignmentFlexAreaInPage		*ParentInPage;

    XAlignmentFlexAreaArea(void);
	XAlignmentFlexAreaArea(AlignmentFlexAreaInPage	*parentInPage);
	~XAlignmentFlexAreaArea(void);

	AlignmentFlexAreaBase	*GetParentBase(void);
	int	GetPage(void);
	int	GetID(void)		{	return AreaID;	}
	void	AllocateTestMap(void);
	int		GetItemCount(void);
	bool	HasItems(void);

    XAlignmentFlexAreaArea  &operator=(const XAlignmentFlexAreaArea &src);
    XAlignmentFlexAreaArea  &CopyWithoutItems(const XAlignmentFlexAreaArea &src,bool ReferedMode);
    void    MoveTo(int dx ,int dy);
	bool	IsInclude(int x ,int y)	{	return(Area.IsInclude(x,y));	}
	bool	IsCrossed(FlexArea *b)	{	return(Area.CheckOverlap(b));	}
	bool    GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	{	return Area.GetXY(x1,y1,x2,y2);	}

	double	GetClosedResultInPoint(int localX ,int localY);
	void	DeleteAllItemsFromParent(void);
	void	DeleteSelectedItems(void);
	void	ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems);

    void    GetCenter(int &cx, int &cy);

	bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	bool	BuildGroupPack(void);
	bool	RemoveRepeatableGroup(void);
	bool	ExecuteStartByInspection(void);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file ,AlignmentFlexAreaInPage *parent);
    bool    SaveUnique(QIODevice *file);
    bool    LoadUnique(QIODevice *file);

	virtual	void	Draw	 (QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove (int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);
	virtual	void	DrawGroup(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	bool	CalcAlignment(ImagePointerContainer &Images ,ImagePointerContainer &TRImages,int offsetx=0,int offsety=0);
	void	SetShiftByGlobal(void);
	void	SetShiftByGlobal(int dx ,int dy);

	bool	MakeAlignment(QPoint *MVector
						, int MVectorXNumb
						, int MVectorYNumb
						, int MVectorXRes
						, int MVectorYRes);

	bool	TestByLibID			(ImagePointerContainer &ImageList ,IntList &LibList);
	bool	GenerateByLibID		(ImagePointerContainer &ImageList ,IntList &LibList);
	bool	GenerateFromMap		(BYTE **BmpMap,int BmpXByte ,int BmpYLen 
								,int LibID
								,OriginType OType
								,AlgorithmBase *Origin
								,int offsetx ,int offsety);
	void	ClearTestMap		(void);
	IndexForGroupList	*GetClosedIndexGroup(int XPos,int YPos);
private:

};


class	WholeMatch
{
	int		SearchListNumb;
	struct	AlignmentFlexAreaShiftListStruct		*SearchList;
	struct	AlignmentFlexAreaShiftListStruct		*SearchSortList;
	struct	AlignmentFlexAreaShiftListIndexStruct	*SearchDetailList;
	int								SearchDetailListNumb;
public:
	AlignmentFlexAreaInPage	*ParentInPage;
public:
	class	SImage
	{
		WholeMatch	*ParentWholeMatch;
	public:
		int		SImageNo;
		int		Division;
		int		SearchDot;
		int		PageNumb;
		XYClass	*SPageOffset;
		BYTE	**STargetImage;	//Shrinked
		int		SDotPerLine;
		int		SMaxLines;
		FlexAreaImageListCoeff	SArea;
		FlexAreaImageListCoeff	*SWholeArea;

		double	A,AA;
		int		ANumb;

		SImage(int n ,WholeMatch *p,int division ,int searchdot);
		~SImage(void);

		void	Release(void);
		bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
		bool	MakeSWholeArea(void);
		void	CalcOwn(void);
		void	MakeTargetImage(void);
		double	CalcMatch(int dx ,int dy);

		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

		FlexArea	&GetSArea(void)	{	return SArea;	}
		LayersBase	*GetLayersBase(void);
	private:
		int		GetAverage(FlexArea &mArea);
		int		GetObviousPixel(FlexArea &mArea,int AvrC);
		void	Thinning(FlexArea &SArea,int gXNumb,int gYNumb);
	};
	SImage	*SImageInfo[2];
	int		SImageNumb;
	int		Layer;

	WholeMatch(AlignmentFlexAreaInPage *p);
	~WholeMatch(void);

	bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteWholeMatch(int &ResultShiftX,int &ResultShiftY);
	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);

	LayersBase	*GetLayersBase(void);

	void	GetMasterImages(ImagePointerContainer &Images);
	void	GetTargetImages(ImagePointerContainer &Images);

private:
	void	AllocSearchDetailList(void);
	
};

class	PointListForGroupIndex
{
public:
	IndexForGroup	*Global;
	IndexForGroup	*Plain;
	QPoint	Vector;
	double	Rotation;

	PointListForGroupIndex(void):Global(NULL),Plain(NULL){	Rotation=0;	}
};

class   AlignmentFlexAreaInPage : public AlgorithmInPagePI
{
	friend	class	XAlignmentFlexAreaArea;

    PointListForGroupIndex      *MVector;
    int         MVectorXNumb;
    int         MVectorYNumb;
    int         MVectorXRes;
    int         MVectorYRes;
	bool		HasDataInBitBuffAttr;
	bool		RecalcMode;
public:
	class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
	{
	public:
		XAlignmentFlexAreaArea	*Area;
		AlignmentGroup			*OnTheGroup;
		AlignmentPacket2DList(void){	Area=NULL;	OnTheGroup=NULL;	}
	};

	NPListPack<XAlignmentFlexAreaArea>  Areas;				//Area statement
    NPListPack<XAlignmentFlexAreaArea>  DispatchAreas;       //Area statement
	IntList		CurrentSelectedAreaID;
	bool		ModeShowArea;
public:
	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	*AlignmentPacket2DContainer;
	int			AlignmentPacket2DContainerXNumb;
	int			AlignmentPacket2DContainerYNumb;
	int			AlignmentPacket2DContainerXRes;
	int			AlignmentPacket2DContainerYRes;
	WholeMatch	WholeMatchData;
	int			ResultWholeMatchDx,ResultWholeMatchDy;

	AlignmentFlexAreaInPage(AlgorithmBase *parent);
	~AlignmentFlexAreaInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType) override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item) override;
	AlignmentPacket2D	*AppendAlignmentFlexAreaPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY ,bool FromGlobal);
	virtual	void	RemoveItem(AlgorithmItemRoot *item) override;

	void	GenerateAreaWithItemLibFromMask(int Priority ,int ItemLibID);

	XAlignmentFlexAreaArea	*GetAlignmentFlexAreaArea(int AreaID);
	int						GetAlignmentFlexAreaCount(void);
	void	RemoveArea(XAlignmentFlexAreaArea *a);
	virtual	bool		Save(QIODevice *f) override;
	virtual	bool		Load(QIODevice *f) override;

	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,ResultInPageRoot *Res) override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res) override;

	bool	GetAlignmentFlexAreaGlobal(AlignmentPacket2D &Point);
	bool	GetAlignmentFlexArea(AlignmentPacket2D &Point);
	IndexForGroup	*GetAlignmentFlexAreaGlobalIndex(AlignmentPacket2D &Point);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
										,FlexArea &area ,AlgorithmBase *OriginBase
										,int ItemClass) override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	bool	PipeGeneration(GeneralPipeInfo &Info) override;

	virtual	void	UndoSetIndependentItemDataCommand(QIODevice *f);
	int		GetMaxAreaID(void);
	void	UndoAppendManualArea(QIODevice *f);
	bool	UseLibraryForMaskingInOtherPage(int LibID);

	bool	IsModeItemEditing(void);
	bool	IsModeAreaEditing(void);

	virtual	int		GetSelectedItemCount(void)	 override									;
	virtual	void	ReleaseAllSelectedItem(void) override												;
	virtual	void	SelectAll(const IntList &LayerList)	 override												;
	virtual	void	SelectLocked(const IntList &LayerList)	 override											;
	virtual	void	SelectLibs(SelectLibListContainer &SelectedList)	override		;
	virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect)	override		;
	virtual	void	SelectPoint(int localX, int localY)					override		;
	virtual	void	CutArea(FlexArea &localArea ,const IntList &LayerList ,bool MultiSelect,const QByteArray &Something=QByteArray())	 override								;
	virtual	void	RegistArea(FlexArea &localArea ,const IntList &LayerList)	 override								;
	virtual	void	DeleteSelectedItems(const IntList &LayerList)	 override				;
	virtual	void	LockSelectedItems(const IntList &LayerList)	 override										;
	virtual	void	BindSelectedItems(const IntList &LayerList)	 override										;
	virtual	void	Activate(int localX ,int localY ,IntList &LayerList,ListLayerAndIDPack &RetItem) override	;
	virtual	void	Activate(int Layer ,int ItemID)	 override										;
	virtual	void	Inactivate(void) override												;

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList) override							;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false) override		;

	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList,const IntList &LayerList) override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase,const IntList &LayerList) override		;
	virtual	void	VisibleAll(const IntList &LayerList) override			;
	virtual	void	InvisibleAll(const IntList &LayerList) override			;
	virtual	void	InvisibleSelected(const IntList &LayerList)	 override	;
	virtual	void	SelectManualCreature(const IntList &LayerList) override	;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my) override{}
	void	MoveFromPipe(GeneralPipeInfo &Info);

	void	GetMasterBuffForMakeArea(bool ReCalcBitMask ,ImagePointerContainer &ImageList);
	int		GetCurrentAreaID(void);

private:
	bool	ExistArea(int localX,int localY);
	bool	GetItemAreas(int LibID , int AreaID , FlexArea &SrcArea ,PureFlexAreaListContainer &ItemArea);
	double	GetThreshLevel(AlgorithmLibrary *Lib,FlexArea &Area ,ImagePointerContainer &Images ,int dx ,int dy);
};

#define	MaxSPointNumb	25

class	BaseMatch : public ServiceForLayers
{
public:
	AlignmentFlexAreaBase	*ABase;
public:
	class	SImage
	{
		BaseMatch	*ParentBaseMatch;
	public:
		int		SImageNo;
		PureFlexAreaListContainer	SArea;

		class	MatchingPointsStruct
		{
		public:
			int		SPoint[MaxSPointNumb][2];
			int		SPointBack[MaxSPointNumb][2];
			int		SPointNumb;
			double	CalcMatch (SImage *Parent ,int dx ,int dy ,int GlobalPage);
			double	CalcMatch1(SImage *Parent ,int dx ,int dy ,int GlobalPage ,int skip);
			void	Draw(SImage *Parent, QPainter &P, int movx ,int movy ,double ZoomRate,const QColor &Col1 ,const QColor &Col2);
		};
		MatchingPointsStruct	MLeftTop	;
		MatchingPointsStruct	MRightTop	;
		MatchingPointsStruct	MLeftBottom	;
		MatchingPointsStruct	MRightBottom;

		double	Angle;
		double	Result;

		SImage(int n ,BaseMatch *p);
		~SImage(void);

		void	Release(void);
		bool	ExecuteInitialAfterEdit1(double angle,BYTE **RootBuff,ExecuteInitialAfterEditInfo &EInfo);
		bool	ExecuteInitialAfterEdit2(double angle,BYTE **RootBuff,ExecuteInitialAfterEditInfo &EInfo);
		double	CalcMatch (int dx ,int dy ,int GlobalPage);
		double	CalcMatch1(int dx ,int dy ,int GlobalPage ,int skip);
		void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate);

		LayersBase	*GetLayersBase(void);
	private:
	};
	SImage	**SImageInfo;
	int		SImageNumb;
	int		Layer;
		
	double	ZoomRate;
	int		SDotPerLine;
	int		SMaxLines;
	BYTE	**BaseBuff;
	double	AngleDelta;
	int		RangeX;
	int		RangeY;
	int		ResultDx,ResultDy,ResultSImageNo;
	struct	SearchStruct
	{
		int		ImageNo;
		int		dx,dy;
		double	Total;
	};
	struct	SearchStruct	*SearchDim;
	int		SearchDimNumb;

	BaseMatch(AlignmentFlexAreaBase *p ,LayersBase *base);
	~BaseMatch(void);

	bool	ExecuteInitialAfterEdit(DWORD ExecuteInitialAfterEdit_Changed);
	bool	MakeSImages(ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteMatching(void);
	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,int OffsetX ,int OffsetY ,AlgorithmDrawAttr *Attr);

private:
	BYTE	**MakeImageBuffer(void);

};

class	AlignmentFlexAreaBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points

	bool		UseOtherPage;
	QColor		ColorPriorityHigh;
	QColor		ColorPriorityMiddle;
	QColor		ColorPriorityLow;
	QColor		ColorPriorityGlobal;
	bool		UseBitBuff;
	int			TransparentLevelInBitBuff;
	int			SkipDotForRoughSearch;
	int			LineMergin;
	int			OutlineWidth;
	bool		ModeWholeMatch;
	int			DivisionWholeMatch;
	int			DivisionWholeMatchDetail;
	int			WholeMatchSearchDot;
	int			WholeMatchSearchDotDetail;
	bool		ModeShowTransArea;
	bool		ModeShowItemLine;
	bool		ModeShowItemArea;
	bool		ModeShowResultArea;
	bool		ModeShowOriginalInResult;
	int			SearchExpandedDotInOutline;
	double		CutOffNearbyMatch;
	bool		EnableBaseMatch;
	double		ZoomRateForBaseMatch;
	int			ExpandBaseMatch;
	int			RotationRangeBaseMatch;	//Degree
	int			PermitDiffBaseMatch;
	int			BaseMatchSep;
	int			BaseMatchLoopSep;
	int			OffsetXBaseMatch;
	int			OffsetYBaseMatch;

	BaseMatch	BaseMatchData;

	AlignmentFlexAreaBase(LayersBase *Base);
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new AlignmentFlexAreaInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;

	//virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	QString	GetDataText(void)	 override	{		return QString("AlignmentFlexArea");	}
	QString	GetDefaultFileName(void)	 override	{	return QString("ConfigAlignmentFlexArea.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	 override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	 const	override;
	void	DrawLocal(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,int OffsetX ,int OffsetY,AlgorithmDrawAttr *Attr);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	 override;
	virtual	void	InitialAfterParamLoaded(void)	 override;
};

//==========================================================================
class	AlignmentFlexAreaInfoList : public NPListSaveLoad<AlignmentFlexAreaInfoList>
{
public:
	int		LibID;
	IntList	AlignmentFlexAreaCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	AlignmentFlexAreaInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(AlignmentFlexAreaCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	AlignmentFlexAreaInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(AlignmentFlexAreaCount.Load(f)==false)
		return false;
	return true;
}
class	AlignmentFlexAreaInfoListPack : public NPListPackSaveLoad<AlignmentFlexAreaInfoList>
{
public:
	AlignmentFlexAreaInfoListPack(void){}

	virtual	AlignmentFlexAreaInfoList	*Create(void)	{	return new AlignmentFlexAreaInfoList();	}
};
//=======================================================================================
class	AddAlignmentFlexAreaAreaPacket : public GUIDirectMessage
{
public:
	FlexArea		Area;
	QString			AreaName;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;
	AlgorithmLibraryListContainer	LibToCreateItems;

	AddAlignmentFlexAreaAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentFlexAreaAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyAlignmentFlexAreaAreaPacket : public GUIDirectMessage
{
public:
	int				AreaID;
	FlexArea		Area;
	QString			AreaName;
	XAlignmentFlexAreaArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;
	AlgorithmLibraryListContainer	LibToCreateItems;

	ModifyAlignmentFlexAreaAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyAlignmentFlexAreaAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdAlignmentFlexAreaReflectChangeItems : public GUIDirectMessage
{
public:
	GUICmdAlignmentFlexAreaReflectChangeItems(LayersBase *base):GUIDirectMessage(base){}
	GUICmdAlignmentFlexAreaReflectChangeItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentFlexAreaPointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	FlexArea	Area;
	int			LibID;

	AddAlignmentFlexAreaPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentFlexAreaPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyAlignmentFlexAreaPointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	int			ItemID;
	WORD		Threshold;
	WORD		MoveDot;
	bool		UsageGlobal;
	WORD		GroupNumber;
	bool		AlignmentFlexAreaOnOutline;

	ModifyAlignmentFlexAreaPointPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyAlignmentFlexAreaPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	MakeAlignmentFlexAreaGroupPacket : public GUIDirectMessage
{
public:
	int	Cmd;

	MakeAlignmentFlexAreaGroupPacket(LayersBase *base):GUIDirectMessage(base){}
	MakeAlignmentFlexAreaGroupPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	RemoveAlignmentFlexAreaGroupPacket : public GUIDirectMessage
{
public:

	RemoveAlignmentFlexAreaGroupPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveAlignmentFlexAreaGroupPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RemoveAlignmentFlexAreaAreaPacket : public GUIDirectMessage
{
public:
	int			AreaID;

	RemoveAlignmentFlexAreaAreaPacket(LayersBase *base):GUIDirectMessage(base)			{	AreaID=-1;	}
	RemoveAlignmentFlexAreaAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	AreaID=-1;	}
};

class	GetSelectedAlignmentFlexAreaAreaPacket : public GUIDirectMessage
{
public:
	QByteArray	BuffData;

	GetSelectedAlignmentFlexAreaAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	GetSelectedAlignmentFlexAreaAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentFlexAreaLibraryListInPastePacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetAlignmentFlexAreaLibraryListInPastePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentFlexAreaLibraryListInPastePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertAlignmentFlexAreaLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertAlignmentFlexAreaLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateAlignmentFlexAreaLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateAlignmentFlexAreaLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentFlexAreaLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetAlignmentFlexAreaLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetAlignmentFlexAreaLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempAlignmentFlexAreaLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempAlignmentFlexAreaLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetAlignmentFlexAreaLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	int			AreaPriority;
	AlgorithmLibraryListContainer	AList;

	CmdGetAlignmentFlexAreaLibraryListPacket(LayersBase *base):GUIDirectMessage(base)			{	AreaPriority=-1;	}
	CmdGetAlignmentFlexAreaLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	AreaPriority=-1;	}
};

class	CmdLoadAlignmentFlexAreaLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadAlignmentFlexAreaLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearAlignmentFlexAreaLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearAlignmentFlexAreaLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteAlignmentFlexAreaLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteAlignmentFlexAreaLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteAlignmentFlexAreaLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempAlignmentFlexAreaItemPacket : public GUIDirectMessage
{
public:
	AlignmentFlexAreaItem	*Point;
	CmdCreateTempAlignmentFlexAreaItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempAlignmentFlexAreaItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqAlignmentFlexAreaInfoListPack : public GUIDirectMessage
{
public:
	int	AreaID;
	AlignmentFlexAreaInfoListPack	Points;

	CmdReqAlignmentFlexAreaInfoListPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentFlexAreaInfoListPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	CmdReqTestByLibID : public GUIDirectMessage
{
public:
	int		AreaID;
	IntList	LibList;
	CmdReqTestByLibID(LayersBase *base):GUIDirectMessage(base){}
	CmdReqTestByLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGenerateByLibID : public GUIDirectMessage
{
public:
	int		AreaID;
	IntList	LibList;
	CmdReqGenerateByLibID(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGenerateByLibID(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqClearTestMap : public GUIDirectMessage
{
public:
	CmdReqClearTestMap(LayersBase *base):GUIDirectMessage(base){}
	CmdReqClearTestMap(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqGenerateAreaWithItemLibFromMask : public GUIDirectMessage
{
public:
	int		Priority;
	int		ItemLibID;

	CmdReqGenerateAreaWithItemLibFromMask(LayersBase *base):GUIDirectMessage(base){}
	CmdReqGenerateAreaWithItemLibFromMask(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqXYResult : public GUIDirectMessage
{
public:
	int		localX,localY;

	int		IndexID;
	int		IndexX1,IndexY1;
	int		IndexX2,IndexY2;
	int		IndexX3,IndexY3;
	bool	EnableIndex1;
	bool	EnableIndex2;
	bool	EnableIndex3;
	int		TotalShiftX		,TotalShiftY		,AreaID;	
	int		WholeMatchShiftX,WholeMatchShiftY;
	int		GlobalShiftX	,GlobalShiftY		,GlobalAreaID;

	CmdReqXYResult(LayersBase *base);
	CmdReqXYResult(GUICmdPacketBase *gbase);
};


inline	CmdReqXYResult::CmdReqXYResult(LayersBase *base)
	:GUIDirectMessage(base)
{
	localX=localY	=0;
	IndexX1	=0,IndexY1	=0;
	IndexX2	=0,IndexY2	=0;
	IndexX3	=0,IndexY3	=0;
	EnableIndex1	=false;
	EnableIndex2	=false;
	EnableIndex3	=false;
	TotalShiftX=0	,TotalShiftY=0		,AreaID	=-1;
	WholeMatchShiftX=0,WholeMatchShiftY=0;
	GlobalShiftX=0,GlobalShiftY=0		,GlobalAreaID=-1;
}
inline	CmdReqXYResult::CmdReqXYResult(GUICmdPacketBase *gbase)
	:GUIDirectMessage(gbase)
{
	localX=localY	=0;
	IndexX1	=0,IndexY1	=0;
	IndexX2	=0,IndexY2	=0;
	IndexX3	=0,IndexY3	=0;
	EnableIndex1	=false;
	EnableIndex2	=false;
	EnableIndex3	=false;
	TotalShiftX=0	,TotalShiftY=0		,AreaID	=-1;
	WholeMatchShiftX=0,WholeMatchShiftY=0;
	GlobalShiftX=0,GlobalShiftY=0		,GlobalAreaID=-1;
}

class	CmdReqAlignmentFlexAreaItem : public GUIDirectMessage
{
public:
	int	AreaID;
	int	localX ,localY;
	int	RetItemID;
	int	RetLibID;
	int	RetGlobalSearchDot;
	int	RetSearchDot;
	bool	RetKeepBW;

	CmdReqAlignmentFlexAreaItem(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentFlexAreaItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdSetAlignmentFlexAreaItem : public GUIDirectMessage
{
public:
	int		ItemID;
	int		LibID;
	int		GlobalSearchDot;
	int		SearchDot;
	bool	KeepBW;
	bool	ModeSetAll;

	CmdSetAlignmentFlexAreaItem(LayersBase *base):GUIDirectMessage(base){}
	CmdSetAlignmentFlexAreaItem(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================
class	AlignmentFlexAreaItemList : public NPListSaveLoad<AlignmentFlexAreaItemList>
{
public:
	struct{
		int		ItemID;
		int		CenterX,CenterY;
		int		x1,y1,x2,y2;
	}Data;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	AlignmentFlexAreaItemList::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
inline	bool	AlignmentFlexAreaItemList::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;

	return true;
}
class	AlignmentFlexAreaItemListPack : public NPListPackSaveLoad<AlignmentFlexAreaItemList>
{
public:
	AlignmentFlexAreaItemListPack(void){}

	virtual	AlignmentFlexAreaItemList	*Create(void)	{	return new AlignmentFlexAreaItemList();	}
};

class	CmdReqAlignmentFlexAreaItemtPack : public GUIDirectMessage
{
public:
	int			LibID;
	int			AreaID;
	AlignmentFlexAreaItemListPack	*Items;

	CmdReqAlignmentFlexAreaItemtPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentFlexAreaItemtPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//==========================================================================

class	MatchAngleList : public NPListSaveLoad<MatchAngleList>
{
public:
	int		SImageNo;
	double	Angle;
	double	MatchingRate;

	MatchAngleList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	MatchAngleListContainer : public NPListPackSaveLoad<MatchAngleList>
{
public:
	virtual	MatchAngleList	*Create(void)	{	return new MatchAngleList();	}
};

inline	bool	MatchAngleList::Save(QIODevice *f)
{
	if(::Save(f,SImageNo)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,MatchingRate)==false)
		return false;
	return true;
}
inline	bool	MatchAngleList::Load(QIODevice *f)
{
	if(::Load(f,SImageNo)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,MatchingRate)==false)
		return false;
	return true;
}

class	CmdReqBaseMatchList : public GUIDirectMessage
{
public:
	MatchAngleListContainer	*ListPoint;

	CmdReqBaseMatchList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqBaseMatchList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGenerateBaseMatch : public GUIDirectMessage
{
public:
	CmdGenerateBaseMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateBaseMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdExecBaseMatch : public GUIDirectMessage
{
public:
	CmdExecBaseMatch(LayersBase *base):GUIDirectMessage(base){}
	CmdExecBaseMatch(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

//===========================================================================
class	AlignmentPointList : public NPListSaveLoad<AlignmentPointList>
{
public:
	int		LibID;
	int		ItemID;
	int		PosX1,PosY1;
	int		PosX2,PosY2;
	int		SearchDot;

	AlignmentPointList(void){}

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};
	
inline	bool	AlignmentPointList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)		return false;
	if(::Save(f,ItemID)==false)		return false;
	if(::Save(f,PosX1)==false)		return false;
	if(::Save(f,PosY1)==false)		return false;
	if(::Save(f,PosX2)==false)		return false;
	if(::Save(f,PosY2)==false)		return false;
	if(::Save(f,SearchDot)==false)	return false;
	return true;
}

inline	bool	AlignmentPointList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)		return false;
	if(::Load(f,ItemID)==false)		return false;
	if(::Load(f,PosX1)==false)		return false;
	if(::Load(f,PosY1)==false)		return false;
	if(::Load(f,PosX2)==false)		return false;
	if(::Load(f,PosY2)==false)		return false;
	if(::Load(f,SearchDot)==false)	return false;
	return true;
}

class	AlignmentPointListContainer : public NPListPackSaveLoad<AlignmentPointList>
{
public:
	virtual	AlignmentPointList	*Create(void)	{	return new AlignmentPointList();	}
};

class	CmdReqAlignmentPointList : public GUIDirectMessage
{
public:
	int							AreaID;
	AlignmentPointListContainer	*PointList;

	CmdReqAlignmentPointList(LayersBase *base):GUIDirectMessage(base){}
	CmdReqAlignmentPointList(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif

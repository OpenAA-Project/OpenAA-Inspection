/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XAlignment.h
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#ifndef XAlignemntH
#define XAlignemntH
/*----------------------------------------------------------------------------*/
//  1.日本語名
//
//  2.概要
//
//  3.機能説明
//
//  4.備考
//
/*----------------------------------------------------------------------------*/
#include <QIODevice>
#include <QPoint>
#include "XFlexArea.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "XPacketAlignment.h"
#include "XAlignOutline.h"
#include "XAOutline.h"
#include "NListComp.h"

#define	AlignmentVersion	1

class	XAlignment;
class   AlignmentInLayer;
class	XAlignmentArea;


class	AlignmentThreshold : public AlgorithmThreshold
{
public:
	ImageBuffer	Image;
	XOutlineList	*OList;		//過去の遺物
	int32			OListNumb;	//過去の遺物

	WORD		MoveDot;		
    WORD		Threshold;
	bool		AlignmentOnOutline;	//輪郭で位置合わせするときtrue

	AlignmentThreshold(XAlignment *parent);
	~AlignmentThreshold(void);

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override;
	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const	override	{	return sizeof(this);	}
};


class   XAlignment : public AlgorithmItemPLI
{
    FlexArea    OutSideArea;
    FlexArea    TransArea;
    FlexArea    InSideArea;
    FlexArea    ClusterMask;
	VectorAlignmentItem		AlignOutline;
  public:
	WORD		GroupNumber;		
    double      MasterX;
    double      MasterY;
    double      CalcedX;
    double      CalcedY;                //探索後の位置
	WORD		AreaID;
	enum	EnumMatchingType{
		_MatchingByArera		=1
		,_MatchingByOutline		=2
	}MatchingType;

	XAlignment(void);

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new XAlignment();	}
	virtual	void	SetParent(AlgorithmInLayerPLI *parent)	override;
	bool	SetMark(FlexArea &area,int threshould);
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)	override;

    virtual	void    MoveTo(int dx ,int dy)	override;

	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;
    XAlignment &operator=(XAlignment &src);

    void    MatchBrightCenter(double &mx ,double &my ,ImageBuffer &Target ,int offsetX=0,int offsetY=0);

	const	AlignmentThreshold	*GetThresholdR(LayersBase *base=NULL)	{	return (const AlignmentThreshold *)GetThresholdBaseReadable(base);	}
	AlignmentThreshold			*GetThresholdW(LayersBase *base=NULL)	{	return (AlignmentThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override{	return new AlignmentThreshold(this);	}

    void    Clear(void);
    virtual	bool    Save(QIODevice *file)					override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase)	override;

	virtual	bool	IsEffective(void)	const	override;
	bool	IsOtherAreaEffective(void);
	void    MakeArea(int ccol ,ImageBuffer &Buff ,ImageBuffer *specialData=NULL);
	bool	GetAlignmentOnOutline(void){	return GetThresholdR()->AlignmentOnOutline;	}

	void	Calc(ImageBuffer &TargetData ,int dx=0 ,int dy=0);
	int		GetMx(void){	return(CalcedX-MasterX);	}
	int		GetMy(void){	return(CalcedY-MasterY);	}

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)		override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;
	virtual	ExeResult	ExecutePreAlignment		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)	override;

	void	CreateArea(ImageBuffer &Img);

public:
	double	GetThreshLevel(ImageBuffer &data ,int dx=0 ,int dy=0);
	bool    GetBrightCenter(ImageBuffer &data ,double ccol
                            ,double &mx ,double &my
                            ,int dx=0,int dy=0
                            ,int xdotperline=-1 ,int ymaxlines=-1);
    double  GetBrightCenterOnOutline(ImageBuffer &data ,int ccol
                                        ,double &mx ,double &my
                                        ,int dx,int dy
                                        ,int xdotperline=-1 ,int ymaxlines=-1);
	double  GetCenterList(int *XListNumb ,int xnumb , int dotperline);
	void    SmallExpand(BYTE *BitPtn,int xlen,int ylen,int bitbyte);
	void    SmallReduce(BYTE *BitPtn,int xlen,int ylen,int bitbyte);
	void    AddOutline(ImageBuffer &data ,BYTE *BitPtn ,int XLen ,int YLen ,int XByte
                                        ,int OffsetX ,int OffsetY
                                        ,int OutlinePrecision);
};

class   XAlignmentPointer :public NPList<XAlignmentPointer>
{
public:
	XAlignment		*Point;
	XAlignmentArea	*Parent;

	XAlignmentPointer(void);
    XAlignmentPointer &operator=(XAlignmentPointer &src);
	virtual	DataInLayer	*GetDataInLayer(void);

	bool    Save(QIODevice *file);
	bool    Load(QIODevice *file ,XAlignmentArea *parent);
};



class   XAlignmentArea : public NPList<XAlignmentArea>
{
	struct	GAlignPointInfo{
		double	SrcX,SrcY;
		double	Dx,Dy;
		int	GroupNumber;
		int	GroupCount;
	};

	GAlignPointInfo	GInfo[10];
	int		GInfoCount;
	bool	GroupMode;
	int		MaxSearchAreaFromItem;
  public:
    int32           AreaID;
    FlexArea        Area;
	QString			AreaName;
	//int32			Priority;
    NPListPack<XAlignmentPointer>			GPack;
	AlignmentShiftContainer					OtherPack;

	enum	AlignmentPointCount
	{
		_Aligned0
		,_Aligned1
		,_Aligned2
		,_Aligned3
		,_Aligned4
	}ResultPointCounts;
	AlgorithmLibraryListContainer	LimitedLib;
    int32				PartsID;			//部品番号		無設定時 -1
    int32				PartsAllocID;       //部品配置ＩＤ
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
	}Priority;
 
//    NPListPack<QPoint			Result[3];
    double          CalcedParam[6];		//原点計算でのアフィン変換パラメーター
	class	AlignmentResultClass
	{
	public:
		double	AlignmentResult[6];
		int		Cx,Cy;

		AlignmentResultClass(void){	Cx=0;	Cy=0;	}
		AlignmentResultClass	&operator=(AlignmentResultClass &src);
	}ALResult[4];
	AlignmentInLayer	*ParentInLayer;

    XAlignmentArea(void);
	XAlignmentArea(AlignmentInLayer	*parentInLayer);

    XAlignmentArea  &operator=(XAlignmentArea &src);
    XAlignmentArea  &CopyWithoutItems(XAlignmentArea &src,bool ReferedMode);
    void    MoveTo(int dx ,int dy);
    void    Initial(ImageBuffer &IData);
	bool	IsInclude(int x ,int y)	{	return(Area.IsInclude(x,y));	}
	bool	IsCrossed(FlexArea *b)	{	return(Area.CheckOverlap(b));	}
	bool    GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const	{	return Area.GetXY(x1,y1,x2,y2);	}
	void	SetGroup(FlexArea &area ,int groupNumber);
	AlignmentPointCount	GetResultInPoint(int localX ,int localY);
	bool	GetAlignment(AlignmentPacket2D &AData);
	virtual	void		RemoveItem(AlgorithmItemPLI *item);

    void    GetCenter(int &cx, int &cy);
	void	Calc(ImageBuffer &TargetData
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	int		GetCalcedItemCount(void);
	bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteStartByInspection(void);
	bool	ReqOtherAlignment(void);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file ,AlignmentInLayer *parent);
    bool    SaveUnique(QIODevice *file);
    bool    LoadUnique(QIODevice *file);

	DataInPage	*GetDataInPage(void);
	virtual	void	Draw	 (QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove (int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);

private:
	bool	Calc0(QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	Calc1(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	Calc2(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	Calc3(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);
	bool	Calc4(GAlignPointInfo GInfo[] 
				, QPoint *MVector
				,int	MVectorXNumb,int	MVectorYNumb
				,int	MVectorXRes	,int	MVectorYRes);};

class   AlignmentInLayer : public AlgorithmInLayerPLI
{
  public:
    NPListPack<XAlignmentArea>  Areas;       //Area statement
    NPListPack<XAlignmentArea>  DispatchAreas;       //Area statement

    QPoint      *MVector;
    int         MVectorXNumb;
    int         MVectorYNumb;
    int         MVectorXRes;
    int         MVectorYRes;

	double ResultShiftX,ResultShiftY;	//平行移動量
	double ResultAngle;					//回転量（ラジアン）
	double ResultExtend;				//拡大率

  public:
    double  GCalcA[6];
    double  GCalcAr[6];

  public:
    AlignmentInLayer(AlgorithmInPageRoot *parent);
    ~AlignmentInLayer(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)	override	{	return(new XAlignment());	}
	virtual	bool				AppendItem(AlgorithmItemRoot *item)	override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item ,int64 itemID)	override	{	return AlgorithmInLayerPLI::AppendItem(item ,itemID);	}
	virtual	void				AppendItemWithoutMakeArea(AlgorithmItemRoot *item ,int AreaID);
	virtual	bool				AppendItemFromLoad(AlgorithmItemRoot *item)	override;

	virtual	void	Draw	(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawItem(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	void	RemoveItem(AlgorithmItemRoot *item)	override;
	void	RemoveArea(XAlignmentArea *a);
	XAlignmentArea	*GetAlignmentArea(int AreaID);

	void	UndoAppendManualArea(QIODevice *f);
	void	UndoAppendManualPoint(QIODevice *f);
	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)		override;
	virtual	void	RemoveItemFormDispatcher(void)				override;

	virtual	void	Release(void)	override;

    bool    Save(QIODevice *file)	override;
    bool    Load(QIODevice *file)	override;
	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	QPoint	*GetPoint(int rx ,int ry);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInLayerRoot *Res)	override;

	void    CleanupItems(void);
    bool    ClearAll(void);
	void    InitializeFromImage(ImageBuffer &IBuff);

	XAlignment	*GetAlignment(int index);
	bool	GetAlignment(AlignmentPacket2D &AData);
    void    GetResultVectorXY(int rx ,int ry ,int &kx ,int &ky);
	int     GetAlignmentNumb(void);

	int		GetAlignmentAreaCount(void){	return Areas.GetCount();	}

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
	virtual	void	CutArea(FlexArea &localArea ,bool MultiSelect,const QByteArray &Something=QByteArray())	override		;
	virtual	void	RegistArea(FlexArea &localArea)									override;
	virtual	void	DeleteSelectedItems(void)										override;
	virtual	void	LockSelectedItems(void)											override;
	virtual	void	BindSelectedItems(void)											override;
	virtual	void	Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)	override;
	virtual	void	Activate(int ItemID)											override;
	virtual	void	Inactivate(void)												override;

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack)							override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)		override;

	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)		override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase)				override;
	virtual	void	VisibleAll(void)			override;
	virtual	void	InvisibleAll(void)			override;
	virtual	void	InvisibleSelected(void)		override;
	virtual	void	SelectManualCreature(void)	override;

	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)					override {}

	bool	ExistArea(int localX,int localY);
	int		GetMaxAreaID(void);
};


class	AlignmentPacket2DList : public NPList<AlignmentPacket2DList> ,public AlignmentPacket2D
{
public:
	AlignmentPacket2DList(void){}
};

class   AlignmentInPage : public AlgorithmInPagePLI
{
public:
	QMutex	AlignmentPacket2DCreaterMutex;
	NPListPack<AlignmentPacket2DList>	AlignmentPacket2DContainer;

	AlignmentInPage(AlgorithmBase *parent);

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override{	return(new AlignmentInLayer(parent));	}
	AlignmentPacket2D	*AppendAlignmentPacket2D(AlgorithmItemRoot *Item ,int localX ,int localY,bool FromGlobal);

	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteAlignment		(int ExeID ,ResultInPageRoot *Res)	override;
	void	GetAlignment(AlignmentPacket2D &AData);
	void	GetAlignmentParam(double m[6]);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
private:
	bool	ExistArea(int localX,int localY);

};

class	AlignmentBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points

	WORD		DefaultThreshold;
	WORD		DefaultMoveDot;
	bool		DefaultAlignmentOnOutline;

	WORD		DefaultOutlineDivCount;
	WORD		DefaultOutlineWidth;
	bool		UseOtherPage;

	AlignmentBase(LayersBase *Base);
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new AlignmentInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)		override;
	virtual	QString	GetDataText(void)								override	{		return QString("Alignment");	}
	QString	GetDefaultFileName(void)								override	{	return QString("ConfigAlignment.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

//=======================================================================================
class	AddAlignmentAreaPacket : public GUIDirectMessage
{
public:
	int				Number;
	FlexArea		Area;
	int32			Page;
	int32			Layer;
	QString			AreaName;
	XAlignmentArea::_EnumPriority	Priority;
	AlgorithmLibraryListContainer	LimitedLib;

	AddAlignmentAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdAlignmentReflectChangeItems : public GUIDirectMessage
{
public:
	GUICmdAlignmentReflectChangeItems(LayersBase *base):GUIDirectMessage(base){}
	GUICmdAlignmentReflectChangeItems(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentPointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	FlexArea	Area;
	WORD		Threshold;
	WORD		MoveDot;
	bool		AlignmentOnOutline;

	AddAlignmentPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyAlignmentPointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	int			ItemID;
	WORD		Threshold;
	WORD		MoveDot;
	bool		AlignmentOnOutline;

	ModifyAlignmentPointPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyAlignmentPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddAlignmentGroupPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	int			GroupNumber;
	FlexArea	Area;

	AddAlignmentGroupPacket(LayersBase *base):GUIDirectMessage(base){}
	AddAlignmentGroupPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	RemoveAlignmentAreaPacket : public GUIDirectMessage
{
public:
	int			AreaID;

	RemoveAlignmentAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	RemoveAlignmentAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GetSelectedAlignmentAreaPacket : public GUIDirectMessage
{
public:
	ListLayerAndIDPack	SelectedArea;

	GetSelectedAlignmentAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	GetSelectedAlignmentAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

	


#endif

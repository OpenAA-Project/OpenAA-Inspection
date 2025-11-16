/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\MatchShiftRotation\XMatchShiftRotation.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#if	!defined(XMatchShiftRotation)
#define	XMatchShiftRotation


#include <QIODevice>
#include <QPoint>
#include <QString>
#include "XFlexAreaImage.h"
#include "XMainSchemeMemory.h"
#include "XDataInLayer.h"
#include "NListComp.h"
#include "XTypeDef.h"
#include "XYCross.h"
#include "XResult.h"
#include "XDataModelPageItem.h"
#include "XAlgorithmLibrary.h"
#include "XMatchShiftRotationLibrary.h"
#include "XStandardCommand.h"

#define	MatchShiftRotationVersion	1

class	MatchShiftRotationItem;
class	AlignmentGroup;
class	XMatchShiftRotationArea;
class	MatchShiftRotationInPage;
class	MatchShiftRotationBase;


class	MatchShiftRotationThreshold : public AlgorithmThreshold
{
public:
	WORD		TargetLayer	;
	int32		SearchLittleInItem	;
	double		MatchingRate;

	MatchShiftRotationThreshold(MatchShiftRotationItem *parent);
	~MatchShiftRotationThreshold(void);

	virtual	void	RegistHist(void)	override;

	virtual	void	CopyFrom(const AlgorithmThreshold &src)	override;
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const override;
	virtual	void	FromLibrary(AlgorithmLibrary *src)	override;
	virtual	void	ToLibrary(AlgorithmLibrary *Dest)	override;

	virtual	bool	Save(QIODevice *f)					override;
    virtual	bool	Load(QIODevice *f)					override;
    virtual	int		GetSize(void)	const override	{	return sizeof(this);	}

	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;
};

#define	Hist_MatchShiftRotationShiftX	1
#define	Hist_MatchShiftRotationShiftY	2
#define	Hist_MatchShiftRotationRotation	3
#define	Hist_MatchShiftRotationRate		4
#define	SetIndependentItemDataCommand_OnlyOne	10
#define	SetIndependentItemDataCommand_All		12

#define	MatchShiftRotationHistogramListReqCommand				3
#define	MatchShiftRotationHistogramListSendCommand				4
#define	MatchShiftRotationReqThresholdReqCommand				5
#define	MatchShiftRotationReqThresholdSendCommand				6
#define	MatchShiftRotationReqTryThresholdCommand				7
#define	MatchShiftRotationSendTryThresholdCommand				8
#define	MatchShiftRotationReqChangeShiftCommand				9
#define	SetIndependentItemNameDataCommand_All					20

class	FlexAreaImageListCoeffAngle : public FlexAreaImageListCoeff
{
public:
	double	Angle;	//Radian;
	double	RoughSumA;
	double	RoughSumA2;
	double	AvrRoughS;
	int		RoughNumb;
	struct	CoefDimStruct
	{
		int	AbsY;
		int	LeftX;
		int	Numb;
		int	SepX;
		BYTE	*Src;
	};
	struct	CoefDimStruct	*CoefDim;
	int						CoefDimNumb;

	FlexAreaImageListCoeffAngle(void);
	~FlexAreaImageListCoeffAngle(void);

	FlexAreaImageListCoeffAngle	&operator=(PureFlexAreaList &src);
	void	MakeRoughSum(int Sep=5);
	double	CalcCoeffRough(int dx	,int dy		,ImageBuffer &Buffer);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class	FlexAreaImageListCoeffAngleContainer : public FlexAreaImageListContainer
{
public:
	FlexAreaImageListCoeffAngleContainer(void){}

	virtual	FlexAreaImageList *CreateNew(void){		return new FlexAreaImageListCoeffAngle();	}

	FlexAreaImageListCoeffAngleContainer &operator=(FlexAreaImageListCoeffAngleContainer &src);
	FlexAreaImageListCoeffAngleContainer &operator=(const FlexAreaImageListCoeffAngleContainer &src);
};

inline	FlexAreaImageListCoeffAngle::FlexAreaImageListCoeffAngle(void)
{
	Angle	=0;
	RoughSumA=RoughSumA2=0;
	RoughNumb=0;
	AvrRoughS=0;
	CoefDim	=NULL;
	CoefDimNumb=0;
}
inline	FlexAreaImageListCoeffAngle::~FlexAreaImageListCoeffAngle(void)
{
	if(CoefDim!=NULL){
		delete	[]CoefDim;
		CoefDim=NULL;
	}
	Angle	=0;
	RoughSumA=RoughSumA2=0;
	RoughNumb=0;
	AvrRoughS=0;
	CoefDimNumb=0;
}

inline	bool	FlexAreaImageListCoeffAngle::Save(QIODevice *f)
{
	if(FlexAreaImageListCoeff::Save(f)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	return true;
}
inline	bool	FlexAreaImageListCoeffAngle::Load(QIODevice *f)
{
	if(FlexAreaImageListCoeff::Load(f)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	return true;
}

inline	FlexAreaImageListCoeffAngleContainer &FlexAreaImageListCoeffAngleContainer::operator=(FlexAreaImageListCoeffAngleContainer &src)
{
	RemoveAll();
	for(FlexAreaImageList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaImageListCoeffAngle	*src=dynamic_cast<FlexAreaImageListCoeffAngle *>(s);
		if(src!=NULL){
			FlexAreaImageListCoeffAngle	*d=new FlexAreaImageListCoeffAngle();
			*d=*src;
			AppendList(d);
		}
	}
	return *this;
}

inline	FlexAreaImageListCoeffAngleContainer &FlexAreaImageListCoeffAngleContainer::operator=(const FlexAreaImageListCoeffAngleContainer &src)
{
	RemoveAll();
	for(FlexAreaImageList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaImageListCoeffAngle	*src=dynamic_cast<FlexAreaImageListCoeffAngle *>(s);
		if(src!=NULL){
			FlexAreaImageListCoeffAngle	*d=new FlexAreaImageListCoeffAngle();
			*d=*src;
			AppendList(d);
		}
	}
	return *this;
}

//--------------------------------------------------------------------------------------------------


class   MatchShiftRotationItem : public AlgorithmItemPI
{
public:
	double		MasterX,MasterY;
    double      ResultLittleDx,ResultLittleDy;	//Calculated position after Area rotation
	WORD		AreaID;
	double		MatchingRate;	//Generate from item

	FlexAreaImageListCoeffAngleContainer	Patterns;
	double		StepAngle;	//Radian

	XMatchShiftRotationArea	*ParentArea;

	MatchShiftRotationItem(void);
	~MatchShiftRotationItem(void);
	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new MatchShiftRotationItem();	}
	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY) override;

    virtual	void    MoveTo(int dx ,int dy) override;

	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;
    MatchShiftRotationItem &operator=(MatchShiftRotationItem &src);

	const	MatchShiftRotationThreshold	*GetThresholdR(LayersBase *base=NULL){	return (const MatchShiftRotationThreshold *)GetThresholdBaseReadable(base);	}
	MatchShiftRotationThreshold			*GetThresholdW(LayersBase *base=NULL){	return (MatchShiftRotationThreshold *)GetThresholdBaseWritable(base);	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new MatchShiftRotationThreshold(this);	}
	
	virtual	void	SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)	override;
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	override;

    virtual	bool    Save(QIODevice *file) override;
    virtual	bool    Load(QIODevice *file,LayersBase *LBase) override;

	bool	IsAreaEffective(void);

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr) override;
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate ,bool OnlyNG) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res) override;

	void	CopyThresholdOnly(MatchShiftRotationItem *src);
	XMatchShiftRotationArea	*GetMatchShiftRotationArea(void)	{	return ParentArea;	}
	FlexAreaImageListCoeffAngle	*GetClosedPattern(double angle);
	bool	GetResultTotalDxy(int &dx ,int &dy ,double &Angle);

	double	Calc(int dx, int dy ,double angle
				,int &SearchedDx ,int &SearchedDy ,int step);
	double	CalcRough(int dx, int dy ,double angle
				,int step);

public:

};

class   XMatchShiftRotationArea : public NPList<XMatchShiftRotationArea>
{
	friend	class   MatchShiftRotationInPage;

	double	StepAngle;
	double	AngleRange;

	double	RoughSepAngle;
	int		RoughStepMove;
	int		RoughIsolation;
public:
	struct	SearchDim
	{
		double	Angle;
		double	SinS,CosS;
		int	Dx,Dy;
		double	CalcD;
	};
private:
	struct	SearchDim	*SearchDimPointer;
	int		SearchDimNumb;

  public:
	AlgorithmItemPointerListContainer	ItemPack;

	int32				AreaID;
	int32				LibID;
    FlexArea			Area;
	QString				AreaName;

    int32				PartsID;			//ïîïiî‘çÜ		ñ≥ê›íËéû -1
    int32				PartsAllocID;       //ïîïiîzíuÇhÇc
	int32				PartsAreaID;
	bool				Locked;
	bool				Selected;
	bool				Active;
	bool				Visible;
	bool				ManualCreated;
	AlgorithmBase		*Origin;

	int32		SearchArea;		//Generate from item
	int32		SearchAngle;	//Generate from item

	int		ResultDx,ResultDy;
	double	ResultAngle;


	MatchShiftRotationInPage		*ParentInPage;

    XMatchShiftRotationArea(void);
	XMatchShiftRotationArea(MatchShiftRotationInPage	*parentInPage);
	~XMatchShiftRotationArea(void);

	MatchShiftRotationBase	*GetParentBase(void);
	int	GetPage(void);
	int	GetID(void)		{	return AreaID;	}

    XMatchShiftRotationArea  &operator=(XMatchShiftRotationArea &src);
    XMatchShiftRotationArea  &CopyWithoutItems(XMatchShiftRotationArea &src,bool ReferedMode);
    void    MoveTo(int dx ,int dy);
	bool	IsInclude(int x ,int y)	{	return(Area.IsInclude(x,y));	}
	bool	IsCrossed(FlexArea *b)	{	return(Area.CheckOverlap(b));	}
	bool    GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	{	return Area.GetXY(x1,y1,x2,y2);	}

	void	DeleteAllItemsFromParent(void);
	void	DeleteSelectedItems(void);
	void	ExecuteMoveItem(int GlobalDx,int GlobalDy,bool AllItems);

    void    GetCenter(int &cx, int &cy);

	bool	ExecuteInitialAfterEdit(ExecuteInitialAfterEditInfo &EInfo);
	bool	ExecuteStartByInspection(void);
	bool	ExecuteProcessing(AlgorithmItemPI *FirstData);

    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file ,MatchShiftRotationInPage *parent);
    bool    SaveUnique(QIODevice *file);
    bool    LoadUnique(QIODevice *file);

	DataInPage	*GetDataInPage(void);
	virtual	void	Draw	 (QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawItems(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove (int dx,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);

private:
	void	ExecuteProcessingMakeCalc(AlgorithmItemPI* FirstData);
};


class   MatchShiftRotationInPage : public AlgorithmInPagePI
{
	friend	class	XMatchShiftRotationArea;

public:
	NPListPack<XMatchShiftRotationArea>  Areas;				//Area statement
	IntList		CurrentSelectedAreaID;
	bool		ModeShowArea;
public:

	MatchShiftRotationInPage(AlgorithmBase *parent);
	~MatchShiftRotationInPage(void);

	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType) override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item) override;
	virtual	void	RemoveItem(AlgorithmItemRoot *item) override;

	XMatchShiftRotationArea	*GetMatchShiftRotationArea(int AreaID);
	int						GetMatchShiftRotationCount(void);
	void	RemoveArea(XMatchShiftRotationArea *a);
	virtual	bool		Save(QIODevice *f) override;
	virtual	bool		Load(QIODevice *f) override;

	virtual	ExeResult	ExecuteStartByInspection(int ExeID ,ResultInPageRoot *Res) override;
	virtual	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ExeResult	ExecuteProcessing		(int ExeID ,ResultInPageRoot *Res) override;

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
	void	UndoSetIndependentItemNameDataCommand(QIODevice *f);

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

private:
	bool	ExistArea(int localX,int localY);
};

class	MatchShiftRotationBase	: public AlgorithmBase
{
public:
	QColor		ColorArea;
	QColor		ColorAreaSelected;
	QColor		ColorAreaActive;
	QColor		ColorPoint;
	QColor		ColorPointSelected;
	QColor		ColorPointActive;
	int32		AlphaLevel;		//Transparent Level to display area and points
	int			RoughSeparationAngle;
	int			RoughSeparationShift;
	int			RoughSeparationIsolation;

	MatchShiftRotationBase(LayersBase *Base);

	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)	override	{	return(new MatchShiftRotationInPage(parent));	}
	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)				override;
	virtual	QString	GetDataText(void)			override {	return QString("MatchShiftRotation");	}
	virtual	QString	GetDefaultFileName(void)	override {	return QString("ConfigMatchShiftRotation.dat");		}
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer)	override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false) override;

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

};

//=======================================================================================

class	MatchShiftRotationDrawAttr : public AlgorithmDrawAttr , public ServiceForLayers
{
public:
	bool	ModeDrawArea;
	bool	ModeDrawItem;
	IntList	SelectedArea;	//Use for item view

	MatchShiftRotationDrawAttr(void);
	MatchShiftRotationDrawAttr(LayersBase *Base);
	MatchShiftRotationDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol ,int AlphaLevel);

	void	Initial(void);

	MatchShiftRotationDrawAttr	&operator=(MatchShiftRotationDrawAttr &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	MatchShiftRotationDrawAttr::MatchShiftRotationDrawAttr(void)
	:ServiceForLayers(NULL)
{
	ModeDrawArea	=false;
	ModeDrawItem	=false;
}

inline	MatchShiftRotationDrawAttr::MatchShiftRotationDrawAttr(LayersBase *Base)
	:ServiceForLayers(Base)
{
	ModeDrawArea	=false;
	ModeDrawItem	=false;
}

inline	MatchShiftRotationDrawAttr::MatchShiftRotationDrawAttr(LayersBase *Base,QColor ncol,QColor scol ,QColor acol ,int AlphaLevel)
	:ServiceForLayers(Base)
{
	NormalColor		=ncol;
	SelectedColor	=scol;
	ActiveColor		=acol;
	NormalColor		.setAlpha(AlphaLevel);
	SelectedColor	.setAlpha(AlphaLevel);
	ActiveColor		.setAlpha(AlphaLevel);
	ModeDrawArea	=false;
	ModeDrawItem	=false;
}

inline	MatchShiftRotationDrawAttr	&MatchShiftRotationDrawAttr::operator=(MatchShiftRotationDrawAttr &src)
{
	AlgorithmDrawAttr::operator=(*((AlgorithmDrawAttr *)&src));
	ServiceForLayers::Copy(this);
	ModeDrawArea			=src.ModeDrawArea	;
	ModeDrawItem			=src.ModeDrawItem	;

	SelectedArea			=src.SelectedArea		;

	return *this;
}
inline	bool	MatchShiftRotationDrawAttr::Save(QIODevice *f)
{
	if(::Save(f,ModeDrawArea)==false)
		return false;
	if(::Save(f,ModeDrawItem)==false)
		return false;

	if(SelectedArea.Save(f)==false)
		return false;

	return true;
}
inline	bool	MatchShiftRotationDrawAttr::Load(QIODevice *f)
{
	if(::Load(f,ModeDrawArea)==false)
		return false;
	if(::Load(f,ModeDrawItem)==false)
		return false;

	if(SelectedArea.Load(f)==false)
		return false;

	return true;
}

//==========================================================================
class	MatchShiftRotationItemList : public NPListSaveLoad<MatchShiftRotationItemList>
{
public:
	struct{
		int		ItemID;
		int		LibID;
		int		CenterX,CenterY;
		int		x1,y1,x2,y2;
	}Data;
	QString		ItemName;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	MatchShiftRotationItemList::Save(QIODevice *f)
{
	if(f->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(::Save(f,ItemName)==false)
		return false;
	return true;
}
inline	bool	MatchShiftRotationItemList::Load(QIODevice *f)
{
	if(f->read((char *)&Data,sizeof(Data))!=sizeof(Data))
		return false;
	if(::Load(f,ItemName)==false)
		return false;

	return true;
}
class	MatchShiftRotationItemListPack : public NPListPackSaveLoad<MatchShiftRotationItemList>
{
public:
	MatchShiftRotationItemListPack(void){}

	virtual	MatchShiftRotationItemList	*Create(void)	{	return new MatchShiftRotationItemList();	}
};

//==========================================================================
class	MatchShiftRotationInfoList : public NPListSaveLoad<MatchShiftRotationInfoList>
{
public:
	int		LibID;
	IntList	MatchShiftRotationCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	MatchShiftRotationInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(MatchShiftRotationCount.Save(f)==false)
		return false;
	return true;
}
inline	bool	MatchShiftRotationInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(MatchShiftRotationCount.Load(f)==false)
		return false;
	return true;
}
class	MatchShiftRotationInfoListPack : public NPListPackSaveLoad<MatchShiftRotationInfoList>
{
public:
	MatchShiftRotationInfoListPack(void){}

	virtual	MatchShiftRotationInfoList	*Create(void)	{	return new MatchShiftRotationInfoList();	}
};
//==========================================================================

class	MatchShiftRotationThresholdReq
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	MatchShiftRotationThresholdReq(void);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MatchShiftRotationThresholdSend
{
public:
	int32	GlobalPage;
	int		ItemID;
	bool	Mastered;
	int32	Dx,Dy;

	int32		SearchArea;
	int32		SearchAngle;

	WORD		TargetLayer	;
	int32		SearchLittleInItem	;
	double		MatchingRate;

	MatchShiftRotationThresholdSend(void);

	void	ConstructList(MatchShiftRotationThresholdReq *reqPacket,MatchShiftRotationBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	MatchShiftRotationReqTryThreshold
{
public:
	int32	GlobalPage;
	int32	Layer;
	int		ItemID;	
	int		AreaID;

	int32		SearchArea;
	int32		SearchAngle;

	MatchShiftRotationItem	Threshold;

	MatchShiftRotationReqTryThreshold(void);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,LayersBase *LBase);
};

class	MatchShiftRotationSendTryThreshold : public AddedDataClass
{
public:
	ResultInItemRoot	*Result;
	double      ResultDx,ResultDy,ResultAngle;	//Calculated position
	double		ResultMatchingRate;

	MatchShiftRotationSendTryThreshold(void);
	~MatchShiftRotationSendTryThreshold(void);

	void	ConstructList(MatchShiftRotationReqTryThreshold *reqPacket,MatchShiftRotationBase *Base);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
//==========================================================================

class	CmdCreateTempMatchShiftRotationLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;

	CmdCreateTempMatchShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdGetMatchShiftRotationLibraryListInPastePacket : public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;
	CmdGetMatchShiftRotationLibraryListInPastePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMatchShiftRotationLibraryListInPastePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdInsertMatchShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdInsertMatchShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdInsertMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdUpdateMatchShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdUpdateMatchShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdUpdateMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMatchShiftRotationLibraryNamePacket : public GUIDirectMessage
{
public:
	int					LibID;
	QString				LibName;
	bool				Success;
	CmdGetMatchShiftRotationLibraryNamePacket(LayersBase *base):GUIDirectMessage(base){}
	CmdGetMatchShiftRotationLibraryNamePacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdGetMatchShiftRotationLibraryListPacket :public GUIDirectMessage
{
public:
	int			LibFolderID;
	AlgorithmLibraryListContainer	AList;

	CmdGetMatchShiftRotationLibraryListPacket(LayersBase *base):GUIDirectMessage(base)			{		}
	CmdGetMatchShiftRotationLibraryListPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{		}
};

class	CmdLoadMatchShiftRotationLibraryPacket :public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	bool				Success;

	CmdLoadMatchShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdClearMatchShiftRotationLibraryPacket: public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdClearMatchShiftRotationLibraryPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdClearMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdDeleteMatchShiftRotationLibraryPacket : public GUIDirectMessage
{
public:
	AlgorithmLibraryLevelContainer	*Point;
	CmdDeleteMatchShiftRotationLibraryPacket (LayersBase *base):GUIDirectMessage(base){}
	CmdDeleteMatchShiftRotationLibraryPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	AddMatchShiftRotationAreaPacket : public GUIDirectMessage
{
public:
	FlexArea		Area;
	QString			AreaName;
	int				LibID;

	AddMatchShiftRotationAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMatchShiftRotationAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyMatchShiftRotationAreaPacket : public GUIDirectMessage
{
public:
	int				AreaID;
	FlexArea		Area;
	QString			AreaName;
	int				LibID;

	ModifyMatchShiftRotationAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyMatchShiftRotationAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	AddMatchShiftRotationPointPacket : public GUIDirectMessage
{
public:
	int			AreaID;
	FlexArea	Area;
	int			LibID;
	QString		ItemName;

	AddMatchShiftRotationPointPacket(LayersBase *base):GUIDirectMessage(base){}
	AddMatchShiftRotationPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	ModifyMatchShiftRotationPointPacket : public GUIDirectMessage
{
public:
	int			ItemID;
	int			LibID;
	QString		ItemName;

	ModifyMatchShiftRotationPointPacket(LayersBase *base):GUIDirectMessage(base){}
	ModifyMatchShiftRotationPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	DeleteMatchShiftRotationPointPacket : public GUIDirectMessage
{
public:
	int			ItemID;

	DeleteMatchShiftRotationPointPacket(LayersBase *base):GUIDirectMessage(base){}
	DeleteMatchShiftRotationPointPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdCreateTempMatchShiftRotationItemPacket : public GUIDirectMessage
{
public:
	MatchShiftRotationItem	*Point;
	CmdCreateTempMatchShiftRotationItemPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdCreateTempMatchShiftRotationItemPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
class	CmdReqMatchShiftRotationInfoListPack : public GUIDirectMessage
{
public:
	int	AreaID;
	MatchShiftRotationInfoListPack	Points;

	CmdReqMatchShiftRotationInfoListPack(LayersBase *base):GUIDirectMessage(base){}
	CmdReqMatchShiftRotationInfoListPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};


class	RemoveMatchShiftRotationAreaPacket : public GUIDirectMessage
{
public:
	int			AreaID;

	RemoveMatchShiftRotationAreaPacket(LayersBase *base):GUIDirectMessage(base)			{	AreaID=-1;	}
	RemoveMatchShiftRotationAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	AreaID=-1;	}
};

class	GetSelectedMatchShiftRotationAreaPacket : public GUIDirectMessage
{
public:
	QByteArray	BuffData;

	GetSelectedMatchShiftRotationAreaPacket(LayersBase *base):GUIDirectMessage(base){}
	GetSelectedMatchShiftRotationAreaPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	CmdReqMatchShiftRotationItemPack : public GUIDirectMessage
{
public:
	int			AreaID;
	MatchShiftRotationItemListPack	*Items;

	CmdReqMatchShiftRotationItemPack(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqMatchShiftRotationItemPack(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	CmdReqMatchShiftRotationItemImages : public GUIDirectMessage
{
public:
	int			AreaID;
	int			ItemID;
	FlexAreaImageListCoeffAngleContainer	*Patterns;

	CmdReqMatchShiftRotationItemImages(LayersBase *base):GUIDirectMessage(base)			{}
	CmdReqMatchShiftRotationItemImages(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{}
};

class	ReqShiftRotaionResult : public GUIDirectMessage
{
public:
	int		AreaID;
	double	Angle;
	int		ShiftX;
	int		ShiftY;
	bool	Found;

	ReqShiftRotaionResult(LayersBase *base):GUIDirectMessage(base)			{	Found=false;	}
	ReqShiftRotaionResult(GUICmdPacketBase *gbase):GUIDirectMessage(gbase)	{	Found=false;	}
};


#endif
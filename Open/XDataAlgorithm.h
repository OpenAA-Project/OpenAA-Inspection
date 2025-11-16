/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDataAlgorithm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XDataAlgorithmH
#define XDataAlgorithmH

#include <QIODevice>
#include <QMouseEvent>
#include <QColor>
#include "XTypeDef.h"
#include "NList.h"
#include "NListComp.h"
#include "XFlexArea.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XVector.h"
#include "XParamBase.h"
#include "XLearningRule.h"
#include "XCSV.h"
#include "XDot.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XMapBuffer.h"
#include "XAlgorithmLibNGType.h"
#include "XUndoBase.h"
#include "XReportedTopic.h"
#include "XHistgramByParam.h"
#include "XManualExecuter.h"
#include "XAlgorithmCommon.h"
#include "XDataAlgorithmThreshold.h"
#include "XDataAlgorithmPipe.h"

enum	ModelType{	Model_PLI=1	,Model_PI=2	};

const	int	MIN_COUNT_ForTHREAD=4;

//=================================================================================================================
class	AlgorithmItemRoot;
class   AlgorithmInLayerRoot;
class   AlgorithmInPageRoot;
class	AlgorithmInPageInOnePhase;
class   AlgorithmBase;
class	AlgorithmParentFromItem;
class	DataInPage;
class	DataInLayer;
class	LayersBase;
class	ParamGlobal;
class	ParamComm;
class	ResultInItemRoot;
class	ResultInLayerRoot;
class	ResultInPageRoot;
class	ResultBasePhase;
class	ResultBaseForAlgorithmRoot;
class	GUIDirectMessage;
class	ClipboardAlgorithmItem;
class	ClipboardAlgorithm;
class	AlgorithmItemIndependentPack;
class	AlgorithmLibraryListContainer;
class	AlgorithmLibrary;
class	AlgorithmLibraryLevelContainer;
class	AlgorithmLibraryList;
class	SelectLibListContainer;
class	OriginNames;
class	ItemPointerListInPage;
class	ItemPointerListInLayer;
class	ItemPointerList;
class	ExpandedSelectedItemListContainer;
class	VectorLineBase;
class	ReportedTopic;
class	LotInformation;
class	ListPageLayerIDPack;
class	AlgorithmLibraryStocker;
class	AlgorithmItemIndependent;
class	LearningMenu;
class	LearningResource;
class	ChangedMap;
class	DetailResultInfoListContainer;
class	AlgorithmItemPointerListContainer;
class	ConfirmItemListContainer;
class	TransformBase;
class	RootNameList;
class	AnyDataContainer;

//==========================================================================

class	AlgorithmDrawAttr
{
public:
	int32	DType;			//=		DisplayImage::DisplayType
	QColor	UncoveredColor;
	QColor	NormalColor		;
	QColor	SelectedColor	;
	QColor	ActiveColor		;
	bool	ModeDrawRental	;
	int32	LineWidth;

	AlgorithmDrawAttr(void);
	AlgorithmDrawAttr(const QColor &ncol,const QColor &scol ,const QColor &acol);
	AlgorithmDrawAttr(const QColor &ncol ,int ntranparentLevel
					, const QColor &scol ,int stranparentLevel
					, const QColor &acol ,int atranparentLevel);
	virtual	~AlgorithmDrawAttr(void){}

	bool	SaveAttr(QIODevice *f);
	bool	LoadAttr(QIODevice *f);
	AlgorithmDrawAttr	&operator=(const AlgorithmDrawAttr &src);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline	AlgorithmDrawAttr::AlgorithmDrawAttr(void)
:	 UncoveredColor	(Qt::cyan)
	,NormalColor	(Qt::green)
	,SelectedColor	(Qt::yellow)
	,ActiveColor	(Qt::red)
	,ModeDrawRental	(false)
	,LineWidth(1)
{}

inline	AlgorithmDrawAttr::AlgorithmDrawAttr(const QColor &ncol,const QColor &scol ,const QColor &acol)
:	 UncoveredColor	(Qt::cyan)
	,NormalColor	(ncol)
	,SelectedColor	(scol)
	,ActiveColor	(acol)
	,ModeDrawRental	(false)
	,LineWidth(1)
{}

inline	AlgorithmDrawAttr::AlgorithmDrawAttr(
					  const QColor &ncol ,int ntranparentLevel
					, const QColor &scol ,int stranparentLevel
					, const QColor &acol ,int atranparentLevel)
:	 UncoveredColor	(Qt::cyan)
	,NormalColor	(ncol)
	,SelectedColor	(scol)
	,ActiveColor	(acol)
	,ModeDrawRental	(false)
	,LineWidth(1)
{
	NormalColor.setAlpha(ntranparentLevel);	
	SelectedColor.setAlpha(stranparentLevel);	
	ActiveColor.setAlpha(atranparentLevel);	
}

class	AlignmentPacketBase
{
public:
	int32	Page;
	int32	Layer;
	int		SourceID;
	int		LibType;
	int		LibID;
	void	*Handle;
	bool	Calculated;

	AlignmentPacketBase(void){	Page=-1;	Layer=-1;	SourceID=-1;	LibType=-1;	LibID=-1;	Calculated=false;	Handle=NULL;	}
	void	Set(AlgorithmItemRoot *src);
	
	AlignmentPacketBase	&operator=(const AlignmentPacketBase &src);
	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

inline AlignmentPacketBase	&AlignmentPacketBase::operator=(const AlignmentPacketBase &src)
{
	Page		=src.Page;
	Layer		=src.Layer;
	SourceID	=src.SourceID;
	LibType		=src.LibType;
	LibID		=src.LibID;
	Calculated	=src.Calculated;
	Handle		=src.Handle;
	return *this;
}

class	AlignmentPacket2D : public AlignmentPacketBase
{
public:
	int		PosXOnTarget,PosYOnTarget;
	double	ShiftX		,ShiftY;
	double	Rotation;	//Radian
	short	Priority;	//0:Strongest	100:Normal

	AlignmentPacket2D(void){	PosXOnTarget=PosYOnTarget=ShiftX=ShiftY=0;	Rotation=0.0;	Priority=100;	}
	AlignmentPacket2D &operator=(const AlignmentPacket2D &src);
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class   SubtractItem : public NPList<SubtractItem>
{
  public:
    int32	ItemID;
    int32	LibID;
	AlgorithmItemRoot	*IndexAfterEdit;

    SubtractItem(void){}
	SubtractItem(const SubtractItem &src);
    SubtractItem(int itemID ,int libID)
		{   ItemID=itemID;  LibID=libID;	IndexAfterEdit=NULL;    }
	SubtractItem(int itemID ,int libID ,AlgorithmItemRoot *a)
		{   ItemID=itemID;  LibID=libID;	IndexAfterEdit=a;    }

    SubtractItem   &operator=(const SubtractItem &src){
        ItemID  =src.ItemID;
        LibID   =src.LibID;
		IndexAfterEdit	=src.IndexAfterEdit;
        return(*this);
        }
    bool    Save(QIODevice *file);
    bool    Load(QIODevice *file);
};

class   SubtractItemContainer : public NPListPack<SubtractItem>
{
public:
	SubtractItemContainer(void){}
	SubtractItemContainer(const SubtractItemContainer &src);

	SubtractItemContainer	&operator=(const SubtractItemContainer &src);
	IntList	MakeBlockIDList(void);
};

//=========================================================================================

class	ItemDataListWithID : public NPList<ItemDataListWithID>
{
public:
	int32		LibID;
	int32		ItemID;
	int32		ItemClassType;
	int32		Layer;
	short		Error;
	QByteArray	IData;

	ItemDataListWithID(void){	LibID=-1;	ItemID=-1;	ItemClassType=-1;	Layer=-1;	Error=0;	}
	ItemDataListWithID(const ItemDataListWithID &src)
	{
		LibID			=src.LibID;
		ItemID			=src.ItemID;
		ItemClassType	=src.ItemClassType;
		Layer			=src.Layer;
		Error			=src.Error;
		IData			=src.IData;
	}

	ItemDataListWithID	&operator=(const ItemDataListWithID &src)
	{
		LibID			=src.LibID;
		ItemID			=src.ItemID;
		ItemClassType	=src.ItemClassType;
		Layer			=src.Layer;
		Error			=src.Error;
		IData			=src.IData;
		return *this;
	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};
class	ItemDataListWithIDContainer : public NPListPack<ItemDataListWithID>
{
public:
	ItemDataListWithIDContainer(void){}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//=========================================================================================

class	ItemDataWithPhasePageLayer : public NPListSaveLoad<ItemDataWithPhasePageLayer>
{
public:
	int32		ItemID;
	int32		Layer;
	int32		Page;
	int32		Phase;
	QByteArray	Data;

	ItemDataWithPhasePageLayer(void){	ItemID=-1;	Layer=-1;	Page=-1;	Phase=-1;	}
	ItemDataWithPhasePageLayer(const ItemDataWithPhasePageLayer &src)
	{
		ItemID			=src.ItemID;
		Layer			=src.Layer;
		Page			=src.Page;
		Phase			=src.Phase;
		Data			=src.Data;
	}

	ItemDataWithPhasePageLayer	&operator=(const ItemDataWithPhasePageLayer &src)
	{
		ItemID			=src.ItemID;
		Layer			=src.Layer;
		Page			=src.Page;
		Phase			=src.Phase;
		Data			=src.Data;
		return *this;
	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class	ItemDataWithPhasePageLayerContainer : public NPListPackSaveLoad<ItemDataWithPhasePageLayer>
{
public:
	ItemDataWithPhasePageLayerContainer(void){}
	ItemDataWithPhasePageLayerContainer(const ItemDataWithPhasePageLayerContainer &src);

	virtual	ItemDataWithPhasePageLayer	*Create(void);
};

//=========================================================================================
class	AlgorithmItemCountInPage : public NPList<AlgorithmItemCountInPage>
{
public:
	IntList	CountInLayer;

	AlgorithmItemCountInPage(void){}
	AlgorithmItemCountInPage(const AlgorithmItemCountInPage &src){	CountInLayer=src.CountInLayer;	}

	AlgorithmItemCountInPage	&operator=(const AlgorithmItemCountInPage &src)
									{	CountInLayer=src.CountInLayer;	return *this;	}
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AlgorithmItemCountInBase : public NPList<AlgorithmItemCountInBase>
{
public:
	NPListPack<AlgorithmItemCountInPage>	CountInPage;
	QString	AlgoRoot;
	QString	AlgoName;

	AlgorithmItemCountInBase(void){}

	AlgorithmItemCountInBase	&operator=(const AlgorithmItemCountInBase &src);
	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	ShowAndSetItemsBaseClass
{
public:
	ShowAndSetItemsBaseClass(void){}
	virtual	~ShowAndSetItemsBaseClass(void){}
};

class	BindedThresholdList : public NPListSaveLoad<BindedThresholdList>
{
public:
	IntList		ItemIDs;
	int32		Layer;
	int32		LibID;
	QByteArray	ThresholdData;

	BindedThresholdList(void){	LibID=-1;	}

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	BindedThresholdContainer : public NPListPackSaveLoad<BindedThresholdList>
{
public:
	BindedThresholdContainer(void){}

	virtual	BindedThresholdList	*Create(void)	override	{	return new BindedThresholdList();	}
};

//=========================================================================================
class	AlgorithmItemPropertyBase : public ParamBase ,public NPList<AlgorithmItemPropertyBase> ,public ServiceForLayers
{
	int64				LibID;
	QString				DLLRoot;
	QString				DLLName;
  #pragma	pack(push,1)
	int					ItemPage;
	int					Itemlayer;
	int					ItemID;
  #pragma	pack(pop)
public:
	AlgorithmItemPropertyBase(LayersBase *base);
	virtual	~AlgorithmItemPropertyBase(void);

	virtual	void	CopyFrom(AlgorithmItemRoot *src)	=0;
	virtual	void	CopyTo  (AlgorithmItemRoot *dst)	=0;
	virtual	AlgorithmItemPropertyBase	*Create(void)	=0;

	virtual	bool	Save(QIODevice *f);
    virtual	bool	Load(QIODevice *f);

	NPListPack<ParamStruct>	&GetParamData(void){	return ParamData;	}
};

class	AlgorithmItemPropertyContainer : public NPListPack<AlgorithmItemPropertyBase>
{
public:
	AlgorithmItemPropertyContainer(void){}

	AlgorithmItemPropertyContainer	&operator=(const AlgorithmItemPropertyContainer &src);
};

//=========================================================================================

class	ItemSearchGroup : public NPList<ItemSearchGroup>
{
	int32	SearchID;
	int32	SearchDot;

	class	ItemPointerList : public NPList<ItemPointerList>
	{
		AlgorithmItemRoot	*ItemPointer;
		int64				ItemID;
	public:
		ItemPointerList(void);
		explicit	ItemPointerList(AlgorithmItemRoot *item);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	NPListPack<ItemPointerList>	Items;

public:
	ItemSearchGroup(void);

	int		GetSearchDot(void)		const	{	return SearchDot;	}
	void	SetSearchDot(int sdot)			{	SearchDot=sdot;		}
	int		GetSearchID(void)		const	{	return SearchID;	}
	void	SetSearchID(int sID)			{	SearchID=sID;		}

	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	ExeResult	ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	ClearAllItems(void);
	void	AppendItem(AlgorithmItemRoot *item);
};

class	ItemSearchGroupContainer : public NPListPack<ItemSearchGroup>
{
public:
	ItemSearchGroupContainer(void){}


	bool	SaveGroup(QIODevice *f);
	bool	LoadGroup(QIODevice *f);
};

class	UniqueAreaType
{
public:
	QString	TypeName;
	int		Code;

	UniqueAreaType(void){	Code=-1;	}
};
//=========================================================================================

class	AlgorithmItemIndex
{
public:
	struct{
		int32	ShadowLevel ;
		int32	ShadowNumber;
		int64	ItemID;
		int32	Layer;
		int32	Page;
		int32	Phase;
	}IndexInAlgorithm;
	QString	DLLRoot	;
	QString	DLLName	;

	AlgorithmItemIndex(void);
	AlgorithmItemIndex(int _ItemID,int _Layer=-1 ,int _Page=-1 ,int _Phase=-1 ,int ShadowNumber=0 ,int ShadowLevel=0);
	AlgorithmItemIndex(int _ItemID,int _Layer ,int _Page ,int _Phase 
						,const QString &dllRoot,const QString &dllName);
	AlgorithmItemIndex(int _ItemID,int _Layer ,int _Page ,int _Phase 
						,int _ShadowNumber,int _ShadowLevel
						,const QString &dllRoot,const QString &dllName);
	AlgorithmItemIndex(const AlgorithmItemIndex &src);
	AlgorithmItemIndex(const AlgorithmItemRoot &src);
	virtual	~AlgorithmItemIndex(void){}

	int		GetShadowLevel(void)	const	{	return IndexInAlgorithm.ShadowLevel ;	}
	int		GetShadowNumber(void)	const	{	return IndexInAlgorithm.ShadowNumber;	}
	int		GetItemID(void)			const	{	return IndexInAlgorithm.ItemID;	}
	int		GetLayer(void)			const	{	return IndexInAlgorithm.Layer;	}
	int		GetPage(void)			const	{	return IndexInAlgorithm.Page;	}
	int		GetPhase(void)			const	{	return IndexInAlgorithm.Phase;	}
	QString	GetDLLRoot(void)		const	{	return 	DLLRoot	;				}
	QString	GetDLLName(void)		const	{	return 	DLLName	;				}

	void	Set(int _ItemID,int _Layer ,int _Page ,int Phase 
						,const QString &dllRoot,const QString &dllName);
	void	Set(int _ItemID,int _Layer ,int _Page ,int Phase 
						,int _ShadowNumber,int _ShadowLevel
						,const QString &dllRoot,const QString &dllName);
	void	Set(const AlgorithmItemRoot &Item);

	void	SetShadowLevel(int _ShadowLevel)	{	IndexInAlgorithm.ShadowLevel =_ShadowLevel;		}
	void	SetShadowNumber(int _ShadowNumber)	{	IndexInAlgorithm.ShadowNumber=_ShadowNumber;	}
	void	SetItemID(int itemid)				{	IndexInAlgorithm.ItemID	=itemid;	}
	void	SetLayer(int layer)					{	IndexInAlgorithm.Layer	=layer;		}
	void	SetPage(int page)					{	IndexInAlgorithm.Page	=page;		}
	void	SetPhase(int phase)					{	IndexInAlgorithm.Phase	=phase;		}
	void	SetDLLRoot(const QString &dllRoot)	{	DLLRoot	=dllRoot;	}	
	void	SetDLLName(const QString &dllName)	{	DLLName	=dllName;	}

	AlgorithmItemIndex	&operator=(const AlgorithmItemIndex &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

//=========================================================================================

#define		DrawType_Selected	0x01
#define		DrawType_Active		0x02

enum Type_ItemComment
{
	 _TypeItemComment_Normal
	,_TypeItemComment_Simple
};
 
//=========================================================================================

class	AlgorithmItemRoot :public LearningValueByLib,public IdentifiedClass
{
	FlexArea			Area;
	VectorLineBase		*VBase;
  #pragma	pack(push,1)
	struct{
		bool			Effective:1;
		bool			Selected:1;
		bool			Active:1;
		bool			EditLocked:1;
		bool			Changed:1;
		bool			CalcDone:1;
		bool			Visible:1;
		bool			InvertLogic:1;		//論理反転　これを使うロジックは個々のアルゴリズ?で実装する
		bool			FromRental:1;
		bool			Editable:1;			//部品から生成されたようなときの編集可?属性
		bool			ManualCreated:1;
		bool			ProcessDone:1;
		bool			CalcEnable:1;		//Enable inspection process.  Implement in each algorithm
		bool			MultiSelection:1;
		bool			ModeReferedAttr:1;	//部品由来のデータのときtrue
		bool			LastMakeHistgramData:1;
		bool			ThroughAllPhases:1;
	};
  #pragma	pack(pop)
	QString				ItemName;
	
protected:
  #pragma	pack(push,1)
	int64				ItemID;				//無設定時 -1
	int64				LibID;
	int32				LoadedVersion;
    int32				PartsID;			//部品番号		無設定時 -1
    int32				PartsAllocID;       //部品配置ＩＤ
    int32				PartsItemID;
	int32				MasterNo;
	ResultInItemRoot			*ResultInThisTime;	
	AlgorithmThresholdContainer	ThresholdStocker;
	AlgorithmThresholdContainer	*ThresholdStockerPointer;
	AlgorithmBase				*Origin;
	LibNGTypeInAlgorithm		*NGTypePoint;
protected:
	OriginType		GeneratedOrigin;
  #pragma	pack(pop)
    SubtractItemContainer	SubBlock;	//除外ブロック番号

public:
	enum _MirrorMode{
		_XMirror	=1
		,_YMirror	=2
	};

	AlgorithmItemRoot(void);
	AlgorithmItemRoot(FlexArea &area);
	AlgorithmItemRoot(FlexArea *area);	//use area memory
	virtual	~AlgorithmItemRoot(void);

	virtual	void	InitialAfterParamLoaded(void){}
	virtual	void	SetParentVirtual(AlgorithmParentFromItem *parent)	=0;

	virtual	AlgorithmItemRoot	*Clone(void)	=0;

	virtual	bool		Save(QIODevice *f);
	virtual	bool		Load(QIODevice *f,LayersBase *LBase);
	virtual	bool		SaveUnique(QIODevice *f){	return true;	}
	virtual	bool		LoadUnique(QIODevice *f){	return true;	}
	virtual	bool		SaveForLearning(QIODevice *f);
	virtual	bool		LoadForLearning(QIODevice *f,LayersBase *LBase);
	bool	SaveHistgram(QIODevice *f);
	bool	LoadHistgram(QIODevice *f);

	virtual	bool	Transform(TransformBase &Param);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	AlgorithmItemRoot	&operator=(const AlgorithmItemRoot &src);
	virtual	void	CopyFrom(AlgorithmItemRoot *src);
	virtual	void	TransformCopyFrom(TransformBase &Param,const AlgorithmItemRoot &src);

	virtual	FlexArea	&GetArea(void);
	virtual	const FlexArea	&GetArea(void)	const;
	virtual	FlexArea	&GetArea(int UniqueAreaType_Code)	{	return GetArea();	}
	virtual	void		SetArea(const FlexArea &area);
	virtual	bool		ShrinkItems(int ExpandPixels,BYTE **Mask=NULL);
			void		MoveAreaPointer(FlexArea *area);
	virtual	bool		IsEffective(void)	const;
	virtual	void		SetEffective(bool effective);
	virtual	void		SetVector(VectorLineBase &src);
	virtual	void		SetVector(VectorLineBase *src);
	virtual	bool	HasVector(void)					{	return (VBase!=NULL)?true:false;	}
	virtual	VectorLineBase	*GetVector(void)		{	return VBase;	}
	virtual	VectorLineBase	*GetVector(void)const	{	return VBase;	}
	virtual	bool		IsValid(void);
	virtual	FlexArea	GetInspectedArea(void);
	int				GetLoadedVersion(void);		//-1:Can't find version

	virtual	void		SetMasterNo(int _MasterNo);
	virtual	int			GetMasterNo(void);
	virtual	bool		ReallocateMasterCount(int CountMaster);

	bool	CheckInAreaAfterShift(int mx ,int my ,int MerginX=0,int MerginY=0);

	virtual	int32		GetItemClassType(void)		{		return 0;		}
	virtual	OriginType	GetOriginType(void)	const	{		return GeneratedOrigin;	}
	virtual	void		SetOriginType(OriginType b)	{		GeneratedOrigin=b;		}

	virtual	AlgorithmThreshold			*GetThresholdBaseWritable(LayersBase *base=NULL,int ThresholdLevelID=-1);
	virtual	const	AlgorithmThreshold	*GetThresholdBaseReadable(LayersBase *base=NULL,int ThresholdLevelID=-1);
	virtual	void	SwitchThresholdLevel(int OldLevel ,int NewLevel);
	virtual	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);
	virtual	void	CopyThresholdFromLibrary(AlgorithmLibraryLevelContainer *src);

	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)			=0;

	void	SetNewThresholdInstance(LayersBase *base ,int ThresholdLevelID=-1);
	virtual	void	CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)				=0;
	bool	IsEditable(void)	const				{	return Editable;	}
	virtual	VectorLineBase	*CreateVectorBase(void)	{	return NULL;		}
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines){}

	virtual	AlgorithmItemPropertyBase	*CreateAlgorithmItemProperty(void){	return NULL;	}

	virtual	void	SetRefereneFrom(AlgorithmItemRoot *src ,int OffsetX ,int OffsetY);
	virtual	void	MasterImageHasChanged(void)	{}
	virtual	void	CopyAttrFrom(AlgorithmItemRoot *SrcItem);
	virtual	void	SetPartsData(int PartsID ,int PartsAllocID ,int PartsItemID);
	AlgorithmLibraryContainer		*GetLibraryContainer(void)	const;
	AlgorithmLibraryLevelContainer	*GetLibrary(void);					//Instance is created inside, so it must be deleted
	AlgorithmLibraryLevelContainer	*GetLibFromManagedCacheLib(void);	//Instance is created inside, so it must be deleted
	bool	GetLibrary(AlgorithmLibraryLevelContainer &Dest);

	virtual	bool	IsInclude(int x ,int y)	const;
	virtual	bool	IsCrossed(FlexArea *b)	const;
	virtual	bool	IsCrossed(int x1, int y1 ,int x2, int y2)	const;
	virtual	bool	GetXY(int &x1 ,int &y1 ,int &x2 ,int &y2)	const;
	virtual	bool	GetXY(double &x1 ,double &y1 ,double &x2 ,double &y2)	const;
	virtual	bool	GetCenter(int &cx ,int &cy)			const;
	virtual	bool	GetCenter(double &cx ,double &cy)	const;
	virtual	void	GetMultiSelectOrign(int &cx ,int &cy)	{	GetCenter(cx,cy);		}

	virtual	bool	IsNull(void)			const;
	virtual	void	MoveTo(int dx ,int dy);
	virtual	void	ClipPage(void);
	virtual	void	ClipPage(int DotPerLine ,int MaxLines);

	virtual	void	ResetCalcDone(void)			{	CalcDone=false;		}
	virtual	bool	IsCalced(void)		const	{	return(CalcDone);	}
	virtual	void	FinishCalc(void)			{	CalcDone=true;		}
	virtual	void	ResetProcessDone(void)		{	ProcessDone=false;	}
	virtual	bool	IsProcessDone(void)	const	{	return(ProcessDone);}
	virtual	void	SetProcessDone(bool b=true)	{	ProcessDone=b;		}

	virtual	bool	CanBeProcessing(void);
	virtual	int		GetLibType(void)	const;
	virtual	int		GetLibID(void)				{	return LibID;		}
	virtual	void	SetLibID(int libID)			{	LibID=libID;		}
	virtual	void	ChangeLibID(int newLibID)	{	LibID=newLibID;		}
	virtual	ResultInItemRoot	*GetCurrentResult(void)	{	return ResultInThisTime;	}
	virtual	ResultInItemRoot	*GetResult(ResultInPageRoot *Rp)	=0;

	virtual	void	SetCurrentResult(ResultInItemRoot *d);
	virtual	void	ClearResult(void)	{}

	virtual	bool	IsOriginParts(void)	const	{	return (PartsID>=0)?true:false;	}
	virtual	AlgorithmBase		*GetOrigin(void){	return Origin;	}
	virtual	void	SetOrigin(AlgorithmBase	*origin){	Origin=origin;	}
	virtual	bool	ReloadFromLibrary(void);
	virtual	void	SetError(short e);
	bool	GetModeReferedAttr(void){	return ModeReferedAttr;	}
	void	SetMakeHistgramData(bool b)			{	LastMakeHistgramData=b;			}
	bool	GetMakeHistgramData(void)	const	{	return LastMakeHistgramData;	}

	virtual	int		GetDrawPriprity(int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);	//0: the most top 
	virtual	void	DrawArea  (FlexArea &area	,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawVector(VectorLineBase *V,QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawAlpha(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr ,const QColor &DefaultColor=Qt::black);
	virtual	void	DrawMove		 (int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMoveTemporary(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);
	virtual	void	DrawResult    (ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate);
	virtual	void	DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);
	virtual	void	SetIndependentItemData(int32 Command
											,int32 LocalPage,int32 Layer
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData);

	virtual	void	DrawMonoBitmap(BYTE **BmpPoint);
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy);
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY);
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage);

	virtual	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo){	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,int ThreadNo,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo){	return _ER_true;	}
	virtual	ExeResult	ExecuteStartByInspection(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteCaptured			(int ExeID,int ThreadNo,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList){	return _ER_true;	}
	virtual	ExeResult	ExecutePreAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteAlignment		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePreProcessing	(int ExeID,int ThreadNo,ResultInItemRoot *Res);
	virtual	ExeResult	ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessingRevived(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostProcessing	(int ExeID,int ThreadNo,ResultInItemRoot *Res);
	virtual	ExeResult	ExecutePreScanning		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteScanning			(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostScanning		(int ExeID,int ThreadNo,ResultInItemRoot *Res){	return _ER_true;	}

	virtual	void	MoveForAlignment(void){}

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map){}

	virtual	bool	GeneralDataRelease(int32 Command,void *data);
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData);
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataReply(int32 Command,void *data);

	virtual	ClipboardAlgorithmItem	*CreateClipboardItem(void);
	virtual	bool	FromClipboardItem(ClipboardAlgorithmItem *Src,LayersBase *LBase);

	//void			GetShiftAfterAlignment(double &dx ,double &dy ,WORD OmitVectorIndex);
	//アラインメント情報取得手段
	//	・ExecuteInitialAfterEdit内でGetAlignmentPointerを呼んで、アラインメントデ???イン?を取得する
	//	・ExecuteAlignment以?で、GetAlignmentForProcessingを呼ぶ
	AlignmentPacketBase	*GetAlignmentPointer(int localX ,int localY ,bool FromGlobal=true);
	void			GetAlignmentForProcessing(AlignmentPacketBase &Packet);

	virtual	void	SetSelected(bool b)			{	Selected=b;			}
	virtual	bool	GetSelected(void)			{	return Selected;	}
	virtual	void	SetEditLocked(bool b)		{	EditLocked=b;		}
	virtual	bool	GetEditLocked(void)			{	return EditLocked;	}
	virtual	void	SetActive(bool b)			{	Active=b;			}
	virtual	bool	GetActive(void)				{	return Active;		}
	virtual	void	SetVisible(bool b)			{	Visible=b;			}
	virtual	bool	GetVisible(void)			{	return Visible;		}
	virtual	void	SetManualCreated(bool b)	{	ManualCreated=b;	GeneratedOrigin=_OriginType_FromManual;	}
	virtual	bool	GetManualCreated(void)		{	return ManualCreated;	}
	virtual	void	SetInvertLogic(bool b)		{	InvertLogic=b;		}
	virtual	bool	GetInvertLogic(void)		{	return InvertLogic;	}
	virtual	void	SetMultiSelection(bool b)	{	MultiSelection=b;	}
	virtual	bool	GetMultiSelection(void)		{	return MultiSelection;	}
	virtual	void	SetThroughAllPhases(bool b)	{	ThroughAllPhases=b;			}
	virtual	bool	GetThroughAllPhases(void)	{	return ThroughAllPhases;	}


	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false);
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy);

	virtual	void	CutArea(FlexArea &localArea,bool &_Changed);

	virtual	void		SetItemID(void)		=0;
	int32				GetID(void)			const	{	return(ItemID);		}
	void				SetID(int id)				{	ItemID=id;			}
	void				SetFromRental(bool b)		{	FromRental=b;		}
	bool				GetFromRental(void)	const	{	return FromRental;	}

	virtual	XYData						GetOutlineOffset(void)	=0;
	virtual	XYData						*GetGlobalOutlineOffset(void);
	virtual	AlgorithmBase				*GetParentBase(void)	const	=0;
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	=0;
	virtual	AlgorithmInPageRoot			*GetParentInPage(void)	const	=0;
	virtual	AlgorithmInLayerRoot		*GetParentInLayer(void)	const	=0;
	virtual	AlgorithmParentFromItem		*GetParentAlgorithm(void)const	=0;
	virtual	LayersBase					*GetLayersBase(void)	const;
	virtual	DataInLayer					*GetDataInLayer(void)	const;
	virtual	DataInPage					*GetDataInPage(void)	const;
	virtual	ParamGlobal					*GetParamGlobal(void)	const;
	virtual	ParamComm					*GetParamComm(void)		const;

	ListPhasePageLayerItem		GetItemIndex(void);
	AlgorithmItemIndex			GetIndex(void);

	int		GetCountAllMasterBuff(void)		const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
	int		GetCountOnlyMasterBuff(void)	const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
	int		GetCountAllBackGroundBuff(void)		const	{	return GetLayersBase()->GetCountAllBackGroundBuff();		}
	int		GetCountOnlyBackGroundBuff(void)	const	{	return GetLayersBase()->GetCountOnlyBackGroundBuff();		}
	int		GetCountDispatchMasterBuff(void)const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}
	int		GetLayerNumb(void)		const;
	int		GetPageNumb(void)		const	{	return (GetParamGlobal()==NULL)?0:GetParamGlobal()->PageNumb;		}
	int		GetPhaseNumb(void)		const	{	return (GetParamGlobal()==NULL)?0:GetParamGlobal()->PhaseNumb;		}
	int		GetDotPerLine(void)		const	
									{	
										DataInPage	*dp=GetDataInPage();
										return (dp==NULL)?0:dp->GetDotPerLine();
									}
	int		GetMaxLines(void)		const
									{	
										DataInPage	*dp=GetDataInPage();
										return (dp==NULL)?0:dp->GetMaxLines();
									}
	int		GetGlobalPage(void);

	int		GetLayer(void)		const;
	int		GetPage(void)		const;
	int		GetPhaseCode(void)	const;
 
	int32	GetPartsID(void)		const	{	return PartsID;			}
	int32	GetPartsAllocID(void)	const	{	return PartsAllocID;	}
	int32	GetPartsItemID(void)	const	{	return PartsItemID;		}
 
	virtual	bool	IsEdited(void)		const;
	virtual	bool	IsCalcDone(void)	const;
	virtual	void	SetEdited(bool edited);
	virtual	void	SetCalcDone(bool calcdone);
	virtual	void	SetItemName(const QString &name)	{	ItemName=name;		}
	virtual	QString GetItemName(void)	const			{	return ItemName;	}
	bool	IsOriginTypeSelection(struct OriginTypeSelection &SelectMode);

	virtual	void	DrawItemListsForPaste(int dx ,int dy 
										,QImage &Pnt,double ZoomRate ,int movx ,int movy);
	virtual	void	ExecuteTransformSelectedItem(TransformBase &M);

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	=0;
	virtual	HistgramByParamBase	*GetHistgramBase(int HistID);
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen);
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected);
	virtual	void	ClearHistgram(void);

	virtual	void	ShrinkArea(int ShrinkDot);
	virtual	void	ShrinkHalf(void);
	virtual	void	ExpandHalf(void);

	void	UndoCutArea(QIODevice *f);

	bool	TF_EnumHistList(HistgramTypeListInAlgoContainer &RetLists);
	bool	TF_ShowHistgramGraph(int HistID);

	LibNGTypeInAlgorithm	*GetLibNGTypeInAlgorithm(void){	return NGTypePoint;	}
	virtual	QString	OutputResult(ResultPosList *p){	return "";	}

	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData);
	virtual	void	MakeIndependentItems(AlgorithmItemIndependent *AInd,int LocalX ,int LocalY)	{}
	virtual	bool	SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)	=0;

	virtual	void	SetAutoThreshold(ParamAutoThreshold &Param){}
	virtual	void	UpdateThreshold(int LearningMenuID ,LearningResource &LRes){}

	virtual	QString	GetComment(Type_ItemComment t)	{	return /**/"";	}

	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	=0;
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL)								=0;
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)							=0;

	virtual	void	ClearSubBlock(void);
	virtual	SubtractItemContainer	&GetSubBlock(void)	{	return SubBlock;	}
	virtual	void	SetSubBlock(const SubtractItemContainer	&src);

	ItemDataListWithID	*MakeItemForLearning(int AddedX,int AddedY,bool OkMode);
	virtual	AlgorithmItemRoot	*SeparateItem(FlexArea &DividedMask);

	//----------- Unit-------------
	bool	IsUnitMode(void);
	double	TransformPixelToUnit(double pixel);
	double	TransformUnitToPixel(double unit);
	QString	TransformPixelToUnitStr(double pixel);
	QString	GetUnitStr(double unit);
	double	TransformPixelToUnitSquare(double pixel);
	double	TransformUnitToPixelSquare(double unit);
	QString	TransformPixelToUnitSquareStr(double pixel);
	QString	GetUnitSquareStr(double unit);

protected:
	virtual	AlgorithmThreshold	*GetThresholdDummy(void)=0;
};

class	AlgorithmThresholdDummy : public AlgorithmThreshold
{
public:
	explicit	AlgorithmThresholdDummy(AlgorithmItemRoot *parent):AlgorithmThreshold(parent){}
	virtual	bool	IsEqual(const AlgorithmThreshold &src)	const	override	{	return true;	}
	virtual	bool	Save(QIODevice *f)	override			{	return true;	}
    virtual	bool	Load(QIODevice *f)	override			{	return true;	}
	virtual	int		GetSize(void)const	override			{	return sizeof(this);	}
};


class	AlgorithmDummyItem : public AlgorithmItemRoot
{
    XYData  DummyOffset;
public:
	AlgorithmDummyItem(void){}

	virtual	AlgorithmItemRoot	*Clone(void)	override	{	return new AlgorithmDummyItem();	}
	virtual	AlgorithmThreshold	*CreateThresholdInstance(void)	override	{	return new AlgorithmThresholdDummy(this);	}
	virtual	void	CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)	override{}

	virtual	void		SetItemID(void)	override{}
	virtual	ResultInItemRoot	*GetResult(ResultInPageRoot *Rp)	override	{	return NULL;	}

	virtual	void	SetParentVirtual(AlgorithmParentFromItem *parent)		override{}
    virtual	XYData						GetOutlineOffset(void)				override{	return DummyOffset;	}
	virtual	AlgorithmBase				*GetParentBase(void)				const	override{	return NULL;	}
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override{	return NULL;	}
	virtual	AlgorithmInPageRoot			*GetParentInPage(void)				const	override{	return NULL;	}
	virtual	AlgorithmInLayerRoot		*GetParentInLayer(void)				const	override{	return NULL;	}
	virtual	AlgorithmParentFromItem		*GetParentAlgorithm(void)			const	override{	return NULL;	}

	virtual	bool	SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)	override{	return true;	}
	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)		override{	return true;	}
	virtual	AlgorithmThreshold	*GetThresholdDummy(void)					override{	return NULL;	}

	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override{	return true;	}
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL)								override{	return true;	}
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)							override{	return true;	}
};


class ChangedMap
{
public:
	BYTE	*Map;
	int32	MapByte;

	ChangedMap(void);
	virtual	~ChangedMap(void);

	void	AllocateByte(int n);
	void	SetChanged(int offset);
	bool	IsChanged(int offset);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	ChangedMap	&operator=(const ChangedMap &src);
};

//================================================================================

class	AlgorithmParentFromItem
{
	AnyDataContainer	*AnyData;
protected:
	AlgorithmItemRoot	**ItemDimPointer;
	int					ItemDimPointerNumb;
	struct{
		bool	ModeParallelExecuteInitialAfterEditPrev	:1;
		bool	ModeParallelExecuteInitialAfterEdit		:1;
		bool	ModeParallelExecuteInitialAfterEditPost	:1;
		bool	ModeParallelExecuteStartByInspection:1;
		bool	ModeParallelExecuteCaptured			:1;
		bool	ModeParallelExecutePreAlignment		:1;
		bool	ModeParallelExecuteAlignment		:1;
		bool	ModeParallelExecutePreProcessing	:1;
		bool	ModeParallelExecuteProcessing		:1;
		bool	ModeParallelExecuteProcessingRevived:1;
		bool	ModeParallelExecutePostProcessing	:1;
		bool	ModeParallelExecutePreScanning		:1;
		bool	ModeParallelExecuteScanning			:1;
		bool	ModeParallelExecutePostScanning		:1;
	}ModeParallel;

public:
	AlgorithmParentFromItem(void);
	~AlgorithmParentFromItem(void);

	AnyDataContainer	*GetAnyData(void)	const	{	return AnyData;	}

	virtual	AlgorithmBase		*GetParentBase(void)					const	=0;
	virtual	LayersBase			*GetLayersBase(void)					const	=0;
	virtual	AlgorithmLibraryContainer	*GetLibraryContainer(void)				=0;

	virtual	XYData						*GetOutlineOffset(void)			const	=0;
	virtual	AlgorithmItemRoot	*SearchIDItem(int itemID)				const	=0;
	virtual	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName)	const	=0;
	virtual	void		FastSearchIDItemStart(void)								=0;
	AlgorithmItemRoot	*FastSearchIDItem(int itemID)					const;
	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)					=0;
	virtual	bool				AppendItem(AlgorithmItemRoot *item)				=0;
	virtual	bool				AppendItem(int Layer ,AlgorithmItemRoot *item)	=0;
	virtual	int64				GetMaxItemID(void)						const	=0;

	virtual	bool				AppendItems(AlgorithmItemPointerListContainer &items)	=0;
	virtual	bool				RemoveItems(AlgorithmItemPointerListContainer &items)	=0;
	virtual	void				RemoveAllDatas(void)							=0;
	virtual	void				RemoveAllDatasByManual(bool CreatedManually)	=0;
	virtual	void				RemoveAllDatasWithoutLocked(void)				=0;
	virtual	void				RemoveAllDatasWithoutManual(void)				=0;

	virtual	bool				CopyShadowAlgorithmItem(ShadowTree *Child , const AlgorithmItemRoot &ParentItem)	=0;

	bool	AppendItemUnknown(AlgorithmItemRoot *item);
	bool	AppendItemManual (AlgorithmItemRoot *item);
	bool	AppendItemLibrary(AlgorithmItemRoot *item);
	bool	AppendItemParts  (AlgorithmItemRoot *item);
	bool	AppendItemGerber (AlgorithmItemRoot *item);

	virtual	void				LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)=0;

	bool	IsModeParallelExecuteInitialAfterEditPrev	(void){	return ModeParallel.ModeParallelExecuteInitialAfterEditPrev	;	}
	bool	IsModeParallelExecuteInitialAfterEdit		(void){	return ModeParallel.ModeParallelExecuteInitialAfterEdit	;		}
	bool	IsModeParallelExecuteInitialAfterEditPost	(void){	return ModeParallel.ModeParallelExecuteInitialAfterEditPost	;	}
	bool	IsModeParallelExecuteStartByInspection		(void){	return ModeParallel.ModeParallelExecuteStartByInspection;	}
	bool	IsModeParallelExecuteCaptured				(void){	return ModeParallel.ModeParallelExecuteCaptured			;	}
	bool	IsModeParallelExecutePreAlignment			(void){	return ModeParallel.ModeParallelExecutePreAlignment		;	}
	bool	IsModeParallelExecuteAlignment				(void){	return ModeParallel.ModeParallelExecuteAlignment		;	}
	bool	IsModeParallelExecutePreProcessing			(void){	return ModeParallel.ModeParallelExecutePreProcessing	;	}
	bool	IsModeParallelExecuteProcessing				(void){	return ModeParallel.ModeParallelExecuteProcessing		;	}
	bool	IsModeParallelExecuteProcessingRevived		(void){	return ModeParallel.ModeParallelExecuteProcessingRevived;	}
	bool	IsModeParallelExecutePostProcessing			(void){	return ModeParallel.ModeParallelExecutePostProcessing	;	}
	bool	IsModeParallelExecutePreScanning			(void){	return ModeParallel.ModeParallelExecutePreScanning		;	}
	bool	IsModeParallelExecuteScanning				(void){	return ModeParallel.ModeParallelExecuteScanning			;	}
	bool	IsModeParallelExecutePostScanning			(void){	return ModeParallel.ModeParallelExecutePostScanning		;	}

protected:
	void	SortDimPointer(void);
};


inline	bool	AlgorithmParentFromItem::AppendItemUnknown(AlgorithmItemRoot *item)
{
	if(item==NULL){
		return false;
	}
	item->SetOriginType(_OriginType_FromUnknown);
	return AppendItem(item);
}

inline	bool	AlgorithmParentFromItem::AppendItemManual (AlgorithmItemRoot *item)
{
	if(item==NULL){
		return false;
	}
	item->SetOriginType(_OriginType_FromManual);
	return AppendItem(item);
}

inline	bool	AlgorithmParentFromItem::AppendItemLibrary(AlgorithmItemRoot *item)
{
	if(item==NULL){
		return false;
	}
	item->SetOriginType(_OriginType_FromLibrary);
	return AppendItem(item);
}

inline	bool	AlgorithmParentFromItem::AppendItemParts  (AlgorithmItemRoot *item)
{
	if(item==NULL){
		return false;
	}
	item->SetOriginType(_OriginType_FromParts);
	return AppendItem(item);
}

inline	bool	AlgorithmParentFromItem::AppendItemGerber (AlgorithmItemRoot *item)
{
	if(item==NULL){
		return false;
	}
	item->SetOriginType(_OriginType_FromCAD);
	return AppendItem(item);
}


class	LinkItemPointerList: public NPList<LinkItemPointerList>
{
public:
	AlgorithmItemRoot	*SrcItem;
	AlgorithmItemRoot	*DstItem;

	LinkItemPointerList(void){	SrcItem=NULL;	DstItem=NULL;	}
	LinkItemPointerList(AlgorithmItemRoot *s ,AlgorithmItemRoot*d){	SrcItem=s;	DstItem=d;	}
};

extern	void	MakeLinkItemByOverlap(const AlgorithmItemPointerListContainer &Src ,const AlgorithmItemPointerListContainer &Dst
									, NPListPack<LinkItemPointerList> &RetLink);

extern	void	MakeLinkItemClosed(const AlgorithmItemPointerListContainer &Src ,const AlgorithmItemPointerListContainer &Dst
									, NPListPack<LinkItemPointerList> &RetLink);
//==========================================================================

class	AlgorithmInLayerRoot:public LearningValueByEach 
							,public AlgorithmParentFromItem 
							,public HistgramInBinder
							,public PipeClass
							,public IdentifiedClass
{
	friend	class	AlgorithmItemRoot;

	XDateTime		CreatedTime;
	int				Layer;
	EntryPointBase	*PInspectionData;
protected:
	int64			StartItemID;		//If item is removed, StartItemID is not calculated again
	bool			Changed;
	bool			CalcDone;

public:
	AlgorithmInLayerRoot(void);
	virtual	~AlgorithmInLayerRoot(void);

	virtual	void	SizeChanged(void){}

	virtual	LayersBase			*GetLayersBase(void)	const	override;
	virtual	DataInPage			*GetDataInPage(void)	const;
	virtual	DataInLayer			*GetDataInLayer(void)	const;
	virtual	AlgorithmLibraryContainer	*GetLibraryContainer(void)	override;
	virtual	ResultInLayerRoot	*GetResultPointer(ResultInspection *Res)	=0;

	virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f);
	virtual	bool    LoadAppend(QIODevice *f){	return AlgorithmInLayerRoot::Load(f);	}
	virtual	bool    LoadByTransform(QIODevice *f ,TransformBase &Param)	=0;
	virtual	bool	SaveUnique(QIODevice *f){	return true;	}
	virtual	bool	LoadUnique(QIODevice *f){	return true;	}
	virtual	bool	SaveHistgram(QIODevice *f)		=0;
	virtual	bool	LoadHistgram(QIODevice *f)		=0;
	virtual	void	ClearHistgram(void)				=0;
	virtual	bool	SaveOnlyThreshold(QIODevice *f)	=0;
	virtual	bool	LoadOnlyThreshold(QIODevice *f)	=0;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	DeliverTransmitDirectly(GUIDirectMessage *packet)	=0;

	virtual	void	Initial(void);
	virtual	void	InitializeToStart(void)			=0;
	virtual	void	InitialAfterParamLoaded(void)	=0;
	virtual	void	Release(void){}
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	=0;
	virtual	bool	ReallocateMasterCount(int CountMaster)=0;
	virtual	bool	CopyShadowAlgorithmLayer(ShadowTree *Child ,const AlgorithmInLayerRoot &SrcParent)	=0;

	virtual	XYData	*GetOutlineOffset(void)			const	override;

	int64			GetIncStartItemID(void);
	void			ClearStartItemID(void)			{	StartItemID=0;		}
	void			SetChanged(bool changed=true)	{	Changed=changed;	}
	bool			IsChanged(void)					{	return Changed;		}
	void			SetEntryPoint(EntryPointBase *pInspectionData){		PInspectionData=pInspectionData;	}
	EntryPointBase	*GetEntryPoint(void)			{	return PInspectionData;	}
	int				GetLoadedVersion(void);
	virtual	AlgorithmItemRoot	*GetItemRoot(int n)=0;
	virtual	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const=0;

	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const=0;
	virtual	AlgorithmInPageRoot			*GetParentInPage(void)	const		=0;

	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	=0;
	virtual	void	CopyItemsFormDispatcherForParts(void)		=0;
	virtual	void	RemoveItemFormDispatcher(void)				=0;

	ParamGlobal		*GetParamGlobal(void)		{	return GetLayersBase()->GetParamGlobal();				}
	ParamComm		*GetParamComm(void)			{	return GetLayersBase()->GetParamComm();					}
	int		GetCountAllMasterBuff(void)		const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
	int		GetCountOnlyMasterBuff(void)	const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
	int		GetCountDispatchMasterBuff(void)const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}	
	int		GetLayerNumb(void);
	int		GetPageNumb(void)			{	return GetLayersBase()->GetParamGlobal()->PageNumb;		}
	int		GetPhaseNumb(void)			{	return GetLayersBase()->GetParamGlobal()->PhaseNumb;	}
	int		GetDotPerLine(void)			{	return (GetDataInPage()==0)?GetParamGlobal()->DotPerLine:GetDataInPage()->GetDotPerLine();	}
	int		GetMaxLines(void)			{	return (GetDataInPage()==0)?GetParamGlobal()->MaxLines	:GetDataInPage()->GetMaxLines();	}
	int		GetLayer(void)			const	{	return Layer;	}
	void	SetLayer(int layer)				{	Layer=layer;	}
	int		GetPage(void)			const;
	int		GetPhaseCode(void)		const;

	virtual	AlgorithmInLayerRoot	*GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName){	return NULL;	}
	virtual	void	SwitchThresholdLevel(int OldLevel ,int NewLevel)			=0;
	virtual	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)	=0;
	virtual	void	ClearResult(void)	=0;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)			=0;
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	=0;
	virtual	bool	DrawResult	  (ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	=0;
	virtual	bool	DrawResultItem(ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	=0;
	virtual	void	DrawMonoBitmap(BYTE **BmpPoint)=0;
	virtual	void	DrawItems(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)=0;
	virtual	void	DrawResultItem(ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)=0;

	virtual	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return _ER_true;	}
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteCaptured				(int ExeID ,ResultInLayerRoot *Res,ListPhasePageLayerPack &CapturedList)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreAlignment			(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteAlignment			(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePreProcessing		(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessing			(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostProcessing		(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePreScanning			(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteScanning				(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostScanning			(int ExeID ,ResultInLayerRoot *Res){	return _ER_true;	}
	virtual	bool		ExecuteManageResult			(int ExeID ,ResultInspection *Res) {	return true;		}

	virtual	void	MoveForAlignment(void)	=0;

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)	=0;

	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen)									=0;
	virtual	void	MakeIndependentItems(bool SubResultMoving, ResultInLayerRoot *RLayer ,int localX ,int localY,AlgorithmItemIndependentPack &Data)				=0;
	virtual	void	MakeIndependentItems(IntList &Items,AlgorithmItemIndependentPack &Data)	=0;
	virtual	void	SetIndependentItemData(int32 Command
											,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData)	=0;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)					=0;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)					=0;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)			=0;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)			=0;
	virtual	bool	GeneralDataReply(int32 Command,void *data)						=0;

	void			GetAlignmentForProcessing(AlignmentPacketBase &Packet);

	virtual	int		GetSelectedItemCount(void)										=0;
	virtual	int		GetItemCount(void)												=0;
	virtual	void	ReleaseAllSelectedItem(void)									=0;
	virtual	void	SelectAll(void)													=0;
	virtual	void	SelectLocked(void)												=0;
	virtual	void	SelectLibs(AlgorithmLibraryListContainer &SelectedList)			=0;
	virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect)				=0;
	virtual	void	SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode)=0;
	virtual	void	SelectPoint(int localX, int localY)								=0;
	virtual	void	CutArea(FlexArea &localArea,bool MultiSelect,const QByteArray &Something=QByteArray())	=0;
	virtual	void	SeparateItems(FlexArea &localArea)								=0;
	virtual	void	RegistArea(FlexArea &localArea)									=0;
	virtual	void	DeleteSelectedItems(void)										=0;
	virtual	void	UndoDeleteSelectedItems(QIODevice *f)							=0;
	virtual	void	LockSelectedItems(void)											=0;
	virtual	void	UndoLockSelectedItems(QIODevice *f)								=0;
	virtual	void	UnlockAll(void)													=0;
	virtual	void	UndoUnlockAll(QIODevice *f)										=0;
	virtual	void	BindSelectedItems(void)											=0;
	virtual	void	UndoBindSelectedItems(QIODevice *f)								=0;
	virtual	void	Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)	=0;
	virtual	void	Activate(int ItemID)											=0;
	virtual	void	AddActivate(int ItemID)											=0;
	virtual	void	Inactivate(void)												=0;

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack)							=0;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)		=0;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,IntList &Items ,bool AllItems=false)		=0;
	virtual	void	UndoExecuteMove(QIODevice *f)									=0;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	=0;
	virtual	bool	ExecutePasteFromSelected(int Dx,int Dy)							=0;
	virtual	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)				=0;

	virtual	void	CopyFrom(AlgorithmInPageRoot *DestParent
							,AlgorithmInLayerRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)								=0;
	virtual	void	TransformCopyFrom(TransformBase &Param,const AlgorithmInLayerRoot &src){}
	virtual	void	InitializeFromParts(void)										=0;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)					=0;
	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)	=0;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase)		=0;
	virtual	void	VisibleAll(void)			=0;
	virtual	void	InvisibleAll(void)			=0;
	virtual	void	InvisibleSelected(void)		=0;
	virtual	void	SelectManualCreature(void)	=0;
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)			=0;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)				=0;
	virtual	void	EnumLibID(IntList &LibIDList)						=0;
	virtual	bool	GetSelectedCenter(int &Cx ,int &Cy)					=0;
	virtual	bool	GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	=0;
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	=0;
	virtual	bool	GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	=0;
	virtual	void	GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)		=0;
	virtual	void	EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	=0;
	virtual	void	EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)		=0;
	virtual	void	GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)	=0;
	virtual	void	EnumSelectedItems(ListPageLayerIDPack &Items)						=0;
	virtual	void	EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)			=0;
	virtual	bool	ShrinkItems(int ExpandPixels,bool MaskForSameLib)	=0;

	virtual	bool	IsEdited(void)				=0;
	virtual	bool	IsCalcDone(void)			=0;
	virtual	void	SetEdited(bool edited)		=0;
	virtual	void	SetCalcDone(bool calcdone)	=0;

	virtual	void	ResetProcessDone(void)		=0;
	virtual	bool	IsProcessDone(void)			=0;
	virtual	void	SetProcessDone(bool b=true)	=0;

	virtual	void	ClearTemporaryItems(void)	=0;
	virtual	void	SetTemporaryItems(ItemPointerListInLayer *Pg)	=0;
	virtual	void	AddItemsForMove(ItemPointerListInLayer *Pg)		=0;
	virtual	void	UndoAddItemsForMove(QIODevice *f)				=0;	
	virtual	void	SelectedItemListsForPaste(ExpandedSelectedItemListContainer &Lists)=0;
	virtual	void	DrawItemListsForPaste(int dx, int dy 
									,QImage &Pnt,int ItemID,double ZoomRate ,int movx ,int movy,int turn)=0;

	virtual	void	ExecuteTransformSelectedItems(TransformBase &M)	=0;
	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	=0;
	virtual	bool	SaveItemsForLearning(ItemDataListWithIDContainer &Buff
											,FlexArea &LocalArea
											,AlgorithmLibraryListContainer &LibList
											,int AddedX,int AddedY ,bool OkMode)	=0;
	virtual	bool	LoadItemsForLearning(ItemDataListWithIDContainer &Buff,int AddedX ,int AddedY)	=0;
	virtual	HistgramByParamBase	*GetHistgramBase(int ItemID,int HistID)=0;
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)=0;
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected)	=0;

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)	{	return NULL;	}
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,void *Anything=NULL)								{	return NULL;	}
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MapVector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	{	return false;	}
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &MapVector ,void *Anything=NULL)							{	return false;	}
	virtual	bool	IncludeLibInReflectionForGenerator(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)		{	return false;	}
	virtual	bool	GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret)				{	return false;	}	

	virtual	bool	GetReflectionMap	(ReflectionMode Mode ,ConstMapBuffer &Map ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	virtual	bool	GetReflectionMap	(ReflectionMode Mode ,ConstMapBuffer &Map ,void *Anything=NULL);		
	virtual	bool	GetReflectionVector	(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	virtual	bool	GetReflectionVector	(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL);		
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL);
	virtual	bool	GetUsageLibInReflection(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret);	

	virtual	void	EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)	=0;
	virtual	void	EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)	=0;
	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData)	=0;
	virtual void	MakeBindedThreshold(BindedThresholdContainer &Container)=0;
	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes){}

	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList){	return true;	}
	virtual	void	MasterImageHasChanged(void)	=0;

	ImageBuffer &GetMasterBuff(void);
	ImageBuffer &GetMasterBuff(int n);
	ImageBuffer &GetBackGroundBuff(void);
	ImageBuffer &GetTargetBuff(void);
	ImageBuffer &GetTargetTRBuff(void);
	ImageBuffer &GetRawTargetBuff(void);
	ImageBuffer &GetDelayedViewBuff(void);
	ImageBuffer &GetCamTargetBuff(void);
	ImageBuffer &GetBitBuff(void);
	ImageBuffer &GetTrialTargetBuff(void);

	ImageBuffer	*GetMasterBuffPointer(void);
	ImageBuffer	*GetMasterBuffPointer(int n);
	ImageBuffer	*GetBackGroundBuffPointer(void);
	ImageBuffer	*GetTargetBuffPointer(void);
	ImageBuffer	*GetTargetTRBuffPointer(void);
	ImageBuffer	*GetRawTargetBuffPointer(void);
	ImageBuffer	*GetDelayedViewBuffPointer(void);
	ImageBuffer	*GetCamTargetBuffPointer(void);
	ImageBuffer	*GetBitBuffPointer(void);
	ImageBuffer	*GetTrialTargetBuffPointer(void);

	//----------- Unit-------------
	bool	IsUnitMode(void);
	double	TransformPixelToUnit(double pixel);
	double	TransformUnitToPixel(double unit);
	QString	TransformPixelToUnitStr(double pixel);
	QString	GetUnitStr(double unit);
	double	TransformPixelToUnitSquare(double pixel);
	double	TransformUnitToPixelSquare(double unit);
	QString	TransformPixelToUnitSquareStr(double pixel);
	QString	GetUnitSquareStr(double unit);
};

inline	int64	AlgorithmInLayerRoot::GetIncStartItemID(void)
{
	const int64	c=StartItemID;
	StartItemID++;
	return c;
}

class	ExecuteTimeClass
{
	friend	class	AlgorithmInPageRoot;

	DWORD	MilisecExecuteInitialAfterEditPrev;
	DWORD	MilisecExecuteInitialAfterEdit;
	DWORD	MilisecExecuteInitialAfterEditPost;
	DWORD	MilisecExecuteStartByInspection;
	DWORD	MilisecExecuteCaptured;
	DWORD	MilisecExecutePreAlignment;
	DWORD	MilisecExecuteAlignment;
	DWORD	MilisecExecutePreProcessing;
	DWORD	MilisecExecuteProcessing;
	DWORD	MilisecExecuteProcessingRevived;
	DWORD	MilisecExecutePostProcessing;
	DWORD	MilisecExecutePreScanning;
	DWORD	MilisecExecuteScanning;
	DWORD	MilisecExecutePostScanning;
public:
	ExecuteTimeClass(void);

	void	ClearExecuteTime(void);

	DWORD	GetMilisecExecuteInitialAfterEditPrev(void)	const;
	DWORD	GetMilisecExecuteInitialAfterEdit(void)		const;
	DWORD	GetMilisecExecuteInitialAfterEditPost(void)	const;
	DWORD	GetMilisecExecuteStartByInspection(void)	const;
	DWORD	GetMilisecExecuteCaptured(void)				const;
	DWORD	GetMilisecExecutePreAlignment(void)			const;
	DWORD	GetMilisecExecuteAlignment(void)			const;
	DWORD	GetMilisecExecutePreProcessing(void)		const;
	DWORD	GetMilisecExecuteProcessing(void)			const;
	DWORD	GetMilisecExecuteProcessingRevived(void)	const;
	DWORD	GetMilisecExecutePostProcessing(void)		const;
	DWORD	GetMilisecExecutePreScanning(void)			const;
	DWORD	GetMilisecExecuteScanning(void)				const;
	DWORD	GetMilisecExecutePostScanning(void)			const;

	virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f);
	ExecuteTimeClass	&operator=(const ExecuteTimeClass &src);
};

class	AlgorithmInPageRoot:public LearningValueByEach
							,public AlgorithmParentFromItem
							,public HistgramInBinder
							,public PipeClass
							,public IdentifiedClass
{
	friend	class	AlgorithmInLayerRoot;
	friend	class	AlgorithmBase;
	friend	class	ExecuteTimeClass;

	XDateTime		CreatedTime;
	int		Page;
protected:
	DataInPage					*PDataInPage;
	EntryPointBase				*PInspectionData;
	AlgorithmInPageInOnePhase	*ParentPhase;
	
	QTime	StartTimeExecuteInitialAfterEditPrev;
	QTime	StartTimeExecuteInitialAfterEdit;
	QTime	StartTimeExecuteInitialAfterEditPost;
	QTime	StartTimeExecuteStartByInspection;
	QTime	StartTimeExecuteCaptured;
	QTime	StartTimeExecutePreAlignment;
	QTime	StartTimeExecuteAlignment;
	QTime	StartTimeExecutePreProcessing;
	QTime	StartTimeExecuteProcessing;
	QTime	StartTimeExecuteProcessingRevived;
	QTime	StartTimeExecutePostProcessing;
	QTime	StartTimeExecutePreScanning;
	QTime	StartTimeExecuteScanning;
	QTime	StartTimeExecutePostScanning;

	ExecuteTimeClass	ExecuteTimeData;
	DWORD	StartTimeMilisec;

protected:
	int64			StartItemID;		//If item is removed, StartItemID is not calculated again
	bool			Changed;
	bool			CalcDone;

public:
	AlgorithmInPageRoot(void);
	virtual	~AlgorithmInPageRoot(void);

	virtual	ModelType	GetModel(void)	=0;
	void	Set(AlgorithmInPageInOnePhase *parent){		ParentPhase=parent;	}
	virtual	bool	Reallocate(int newLayerNumb)	=0;
	virtual	bool	ReallocateMasterCount(int CountMaster)=0;

	virtual	bool    Save(QIODevice *f);
    virtual	bool    Load(QIODevice *f);
	virtual	bool    LoadByTransform(QIODevice *f ,TransformBase &Param)	=0;
	virtual	bool    LoadAppend(QIODevice *f){	return AlgorithmInPageRoot::Load(f);	}
	virtual	bool	SaveUnique(QIODevice *f){	return true;	}
	virtual	bool	LoadUnique(QIODevice *f){	return true;	}
	virtual	void	SizeChanged(LayersBase *Base){}
	virtual	bool	SaveHistgram(QIODevice *f)	=0;
	virtual	bool	LoadHistgram(QIODevice *f)	=0;
	virtual	void	ClearHistgram(void)			=0;
	virtual	bool	SaveOnlyThreshold(QIODevice *f)	=0;
	virtual	bool	LoadOnlyThreshold(QIODevice *f)	=0;

	void	SetPDataInPage(DataInPage *p)			{	PDataInPage=p;		}
	void	SetPInspectionData(EntryPointBase *p)	{	PInspectionData=p;	}

	int				GetPage(void)		const	{	return Page;	}
	int				GetGlobalPage(void);
	void			SetPage(int page)			{	Page=page;		}
	int				GetPhaseCode(void)	const;
	EntryPointBase	*GetEntryPoint(void)		{	return PInspectionData;	}
	void			SetEntryPoint(EntryPointBase *pInspectionData){		PInspectionData=pInspectionData;	}
	XYData			*GetGlobalOutlineOffset(void);
	virtual			XYData	*GetOutlineOffset(void)			const	override;

	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)=0;
	virtual	AlgorithmInLayerRoot	*GetLayerData(int layer)	const	{	return NULL;	}
	virtual	AlgorithmItemRoot	*GetItemData(int layer ,int itemID)		const	=0;
	virtual	AlgorithmItemRoot	*FindFastItemData(int layer ,int itemID)const	=0;
	virtual	AlgorithmItemRoot	*GetItemRoot(int n)						const	=0;
	virtual	LayersBase			*GetLayersBase(void)		const	override;
	AlgorithmInPageInOnePhase	*GetParentPhase(void)		const	{	return ParentPhase;	}
	virtual	DataInPage			*GetDataInPage(void)		const	{	return PDataInPage;	}
	virtual	DataInLayer			*GetDataInLayer(int layer)	const	{	return (PDataInPage!=NULL)?PDataInPage->GetLayerData(layer):NULL;	}
	virtual	AlgorithmLibraryContainer	*GetLibraryContainer(void)	override;
	ResultInPageRoot	*GetResultPointer(ResultInspection *Res)	const;
	virtual	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const=0;

	void			SetChanged(bool changed=true)	{	Changed=changed;	}
	bool			IsChanged(void)					{	return Changed;		}

	int64			GetIncStartItemID(void);
	void			ClearStartItemID(void)			{	StartItemID=0;		}
	int				GetLoadedVersion(void);

	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	=0;
	virtual	void	CopyItemsFormDispatcherForParts(void)		=0;
	virtual	void	RemoveItemFormDispatcher(void)				=0;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	DeliverTransmitDirectly(GUIDirectMessage *packet)	=0;

	virtual	void	Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base);
	virtual	void	InitializeToStart(void)		=0;
	virtual	void	InitialAfterParamLoaded(void)=0;
	virtual	void	Release(void){}
	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	=0;
	virtual	bool	CopyShadowAlgorithmPage(ShadowTree *Child ,const AlgorithmInPageRoot &SrcParent)	=0;

	bool	IsInclude(int localX ,int localY)	const;
	virtual	AlgorithmInPageRoot	*GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	const
									{	return NULL;	}
	virtual	void	ClearResult(void)	=0;

	ParamGlobal	*GetParamGlobal(void)	const	{	return(GetLayersBase()->GetParamGlobal());		}
	ParamComm	*GetParamComm(void)		const	{	return(GetLayersBase()->GetParamComm());		}
	int		GetCountAllMasterBuff(void)		const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
	int		GetCountOnlyMasterBuff(void)	const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
	int		GetCountDispatchMasterBuff(void)const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}
	int		GetLayerNumb(void)		const;
	int		GetPageNumb(void)		const	{	return(GetLayersBase()->GetParamGlobal()->PageNumb);		}
	int		GetPhaseNumb(void)		const	{	return(GetLayersBase()->GetParamGlobal()->PhaseNumb);		}
	int		GetDotPerLine(void)		const	{	return (GetDataInPage()==NULL)?GetParamGlobal()->DotPerLine	:GetDataInPage()->GetDotPerLine();	}
	int		GetMaxLines(void)		const	{	return (GetDataInPage()==NULL)?GetParamGlobal()->MaxLines	:GetDataInPage()->GetMaxLines();	}
	
	virtual	void	MakeIndependentItems(bool SubResultMoving, ResultInPageRoot *RPage,int localX ,int localY,AlgorithmItemIndependentPack &Data)	=0;
	virtual	void	MakeIndependentItems(int Layer ,IntList	&Items,AlgorithmItemIndependentPack &Data)	=0;
	virtual	void	SetIndependentItemData(int32 Command
											,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData)=0;
	virtual	bool	GeneralDataRelease(int32 Command,void *data)			=0;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			=0;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	=0;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	=0;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				=0;

	virtual	void	SelectItems(FlexArea &area ,const IntList &LayerList,bool MultiSelect)	=0;
	virtual	void	SelectAll(const IntList &LayerList)					=0;
	virtual	void	SelectLocked(const IntList &LayerList)				=0;
	virtual	void	SelectLibs(SelectLibListContainer &SelectedList)	=0;
	virtual	void	SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode	,const IntList &LayerList)	=0;
	virtual	void	CutArea(FlexArea &area ,const IntList &LayerList ,bool MultiSelect,const QByteArray &Something=QByteArray())	=0;
	virtual	void	SeparateItems(FlexArea &area ,const IntList &LayerList)	=0;
	virtual	void	RegistArea(FlexArea &area ,const IntList &LayerList)=0;
	virtual	void	DeleteSelectedItems(const IntList &LayerList)		=0;
	virtual	void	UndoDeleteSelectedItems(QIODevice *f)				=0;
	virtual	void	LockSelectedItems(const IntList &LayerList)			=0;
	virtual	void	UndoLockSelectedItems(QIODevice *f)					=0;
	virtual	void	UnlockAll(const IntList &LayerList)					=0;
	virtual	void	UndoUnlockAll(QIODevice *f)							=0;
	virtual	void	BindSelectedItems(const IntList &LayerList)			=0;
	virtual	void	UndoBindSelectedItems(QIODevice *f)					=0;
	virtual	void	Activate(int PosX,int PosY ,IntList &LayerList ,ListLayerAndIDPack &RetItem)	=0;
	virtual	void	Activate(int Layer ,int ItemID)						=0;
	virtual	void	AddActivate(int Layer ,int ItemID)					=0;
	virtual	void	Inactivate(void)									=0;
	virtual	void	GetLayerAndItemID(int LocalX ,int LocalY ,ListLayerIDLibNamePack &ItemList ,const IntList &LayerList)	=0;
	virtual	void	GetLayerAndItemID(FlexArea &CoveredArea  ,ListLayerAndIDPack &ItemList ,const IntList &LayerList)		=0;
	virtual	void	GetItems(ListLayerAndIDPack &ItemList ,AlgorithmItemPointerListContainer &Items)				=0;
	virtual	void	EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)	=0;
	virtual	void	EnumOriginTypeItems(int layer ,OriginType b ,AlgorithmItemPointerListContainer &Items)	=0;
	virtual	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	EnumItems(int layer ,void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	ScanItems(int layer ,void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))	=0;
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)	=0;
	virtual	void	EnumItems(int layer,ListPhasePageLayerLibIDPack &ItemIDList)	=0;

	virtual	void	SelectItemByID(ListLayerAndIDPack &SelectedItem)	=0;
	virtual	void	VisibleAll(const IntList &LayerList)				=0;
	virtual	void	InvisibleAll(const IntList &LayerList)				=0;
	virtual	void	InvisibleSelected(const IntList &LayerList)			=0;
	virtual	void	SelectManualCreature(const IntList &LayerList)		=0;
	virtual	bool	GetSelectedCenter(DotListContainer &CenterByLayer)	=0;
	virtual	bool	GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	=0;
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)			=0;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	=0;
	virtual	void	EnumLibID(IntList &LibIDList)						=0;
	virtual	void	MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)	=0;
	virtual	bool	GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	=0;
	virtual	bool	ShrinkItems(const IntList &LayerList,int ExpandPixels,bool MaskForSameLib)	=0;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)		=0;
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)					=0;
	virtual	bool	DrawResult	  (ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	=0;
	virtual	bool	DrawResultItem(ResultInPageRoot *Res,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)=0;
	virtual	void	DrawMonoBitmap(BYTE **BmpPoint)=0;
	virtual	void	DrawItems(QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)=0;
	virtual	void	DrawResultItem(ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)=0;

	virtual	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo){	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo){	return _ER_true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo){	return _ER_true;	}
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteCaptured				(int ExeID ,ResultInPageRoot *Res,ListPhasePageLayerPack &CapturedList)	{	return _ER_true;	}
	virtual	ExeResult	ExecutePreAlignment			(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteAlignment			(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePreProcessing		(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessing			(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostProcessing		(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePreScanning			(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecuteScanning				(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	ExeResult	ExecutePostScanning			(int ExeID ,ResultInPageRoot *Res){	return _ER_true;	}
	virtual	bool		ExecuteManageResult			(int ExeID ,ResultInspection *Res){	return true;		}

	virtual	void	MoveForAlignment(void)	=0;

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)	=0;
	virtual	void	RefreshByMap(int layer,ReflectionMode Mode,ConstMapBufferListContainer &Map)	=0;

	void	IncrementNGCounterWithMutex(int result);
	virtual	int		GetNGCounter(void);
	virtual	void	AddNGCounter(int NGCount);

	void			GetAlignmentForProcessing(AlignmentPacketBase &Packet);

	virtual	int		GetSelectedItemCount(void)			=0;
	virtual	int		GetItemCount(void)					=0;
	virtual	void	ReleaseAllSelectedItem(void)		=0;
	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)	=0;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)		=0;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems=false)	=0;
	virtual	void	UndoExecuteMove(QIODevice *f)								=0;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)	=0;
	virtual	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
						,FlexArea &area,AlgorithmBase *OriginBase ,int ItemClass)=0;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area ,bool SelectModeAfterPaste=false)=0;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,VectorLineBase *Vector,bool SelectModeAfterPaste=false)=0;
	virtual	bool	ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)	=0;
	virtual	void	SelectedItemListsForPaste(IntList &LayerList ,ExpandedSelectedItemListContainer &Lists)=0;
	virtual	void	DrawItemListsForPaste(int dx, int dy 
										,QImage &Pnt,int Layer,int ItemID ,double ZoomRate ,int movx ,int movy,int turn)	=0;
	virtual	void	GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)		=0;
	virtual	void	EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	=0;
	virtual	void	EnumItemsByLib(int layer ,IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	=0;
	virtual	void	EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)		=0;
	virtual	void	EnumAllItems(int layer,AlgorithmItemPointerListContainer &ItemPointers)		=0;
	virtual	void	GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)	=0;
	virtual	void	MirrorItems(AlgorithmItemRoot::_MirrorMode MirrorMode,int PageNumb,QByteArray BuffData[]);
	virtual	void	UndoMirrorItems(QIODevice *f);
	virtual	void	EnumSelectedItems(ListPageLayerIDPack &Items)	=0;

	virtual	void	ExecuteTransformSelectedItems(TransformBase &M)	=0;
	virtual	void	GetAffinParam(double SrcX1,double SrcY1
								, double SrcX2,double SrcY2
								, double SrcX3,double SrcY3
								, double TargetX1,double TargetY1
								, double TargetX2,double TargetY2
								, double TargetX3,double TargetY3
								, double Dest[6]);

	virtual	void	GenerateAlgorithmItemCount(AlgorithmItemCountInPage &Ret)=0;
	virtual	void	CopyFrom(AlgorithmBase *DestParent
							,AlgorithmInPageRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)												=0;
	virtual	void	TransformCopyFrom(TransformBase &Param,const AlgorithmInPageRoot &ParentAPage){}
	virtual	void	InitializeFromParts(void)														=0;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)=0;

	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList ,const IntList &LayerList)	=0;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase ,const IntList &LayerList)		=0;
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	=0;

	int		GetMasterBuffList		(ImageBuffer *ImageList[])		const;
	int		GetMasterBuffList		(int n,ImageBuffer *ImageList[])const;
	int		GetTargetBuffList		(ImageBuffer *ImageList[])		const;
	int		GetTargetTRBuffList		(ImageBuffer *ImageList[])		const;
	int		GetDelayedViewBuffList	(ImageBuffer *ImageList[])		const;
	int		GetBitBuffList			(ImageBuffer *ImageList[])		const;
	int		GetTrialTargetBuffList	(ImageBuffer *ImageList[])		const;

	void	GetMasterImages			(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetMasterImages(Images);		}
	void	GetMasterImages			(int n,ImagePointerContainer &Images)	const	{	GetDataInPage()->GetMasterImages(n,Images);		}
	void	GetTargetImages			(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetTargetImages(Images);		}
	void	GetTargetTRImages		(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetTargetTRImages(Images);		}
	void	GetDelayedViewImages	(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetDelayedViewImages(Images);	}
	void	GetBitImages			(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetBitImages(Images);			}
	void	GetTrialTargetImages	(ImagePointerContainer &Images)			const	{	GetDataInPage()->GetTrialTargetImages(Images);	}

	virtual	bool	ConvertImage(ImagePointerContainer &SrcImages ,ImagePointerContainer &DstImages){	return true;	}

	virtual	bool	IsEdited(void)				=0;
	virtual	bool	IsCalcDone(void)			=0;
	virtual	void	SetEdited(bool edited)		=0;
	virtual	void	SetCalcDone(bool calcdone)	=0;

	virtual	void	ResetProcessDone(void)		=0;
	virtual	bool	IsProcessDone(void)			=0;
	virtual	void	SetProcessDone(bool b=true)	=0;

	virtual	void	ClearTemporaryItems(void)	=0;
	virtual	void	SetTemporaryItems(ItemPointerListInPage *Pg)	=0;
	virtual	void	AddItemsForMove(ItemPointerListInPage *Pg)		=0;
	virtual	void	UndoAddItemsForMove(QIODevice *f)				{}	
	virtual	void	AppendItemsInPage(int Layer,AlgorithmItemPointerListContainer &SrcPointers)	=0;
	virtual	void	RemoveItemsInPage(int Layer,IntList &IDList)	=0;
	virtual	void	SwitchThresholdLevel(int OldLevel ,int NewLevel)			=0;
	virtual	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)	=0;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	=0;

	virtual	bool	SaveItemsForLearning(ItemDataListWithIDContainer &Buff
											,FlexArea &LocalArea
											,AlgorithmLibraryListContainer &LibList
											,int AddedX,int AddedY,bool OkMode)=0;
	virtual	bool	LoadItemsForLearning(ItemDataListWithIDContainer &Buff,int AddedX ,int AddedY)	=0;
	virtual	bool	GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)		=0;
	virtual	HistgramByParamBase	*GetHistgramBase(int Layer,int ItemID,int HistID)=0;
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)	=0;
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected)	=0;

	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL){	return NULL;	}	
	virtual	ConstMapBuffer	*CreateReflectionMapForGenerator(ReflectionMode Mode ,int layer ,void *Anything=NULL)							{	return NULL;	}
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &Vector ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	{	return false;	}
	virtual	bool	CreateReflectionVectorForGenerator(ReflectionMode Mode ,VectorLineBase &Vector ,int layer ,void *Anything=NULL)								{	return false;	}
	virtual	bool	IncludeLibInReflectionForGenerator(ReflectionMode Mode ,int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL)	{	return false;	}
	virtual	bool	GetUsageLibInReflectionForGenerator(ReflectionMode Mode ,int layer,AlgorithmLibraryListContainer &Ret)				{	return false;	}

	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,void *Anything=NULL);		
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL);		
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	virtual	bool	GetUsageLibInReflection(ReflectionMode Mode ,AlgorithmLibraryListContainer &Ret);	

	void	ClearExecuteTime(void);
	ExecuteTimeClass	&GetExecuteTime(void)	{	return ExecuteTimeData;		}
	virtual	void	EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)	=0;
	virtual	void	EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)	=0;

	virtual	ResultInItemRoot	*CreateResult(void)	=0;
	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData)	=0;
	virtual void	MakeBindedThreshold(BindedThresholdContainer &Container)=0;
	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes){}
	
	virtual	bool	SaveMasterData(void);
	virtual	bool	LoadMasterData(void);

	virtual	void	MasterImageHasChanged(void)	=0;
	void	SetStartTimeMilisec(void);
	DWORD	GetStartTimeMilisec(void)	const	{	return StartTimeMilisec;	}


	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList)	{	return true;	}
	virtual	void	MakeOutlineItemsInSelectedItems(int OutlineWidth)	{}

	void	StartMilisecExecuteInitialAfterEditPrev(void)	;
	void	StartMilisecExecuteInitialAfterEdit(void)		;
	void	StartMilisecExecuteInitialAfterEditPost(void)	;
	void	StartMilisecExecuteStartByInspection(void)		;
	void	StartMilisecExecuteCaptured(void)				;
	void	StartMilisecExecutePreAlignment(void)			;
	void	StartMilisecExecuteAlignment(void)				;
	void	StartMilisecExecutePreProcessing(void)			;
	void	StartMilisecExecuteProcessing(void)				;
	void	StartMilisecExecuteProcessingRevived(void)		;
	void	StartMilisecExecutePostProcessing(void)			;
	void	StartMilisecExecutePreScanning(void)			;
	void	StartMilisecExecuteScanning(void)				;
	void	StartMilisecExecutePostScanning(void)			;

	void	EndMilisecExecuteInitialAfterEditPrev(void)	;
	void	EndMilisecExecuteInitialAfterEdit(void)		;
	void	EndMilisecExecuteInitialAfterEditPost(void)	;
	void	EndMilisecExecuteStartByInspection(void)	;
	void	EndMilisecExecuteCaptured(void)				;
	void	EndMilisecExecutePreAlignment(void)			;
	void	EndMilisecExecuteAlignment(void)			;
	void	EndMilisecExecutePreProcessing(void)		;
	void	EndMilisecExecuteProcessing(void)			;
	void	EndMilisecExecuteProcessingRevived(void)	;
	void	EndMilisecExecutePostProcessing(void)		;
	void	EndMilisecExecutePreScanning(void)			;
	void	EndMilisecExecuteScanning(void)				;
	void	EndMilisecExecutePostScanning(void)			;

	DWORD	GetMilisecExecuteInitialAfterEditPrev(void)		const;
	DWORD	GetMilisecExecuteInitialAfterEdit(void)			const;
	DWORD	GetMilisecExecuteInitialAfterEditPost(void)		const;
	DWORD	GetMilisecExecuteStartByInspection(void)		const;
	DWORD	GetMilisecExecuteCaptured(void)					const;
	DWORD	GetMilisecExecutePreAlignment(void)				const;
	DWORD	GetMilisecExecuteAlignment(void)				const;
	DWORD	GetMilisecExecutePreProcessing(void)			const;
	DWORD	GetMilisecExecuteProcessing(void)				const;
	DWORD	GetMilisecExecuteProcessingRevived(void)		const;
	DWORD	GetMilisecExecutePostProcessing(void)			const;
	DWORD	GetMilisecExecutePreScanning(void)				const;
	DWORD	GetMilisecExecuteScanning(void)					const;
	DWORD	GetMilisecExecutePostScanning(void)				const;

	//----------- Unit-------------
	bool	IsUnitMode(void)							const;
	double	TransformPixelToUnit(double pixel)			const;
	double	TransformUnitToPixel(double unit)			const;
	QString	TransformPixelToUnitStr(double pixel)		const;
	QString	GetUnitStr(double unit)						const;
	double	TransformPixelToUnitSquare(double pixel)	const;
	double	TransformUnitToPixelSquare(double unit)		const;
	QString	TransformPixelToUnitSquareStr(double pixel)	const;
	QString	GetUnitSquareStr(double unit)				const;
};

inline	int64	AlgorithmInPageRoot::GetIncStartItemID(void)
{
	int64	c=StartItemID;
	StartItemID++;
	return c;
}

inline	void	AlgorithmInPageRoot::IncrementNGCounterWithMutex(int result)
{
	GetDataInPage()->IncrementNGCounterWithMutex(result);
}
inline	int		AlgorithmInPageRoot::GetNGCounter(void)
{
	return GetDataInPage()->GetNGCounter();
}
inline	void	AlgorithmInPageRoot::AddNGCounter(int NGCount)
{
	GetDataInPage()->AddNGCounter(NGCount);
}

class	AlgorithmInPageInOnePhase	final :public IdentifiedClass
{	
	AlgorithmInPageRoot	**PageData;
	int32				AllocatedPageNumb;
	int32				EffectivePageNumb;
	int32				PhaseCode;			//０から順番に付けられる
	AlgorithmBase		*ParentBase;
	LayersBase			*Parent;
	bool				EnableExecute;
public:

	AlgorithmInPageInOnePhase(int phaseCode,AlgorithmBase *Base);
	virtual	~AlgorithmInPageInOnePhase(void);

	void	InitialCreate(void);
	void	InitializeToStart(void);
	void	InitialAfterParamLoaded(void);
	void	Release(void);
	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	bool	Reallocate(int newPageNumb ,int newLayerNumb);
	bool	ReallocateMasterCount(int CountMaster);
	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	bool	RemovePage(int IndexPage);

	int		GetCountAllMasterBuff(void)		const	{	return GetLayersBase()->GetCountAllMasterBuff();		}
	int		GetCountOnlyMasterBuff(void)	const	{	return GetLayersBase()->GetCountOnlyMasterBuff();		}
	int		GetCountDispatchMasterBuff(void)const	{	return GetLayersBase()->GetCountDispatchMasterBuff();	}

	int		GetPhaseCode(void)	const	{	return PhaseCode;			}
	void	SetPhaseCode(int phase)		{	PhaseCode=phase;			}
	int32	GetEffectivePageNumb(void)	{	return EffectivePageNumb;	}

	AlgorithmInPageRoot		*GetPageData(int page)	const	{		return (page<EffectivePageNumb)?PageData[page]:NULL;	}
	void				SizeChanged(AlgorithmBase *Base);
	AlgorithmInPageRoot	*SetPageData(int page,AlgorithmInPageRoot *pData);
	bool				RemovePage(AlgorithmInPageRoot *pData);

	AlgorithmBase	*GetParentBase(void)	const	{	return ParentBase;		}
	LayersBase		*GetLayersBase(void)	const	{	return Parent;			}
	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const;
	int				GetLoadedVersion(void);
	void	InitializeFromParts(void);

	bool	Save(AlgorithmBase *Base,QIODevice *f);
	bool	Load(AlgorithmBase *Base,QIODevice *f);
	bool	SaveHistgram(AlgorithmBase *Base,QIODevice *f);
	bool	LoadHistgram(AlgorithmBase *Base,QIODevice *f);
	void	ClearHistgram(void);
	bool	SaveOnlyThreshold(QIODevice *f);
	bool	LoadOnlyThreshold(QIODevice *f);
	bool	SaveOnly(QIODevice *f);
	bool	LoadOnly(QIODevice *f);

	void	EnumLibID(IntList &LibIDList);
	void	DeliverTransmitDirectly(GUIDirectMessage *packet);
	
	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	void	DrawMove(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);
	bool	DrawResultBase(ResultBasePhase *Res					   ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,int localPage);
	bool	DrawResultItem(ResultBasePhase *Res,IntList &LayerList ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);

	bool	IsCalcDone(void);
	bool	IsEdited(void);
	void	SetEdited(bool edited);

	void	ResetProcessDone(void)		;
	bool	IsProcessDone(void)			;
	void	SetProcessDone(bool b=true)	;
	void	ClearResult(void);

	bool	GetEnableExecute(void)		{	return EnableExecute;	}
	void	SetEnableExecute(bool b)	{	EnableExecute=b;		}
	void	SwitchThresholdLevel(int OldLevel ,int NewLevel);
	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);

	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData);
	void	MoveForAlignment(void);
	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName ,int *Page=NULL ,int *Layer=NULL);

	void	MoveItemsToDispatcherForLoadingParts(void);
	void	CopyItemsFormDispatcherForParts(void);
	void	RemoveItemFormDispatcher(void);

	bool	GeneralDataRelease(int32 Command,void *data);
	void	*GeneralDataCreate(int32 Command,void *reqData);
	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data);
	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data);
	bool	GeneralDataReply(int32 Command,void *data);

	bool	SaveCSVMasterReport(QStringListListCSV &CSVData);
	
	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item));
	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item));
	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList);

	int		GetSelectedItemCount(void);
	void	ReleaseAllSelectedItem(void);
};

class	AlgorithmBase :  public ParamBaseForAlgorithm 
						,public LearningValueByEach
						,public NPList<AlgorithmBase>
						,public ServiceForLayers
						,public PipeAlgorithmBase
						,public IdentifiedClass
{
	friend	class	ResultBaseForAlgorithmRoot;
	friend	class	LogicDLL;
	friend	class	AlgorithmInPageRoot;
	friend	class	AlgorithmItemRoot;

	XDateTime		CreatedTime;
	AlgorithmLibraryListContainer	*CacheLib;
	AlgorithmLibraryStocker			*ManagedCacheLib;

	int32				AllocatedPhaseNumb;
	AlgorithmInPageInOnePhase	**PageDataPhase;
	LibraryListWithNGTypeContainer	NGListForInspect;
	QMutex				MutexFromItem;
	QReadWriteLock		MutexRegistHistgram;
	int					LoadedVersion;
	bool				ModeToShowNGMark;
	int					MaxMilisecInPage;

	ManualExecuter		ManualExecuterData;
protected:
	struct{
		bool	ModeParallelExecuteInitialAfterEditPrev	:1;
		bool	ModeParallelExecuteInitialAfterEdit		:1;
		bool	ModeParallelExecuteInitialAfterEditPost	:1;
		bool	ModeParallelExecuteStartByInspection	:1;
		bool	ModeParallelExecuteCaptured				:1;
		bool	ModeParallelExecutePreAlignment			:1;
		bool	ModeParallelExecuteAlignment			:1;
		bool	ModeParallelExecutePreProcessing		:1;
		bool	ModeParallelExecuteProcessing			:1;
		bool	ModeParallelExecuteProcessingRevived	:1;
		bool	ModeParallelExecutePostProcessing		:1;
		bool	ModeParallelExecutePreScanning			:1;
		bool	ModeParallelExecuteScanning				:1;
		bool	ModeParallelExecutePostScanning			:1;
	}ModeParallelForPhase;

public:
	class	RegisteredHistgramList : public NPList<RegisteredHistgramList>
	{
		QString	Name;
		int		ID;
	public:
		RegisteredHistgramList(void){	ID=-1;	}
		RegisteredHistgramList(const QString &_Name ,int id):Name(_Name),ID(id){}

		int				GetID(void)		{	return ID;		}
		const QString  &GetName(void)	{	return Name;	}
		
		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
		RegisteredHistgramList	&operator=(const RegisteredHistgramList &src);
	};
	class	RegisteredHistgramListContainer : public NPListPack<RegisteredHistgramList>
	{
	public:
		RegisteredHistgramListContainer(void){}

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
		RegisteredHistgramListContainer	&operator=(const RegisteredHistgramListContainer &src);
	};
	bool				EnableMoveForAlignment;

private:
	RegisteredHistgramListContainer	RegisteredHistgramContainer;

protected:
	LogicDLL			*LogicDLLPoint;

	bool			Changed;
	bool			CalcDone;
	bool			EnableToSave;	//If data is removed temporary, this is false
	bool			ModeLoadSaveInPlayer;	//Should add SetParam function if Algorithm needs this

	void	ReleaseData(void);
public:

	explicit	AlgorithmBase(LayersBase *Base);
	virtual	~AlgorithmBase(void);

	ModelType	GetModel(void);
	AlgorithmInPageRoot			*GetPageData(int page)	const;
	virtual	AlgorithmInPageRoot	*NewChild(AlgorithmBase *parent)=0;
	virtual	void	Initial(LayersBase *Base);
	virtual	void	InitialAfterParamLoaded(void);
	virtual	void	InitializeToStart(void);
	virtual	void	Release(void);
	virtual	bool	RemovePage(AlgorithmInPageRoot *pData);
	virtual	AlgorithmInPageRoot	*SetPageData(int page,AlgorithmInPageRoot *pData);
	virtual	void	SizeChanged(void);
	AlgorithmInPageInOnePhase	*GetPageDataPhase(int phase)	const;

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb);
	virtual	bool	Reallocate(int newPhaseNumb);
	virtual	bool	RemovePhase(int RemovedPhaseCode);
	virtual	bool	ReallocateMasterCount(int CountMaster);
	virtual	bool	InsertPage(int IndexPage);	//Create page before Indexed page
	virtual	bool	RemovePage(int IndexPage);

	
	LogicDLL		*GetLogicDLL(void)		const{		return LogicDLLPoint;	}
	bool	GetAlgorithmRootName(QString &DLLRoot ,QString &DLLName);
	bool	GetAlgorithmRootName(RootNameList &RetRootName);
	bool	GetModeToShowNGMark(void)		{	return ModeToShowNGMark;	}
	virtual	bool	HasReflection(ReflectionMode mode)	{	return false;	}
	const	QString	GetExplain(void);
	virtual	QString	GetNameByCurrentLanguage(void);

	virtual	void	MoveItemsToDispatcherForLoadingParts(void);
	virtual	void	CopyItemsFormDispatcherForParts(void);
	virtual	void	RemoveItemFormDispatcher(void);
	void	ChangeAlgorithmType(DWORD algorithmtype);
	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName ,int *Phase=NULL,int *Page=NULL ,int *Layer=NULL);
	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	bool	SaveHistgram(QIODevice *f);
	bool	LoadHistgram(QIODevice *f);

	virtual	bool	SaveUnique(QIODevice *f){	return true;	}
	virtual	bool	LoadUnique(QIODevice *f){	return true;	}

	virtual	bool	SaveOnlyBase(QIODevice *f);
	virtual	bool	LoadOnlyBase(QIODevice *f,QString &ErrorMsg);
	virtual	bool	LoadOnlyBase(QIODevice *f);
	virtual	bool	SaveOnlyThreshold(QIODevice *f);
	virtual	bool	LoadOnlyThreshold(QIODevice *f);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	void	DeliverTransmitDirectly(GUIDirectMessage *packet);
	virtual	bool				SaveInPacket(QIODevice *f ,GUIDirectMessage *packet);
			QString				LoadInPacket(QIODevice *f);
	virtual	GUIDirectMessage	*LoadInPacket(QIODevice *f ,const QString &ClassName)	{	return NULL;	}

	virtual void	SetupLibFolder(int LibFolderID ,int originalLibFolder){}	//originalLibFolder=-1: Only selection

	int			GetEffectivePageNumb(void)	const	{	return (PageDataPhase!=NULL)?PageDataPhase[0]->GetEffectivePageNumb():-1;	}
	QSqlDatabase	&GetDatabase(void)		const	{	return GetLayersBase()->GetDatabase();	}
	AlgorithmLibraryContainer	*GetLibraryContainer(void);
	AlgorithmLibrary			*CreateLibrary(void);

	int			GetLibType(void);
	bool		GetDLLName(QString &DLLRoot ,QString &DLLName)	const;
	virtual	WORD			GetDLLVersion(void);	
	int						GetSelectedItemCount(void);
	void					ReleaseAllSelectedItem(void);
	AlgorithmLibraryList	*FindLibFromCache(int LibID);
	int						GetLoadedVersion(void)		{	return LoadedVersion;	}
	void					SetLoadedVersion(WORD ver)	{	LoadedVersion=ver;	}
	void					SwitchThresholdLevel(int OldLevel ,int NewLevel);
	void					CopyThresholdLevel	(int SourceLevelID ,int DestLevelID);
	QString					GetLibComment(int LibID);
	virtual	void	EnumLibID(IntList &LibIDList);

	virtual	AlgorithmDrawAttr	*CreateDrawAttr(void)	=0;
	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr);
	virtual	void	DrawMove(int localPage ,int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr);
	virtual	bool	DrawResultBase(int32 ShowFixedPhase, ResultBaseForAlgorithmRoot *Res					  ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,int localPage);
	virtual	bool	DrawResultItem(ResultBaseForAlgorithmRoot *Res,IntList &LayerList ,QPainter &PntFromIData ,QImage &IData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG);
	virtual	void	DrawMonoBitmap(BYTE **BmpPoint);

	virtual	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteCaptured				(int ExeID ,ResultBaseForAlgorithmRoot *Res,ListPhasePageLayerPack &CapturedList);
	virtual	ExeResult	ExecutePreAlignment			(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteAlignment			(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecutePreProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteProcessing			(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecutePostProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecutePreScanning			(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteScanning				(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecutePostScanning			(int ExeID ,ResultBaseForAlgorithmRoot *Res);
	virtual	ExeResult	ExecuteManageResult			(int ExeID ,ResultInspection *Res)			{	return _ER_true;	}

	virtual	ExeResult	ExecuteRemoveResult(int32 MasterCode , LotBase *Lot , int64 InspectionID ,ResultBaseForAlgorithmRoot *Ref){	return _ER_true;	}
	//	ExecuteRemoveResult?が呼ばれるのは、検査結果が書き込まれずにバッフ?から取り除かれるとき

	bool			GetEnableMoveForAlignment(void)		{	return EnableMoveForAlignment;	}
	void			SetEnableMoveForAlignment(bool b)	{	EnableMoveForAlignment=b;		}
	virtual	void	MoveForAlignment(void);

	virtual	void	MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmItemIndependentPack &Data);
	virtual	void	SetIndependentItemData(int32 Command
											,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData);

	virtual	bool	GeneralDataRelease(int32 Command,void *data);
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData);
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data);
	virtual	bool	GeneralDataReply(int32 Command,void *data);

	virtual	void	ExecuteCopy(int localPage ,ClipboardAlgorithm &Pack,IntList &LayerList);
	virtual	void	ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,bool AllItems=false);
	virtual	void	ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems=false);
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int LocalPage ,int GlobalDx,int GlobalDy);

	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,bool SelectModeAfterPaste=false);
	virtual	bool	ShowPasteCreateWithShape(QByteArray &templateData,int Layer){	return true;	}
	virtual	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy
					,const QString &OriginRoot ,const QString &OriginName
					,int ItemClass);

	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item));
	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item));
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList);

	virtual	void	CopyFrom(AlgorithmBase *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode);
	virtual	void	InitializeFromParts(void);

	virtual	bool	IsEdited(void);
	virtual	bool	IsCalcDone(void);
	virtual	void	SetEdited(bool edited);
	virtual	void	SetCalcDone(bool calcdone);

	virtual	void	ResetProcessDone(void)		;
	virtual	bool	IsProcessDone(void)			;
	virtual	void	SetProcessDone(bool b=true)	;

	virtual	void	ExecuteTransformSelectedItems(TransformBase &M);

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData);
	virtual	int		GetUniqueAreaType(UniqueAreaType UTypeDim[] ,int MaxDimCount){		return 0;	}

	virtual	void	LoopOnIdle(void){}

	bool	GetNGTypeContainer(int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer);
	LibraryListWithNGType	*GetNGTypeList(int libID);
	LibraryListWithNGType	*SetNGTypeList(int libID);
	LibNGTypeItem	*GetLibNGTypeItem(int TypeUniqueCode);
	virtual	LibNGTypeItem	*SearchNGCause(LibraryListWithNGType *L, AlgorithmItemRoot *aitem,ResultPosList *p);

	void	ClearManagedCacheLib(void);
	bool	LoadManagedCacheLib(int LibID);
	AlgorithmLibraryLevelContainer	*ReloadManagedCacheLib(int LibID);
	bool	LoadAllManagedCacheLib(void);
	AlgorithmLibraryLevelContainer	*FindLibFromManagedCacheLib(int LibID);
	AlgorithmLibraryLevelContainer	*FindOrLoadLibFromManagedCacheLib(int LibID);

	void	ClearHistgram(void);
	void	RegistHistgram(AlgorithmItemRoot *item ,const QString &Name ,int id);
	void	EnumHistgram(QStringList &HistNames);
	QString	GetHistgramName(int HistID);
	void	EnumHistgram(AlgorithmBase::RegisteredHistgramListContainer &List);
	int		GetHistgramID(int row);

	virtual	void	MakeReportedTopics(ReportedTopicContainer &RetContainer)	const{}
	bool	ExecuteMacro(const QString &FuncName, QStringList &Args, bool &ExeReturn);

	ManualExecuter	&GetManualExecuter(void)	{	return ManualExecuterData;	}
	bool	ManualExecuteAll(void);

	void	SetEnableToSave(bool b)		{	EnableToSave=b;			}
	bool	GetEnableToSave(void)		{	return EnableToSave;	}

	bool	GetModeLoadSaveInPlayer(void)	{	return ModeLoadSaveInPlayer;	}
	void	SetModeLoadSaveInPlayer(bool b)	{	ModeLoadSaveInPlayer=b;			}
	int		GetMaxMilisecInPage(void)		{	return MaxMilisecInPage;		} 
	void	SetMaxMilisecInPage(int d)		{	MaxMilisecInPage=d;				}

	bool	GetDrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList);

	virtual	int	GetLearningMenu(LearningMenu MenuPointer[] ,int MaxDimCount)	{	return 0;	}
	bool	SetCurrentIntoThresholdLevel(int LevelID);	//Write current threshold into ThresholdLevel

	bool	ReqConfirmItemList(int page,ConfirmItemListContainer	&RetItemList);

	virtual	bool	AvailableShrinkItem(void)		const	{	return true;	}
	virtual	bool	AvailableChangeLibrary(void)	const	{	return true;	}
	virtual	bool	AvailableAlgorithmComponentWindow(void)	const;
	virtual	bool	AvailableGenerateBlock(void)	const	{	return false;	}

	virtual	void	ChildCopyShadowTreeParamLogicDLL(AlgorithmBase *Parent);
};


inline	LayersBase	*AlgorithmThreshold::GetLayersBase(void)	const{	return (Parent==NULL)?NULL:Parent->GetLayersBase();						}
inline	LayersBase	*AlgorithmItemRoot::GetLayersBase(void)		const{	return (GetParentBase()==NULL)?NULL:GetParentBase()->GetLayersBase();		}
inline	DataInPage	*AlgorithmItemRoot::GetDataInPage(void)		const{	return (GetLayersBase()==NULL)?NULL:GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());		}
inline	DataInLayer	*AlgorithmItemRoot::GetDataInLayer(void)	const{	return (GetDataInPage()==NULL)?NULL:GetDataInPage()->GetLayerData(GetLayer());	}
inline	ParamGlobal	*AlgorithmItemRoot::GetParamGlobal(void)	const{	return (GetParentBase()==NULL)?NULL:GetParentBase()->GetParamGlobal();	}
inline	ParamComm	*AlgorithmItemRoot::GetParamComm(void)		const{	return (GetParentBase()==NULL)?NULL:GetParentBase()->GetParamComm();	}
inline	int			AlgorithmItemRoot::GetLayer(void)	const	{	return (GetParentInLayer()!=NULL)?GetParentInLayer()->GetLayer():0;		}
inline	int			AlgorithmItemRoot::GetPage(void)	const	{	return GetParentInPage()->GetPage();				}
inline	void		AlgorithmItemRoot::SetMasterNo(int _MasterNo){	MasterNo=_MasterNo;	}
inline	int			AlgorithmItemRoot::GetMasterNo(void)		{	return MasterNo;	}

inline	int		AlgorithmInLayerRoot::GetPage(void)	const			{		return (GetParentInPage()==NULL)?0:GetParentInPage()->GetPage();	}
inline	LayersBase		*AlgorithmInLayerRoot::GetLayersBase(void)	const	{	return (GetParentBase()==NULL)?NULL:GetParentBase()->GetLayersBase();			}
inline	DataInPage		*AlgorithmInLayerRoot::GetDataInPage(void)	const	{	return (GetLayersBase()==NULL)?NULL:GetLayersBase()->GetPageDataPhase(GetPhaseCode())->GetPageData(GetPage());		}
inline	DataInLayer		*AlgorithmInLayerRoot::GetDataInLayer(void)	const	{	return (GetDataInPage()==NULL)?NULL:GetDataInPage()->GetLayerData(GetLayer());	}

inline	AlignmentPacket2D &AlignmentPacket2D::operator=(const AlignmentPacket2D &src)
{
	AlignmentPacketBase::operator=(src);
	PosXOnTarget=src.PosXOnTarget;
	PosYOnTarget=src.PosYOnTarget;
	ShiftX		=src.ShiftX;
	ShiftY		=src.ShiftY;
	Rotation	=src.Rotation;
	Priority	=src.Priority;
	return *this;
}

inline	AlgorithmLibraryContainer	*AlgorithmInPageRoot::GetLibraryContainer(void)	
{
	return (GetParentBase()!=NULL)?GetParentBase()->GetLibraryContainer():NULL;
}

inline	AlgorithmLibraryContainer	*AlgorithmInLayerRoot::GetLibraryContainer(void)
{
	return (GetParentBase()!=NULL)?GetParentBase()->GetLibraryContainer():NULL;
}

inline	AlgorithmLibraryContainer	*AlgorithmItemRoot::GetLibraryContainer(void)	const
{
	return (GetParentBase()!=NULL)?GetParentBase()->GetLibraryContainer():NULL;
}
inline	LayersBase	*AlgorithmInPageRoot::GetLayersBase(void)	const	{	return (GetParentBase()!=NULL)?GetParentBase()->GetLayersBase():NULL;			}

//=================================================================================================================

//-------------------------------------------------------------------------------------
class	AlgorithmItemIndependent : public NPList<AlgorithmItemIndependent>
{
public:
	int32				PhaseCode;
	int32				GlobalPage;
	int32				Layer;
	int64				ItemID;
	int32				LibID;
	int32				ItemClassType;
	AlgorithmItemRoot	*Data;
	QString				AlgorithmRoot;
	QString				AlgorithmName;
	LayersBase			*Base;
	QByteArray			Something;
	int32				Result;
	QString				TypeInNoLib;	//Categorized in LibID==-1

	AlgorithmItemIndependent(const AlgorithmItemIndependent &src);
	explicit	AlgorithmItemIndependent(LayersBase *base);
	explicit	AlgorithmItemIndependent(LayersBase *base,const QString &algorithmRoot ,const QString &AlgorithmName);

	void	Set(AlgorithmItemRoot *SrcToBeCopied);
	AlgorithmItemIndependent	&operator=(const AlgorithmItemIndependent &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

class	AlgorithmItemIndependentPack
{
public:
	IntList			EdittedMemberID;
	NPListPack<AlgorithmItemIndependent>	Items;
	LayersBase		*Base;
	int32			LocalX,LocalY;

	explicit	AlgorithmItemIndependentPack(LayersBase *base){	Base=base;	LocalX=LocalY=0;	}
	AlgorithmItemIndependentPack(const AlgorithmItemIndependentPack &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
	AlgorithmItemIndependentPack	&operator=(const AlgorithmItemIndependentPack &src);
};

//=================================================================================================================

class	ItemPointerListInPage : public NPList<ItemPointerListInPage>
{
public:
	int	Page;
	NPListPack<ItemPointerListInLayer>	LayerList;

	ItemPointerListInPage(void)		{	Page=0;		}
	explicit	ItemPointerListInPage(int page)	{	Page=page;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,AlgorithmInPageRoot *Pg,LayersBase *LBase);
	int	GetItemsCount(void);
};
class	ItemPointerListInLayer : public NPList<ItemPointerListInLayer>
{
public:
	int	Layer;
	NPListPack<ItemPointerList>			ItemList;

	ItemPointerListInLayer(void)		{	Layer=0;		}
	explicit	ItemPointerListInLayer(int layer)	{	Layer=layer;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f,AlgorithmInPageRoot *Pg,LayersBase *LBase);
	int	GetItemsCount(void);
};

class	ItemPointerList : public NPList<ItemPointerList>
{
public:
	AlgorithmItemRoot	*ItemPointer;
	bool				Created;
	int					Dx,Dy;

	ItemPointerList(void)					{	ItemPointer=NULL;	Created=false;	Dx=Dy=0;	}
	ItemPointerList(AlgorithmItemRoot *item,int dx ,int dy){	ItemPointer=item;	Created=false;	Dx=dx;	Dy=dy;	}
	~ItemPointerList(void);

	AlgorithmItemRoot	*GetItem(void)	const	{	return ItemPointer;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f ,AlgorithmItemRoot *CreatedItem,LayersBase *LBase);
};

#endif


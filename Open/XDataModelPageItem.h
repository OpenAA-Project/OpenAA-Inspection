/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDataModelPageItem.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDATAMODELPAGEITEM_H)
#define	XDATAMODELPAGEITEM_H


//#if	defined(DefinedModel)
//#error Model is already defined
//#endif
//#define	DefinedModel


#include "XDataAlgorithm.h"
#include "XResult.h"
#include "XAlgorithmBase.h"
#include "XHistgramByParam.h"
#include "XDataAlgorithmList.h"

class	ResultInPagePI;
class	ResultBaseForAlgorithmPI;
class	AlgorithmItemPI;
class   AlgorithmInPagePI;

//=========================================================================================


class  ResultInItemPI : public NPList<ResultInItemPI> ,public ResultInItemRoot
{
	ResultInPagePI	*Parent;
  public:

	ResultInItemPI(void){	Parent=NULL;	}
	
	void	SetParent(ResultInPagePI *parent){	Parent=parent;	}

	virtual	ResultInItemRoot	*Clone(void)	override;

	virtual	LogicDLL			*GetLogicDLL(void)			const	override;
	EntryPointBase				*GetEntryPoint(void)		const;
	ResultInPagePI				*GetParent(void)			const	{	return Parent;	}
	virtual	ResultInspection	*GetResultInspection(void)	const	override;
	virtual	int					GetPage(void)				const	override;
	virtual	int					GetPhaseCode(void)			const	override;
	virtual	int					GetLayer(void)				const	override;
	virtual	AlgorithmBase		*GetAlgorithmBase(void)		const	override;
	virtual	AlgorithmItemRoot	*GetAlgorithmItemRoot(void)	const	override;
	virtual	LayersBase			*GetLayersBase(void)		const	override;
	virtual	int					GetDotPerLine(void)			const	override;
	virtual	int					GetMaxLines(void)			const	override;
};


class	ResultInPagePI : public ResultInPageRoot
{
	friend	class	ResultInItemPI;
	friend	class	ResultInLayerPI;

	ResultBaseForAlgorithmRoot		*Parent;
	int32				AllocatedResultCount;
	NPListPack<ResultInItemPI>		Result;
public:

	explicit	ResultInPagePI(ResultBasePhase *pPhaseParent,DataInPage *pPage);
	virtual	~ResultInPagePI(void);

	virtual	ResultInItemRoot	*CreateItem(void)			override;
	virtual	ResultInItemRoot	*CreateItemDim(int count)	override;
	virtual	ResultInItemRoot	*FindResultInItem(int layer ,int ItemID)	const	override;
	virtual	ResultInItemRoot	*FastSearchIDItem(int layer ,int ItemID)	const	override;

	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)	override;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)	override;

	virtual	bool	Initial(ResultBaseForAlgorithmRoot *parent)	override;
	virtual	void	Alloc(AlgorithmInPagePI *page);
	virtual	void	Release(void)	override;
	virtual	bool	Reallocate(int newLayerNumb)	override{	return true;	};

	virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file)	override;
	virtual	void	MoveMerge(ResultInPageRoot &dst)	override;
	virtual	ResultDLLBaseRoot	*GetResultDLLBase(void)	const	override;
	ResultInItemPI		*GetItem(int number);
	ResultInItemPI		*SearchItem(int number)		{	return GetItem(number);		}
	ResultInItemPI		*GetResultFirst(void)		{	return Result.GetFirst();	}
	ResultInItemPI		*GetResultItem(int number)	{	return Result[number];		}
	int					GetResultCount(void)		{	return Result.GetNumber();	}
	int					GetItemCount(void)			{	return AllocatedResultCount;	}

	AlgorithmInPageRoot			*GetAlgorithmInPage(void)	const;
	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override;
	AlgorithmBase				*GetAlgorithmBase(void)				const	override;

	virtual	void	InitialInspection(void)	override;
	virtual	bool	GatherResult(bool3 &OK)	const	override;
	virtual	bool	GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const override;

	virtual	int			GetNGCount(void)		const	override;
	virtual	int			GetNGPointCount(void)	const	override;
	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)	override;
	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,char *ResList)		override;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)			override;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f,int &WrittenNGCount)		override;
	virtual	void	OutputResult(FlexArea &Area ,int OffsetX ,int OffsetY
								,int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)	override;
	virtual	ResultInspection	*GetResultInspection(void)	const	override;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)	override;
	virtual	void	GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)	override;
	virtual	void	GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)	override;
	virtual	void	BindNGAreaListContainer(NGAreaListContainer &List)	override;
	virtual	void	ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item,void *_Something),void *Something)	override;
	virtual	void	ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something)	override;
	virtual	void	MakeResultDetailInNG(DetailResultInfoListContainerAll &List)	override;

	virtual	void	SetResultMarkForLearning(void)	override;
	virtual	void	ReviveResult(LearningImage *c)	override;
	virtual	int		GetPointerListOfResultPosList(FlexArea &OverlapArea ,ResultPosList **RetDim ,int MaxCount)	override;

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID)	override;
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID)	override;
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID)	override;
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ListPhasePageLayerPack &CapturedList)	override;
	virtual	ExeResult	ExecutePreAlignment			(int ExeID)	override;
	virtual	ExeResult	ExecuteAlignment			(int ExeID)	override;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID)	override;
	virtual	ExeResult	ExecuteProcessing			(int ExeID)	override;
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID)	override;
	virtual	ExeResult	ExecutePostProcessing		(int ExeID)	override;
	virtual	ExeResult	ExecutePreScanning			(int ExeID)	override;
	virtual	ExeResult	ExecuteScanning				(int ExeID)	override;
	virtual	ExeResult	ExecutePostScanning			(int ExeID)	override;

	virtual	void	SetCurentCalcDone(bool b)	override;
	virtual	void	ClearResult(void)			override;

protected:
	NPListPack<ResultInItemPI>	&GetRawResult(void)	const{	return (NPListPack<ResultInItemPI>	&)Result;	}
};

inline	ResultInItemRoot	*ResultInPagePI::CreateItem(void)
{	
	ResultInItemRoot	*r;
	if(AlgoPointer!=NULL){
		r=AlgoPointer->CreateResult();
	}
	else{
		r=new ResultInItemPI();	
	}
	((ResultInItemPI *)r)->SetParent(this);
	return r;
}
inline	ResultInItemRoot	*ResultInPagePI::CreateItemDim(int count)
{
	ResultInItemPI	*r=new ResultInItemPI[count];
	for(int i=0;i<count;i++){
		r[i].SetParent(this);
	}
	return r;
}


class	ResultBaseForAlgorithmPI : public ResultBaseForAlgorithmRoot
{
	friend	class	ResultInItemPI;
	friend	class	ResultInLayerPI;
	friend	class	ResultInPagePI;
public:

	explicit	ResultBaseForAlgorithmPI(LogicDLL *parent);
	virtual	~ResultBaseForAlgorithmPI(void);

	virtual	ResultInPageRoot	*CreatePage(int phase ,int page)			override;
	virtual	ResultBaseForAlgorithmRoot	*CreateResultBaseForAlgorithm(void)	override;
	virtual	bool	DrawResult(int32 ShowFixedPhase
						,QPainter &PntFromIData ,QImage *IData 
						,int MovX ,int MovY ,double ZoomRate,int localPage)	override;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)			override;
	virtual	void	ExecuteInAllItems(int phase,void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)	override;
};

inline	LayersBase			*ResultInItemPI::GetLayersBase(void)	const
{
	return (Parent!=NULL)?Parent->GetLayersBase():NULL;
}
inline	ResultInspection	*ResultInItemPI::GetResultInspection(void)	const{	return (Parent!=NULL)?Parent->GetResultInspection():NULL;	}
inline	ResultInspection	*ResultInPagePI::GetResultInspection(void)	const{	return (Parent!=NULL)?Parent->GetResultInspection():NULL;	}
inline	int	ResultInItemPI::GetPage(void)		const	{	return (Parent!=NULL)?Parent->GetPage():-1;	}
inline	int	ResultInItemPI::GetPhaseCode(void)	const	{	return (Parent!=NULL)?Parent->GetPhaseCode():-1;	}
inline	int	ResultInItemPI::GetLayer(void)		const	{	return 0;	}

//=========================================================================================

class	AlgorithmItemPI : public NPList<AlgorithmItemPI> ,public AlgorithmItemRoot
{
	friend	class   AlgorithmInPagePI;
protected:
	AlgorithmInPagePI	*Parent;

public:
	AlgorithmItemPI(void);
	explicit	AlgorithmItemPI(FlexArea &area);
	explicit	AlgorithmItemPI(FlexArea *area);	//Use area memory
	virtual	~AlgorithmItemPI(void){}

	virtual	void	SetItemID(void)	override;
	virtual	AlgorithmItemPI	&operator=(const AlgorithmItemRoot &src)	override;

	virtual	XYData						GetOutlineOffset(void)		override;
	virtual	AlgorithmBase				*GetParentBase(void)		const	override;
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override;
	virtual	AlgorithmInPageRoot			*GetParentInPage(void)		const	override;
	virtual	AlgorithmInLayerRoot		*GetParentInLayer(void)		const	override;
	virtual	AlgorithmParentFromItem		*GetParentAlgorithm(void)	const	override;
	AlgorithmInPagePI	*GetParent(void){	return Parent;	}
	virtual	void	CopyFrom(AlgorithmItemRoot *src)	override;

	virtual	void	SetParentVirtual(AlgorithmParentFromItem *parent)	override;
	virtual	void	SetParent(AlgorithmInPagePI *parent);
	ExeResult	ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo,ResultInItemRoot *Res ,ExecuteInitialAfterEditInfo &EInfo) override;
	virtual	ResultInItemRoot	*GetCurrentResult(void)			override;
	virtual	ResultInItemRoot	*GetResult(ResultInPageRoot *Rp)override;

	virtual	ClipboardAlgorithmItem	*CreateClipboardItem(void)	override;
	virtual	void	CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)	override;

	ImageBuffer		**GetMasterBuff(void);
	ImageBuffer		**GetMasterBuff(int n);
	ImageBuffer		**GetTargetBuff(void);
	ImageBuffer		**GetTargetTRBuff(void);
	ImageBuffer		**GetBitBuff(void);

	virtual	bool	SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)	override;

	int	GetMasterBuffList		(ImageBuffer *ImageList[]);
	int	GetMasterBuffList		(int n,ImageBuffer *ImageList[]);
	int	GetBackGroundBuffList	(ImageBuffer *ImageList[]);
	int	GetBackGroundBuffList	(int n,ImageBuffer *ImageList[]);
	int	GetTargetBuffList		(ImageBuffer *ImageList[]);
	int	GetTargetTRBuffList		(ImageBuffer *ImageList[]);
	int	GetBitBuffList			(ImageBuffer *ImageList[]);
	int	GetTrialTargetBuffList	(ImageBuffer *ImageList[]);

	int	GetMasterBuffList		(ImagePointerContainer &ImageList);
	int	GetMasterBuffList		(int n,ImagePointerContainer &ImageList);
	int	GetBackGroundBuffList	(ImagePointerContainer &ImageList);
	int	GetBackGroundBuffList	(int n,ImagePointerContainer &ImageList);
	int	GetTargetBuffList		(ImagePointerContainer &ImageList);
	int	GetTargetTRBuffList		(ImagePointerContainer &ImageList);
	int	GetBitBuffList			(ImagePointerContainer &ImageList);
	int	GetTrialTargetBuffList	(ImagePointerContainer &ImageList);

	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	override;

	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,AlgorithmLibrary *LibData ,void *Anything=NULL)	;	
	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBufferListContainer &Map ,void *Anything=NULL)							;		
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL)	override;
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL)								override;
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)							override;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	override	{	return true;	}
protected:
	virtual	AlgorithmThreshold	*GetThresholdDummy(void)	override;
};


template<class TPage,class TBase>
class	AlgorithmItemPITemplate : public AlgorithmItemPI
{
public:
	AlgorithmItemPITemplate(void){}
	AlgorithmItemPITemplate(FlexArea &area):AlgorithmItemPI(area){}

	TBase	*tGetOrigin(void)	{	return (TBase *)(AlgorithmItemPI::GetOrigin());	}
	TBase	*tGetParentBase(void)	{	return (TBase *)(AlgorithmItemPI::GetParentBase());		}
	TPage	*tGetParentInPage(void)	{	return (TPage *)(AlgorithmItemPI::GetParentInPage());		}
};

class   AlgorithmInPagePI : public AlgorithmInPageRoot
{
	friend	class	AlgorithmItemPI;
	friend	class	AlgorithmBasePI;

	class	OMPAlgorithmItemStruct
	{
	public:
		int	ThreadNo;
		AlgorithmItemPI		**CalcThread;
		ResultInItemPI		**Result;
		int					CalcThreadCount;
		AlgorithmInPagePI	*Parent;

		OMPAlgorithmItemStruct(void);
		virtual	~OMPAlgorithmItemStruct(void);
		void	Alloc(AlgorithmInPagePI *parent ,int threadNo,int N);
		void	Set(int n,AlgorithmItemPI	*c,ResultInItemPI	*r);

		ExeResult	ExecuteInitialAfterEditPreve(int ExeID,ExecuteInitialAfterEditInfo &EInfo);
		ExeResult	ExecuteInitialAfterEdit		(int ExeID,ExecuteInitialAfterEditInfo &EInfo);
		ExeResult	ExecuteInitialAfterEditPost	(int ExeID,ExecuteInitialAfterEditInfo &EInfo);
		ExeResult	ExecuteStartByInspection	(int ExeID);
		ExeResult	ExecuteCaptured				(int ExeID,ListPhasePageLayerPack &CapturedList);
		ExeResult	ExecutePreAlignment			(int ExeID);
		ExeResult	ExecuteAlignment			(int ExeID);
		ExeResult	ExecutePreProcessing		(int ExeID);
		ExeResult	ExecuteProcessing			(int ExeID);
		ExeResult	ExecuteProcessingRevived	(int ExeID);
		ExeResult	ExecutePostProcessing		(int ExeID);
		ExeResult	ExecutePreScanning			(int ExeID);
		ExeResult	ExecuteScanning				(int ExeID);
		ExeResult	ExecutePostScanning			(int ExeID);
	}*CalcThreadDim;
	int	ThreadNumb;
	int	CalcThreadDataCount;

	int				DrawResultTableNumb;
	AlgorithmItemPI	**DrawResultATable;
	ResultInItemPI	**DrawResultRTable;
	int32			AllocatedCountMasterBuff;
	int32			AllocatedCountBackGroundBuff;
	ImageBuffer		***MasterBuffDim;
	ImageBuffer		***BackGroundBuffDim;
	ImageBuffer		**TargetBuffDim;
	ImageBuffer		**TargetTRBuffDim;
	ImageBuffer		**BitBuffDim;
	ImageBuffer		**TrialTargetBuffDim;
	QMutex			MutexTemporaryItem;

protected:
	NPListPack<AlgorithmItemPI>		Data;
	NPListPack<AlgorithmItemPI>		Dispatcher;
	NPListPack<AlgorithmItemPI>		RentalData;
	NPListPack<ItemPointerList>		TemporaryItemList;
	AlgorithmThreshold	*ThresholdDummy;

protected:
	AlgorithmBase				*Parent;

	void	ReleaseData(void);

public:
	explicit	AlgorithmInPagePI(AlgorithmBase *parent);
	virtual	~AlgorithmInPagePI(void);

	virtual	ModelType	GetModel(void)	override	{	return	Model_PI;	}
	virtual	void		Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)	override;
	virtual	void		InitializeToStart(void)			override;
	virtual	void		InitialAfterParamLoaded(void)	override;
	virtual	void		Release(void)					override;
	virtual	bool		ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool		Reallocate(int newLayerNumb)	override;
	virtual	void		SizeChanged(LayersBase *Base)	override;
	virtual	bool		ReallocateMasterCount(int CountMaster)	override;

	virtual	bool		CopyShadowAlgorithmPage(ShadowTree *Child ,const AlgorithmInPageRoot &SrcParent)	override;
	virtual	bool		CopyShadowAlgorithmItem(ShadowTree *Child ,const AlgorithmItemRoot &ParentItem)	override	{	return true;	}

	virtual	bool		GetDLLName(QString &DLLRoot ,QString &DLLName);
	AlgorithmBase		*GetParentBase(void)	const	override	{	return Parent;	}
	DataInPage			*GetDataInPage(void)	const	override	{	return AlgorithmInPageRoot::GetDataInPage();	}
	AlgorithmInPageRoot	*GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	const	override;
	virtual	int			GetSelectedItemCount(void)	override;
	virtual	int			GetItemCount(void)			override;
	virtual	void		ReleaseAllSelectedItem(void)override;
	virtual	void		RemoveAllDatas(void)		override;
	virtual	void		RemoveAllDatasWithoutLocked(void)	override;

	virtual	AlgorithmItemPI	*GetFirstData(void)		const	{	return(Data.GetFirst());	}
	//virtual	void		InitialInspection(void);
	virtual	AlgorithmItemRoot	*GetItemData(int layer ,int itemID)		const	override;
	virtual	AlgorithmItemRoot	*FindFastItemData(int layer ,int itemID)const	override;
	virtual	void				LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)	override;
	virtual	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const	override;

	AlgorithmItemPI		*GetItem(int localX ,int localY)	const;
	AlgorithmItemPI		*GetItemRoot(int number)	const	override	{	return Data.GetItem(number);	}
	virtual	void	FastSearchIDItemStart(void)				override;
	virtual	AlgorithmItemRoot	*SearchIDItem(int itemID)					const	override;
	virtual	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName)	const	override;
	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item);
	virtual	void		RemoveItem(AlgorithmItemRoot *item);
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID);
	virtual	bool		AppendItems(AlgorithmItemPointerListContainer &items)	override;
	virtual	bool		RemoveItems(AlgorithmItemPointerListContainer &items)	override;
	virtual	void		RemoveAllDatasByManual(bool CreatedManually)			override;
	virtual	void		RemoveAllDatasWithoutManual(void)						override;
	virtual	int64		GetMaxItemID(void)		const	override;

	virtual	void	InsertItem(AlgorithmItemRoot *item,AlgorithmItemRoot *Key);
	void	InitialThreadBufferForExecute(void);

	virtual	bool		Save(QIODevice *f)				override;
	virtual	bool		Load(QIODevice *f)				override;
	virtual	bool		LoadByTransform(QIODevice *f ,TransformBase &Param)	override;
	virtual	bool		LoadAppend(QIODevice *f)		override;
	virtual	bool		SaveHistgram(QIODevice *f)		override;
	virtual	bool		LoadHistgram(QIODevice *f)		override;
	virtual	void		ClearHistgram(void)				override;
	virtual	bool		SaveOnlyThreshold(QIODevice *f)	override;
	virtual	bool		LoadOnlyThreshold(QIODevice *f)	override;

	virtual	void		TransmitDirectly(GUIDirectMessage *packet)			override;
	virtual	void		DeliverTransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	AlgorithmInLayerRoot	*NewChild(AlgorithmInPageRoot *parent)	override	{	return NULL;	}

	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)		override;
	virtual	void	RemoveItemFormDispatcher(void)				override;
	virtual	void	ClearResult(void)							override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)				override;
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	bool	DrawResult	  (ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)		override;
	virtual	bool	DrawResultItem(ResultInPageRoot *Res,IntList &LayerList ,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	DrawMonoBitmap(BYTE **BmpPoint)	override;
	virtual	void	DrawItems(QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)	override;
	virtual	void	DrawResultItem(ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,IntList &LayerList ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)override;

	virtual	void	MakeIndependentItems(bool SubResultMoving, ResultInPageRoot *RPage,int localX ,int localY,AlgorithmItemIndependentPack &Data)	override;
	virtual	void	MakeIndependentItems(int Layer ,IntList	&Items,AlgorithmItemIndependentPack &Data)	override;
	virtual	void	SetIndependentItemData(int32 Command
											,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData)	override;

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ResultInPageRoot *Res,ListPhasePageLayerPack &CapturedList)	override;
	virtual	ExeResult	ExecutePreAlignment			(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment			(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing			(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing		(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecutePreScanning			(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecuteScanning				(int ExeID,ResultInPageRoot *Res)	override;
	virtual	ExeResult	ExecutePostScanning			(int ExeID,ResultInPageRoot *Res)	override;

	ExeResult	FuncExecuteInitialAfterEditPrev	(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	FuncExecuteInitialAfterEdit		(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	FuncExecuteInitialAfterEditPost	(int ExeID,ResultInPageRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	FuncExecuteStartByInspection	(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecuteCaptured				(int ExeID,ResultInPageRoot *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	FuncExecutePreAlignment			(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecuteAlignment			(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecutePreProcessing		(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecuteProcessing			(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecuteProcessingRevived	(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecutePostProcessing		(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecutePreScanning			(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecuteScanning				(int ExeID,ResultInPageRoot *Res);
	ExeResult	FuncExecutePostScanning			(int ExeID,ResultInPageRoot *Res);

	virtual	void	MoveForAlignment(void)	override;

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)	override;
	virtual	void	RefreshByMap(int layer,ReflectionMode Mode,ConstMapBufferListContainer &Map)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	void	GetItemBitmap(BYTE **Dst ,int XByte, int XLen ,int YLen);
	virtual	void	SelectAll(const IntList &LayerList=IntList())			override;
	virtual	void	SelectItems(const IntList &ItemIDs);
	virtual	void	SelectLocked(const IntList &LayerList=IntList())		override;
	virtual	void	SelectLibs(SelectLibListContainer &SelectedList)		override;
	virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect);
	virtual	void	SelectPoint(int localX, int localY);
	virtual	void	SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode	,const IntList &LayerList=IntList())	override;
	virtual	void	CutArea(FlexArea &localArea,const IntList &LayerList,bool MultiSelect,const QByteArray &Something=QByteArray())	override;
	virtual	void	SeparateItems(FlexArea &localArea,const IntList &LayerList)				override;
	virtual	void	RegistArea(FlexArea &localArea,const IntList &LayerList=IntList())		override;
	virtual	void	DeleteSelectedItems(const IntList &LayerList=IntList())	override;
	virtual	void	UndoDeleteSelectedItems(QIODevice *f)					override;
	virtual	void	LockSelectedItems(const IntList &LayerList=IntList())	override;
	virtual	void	UndoLockSelectedItems(QIODevice *f)						override;
	virtual	void	UnlockAll(const IntList &LayerList=IntList())			override;
	virtual	void	UndoUnlockAll(QIODevice *f)								override;
	virtual	void	BindSelectedItems(const IntList &LayerList=IntList())	override;
	virtual	void	UndoBindSelectedItems(QIODevice *f)						override;
	virtual	void	Activate(int localX ,int localY,IntList &LayerList ,ListLayerAndIDPack &RetItem)	override;
	virtual	void	Activate(int Layer ,int ItemID)							override;
	virtual	void	AddActivate(int Layer ,int ItemID)						override;
	virtual	void	Inactivate(void)										override;
	virtual	void	GetItemIDListOnPoint(int localX,int localY,IntList &RetList);
	virtual	void	GetItemIDListOnPoint(FlexArea &CoveredArea ,IntList &RetList);

	virtual	void	SelectItems(FlexArea &Area ,const IntList &LayerList ,bool MultiSelect)			override;
	virtual	void	GetLayerAndItemID(int LocalX ,int LocalY ,ListLayerIDLibNamePack &ItemList ,const IntList &LayerList=IntList())	override;
	virtual	void	GetLayerAndItemID(FlexArea &CoveredArea ,ListLayerAndIDPack &ItemList ,const IntList &LayerList=IntList())		override;
	virtual	void	GetItems(ListLayerAndIDPack &ItemList ,AlgorithmItemPointerListContainer &Items)								override;
	virtual	void	EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)					override;
	virtual	void	EnumOriginTypeItems(int layer ,OriginType b ,AlgorithmItemPointerListContainer &Items)	override;
	virtual	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	EnumItems(int layer ,void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))				override;
	virtual	void	ScanItems(int layer ,void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)										override;
	virtual	void	EnumItems(int layer,ListPhasePageLayerLibIDPack &ItemIDList)	override;

	virtual	void	SelectItemByID(ListLayerAndIDPack &SelectedItem)									override;
	virtual	void	GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)						override;
	virtual	void	EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	override;
	virtual	void	EnumItemsByLib(int layer ,IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	override;
	virtual	void	EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)						override;
	virtual	void	EnumAllItems(int layer,AlgorithmItemPointerListContainer &ItemPointers)		override;
	virtual	void	GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)					override;
	virtual	void	AppendItemsInPage(int Layer,AlgorithmItemPointerListContainer &SrcPointers)			override;
	virtual	void	RemoveItemsInPage(int Layer,IntList &IDList)										override;
	virtual	void	EnumSelectedItems(ListPageLayerIDPack &Items)										override;
	virtual	void	SwitchThresholdLevel(int OldLevel ,int NewLevel)									override;
	virtual	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)							override;
	void	RemoveInvalidItems(void);

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList=IntList())			override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)							override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems=false)	override;
	virtual	void	UndoExecuteMove(QIODevice *f)														override;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)				override;
	virtual	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
												,FlexArea &area ,AlgorithmBase *OriginBase
												,int ItemClass)											override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste=false)				override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,VectorLineBase *Vector,bool SelectModeAfterPaste=false)		override;
	void	UndoExecutePaste(QIODevice *f);
	virtual	bool	ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)	override;

	virtual	void	VisibleAll(const IntList &LayerList=IntList())			override;
	virtual	void	InvisibleAll(const IntList &LayerList=IntList())		override;
	virtual	void	InvisibleSelected(const IntList &LayerList=IntList())	override;
	virtual	void	SelectManualCreature(const IntList &LayerList=IntList())override;
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)				override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;
	virtual	void	EnumLibID(IntList &LibIDList)							override;
	virtual	void	MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)			override;
	virtual	bool	GetSelectedCenter(DotListContainer &CenterByLayer)		override;
	virtual	bool	GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)		override;
	virtual	bool	GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	override;

	virtual	void	GenerateAlgorithmItemCount(AlgorithmItemCountInPage &Ret)	override;
	virtual	void	CopyFrom(AlgorithmBase *DestParent
							,AlgorithmInPageRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)						override;
	virtual	void	InitializeFromParts(void)								override;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)			override;
	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList ,const IntList &LayerList=IntList())	override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase,const IntList &LayerList=IntList())				override;
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)override;

	virtual	bool	IsEdited(void)				override;
	virtual	bool	IsCalcDone(void)			override;
	virtual	void	SetEdited(bool edited)		override;
	virtual	void	SetCalcDone(bool calcdone)	override;

	virtual	void	ResetProcessDone(void)		override;
	virtual	bool	IsProcessDone(void)			override;
	virtual	void	SetProcessDone(bool b=true)	override;

	virtual	void	ClearTemporaryItems(void)						override;
	virtual	void	SetTemporaryItems(ItemPointerListInPage *Pg)	override;
	virtual	void	AddItemsForMove(ItemPointerListInPage *Pg)		override;
	virtual	void	UndoAddItemsForMove(QIODevice *f)				override;

	virtual	void	SelectedItemListsForPaste(IntList &LayerList ,ExpandedSelectedItemListContainer &Lists)	override;
	virtual	void	DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int Layer,int ItemID,double ZoomRate ,int movx ,int movy,int turn)	override;
	virtual	void	ExecuteTransformSelectedItems(TransformBase &M)			override;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	override;
	virtual	bool	SaveItemsForLearning(ItemDataListWithIDContainer &Buff
											,FlexArea &LocalArea
											,AlgorithmLibraryListContainer &LibList
											,int AddedX,int AddedY,bool OkMode)	override;
	virtual	bool	LoadItemsForLearning(ItemDataListWithIDContainer &Buff,int AddedX ,int AddedY)	override;
	virtual	bool	GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)		override;
	virtual	HistgramByParamBase	*GetHistgramBase(int Layer,int ItemID,int HistID)					override;
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)								override;
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected)						override;
	virtual	bool	ShrinkItems(const IntList &LayerList,int ExpandPixels,bool MaskForSameLib)		override;

	virtual	void	EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)			override;
	virtual	void	EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)override;

	ImageBuffer		**GetMasterBuff(void);
	ImageBuffer		**GetMasterBuff(int n);
	ImageBuffer		**GetBackGroundBuff(void);
	ImageBuffer		**GetBackGroundBuff(int n);
	ImageBuffer		**GetTargetBuff(void);
	ImageBuffer		**GetTargetTRBuff(void);
	ImageBuffer		**GetBitBuff(void);
	ImageBuffer		**GetTrialTargetBuff(void);

	int	GetMasterBuffList		(ImageBuffer *ImageList[]);
	int	GetMasterBuffList		(int n ,ImageBuffer *ImageList[]);
	int	GetBackGroundBuffList	(ImageBuffer *ImageList[]);
	int	GetBackGroundBuffList	(int n ,ImageBuffer *ImageList[]);
	int	GetTargetBuffList		(ImageBuffer *ImageList[]);
	int	GetTargetTRBuffList		(ImageBuffer *ImageList[]);
	int	GetTrialTargetBuffList	(ImageBuffer *ImageList[]);

	int	GetMasterBuffList		(ImagePointerContainer &ImageList);
	int	GetMasterBuffList		(int n,ImagePointerContainer &ImageList);
	int	GetBackGroundBuffList	(ImagePointerContainer &ImageList);
	int	GetBackGroundBuffList	(int n,ImagePointerContainer &ImageList);
	int	GetTargetBuffList		(ImagePointerContainer &ImageList);
	int	GetTargetTRBuffList		(ImagePointerContainer &ImageList);
	int	GetTrialTargetBuffList	(ImagePointerContainer &ImageList);

	virtual	ResultInItemRoot	*CreateResult(void)	override	{	return new ResultInItemPI();	}
	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData)	override;
	virtual void	MakeBindedThreshold(BindedThresholdContainer &Container)override;

	virtual	void	GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items) override;
	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes) override;

	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList)	override;
	virtual	void	MasterImageHasChanged(void)	override;
};

template<class TItem,class TBase>
class	AlgorithmInPagePITemplate : public AlgorithmInPagePI
{
public:
	explicit	AlgorithmInPagePITemplate(AlgorithmBase *parent):AlgorithmInPagePI(parent){}

	TBase	*tGetParentBase(void)		{	return (TBase *)GetParentBase();		}
	TItem	*tGetItemData(int itemID)	{	return (TItem *)GetItemData(0 ,itemID);	}
	TItem	*tGetFirstData(void)		{	return (TItem *)GetFirstData();			}
	TItem	*tCreateItem(int ItemClassType=0)	
			{	
				TItem *Item=(TItem *)CreateItem(ItemClassType);
				Item->SetParent(this);
				return Item;
			}
};

//=========================================================================================
inline	bool	AlgorithmInPagePI::GetDLLName(QString &DLLRoot ,QString &DLLName)
{
	return GetParentBase()->GetDLLName(DLLRoot ,DLLName);
}

inline	AlgorithmThreshold	*AlgorithmItemPI::GetThresholdDummy(void)
{
	if(GetParent()==NULL)
		return NULL;
	if(GetParent()->ThresholdDummy==NULL){
		GetParent()->ThresholdDummy=CreateThresholdInstance();
	}
	return GetParent()->ThresholdDummy;
}


#endif

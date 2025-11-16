/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDataModelPageLayerItem.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDATAMODELPAGELAYERITEM_H)
#define	XDATAMODELPAGELAYERITEM_H

//#if	defined(DefinedModel)
//#error Model is already defined
//#endif
//#define	DefinedModel

#include "XDataAlgorithm.h"
#include "XResult.h"
#include "XHistgramByParam.h"
#include "XDataAlgorithmList.h"

class	ResultInLayerPLI;
class	ResultInPagePLI;
class	ResultBaseForAlgorithmPLI;
class	AlgorithmItemPLI;
class   AlgorithmInLayerPLI;
class   AlgorithmInPagePLI;
class   SlaveCommReqRentalItems;
class   SlaveCommAckRentalItems;
class   ConfirmItemListContainer;

//=========================================================================================


class  ResultInItemPLI : public ResultInItemRoot
{
	ResultInLayerPLI	*Parent;
public:

	ResultInItemPLI(void){	Parent=NULL;	}
	void	SetParent(ResultInLayerPLI *parent){	Parent=parent;	}

	virtual	ResultInItemRoot	*Clone(void)	override;

	virtual	LogicDLL			*GetLogicDLL(void)			const	override;
	EntryPointBase				*GetEntryPoint(void)		const;
	virtual	ResultInspection	*GetResultInspection(void)	const	override;
	ResultInLayerPLI			*GetParent(void)			const	{	return Parent;	}
	virtual	int					GetPage(void)				const	override;
	virtual	int					GetPhaseCode(void)			const	override;
	virtual	int					GetLayer(void)				const	override;
	virtual	AlgorithmBase		*GetAlgorithmBase(void)		const	override;
	virtual	AlgorithmItemRoot	*GetAlgorithmItemRoot(void)	const	override;
	virtual	LayersBase			*GetLayersBase(void)		const	override;
	virtual	int					GetDotPerLine(void)			const	override;
	virtual	int					GetMaxLines(void)			const	override;
};


class	ResultInLayerPLI : public NPList<ResultInLayerPLI> ,public ResultInLayerRoot
{
	friend	class	ResultInItemPLI;
	friend	class	ResultInPagePLI;

	ResultInPagePLI		*Parent;
	ResultInItemPLI		*Result;
	int32				AllocatedResultCount;
public:

	explicit	ResultInLayerPLI(DataInLayer *pDataInLayer,ResultInPagePLI *parent);
	virtual	~ResultInLayerPLI(void);

	virtual	ResultInItemRoot	*CreateItem(void)				override;
	virtual	ResultInItemRoot	*CreateItemDim(int count)		override;
	virtual	ResultInItemPLI		*FindResultInItem(int ItemID)	const;
	virtual	ResultInItemRoot	*FastSearchIDItem(int ItemID)	const	override;

	void	Initial(ResultBaseForAlgorithmRoot *parent	)	override;

	virtual	AlgorithmInLayerRoot		*GetAlgorithmInLayer(void)			const	override;
	virtual	AlgorithmInPageRoot			*GetAlgorithmInPage(void)			const	override;
	virtual	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override;
	virtual	AlgorithmBase				*GetAlgorithmBase(void)				const	override;
	void	Alloc(AlgorithmInLayerPLI *ALayer);
    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file)	override;
	virtual	void	MoveMerge(ResultInLayerRoot &dst)	override;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)	override;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)	override;

	virtual	ResultInItemPLI		*GetResultItem(int number)	const	{	return &Result[number];	}
	int		GetItemCount(void)								const	{	return AllocatedResultCount;	}

	virtual	XDateTime	&GetStartInspectionTime(void)	override;
	virtual	void	InitialInspection(void)				override;
	virtual	int		GetNGCount(void)						const	override;
	virtual	int		GetNGPointCount(void)					const	override;
	virtual	ResultInspection	*GetResultInspection(void)	const	override;

	virtual	bool	GatherResult(bool3 &OK)				override;
	virtual	bool	GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const override;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)	override;
	virtual	int		GetPage(void)	const	override;
	virtual	void	GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)	override;
	virtual	void	GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)	override;
	virtual	void	BindNGAreaListContainer(NGAreaListContainer &List)	override;
	virtual	void	ExecuteFuncInAllItems(void (*ItemFunc)(ResultInItemRoot *Item,void *_Something),void *Something);
	virtual	void	ExecuteFuncInAllItemPos(void (*PosFunc)(ResultInItemRoot *Item, ResultPosList *RPos,void *_Something),void *Something);
	virtual	void	MakeResultDetailInNG(DetailResultInfoListContainerAll &List);

	virtual	void	SetResultMarkForLearning(void);
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
};

inline	ResultInItemRoot	*ResultInLayerPLI::CreateItemDim(int count)
{
	ResultInItemPLI	*r=new ResultInItemPLI[count];
	return r;
}

class	ResultInPagePLI : public ResultInPageRoot
{
	friend	class	ResultInItemPLI;
	friend	class	ResultInLayerPLI;

	ResultBaseForAlgorithmRoot		*Parent;
	NPListPack<ResultInLayerPLI>	LayerData;
public:

	explicit	ResultInPagePLI(ResultBasePhase *pPhaseParent,DataInPage *pPage);
	virtual	~ResultInPagePLI(void);

	virtual	ResultInItemRoot	*CreateItem(void)			override {	return NULL;	}
	virtual	ResultInItemRoot	*CreateItemDim(int count)	override {	return NULL;	}
	virtual	ResultInItemRoot	*FindResultInItem(int layer ,int ItemID)	const	override;
	virtual	ResultInItemRoot	*FastSearchIDItem(int layer ,int ItemID)	const	override;

	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,NPListPack<TmpNGRectClass> &TmpRect,ErrorGroupPack &SpecializedGroup)	override;
	virtual	void	BuildNGImages(int ImageW ,int ImageH ,int Bevel ,TmpNGDim &TmpRectDim,ErrorGroupPack &SpecializedGroup)	override;

	virtual	bool	Initial(ResultBaseForAlgorithmRoot *parent)	override;
	virtual	void	Release(void)	override;
	virtual	bool	Reallocate(int newLayerNumb)	override;

	ResultInLayerPLI	&GetLayerData(int layer)	const	{		return(*LayerData.GetItem(layer));		}
    virtual	bool    Save(QIODevice *file)	override;
    virtual	bool    Load(QIODevice *file)	override;
	virtual	void	MoveMerge(ResultInPageRoot &dst)		override;
	virtual	ResultDLLBaseRoot	*GetResultDLLBase(void)		const	override;
	AlgorithmInPageRoot			*GetAlgorithmInPage(void)	const;
	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override;
	AlgorithmBase				*GetAlgorithmBase(void)				const	override;

	virtual	void	InitialInspection(void)	override;

	virtual	int		GetNGCount(void)		const	override;
	virtual	int		GetNGPointCount(void)	const	override;
	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)	override;
	virtual	void	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,char *ResList)		override;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,QIODevice *f,int &WrittenNGCount)			override;
	virtual	bool	OutputResult(int globalPage ,LogicDLL *LogicDLLPoint ,FileThread *f,int &WrittenNGCount)			override;
	virtual	void	OutputResult(FlexArea &Area ,int OffsetX ,int OffsetY
								,int globalPage ,LogicDLL *LogicDLLPoint ,QStringList &ResList)	override;
	virtual	ResultInspection	*GetResultInspection(void)	const	override;

	virtual	bool	GatherResult(bool3 &OK)	const	override;
	virtual	bool	GatherResult(NPListPack<ResultPosInfo> &RContainer,bool3 &OK)	const override;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)	override;
	virtual	void	GetNGItemList(NPListPack<ResultInItemRootPointerList> &Ret ,FlexArea &area)	override;
	virtual	void	GetItemListByErrorGroupID(NPListPack<ResultInItemRootPointerList> &Ret ,int ErrorGroupID)	override;
	virtual	void	BindNGAreaListContainer(NGAreaListContainer& List)	override;
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
};


class	ResultBaseForAlgorithmPLI : public ResultBaseForAlgorithmRoot
{
	friend	class	ResultInItemPLI;
	friend	class	ResultInLayerPLI;
	friend	class	ResultInPagePLI;
	int32				AllocPageNumb;
	ResultInPageRoot	**PageData;
public:

	explicit	ResultBaseForAlgorithmPLI(LogicDLL *parent);
	virtual	~ResultBaseForAlgorithmPLI(void);

	virtual	ResultInPageRoot	*CreatePage(int phase ,int page)			override;
	virtual	ResultBaseForAlgorithmRoot	*CreateResultBaseForAlgorithm(void)	override;
	virtual	bool	DrawResult(int32 ShowFixedPhase
						,QPainter &PntFromIData ,QImage *IData 
						,int MovX ,int MovY ,double ZoomRate,int localPage)	override;

	virtual	void	ExecuteInAllItems(void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)			override;
	virtual	void	ExecuteInAllItems(int phase,void (*Func)(ResultInItemRoot *Item ,void *Something),void *Something)	override;
};

inline	LayersBase			*ResultInItemPLI::GetLayersBase(void)	const
{
	return (Parent!=NULL)?Parent->GetLayersBase():NULL;
}

inline	XDateTime	&ResultInLayerPLI::GetStartInspectionTime(void)				{	return Parent->Parent->GetParent()->GetStartTimeForInspection();	}
inline	ResultInspection	*ResultInItemPLI::GetResultInspection(void)	const	{	return (Parent!=NULL)?Parent->GetResultInspection():NULL;	}
inline	ResultInspection	*ResultInLayerPLI::GetResultInspection(void)const	{	return (Parent!=NULL)?Parent->GetResultInspection():NULL;	}
inline	ResultInspection	*ResultInPagePLI::GetResultInspection(void)	const	{	return (Parent!=NULL)?Parent->GetResultInspection():NULL;	}

inline	int	ResultInItemPLI::GetPage(void)		const	{	return (Parent!=NULL)?Parent->GetPage():-1;			}
inline	int	ResultInItemPLI::GetPhaseCode(void)	const	{	return (Parent!=NULL)?Parent->GetPhaseCode():-1;	}
inline	int	ResultInItemPLI::GetLayer(void)		const	{	return (Parent!=NULL)?Parent->GetLayer():-1;		}
inline	int	ResultInLayerPLI::GetPage(void)		const	{	return (Parent!=NULL)?Parent->GetPage():-1;			}



//=========================================================================================

class	AlgorithmItemPLI : public NPList<AlgorithmItemPLI> ,public AlgorithmItemRoot
{
	friend	class   AlgorithmInLayerPLI;
protected:
	AlgorithmInLayerPLI	*Parent;

public:
	AlgorithmItemPLI(void);
	explicit	AlgorithmItemPLI(FlexArea &area);
	explicit	AlgorithmItemPLI(FlexArea *area);	//Use area memory
	virtual	~AlgorithmItemPLI(void){}

	virtual	void	SetItemID(void)	override;
	virtual	AlgorithmItemPLI	&operator=(const AlgorithmItemRoot &src)	override;

	virtual	XYData					GetOutlineOffset(void)		override;
	virtual	AlgorithmBase			*GetParentBase(void)		const	override;
	AlgorithmInPageInOnePhase		*GetAlgorithmInPageInOnePhase(void)	const	override;
	virtual	AlgorithmInPageRoot		*GetParentInPage(void)		const	override;
	virtual	AlgorithmInLayerRoot	*GetParentInLayer(void)		const	override;
	virtual	AlgorithmParentFromItem	*GetParentAlgorithm(void)	const	override;
	AlgorithmInLayerPLI	*GetParent(void){	return Parent;	}
	virtual	ResultInItemRoot	*GetCurrentResult(void)			override;
	virtual	ResultInItemRoot	*GetResult(ResultInPageRoot *Rp)override;

	virtual	void	CopyParentFrom(AlgorithmItemRoot *src,AlgorithmInPageRoot *P, int Layer)	override;
	virtual	void	CopyFrom(AlgorithmItemRoot *src)			override;
	
	virtual	void	SetParentVirtual(AlgorithmParentFromItem *parent)	override;
	virtual	void	SetParent(AlgorithmInLayerPLI *parent);
	ExeResult	ExecuteInitialAfterEdit	(int ExeID,int ThreadNo,ResultInItemRoot *Res ,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	bool	SetParentPointer(AlgorithmBase *InstBase ,int PhaseCode,int GlobalPage,int Layer)	override;

	ImageBuffer		&GetMasterBuff(void);
	ImageBuffer		&GetMasterBuff(int n);
	ImageBuffer		&GetBackGroundBuff(void);
	ImageBuffer		&GetBackGroundBuff(int n);
	ImageBuffer		&GetTargetBuff(void);
	ImageBuffer		&GetTargetTRBuff(void);
	ImageBuffer		&GetBitBuff(void);
	ImageBuffer		&GetTrialTargetBuff(void);

	ImageBuffer		&GetMasterBuffByLayerNo		(int LayerNo);
	ImageBuffer		&GetMasterBuffByLayerNo		(int LayerNo,int n);
	ImageBuffer		&GetBackGroundBuffByLayerNo		(int LayerNo);
	ImageBuffer		&GetBackGroundBuffByLayerNo		(int LayerNo,int n);
	ImageBuffer		&GetTargetBuffByLayerNo		(int LayerNo);
	ImageBuffer		&GetTargetTRBuffByLayerNo	(int LayerNo);
	ImageBuffer		&GetBitBuffByLayerNo		(int LayerNo);
	ImageBuffer		&GetTrialTargetBuffByLayerNo(int LayerNo);

	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	override;

	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,AlgorithmLibrary *LibData ,void *Anything=NULL)		;
	virtual	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,void *Anything=NULL)									;
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,AlgorithmLibrary *LibData ,void *Anything=NULL)override;
	virtual	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &Vector ,void *Anything=NULL)							override;
	virtual	bool	IncludeLibInReflection(ReflectionMode Mode ,AlgorithmLibrary *LibData ,void *Anything=NULL)						override;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	override	{	return true;	}
protected:
	virtual	AlgorithmThreshold	*GetThresholdDummy(void)	override;
};

template<class TLayer,class TPage,class TBase>
class	AlgorithmItemPLITemplate : public AlgorithmItemPLI
{
public:
	AlgorithmItemPLITemplate(void){}
	AlgorithmItemPLITemplate(FlexArea &area):AlgorithmItemPLI(area){}

	TBase	*tGetOrigin(void)		{	return (TBase *)(AlgorithmItemPLI::GetOrigin());	}
	TBase	*tGetParentBase(void)	{	return (TBase *)(AlgorithmItemPLI::GetParentBase());		}
	TPage	*tGetParentInPage(void)	{	return (TPage *)(AlgorithmItemPLI::GetParentInPage());		}
	TLayer	*tGetParentInLayer(void){	return (TLayer *)(AlgorithmItemPLI::GetParentInLayer());	}
};

class   AlgorithmInLayerPLI : public AlgorithmInLayerRoot
{
	friend	class   AlgorithmInPagePLI;
	friend	class	AlgorithmItemPLI;

	class	OMPAlgorithmItemStruct
	{
	public:
		int	ThreadNo;
		AlgorithmItemPLI	**CalcThread;
		ResultInItemPLI		**Result;
		int					CalcThreadCount;
		AlgorithmInLayerPLI	*Parent;

		OMPAlgorithmItemStruct(void);
		virtual	~OMPAlgorithmItemStruct(void);
		void	Alloc(AlgorithmInLayerPLI	*parent,int threadNo,int N);
		void	Set(int n,AlgorithmItemPLI	*c,ResultInItemPLI	*r);

		ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,ExecuteInitialAfterEditInfo &EInfo);
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

	int					DrawResultTableNumb;
	AlgorithmItemPLI	**DrawResultATable;
	ResultInItemPLI		**DrawResultRTable;
	QMutex				MutexTemporaryItem;

protected:
	NPListPack<AlgorithmItemPLI>	Data;
	NPListPack<AlgorithmItemPLI>	Dispatcher;
	NPListPack<ItemPointerList>		TemporaryItemList;
	NPListPack<AlgorithmItemPLI>	RentalData;
	AlgorithmInPagePLI				*Parent;
	AlgorithmThreshold	*ThresholdDummy;

public:
    explicit	AlgorithmInLayerPLI(AlgorithmInPageRoot *parent);
	virtual	~AlgorithmInLayerPLI(void);

	virtual	void		InitializeToStart(void)			override;
	virtual	void		InitialAfterParamLoaded(void)	override;
	virtual	bool		ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool		ReallocateMasterCount(int CountMaster)				override;

	virtual	bool		CopyShadowAlgorithmLayer(ShadowTree *Child ,const AlgorithmInLayerRoot &SrcParent)	override;
	virtual	bool		CopyShadowAlgorithmItem(ShadowTree *Child ,const AlgorithmItemRoot &ParentItem)	override	{	return true;	}

	virtual	bool		AppendItem(AlgorithmItemRoot *item)					override;
	virtual	bool		AppendItem(int Layer ,AlgorithmItemRoot *item)		override;
	virtual	bool		AppendItemFromLoad(AlgorithmItemRoot *item);
	virtual	bool		AppendItem(AlgorithmItemRoot *item ,int64 itemID);
	virtual	void		RemoveItem(AlgorithmItemRoot *item);
	virtual	bool		AppendItems(AlgorithmItemPointerListContainer &items)	override;
	virtual	bool		RemoveItems(AlgorithmItemPointerListContainer &items)	override;
	virtual	void		RemoveAllDatasByManual(bool CreatedManually)			override;
	virtual	void		RemoveAllDatasWithoutLocked(void)						override;
	virtual	void		RemoveAllDatasWithoutManual(void)						override;
	virtual	int64		GetMaxItemID(void)		const	override;

	virtual	AlgorithmItemPLI	*GetItem(int localX ,int localY);
	virtual	AlgorithmItemRoot	*GetItemRoot(int number)	override	{	return Data.GetItem(number);	}
	virtual	void				RemoveAllDatas(void)	override;
	virtual	AlgorithmItemPLI	*GetFirstData(void)		const		{	return(Data.GetFirst());	}
	virtual	int					GetItemCount(void)		override	{	return Data.GetNumber();	}
	virtual	int					GetTotalItemCount(void)		{	return Data.GetNumber()+RentalData.GetNumber();	}
	virtual	void				RemoveListData(AlgorithmItemPLI *item){	Data.RemoveList(item);	}
	virtual	void				LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)	override;

	virtual	AlgorithmItemRoot	*SearchIDItem(int itemID)	const	override;
	virtual	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName)	const	override;
	virtual	void	FastSearchIDItemStart(void)	override;
	void	IncrementNGCounterWithMutex(int result);
	int		GetNGCounter(void);
	virtual	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const	override;

    virtual	bool		Save(QIODevice *f)			override;
    virtual	bool		Load(QIODevice *f)			override;
	virtual	bool		LoadByTransform(QIODevice *f ,TransformBase &Param)	override;
	virtual	bool		LoadAppend(QIODevice *f)	override;
	virtual	bool		SaveHistgram(QIODevice *f)	override;
	virtual	bool		LoadHistgram(QIODevice *f)	override;
	virtual	void		ClearHistgram(void)			override;
	virtual	bool		SaveOnlyThreshold(QIODevice *f)	override;
	virtual	bool		LoadOnlyThreshold(QIODevice *f)	override;

	virtual	bool				GetDLLName(QString &DLLRoot ,QString &DLLName);
	virtual	AlgorithmBase		*GetParentBase(void)				const	override;
	AlgorithmInPageInOnePhase	*GetAlgorithmInPageInOnePhase(void)	const	override;
	virtual	AlgorithmInPageRoot	*GetParentInPage(void)				const	override;
	virtual	ResultInLayerRoot	*GetResultPointer(ResultInspection *Res)	override;

	virtual	int			GetSelectedItemCount(void)	override;
	virtual	void		GetItemIDListOnPoint(int localX,int localY,IntList &RetList);
	virtual	void		GetItemIDListOnPoint(FlexArea &CoveredArea,IntList &RetList);
	virtual	void		MoveItemsToDispatcherForLoadingParts(void)	override;
	virtual	void		CopyItemsFormDispatcherForParts(void)		override;
	virtual	void		RemoveItemFormDispatcher(void)				override;
	virtual	void		ClearResult(void)							override;

	virtual	void		DeliverTransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	XYData		*GetOutlineOffset(void)		const	override;
	ImageBuffer			&GetMasterBuff(void)		{	return GetDataInLayer()->GetMasterBuff();		}
	ImageBuffer			&GetMasterBuff(int n)		{	return GetDataInLayer()->GetMasterBuff(n);		}
	ImageBuffer			&GetBackGroundBuff(void)	{	return GetDataInLayer()->GetBackGroundBuff();		}
	ImageBuffer			&GetBackGroundBuff(int n)	{	return GetDataInLayer()->GetBackGroundBuff(n);		}
	ImageBuffer			&GetTargetBuff(void)		{	return GetDataInLayer()->GetTargetBuff();		}
	ImageBuffer			&GetTargetTRBuff(void)		{	return GetDataInLayer()->GetTargetTRBuff();		}
	ImageBuffer			&GetBitBuff(void)			{	return GetDataInLayer()->GetBitBuff();			}
	ImageBuffer			&GetTrialTargetBuff(void)	{	return GetDataInLayer()->GetTrialTargetBuff();	}

	AlgorithmInLayerRoot	*GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	override;

	virtual	void	Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	bool	DrawResult	  (ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;
	virtual	bool	DrawResultItem(ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)	override;
	virtual	void	DrawMonoBitmap(BYTE **BmpPoint)	override;
	virtual	void	DrawItems(QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)	override;
	virtual	void	DrawResultItem(ResultInLayerRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,DWORD DrawType)override;

	virtual	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteInitialAfterEdit		(int ExeID,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteInitialAfterEditPost	(int ExeID,ResultInLayerRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	override;
	virtual	ExeResult	ExecuteStartByInspection	(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteCaptured				(int ExeID,ResultInLayerRoot *Res,ListPhasePageLayerPack &CapturedList)	override;
	virtual	ExeResult	ExecutePreAlignment			(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteAlignment			(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreProcessing		(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessing			(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteProcessingRevived	(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePostProcessing		(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePreScanning			(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecuteScanning				(int ExeID,ResultInLayerRoot *Res)	override;
	virtual	ExeResult	ExecutePostScanning			(int ExeID,ResultInLayerRoot *Res)	override;

	virtual	void	MoveForAlignment(void)	override;
	void	RemoveInvalidItems(void);

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)	override;

	virtual	void	GetItemBitmap(BYTE** Dst, int XByte, int XLen, int YLen)	override;
	virtual	void	MakeIndependentItems(bool SubResultMoving, ResultInLayerRoot *RLayer ,int localX ,int localY,AlgorithmItemIndependentPack &Data)	override;
	virtual	void	MakeIndependentItems(IntList &Items,AlgorithmItemIndependentPack &Data) override;
	virtual	void	SetIndependentItemData(int32 Command
											,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	void	ReleaseAllSelectedItem(void)	override;
	virtual	void	SelectAll(void)					override;
	virtual	void	SelectLocked(void)				override;
	virtual	void	SelectItems(const IntList &ItemIDs);
	virtual	void	SelectLibs(AlgorithmLibraryListContainer &SelectedList)	override;
	virtual	void	SelectArea(FlexArea &localArea,bool MultiSelect)		override;
	virtual	void	SelectPoint(int localX, int localY)						override;
	virtual	void	SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode)	override;
	virtual	void	CutArea(FlexArea &localArea,bool MultiSelect,const QByteArray &Something=QByteArray())			override;
	virtual	void	SeparateItems(FlexArea &localArea)						override;
	virtual	void	RegistArea(FlexArea &localArea)							override;
	virtual	void	DeleteSelectedItems(void)								override;
	virtual	void	UndoDeleteSelectedItems(QIODevice *f)					override;
	virtual	void	LockSelectedItems(void)									override;
	virtual	void	UndoLockSelectedItems(QIODevice *f)						override;
	virtual	void	UnlockAll(void)											override;
	virtual	void	UndoUnlockAll(QIODevice *f)								override;
	virtual	void	BindSelectedItems(void)									override;
	virtual	void	UndoBindSelectedItems(QIODevice *f)						override;
	virtual	void	Activate(int localX ,int localY ,ListLayerAndIDPack &RetItem)	override;
	virtual	void	Activate(int ItemID)									override;
	virtual	void	AddActivate(int ItemID)									override;
	virtual	void	Inactivate(void)										override;
	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack)					override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)	override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,IntList &Items ,bool AllItems=false)	override;
	virtual	void	UndoExecuteMove(QIODevice *f)							override;
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)		override;
	virtual	bool	ExecutePasteFromSelected(int Dx,int Dy)					override;

	virtual	void	CopyFrom(AlgorithmInPageRoot *DestParent
							,AlgorithmInLayerRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)						override;
	virtual	void	InitializeFromParts(void)								override;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)			override;
	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList)	override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase)		override;

	virtual	void	VisibleAll(void)			override;
	virtual	void	InvisibleAll(void)			override;
	virtual	void	InvisibleSelected(void)		override;
	virtual	void	SelectManualCreature(void)	override;
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)		override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)	override;
	virtual	void	EnumLibID(IntList &LibIDList)					override;
	void	MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer);
	virtual	bool	GetSelectedCenter(int &Cx ,int &Cy)				override;
	virtual	bool	GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)		override;
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	override;
	virtual	bool	GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)	override;

	virtual	bool	IsEdited(void)				override;
	virtual	bool	IsCalcDone(void)			override;
	virtual	void	SetEdited(bool edited)		override;
	virtual	void	SetCalcDone(bool calcdone)	override;

	virtual	void	ResetProcessDone(void)		override;
	virtual	bool	IsProcessDone(void)			override;
	virtual	void	SetProcessDone(bool b=true)	override;

	virtual	void	ClearTemporaryItems(void)						override;
	virtual	void	SetTemporaryItems(ItemPointerListInLayer *Pg)	override;
	virtual	void	AddItemsForMove(ItemPointerListInLayer *Pg)		override;
	virtual	void	GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)	override;
	virtual	void	EnumItemsByLib(IntList &LibIDs ,AlgorithmItemPointerListContainer &ItemPointers)	override;
	virtual	void	EnumAllItems(AlgorithmItemPointerListContainer &ItemPointers)						override;
	virtual	void	GetSelectedItems(AlgorithmItemPointerListContainer &ItemPointers)					override;
	virtual	void	EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)			override;
	virtual	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))			override;
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)									override;
	virtual	void	SwitchThresholdLevel(int OldLevel ,int NewLevel)									override;
	virtual	void	CopyThresholdLevel	(int SourceLevelID ,int DestLevelID)							override;

	virtual	void	RemoveItems(IntList &IDList);
	virtual	void	EnumSelectedItems(ListPageLayerIDPack &Items)	override;

	virtual	void	SelectedItemListsForPaste(ExpandedSelectedItemListContainer &Lists)	override;
	virtual	void	DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int ItemID,double ZoomRate ,int movx ,int movy,int turn)	override;
	virtual	void	ExecuteTransformSelectedItems(TransformBase &M)			override;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	override;
	virtual	bool	SaveItemsForLearning(ItemDataListWithIDContainer &Buff 
											,FlexArea &LocalArea
											,AlgorithmLibraryListContainer &LibList
											,int AddedX,int AddedY,bool OkMode)	override;
	virtual	bool	LoadItemsForLearning(ItemDataListWithIDContainer &Buff ,int AddedX ,int AddedY)									override;
	virtual	bool	GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items);
	virtual	HistgramByParamBase	*GetHistgramBase(int ItemID,int HistID)			override;
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)			override;
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected)	override;
	virtual	bool	ShrinkItems(int ExpandPixels,bool MaskForSameLib)			override;

	virtual	void	EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)				override;
	virtual	void	EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)	override;

	void	UndoExecutePaste(QIODevice *f);
	virtual	void	UndoAddItemsForMove(QIODevice *f)	override;

	void	ClearRentalItem(void);
	void	ReqRentalItem(QByteArray &Something);
	virtual	void	AckRentalItem(int ForOtherGlobalPage ,QByteArray &Something , NPListPack<AlgorithmItemPLI> &_RentalData){}
	virtual	void	AddRentalItem(int ItemID ,AlgorithmItemPLI *p);
	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData)	override;
	virtual void	MakeBindedThreshold(BindedThresholdContainer &Container)override;

	virtual	void	GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items) override;
	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)	override;

	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList)	override;
	virtual	void	MasterImageHasChanged(void)	override;
protected:
	void	InitialThreadBufferForExecute(void);
	void	SendRentalItem(int ForOtherGlobalPage ,NPListPack<AlgorithmItemPLI> &_RentalData);
};

template<class TItem,class TPage,class TBase>
class	AlgorithmInLayerPLITemplate : public AlgorithmInLayerPLI
{
public:
	explicit	AlgorithmInLayerPLITemplate(AlgorithmInPageRoot *parent):AlgorithmInLayerPLI(parent){}

	TItem	*tGetItem(int localX ,int localY)	{	return (TItem *)GetItem(localX ,localY);	}
	//TItem	*tGetItem(int number)				{	return (TItem *)GetItem(number);			}
	//Error by Linux

	TItem	*tGetFirstData(void)				{	return (TItem *)GetFirstData();				}
	TItem	*tGetNextData(TItem	*item)			{	return (TItem *)(item->GetNext());			}

	TItem	*tSearchIDItem(int itemID)			{	return (TItem *)SearchIDItem(itemID);		}

	TBase	*tGetParentBase(void)				{	return (TBase *)GetParentBase();			}
	TPage	*tGetParentInPage(void)				{	return (TPage *)GetParentInPage();			}
	TItem	*tNewChild(int ItemClassType)
		{	
			TItem *	Item=(TItem *)CreateItem(ItemClassType);
			Item->SetParent(this);
			return Item;
		}
};

class   AlgorithmInPagePLI : public AlgorithmInPageRoot
{
	friend	class	AlgorithmItemPLI;
	friend	class   AlgorithmInLayerPLI;
	friend	class	AlgorithmBase;
protected:
	AlgorithmInLayerPLI	**LayerData;
	int32				AllocatedLayerNumb;
	AlgorithmBase		*Parent;
	SlaveCommReqRentalItems	*SlaveCommReqRentalItemsInst;
	SlaveCommAckRentalItems	*SlaveCommAckRentalItemsInst;

	void	ReleaseData(void);

public:
	explicit	AlgorithmInPagePLI(AlgorithmBase *parent);
	virtual	~AlgorithmInPagePLI(void);

	virtual	ModelType	GetModel(void)	override	{	return	Model_PLI;	}

	virtual	void		Initial(AlgorithmInPageInOnePhase *phaseParent,LayersBase *Base)	override;
	virtual	void		InitializeToStart(void)					override;
	virtual	void		InitialAfterParamLoaded(void)			override;
	virtual	void		Release(void)							override;
	virtual	bool		ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)	override;
	virtual	bool		Reallocate(int newLayerNumb)			override;
	virtual	bool		ReallocateMasterCount(int CountMaster)	override;
	virtual	bool		CopyShadowAlgorithmPage(ShadowTree *Child ,const AlgorithmInPageRoot &SrcParent)	override;
	virtual	bool		CopyShadowAlgorithmItem(ShadowTree *Child , const AlgorithmItemRoot &ParentItem)	override	{	return false;	}

	virtual	AlgorithmItemRoot	*SearchIDItem(int itemID)	const	override {	return NULL;	}
	virtual	void	FastSearchIDItemStart(void)						override;
	virtual	AlgorithmItemRoot	*CreateItem(int ItemClassType)		override;
	virtual	bool				AppendItem(AlgorithmItemRoot *item)				override	{	return true;	}
	virtual	bool				AppendItem(int Layer ,AlgorithmItemRoot *item)	override;
	virtual	bool		AppendItems(AlgorithmItemPointerListContainer &items)	override	{	return false;	}
	virtual	void		RemoveAllDatasByManual(bool CreatedManually)			override;
	virtual	void		RemoveAllDatasWithoutLocked(void)						override;
	virtual	void		RemoveAllDatasWithoutManual(void)						override;
	virtual	bool		RemoveItems(AlgorithmItemPointerListContainer &items)	override	{	return false;	}
	virtual	int64		GetMaxItemID(void)		const	override;

	AlgorithmInLayerRoot *GetLayerData(int layer)		const	override	{	return (layer<AllocatedLayerNumb)?LayerData[layer]:NULL;	}
	AlgorithmInLayerPLI *GetLayerDataPLI(int layer)		const				{	return (AlgorithmInLayerPLI *)GetLayerData(layer);	}
	AlgorithmBase		*GetParentBase(void)	const			override	{	return Parent;	}
	DataInPage			*GetDataInPage(void)	const			override	{	return AlgorithmInPageRoot::GetDataInPage();	}
	AlgorithmInPageRoot	*GetAlgorithm(const QString &_DLLRoot ,const QString &_DLLName)	const	override;
	virtual	AlgorithmItemRoot	*GetItemData(int layer ,int itemID)				const	override;
	virtual	AlgorithmItemRoot	*FindFastItemData(int layer ,int itemID)		const	override;
	virtual	AlgorithmItemRoot	*GetItemRoot(int n)								const	override	{	return NULL;	}
	virtual	AlgorithmItemRoot	*SearchItemByName(const QString &ItemName)		const	override;
	virtual	int			GetSelectedItemCount(void)										override;
	virtual	int			GetItemCount(void)												override;
	virtual	void		LoopforAllItems(void (*ItemFunc)(AlgorithmItemRoot *Item ,void *_Something),void *Something)	override;
	virtual	AlgorithmItemRoot	*FindItem(const AlgorithmItemIndex &Index)	const	override;

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
	virtual	AlgorithmItemRoot		*CreateItem(int layer, int ItemClassType)	{		return GetLayerData(layer)->CreateItem(ItemClassType);		}
	virtual	void	MoveItemsToDispatcherForLoadingParts(void)	override;
	virtual	void	CopyItemsFormDispatcherForParts(void)		override;
	virtual	void	RemoveItemFormDispatcher(void)				override;
	virtual	void	ClearResult(void)							override;

	virtual	void	Draw(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)	override;
	virtual	void	DrawMove(int dx ,int dy,QImage &pnt, int movx ,int movy ,double ZoomRate ,const QColor &Col,AlgorithmDrawAttr *Attr)	override;
	virtual	bool	DrawResult	  (ResultInPageRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate)	override;
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

	virtual	void	RefreshByMap(ReflectionMode Mode,ConstMapBufferListContainer &Map)				override;
	virtual	void	RefreshByMap(int layer,ReflectionMode Mode,ConstMapBufferListContainer &Map)	override;

	virtual	bool	GeneralDataRelease(int32 Command,void *data)			override;
	virtual	void	*GeneralDataCreate(int32 Command,void *reqData)			override;
	virtual	bool	GeneralDataLoad(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataSave(QIODevice *f,int32 Command,void *data)	override;
	virtual	bool	GeneralDataReply(int32 Command,void *data)				override;

	virtual	void	SelectItems(FlexArea &Area ,const IntList &LayerList,bool MultiSelect)	override;
	virtual	void	ReleaseAllSelectedItem(void)											override;
	virtual	void	RemoveAllDatas(void)													override;
	virtual	void	SelectAll(const IntList &LayerList)										override;
	virtual	void	SelectLocked(const IntList &LayerList)									override;
	virtual	void	SelectLibs(SelectLibListContainer &SelectedList)						override;
	virtual	void	SelectItemsByOriginType(struct	OriginTypeSelection &SelectMode	,const IntList &LayerList)	override;
	virtual	void	CutArea(FlexArea &area ,const IntList &LayerList,bool MultiSelect,const QByteArray &Something=QByteArray())		override;
	virtual	void	SeparateItems(FlexArea &area ,const IntList &LayerList)					override;
	virtual	void	RegistArea(FlexArea &area ,const IntList &LayerList)					override;
	virtual	void	DeleteSelectedItems(const IntList &LayerList)		override;
	virtual	void	UndoDeleteSelectedItems(QIODevice *f)				override {}		;
	virtual	void	LockSelectedItems(const IntList &LayerList)			override;
	virtual	void	UndoLockSelectedItems(QIODevice *f)					override {}		;
	virtual	void	UnlockAll(const IntList &LayerList)					override;
	virtual	void	UndoUnlockAll(QIODevice *f)							override {}		;
	virtual	void	BindSelectedItems(const IntList &LayerList)			override;
	virtual	void	UndoBindSelectedItems(QIODevice *f)					override {}		;
	virtual	void	Activate(int PosX,int PosY ,IntList &LayerList ,ListLayerAndIDPack &RetItem)	override;
	virtual	void	Activate(int Layer ,int ItemID)						override;
	virtual	void	AddActivate(int Layer ,int ItemID)					override;
	virtual	void	Inactivate(void)									override;
	virtual	void	GetLayerAndItemID(int LocalX ,int LocalY ,ListLayerIDLibNamePack &ItemList ,const IntList &LayerList)	override;
	virtual	void	GetLayerAndItemID(FlexArea &CoveredArea ,ListLayerAndIDPack &ItemList ,const IntList &LayerList)		override;
	virtual	void	GetItems(ListLayerAndIDPack &ItemList ,AlgorithmItemPointerListContainer &Items)						override;
	virtual	void	EnumOriginTypeItems(OriginType b ,AlgorithmItemPointerListContainer &Items)			override;
	virtual	void	EnumOriginTypeItems(int layer ,OriginType b ,AlgorithmItemPointerListContainer &Items)	override;
	virtual	void	EnumItems(void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	EnumItems(int layer ,void *caller,AlgorithmItemPointerListContainer &Items , bool (*func)(void *caller,AlgorithmItemRoot *item))override;
	virtual	void	ScanItems(void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))				override;
	virtual	void	ScanItems(int layer ,void *caller,void (*func)(void *caller,AlgorithmItemRoot *item))	override;
	virtual	void	EnumItems(ListPhasePageLayerLibIDPack &ItemIDList)										override;
	virtual	void	EnumItems(int layer,ListPhasePageLayerLibIDPack &ItemIDList)	override;

	virtual	void	SelectItemByID(ListLayerAndIDPack &SelectedItem)				override;
	virtual	void	GetAllItems(AlgorithmItemPointerListContainer &ItemPointers)	override;
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

	virtual	void	VisibleAll(const IntList &LayerList)			override;
	virtual	void	InvisibleAll(const IntList &LayerList)			override;
	virtual	void	InvisibleSelected(const IntList &LayerList)		override;
	virtual	void	SelectManualCreature(const IntList &LayerList)	override;

	virtual	void	ExecuteCopy(ClipboardAlgorithm &Pack,const IntList &LayerList)							override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,bool AllItems=false)								override;
	virtual	void	ExecuteMove(int GlobalDx,int GlobalDy,ListPageLayerIDPack &Items ,bool AllItems=false)	override;
	virtual	void	UndoExecuteMove(QIODevice *f)															override {}
	virtual	void	GetPageListForExecuteMove(IntList &PageList ,int GlobalDx,int GlobalDy)					override;
	virtual	bool	ExecutePasteCreateWithShape(int32 PastedLayer,ClipboardAlgorithmItem *item ,QIODevice &Buff,int globalDx, int globalDy 
								,FlexArea &area ,AlgorithmBase *OriginBase
								,int ItemClass)																override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,FlexArea &area,bool SelectModeAfterPaste=false)			override;
	virtual	bool	ExecutePaste(int32 PastedLayer,ClipboardAlgorithmItem *item ,int globalDx, int globalDy,VectorLineBase *Vector,bool SelectModeAfterPaste=false)	override;
	virtual	bool	ExecutePasteFromSelected(IntList &PastedLayer,int Dx,int Dy)							override;

	virtual	void	GenerateAlgorithmItemCount(AlgorithmItemCountInPage &Ret)								override;
	virtual	void	CopyFrom(AlgorithmBase *DestParent
							,AlgorithmInPageRoot *src 
							,int OffsetX,int OffsetY
							,int PartsMaster ,int PartsID
							,bool ReferedThresholdMode)														override;
	virtual	void	InitializeFromParts(void)																override;
	virtual	void	CopyItems(FlexArea &SrcArea ,int mx ,int my)											override;
	virtual	void	GetOriginRootNames(NPListPack<OriginNames> &OriginNameList ,const IntList &LayerList)	override;
	virtual	void	SelectOriginRootNames(AlgorithmBase *OriginBase ,const IntList &LayerList)				override;
	virtual	void	RotateItem(int AngleDegree ,int Cx, int Cy)												override;
	virtual	void	MirrorItem(AlgorithmItemRoot::_MirrorMode MirrorMode ,int PointX ,int PointY)			override;
	virtual	void	EnumLibID(IntList &LibIDList)															override;
	virtual	void	MakeItemList(int LibID,AlgorithmItemPointerListContainer &RetContainer)					override;
	virtual	bool	GetSelectedCenter(DotListContainer &CenterByLayer)										override;
	virtual	bool	GetSelectedXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)										override;
	virtual	void	GetOutsideItems(int dx,int dy,NPListPack<ItemPointerListInPage> &OutsideItems,int MaxGlobalPage)	override;
	virtual	bool	GetOccupiedItemXY(int &X1 ,int &Y1 ,int &X2 ,int &Y2)									override;

	virtual	bool	IsEdited(void)				override;
	virtual	bool	IsCalcDone(void)			override;
	virtual	void	SetEdited(bool edited)		override;
	virtual	void	SetCalcDone(bool calcdone)	override;

	virtual	void	ResetProcessDone(void)		override;
	virtual	bool	IsProcessDone(void)			override;
	virtual	void	SetProcessDone(bool b=true)	override;

	virtual	void	ClearTemporaryItems(void)					override;
	virtual	void	SetTemporaryItems(ItemPointerListInPage *Pg)override;
	virtual	void	AddItemsForMove(ItemPointerListInPage *Pg)	override;

	virtual	void	SelectedItemListsForPaste(IntList &LayerList ,ExpandedSelectedItemListContainer &Lists)	override;
	virtual	void	DrawItemListsForPaste(int dx, int dy ,QImage &Pnt,int Layer,int ItemID,double ZoomRate ,int movx ,int movy,int turn)	override;
	virtual	void	ExecuteTransformSelectedItems(TransformBase &M)		override;

	virtual	bool	SaveCSVMasterReport(QStringListListCSV &CSVData)	override;
	virtual	bool	SaveItemsForLearning(ItemDataListWithIDContainer &Buff 
											,FlexArea &LocalArea
											,AlgorithmLibraryListContainer &LibList
											,int AddedX,int AddedY,bool OkMode)	override;
	virtual	bool	LoadItemsForLearning(ItemDataListWithIDContainer &Buff ,int AddedX ,int AddedY)	override;
	virtual	bool	GetPointedItems(int LocalX ,int LocalY ,NPListPack<ItemPointerList> &Items)		override;
	virtual	HistgramByParamBase	*GetHistgramBase(int Layer,int ItemID,int HistID)				override;
	virtual	void	MakeUncoveredMap(BYTE **BMap, int XByte ,int YLen)							override;
	virtual	void	SetItemName(const QString &ItemName , bool OnlySelected)					override;
	virtual	bool	ShrinkItems(const IntList &LayerList,int ExpandPixels,bool MaskForSameLib)	override;

	virtual	void	EnumItemHistgram(int HistID ,AlgorithmItemPointerListContainer &RetContainer)			override;
	virtual	void	EnumItemHistgram(int HistID ,int LibID ,AlgorithmItemPointerListContainer &RetContainer)override;

	virtual	ResultInItemRoot	*CreateResult(void)		override	{	return new ResultInItemPLI();	}
	virtual	bool	ManualExecuteAll(ManualExecuter &ManualExecuterData)	override;
	virtual void	MakeBindedThreshold(BindedThresholdContainer &Container)override;

	virtual	bool	ExecuteAutoThreshold(ParamAutoThreshold &executer)	override;
	virtual	void	GenerateItemListForAutoThreshold(AlgorithmItemPointerListContainerByLibContainer &Items) override;
	virtual	void	UpdateThreshold(int LearningMenuID,int LibID,int ItemID,LearningResource &LRes)	override;

	virtual	bool	MakeConfirmItem(ConfirmItemListContainer &ItemList)	override;
	virtual	void	MasterImageHasChanged(void)	override;
};

inline	AlgorithmItemRoot	*AlgorithmInPagePLI::CreateItem(int ItemClassType)	
{	
	if(GetLayerData(0)!=NULL){
		return GetLayerData(0)->CreateItem(ItemClassType);
	}
	return NULL;	
}


template<class TItem,class TLayer,class TBase>
class	AlgorithmInPagePLITemplate : public AlgorithmInPagePLI
{
public:
	explicit	AlgorithmInPagePLITemplate(AlgorithmBase *parent):AlgorithmInPagePLI(parent){}

	TLayer	*tGetLayerData(int layer)	{	return (TLayer *)GetLayerData(layer);	}
	TBase	*tGetParentBase(void)		{	return (TBase *)GetParentBase();		}
	TItem	*tGetItemData(int layer ,int itemID)		{	return (TItem *)GetItemData(layer ,itemID);	}
	TItem	*tCreateItem(int layer, int ItemClassType)	{	return (TItem *)CreateItem(layer, ItemClassType);	}

};

//=========================================================================================
inline	bool	AlgorithmInLayerPLI::GetDLLName(QString &DLLRoot ,QString &DLLName)
{
	return GetParentBase()->GetDLLName(DLLRoot ,DLLName);
}

inline	AlgorithmThreshold	*AlgorithmItemPLI::GetThresholdDummy(void)
{
	if(GetParent()==NULL)
		return NULL;
	if(GetParent()->ThresholdDummy==NULL){
		GetParent()->ThresholdDummy=CreateThresholdInstance();
	}
	return GetParent()->ThresholdDummy;
}


#endif
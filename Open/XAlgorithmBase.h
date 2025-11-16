/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmBase.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XALGORITHMBASEH
#define XALGORITHMBASEH

#include <QtGui>
#include <QObject>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XResult.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XCSV.h"
#include "XMapBuffer.h"
#include "XMacroFunction.h"
#include "XAlgorithmCommon.h"

class	AlgorithmItemRoot;
class	AlgorithmBase;
class	ExcludedListPack;
class	AlgorithmLibraryContainer;
class	AlgorithmDLLContainer;
class	AlignmentPacketBase;
class	AlgorithmItemIndependentPack;
class	ClipboardAlgorithm;
class	ShowAndSetItemsBaseClass;
class	RootNameListContainer;
class	AlgorithmDefList;
class	QSqlDatabase;
class	AlgorithmLibrary;
class	VectorLineBase;
class	LibNGTypeInAlgorithm;
class	ErrorCodeList;
class	LotInformation;
class	LotBase;
class	LanguagePackage;
class	AlgorithmDLLList;
class	ExecuteInitialAfterEditInfo;
class	AlgorithmLibraryListContainer;
class	AlgorithmDLLList;
//========================================================================

class	LogicDLL	: public QObject 
					 ,public NPList<LogicDLL>,public ServiceForLayers ,public DLLMacroFunc
{
	Q_OBJECT

	friend	class	AlgorithmBase;
	friend	class	AlgorithmDLLList;

	AlgorithmDLLList	*DLLPointer;
	AlgorithmBase	*InstBase;
	AlgorithmLibraryContainer	*LibContainer;

	QWidget		*ShowAndSetItemsForm;
	QWidget		*ChangeItemsAttrForm;

	QString			Organization;
	WORD			DLLType;
	WORD			Ver;

	int32			DynamicID;			
	QString			BlobName;
	DWORD			AlgorithmType;
	QString			Copyright;
	bool			EnabledExpandable;	//部品として使用されるときの展開を行うかどうか

	int				PriorityInitialAfterEdit;
	int				PriorityAutoGeneration;
	int				PriorityStartByInspection;
	int				PriorityCaptured;
	int				PriorityPreAlignment;
	int				PriorityAlignment;
	int				PriorityPreProcessing;
	int				PriorityProcessing;
	int				PriorityProcessingRevived;
	int				PriorityPostProcessing;
	int				PriorityPreScanning;
	int				PriorityScanning;
	int				PriorityPostScanning;
	int				PriorityManageResult;

public:

	LogicDLL(LayersBase *Base);
	~LogicDLL(void);

	void		Set(AlgorithmDLLList *s);
	LogicDLL	&operator=(LogicDLL &src);
	bool		IsAlgorithm(void);
	bool		IsAlignment(void);
	bool		SetLanguageCode(int LanguageCode);
	void		InitialName(void);
	bool		InitialAlloc(LayersBase *Base);
	void		InitialAfterParamLoaded(void);
	AlgorithmBase	*AllocOnly(LayersBase *Base);
	void		ReallocAlgorithmBase(LayersBase *Base);
	bool		InitialLibrary(LayersBase *Base);
	bool		ReallocXYPixels(int NewDotPerLine ,int NewMaxLines);

	bool		CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db);
	int			GetPriority(int PriorityTypeBit_Type)	const;
	void		ChangeAlgorithmType(DWORD algorithmtype);
	void		AssociateComponent	(ComponentListContainer &List);

	QString		GetFileName(void)		const;
	QString		GetDLLRoot(void)		const;
	QString		GetDLLName(void)		const;
	QString		GetExplain(void);
	WORD		GetDLLType(void)		{	return DLLType;		}
	int32		GetDynamicID(void)		{	return DynamicID;	}
	bool		CheckAlgorithmType(int algotype)	{	return (AlgorithmType & algotype)!=0?true:false;	}
	DWORD		MaskAlgorithmType(DWORD algotype)	{	return AlgorithmType & algotype;	}
	DWORD		GetAlgorithmType(void)	const	{	return AlgorithmType;	}
	QString		GetOrganization(void)	const	{	return Organization;	}
	WORD		GetVer(void)			const	{	return Ver;		}
	void		SetDynamicID(int32 id)			{	DynamicID=id;	}
	QString		GetBlobName(void)		const	{	return BlobName;	}
	bool		GetEnabledExpandable(void)	const{	return EnabledExpandable;	}
	void		SetEnabledExpandable(bool b)	{	EnabledExpandable=b;	}
	bool		IsMaskAlgorithm(void);
	bool		IsProcessAlgorithm(void);
	bool		CheckDLL(const QString &root, const QString &name);

	AlignmentPacketBase	*GetAlignmentPointer(int localPage, int localX ,int localY ,AlgorithmItemRoot *Item ,bool FromGlobal=true);
	void		GetAlignmentForProcessing		 (int localPage, AlignmentPacketBase &Packet);

	AlgorithmLibraryContainer	*GetLibContainer(void){	return LibContainer;	}

	bool	ExecuteMoveItemsToDispatcherForLoadingParts(void);
	bool	ExecuteCopyItemsFormDispatcherForParts(void);
	bool	ExecuteRemoveItemFormDispatcher(void);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultBaseForAlgorithmRoot *pResult ,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultBaseForAlgorithmRoot *pResult ,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultBaseForAlgorithmRoot *pResult ,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteCaptured				(int ExeID ,ResultBaseForAlgorithmRoot *pResult,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment			(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteAlignment			(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecutePreProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteProcessing			(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecutePostProcessing		(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecutePreScanning			(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteScanning				(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecutePostScanning			(int ExeID ,ResultBaseForAlgorithmRoot *pResult);
	ExeResult	ExecuteManageResult			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteMatch				(int ExeID ,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result);

	bool	DrawResultBase(int32 ShowFixedPhase,ResultBaseForAlgorithmRoot *Res ,QPainter &PntFromIData ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage);
	void	ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something);
	void	MakeIndependentItems(int32 TargetPhase,int32 localPage,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	SetIndependentItemData(int32 Command
									,int32 TargetPhase,int32 LocalPage,int32 Layer ,int32 ItemID
									,AlgorithmItemRoot *Data
									,IntList &EdittedMemberID
									,QByteArray &Something
									,QByteArray &AckData);
	bool	DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList);
	bool	ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff);
	bool	BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest);

	QWidget	*GetShowAndSetItemsForm(void)	const	{	return 	ShowAndSetItemsForm;	}
	QWidget	*GetChangeItemsAttrForm(void)	const	{	return 	ChangeItemsAttrForm;	}
	bool	IsAvailableGetShowAndSetItemsForm(void)	const;
	bool	IsAvailableGetChangeItemsAttrForm(void)	const;

	void	ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	SaveItem(QIODevice *f,AlgorithmItemRoot *item);
	bool	LoadItem(QIODevice *f,AlgorithmItemRoot *item);
	AlgorithmItemRoot *CreateItem(AlgorithmBase *InstBase ,int ItemClassType);
	ResultBaseForAlgorithmRoot	*CreateResultBaseForAlgorithm(ResultInspection *ResultInspectionPointer);

	AddedDataClass	*LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
	bool			SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
	void			RemoveAddedResultData(AddedDataClass *d);
	AlgorithmBase	*GetInstance(void){		return InstBase;	}

	bool	ReleaseGeneralAlgorithmData(int32 Command,void *data);
	void	*CreateGeneralAlgorithmData(int32 Command,void *reqData);
	bool	LoadGeneralAlgorithmData(QIODevice *f,int32 Command ,void *data);
	bool	SaveGeneralAlgorithmData(QIODevice *f,int32 Command ,void *data);
	bool	ReplyGeneralAlgorithmData(int32 Command ,void *data);
	bool	GetNGTypeContainer(int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer);

	ClipboardAlgorithm	*ExecuteCopy(int localPage ,const XDateTime &createdTime,IntList &LayerList);

	bool	IsEdited(void);
	bool	IsCalcDone(void);
	void	SetEdited(bool edited);
	void	SetCalcDone(bool calcdone);

	bool	LocalPos2Name(int LocalPage ,int XLocalPos, int YLocalPos ,QString &Name);

	bool	SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData);
	void	MakeUncoveredMap(int Page ,BYTE **BMap, int XByte ,int YLen);
	bool	ReceivePacketDirectComm(int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);

	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	bool	GetReflectionMap(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase ,int page, int layer ,void *Anything=NULL);		
	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &MapVector ,int phase ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	bool	GetReflectionVector(ReflectionMode Mode ,VectorLineBase &MapVector ,int phase ,int page, int layer ,void *Anything=NULL);
	bool	IncludeLibInReflection(ReflectionMode Mode ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);
	bool	GetUsageLibInReflection(ReflectionMode Mode ,int page, int layer,AlgorithmLibraryListContainer &Ret);	

	virtual	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)	override;

private:
	QString		GetDefaultFileName(void);
public slots:
	void	SlotShowAndSetItemsFormClosed();
};


class	LogicDLLBaseClass : public NPListPack<LogicDLL>,public ServiceForLayers
{
public:
	LogicDLLBaseClass(LayersBase *base);
	~LogicDLLBaseClass(void);

	LogicDLLBaseClass	&operator=(const LogicDLLBaseClass &src);
	void	CopyFrom(LayersBase *ToBase,const LogicDLLBaseClass &src);
	int		AddDLLs(const AlgorithmDLLContainer &AlgoCont ,LayersBase *Base);
	bool	LoadOneDLL(LayersBase *Base ,const QString &DLLFileNameWithPath);
	void	AssociateComponent	(ComponentListContainer &List);

	bool	CheckDuplicatedAlgorithm(QStringList &Error);
	bool	CheckInstalledAlgorithm(RootNameListContainer &FromGUI ,RootNameListContainer &LackOfAlgorithm);
	void    InitialAfterParamLoaded(void);

	LogicDLL	*Search(int dynamicID);
	LogicDLL	*Search(const QString &_DLLRoot ,const QString &_DLLName);
	LogicDLL	*SearchByAlgorithmType(int algoType);
	LogicDLL	*NextByAlgorithmType(LogicDLL *Before,int algoType);
	LogicDLL	*SearchByLibType(int LibType);

	int			GetDLLCounts(void);
	bool		SetLanguageCode(int LanguageCode);

	bool	CheckAndCreateBlobInMasterPageTable(const QSqlDatabase &db);
	int		MakeFieldList(ExcludedListPack &List);
	bool	InitialLibrary(LayersBase *Base);
	bool	LocalPos2Name(int LocalPage ,int XLocalPos, int YLocalPos ,QString &Name);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteStartByInspection	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreAlignment			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteCaptured				(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecuteAlignment			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessing		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessing			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevived	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessing		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreScanning			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteScanning				(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostScanning			(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteManageResult			(int ExeID ,ResultInspection *Res);

	ExeResult	ExecuteRemoveResult(int32 MasterCode , LotBase *Lot , int64 InspectionID ,ResultInspection *Ref);

	bool	GetReflectionMap	(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	bool	GetReflectionMap	(ReflectionMode Mode ,ConstMapBuffer &Map ,int phase,int page, int layer ,void *Anything=NULL);		
	bool	GetReflectionVector	(ReflectionMode Mode ,VectorLineBase &Vector ,int phase,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);	
	bool	GetReflectionVector	(ReflectionMode Mode ,VectorLineBase &Vector ,int phase,int page, int layer ,void *Anything=NULL);
	bool	IncludeLibInReflection(ReflectionMode Mode ,int page, int layer ,AlgorithmLibrary *LibData ,void *Anything=NULL);
	bool	GetUsageLibInReflection(ReflectionMode Mode ,int page, int layer,AlgorithmLibraryListContainer &Ret);	

	void	ExecuteMove(int localPage ,int GlobalDx,int GlobalDy,bool AllItems=false);

	void	ClearResultInPhase(int phase);
};

#endif
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XAlgorithmInterfaceDLL.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef XALGORITHMINTERFACEDLLH
#define XALGORITHMINTERFACEDLLH

#include <QtGui>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XResult.h"
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XCSV.h"
#include "XMapBuffer.h"
#include "XDLLManager.h"
#include "XMacroFunction.h"

class	EntryPointBase;

class	AlgorithmItemRoot;
class	AlgorithmBase;
class	ExcludedListPack;
class	AlgorithmLibraryContainer;
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
class	ExecuteInitialAfterEditInfo;
class	LogicDLL;

class	AlgorithmDLLList : public NPList<AlgorithmDLLList>,public DLLManager,public ServiceForLayers
{
	friend	class	LogicDLL;

	const AlgorithmDLLList	*Parent;		
	QString			FileName;
	QLibrary 		DllLib;

	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	bool			(*DLL_GetName)(QString &Root ,QString &Name);
	WORD			(*DLL_GetVersion)(void);
	const char		*(*DLL_GetExplain)(void);
	void			(*DLL_SetLanguage)		(LanguagePackage &Pkg ,int LanguageCode);
	void			(*DLL_SetLanguageCommon)(LanguagePackage &Pkg ,int LanguageCode);
	bool			(*DLL_CheckCopyright)(QString &CopyrightString);
	const char		*(*DLL_GetBlobName)(void);
	DWORD			(*DLL_GetAlgorithmType)(void);
	AlgorithmBase	*(*DLL_InitialAlloc)(LayersBase *Base);
	void			(*DLL_Close)(void);
	void			(*DLL_ReleaseAlgorithmBase)(AlgorithmBase *Point);
	void			(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);

	AlgorithmLibraryContainer	*(*DLL_NewLibrary)(LayersBase *Base);
	int				(*DLL_GetPriority)(int PriorityTypeBit_Type);

	bool	(*DLL_ExecuteMoveItemsToDispatcherForLoadingParts)(AlgorithmBase *base);
	bool	(*DLL_ExecuteCopyItemsFormDispatcherForParts)(AlgorithmBase *base);
	bool	(*DLL_ExecuteRemoveItemFormDispatcher)(AlgorithmBase *base);

	ExeResult	(*DLL_ExecuteInitialAfterEdit	)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	(*DLL_ExecuteStartByInspection	)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteCaptured			)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res ,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecutePreAlignment		)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteAlignment			)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecutePreProcessing		)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteProcessing			)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteProcessingRevived	)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecutePostProcessing		)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecutePreScanning		)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteScanning			)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecutePostScanning		)(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	(*DLL_ExecuteManageResult		)(int ExeID ,AlgorithmBase *base,ResultInspection *Res);

	ExeResult	(*DLL_ExecuteMatch				)(int ExeID ,AlgorithmBase *InstBase,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result);

	bool	(*DLL_DrawResultBase)(int32 ShowFixedPhase,AlgorithmBase *InstBase ,ResultBaseForAlgorithmRoot *Res,QPainter & ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage);
	QWidget	*(*DLL_ShowAndSetItems)(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something);
	void	(*DLL_MakeIndependentItems)(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	(*DLL_SetIndependentItemData)(int32 Command
											,AlgorithmBase *InstBase ,int32 TargetPhase,int32 LocalPage,int32 Layer,int32 ItemID
											,AlgorithmItemRoot *Data
											,IntList &EdittedMemberID
											,QByteArray &Something
											,QByteArray &AckData);
	bool	(*DLL_DrawResultDetail)(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList);

	QWidget	*(*DLL_ChangeItemsAttr)(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	(*DLL_SaveItem)(QIODevice *f,AlgorithmItemRoot *item);
	bool	(*DLL_LoadItem)(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase);
	ResultBaseForAlgorithmRoot	*(*DLL_CreateResultBaseForAlgorithm)(LogicDLL *parent);

	AddedDataClass	*(*DLL_LoadAddedResultData )(QIODevice *f ,int32 AddedDataType);
	bool			(*DLL_SaveAddedResultData  )(QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
	void			(*DLL_RemoveAddedResultData)(AddedDataClass *d);

	bool	(*DLL_ReleaseGeneralAlgorithmData)(AlgorithmBase *InstBase ,int32 Command,void *data);
	void	*(*DLL_CreateGeneralAlgorithmData)(AlgorithmBase *InstBase ,int32 Command,void *reqData);
	bool	(*DLL_LoadGeneralAlgorithmData)(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
	bool	(*DLL_SaveGeneralAlgorithmData)(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
	bool	(*DLL_ReplyGeneralAlgorithmData)(AlgorithmBase *InstBase ,int32 Command ,void *data);

	bool	(*DLL_ResultItemToString)(ResultInItemRoot *ItemRes ,QString &RetStrBuf);
	bool	(*DLL_BindSpecialResult)(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest);

	bool	(*DLL_SaveCSVMasterReport)(AlgorithmBase *InstBase, QStringListListCSV &CSVData);


	AlignmentPacketBase	*(*DLL_GetAlignmentPointer)(AlgorithmBase *base ,int localPage, int localX ,int localY,AlgorithmItemRoot *Item ,bool FromGlobal);
	void		(*DLL_GetAlignmentForProcessing			)(AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet);

	bool	(*DLL_IsEdited)(AlgorithmBase *InstBase);
	bool	(*DLL_IsCalcDone)(AlgorithmBase *InstBase);
	void	(*DLL_SetEdited)(AlgorithmBase *InstBase,bool edited);
	void	(*DLL_SetCalcDone)(AlgorithmBase *InstBase,bool calcdone);

	bool	(*DLL_LocalPos2Name)(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name);

	bool	(*DLL_GetNGTypeContainer)(AlgorithmBase *ABAse 
										 , int LibID
										 , LibNGTypeInAlgorithm &NGTypeContainer);
	bool	(*DLL_ReceivePacketDirectComm)(AlgorithmBase *ABase ,LayersBase *Base
											,int32 cmd ,int32 globalPage 
											,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName
											,QBuffer &buff
											,int32 IDForUndo
											,ErrorCodeList &ErrorData);
	
	int32	(*DLL_RegistMacroFunction)(ExportFuncForMacro Functions[],int MaxBuffer);

	bool			InFunc;

	int				PriorityInitialAfterEdit;
	int				PriorityAutoGeneration;
	int				PriorityStartByInspection;
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

	QString			DLLRoot;
	QString			DLLName;

public:
	enum	OperationMode{
		 ModeInitialAfterEdit	=1
		,ModeAutoGeneration		=12
		,ModeStartByInspection	=2
		,ModePreAlignment		=3
		,ModeAlignment			=4
		,ModePreProcessing		=5
		,ModeProcessing			=6
		,ModeProcessingRevived	=13
		,ModePostProcessing		=7
		,ModePreScanning		=8
		,ModeScanning			=9
		,ModePostScanning		=10
		,ModeManageResult		=11
	};

	AlgorithmDLLList(LayersBase *Base);
	AlgorithmDLLList(const AlgorithmDLLList *parent ,LayersBase *Base);
	~AlgorithmDLLList(void);

	bool	LoadDLL(const QString &filename);
	virtual	void	GetExportFunctions(QStringList &Str)	override;

	bool			IsAlgorithm(void);
	QString			GetFileName(void)		const	{	return FileName;	}
	void			SetFileName(const QString &_FileName){	FileName=_FileName;		}
	bool			GetOrganization(QString &str);
	WORD			GetDLLType(void);
	bool			GetName(QString &Root ,QString &Name);
	bool			GetName(void);
	WORD			GetVersion(void);
	const QString	GetExplain(void);
	bool			SetLanguage(int LanguageCode);
	bool			CheckCopyright(QString &CopyrightString);
	const char		*GetBlobName(void);
	DWORD			GetAlgorithmType(void);
	AlgorithmBase	*InitialAlloc(LayersBase *Base);
	void			ReleaseAlgorithmBase(AlgorithmBase *Point);
	bool			CheckDLL(const QString &root, const QString &name)	{	return (DLLRoot==root && DLLName==name)?true:false;	}
	QString			GetDLLRoot(void)	const	{	return DLLRoot;		}
	QString			GetDLLName(void)	const	{	return DLLName;		}
	bool			CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);

	AlgorithmLibraryContainer	*NewLibrary(LayersBase *Base);
	int				GetPriority(int PriorityTypeBit_Type);

	void	SaveAlgorithmDefFile(QTextStream &FStr,QStringList &EffectiveAlgoFileNames);
	void	SetPriorityDetail(OperationMode mode,int priority);
	int		GetPriorityDetail(OperationMode mode);
	void	SetPriority(const AlgorithmDefList &Def);

	bool	ExecuteMoveItemsToDispatcherForLoadingParts(AlgorithmBase *base);
	bool	ExecuteCopyItemsFormDispatcherForParts(AlgorithmBase *base);
	bool	ExecuteRemoveItemFormDispatcher(AlgorithmBase *base);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEdit		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteStartByInspection	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteCaptured				(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res ,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignment			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteAlignment			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecutePreProcessing		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteProcessing			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteProcessingRevived	(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecutePostProcessing		(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecutePreScanning			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteScanning				(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecutePostScanning			(int ExeID ,AlgorithmBase *base,ResultBaseForAlgorithmRoot *Res);
	ExeResult	ExecuteManageResult			(int ExeID ,AlgorithmBase *base,ResultInspection *Res			);

	ExeResult	ExecuteMatch			(int ExeID ,AlgorithmBase *InstBase,ImagePointerContainer &TargetImages,int cx, int cy ,double &Result);

	bool	DrawResultBase(int32 ShowFixedPhase ,AlgorithmBase *InstBase ,ResultBaseForAlgorithmRoot *Res,QPainter & ,QImage *IData ,int MovX ,int MovY ,double ZoomRate,int localPage);
	QWidget	*ShowAndSetItems(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data,ShowAndSetItemsBaseClass *Something);
	void	MakeIndependentItems(int32 TargetPhase,int32 localPage ,bool SubResultMoving, int localX ,int localY,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	SetIndependentItemData(int32 Command
									,AlgorithmBase *InstBase ,int32 TargetPhase,int32 LocalPage,int32 Layer ,int32 ItemID
									,AlgorithmItemRoot *Data
									,IntList &EdittedMemberID
									,QByteArray &Something
									,QByteArray &AckData);
	bool	DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList);

	QWidget	*ChangeItemsAttr(QWidget *parent, int32 Command ,AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);

	bool	SaveItem(QIODevice *f,AlgorithmItemRoot *item);
	bool	LoadItem(QIODevice *f,AlgorithmItemRoot *item,LayersBase *LBase);
	ResultBaseForAlgorithmRoot	*CreateResultBaseForAlgorithm(LogicDLL *parent);

	AddedDataClass	*LoadAddedResultData (QIODevice *f ,int32 AddedDataType);
	bool			SaveAddedResultData  (QIODevice *f ,AddedDataClass *d ,int32 AddedDataType);
	void			RemoveAddedResultData(AddedDataClass *d);

	bool	ReleaseGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *data);
	void	*CreateGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command,void *reqData);
	bool	LoadGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
	bool	SaveGeneralAlgorithmData(AlgorithmBase *InstBase ,QIODevice *f,int32 Command ,void *data);
	bool	ReplyGeneralAlgorithmData(AlgorithmBase *InstBase ,int32 Command ,void *data);

	bool	ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff);
	bool	BindSpecialResult(ResultInItemRoot *ItemRes ,ErrorGroupPack &Dest);

	bool	SaveCSVMasterReport(AlgorithmBase *InstBase, QStringListListCSV &CSVData);


	AlignmentPacketBase	*GetAlignmentPointer(AlgorithmBase *base ,int localPage, int localX ,int localY,AlgorithmItemRoot *Item ,bool FromGlobal=true);
	void		GetAlignmentForProcessing		 (AlgorithmBase *base ,int localPage, AlignmentPacketBase &Packet);

	bool	IsEdited(AlgorithmBase *InstBase);
	bool	IsCalcDone(AlgorithmBase *InstBase);
	void	SetEdited(AlgorithmBase *InstBase,bool edited);
	void	SetCalcDone(AlgorithmBase *InstBase,bool calcdone);

	bool	LocalPos2Name(AlgorithmBase *Base ,int Page ,int XLocalPos, int YLocalPos ,QString &Name);
	bool	GetNGTypeContainer(AlgorithmBase *ABase 
							,  int LibID
							,  LibNGTypeInAlgorithm &NGTypeContainer);
	bool	ReceivePacketDirectComm(AlgorithmBase *ABase ,int32 cmd ,int32 globalPage ,const char *EmitterRoot ,const char *EmitterName ,const char *ClassName,QBuffer &buff,int32 IDForUndo,ErrorCodeList &ErrorData);
	int		RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer);
};

class	AlgorithmDefList : public NPList<AlgorithmDefList>
{
public:
	QString	Str;
	int		PriorityInitialAfterEdit;
	int		PriorityAutoGeneration;
	int		PriorityStartByInspection;
	int		PriorityPreAlignment;
	int		PriorityAlignment;
	int		PriorityPreProcessing;
	int		PriorityProcessing;
	int		PriorityProcessingRevived;
	int		PriorityPostProcessing;
	int		PriorityPreScanning;
	int		PriorityScanning;
	int		PriorityPostScanning;
	int		PriorityManageResult;

	AlgorithmDefList(void);
	void	SetLine(const QString &DefStr);
};


class	AlgorithmDLLContainer : public NPListPack<AlgorithmDLLList>,public ServiceForLayers
{
	NPListPack<AlgorithmDefList>	AlgorithmDef;
public:
	AlgorithmDLLContainer(LayersBase *Base)
		:ServiceForLayers(Base){}

	int		SearchAddDLL(RootNameListContainer &AlgoList ,LayersBase *Base ,const QStringList &AlgorithmPath,bool LoadAll);
	int		CopyAddDLL(const AlgorithmDLLContainer *Parent);
	bool	LoadOneDLL(LayersBase *Base ,const QString &DLLFileNameWithPath);
	bool	LoadAlgorithmDefFile(void);
	bool	SaveAlgorithmDefFile(QStringList &EffectiveAlgoFileNames);
	AlgorithmDefList	*SearchDef(const QString &AlgoFileName);
	bool	CheckSystemVersion(QStringList &Str);

};

#endif